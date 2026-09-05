# AGENTS.md — kotek (core framework, layer 1)

> Living document. Every agent working in this repo MUST read this first and MUST
> update the Task Registry (status + date + notes) when it advances or finishes a task.
> Last updated: 2026-09-05 (K25 phase B1: VFM-mapped reads are real behind
> `VFM_READ` — map → 64 KB-chunked copy → unmap, no user-space cache per the
> owner's streaming-first posture; `VFM_CACHE` retired with a one-time warning;
> see the K25 row).

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

## 1a. Module backend philosophy (owner directive 2026-07-23 — keep current)

Every kotek module should, **where reasonable**, offer backends from **popular,
community-proven, well-API-designed libraries** (the way math already does with
GLM/DirectXMath) — chosen because they solve real problems and have deep
community recognition — **plus our own no-dependency implementation** so the
module always builds with zero external requirements. The rule of three for every
module's backend matrix: {own no-dep impl} ∪ {proven open-source backends} ∪
{user-provided impl via the ktkI* interface}. Examples by module:
- math: GLM / DirectXMath / own `kotek_std_math_own.h` (all three landed
  2026-07-24, GLM-parity tested at 1e-5)
- containers: std / boost(+boost::container) / ETL (static) / own pmr hybrids
- logging: spdlog / own
- serialization/json: boost::json / own
- filesystem: native / zlib archives
- window: GLFW / (future SDL)
- UI: ImGui / RmlUi / CEF / own
- ECS: pico_ecs (vendored) / entt / own
- render: bgfx (raster) / NRI (dx12/vk + RT, in progress K11) / user impl
- video: dav1d default / user impl (own codec is out of scope)
- threading: std / TBB

**User-impl mechanism (K4)**: the compile-time backend enum per module is
`KOTEK_USE_<MODULE>_BACKEND_<NAME>`; the "user provides their own
implementation" path is the K21 plugin override system (§5a — drop a
`plugins/<module>.dll` replacement for ANY module, in any linkage mode) or a
direct-path registration of a custom `ktkI*` implementation into the main
manager's service-locator slot at module init. Guards like
`KOTEK_USE_<MODULE>_BACKEND_USER` are added where a compile-time user impl is
meaningful (math is the reference: GLM/DXM/OWN are compile-time switches;
runtime replacement of the math module itself happens via plugins).
Build validation must cover **each combination of these backends**, not only the
default: curated named configurations (minimal / full / no-deps / per-backend
variants) run in CI so backend switches never bit-rot. When adding a new module,
write its entry here in the same form and register its backends in the config
matrix (K4).

## 2. Module conventions (follow exactly)

- Modules are flat siblings under `kotek/src/`, named `kotek.<layer>[.<group>[.<name>[.<backend>]]]`
  (e.g. `kotek.core.containers.vector`, `kotek.render.bgfx`, `kotek.core.os.win32`).
  Directory name == CMake target name.
- **Namespace form**: the real namespace is `Kotek` (capital, renamable via
  `KOTEK_BEGIN_NAMESPACE_KOTEK`); kotek's own code uses the `KUN_*`/`kun_*`
  macros. `kotek.core/include/kotek_core.h` defines lowercase aliases
  (`namespace kotek/core/render = Kotek::Core/...`) and **consumers (zircon and
  above) must use those, never `Kotek::` directly** — the alias layer is what
  keeps the cmake namespace-rename feature working. Direct-`Kotek::` sites are
  debt (measured 2026-07-24: 43 in kotek, 258 in zircon — zircon Z16 sweep).
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
- **Unit tests are living code — always actualized** (owner directive 2026-07-23):
  every test must match the current codebase's contracts; when behavior changes,
  the test changes in the same commit. A test that no longer matches reality is
  refactored or deleted (context decides) — never left rotting. Tests are
  functional proofs of what a class/module PROMISES, not per-method formalities.

## 3. Container taxonomy (core concept — do not break)

| Category | Backed by | Reallocation | Header pattern |
|---|---|---|---|
| **static** | ETL (`etl::vector` etc.) | never; fixed capacity | `kotek_std_alias_static_<name>.h` |
| **hybrid** | `std::pmr` (or boost pmr) over inline buffer + `monotonic_buffer_resource` | optional (`Realloc` template param; upstream = default or `null_memory_resource`) | `kotek_std_alias_hybrid_<name>.h` |
| **dynamic** | `std`/`boost` with `KOTEK_USE_MEMORY_ALLOCATOR_CLASS` | always | `kotek_std_alias_<name>.h` |

- All aliases live in `Kotek::ktk`; `_t` twins are exported at `Kotek::` scope.
- Umbrella headers map `ktk_<name>` to one category via `KOTEK_USE_LIBRARY_TYPE_EMB/DYN/HYB`
  + `static_assert(is_same_v<...>)` + `#error unknown configuration`.
- **Availability vs resolution (verified 2026-07-23)**: `KOTEK_LIBRARY_TYPE`
  (default `EMB`) picks which category `ktk_*` resolves to; the independent
  `KOTEK_STD_LIBRARY_{STATIC,HYBRID,DYNAMIC}_CONTAINERS` switches (all default
  ON) control whether a category is *available* at all. The **embedded
  configuration** consumers like zircon require is: `EMB` + `STATIC=ON`
  (zircon hard-guards this with a force-included `#error` header, zircon task
  Z12); the strict shipping variant additionally sets `HYBRID=OFF DYNAMIC=OFF`
  so those categories are not even declarable. Hardening TODO: make umbrella
  headers include only enabled categories' alias headers and `#error` on
  direct includes of disabled ones (today a disabled category still declares).
- Allocator: `KOTEK_USE_MEMORY_ALLOCATOR_CLASS` = `mi_stl_allocator` (mimalloc) or
  `std::allocator`, from `KOTEK_MEMORY_ALLOCATOR_CPU` (see `kotek.core.memory.cpu`).

## 4. Configuration system (how KOTEK_* works)

1. CMake cache vars (settable with `-D`): e.g. `KOTEK_STD_LIBRARY=STD|BOOST`,
   `KOTEK_LIBRARY_TYPE=EMB|DYN|HYB`, `KOTEK_CONFIGURATION_TYPE=minimal|...`,
   `KOTEK_DEPS_FOLDER=vcpkg|nuget`, `KOTEK_DEVELOPMENT_TYPE=SHARED|STATIC`,
   `KOTEK_GAME_OUTPUT_LIBRARY_NAME=game.ktk`, `KOTEK_MATH_LIBRARY=GLM|DXM`,
   `KOTEK_WINDOW_LIBRARY=GLFW`, `KOTEK_ECS_BACKEND=PICO`,
   `KOTEK_ASSERT_STDERR_ROUTING=ON|OFF`, profilers, tests, …
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

### Plugin overrides (task K21, 2026-07-23)

Users can replace kotek's built-in module implementations with their own
dlls in **every linkage mode** (static .lib / shared .dll / PLUGIN) — the
community-maintenance escape hatch if the original developers abandon a
module. Mechanism:

- `KOTEK_INVOKE_MODULE` is override-first: every module-entry invocation
  first calls `ktkPluginTryOverride(verb, symbol, manager)`
  (`kotek.core.main_manager/src/kotek_plugin_override.cpp`, compiled in ALL
  modes), a tri-state (negative = no override registered → the macro falls
  back to the previous built-in path: direct call in STATIC/SHARED, manifest
  loader in PLUGIN; non-negative = the override entry was called and the
  value is its bool result). No call-site edits were needed.
- The module-name ↔ entry-symbol table (`kotek_plugin_registry.h`) is
  generated by `kotek_generate_plugin_manifest()` in EVERY linkage mode now
  (was PLUGIN-only); folder/target names are the source of truth, so renamed
  folders just rename the override dll.
- Override dlls live in `plugins/` next to the data folders (working
  directory of the exe). Two registration variants, json wins:
  - **A (name convention):** `plugins/<module-folder-name>.dll` (e.g.
    `plugins/kotek.core.containers.map.dll`) automatically overrides that
    module's entries.
  - **B (json config):** `plugins/plugins.json` maps module names to
    user-chosen dll file names:
    `{"modules": {"kotek.core.containers.map": "my_fast_map.dll"}}`.
- Two terminal engine flags (codegen helpers, work in every linkage mode):
  `--kotek_plugins_template` writes `plugins/plugins.template.json` (every
  known module with an empty dll field, ready to fill as variant B) and
  `--kotek_plugins_modules` writes `plugins/plugins.modules.json` (plain
  array of the known module names); each prints a message and exits 0.
