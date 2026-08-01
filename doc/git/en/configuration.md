# kotek — configuration reference

Everything user-facing that configures kotek: CMake options at build time and
command-line arguments at runtime. This table is maintained alongside the code —
the machine-readable registry is `cmake/options_help.cmake`
(`cmake -DKOTEK_HELP=ON` prints it); if a row here disagrees with the registry,
the registry is right and this file has a bug (report or fix it).

## CMake options

| Option | Default | Meaning |
|---|---|---|
| `KOTEK_LIBRARY_TYPE` | `EMB` | Container model the `ktk_*` aliases resolve to: `EMB` = static etl (no reallocation), `DYN` = regular std/boost, `HYB` = pmr inline-buffer (bounded, grows only when allowed) |
| `KOTEK_STD_LIBRARY_STATIC_CONTAINERS` | `ON` | etl-based static containers available |
| `KOTEK_STD_LIBRARY_HYBRID_CONTAINERS` | `ON` | hybrid (pmr inline-buffer) containers available |
| `KOTEK_STD_LIBRARY_DYNAMIC_CONTAINERS` | `ON` | regular std/boost containers available. `OFF`+`EMB` = strict embedded configuration (only static containers exist in code) |
| `KOTEK_CONFIGURATION_TYPE` | `minimal` | dependency preset name → `cmake/windows/vcpkg_nuget_<name>.cmake` package list |
| `KOTEK_DEPS_FOLDER` | *(empty)* | dependency source: empty = nuget+vcpkg presets, `vcpkg` = vcpkg only, `<folder>` = manual deps folder (convention layout + optional `deps.json`) |
| `KOTEK_VCPKG_TRIPLET` | `x64-windows-static` | vcpkg triplet. MUST match the CRT (`/MT` → `x64-windows-static`, `/MD` → `x64-windows`) or LNK2038 |
| `KOTEK_DEVELOPMENT_TYPE` | `SHARED` | user game module output: `SHARED` = `game.ktk` dll, `STATIC` = linked into the exe (then the three `KOTEK_*GAME*` variables below are required from the layer root) |
| `KOTEK_GAME_OUTPUT_LIBRARY_NAME` | `game.ktk` | file name of the produced user game module |
| `KOTEK_LINKAGE` | `STATIC` | module linkage: `STATIC` = all modules .lib, `SHARED` = all .dll implicit (needs an acyclic graph), `PLUGIN` = explicit LoadLibrary via the generated manifest + `KOTEK_INVOKE_MODULE` |
| `KOTEK_LINKAGE_FORCE_STATIC` | *(empty)* | semicolon list of module targets forced STATIC inside a SHARED/PLUGIN scenario (cyclic clusters) |
| `KOTEK_LINKAGE_FORCE_SHARED` | *(empty)* | semicolon list of module targets forced SHARED inside a STATIC scenario |
| `KOTEK_GAME_MODULE_FUNCTIONS_FILE` | layer root sets | STATIC dev type only: quoted header declaring the game-module entry points (zircon: `"zircon_game.h"`) |
| `KOTEK_USER_GAME_PROJECT_NAME` | layer root sets | STATIC dev type only: include dir of the game-module entry header, relative to the layer root (zircon: `src/engine`) |
| `KOTEK_USER_GAME_MODULE_FOR_LINK_NAME` | layer root sets | STATIC dev type only: CMake target of the game module for kotek.game to link (zircon: `zircon`) |
| `KOTEK_MATH_LIBRARY` | `GLM` | math backend: `GLM` / `DXM` (DirectXMath) / `KOTEK_OWN` (own no-deps scalar) |
| `KOTEK_JSON_LIBRARY` | `BOOST` | JSON backend: `BOOST` (Boost.JSON) / `KOTEK_OWN` (own no-deps streaming SAX reader/writer + small DOM) |
| `KOTEK_WINDOW_LIBRARY` | `GLFW` | windowing backend: `GLFW` / `WIN32` (own no-deps Win32 backend) |
| `KOTEK_LOG_LIBRARY` | `SPDLOG` | logging backend: `SPDLOG` / `BOOST` / `CUSTOM` (own no-deps logger: OS-handle file sink, console, debug output window) |
| `KOTEK_ECS_BACKEND` | `PICO` | ECS backend: `PICO` (pico_ecs) / `ENTT` (disabled `#error todo` branches today) |
| `KOTEK_NRI` | `ON` | NRI render backend (D3D12, phase 1): clones the pinned NRI into `external/nri`, builds `kotek.render.nri`, enables the DirectX-slot dispatch. `OFF` skips all three |
| `KOTEK_STARTUP_RENDERER` | `OpenGLES_SpecifiedByUser` | startup renderer enum name (routes to bgfx by default; the DirectX slot goes to NRI) |
| `KOTEK_STARTUP_RENDERER_VERSION` | `OpenGLES_3_1` | startup renderer version enum name |
| `KOTEK_STARTUP_RENDERER_VENDOR` | `BGFX` | startup renderer vendor enum name |
| `KOTEK_TESTS` | `OFF` | build test targets |
| `KOTEK_TESTS_RUNTIME` | `OFF` | run gtest suites at engine boot (Debug) |
| `KOTEK_ASSERT_STDERR_ROUTING` | `OFF` | `ON` = CRT asserts/errors print to stderr + fail-fast (CI/agents); `OFF` = stock modal dialog (what end users expect) |
| `KOTEK_WINDOWS_XP` | `OFF` | target Windows XP (forces C++17; use with `-T v141_xp`) |
| `KOTEK_CPP_STANDARD` | `20` (`17` for XP) | C++ standard for the whole tree, exposed to code as `KOTEK_USE_CPP_STANDARD` |
| `KOTEK_CPU_PROFILER` | `OFF` Debug / `ON` Release | Tracy CPU profiler (built with delayed init + manual lifetime) |
| `KOTEK_GPU_PROFILER` | `OFF` Debug / `ON` Release | GPU profiler |
| `KOTEK_MEMORY_ALLOCATOR_CPU` | `MIMALLOC` | CPU allocator backend (forced OFF when leak detection is ON — the tracker needs plain CRT malloc) |
| `KOTEK_MEMORY_LEAK_DETECTION` | `OFF` | CRT leak detection regime (disables the custom allocator) |
| `KOTEK_USE_MEMORY_TRACKER` | `OFF` | opt-in allocation leak tracker |
| `KOTEK_CPP_ASAN` | `OFF` | address sanitizer build flags |
| `KOTEK_HELP` | `OFF` | print the option registry and stop |

