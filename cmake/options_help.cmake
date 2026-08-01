# K6: `cmake -DKOTEK_HELP=ON` prints every kotek option with its meaning and
# stops before any heavy work. The registry below is the curated, living list
# of user-facing options — when you add an option anywhere in kotek's CMake,
# add it here in the same commit (AGENTS.md rule: docs die when they drift).
#
# Format per entry: name|default|description (pipe is the field separator).

set(KOTEK_OPTIONS_REGISTRY
	"KOTEK_LIBRARY_TYPE|EMB|container implementation the ktk_* aliases resolve to: EMB=static etl (no reallocation), DYN=regular std/boost, HYB=pmr inline-buffer (broken today)"
	"KOTEK_STD_LIBRARY_STATIC_CONTAINERS|ON|etl-based static containers available"
	"KOTEK_STD_LIBRARY_HYBRID_CONTAINERS|ON|hybrid (pmr inline-buffer) containers available (HYB library type is broken today)"
	"KOTEK_STD_LIBRARY_DYNAMIC_CONTAINERS|ON|regular std/boost containers available. OFF+EMB = strict embedded configuration (only static containers exist in code)"
	"KOTEK_CONFIGURATION_TYPE|minimal|dependency preset name -> cmake/windows/vcpkg_nuget_<name>.cmake package list"
	"KOTEK_DEPS_FOLDER|(empty)|dependency source: empty=nuget+vcpkg presets, vcpkg=vcpkg only, <folder>=manual deps folder (K10)"
	"KOTEK_VCPKG_TRIPLET|x64-windows-static|vcpkg triplet. MUST match the CRT (/MT -> x64-windows-static, /MD -> x64-windows) or LNK2038"
	"KOTEK_DEVELOPMENT_TYPE|SHARED|user game module output: SHARED=game.ktk dll, STATIC=linked into the exe (then KOTEK_GAME_MODULE_FUNCTIONS_FILE, KOTEK_USER_GAME_PROJECT_NAME, KOTEK_USER_GAME_MODULE_FOR_LINK_NAME are required from the layer root)"
	"KOTEK_GAME_OUTPUT_LIBRARY_NAME|game.ktk|file name of the produced user game module"
	"KOTEK_LINKAGE|STATIC|module linkage scenario: STATIC=all modules .lib, SHARED=all modules .dll implicit (needs acyclic graph), PLUGIN=explicit LoadLibrary via manifest + KOTEK_INVOKE_MODULE"
	"KOTEK_LINKAGE_FORCE_STATIC|(empty)|semicolon list of module targets forced STATIC inside a SHARED/PLUGIN scenario (cyclic clusters)"
	"KOTEK_LINKAGE_FORCE_SHARED|(empty)|semicolon list of module targets forced SHARED inside a STATIC scenario"
	"KOTEK_GAME_MODULE_FUNCTIONS_FILE|(layer root sets it)|STATIC dev type only: quoted header name declaring the user game-module entry points (zircon: \"zircon_game.h\")"
	"KOTEK_USER_GAME_PROJECT_NAME|(layer root sets it)|STATIC dev type only: include dir of the user game-module entry header, relative to the layer root (zircon: src/engine)"
	"KOTEK_USER_GAME_MODULE_FOR_LINK_NAME|(layer root sets it)|STATIC dev type only: CMake target of the user game module for kotek.game to link (zircon: zircon)"
	"KOTEK_MATH_LIBRARY|GLM|math backend: GLM (vcpkg) / DXM (DirectXMath, Windows SDK) / KOTEK_OWN (kotek's own no-deps scalar impl)"
	"KOTEK_JSON_LIBRARY|BOOST|json backend: BOOST (boost.json, default) / KOTEK_OWN (kotek's own no-deps backend: streaming SAX reader/writer + small DOM, task K4)"
	"KOTEK_WINDOW_LIBRARY|GLFW|windowing backend"
	"KOTEK_ECS_BACKEND|PICO|ECS backend: PICO (pico_ecs, default) / ENTT (branches exist behind KOTEK_USE_ECS_BACKEND_ENTT but are disabled with #error todo)"
	"KOTEK_NRI|ON|NRI render backend (D3D12 phase 1): clones the pinned NRI into external/nri, builds kotek.render.nri, enables the DirectX-slot dispatch. OFF skips all three and suppresses KOTEK_USE_RENDER_NRI (select at runtime with --render_nri_dx12)"
	"KOTEK_STARTUP_RENDERER|OpenGLES_SpecifiedByUser|startup renderer enum name (routes to bgfx by default. The DirectX slot goes to NRI phase 1)"
	"KOTEK_STARTUP_RENDERER_VERSION|OpenGLES_3_1|startup renderer version enum name"
	"KOTEK_STARTUP_RENDERER_VENDOR|BGFX|startup renderer vendor enum name"
	"KOTEK_TESTS|OFF|build test targets"
	"KOTEK_TESTS_RUNTIME|OFF|run gtest suites at engine boot (Debug)"
	"KOTEK_ASSERT_STDERR_ROUTING|OFF|ON = CRT asserts/errors print to stderr + fail-fast (CI/agents), OFF = stock modal dialog (default, what end users expect)"
	"KOTEK_WINDOWS_XP|OFF|target Windows XP (forces C++17, use with -T v141_xp)"
	"KOTEK_CPP_STANDARD|20 (17 for XP)|C++ standard for the whole tree, exposed to code as KOTEK_USE_CPP_STANDARD"
	"KOTEK_CPU_PROFILER|OFF Debug / ON Release|tracy cpu profiler (lib is built with TRACY_DELAYED_INIT+TRACY_MANUAL_LIFETIME via the pinned port patch)"
	"KOTEK_GPU_PROFILER|OFF Debug / ON Release|gpu profiler"
	"KOTEK_MEMORY_ALLOCATOR_CPU|MIMALLOC|cpu allocator backend (MIMALLOC default. Forced OFF when KOTEK_MEMORY_LEAK_DETECTION=ON — the tracker needs plain CRT malloc, K9 rework pending)"
	"KOTEK_MEMORY_LEAK_DETECTION|OFF|CRT leak detection regime (disables the custom allocator)"
	"KOTEK_USE_MEMORY_TRACKER|OFF|opt-in allocation leak tracker (K9 rework pending)"
	"KOTEK_CPP_ASAN|OFF|address sanitizer build flags (the genex check is broken, see known issues)"
	"KOTEK_HELP|OFF|print this option registry and stop (this flag)"
)

function(kotek_print_options_help)
	message(STATUS "==================== kotek options (K6) ====================")
	foreach(_entry IN LISTS KOTEK_OPTIONS_REGISTRY)
		string(REPLACE "|" ";" _parts "${_entry}")
		list(GET _parts 0 _name)
		list(GET _parts 1 _default)
		list(GET _parts 2 _desc)
		message(STATUS "${_name} = [${_default}]\n    ${_desc}")
	endforeach()
	message(STATUS "capacity knobs: all KOTEK_DEF_* element counts/buffer sizes live in kotek/src/kotek.core.defines.static.cpp/CMakeLists.txt (each becomes a -D with the same name)")
	message(STATUS "=============================================================")
endfunction()