- Override dll handles stay loaded for the process lifetime (an override is
  its own module with its own CRT — the module-boundary rules of §8 apply;
  the `bool(ktkMainManager*)` entry contract is boundary-safe). A failed
  load or a missing exported entry logs a warning and falls back to the
  built-in implementation. Overriding `kotek.core.main_manager` itself also
  replaces the flag-handling hook (it lives in that module's init).
- Tests: `kotek.core/tests/kotek_core_test_plugin_override.cpp` + the
  test-double dll `kotek.core/tests/kotek.core.tests.plugin` (plain SHARED
  target that registers its entries into the generated registry). The suite
  follows the module's registrar idiom: `RegisterTests_PluginOverride_
  ForModule_Core` is called from `RegisterAllTests` in main_core_dll.cpp —
  unreferenced gtest TUs in a static lib are dropped archive members, and
  /INCREMENTAL preserves that state, so the reference from the always-linked
  orchestrator obj is what pulls the tests into kotek.exe.

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
- **NO static storage duration (owner directive 2026-08-02 — zircon rule 1a,
  applies to kotek equally).** No file-scope globals, no function-local
  `static`, no static class members: they are hidden module-local singletons
  and the root of this codebase's worst defect classes (the etl
  intrusive-list terminator AV, cross-CRT frees, init-order hazards,
  never-unload lock states). etl `static_cstring`/`static_vector` TYPES are
  unaffected — they name capacity, not storage duration. Replacements in
  preference order: members of the owning class; explicit instances owned by
  a manager/context; singletons as registered services behind interfaces
  (the ktkI* locator). Existing statics are being swept (task K24 —
  `_pLoggerMain`/`_pLoggerMsvcOutput` and friends); new static storage in a
  PR is a defect on sight.
- **Wrappers are the contract (owner directive 2026-09-02).** Framework
  consumers (zircon and every upper layer) never call standard-library or
  third-party functions directly — they call kotek wrappers. New
  functionality enters the ecosystem as a wrapper FIRST, with the backend
  matrix (STD / BOOST / kotek-own / user re-registration); direct
  std/third-party calls live only inside wrapper implementations (and in
  `src/tools` host tools).
- **Test tiers (owner directive 2026-09-02).** Heavy stress suites are gated
  behind `KOTEK_USE_TESTS_HEAVY` (CMake `-DKOTEK_TESTS_HEAVY=ON`, OFF by
  default); every heavy suite keeps a lightweight default tier of the same
  functional proof. Debug boot time is a budget — no test may make the
  default boot meaningfully slower without the flag.

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
- **Assert presentation flag (2026-07-23)**: default = stock modal CRT dialog
  (what users/manual debugging expect). `KOTEK_ASSERT_STDERR_ROUTING=ON` →
  `KOTEK_USE_ASSERT_STDERR_ROUTING`, routes CRT asserts/errors to stderr +
  fail-fast in both binaries (exe entry + game module init); mandatory for
  CI/agents — a modal dialog on a headless runner hangs the job. The flag
  covers CRT-level reports only; `KOTEK_ASSERT` logs through the engine
  logger in every configuration. **Exe-run modal discipline (mandatory for
  agents, 2026-08-01)**: before running ANY built .exe (boot, test runner,
  tool) verify the tree was configured with the routing flag
  (`grep KOTEK_ASSERT_STDERR_ROUTING <tree>/CMakeCache.txt`); keep captures
  bounded (`timeout` + size cap); after the run sweep for stuck modals
  (EnumWindows `#32770` + `tasklist //FI "IMAGENAME eq WerFault.exe"`,
  clear with `taskkill //F //IM <exe>`). A modal an agent cannot click
  blocks all automation — the WER `DontShowUI=1` switch (zircon §5, set on
  the owner's machine 2026-08-01) is the last line of defense for hard
  crashes, not a substitute for the routing flag.
- **Cross-CRT file handles (fixed 2026-07-31)**: the logger bridge
  (`Set_LoggerMain` into game.ktk) shares one exe-constructed logger across
  modules; its file sink was a CRT `FILE*`, and game.ktk's header-inline
  write path uses its OWN CRT, where that handle is invalid — `fwrite`
  failed silently, so `data_user/all.log` stayed empty in SHARED dev type
  while console output looked healthy (the class predates the CUSTOM
  backend — CRT-bound file sinks were always broken in SHARED mode, it was
  simply never noticed). Same family as the etl-terminator and debug-heap
  rules: **per-module CRT state + cross-module inline code do not mix — a
  CRT `FILE*` must never cross a module boundary.** The CUSTOM backend's
  sink is a Win32 `HANDLE` (`CreateFileA`/`WriteFile`/`FlushFileBuffers`,
  valid process-wide, `FILE_APPEND_DATA` for O_APPEND semantics); any future
  file-owning object shared across modules must use OS handles or be
  constructed per consuming module.
- **Generated preprocessors header accumulation (fixed 2026-07-31)**: the
  defines codegen APPENDED to the per-module generated header across
  configures, so flipping a backend in an existing build tree left the old
  backend's defines behind and they silently shadowed the new backend
  (found when a CUSTOM-configured build still ran the spdlog runtime).
  `kotek_add_defines_subdirectory` now resets the header
  (`file(WRITE ... "")`) before appending the current config's sections.
  Rule: reconfiguring an existing tree must be as correct as a fresh
  configure — never append config-specific generated content without a
  reset.
- **Generated preprocessors header lives in the build tree (fixed 2026-07-23)**:
  every defines module generates its own `kotek_std_preprocessors.h` whose
  content is configuration-specific (dev type, library type, capacities).
  It used to be written into the module's SOURCE include dir (relative
  `./include/...`), so two parallel build dirs with different configs
  clobbered each other (a full-static leg compiled with the default leg's
  header and died on `#error engine supports only STATIC or SHARED`).
  `kotek/CMakeLists.txt` now sets `KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS`
  per module via `kotek_add_defines_subdirectory()` to
  `${CMAKE_CURRENT_BINARY_DIR}/<module>/include/...` and the umbrellas
  reference it by the SAME virtual-path convention as the source tree
  (`<kotek.core.defines.XXX/include/kotek_std_preprocessors.h>`) which
  resolves into `${CMAKE_CURRENT_BINARY_DIR}/src` on the module's PUBLIC
  includes — unique per module, no shadowing. The helper also normalizes
  legacy codegen that appended `#pragma once` once per section (13 modules)
  down to a single leading pragma. Rule: config-specific generated files
  belong to the build tree, never the source tree.
- **CI state (2026-07-23)**: GitHub workflows (`build/tests/modules`) run on
  every push but were RED at the configure step on the CI image (vcpkg builds
  the full minimal dep set — vulkan SDK, bgfx, boost-json, tracy, dav1d —
  from source; a port fails there, exact one needs the admin-only job log).
  Local standalone configure+build is green. Fixed so far: vcpkg cache
  trimmed from ~6.5 GB (installed+packages+buildtrees) to ~1.2 GB
  (installed+tool, quota-safe, key v2 hashed on the dep list); kotek
  `tests.yml` is now build-only (runtime gtests need `game.ktk` from zircon —
  they live in the zircon repo's tests workflow, which also runs the real
  engine boot with `KOTEK_ASSERT_STDERR_ROUTING=ON`). Durable fix = vcpkg
  binary caching over the owner's nuget feed (blocked on K16: API key as CI
  secret vs local).
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
- **HYB library type (fixed 2026-08-01)**: was 0-byte
  `kotek_std_alias_hybrid_{deque,queue,list}.h` + static_asserting umbrellas —
  now implemented and CI-covered (see the K4 containers fragment). Found
  pre-existing, still OPEN: DYN-branch defects in container umbrellas
  (`kotek_core_containers_unordered_map.h` maps `ktkUnorderedMap` → misspelled
  `unordered_mapkds`; `kotek_std_alias_filesystem_path.h` DYN branch defines a
  `ktk_array` typo; several DYN branches reference macros that don't exist —
  the DYN library type has never compiled), plus dead duplicate
  `kotek_std_alias_static_array.h` (identical copy of the alias header, never
  included). Fix when the DYN config becomes a target.
- **Custom new/delete leak tracker is dead code**: guarded by `#ifdef KOTEK_DEBUG` in
  `kotek.core.memory.cpu/src/kotek_std_memory.cpp`, but `KOTEK_DEBUG` is only defined
  by the *zircon* root CMake, not kotek's. Only mimalloc-new-delete is active. (Task K9.)
- `hybrid_vector_impl::is_static()` returns `Realloc` (inverted);
  `hybrid_vector_impl::swap()` throws unconditionally.
- `ktk::memory::expand/strndndup` stubs return nullptr without mimalloc.
- `KOTEK_CPP_ASAN` genex check in `kotek/CMakeLists.txt` is broken.
- `kotek.render.dx12` commented out; ANGLE modules only in non-minimal configs.
- **Interfaces in `kotek.core.api/kotek_api.h` are pure C++ (no C ABI) — binary-level
  cross-compiler replaceability is not guaranteed (see validation notes, task K3).
- **Runtime status (2026-07-23, CLEAN RUN)**: `kotek.exe --no_splash
  --kotek_frames=30` boots → 14/14 zircon + 163/163 kotek tests → 30 frames →
  full shutdown → **exit 0**. Earlier fixes: STD-mode `ktkJson::Get` stub →
  `KOTEK_USE_NOT_CUSTOM_LIBRARY`; `dll::shared_library` move semantics;
  `ktk::dll::program_location()`; 8 hybrid-container `throw`s → `KOTEK_ASSERT`;
  `KOTEK_INVOKE_MODULE` unified. 2026-07-23 fixes: (a) console
  `Register_Command` segfault — **etl intrusive-list terminator is a
  module-local static**: a container constructed by the exe terminates buckets
  with an address game.ktk never compares equal to, so cross-module
  insert/erase walks off the bucket (null+8 read). Fixed zircon-side by
  constructing the console in the consuming module (see rule below); the
  earlier `KOTEK_DEF_COMMAND_CONSOLE_COMMAND_STORAGE_COUNT` 128→512 bump was
  NOT the cause but stays as headroom. (b) render shutdown dispatch: stray
  `if (is_gl)` line swallowed the whole else-if chain — bgfx shutdown never
  ran. (c) filesystem: native `Read_File` VFM branch returned false for
  existing files (VFM unimplemented → now falls through to `fopen`); two
  off-by-one terminator writes (`file_size == buffer/cache size` overflowed by
  1 byte); 8 redundant `KOTEK_ASSERT(false)` dropped where the warning right
  after already degrades. (d) `matrix2x2_f::e/c`: 6 inverted range asserts.
  (e) cross-CRT heap frees root-caused + mitigated (see rule below);
  `ShutdownModule_Core_Engine_Config` intentionally leaks the config until K9.
  Residual: ~5 CRT-startup heap asserts; splash window is created on a
  detached thread (bounded-wait mitigation; fix = main thread only).
