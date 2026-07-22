# AGENTS.md — kotek (core framework, layer 1)

> Living document. Every agent working in this repo MUST read this first and MUST
> update the Task Registry (status + date + notes) when it advances or finishes a task.
> Last updated: 2026-07-21 (initial creation after full codebase analysis).

## 1. What kotek is

kotek is **layer 1** of a three-layer stack:

```
┌─────────────────────────────────────────────┐
│ layer 3: game / business logic (user code)  │  ← not this repo, not built yet
├─────────────────────────────────────────────┤
│ layer 2: zircon (engine)                    │  ← github.com/wh1t3lord/zircon
├─────────────────────────────────────────────┤
│ layer 1: kotek (core framework)             │  ← THIS REPO (github.com/wh1t3lord/kotek)
└─────────────────────────────────────────────┘
```

**Philosophy (the owner's intent, preserve it):**

1. **Everything is replaceable.** Every module exposes an interface (`ktkI*` in
   `kotek.core.api`). Default implementations register themselves into `ktkMainManager`
   at module init; a user may re-register their own implementation of any slot instead.
   Partial replacement (one module) and total replacement (everything) must both work.
2. **Stable API surface.** Public interfaces should not need breaking changes for a very
   long time. If the default implementation is disliked, the user keeps the interface
   and swaps the implementation — so the framework never "goes legacy" for them.
3. **Minimal toolchain.** CMake + C/C++ only. No Python, no scripting languages, no
   code generators in other languages. Any tool we need we write in C/C++.
4. **Switchable backends & containers.** Standard library (STD/BOOST/custom),
   container category (static/hybrid/dynamic), renderer, window library, allocator,
   logger etc. are all CMake-time switches materialized as `KOTEK_USE_*` macros.
5. **Shrinkable configurations.** From "everything static-linked into kotek.exe" to
   "everything shared (.dll)", with per-library override. Current default must stay the
   default: plain `cmake ..` → all modules `.lib` + `kotek.exe` (+ `game.ktk` user lib).
6. **Multi-OS by design, Windows first.** OS abstraction via `kotek.core.os[.win32|.linux]`.
   Console platforms (PS4/PS5/Xbox/Switch) are NDA-bound → platform layer must exist,
   but platform code cannot live in the public repo. (PS3 is unrealistic for a C++20
   codebase — treat as dropped unless the owner insists.)

## 2. Module conventions (follow exactly)

- Modules are flat siblings under `kotek/src/`, named `kotek.<layer>[.<group>[.<name>[.<backend>]]]`
  (e.g. `kotek.core.containers.vector`, `kotek.render.bgfx`, `kotek.core.os.win32`).
  Directory name == CMake target name.
- Internal layout per module:
  ```
  kotek.x.y/
  ├── CMakeLists.txt          # add_library(${PROJECT_NAME} STATIC ...) today
  ├── include/
  │   ├── kotek_x_y.h          # umbrella header (path with _ instead of .)
  │   └── kotek_std_alias_*.h  # "std alias" headers exposing types
  └── src/
      └── main_x_y_dll.cpp     # module entry: InitializeModule_* / ShutdownModule_*
  ```
- Cross-module includes use the repo `src` root as base:
  `#include <kotek.core.defines.static.cpp/include/kotek_core_defines_static_cpp.h>`
- **Registration pattern** (how default impls are installed), in `main_*_dll.cpp`:
  ```cpp
  ktkFileSystem* p_instance = new ktkFileSystem();
  p_instance->Initialize(p_manager->Get_EngineConfig());
  p_manager->Set_FileSystem(p_instance);        // service-locator slot
  ```
  Shutdown reverses it (dynamic_cast back, `delete`, `Set_* (nullptr)`).
  `ktkMainManager` (`kotek.core.main_manager`) holds one raw-pointer slot per interface.
- Aggregator modules (e.g. `kotek.core.containers`) only link their children PUBLIC.
- Modules are added in `kotek/CMakeLists.txt` via plain `add_subdirectory` **in
  dependency order** — there is no per-module cmake macro. Keep that order sane.

## 3. Container taxonomy (core concept — do not break)

| Category | Backed by | Reallocation | Header pattern |
|---|---|---|---|
| **static** | ETL (`etl::vector` etc.) | never; fixed capacity | `kotek_std_alias_static_<name>.h` |
| **hybrid** | `std::pmr` (or boost pmr) over inline buffer + `monotonic_buffer_resource` | optional (`Realloc` template param; upstream = default or `null_memory_resource`) | `kotek_std_alias_hybrid_<name>.h` |
| **dynamic** | `std`/`boost` with `KOTEK_USE_MEMORY_ALLOCATOR_CLASS` | always | `kotek_std_alias_<name>.h` |

- All aliases live in `Kotek::ktk`; `_t` twins are exported at `Kotek::` scope.
- Umbrella headers map `ktk_<name>` to one category via `KOTEK_USE_LIBRARY_TYPE_EMB/DYN/HYB`
  + `static_assert(is_same_v<...>)` + `#error unknown configuration`.
- Allocator: `KOTEK_USE_MEMORY_ALLOCATOR_CLASS` = `mi_stl_allocator` (mimalloc) or
  `std::allocator`, from `KOTEK_MEMORY_ALLOCATOR_CPU` (see `kotek.core.memory.cpu`).

## 4. Configuration system (how KOTEK_* works)

1. CMake cache vars (settable with `-D`): e.g. `KOTEK_STD_LIBRARY=STD|BOOST`,
   `KOTEK_LIBRARY_TYPE=EMB|DYN|HYB`, `KOTEK_CONFIGURATION_TYPE=minimal|...`,
   `KOTEK_DEPS_FOLDER=vcpkg|nuget`, `KOTEK_DEVELOPMENT_TYPE=SHARED|STATIC`,
   `KOTEK_GAME_OUTPUT_LIBRARY_NAME=game.ktk`, `KOTEK_MATH_LIBRARY=GLM|DXM`,
   `KOTEK_WINDOW_LIBRARY=GLFW`, `KOTEK_ECS_BACKEND=PICO`, profilers, tests, …
   (full list: `kotek/CMakeLists.txt` + `kotek.core.defines.static.*/CMakeLists.txt`).
2. `kotek.core.defines.static.*` modules accumulate `-DKOTEK_*` compile definitions
   (PUBLIC → propagate everywhere).
3. The same modules `file(APPEND)` a generated header
   `kotek.core.defines.static.cpp/include/kotek_std_preprocessors.h`
   translating `KOTEK_X` → `#define KOTEK_USE_X`. **Code only ever tests `KOTEK_USE_*`.**
4. Namespace names themselves are macros: `KOTEK_BEGIN_NAMESPACE_KOTEK/_CORE/_KTK/...`,
   qualifiers `kun_kotek` / `kun_core` / `kun_ktk` (or uppercase `KUN_*`).

## 5. Dependency management (three modes, keep all three working)

- **vcpkg** (current default for `minimal`): auto-cloned into `kotek/vcpkg/` at
  configure time by `kotek/cmake/windows/vcpkg_nuget_minimal.cmake`, classic mode
  (`vcpkg install pkg:x64-windows`, one call per package), toolchain included directly.
- **nuget**: `kotek/cmake/windows/nuget.cmake` picks a
  `WinXX-Msvc-Packages[-Minimal].config` by OS build number, restores
  `Kotek.Packages.*` packages into `kotek/nuget/packages/`, validates layout.
- **manual**: every `find_package` has a second branch with
  `PATHS "../../${KOTEK_DEPS_FOLDER}/..."`. UX of manual mode is currently poor
  (task K10).
- Rule: **no new third-party dependency** without owner approval. Prefer no-dep
  own implementation when reasonable; keep the "no-dependencies + kotek's own impl"
  configuration buildable for every module.

## 5a. Linkage scenarios (added 2026-07-22, task K18)

`cmake/library.cmake` implements the three output scenarios the owner requires;
`KOTEK_LINKAGE` selects one globally, `KOTEK_LINKAGE_FORCE_STATIC/FORCE_SHARED`
override per module:

1. **STATIC** (default): everything `.lib` into `kotek.exe`. Cycles tolerated.
   Status: **green, validated**.
2. **SHARED** = "dll implicit" (load-time): modules are `.dll` + import `.lib`,
   consumers call exports directly (`WINDOWS_EXPORT_ALL_SYMBOLS`; data globals
   still need export macros). Requires an **acyclic** module graph — kotek's
   graph is currently cyclic (272 edges) so full-SHARED kotek does not
   generate; zircon layer minus the editor cluster works (see zircon Z9).
3. **PLUGIN** = "dll explicit" (run-time): feature modules are `.dll`s loaded
   by `LoadLibrary`/`GetProcAddress` at startup. Each module keeps its
   `InitializeModule_*/ShutdownModule_*` entry points, registered via
   `kotek_add_library(... INIT x SHUTDOWN y)` and compiled into
   `kotek_plugin_manifest.h` (generated into `<build>/generated/`).
   Orchestrators call entries through `KOTEK_INVOKE_MODULE_INIT/SHUTDOWN`
   (`KOTEK_INVOKE_MODULE_INIT_V` for version-taking render backends), which
   compile to direct calls in modes 1-2 and to `ktkPluginInvoke*` (implemented
   in `kotek.core.main_manager/src/kotek_plugin_invoke.cpp`, dll handles
   cached, `ktkPluginUnloadAll` at shutdown) in mode 3. Static leaves
   (defines/types/constants/containers/enum/casting/api/main_manager/utility/
   math/format/pch/game — `KOTEK_PLUGIN_STATIC_MODULES` + prefix groups) are
   linked into whichever binary needs them. `kotek_target_link_libraries`
   erases link edges to plugin modules and propagates only usage requirements
   (genex include dirs/defs) — **plugin code may only talk to other modules
   through `ktkMainManager` interfaces; a direct call fails at link time. That
   is the enforcement of interface purity.**
   Known constraints: allocation ownership across dll boundaries (memory.cpu
   override story, task K9), duplicated static-leaf state per dll (documented,
   acceptable for stateless/header-only leaves), plugin init ORDER matters
   (engine_config before filesystem...) — orchestration order is preserved by
   the converted orchestrators, runtime validation pending.

### Validated configuration matrix (2026-07-22, all Debug builds 0 errors)

| # | Configuration | cmake flags | Status |
|---|---|---|---|
| 1 | full static (default) | `cmake ..` | **green** |
| 2 | kotek static + zircon dlls | `-DKOTEK_LINKAGE_FORCE_SHARED="zircon.core;zircon.ecs;zircon.editor;zircon.game;zircon.game.session;zircon.render;zircon.world"` | **green** (editor cluster forced static — cyclic, Z9) |
| 3 | kotek dlls (PLUGIN) + zircon static | `-DKOTEK_LINKAGE=PLUGIN -DKOTEK_LINKAGE_FORCE_STATIC="zircon.*"` | **green** (27 plugin dlls) |
| 4 | kotek.exe + game.ktk | default `KOTEK_DEVELOPMENT_TYPE=SHARED` | **green** (= #1) |
| 5a | PLUGIN + zircon partial dll | `-DKOTEK_LINKAGE=PLUGIN -DKOTEK_LINKAGE_FORCE_SHARED="zircon.ecs;zircon.world"` | **green** |
| 5b | static + kotek partial dll | `-DKOTEK_LINKAGE_FORCE_SHARED="kotek.render.bgfx;kotek.core.filesystem"` | **green** |
| 6 | kotek all-dll implicit | `-DKOTEK_LINKAGE=SHARED` | blocked: cyclic module graph (needs Z9-style cycle work in kotek) |

Gotchas proven by the matrix: implicitly-linked dlls must NOT use PCH
(`kotek_target_precompile_headers` degrades to `/FI` for them — the PCH
sentinel breaks CMake's create_def); plugin dlls export only their
`Initialize/Shutdown/Serialize/DeserializeModule_*` contract via a generated
minimal `.def`.

## 6. Coding style

- `#pragma once` (never include guards in own code). `.clang-format` at repo root.
- Classes `ktkPascalCase`, interfaces `ktkIName`, backend classes in sub-namespace
  (`Kotek::Render::gl::ktkRenderDevice`), members `m_` / `m_p_`, aliases `*_t`,
  enum values `k`-prefixed.
- Diagnostics via `KOTEK_ASSERT / KOTEK_TRACE / KOTEK_MESSAGE[_WARNING/_ERROR]`.
- Comments: English Doxygen preferred (`\~english` / legacy `\~russian` tags exist);
  new comments in English.
- C++20, MSVC static runtime (`/MT[d]`), `NOMINMAX`. Windows-only today
  (`kotek/CMakeLists.txt` FATAL_ERRORs on other OS).

## 7. Build

```bash
mkdir build && cd build
cmake ..            # default = minimal config, vcpkg deps, all static + kotek.exe + game.ktk
cmake --build .     # or open the generated solution
```
Outputs: `build/bin` (exe/dll), `build/lib` (static libs). Last used generator on the
owner machine: `Visual Studio 18 2026`.

## 8. Known issues / debts (verified 2026-07-21 — fix when touched)

- **CRT consistency (resolved 2026-07-22, validation pending)**: `/MT` restored in
  `cmake/windows/compiler_globals.cmake`; vcpkg deps follow via
  `KOTEK_VCPKG_TRIPLET` (default `x64-windows-static`) wired in
  `kotek/CMakeLists.txt` + both `vcpkg_nuget*.cmake`. If you ever switch CRT to
  `/MD`, switch the triplet to `x64-windows` too — mixing fails with LNK2038.
- **SHARED linkage limitations** (`KOTEK_LINKAGE=SHARED`, K18):
  `WINDOWS_EXPORT_ALL_SYMBOLS` exports functions but not data globals;
  circular target dependencies (tolerated by .lib) break .dll linking —
  **measured 2026-07-22: kotek's module graph is deeply cyclic (272 back-edges),
  so all-.dll does not generate.** Paths to all-SHARED: (a) merge cyclic
  clusters into bigger DLLs, (b) split header-only/INTERFACE parts out of the
  cycles, (c) keep kotek static and ship upper layers as DLLs (works today).
  Zircon's own module graph is acyclic — `KOTEK_LINKAGE_FORCE_SHARED` on the
  zircon modules generates cleanly.
- **Handling rules for mixed .lib/.dll marking** (validated 2026-07-22):
  (1) a module may be SHARED only if its symbol-usage graph with its
  dependencies is acyclic — declared `target_link_libraries` edges are NOT
  enough, actual usage matters (static linking hides undeclared usage);
  (2) cyclic clusters must be merged into one DLL or refactored to talk
  through interfaces registered in the locator (the ktkI* pattern);
  (3) a SHARED module's import lib must be linked by every consumer — with
  `kotek_add_library` + PUBLIC links this is automatic, but modules that
  historically relied on "the exe links everything" must declare their real
  dependencies;
  (4) data globals crossing DLL boundaries need explicit export macros —
  avoid them, prefer accessor functions.
- **HYB library type cannot compile**: `kotek_std_alias_hybrid_{deque,queue,list}.h`
  are 0-byte but umbrella headers static_assert them under `KOTEK_USE_LIBRARY_TYPE_HYB`.
- **Custom new/delete leak tracker is dead code**: guarded by `#ifdef KOTEK_DEBUG` in
  `kotek.core.memory.cpu/src/kotek_std_memory.cpp`, but `KOTEK_DEBUG` is only defined
  by the *zircon* root CMake, not kotek's. Only mimalloc-new-delete is active. (Task K9.)
- `hybrid_vector_impl::is_static()` returns `Realloc` (inverted);
  `hybrid_vector_impl::swap()` throws unconditionally.
- `ktk::memory::expand/strndndup` stubs return nullptr without mimalloc.
- `KOTEK_CPP_ASAN` genex check in `kotek/CMakeLists.txt` is broken.
- `kotek.render.dx12` commented out; ANGLE modules only in non-minimal configs.
- Interfaces in `kotek.core.api/kotek_api.h` are pure C++ (no C ABI) — binary-level
  cross-compiler replaceability is not guaranteed (see validation notes, task K3).
- ~130 micro-modules: fine-grained replaceability but heavy configure/IDE cost.
- Recurring TODO clusters: `kotek.render.gl` buffer reallocations/sync,
  `kotek.core.containers` unimplemented `shared_mutex/semaphore`, `kotek.game` update
  loop cleanup, `kotek_api.h` ~15 TODOs. Grep `TODO|FIXME` before editing a module.

## 9. Task Registry (owner's tasks — update status as work happens)

Status values: `open` / `in-progress` / `done` / `blocked` / `dropped(reason)`.

| ID | Task | Status | Notes |
|----|------|--------|-------|
| K1 | Project compiles (default config, owner machine) | done (2026-07-22) | all kotek modules + zircon build green in Debug. Fixed: `try_emplace<Args>` pack-expansion in hybrid map headers, VS2026 `_MSC_VER 1951`, `/FS` vs C1041, stale-cache configure pitfall (wipe `build/` if find_package fails on installed packages). **Deviation: /MD CRT — see §8** |
| K2 | C/C++ tool: parse CMakeLists → VS .sln/.vcxproj for **VS17/19/22 only** (VS2013 dropped by owner 2026-07-22 — it can't compile C++20 and its format is obsolete) into `ide/vs/vs{17,19,22}`; offline files are a hedge against CMake removing old generators. `.bat`-buildable without cmake; CMakeLists for the tool; C++20 task-based; streaming; fixed buffers via pmr (no-realloc), buffer sizes in a config header; <1 MB RAM target; auto-detect installed VS via official ways (vswhere/registry); buildable by highest installed VS; regeneration flow: manual .bat / `cmake ..` hook / CI artifact | open | parser scope: kotek/zircon CMake dialect subset (proposed, not yet confirmed by owner) |
| K3 | Validate architecture & plans | done (2026-07-21) | verdict delivered in chat; key points in §10 |
| K4 | Per-module backend config matrix: {no-deps+kotek impl} / {deps backends} / {user impl}; add missing `KOTEK_USE_*_USER_IMPL`-style guards where absent | open | pattern must be uniform across modules |
| K5 | GitHub CI/CD: compile EACH module isolated (all supported backends; skip user-impl) + whole solution; free plan; disk-space strategy (vcpkg binary cache / ccache; public repo ⇒ unlimited minutes, cache limit 10 GB) | open | no GH workflows exist yet; only legacy azure-pipelines.yml |
| K6 | CMake command printing all kotek options + meaning (help) | open | e.g. `cmake -D KOTEK_HELP=ON` or custom target |
| K7 | Short, laconic documentation of kotek concepts | open | explicitly LAST task |
| K8 | AGENTS.md progress tracking | done (2026-07-21) | this file; keep updating |
| K9 | Fix new/delete override situation (mimalloc problems; dead leak tracker) | open | see §8 |
| K10 | Deps UX: nuget (github.com/wh1t3lord/kotek-nuget), vcpkg-only, manual folder mode; flags to select; make manual mode friendly (no hand-typed path lists) | open | validate all three modes actually work |
| K11 | Delete GAPI/render backends except bgfx; add NVIDIA NRI backend (kotek + zircon) | open | delete: gl/gles/angle/vk (+software? confirm); keep bgfx; new `kotek.render.nri` |
| K12 | Final commit+push via `git acp "msg"` | blocked | ⚠ alias `acp` does NOT exist in git config — define it or use explicit add/commit/push; kotek is a submodule (commit there separately, then bump in zircon) |
| K13 | ImGui: analyze multi-context support; design MT-safe usage | done (2026-07-22) | ANALYSIS: Dear ImGui supports multiple ImGuiContexts, but the current-context pointer (GImGui) is a plain global, NOT thread-local — concurrent multi-context use across threads is unsafe by default. Only two safe models, both now supported: (1) single-UI-thread (default, unchanged); (2) context-per-thread + serialization. IMPLEMENTED: `ktkIImguiContextManager` (kotek.core.api) + `ktkImguiContextManager` (kotek.ui.imgui, owned by the wrapper, exposed via `ktkIImguiWrapper::Get_ContextManager`); per-thread `CreateContextForThread`/`BindThreadContext` (thread_local binding), `Lock`/`Unlock` (mutex + SetCurrentContext to the caller's context), RAII `ktkImguiLockGuard` in `kotek_ui_imgui_context_manager.h`, debug asserts on unbound/no-context use; editor imgui pass adopts its context as the default. Zircon editor/game sessions should map 1:1 to named contexts when MT UI is enabled |
| K14 | Video: dav1d as default backend behind `ktkIVideoPlayer*`; document that own codec impl is out of scope; design user-backend hook | open | current: `kotek.ui.videoplayer[.avif]` |
| K15 | Decide whether kotek keeps render backend projects at all (vs. zircon-only); position kotek as standardization layer | open | see §10 |
| K16 | Produce & upload NuGet packages to owner's nuget.org account | blocked | needs API key from owner (use CI secret) |
| K17 | Implement the planned-but-missing backends | open | enumerate after K11/K15 decisions |
| K18 | CRT consistency + linkage model (all-.lib / all-.dll / mixed per-module) | in-progress (2026-07-22) | DONE: /MT + `KOTEK_VCPKG_TRIPLET=x64-windows-static` (green); `cmake/library.cmake` with THREE scenarios — STATIC (green, validated), SHARED implicit (works for acyclic layers; kotek itself is cyclic=blocked), PLUGIN explicit (manifest + `ktkPluginInvoke*` + `KOTEK_INVOKE_MODULE_*`; configure+link pass). PLUGIN status: **green (2026-07-22, see K20)** — 27 plugin DLLs + `game.ktk` + `kotek.exe` link with 0 errors; runtime validation still pending. Supporting fixes made: vcpkg toolchain now included every configure; global `find_package(... GLOBAL)` hoist block; `kotek_finalize_plugin_links` BFS pass; `pkg_check_modules GLOBAL dav1d`; `format` links fmt on Windows (latent bug); explicit deps added (main_manager/os.win32/filesystem.path/console-see-K20) |
| K19 | C++17 compatibility for Windows XP targets | open | switch added 2026-07-22: `KOTEK_WINDOWS_XP=ON` (or `-DKOTEK_CPP_STANDARD=17`) in `compiler_globals.cmake` + `KOTEK_USE_CPP_STANDARD` def; needs `v141_xp` toolset. Audit not done: known C++20-only hotspots — `std::format` (kotek.core.format), concepts, consteval; codebase must compile under BOTH standards |
| K20 | Interface purity for PLUGIN/SHARED modes (worklist) | done (2026-07-22) | **PLUGIN build is GREEN: 0 errors** (was 191; 27 plugin DLLs + `game.ktk` + `kotek.exe` all link; STATIC build kept green too). What was done per hotspot: (1) **console**: `ktkIConsole` gained `Push_Command`/`Execute_Command(enum_base_t, console_command_args_t)` + `Flush` (signatures identical to `ktkConsole`; the `console_command_*` aliases moved from `kotek_console.h` to `kotek_api.h`); new `ktkMainManager` slot `Set_/Get_Console`; `kotek.core.console` creates+owns the instance at module init; zircon fetches it from the slot (static_cast only because `Register_Command` is a template, no more `new/delete`); `ktkIGameManager::GetConsole` now returns `ktkIConsole*` — all enum-arg calls became vtable dispatches (incl. vk swapchain's). (2) **render pass bases**: `kotek_render_graph_simplified{,_render_pass}.{h,cpp}` moved `kotek.render.{gl,bgfx}` → `kotek.render.shared.{gl,bgfx}` (static leaves; namespaces unchanged; umbrellas updated); gl's `ktkRenderShaderManager`/`ktkRenderGeometryManager`/`ktkRenderBuffer` also moved to `shared.gl` (zircon's gles3 passes call them directly); gl's `Get_ManagerShader/Geometry` inlined for the same reason; `ktkIRenderResourceManager` gained default-noop `Update()` (gl/bgfx override) so zircon renderers route through it; `angle.gles23` links shared.gl now (non-minimal config, untested). (3) **ImGui**: `ktkIImguiWrapper` extended additively (`ImGui_ImplVulkan_Shutdown`, `ImFontConfig_Create`, `FontAtlas_AddFontFromMemoryTTF/GetGlyphRangesCyrillic/GetTexDataAsRGBA32/SetTexID`); zircon's 4 imgui passes + vk's `kotek_render_imgui_manager` route every ImGui call through the wrapper (no raw `ImGui::` remains). (4) **gl/vk residuals**: gl declares real deps `kotek.render.shared`+`shared.gl` (ktkShaderModule/ktkBufferModule/ktkRenderStats); vk links `kotek.core.memory.gpu.vulkan` — demoted to static leaf (allocator backend, same rationale as memory.cpu). (5) **tests**: `RegisterAllTests` body + kotek.core's `tests/` sources + zircon's unit-test sources & registrar calls guarded with `#if !defined(KOTEK_USE_LINKAGE_PLUGIN)` (tests instantiate concrete classes across modules = static-mode-only feature). (6) **serialize orchestration**: new `KOTEK_INVOKE_MODULE_SERIALIZE/DESERIALIZE[_NS]` macros + `ktkPluginInvokeSerialize/Deserialize` (verb-derive the init symbol, manifest lookup, GetProcAddress); manifest emits `KOTEK_ENTRY_` flags for serialize/deserialize symbols; all ~16 orchestrator call sites converted (os/window/window_manager/memory/memory.gpu/profilers/filesystem/core/ui/ui.videoplayer/kotek.game); `kotek.core.filesystem` declares its real dep `kotek.core.containers.filesystem`. (7) **window glue**: `ktkIWindowConsole` added to the API; `ktkWindowConsole` implements it, `kotek.core.window` creates+owns it (new `Set_/Get_WindowConsole` slot), zircon uses the slot; `ktkIWindow` gained `HideWindow`+`RegisterUserMainManager` (ktkWindow overrides); `ktkWindowSplash` moved `kotek.core.window` → `kotek.game` (the bootstrapper needs it before any plugin loads). (8) **`__` export bug**: CMake's `create_def` truncated the MSVC PCH sentinel `__@@_PchSym_@00@...` to `__` in exports.def; any DLL linking 2+ PCH-bearing static libs got an ambiguous match (LNK4022/LNK2001) — fixed in `library.cmake`: PLUGIN-mode plugin DLLs now export ONLY their module contract (`Initialize/Shutdown[/Serialize/Deserialize]Module_*`) via a cmake-generated minimal .def instead of `WINDOWS_EXPORT_ALL_SYMBOLS` (also kills junk data-global exports). (9) `KOTEK_USE_LINKAGE_*` define now applied at zircon root scope too (was kotek-subdirectory-only, zircon's `KOTEK_INVOKE_MODULE_*` macros evaluated the wrong branch). Leftovers: SHARED mode still needs acyclicity work (K18 §8); `angle.gles23` non-minimal config untested; `kotek.core.os.linux` still in the plugin manifest on Windows (pre-existing) |

## 10. Architecture validation summary (2026-07-21)

- **Sound & industry-proven**: service-locator + interface-per-module + static linking
  default = solid. Closest analogues: The Machinery (all-plugin engine), Unreal modules,
  EASTL/ETL-style fixed containers. The replaceable-implementation goal is achievable.
- **Honest limits**:
  - "No breaking changes for hundreds of years" is not literally possible in C++ —
    no stable ABI (vtables, std types, layout). Achievable version: versioned
    interfaces + optional C-ABI boundary for binary plugins + source compatibility.
  - User *extending* an interface with new functions kotek doesn't know: impossible for
    kotek to call them, but possible for the user's own layer via derived interfaces +
    a `QueryInterface(id)`-style mechanism. Recommend adding one to the `ktkI*` base.
  - `.dll` swap works only with identical compiler/ABI unless a C boundary exists.
- Full discussion was delivered to the owner in chat; decisions pending (see questions
  logged in zircon's AGENTS.md §Open Questions).
