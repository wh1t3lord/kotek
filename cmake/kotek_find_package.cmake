# kotek_find_package(<dep> [usual find_package args...]) — task K10
#
# One dependency resolution entry point for every module. In the default
# (vcpkg) and nuget modes it is a plain pass-through to find_package. In
# MANUAL mode (KOTEK_DEPS_FOLDER is a user folder, resolved once to
# KOTEK_DEPS_FOLDER_PATH at the root) it resolves, in order:
#   1. <folder>/deps.json — exact path overrides for stray layouts:
#        { "Tracy": "D:/libs/tracy-0.13.1", "glm": "../third_party/glm" }
#      (keys are the find_package names, case-sensitive; relative paths are
#      relative to the deps folder)
#   2. <folder>/<dep>/ — the convention layout (vcpkg-style: the package's
#      *Config.cmake under share/, lib/cmake/ or the root — anything
#      find_package CONFIG finds under a prefix)
#   3. plain find_package (vcpkg/system fallback)
# NO_DEFAULT_PATH is used for 1+2: what the user pointed at is authoritative.

function(kotek_find_package dep)
	# static-CRT builds need the static zlib names (zs/zsd); the vcpkg
	# toolchain sets ZLIB_USE_STATIC_LIBS itself, manual mode does not
	if (dep STREQUAL "ZLIB")
		if ("${KOTEK_VCPKG_TRIPLET}" MATCHES "static")
			set(ZLIB_USE_STATIC_LIBS ON)
		endif()
		find_package(${dep} ${ARGN})
		# without the vcpkg toolchain the find lands on ZLIBConfig.cmake,
		# which exports ZLIB::ZLIBSTATIC only — vcpkg's own cmake wrapper is
		# what normally aliases ZLIB::ZLIB for consumers (freetype/png's
		# exports reference it), so manual mode must bridge it itself
		if (NOT TARGET ZLIB::ZLIB AND TARGET ZLIB::ZLIBSTATIC)
			add_library(ZLIB::ZLIB ALIAS ZLIB::ZLIBSTATIC)
		endif()
		return()
	endif()

	set(_kotek_manual OFF)
	if (NOT "${KOTEK_DEPS_FOLDER}" STREQUAL "" AND
		NOT "${KOTEK_DEPS_FOLDER}" STREQUAL "vcpkg" AND
		NOT "${KOTEK_DEPS_FOLDER}" STREQUAL "nuget" AND
		NOT "${KOTEK_DEPS_FOLDER_PATH}" STREQUAL "")
		set(_kotek_manual ON)
	endif()

	if (_kotek_manual)
		# 1. deps.json override
		if (EXISTS "${KOTEK_DEPS_FOLDER_PATH}/deps.json")
			file(READ "${KOTEK_DEPS_FOLDER_PATH}/deps.json" _kotek_deps_json)
			string(JSON _kotek_dep_path ERROR_VARIABLE _kotek_json_err
				GET "${_kotek_deps_json}" "${dep}")
			if (NOT _kotek_json_err)
				if (NOT IS_ABSOLUTE "${_kotek_dep_path}")
					set(_kotek_dep_path "${KOTEK_DEPS_FOLDER_PATH}/${_kotek_dep_path}")
				endif()
				message(STATUS "[kotek]: ${dep} resolved via deps.json -> ${_kotek_dep_path}")
				find_package(${dep} ${ARGN} PATHS "${_kotek_dep_path}" NO_DEFAULT_PATH)
				return()
			endif()
		endif()

		# 2. convention folder <folder>/<dep>/
		if (EXISTS "${KOTEK_DEPS_FOLDER_PATH}/${dep}")
			message(STATUS "[kotek]: ${dep} resolved via ${KOTEK_DEPS_FOLDER} -> ${KOTEK_DEPS_FOLDER_PATH}/${dep}")
			find_package(${dep} ${ARGN} PATHS "${KOTEK_DEPS_FOLDER_PATH}/${dep}" NO_DEFAULT_PATH)
			return()
		endif()
	endif()

	# 3. fallback (vcpkg/system)
	find_package(${dep} ${ARGN})
endfunction()