- **gtest TUs in static libs need the registrar idiom (found 2026-07-23,
  relevant to K22)**: a test .cpp compiled into a module's static lib is an
  unreferenced archive member — the linker drops its obj and the tests
  silently never register, and `/INCREMENTAL` preserves that state across
  rebuilds (the surviving 163 baseline suites are pulled only because
  `RegisterAllTests` in main_core_dll.cpp — an always-linked obj —
  references their `RegisterTests_*` registrars; `main_core_dll.obj`'s
  references drag the test objs into kotek.exe). Any NEW runtime suite must
  (a) live in `kotek.core/tests/` (runtime tests are a kotek.core feature,
  guarded `KOTEK_TESTS + KOTEK_TESTS_RUNTIME + NOT PLUGIN`), (b) define an
  always-compiled empty `RegisterTests_<X>_ForModule_Core` OUTSIDE the
  `KOTEK_USE_TESTS/KOTEK_DEBUG` guards, (c) declare it in `kotek_core.h` and
  call it from `RegisterAllTests`. Also note the second, independent reason
  suites can go missing: the test TU needs `-DKOTEK_TESTS` (from
  `kotek.core.defines.static.tests`) on its compile line — module-local
  tests like `kotek.core.utility/tests/` lack it and compile EMPTY, which
  is why there has never been a `Utility` suite in the 163.
