if (WIN32)
    find_program(NUGET_COMMAND nuget)
    if(NOT NUGET_COMMAND)
        message("NuGet not found in PATH!")
        message("Downloading NuGet...")
        if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/nuget")
            execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_SOURCE_DIR}/nuget")
            file(DOWNLOAD https://dist.nuget.org/win-x86-commandline/latest/nuget.exe
                "${CMAKE_CURRENT_SOURCE_DIR}/nuget/nuget.exe")
        endif()
        set(NUGET_COMMAND "${CMAKE_BINARY_DIR}/nuget/nuget.exe")
        message("NuGet downloaded: ${NUGET_COMMAND}")
    else()
        message("NuGet found: ${NUGET_COMMAND}")
    endif()
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(KOTEK_NUGET_ARCH_BIT_NUMBER "x64" CACHE INTERNAL "")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(KOTEK_NUGET_ARCH_BIT_NUMBER "x86" CACHE INTERNAL "")
endif()

if (WIN32)
    set(KOTEK_NUGET_CMAKE_FOLDER_PLATFORM_NAME "windows" CACHE INTERNAL "")
    if (MSVC)
        set(KOTEK_NUGET_COMPILER_NAME "Msvc" CACHE INTERNAL "")
        message("Your OS is: ${CMAKE_SYSTEM_NAME} with version ${CMAKE_SYSTEM_VERSION}")
        message("Determing your exact Windows version based on build number...")
        if ("${CMAKE_SYSTEM_VERSION}" STRGREATER_EQUAL "10.0.")
            string(SUBSTRING "${CMAKE_SYSTEM_VERSION}" 5 -1 kotek_win_build_number)
            message("Your build number: ${kotek_win_build_number}")

            if ("${kotek_win_build_number}" STREQUAL "10240")
                set(KOTEK_NUGET_PLATFORM_NAME "Win10" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 10, Version 1507")
            elseif ("${kotek_win_build_number}" STREQUAL "10586")
                set(KOTEK_NUGET_PLATFORM_NAME "Win10" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 10, Version 1511")
            elseif ("${kotek_win_build_number}" STREQUAL "14393")
                set(KOTEK_NUGET_PLATFORM_NAME "Win10" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 10, Version 1607 or Windows Server 2016, Version 1607")
            elseif ("${kotek_win_build_number}" STREQUAL "15063")
                set(KOTEK_NUGET_PLATFORM_NAME "Win10" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 10, Version 1703")
            elseif ("${kotek_win_build_number}" STREQUAL "16299")
                set(KOTEK_NUGET_PLATFORM_NAME "Win10" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 10, Version 1709")
            elseif ("${kotek_win_build_number}" STREQUAL "17134")
                set(KOTEK_NUGET_PLATFORM_NAME "Win10" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 10, Version 1803")
            elseif ("${kotek_win_build_number}" STREQUAL "17763")
                set(KOTEK_NUGET_PLATFORM_NAME "Win10" CACHE INTERNAL "")
                message("Build number says your OS is: Windows Server 2019, Version 1809 or Windows 10, Version 1809")
            elseif ("${kotek_win_build_number}" STREQUAL "18362")
                set(KOTEK_NUGET_PLATFORM_NAME "Win10" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 10, Version 1903")
            elseif ("${kotek_win_build_number}" STREQUAL "18363")
                set(KOTEK_NUGET_PLATFORM_NAME "Win10" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 10, Version 1909 or Windows Server, Version 1909")
            elseif ("${kotek_win_build_number}" STREQUAL "19041")
                set(KOTEK_NUGET_PLATFORM_NAME "Win10" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 10, Version 2004 or Windows Server, Version 2004")
            elseif ("${kotek_win_build_number}" STREQUAL "19042")
                set(KOTEK_NUGET_PLATFORM_NAME "Win10" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 10, Version 20H2")
            elseif ("${kotek_win_build_number}" STREQUAL "19043")
                set(KOTEK_NUGET_PLATFORM_NAME "Win10" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 10, Version 21H1")
            elseif ("${kotek_win_build_number}" STREQUAL "19044")
                set(KOTEK_NUGET_PLATFORM_NAME "Win10" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 10, Version 21H2")         
            elseif ("${kotek_win_build_number}" STREQUAL "19045")
                set(KOTEK_NUGET_PLATFORM_NAME "Win10" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 10, Version 22H2")
            elseif ("${kotek_win_build_number}" STREQUAL "22000")
                set(KOTEK_NUGET_PLATFORM_NAME "Win11" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 11, Version 21H2")
            elseif ("${kotek_win_build_number}" STREQUAL "22621")
                set(KOTEK_NUGET_PLATFORM_NAME "Win11" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 11, Version 22H2")
            elseif ("${kotek_win_build_number}" STREQUAL "22631")
                set(KOTEK_NUGET_PLATFORM_NAME "Win11" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 11, Version 23H2")
            else()
                message(FATAL_ERROR "failed to determine windows based on your build number [${kotek_win_build_number}] report to kotek developers -> https://gitlab.com/wh1t3lord/kotek/-/issues")
            endif()
        elseif ("${CMAKE_SYSTEM_VERSION}" STRGREATER_EQUAL "6.2.")
            string(SUBSTRING "${CMAKE_SYSTEM_VERSION}" 4 -1 kotek_win_build_number)
            message("Your build number: ${kotek_win_build_number}")

            if ("${kotek_win_build_number}" STREQUAL "9200")
                set(KOTEK_NUGET_PLATFORM_NAME "Win8" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 8")
            else()
                message(FATAL_ERROR "failed to determine windows based on your build number [${kotek_win_build_number}] report to kotek developers -> https://gitlab.com/wh1t3lord/kotek/-/issues")
            endif()
        elseif ("${CMAKE_SYSTEM_VERSION}" STRGREATER_EQUAL "6.3.")
            string(SUBSTRING "${CMAKE_SYSTEM_VERSION}" 4 -1 kotek_win_build_number)
            message("Your build number: ${kotek_win_build_number}")

            if ("${kotek_win_build_number}" STREQUAL "9600")
                set(KOTEK_NUGET_PLATFORM_NAME "Win8.1" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 8.1 or Windows Server 2012 R2")
            else()
                message(FATAL_ERROR "failed to determine windows based on your build number [${kotek_win_build_number}] report to kotek developers -> https://gitlab.com/wh1t3lord/kotek/-/issues")
            endif()
        elseif ("${CMAKE_SYSTEM_VERSION}" STRGREATER_EQUAL "6.1.")
            string(SUBSTRING "${CMAKE_SYSTEM_VERSION}" 4 -1 kotek_win_build_number)
            message("Your build number: ${kotek_win_build_number}")

            if ("${kotek_win_build_number}" STREQUAL "7600")
                set(KOTEK_NUGET_PLATFORM_NAME "Win7" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 7 or Windows Server 2008 R2")
            elseif ("${kotek_win_build_number}" STREQUAL "7601")
                set(KOTEK_NUGET_PLATFORM_NAME "Win7" CACHE INTERNAL "")
                message("Build number says your OS is: Windows 7, Service Pack 1 or Windows Server 2008 R2, Service Pack 1")
            elseif ("${kotek_win_build_number}" STREQUAL "8400")
                set(KOTEK_NUGET_PLATFORM_NAME "Win7" CACHE INTERNAL "")
                message("Build number says your OS is: Windows Home Server 2011")
            else()
                message(FATAL_ERROR "failed to determine windows based on your build number [${kotek_win_build_number}] report to kotek developers -> https://gitlab.com/wh1t3lord/kotek/-/issues")
            endif()
        else()
            message(FATAL_ERROR "unsupported windows build or version, report to kotek developers -> https://gitlab.com/wh1t3lord/kotek/-/issues")
        endif()

        message("Getting packages for ${KOTEK_NUGET_PLATFORM_NAME} based on compiler ${KOTEK_NUGET_COMPILER_NAME}")
        message("Generated package config name: [${KOTEK_NUGET_PLATFORM_NAME}-${KOTEK_NUGET_COMPILER_NAME}-Packages]")
        message("Searching for file...")

        if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${KOTEK_NUGET_CMAKE_FOLDER_PLATFORM_NAME}/${KOTEK_NUGET_PLATFORM_NAME}-${KOTEK_NUGET_COMPILER_NAME}-Packages.config")
            message("Using packages config file [${KOTEK_NUGET_PLATFORM_NAME}-${KOTEK_NUGET_COMPILER_NAME}-Packages.config]")
            message("Making config usable for nuget")
            
            if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${KOTEK_NUGET_CMAKE_FOLDER_PLATFORM_NAME}/packages.config")
               # message("removing existing packages.config, because we don't need it")
                file(REMOVE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${KOTEK_NUGET_CMAKE_FOLDER_PLATFORM_NAME}/packages.config)
            endif()

            if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/nuget")
                file(REMOVE_RECURSE ${CMAKE_CURRENT_SOURCE_DIR}/nuget)
            endif()
            
            
            file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${KOTEK_NUGET_CMAKE_FOLDER_PLATFORM_NAME}/${KOTEK_NUGET_PLATFORM_NAME}-${KOTEK_NUGET_COMPILER_NAME}-Packages.config DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${KOTEK_NUGET_CMAKE_FOLDER_PLATFORM_NAME}/rename)
            if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${KOTEK_NUGET_CMAKE_FOLDER_PLATFORM_NAME}/rename/${KOTEK_NUGET_PLATFORM_NAME}-${KOTEK_NUGET_COMPILER_NAME}-Packages.config")
                message(FATAL_ERROR "failed to copy file, request more rights for CMake, aborting...")
            endif()
           # message("copy was successful!")

            file(RENAME ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${KOTEK_NUGET_CMAKE_FOLDER_PLATFORM_NAME}/rename/${KOTEK_NUGET_PLATFORM_NAME}-${KOTEK_NUGET_COMPILER_NAME}-Packages.config ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${KOTEK_NUGET_CMAKE_FOLDER_PLATFORM_NAME}/rename/packages.config)

            if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${KOTEK_NUGET_CMAKE_FOLDER_PLATFORM_NAME}/rename/packages.config")
                message(FATAL_ERROR "failed to rename file, request more rights for CMake, aborting...")
            endif()

           # message("rename was successful!")

            file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${KOTEK_NUGET_CMAKE_FOLDER_PLATFORM_NAME}/rename/packages.config DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${KOTEK_NUGET_CMAKE_FOLDER_PLATFORM_NAME})

            if (NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${KOTEK_NUGET_CMAKE_FOLDER_PLATFORM_NAME}/packages.config")
                message(FATAL_ERROR "failed to move file packages.config to directory ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${KOTEK_NUGET_CMAKE_FOLDER_PLATFORM_NAME} probably you should give more rights to CMake or enable writing mode for specified folder")
            endif()

           # message("move was successful!")

            file(REMOVE_RECURSE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${KOTEK_NUGET_CMAKE_FOLDER_PLATFORM_NAME}/rename)

            if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${KOTEK_NUGET_CMAKE_FOLDER_PLATFORM_NAME}/rename")
                message(FATAL_ERROR "failed to remove folder ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${KOTEK_NUGET_CMAKE_FOLDER_PLATFORM_NAME}/rename")
            endif()

            message("Start to download packages from config...")

            execute_process(
                COMMAND ${NUGET_COMMAND} restore ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${KOTEK_NUGET_CMAKE_FOLDER_PLATFORM_NAME}/packages.config -SolutionDirectory ${CMAKE_CURRENT_SOURCE_DIR}/nuget
            )

			# Validating libs and dlls because we can make some errors with packags configuration 
			# Like mistake with paths and lib can store in dlls folder or dlls in libs...

			# So we need to fix that mistake

			file(GLOB nuget_packages RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages  ${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/Kotek.Packages.*)
			
			foreach (folder_name IN LISTS nuget_packages)
				if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}")
					if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes")
						if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}")
							if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}")
								if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}")
									if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib" AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/bin")
										if (WIN32)
											message("validating package folder: ${folder_name}")
											file(GLOB package_libs_names_in_debug_dll_folder RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/bin/Debug/ ${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/bin/Debug/*.lib)
											file(GLOB package_libs_names_in_release_dll_folder RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/bin/Release/ ${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/bin/Release/*.lib)

											file(GLOB package_dlls_names_in_debug_lib_folder RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/ 
												${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/*.dll
												${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/*.pdb
											)
											file(GLOB package_dlls_names_in_release_lib_folder RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/ 
												${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/*.dll
												${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/*.pdb
											)
											if ("${package_libs_names_in_debug_dll_folder}" MATCHES ".lib")
												message("--Found libs in Debug dlls!")

												foreach (lib_name IN LISTS package_libs_names_in_debug_dll_folder)
													file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/bin/Debug/${lib_name}" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/")

													if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/${lib_name}")
														message("\tMoving file to correct folder: ${lib_name}")
													endif()
												endforeach()
											endif()

											if ("${package_libs_names_in_release_dll_folder}" MATCHES ".lib")
												message("--Found libs in Release dlls!")
												
												foreach (lib_name IN LISTS package_libs_names_in_release_dll_folder)
													file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/bin/Release/${lib_name}" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/")

													if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/${lib_name}")
														message("\tMoving file to correct folder: ${lib_name}")
													endif()
												endforeach()
											endif()

											if ("${package_dlls_names_in_debug_lib_folder}" MATCHES ".pdb" OR "${package_dlls_names_in_debug_lib_folder}" MATCHES ".dll")
												message("--Found dlls in Debug libs!")

												foreach (lib_name IN LISTS package_dlls_names_in_debug_lib_folder)
													file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Debug/${lib_name}" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/bin/Debug/")

													if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/bin/Debug/${lib_name}")
														message("\tMoving file to correct folder: ${lib_name}")
													endif()
												endforeach()
											endif()

											if ("${package_dlls_names_in_release_lib_folder}" MATCHES ".pdb" OR "${package_dlls_names_in_release_lib_folder}" MATCHES ".dll")
												message("--Found dlls in Release libs!")

												foreach (lib_name IN LISTS package_dlls_names_in_release_lib_folder)
													file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/lib/Release/${lib_name}" DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/bin/Release/")

													if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/nuget/packages/${folder_name}/runtimes/${KOTEK_NUGET_PLATFORM_NAME}/${KOTEK_NUGET_COMPILER_NAME}/${KOTEK_NUGET_ARCH_BIT_NUMBER}/bin/Release/${lib_name}")
														message("\tMoving file to correct folder: ${lib_name}")
													endif()
												endforeach()
											endif()
										else()
											message(FATAL_ERROR "provide implementation for other platforms...")
										endif()
									endif()
								endif()
							endif()
						endif()
					endif()
				endif()
			endforeach()

        else()
            message(FATAL_ERROR "failed to obtain file: [${KOTEK_NUGET_PLATFORM_NAME}-${KOTEK_NUGET_COMPILER_NAME}-Packages.config] report to kotek developers -> https://gitlab.com/wh1t3lord/kotek/-/issues")
        endif()
    endif()
endif()