Capacity knobs: every `KOTEK_DEF_*` element count / buffer size lives in
`kotek/src/kotek.core.defines.static.cpp/CMakeLists.txt` and becomes a `-D` with
the same name.

## Runtime arguments (kotek.exe)

### General

| Argument | Meaning |
|---|---|
| `--kotek_help` | print the supported command-line arguments and exit |
| `--kotek_frames=N` | run exactly N frames and exit (deterministic boot smoke; CI uses `--no_splash --kotek_frames=30`) |
| `--no_splash` | skip the splash screen |
| `--log_file=<name-or-path>` | route the log to a specific file (bare name lands in `data_user/`, a path is used as given) |
| `--exec=<file>` | execute a console-command file at startup |
| `--headless` | run without creating windows |
| `--fullscreen` / `--windowed` | window mode |
| `--vsync` / `--novsync` | vertical sync on/off |
| `--width=<px>` / `--height=<px>` | window size |

### Plugin system

| Argument | Meaning |
|---|---|
| `--kotek_plugins_template` | generate `plugins/plugins.json` as a template to fill in (module name → your DLL file) |
| `--kotek_plugins_modules` | generate the JSON listing the module names this build was compiled with (the names the registry matches against) |

### Editor (consumed by the game module — zircon)

| Argument | Meaning |
|---|---|
| `--editor_imgui` | run the ImGui-based editor session |
| `--editor` | run the wxWidgets SDK path (only in `KOTEK_USE_SDK` builds) |

### Renderer selection

| Argument | Meaning |
|---|---|
| `--render_nri_dx12` | the NRI backend on DirectX 12 (requires `KOTEK_NRI=ON` at configure time) |
| `--render_dx_7 … --render_dx_12`, `--render_dx_latest` | DirectX slot selection; the DirectX slot dispatches to the NRI backend in the current build |
| `--render_gl3_3`, `--render_gl4_6`, `--render_gl_latest`, `--render_gles*` | GL-era names retained for compatibility — they route to the bgfx backend (there is no standalone GL backend) |
| `--render_vk1_0 … --render_vk1_3`, `--render_vk_latest` | reserved; no standalone Vulkan backend in the current build |