- **Module-boundary rules (verified 2026-07-23, apply to every layer)**:
  (1) any object whose inline/template methods touch **etl intrusive
  containers** must be constructed AND destroyed in the module that uses
  those methods — etl terminators (`intrusive_forward_list_base<TLink>::
  terminator`) are module-local statics, foreign-built containers corrupt
  on cross-module mutation; (2) any **heap-owning** object (std::string /
  containers / `new`d members) must not be freed by a different module —
  `/MT` gives each module its own CRT debug-heap block list, cross-frees
  assert `__acrt_first_block == header` and poison the lists. Today's
  containment: allocation tracking stays ON (do not hide reports), the
  unsound **exit leak dump** (`_CRTDBG_LEAK_CHECK_DF`, force-enabled by
  kotek.core.memory.cpu) is disabled at each module's shutdown, and the
  engine config is intentionally leaked; real fix = **K9 shared
  allocator** so no cross-CRT free exists.
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
| K4 | Per-module backend config matrix: {no-deps+kotek impl} / {deps backends} / {user impl}; add missing `KOTEK_USE_*_USER_IMPL`-style guards where absent | in-progress (2026-07-25) | matrix design in §1a; user-impl mechanism = K21 (§5a). VALIDATION: math is the first fully-covered module — all three backends compile-validated again today post-NRI/Z16 (GLM = default in every build; DXM and KOTEK_OWN via `-DKOTEK_MATH_LIBRARY=DXM|KOTEK_OWN`, 0 errors each, parity suite `kotek_core_test_math_backends.cpp` compiles in both). CI: `matrix.yml` gained `math-dxm` + `math-own` legs (it only had math-glm), fixed the latent `--config Debug` for every leg (minimal-release silently built Debug; now `matrix.cfg` per leg), cache key aligned to the v2+hashFiles scheme of the other workflows, timeout 120→180 (cold-cache dep rebuilds), plus the `deps-manual` leg (K10). PER-MODULE GUARD INVENTORY (2026-07-30 audit, the sweep's concrete backlog): **math** GLM/DXM/KOTEK_OWN ✅ complete+CI; **render** bgfx/NRI-D3D12 ✅ (K11, NRI-VK+RT phase 2); **video** dav1d + own-out-of-scope verdict ✅ (K14); **containers** STD/BOOST/ETL(EMB)/HYB ✅ (`KOTEK_LIBRARY_TYPE`) — HYB FIXED (2026-08-01): hybrid_{deque,list,queue} implemented on the hybrid-vector pmr idiom (bounded monotonic_buffer_resource, null_memory_resource upstream when Realloc=false → overflow throws bad_alloc from the resource, never a silent realloc), `is_static()` inversion fixed in vector, never-compiled latent bugs fixed across map/umap/uset/string (bogus typedefs/members the HYB instantiation finally exposed), `uses_allocator=false_type` propagation guards on all 8 hybrid headers, umbrella HYB branches wired (incl. string's 22 ktk_*string* macros + filesystem path taking the EMB branch), 59/59 container tests via standalone runner, CI leg `containers-hyb` (kotek-scoped — zircon refuses non-EMB by Z12 design); **memory** mimalloc/CRT-OFF ✅ (K9 pending); **string** STD/BOOST + RAW/OPTIMIZED ✅; **logging** SPDLOG/BOOST/CUSTOM — CUSTOM own impl LANDED (2026-07-31): header-only `ktkCustomLogger` in kotek.core.log (spdlog-shaped info/warn/error/trace surface incl. the `{}`-variadic forms the macros emit, one macro set serves both backends in `kotek_std_dependent_preprocessors.h`), spdlog dep skipped in CUSTOM config, `-DKOTEK_LOG_LIBRARY=CUSTOM` configures+links green; two systemic fixes landed with it — (a) the generated preprocessors header was APPEND-ONLY across configures, so a backend flip in an existing build tree left the old backend's defines in place and silently shadowed the new one (reset per configure in `kotek_add_defines_subdirectory` — repairs ALL backend switching, not just logging); (b) the file sink is a Win32 OS handle, not a CRT FILE* (§8 cross-CRT handles), writes mutex-serialized for spdlog `_mt` parity; **UI** RMLUI/CEF/ATHENA guards exist (`KOTEK_UI_GAME_LIBRARY`) — ATHENA is the owner's own UI lib, guard only, zero sources; OWNER DECISION 2026-07-31: skip ATHENA for now (guard stays dormant, UI = RMLUI/CEF + imgui wrapper) — do not start it without a fresh directive; **ECS** pico vendored + `kotek::entity_t` backend alias ✅, ENTT branches are dead `#error todo` code (zircon-side task); **window** GLFW-only — no second backend and no own win32-window alternative registered (K17: SDL or own); **json** BOOST/KOTEK_OWN ✅ (`KOTEK_JSON_LIBRARY`, landed 2026-08-01): own no-dep backend — DOM (`kotek_own_json.h`: 24-byte `value`, single-allocation bodies, pmr-style `static_resource` (sticky-fail + warning on exhaustion, never a crash) / `monotonic_resource`, boost-shaped `tag_invoke` interop so `ktkJson` + every call site in both repos compiles unchanged) + streaming (`kotek_own_json_stream.h`: chunk-safe SAX `stream_reader`/`stream_writer`, fixed buffers, capacities as named #defines, comments/trailing-commas opt-in); boost dep skipped under `KOTEK_OWN`; `parse`/`serialize` + `parser`/`serializer` streaming wrappers for `ktkResourceText`; 10 JsonOwn gtests (roundtrip, unicode/escapes, malformed-graceful, number edges, resource exhaustion, stream↔DOM chunk-invariance at 1/7/63/1023 chunk sizes, every-split-point); first DOM revision was 2× boost's footprint and got reworked until `sys_info.json` fits the 1024-byte static_resource in `ktkResourceText` again; verified: 0 errors full tree, boot exit 0 with 187/187 + 14/14 under KOTEK_OWN; CI leg `json-own`; **threading** std is the only alias provider (`mutex_t` & friends map to `ktk::mt::` std-backed types — the no-dep floor by design) and TBB exists as an explicit opt-in module — NOT a switchable-guard design and that is acceptable (verified 2026-07-30); **logging** guards are INCOMPLETE (verified 2026-07-30): code has `KOTEK_USE_LOG_LIBRARY_BOOST`/`_SPDLOG` branches but `kotek.core.log/CMakeLists.txt` unconditionally requires spdlog whatever the flag says, and the CUSTOM backend exists only as a vestigial output flag — no code, no cmake branch (K17: own logging impl; the cmake find must become flag-conditional when it lands). User-impl = K21 for every row. NEXT: the K17 missing own-backends (window, json, ATHENA, logging-CUSTOM) and the logging cmake flag-conditional find |
| K5 | GitHub CI/CD: compile EACH module isolated (all supported backends; skip user-impl) + whole solution; free plan; disk-space strategy (vcpkg binary cache / ccache; public repo ⇒ unlimited minutes, cache limit 10 GB) | done (2026-07-25) | **ALL THREE WORKFLOWS GREEN on 78cbd58** (build + tests + modules). What it took: vcpkg cache 6.5GB→1.2GB (quota-safe), pin 1bf99941, mimalloc in the dep set, pwsh wildcard sanitize, per-port dep retry, timeouts 90→180, gtest body guard, LNK2038 CRT include order, Tracy `FrameMark` collision + manual-lifetime portfile patch, `contents: write` + clone-based `ci-logs` publishing everywhere, configure retry ×3 with tee'd attempt logs, `restore-keys` cache fallback (the cold-cache tests failure class), math constexpr mismatches (matrix4x4f + vector1f-4f), NRI wiring (OFF propagation, macro dedup). Build legs: Debug-static + Release-static required and green; Debug/Release-dynamic stay continue-on-error by K18 design. matrix.yml (nightly): minimal Debug/Release (per-leg `--config` fixed), plugin-linkage, math-glm/dxm/own. The `ci-logs` branch is the public read path for any future failure |
| K6 | CMake command printing all kotek options + meaning (help) | done (2026-07-25) | `cmake -DKOTEK_HELP=ON` — prints the curated registry in `cmake/options_help.cmake` (name|default|description, 34 entries) and stops before any dep work (fast, no vcpkg fetch). Registry made current: KOTEK_NRI, the three STATIC-dev-type game-module names, per-config profiler defaults (OFF Debug/ON Release), MIMALLOC default + leak-detection interplay, NRI-live renderer notes; the file header carries the rule that every new option joins the registry in the same commit. Two `;`-in-description bugs fixed (semicolons are CMake list separators and split entries). Verified: 0 errors, 38 options print. Paired human doc (owner directive 2026-08-01): `doc/git/en/configuration.md` carries the CMake-option + runtime-argument tables, referenced from the root README — any option/argument change updates BOTH this registry and that file in the same commit |
| K7 | Short, laconic documentation of kotek concepts | open | explicitly LAST task |
| K8 | AGENTS.md progress tracking | done (2026-07-21) | this file; keep updating |
| K9 | Fix new/delete override situation (mimalloc problems; dead leak tracker) | in-progress (2026-07-24 analysis) | tracker made opt-in via `KOTEK_USE_MEMORY_TRACKER` (was silently on in Debug). CURRENT STATE: two allocation paths — (a) mimalloc's own new/delete (`mimalloc-new-delete.h`, active in Release where `KOTEK_MEMORY_ALLOCATOR_CPU=MIMALLOC`), (b) manual global `operator new` in `kotek_std_memory.cpp` (std::malloc + leak-tracker map, active in Debug where leak detection disables the custom allocator). PROBLEMS: (1) the manual override `throw`s `std::bad_alloc` (4 sites) and tracker paths throw `runtime_error` (3 sites) — violates the no-exceptions rule; (2) the Debug CRT-malloc fallback is exactly what creates per-module CRT debug heaps → the whole cross-CRT `__acrt_first_block` assert family (§8); (3) mimalloc instances are per-module too (static link), so Release shares the same cross-heap class in milder form; (4) tracker races + unconditional `CaptureStackBackTrace` cost. PLAN: v1 — purge all `throw`s (assert+fatal semantics, no bad_alloc exceptions); route the Debug fallback through `mi_malloc/mi_free` as well (mimalloc in every config, its own debug checks replace the CRT debug heap's role → kills the cross-CRT assert family at the source); keep the tracker opt-in and make it race-safe (sharded map or mimalloc stats). v2 (the real enabler for free .dll swapping): one shared allocator service behind `ktkIMemoryAllocator` so every module allocates from ONE heap regardless of CRT — needs owner sign-off on the exact mimalloc problem he hit before adopting it everywhere |
| K10 | Deps UX: nuget (github.com/wh1t3lord/kotek-nuget), vcpkg-only, manual folder mode; flags to select; make manual mode friendly (no hand-typed path lists) | in-progress (2026-07-25 wrapper+pilots) | MODE AUDIT: (1) **vcpkg-only** (`KOTEK_DEPS_FOLDER=vcpkg`, the `minimal` configuration) — validated daily, local + all CI legs; the only mode that is green today. (2) **nuget** (empty `KOTEK_DEPS_FOLDER` + non-minimal `KOTEK_CONFIGURATION_TYPE` → `nuget.cmake` + `Win1x-Msvc-Packages[-Minimal].config`) — analyzed kotek-nuget (26 `Kotek.Packages.*.Vcpkg` recipes, vcpkg-built binaries repackaged per win10/win11-msvc-x64 runtime): **the feed is stale for the current build model** — packages are built with the `x64-windows` (/MD) triplet (e.g. tracy 0.11.1 from `tracy_x64-windows`) while kotek is /MT (`x64-windows-static`) since 2026-07-22, and the tracy package also predates the manual-lifetime portfile patch; nuget mode stays legacy until K16 rebuilds + uploads MT packages from the pinned vcpkg (the recipes also carry absolute `vcpkg\packages\` paths — rebuildable only on the layout they were authored on). (3) **manual folder** (`KOTEK_DEPS_FOLDER=<name>`, folder must sit INSIDE the kotek source dir): today each module hardcodes its own subpath (`find_package(Tracy REQUIRED PATHS "../../${KOTEK_DEPS_FOLDER}/Tracy"`) — undocumented, per-module inconsistent, no mapping story. MANUAL-MODE UX DESIGN (the owner's "not hand-typed paths"): convention + one optional mapping file — `<folder>/<DepName>/{include,lib,share}` (vcpkg-style, auto-discovered) with an optional `<folder>/deps.json` (`{"tracy": "D:/libs/tracy", ...}`) for stray layouts; a single `kotek_find_package(<dep> ...)` wrapper in `cmake/` resolves in order: deps.json entry → `<folder>/<DepName>` → system/vcpkg `find_package`. Every module's find call migrates to the wrapper (mechanical, per-module). IMPLEMENTATION: **wrapper + pilots landed (2026-07-25)** — `cmake/kotek_find_package.cmake` (deps.json override → `<folder>/<DepName>/` convention → vcpkg/system fallback, `NO_DEFAULT_PATH` on manual hits; included from the root; `KOTEK_DEPS_FOLDER_PATH` anchored once at the root so module dirs never recompute); pilots migrated: Tracy (`kotek.core.profilers`, the if/else collapsed to one call) and glm (`kotek.core` tests branch + `kotek.core.math`, manual branches only — nuget glob machinery untouched). VERIFIED: deps.json override + convention folder both resolve correctly in isolated `cmake -P` fixtures (the fixture's own config file provably executes); default vcpkg path byte-identical (full Debug build + boot exit 0, 14/14 + 189/189). SWEEP DONE (same day): all 44 hardcoded `find_package(... PATHS "../../${KOTEK_DEPS_FOLDER}/...")` sites across 30 module CMakeLists migrated to `kotek_find_package` (14 shapes: Boost×4, CEF, GTest, TBB, directxmath, etl, fmt, glfw3, mimalloc, spdlog, utf8cpp) — 0 hardcodes remain; regression build + boot green. NOTE the standardization: the old manual scheme was per-module inconsistent (some deps resolved at the folder root, some in subfolders) — the wrapper's documented convention is `<folder>/<DepName>/` (or deps.json), so a pre-existing manual folder may need the one-time re-layout. MANUAL MODE END-TO-END GREEN (same day, standalone `kotek.exe` links): what it took — `KOTEK_CONFIGURATION_TYPE` now defaults to `minimal` in every mode (manual configures previously fell to the BOOST default and died on boost_filesystem, which the minimal set lacks); the root hoist block runs for manual mode too (was vcpkg-only — imported targets like bgfx::bx never existed in module scopes) and goes through the wrapper; `CMAKE_FIND_PACKAGE_PREFER_CONFIG=TRUE` in manual mode (the vcpkg toolchain behavior — module-mode `find_dependency` inside package configs creates partial export sets that kill the later CONFIG find, freetype/PNG); the wrapper bridges ZLIB (static names `zs/zsd` via `ZLIB_USE_STATIC_LIBS` + the `ZLIB::ZLIB`→`ZLIB::ZLIBSTATIC` alias the vcpkg toolchain normally provides); os.win32's manual-mode FATAL stub merged into the vcpkg branch; dav1d's pkg-config branch merged (manual mode needs `PKG_CONFIG`+`PKG_CONFIG_PATH` set — documented for users, set in the CI leg); videoplayer.avif's FATAL stubs gone. USER GUIDE (manual mode): put a vcpkg-style prefix anywhere, `cmake -S . -B build -DKOTEK_DEPS_FOLDER=<folder-name-inside-kotek> -DCMAKE_PREFIX_PATH=<prefix>`, optionally `<folder>/deps.json` for per-dep exact paths, `PKG_CONFIG`/`PKG_CONFIG_PATH` for pkgconf deps (dav1d). matrix.yml gained the `deps-manual` leg proving this on CI nightly. **deps-manual leg ROOT-CAUSED + FIXED (2026-08-01)**: red since the efffb0a nightly — the root `PkgConfig REQUIRED` hoist (plugin-edge-fixup heritage) assumed pkgconf, but pkgconf is a TOOL that only ships inside vcpkg-built trees (`tools/pkgconf/pkgconf.exe`) and manual mode bypasses the toolchain; dav1d has NO CMake config package (`share/dav1d` = copyright/usage only), pkg-config is its only discovery channel. Fix: root hoist → `QUIET` (vcpkg mode unchanged), the avif module resolves `PKG_CONFIG_EXECUTABLE` + `PKG_CONFIG_PATH` from the dep prefixes (`CMAKE_PREFIX_PATH` env + `<folder>/dav1d` convention) in manual mode — no Unix-tool install demanded from a Windows user. Verified with the exact CI recipe locally: configure+build green, dav1d 1.5.3 found via pkgconf from the prefix, vcpkg reconfigure unaffected. NEXT: K16 unblocks the nuget side |
| K11 | Delete GAPI/render backends except bgfx; add NVIDIA NRI backend (kotek + zircon) | in-progress (2026-07-25 phase 1 done) | DELETED: kotek.render.{gl,vk,software,angle.gles,angle.gles23,gl.glad,shared.gl,shared.vk,shared.dx} + zircon render/{gles3,vk}; bgfx kept & de-GL'd. **NRI phase 1 LIVE (2026-07-25)**: `kotek.render.nri` module (`ktkRenderDevice`/`ktkRenderSwapchain`/`ktkRenderResourceManager` over NRI **v180**, D3D12-only, static) — device+queue+cmd alloc/buffer+fence, swap chain (2 back buffers, vsync from config), clear-color present (acquire→barrier→clear→barrier→submit→present, frame-fence paced); resource manager is an honest phase-1 stub (warns, never aborts). Dep: pinned shallow clone into `external/nri` (gitignored) via `cmake/windows/nri.cmake` (`-DKOTEK_NRI=OFF` skips), which also applies an idempotent patch gating NRI's OMM dummy structs on `D3D12_SDK_VERSION < 615` (SDK 26100=616 ships the real ones → C2011 otherwise). Dispatch: the DirectX slot maps to NRI in `main_render_dll.cpp` init+shutdown (both the `--render_dx*` branch and the config-default `is_dx` branch, `KOTEK_INVOKE_MODULE` so K21 overrides apply). New flag `--render_nri_dx12` (constant in `kotek_std_constants.h`): parser maps it to `DirectX_SpecifiedByUser`+`kDirectX_Latest` and engine-config skips the bgfx startup default when present. rmlui manager accepts the DirectX slot. Tests: `kotek_core_test_render_nri.cpp` (4 tests — flag parse + negative control GPU-free; device lifecycle + 3-frame present on a hidden owned HWND, GPU-gated `GTEST_SKIP`). Zircon side: `zircon_renderer_nri` (minimal `ktkIRenderer`, forwards `draw()` to the swapchain Present; no NRI types in zircon), DirectX-slot cases in all game-manager renderer switches, sessions skip render-graph init. VERIFIED 2026-07-25: full Debug build green; boot `--render_nri_dx12 --no_splash --kotek_frames=30` exit 0 (RTX 4060 Laptop, ID3D12Device8, NRI v180, shader model 609, 1920x1175 2-buffer vsync swap chain, clean shutdown), 189/189 kotek tests + default bgfx boot exit 0 unchanged. REMAINING (phase 2+): zircon passes split for NRI (Z5), NRI-Vulkan slot, ray tracing (the RTX hardware + NRI RT extension are ready), swap-chain resize hookup, user-supplied backend registration |
| K12 | Final commit+push via `git acp "msg"` | in-progress | alias now exists (verified); used for phase commits; kotek is a submodule (commit there first, then bump in zircon) |
| K13 | ImGui: analyze multi-context support; design MT-safe usage | done (2026-07-22) | ANALYSIS: Dear ImGui supports multiple ImGuiContexts, but the current-context pointer (GImGui) is a plain global, NOT thread-local — concurrent multi-context use across threads is unsafe by default. Only two safe models, both now supported: (1) single-UI-thread (default, unchanged); (2) context-per-thread + serialization. IMPLEMENTED: `ktkIImguiContextManager` (kotek.core.api) + `ktkImguiContextManager` (kotek.ui.imgui, owned by the wrapper, exposed via `ktkIImguiWrapper::Get_ContextManager`); per-thread `CreateContextForThread`/`BindThreadContext` (thread_local binding), `Lock`/`Unlock` (mutex + SetCurrentContext to the caller's context), RAII `ktkImguiLockGuard` in `kotek_ui_imgui_context_manager.h`, debug asserts on unbound/no-context use; editor imgui pass adopts its context as the default. Zircon editor/game sessions should map 1:1 to named contexts when MT UI is enabled |
| K14 | Video: dav1d as default backend behind `ktkIVideoPlayer*`; document that own codec impl is out of scope; design user-backend hook | design done (2026-07-25), impl pending | VERDICT (owner's question "is own codec even reasonable"): **NO** — a production AV1/HEVC decoder is years of spec-grade work (entropy coding, transforms, loop filters, conformance vectors); that is exactly the problem class the framework answers with deeply-validated OSS (the GLM/bgfx rule), so an own codec is out of scope BY DESIGN, not by lack of effort. dav1d (VideoLAN, the SOTA AV1 decoder) is the default decode backend and already a dependency. SHRINKABLE SHAPE (the pattern the owner asked to generalize to every module): the module is a thin orchestration shell over a NARROW backend interface, replaceable three ways — (a) compile-time switch `KOTEK_USE_VIDEO_DECODER_DAV1D` (guard skeleton landed in defines.static.cpp, default ON); (b) runtime registration of a custom decoder into a service slot (lands with the player impl — users plug HEVC/VP9/proprietary/hardware DXVA/NVDEC decoders without forking kotek); (c) whole-module replacement via K21 (`plugins/kotek.ui.videoplayer.dll` — the dispatcher already routes through `KOTEK_INVOKE_MODULE`, works today). INTERFACE SPLIT: `ktkIVideoPlayerManager` (exists in kotek_api.h — the player shell: open/close/play/pause/seek/render, grows with the impl) vs **`ktkIVideoDecoder`** (the narrow backend contract: Open(stream)/Decode(packet)→frame/Flush/Close — lands with the player, dav1d fills it first); container demux (mp4/mkv/webm) is a separate concern, phase 1 is raw AV1 (ivf/avif). NOTE: the `.avif` module name covers the AV1 family (AVIF image format + AV1 video in ivf) — keep the name, comment the scope. NEXT (K17-family): player shell + dav1d decoder backend + `ktkIVideoDecoder` in core.api |
| K15 | Decide whether kotek keeps render backend projects at all (vs. zircon-only); position kotek as standardization layer | open | see §10 |
| K16 | Produce & upload NuGet packages to owner's nuget.org account | blocked | needs API key from owner (use CI secret) |
| K17 | Implement the planned-but-missing backends | in-progress (2026-07-24) | DXM math backend implemented (first of the matrix): all DXM `#error todo` branches in `kotek.core.math` completed; storage = column-major contract kept (`m_base.m[column][row]`, so a loaded XMMATRIX is the transpose of the logical matrix — `XMMatrixMultiply`/`XMQuaternionMultiply` operand order swapped at the boundary, mat*vec via `XMVector4Transform(v, X)`, determinant/inverse transpose-invariant so direct); DXM deps come from the Windows SDK (`um/DirectXMath.h`, vcpkg port optional); `get_math_determinant`/`get_math_inverse` (2x2/3x3/4x4) + `get_math_normalize`/`get_math_slerp` (quaternion) added for both backends; fixed the GLM `quaternionf(x,y,z,w)` ctor forwarding to `glm::quat(w,x,y,z)` (component permutation bug — zircon's transform workaround via accessors is unaffected); parity test suite `kotek.core/tests/kotek_core_test_math_backends.cpp` (DXM vs raw-GLM reference, 1e-5) wired as `RegisterTests_MathBackends_ForModule_Core`. OWN no-dep math backend done (2026-07-24, `-DKOTEK_MATH_LIBRARY=KOTEK_OWN`): new `kotek.core.math/include/kotek_std_math_own.h` — POD backing types (`vec2/3/4` with x/y/z/w, `mat2x2/3x3/4x4` as column-vector arrays so `m[col][row]` is the same contiguous blob as glm/DXM, `quat` as x,y,z,w; `base_vec1_t = float` like DXM) with scalar implementations of every operation the GLM/DXM branches have (dot/cross/length/length_squared/normalize/distance, component +,-,·, scalar·, mat·mat, mat·vec, vec·mat, transpose/determinant/inverse (adjugate via cofactors), quat Hamilton product/inverse/normalize/slerp (GLM short-path), look_at_rh, perspective_rh_no (GLM [-1,1] depth), radians/degrees) — no intrinsics, no third-party includes, linear loops over contiguous fields. Config wired exactly like GLM/DXM (`KOTEK_MATH_LIBRARY_OWN` output flag + unconditional `KOTEK_USE_MATH_LIBRARY_OWN` in the generated preprocessors header; supported list = GLM, DXM, KOTEK_OWN). Every `#if GLM / #elif DXM` site gained `#elif defined(KOTEK_USE_MATH_LIBRARY_OWN)` and every dead `#else` became `#error unknown math library` across vector1-4f, matrix2x2/3x3/4x4f, quaternionf.h, math_functions_{vector,matrix,quaternion,numeric}.h; the backend-agnostic nf views needed no changes. Parity suite (16 tests, GLM reference 1e-5) runs unchanged under OWN (glm pulled PRIVATE for the test TU as with DXM): 185/185 kotek + 14/14 zircon PASSED, smoke exit 0; DXM and GLM builds stay green. Latent fix shared with DXM: `convert_to_radians/degrees` for double/long double had inverted converter constants (to_radians used 180/pi). `quaternionf::operator+=` GLM branch still empty (pre-existing, only OWN implements it). EIGEN still open. Quaternion surface extended (2026-09-04, zircon Z20's editor-camera quaternion driver): `get_math_angle_axis(angle_radians, axis)` + `get_math_rotate(quaternionf, vector3f)` in `kotek_std_math_functions_quaternion.h` and `get_math_asin(float)` in `kotek_std_math_functions_numeric.h` (scalar trig has no backend differentiation — shared CRT body, the wrapper exists for the wrappers-only rule); the own backend gained the matching scalar `angle_axis`/`rotate(quat, vec3)` in `kotek_std_math_own.h`. API identical across GLM/DXM/KOTEK_OWN **Own Win32 window backend (2026-07-31, phase 1)**: new `kotek.core.window.win32` module — `ktkWindowWin32 : ktkIWindow` over raw Win32 (WNDCLASS+CreateWindowEx, WndProc WM_CLOSE/DESTROY→close flag, borderless-popup fullscreen with placement restore, ClipCursor/ShowCursor input types, live GetClientRect dims, `ktkWin32OSData{hWnd,hInstance}` identical to the GLFW path so bgfx/NRI consume it unchanged; GL/GLES init paths assert-removed per K11, NO_API only) — zero third-party deps, selected with `-DKOTEK_WINDOW_LIBRARY=WIN32` (GLFW default). Design: exactly ONE backend module builds per config (the glfw headers in `kotek_os.h` are flag-gated, so the inactive backend cannot compile — and the WIN32 config needs no glfw anywhere, `imgui_impl_glfw.cpp` included); dispatcher routes via `KOTEK_INVOKE_MODULE` (K21-overrideable); backend umbrellas stay unconditional after the pragma-once trap was root-caused (an early transitive include before the flag-defining defines copy made the guarded includes permanently vanish); the imgui wrapper's 13 glfw-named methods map onto `ImGui_ImplWin32_*` (init/shutdown/frame real; the 8 glfw-shaped input callbacks are phase-1 no-ops) with `GLFWwindow/GLFWmonitor` forward-declared in the WIN32 config. VERIFIED: standalone `-DKOTEK_WINDOW_LIBRARY=WIN32` chain links `kotek.exe` with 0 errors (no GLFW); default GLFW path byte-identical green; **runtime boot on the own backend exit 0** — `ktkWindowWin32::ObtainInformationAboutDisplay` logged the display size, 30 frames presented through bgfx over the same `ktkWin32OSData` contract, 14/14 + 189/189 tests, clean shutdown; the 8 zircon-side GLFW-guarded sites got phase-1 branches (imgui init/shutdown through the wrapper mapping, docking viewports deferred to phase 2, game-manager callback registrations no-op'd with the phase-2 note). PHASE 2 (a-d landed 2026-07-31): **(a)** `ktkInputPlatformBackendArgs_WINAPI` gained the full event fields (key/scancode/action/mods; action reuses the glfw action constants press=1/release=0/repeat=2). **(b)** ONE `constexpr winapi_key_to_glfw()` translator in `kotek_input.cpp` (~80 lines: ASCII 0x20-0x7E passes through — glfw and VK are identical there; numpad 0x60-0x69 and F-keys 0x70-0x87 by range rule; ~45 specials by hand) feeds the three existing switch cases (Update dispatch, Update_Keyboard, Update_Mouse) — the cases translate then re-dispatch into the existing glfw-shaped logic, so there is zero logic duplication; win32 mouse buttons need no translation (same codes as glfw). **(c)** `ktkWindowWin32::Forward_EventToInput` — the WndProc feeds keyboard (WM_KEY*/WM_SYSKEY*, auto-repeat from lParam bit 30, live modifier bits from `GetAsyncKeyState`) and mouse (all buttons incl. X1/X2) into `m_p_main_manager->Get_Input()->Update_Controller`; no interface changes, no zircon coupling. **(d)** imgui: `Set_WndProcChain` on the CONCRETE `ktkWindowWin32` (the ktkIWindow interface stays frozen) — both zircon imgui passes install `ImGui_ImplWin32_WndProcHandler` at init (WIN32 config only), so the editor UI sees mouse/keyboard on this backend. **(e) wrapper interface generalized (2026-07-31)**: `ktkIImguiWrapper`'s 13 glfw-shaped methods are now backend-agnostic — `ImGui_InitForOpenGL/Vulkan/Other`, `ImGui_ShutdownPlatform`, `ImGui_NewFramePlatform`, and the 8 callbacks take `void*` native handles (consumers pass `GetWindowHandle()` unchanged); the wrapper dispatches per config (GLFW casts to dear imgui's real backend, WIN32 maps to `ImGui_ImplWin32_*` with phase-1 no-op callbacks); all 22 zircon call sites renamed, win32-branch casts simplified to plain `void*` passes. STILL OPEN: (f2) interactive input verification on the win32 backend (the gtest suite proves the translation+state machine; a live keypress-through-WndProc check is a manual step) |
| K18 | CRT consistency + linkage model (all-.lib / all-.dll / mixed per-module) | in-progress (2026-07-22) | DONE: /MT + `KOTEK_VCPKG_TRIPLET=x64-windows-static` (green); `cmake/library.cmake` with THREE scenarios — STATIC (green, validated), SHARED implicit (works for acyclic layers; kotek itself is cyclic=blocked), PLUGIN explicit (manifest + `ktkPluginInvoke*` + `KOTEK_INVOKE_MODULE_*`; configure+link pass). PLUGIN status: **green (2026-07-22, see K20)** — 27 plugin DLLs + `game.ktk` + `kotek.exe` link with 0 errors; runtime validation still pending. Supporting fixes made: vcpkg toolchain now included every configure; global `find_package(... GLOBAL)` hoist block; `kotek_finalize_plugin_links` BFS pass; `pkg_check_modules GLOBAL dav1d`; `format` links fmt on Windows (latent bug); explicit deps added (main_manager/os.win32/filesystem.path/console-see-K20) |
| K19 | C++17 compatibility for Windows XP targets | open | switch added 2026-07-22: `KOTEK_WINDOWS_XP=ON` (or `-DKOTEK_CPP_STANDARD=17`) in `compiler_globals.cmake` + `KOTEK_USE_CPP_STANDARD` def; needs `v141_xp` toolset. Audit not done: known C++20-only hotspots — `std::format` (kotek.core.format), concepts, consteval; codebase must compile under BOTH standards |
| K20 | Interface purity for PLUGIN/SHARED modes (worklist) | done (2026-07-22) | **PLUGIN build is GREEN: 0 errors** (was 191; 27 plugin DLLs + `game.ktk` + `kotek.exe` all link; STATIC build kept green too). What was done per hotspot: (1) **console**: `ktkIConsole` gained `Push_Command`/`Execute_Command(enum_base_t, console_command_args_t)` + `Flush` (signatures identical to `ktkConsole`; the `console_command_*` aliases moved from `kotek_console.h` to `kotek_api.h`); new `ktkMainManager` slot `Set_/Get_Console`; `kotek.core.console` creates+owns the instance at module init; zircon fetches it from the slot (static_cast only because `Register_Command` is a template, no more `new/delete`); `ktkIGameManager::GetConsole` now returns `ktkIConsole*` — all enum-arg calls became vtable dispatches (incl. vk swapchain's). (2) **render pass bases**: `kotek_render_graph_simplified{,_render_pass}.{h,cpp}` moved `kotek.render.{gl,bgfx}` → `kotek.render.shared.{gl,bgfx}` (static leaves; namespaces unchanged; umbrellas updated); gl's `ktkRenderShaderManager`/`ktkRenderGeometryManager`/`ktkRenderBuffer` also moved to `shared.gl` (zircon's gles3 passes call them directly); gl's `Get_ManagerShader/Geometry` inlined for the same reason; `ktkIRenderResourceManager` gained default-noop `Update()` (gl/bgfx override) so zircon renderers route through it; `angle.gles23` links shared.gl now (non-minimal config, untested). (3) **ImGui**: `ktkIImguiWrapper` extended additively (`ImGui_ImplVulkan_Shutdown`, `ImFontConfig_Create`, `FontAtlas_AddFontFromMemoryTTF/GetGlyphRangesCyrillic/GetTexDataAsRGBA32/SetTexID`); zircon's 4 imgui passes + vk's `kotek_render_imgui_manager` route every ImGui call through the wrapper (no raw `ImGui::` remains). (4) **gl/vk residuals**: gl declares real deps `kotek.render.shared`+`shared.gl` (ktkShaderModule/ktkBufferModule/ktkRenderStats); vk links `kotek.core.memory.gpu.vulkan` — demoted to static leaf (allocator backend, same rationale as memory.cpu). (5) **tests**: `RegisterAllTests` body + kotek.core's `tests/` sources + zircon's unit-test sources & registrar calls guarded with `#if !defined(KOTEK_USE_LINKAGE_PLUGIN)` (tests instantiate concrete classes across modules = static-mode-only feature). (6) **serialize orchestration**: new `KOTEK_INVOKE_MODULE_SERIALIZE/DESERIALIZE[_NS]` macros + `ktkPluginInvokeSerialize/Deserialize` (verb-derive the init symbol, manifest lookup, GetProcAddress); manifest emits `KOTEK_ENTRY_` flags for serialize/deserialize symbols; all ~16 orchestrator call sites converted (os/window/window_manager/memory/memory.gpu/profilers/filesystem/core/ui/ui.videoplayer/kotek.game); `kotek.core.filesystem` declares its real dep `kotek.core.containers.filesystem`. (7) **window glue**: `ktkIWindowConsole` added to the API; `ktkWindowConsole` implements it, `kotek.core.window` creates+owns it (new `Set_/Get_WindowConsole` slot), zircon uses the slot; `ktkIWindow` gained `HideWindow`+`RegisterUserMainManager` (ktkWindow overrides); `ktkWindowSplash` moved `kotek.core.window` → `kotek.game` (the bootstrapper needs it before any plugin loads). (8) **`__` export bug**: CMake's `create_def` truncated the MSVC PCH sentinel `__@@_PchSym_@00@...` to `__` in exports.def; any DLL linking 2+ PCH-bearing static libs got an ambiguous match (LNK4022/LNK2001) — fixed in `library.cmake`: PLUGIN-mode plugin DLLs now export ONLY their module contract (`Initialize/Shutdown[/Serialize/Deserialize]Module_*`) via a cmake-generated minimal .def instead of `WINDOWS_EXPORT_ALL_SYMBOLS` (also kills junk data-global exports). (9) `KOTEK_USE_LINKAGE_*` define now applied at zircon root scope too (was kotek-subdirectory-only, zircon's `KOTEK_INVOKE_MODULE_*` macros evaluated the wrong branch). Leftovers: SHARED mode still needs acyclicity work (K18 §8); `angle.gles23` non-minimal config untested; `kotek.core.os.linux` still in the plugin manifest on Windows (pre-existing) |
| K21 | Plugin override system: user dlls replace built-in module entries in EVERY linkage mode | done (2026-07-23) | override-first `KOTEK_INVOKE_MODULE` via tri-state `ktkPluginTryOverride` (kotek.core.main_manager, compiled in all modes); `kotek_plugin_registry.h` (module-name↔entry-symbols) now generated in EVERY linkage mode by `kotek_generate_plugin_manifest()` (+ Serialize/Deserialize detection hoisted in `kotek_add_library`); `plugins/` folder next to the data dirs; variant A name convention `plugins/<module>.dll`, variant B `plugins/plugins.json` (json wins); flags `--kotek_plugins_template` / `--kotek_plugins_modules` (write file, print, exit 0 — CRT leak dump disabled first, works in all modes); gtest suite `kotek.core/tests/kotek_core_test_plugin_override.cpp` (6/6 PASSED) + test-double dll `kotek.core.tests.plugin`; smoke `kotek.exe --no_splash --kotek_frames=30` exit 0 (14/14 + 169/169) — see §5a "Plugin overrides" |

| K22 | Unit tests for every class and public function (both repos, zircon Z14) | open | owner directive 2026-07-23: functional proofs, not per-method formalities — behavior + edge cases + stress where the contract promises it (the 100k-command history stress is the reference); cover as much as possible. Rule in §2: tests are living code, kept actualized in the same commit as the behavior change, outdated ones refactored or deleted |
| K23 | CLI flags standardization (research + implement) | open | research 2026-07-23 across Unity/Unreal/Godot/Source/CryEngine — recurring categories: display size + fullscreen/windowed + renderer-select (5/5 engines), log control (5/5), headless/no-graphics (4/5), fps cap/benchmark (4/5), paths (4/5), vsync + splash + editor-vs-game + boot-exec + no-audio + gpu-validation (3/5). kotek has: `--editor`, `--editor_imgui`, `--no_splash`, `--kotek_frames=N`, `--width`, `--height`, `--render_*` (legacy gl/vk names dead — retarget to `--render_bgfx` / `--render_nri_*` when NRI lands), plus the new plugin flags. PROPOSED additions (naming: `--snake_case`, `--name=value`, `--kotek_*` prefix for engine-meta): P1 automation — `--headless`, `--log_file=<path>`, `--fullscreen`/`--windowed`, `--vsync`/`--novsync`, `--exec="<console cmd>"` (repeatable; runs registered console commands at boot — drives editor/game integration tests from CLI), `--kotek_help` (prints all flags, exit 0; runtime counterpart of K6); P2 determinism — `--seed=<u64>`, `--time_scale=<f>`, `--userdir=<path>` (parallel test runs); P3 debug — `--gpu_validation`, `--noaudio`, `--safe_mode`, `--version`. Convention to steal from Godot: everything after `--` passes through to the game layer unparsed |
| K24 | Purge static storage duration from kotek (+ zircon Z18) | open | owner directive 2026-08-02, rule §6: NO file-scope globals, function-local `static`, or static class members (etl `static_*` TYPES unaffected — they name capacity, not storage duration). This rule is the formalization of the stack's worst recurring defect classes (etl intrusive-list terminator AV, cross-CRT frees, init-order hazards, never-unload lock states, the 2026-08-01 double-run suite collision). Replacement patterns in preference order: owning-class members → manager/context-owned instances → registered services behind ktkI* interfaces. INVENTORY first (grep audit + classification per site), then replace by hazard class — known targets: `_pLoggerMain`/`_pLoggerMsvcOutput` module globals (main_core_log_dll.cpp, the log-backend pair), test-file globals (`g_builtin_init_called` family in the plugin tests), any `static` locals. First compliance edit DONE (2026-08-02): the plugin-override test's `s_invocation` static replaced with pid+timestamp path uniqueness (no static state). OWNER DECISIONS (2026-08-02): vendored third-party inside kotek/src (imgui/pico/vma/stb, ~1,400 statics) EXEMPT; namespace-scope inline-constexpr POD EXEMPT. INVENTORY DONE (2026-08-02, agent-35 audit — the zircon Z18 row carries the same content): kotek's surface = 12 mutable globals/9 sites + 12 function-local statics/8 sites + 3 thread_local; zero mutable static class members. Top hazards: the `_pLoggerMain`/`_pLoggerMsvcOutput` pairs (both backend branches), the plugin override/invoke never-unload registries (~132 KB), the `kotek_std_memory.cpp` tracker cluster (replaced global new/delete runs it per allocation), `kotek_own_json.h` Meyers set (per-module default_resource — documented intentional), `saved_placement` (latent multi-window bug), imgui TLS pair (hot-reload hazard when NRI phase 3 unloads). Batch 1 DONE (2026-08-02, ae5b140). OWNER FORK DECISIONS (2026-08-02): logger globals → macro-context refactor (batch 2b, its own task); own-json default_resource EXEMPT (documented per-TU design) + mutable `fallback_*` scratch converted (batch 2a); `kotek_std_memory.cpp` tracker cluster → deferred to K9. Batch 2a sites: plugin override/invoke registries → ktkMainManager-owned state struct (macros carry the manager already); zircon command_registry Meyers → history member; imgui TLS → manager-keyed member map; own-json mutables |

| K25 | Filesystem overhaul: B0 foundation repair → B1 VFM-mapped reads → B2 packed archives (.kpack) → B3 streaming/async → B4 embedded fault-tolerant defaults | in-progress (B1 done 2026-09-05) | owner-approved plan 2026-09-04 (session plans dir). **B0 DONE (2026-09-04)**: (1) missing file on ANY native read/write/open path = false / kInvalidFileHandleType + one `KOTEK_MESSAGE_WARNING` with the path — the fopen/exists asserts are gone (user data is not a programmer error); (2) `Get_FileSize(path)` implemented at both levels (native fopen/ftell graceful, full dispatcher boilerplate); (3) interface-dead `ustring` Read/Write_File overloads deleted from `ktkIFileSystem`+`ktkFileSystem` (zero callers in both repos); `Write_File(path, const uint8_t*, size)` is real — forwards to the char* dispatch, native write mode flipped `"w"`→`"wb"` so byte payloads write without CRLF translation (json writers escape raw newlines, nothing observes it — proven by the 0x0A roundtrip test); (4) all 39 `std::exit(-1)` in the dispatch boilerplate → KOTEK_ASSERT + return false/invalid-handle; the 8 "all file systems failed" trailing asserts dropped (the warning after them already degrades); the zlib-shell "todo: implement" asserts on the same paths → graceful skip warnings; (5) the shared-scratch return path deleted (`m_reserved_cache[2048]`) — buffer-too-small = false + the REQUIRED size in the size out-param, the pointer is never redirected (the `ktkIFileSystem::Read_File` contract comment rewritten); (6) the DYN-branch `ktk_array` copy-paste in `kotek_std_alias_filesystem_path.h` fixed to `ktk_filesystem_path`; (7) ~640 commented legacy lines deleted (5 blocks in kotek_filesystem.cpp, the file_text Load/Save block, the "todo: legacy delete" header constants); declared-but-never-defined `ktkFileSystem_Native::Initialize` removed (B1 revives the concept); dead `VFM_FILE_MAX_COUNT` removed; (8) `KOTEK_DEF_FILESYSTEM_STORAGE_MAX_FILES_COUNT` is one value 512 (was 2048/32 on KOTEK_SDK_IMGUI; measured boot handles are single digits, 512 covers B1-B3 headroom). BUGS FOUND+FIXED en route: the dispatch `Open_File` discarded the native handle (returned kInvalidFileHandleType ALWAYS) and its empty-path early return returned 0-as-handle; native `Close_File` never returned the handle to the pool (slot leak); the `repeat_fs` capacity check was INVERTED (`capacity <= list_size`, fired on any explicit-priority call with the priority-list feature — never exercised before) → now `list_size <= capacity`. BUG DOCUMENTED, NOT FIXED (B2 scope, changes runtime behavior): `ktkFrameworkConfig::Set_FS_PriorityList` counts entries `!= kAuto && != kEndOfEnum`, and `kZlib == kEndOfEnum` (=2) — the sentinel collision silently drops the kZlib entry, so the stored priority list for `["Native","ZLIB"]` is `[Native]` (list_size 1); the zlib branches therefore never execute today — fixing it (drop the kEndOfEnum exclusion) activates the zlib-fallback warnings and belongs with B2's real priority-list work. ALSO DOCUMENTED (plan §Risks, not redesigned in B0): the repeat_fs fallback loop is provably unreachable as written (`was_overloaded_fs_order` is mutually exclusive with the loop's guard) — kept for B2; the handle-as-pointer-into-pool ABI; `Read_File(path, char*&)` stays an assert-stub (interface-kept, zero callers); `ktkFileSystem_Zlib::Initialize` declared-never-defined (B2 shell). Tests: 5 new `Filesystem.test_b0_*` suites in kotek_core_test_filesystem.cpp (missing-file graceful read in both dispatch shapes + missing open, Get_FileSize present/absent in both shapes, uint8 write→read byte-exact roundtrip incl. 0x0A, handle Open/GetFileSize/Tell/Seek/Write/Close roundtrip, buffer-too-small false+required-size then retry-with-reported-size) — fixtures under data_user/tests, self-cleaning. VERIFIED: build+gfxdev Debug RC 0 (0 errors, no new compile warnings), boot `--no_splash --editor_imgui --kotek_frames=30` exit 0, zircon 61/61 + kotek 232/232 (227+5), 4 debug_heap(996) residuals (≤6 tolerated), zero new boot-flow warnings (the missing-file warnings fire only from the tests that prove them). Zircon side (Z8): `gltf_read_file` migrated from the Is_Exists+alias-layer file_size TOCTOU pair to the interface `Get_FileSize(path)`; the three shader-blob readers' stale "native read path asserts" comments updated (the Is_Exists guards stay — they suppress the warning); scene_metadata's guard comment didn't cite the assert (untouched). **B1 DONE (2026-09-05)** — VFM-mapped reads are REAL behind the existing `VFM_READ` runtime flag, in the STREAMING-FIRST posture (owner directive 2026-09-05, zircon rule 9: NO user-space mapping cache — the OS page cache already is the file-content cache): the native single-shot read with the flag on maps the file via the NEW `ktkFileSystem_VFM::MapFileForRead` (classifies `eVFMMapFileResult::{kSuccess,kEmptyFile,kMissingFile,kMappingFailed}`), copies out of the mapping in `KOTEK_DEF_FILESYSTEM_VFM_STREAM_CHUNK_SIZE` chunks (64 KB, NEW named define — the consumer never holds more than one chunk over its own buffer), and unmaps immediately (map->copy->unmap, nothing persists; repeated access rides the OS page cache or B3's streaming). Contracts on the mapped path, all pinned by tests: byte-identical to the CRT path INCLUDING the room-permitting terminator at `[size]`; the B0 too-small-buffer contract (false + REQUIRED size, pointer never redirected); missing file = false + size 0 + ONE warning with the CRT fallback deliberately NOT engaged (no double noise); a mapping failure on an existing file warns (VFM-side, with GetLastError) + degrades to the CRT read — never a hard error on user data; a 0-byte file is an explicit successful empty read detected by size query BEFORE any map attempt (CreateFileMapping rejects size 0 on Win32). `VFM_CACHE` is RETIRED: the enum value stays so old configs parse, setting it warns once per filesystem instance (points at the OS page cache + streaming) and is otherwise inert; the shipped sys_info.json drops it (`FS_Features:["VFM_READ","PRIORITY_LIST"]`); the 379-hits-per-boot "vfm cache is not implemented" warning is dead. VFM-layer fixes en route (zero callers before B1, never exercised): `MapFile` returned `size()-1` instead of a reused free slot's id and read the free-id queue `.back()`/`.pop()` (front/back mismatch); `UnMapFile` ERASED its slot (positions of other live ids shifted under any holder of an id) — now marks free + returns the id to the pool, positions stable; `MapViewOfFile` failure leaked the mapping handle (now closed); the per-mapping debug byte-preview at Shutdown and the per-unmap debug line became one summary message with the counters. Wiring: `ktkFileSystem::Initialize` calls `m_vfm.Initialize()` + `m_fs_native.Initialize(&m_vfm)` (the B1-revived native Initialize, VFM-guarded). Diagnostics (house pattern, test-pinned): `Get_StatMapCount()/Get_StatUnmapCount()` on the VFM + `ktkFileSystem::Get_VFM()` concrete-class seam (deliberately NOT on ktkIFileSystem); outstanding = maps − unmaps, every read balances, Shutdown must see zero. THREADING: NOT thread-safe by design this phase (the filesystem is single-threaded today; the zircon resource worker's real IO is B3's scope — documented on the class). The `file_handle_vfm_t` variant stays unconstructed (the single-shot path needs no handles; B3 decides). Tests: 5 NEW `Filesystem.test_b1_*` suites in kotek_core_test_filesystem.cpp (fixtures in data_user/tests, self-cleaning; flags driven through the test's own `ktkFrameworkConfig::Set_FS_FeaturesFlag` AFTER Initialize because Initialize parses the shipped sys_info.json into the config): vfm==native byte parity on 4 KB binary incl 0x00/0xFF across CRT/mapped/retired-flag shapes + the too-small contract on the mapped path; a 200,011-byte file (3 full 64 KB chunks + a 3,403-byte tail) byte-identical through the chunked copy with map/unmap balance pins; missing file graceful in both flag shapes with counters proving nothing mapped; 0-byte file success + terminator parity + no map; shutdown balance (maps==unmaps at rest and after Shutdown). VERIFIED: build+gfxdev Debug RC 0, boot `--no_splash --editor_imgui --kotek_frames=30` exit 0 with zero "vfm cache is not implemented" lines and zero new warnings, a flags-off boot exercises the CRT path (exit 0), zircon + kotek suites green, debug_heap(996) residuals within the tolerated ≤6 |

