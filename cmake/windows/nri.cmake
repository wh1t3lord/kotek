# NRI dependency (task K11): pinned shallow clone at configure time, same
# pattern as the vcpkg clone in vcpkg_nuget_minimal.cmake. NRI is not in
# vcpkg at our pin, and the owner's nuget feed has no NRI package yet —
# until it does, we clone + add_subdirectory (NRI's own CMake produces the
# static `NRI` target and fetches its own deps via FetchContent; phase 1 is
# D3D12-only so no Vulkan SDK and no nvapi/amdags are required).

set(KOTEK_NRI_PINNED_TAG "v180")
get_filename_component(KOTEK_NRI_ROOT "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
set(KOTEK_NRI_DIR "${KOTEK_NRI_ROOT}/external/nri")

if (NOT EXISTS "${KOTEK_NRI_DIR}/CMakeLists.txt")
	message(STATUS "[kotek]: cloning NRI ${KOTEK_NRI_PINNED_TAG} into ${KOTEK_NRI_DIR} (one-time)...")
	execute_process(
		COMMAND "git" clone --depth 1 --branch ${KOTEK_NRI_PINNED_TAG}
			https://github.com/NVIDIAGameWorks/NRI.git "${KOTEK_NRI_DIR}"
		RESULT_VARIABLE _kotek_nri_clone_result
	)
	if (NOT _kotek_nri_clone_result EQUAL 0)
		message(FATAL_ERROR "[kotek]: failed to clone NRI (${_kotek_nri_clone_result}) — check network/git")
	endif()
endif()

# NRI v180 vs Windows SDK >= 10.0.26100 (D3D12_SDK_VERSION 616): NRI guards
# its fallback D3D12_RAYTRACING_GEOMETRY_OMM_LINKAGE_DESC /
# D3D12_RAYTRACING_OPACITY_MICROMAP_HISTOGRAM_ENTRY dummies on
# D3D12_RAYTRACING_OPACITY_MICROMAP_ARRAY_BYTE_ALIGNMENT, but the 616 SDK
# headers carry the REAL OMM structs without that macro — the guard passes
# and the dummies collide with the SDK's structs (C2011, then a cascade of
# undefined-type errors). OMM structs entered the SDK at D3D12_SDK_VERSION
# 615, so gate the dummies on that; the alignment macro keeps its own
# #ifndef because DeviceD3D12.hpp uses it unconditionally. Idempotent
# in-place patch, applied at every configure (the clone is gitignored).
file(READ "${KOTEK_NRI_DIR}/Source/D3D12/SharedD3D12.h" _kotek_nri_shared_d3d12)
# normalize to LF so the match is independent of git's core.autocrlf
string(REPLACE "\r\n" "\n" _kotek_nri_shared_d3d12 "${_kotek_nri_shared_d3d12}")
set(_kotek_nri_omm_guard "#ifndef D3D12_RAYTRACING_OPACITY_MICROMAP_ARRAY_BYTE_ALIGNMENT\n#    define D3D12_RAYTRACING_OPACITY_MICROMAP_ARRAY_BYTE_ALIGNMENT 128\n\nstruct D3D12_RAYTRACING_GEOMETRY_OMM_LINKAGE_DESC {\n    bool unused;\n};\n\nstruct D3D12_RAYTRACING_OPACITY_MICROMAP_HISTOGRAM_ENTRY {\n    bool unused;\n};\n#endif")
set(_kotek_nri_omm_guard_fixed "#ifndef D3D12_RAYTRACING_OPACITY_MICROMAP_ARRAY_BYTE_ALIGNMENT\n#    define D3D12_RAYTRACING_OPACITY_MICROMAP_ARRAY_BYTE_ALIGNMENT 128\n#endif\n\n// patched by kotek (cmake/windows/nri.cmake): the 615+ SDK provides the\n// real OMM structs, defining dummies here collides with them\n#if (D3D12_SDK_VERSION < 615)\nstruct D3D12_RAYTRACING_GEOMETRY_OMM_LINKAGE_DESC {\n    bool unused;\n};\n\nstruct D3D12_RAYTRACING_OPACITY_MICROMAP_HISTOGRAM_ENTRY {\n    bool unused;\n};\n#endif")
if (_kotek_nri_shared_d3d12 MATCHES "D3D12_SDK_VERSION < 615")
	# already patched
elseif (_kotek_nri_shared_d3d12 MATCHES "D3D12_RAYTRACING_GEOMETRY_OMM_LINKAGE_DESC")
	string(REPLACE "${_kotek_nri_omm_guard}" "${_kotek_nri_omm_guard_fixed}"
		_kotek_nri_shared_d3d12 "${_kotek_nri_shared_d3d12}")
	if (NOT _kotek_nri_shared_d3d12 MATCHES "D3D12_SDK_VERSION < 615")
		message(FATAL_ERROR "[kotek]: NRI SharedD3D12.h OMM patch did not apply — upstream text drifted, update cmake/windows/nri.cmake")
	endif()
	file(WRITE "${KOTEK_NRI_DIR}/Source/D3D12/SharedD3D12.h" "${_kotek_nri_shared_d3d12}")
	message(STATUS "[kotek]: patched NRI SharedD3D12.h (OMM dummies gated on D3D12_SDK_VERSION < 615)")
endif()

# phase 1: static library, D3D12 only, no vendor extension libs
set(NRI_STATIC_LIBRARY ON CACHE BOOL "" FORCE)
set(NRI_ENABLE_D3D11_SUPPORT OFF CACHE BOOL "" FORCE)
set(NRI_ENABLE_VK_SUPPORT OFF CACHE BOOL "" FORCE)
set(NRI_ENABLE_NONE_SUPPORT OFF CACHE BOOL "" FORCE)
set(NRI_ENABLE_EXTERNAL_LIBRARIES OFF CACHE BOOL "" FORCE)

add_subdirectory("${KOTEK_NRI_DIR}" "${CMAKE_BINARY_DIR}/external/nri")