| K26 | Exe-side input feeding: window callbacks feed `ktkInput` from the LIVE GLFW copy | done (2026-09-05) | THE DISEASE (the static-GLFW-per-module class, zircon §5): GLFW is a static lib, every module owns a private copy of its global state; the window lives in kotek.exe's INITIALIZED copy, so `glfwSet*Callback` issued from game.ktk (`zircon_game_manager::initialize_input`) wrote into that module's never-initialized copy (`_GLFW_REQUIRE_INIT` early-returns) and the callbacks never fired — `ktkInput` was starved in EVERY boot, and the editor gate skipped even the dead installation under `--editor*`. The same class as the imgui two-copies defect (2026-09-02/03) and the opposite of the reverted "event-chain bridge" (e274e42 — never hand game.ktk's raw callback addresses to anything; here NOTHING crosses module boundaries: the callbacks live exe-side and feed the exe-side input manager). THE FIX: (1) `ktkWindow` (kotek.core.window.glfw) receives the main manager at construction from the module entry, and `Initialize` installs `window_callback_key` / `window_callback_mouse_button` / `window_callback_cursor_pos` on the live copy + `glfwSetWindowUserPointer` as the event-time channel — unconditional (no editor gate), both session types fed; (2) key/mouse-button forward as `Update_Controller` with `ktkInputPlatformBackendArgs_GLFW3` (the raw GLFW key/action/scancode/mods, key<0 dropped — the translation tables are indexed by the raw key); cursor-pos does the prev/current `Set_ControllerData` dance + normalized pair (0x0 minimized window skipped without assert) + `Set_ControllerUpdate` so `Update()` publishes `kMouseDeltaX/Y`; scroll NOT forwarded (`eInputControllerMouseData` has no scroll fields); (3) the feed guard is the NEW additive virtual `ktkIInput::Get_PlatformBackend()` (default `kPlatformBackend_Unknown`, `ktkInput` returns its real backend) — the callback only feeds when the manager was initialized for GLFW3, otherwise `Update_Controller`'s backend-mismatch assert would fire on early events (zircon's `initialize_input` runs after the window exists); (4) imgui chaining untouched: the imgui backend installs later via `ImGui_InitForOther(handle, true)` and chains INTO these as PrevUserCallback*. Module edge: kotek.core.window.glfw now links kotek.core.input (the args struct), acyclic. Zircon side: the entire dead GLFW-callback block deleted (10 free functions — none referenced outside the installation; `WindowCallback_Resize` pushed `kConsoleCommand_Render_Resize` but never fired, the console registration of the handler stays), the editor gate and the `RegisterUserMainManager` call gone (the interface method stays for users). Tests: `Input.WindowCallbackFeedingContract_GLFW3` pins the exact callback feeding sequence headlessly (key press → Is_KeyPressed, mouse button, two cursor moves with prev-tracking + deltas, delta zeroing on an eventless frame, the GLFW3/Unknown backend guard). The interactive proof (real RMB-look/WASD) is the owner's manual check |

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
