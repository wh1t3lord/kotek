project('kotek.engine', default_options : ['default_library=static'])
# message('[${PROJECT_NAME}]: CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}')
# message('[${PROJECT_NAME}]: CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}')
# it is our requirement for generating the library e.g. don't just write 'cmake ..'
if '${CMAKE_BUILD_TYPE}', 'STREQUAL', ''
  # message(['FATAL_ERROR', '[${PROJECT_NAME}]: you must specify CMAKE_BUILD_TYPE flag with the following types: Debug, Release, MinSizeRel, RelWithDebInfo. It supposed to be like -DCMAKE_BUILD_TYPE=Debug'])
endif
if '${KOTEK_DEPS_FOLDER_ENABLE}', 'STREQUAL', ''
  kotek_deps_folder_enable = ['ON', 'CACHE', 'INTERNAL', '']
  # message('[${PROJECT_NAME}]: KOTEK_DEPS_FOLDER is enabled! Now you should specified your dependency folder name (but not its path)')
endif
# message('[${PROJECT_NAME}]: build type is '${CMAKE_BUILD_TYPE}'')
if '${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}', 'STREQUAL', ''
  kotek_filename_for_generating_preprocessors = './include/kotek_std_preprocessors.h'
endif
# message('[${PROJECT_NAME}]: filename for generating preprocessors: '${KOTEK_FILENAME_FOR_GENERATING_PREPROCESSORS}'')
if '${KOTEK_DEPS_FOLDER_ENABLE}', 'STREQUAL', 'ON'
  if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', ''
    # TODO: add conan here
    # message('[${PROJECT_NAME}]: trying to make an attempt to find any package manager that user provides to this path [${CMAKE_CURRENT_SOURCE_DIR}]')
    if 'EXISTS', '${CMAKE_CURRENT_SOURCE_DIR}/vcpkg'
      # message('[${PROJECT_NAME}]: VCPKG exists so we use dependencies from vcpkg')
      cmake_toolchain_file = '${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake'
      kotek_deps_folder = ['vcpkg', 'CACHE', 'INTERNAL', '']
    else
      # message(['FATAL_ERROR', '[${PROJECT_NAME}] cmake didn't find vcpkg folder where root CMakeLists.txt is located. Otherwise you have to specify your folder where dependencies are stored'])
    endif
  else
    if 'EXISTS', '${CMAKE_CURRENT_SOURCE_DIR}/${KOTEK_DEPS_FOLDER}'
      # message('[${PROJECT_NAME}]: your dependency folder is '${KOTEK_DEPS_FOLDER}'')
    else
      # message('[${PROJECT_NAME}]: your specified folder [${KOTEK_DEPS_FOLDER}] doesn't exist in path [${CMAKE_CURRENT_SOURCE_DIR}]')
    endif
  endif
endif
# include_directories('engine')
subdir('engine/kotek.core.defines.static.cpp')
subdir('engine/kotek.core.defines.static.git')
subdir('engine/kotek.core.defines.static.render')
subdir('engine/kotek.core.defines.static.render.dx')
subdir('engine/kotek.core.defines.static.render.gl')
subdir('engine/kotek.core.defines.static.render.vk')
subdir('engine/kotek.core.defines.static.math')
subdir('engine/kotek.core.defines.static.os')
subdir('engine/kotek.core.defines.static.os.win32')
subdir('engine/kotek.core.defines.static.os.linux')
subdir('engine/kotek.core.defines.static.profilers')
subdir('engine/kotek.core.defines.static.sdk')
subdir('engine/kotek.core.defines.static.string')
subdir('engine/kotek.core.defines.static.tests')
subdir('engine/kotek.core.defines.static')
subdir('engine/kotek.core.defines_dependent.text')
subdir('engine/kotek.core.defines_dependent.message')
subdir('engine/kotek.core.defines_dependent.assert')
subdir('engine/kotek.core.defines_dependent.ecs')
subdir('engine/kotek.core.defines_dependent')
subdir('engine/kotek.core.defines')
subdir('engine/kotek.core')
subdir('engine/kotek.core.api')
subdir('engine/kotek.core.types')
subdir('engine/kotek.core.types.char')
subdir('engine/kotek.core.types.numerics')
subdir('engine/kotek.core.types.string')
subdir('engine/kotek.core.casting')
subdir('engine/kotek.core.casting.lexical')
subdir('engine/kotek.core.casting.string')
subdir('engine/kotek.core.constants')
subdir('engine/kotek.core.constants.math')
subdir('engine/kotek.core.constants.ecs')
subdir('engine/kotek.core.constants.string')
subdir('engine/kotek.core.constants.window')
subdir('engine/kotek.core.containers')
subdir('engine/kotek.core.containers.any')
subdir('engine/kotek.core.containers.array')
subdir('engine/kotek.core.containers.string')
subdir('engine/kotek.core.containers.hash')
subdir('engine/kotek.core.containers.deque')
subdir('engine/kotek.core.containers.dll')
subdir('engine/kotek.core.containers.filesystem')
subdir('engine/kotek.core.containers.filesystem.path')
subdir('engine/kotek.core.containers.function')
subdir('engine/kotek.core.containers.io')
subdir('engine/kotek.core.containers.json')
subdir('engine/kotek.core.containers.map')
subdir('engine/kotek.core.containers.microsoft')
subdir('engine/kotek.core.containers.microsoft.wrl.comptr')
subdir('engine/kotek.core.containers.multithreading')
subdir('engine/kotek.core.containers.multithreading.tbb')
subdir('engine/kotek.core.containers.multithreading.atomic')
subdir('engine/kotek.core.containers.multithreading.mutex')
subdir('engine/kotek.core.containers.multithreading.shared_mutex')
subdir('engine/kotek.core.containers.multithreading.thread')
subdir('engine/kotek.core.containers.multithreading.semaphore')
subdir('engine/kotek.core.containers.pair')
subdir('engine/kotek.core.containers.queue')
subdir('engine/kotek.core.containers.shared_ptr')
subdir('engine/kotek.core.containers.unique_ptr')
subdir('engine/kotek.core.containers.unordered_map')
subdir('engine/kotek.core.containers.unordered_set')
subdir('engine/kotek.core.containers.variant')
subdir('engine/kotek.core.containers.vector')
subdir('engine/kotek.core.filesystem')
subdir('engine/kotek.core.filesystem.file_text')
subdir('engine/kotek.core.format')
subdir('engine/kotek.core.memory')
subdir('engine/kotek.core.memory.cpu')
subdir('engine/kotek.core.memory.gpu')
subdir('engine/kotek.core.memory.gpu.vulkan')
if '${KOTEK_MEMORY_LEAK_DETECTION}', 'STREQUAL', 'ON'
  if '${KOTEK_CPP_MEMORY_LEAK_LIBRARY}', 'STREQUAL', 'VLD'
    subdir('engine/kotek.core.memory.vld')
  endif
endif
subdir('engine/kotek.core.math')
subdir('engine/kotek.core.profilers')
subdir('engine/kotek.core.profilers.cpu')
subdir('engine/kotek.core.profilers.gpu')
subdir('engine/kotek.core.resource_manager')
subdir('engine/kotek.core.resource_manager.loader')
subdir('engine/kotek.core.resource_manager.saver')
subdir('engine/kotek.core.os')
subdir('engine/kotek.core.os.win32')
subdir('engine/kotek.core.os.linux')
subdir('engine/kotek.core.window')
subdir('engine/kotek.core.window.glfw')
subdir('engine/kotek.core.window_manager')
subdir('engine/kotek.core.log')
subdir('engine/kotek.core.console')
subdir('engine/kotek.core.engine_config')
subdir('engine/kotek.core.main_manager')
subdir('engine/kotek.core.ecs')
subdir('engine/kotek.core.enum')
subdir('engine/kotek.core.enum.core')
subdir('engine/kotek.core.enum.render')
subdir('engine/kotek.core.enum.render.dx')
subdir('engine/kotek.core.enum.render.gl')
subdir('engine/kotek.core.enum.render.vk')
subdir('engine/kotek.core.input')
subdir('engine/kotek.core.utility')
subdir('engine/kotek.game')
subdir('engine/kotek.ui')
subdir('engine/kotek.ui.imgui')
if '${KOTEK_UI_GAME_LIBRARY}', 'STREQUAL', 'CEF'
  subdir('engine/kotek.ui.cef')
elif '${KOTEK_UI_GAME_LIBRARY}', 'STREQUAL', 'RMLUI'
  subdir('engine/kotek.ui.rmlui')
endif
subdir('engine/kotek.ui.videoplayer')
subdir('engine/kotek.ui.videoplayer.avif')
if 'WIN32'
  # DEPRECATED: undo comments when you finish vulkan renderer!
  #add_subdirectory("engine/kotek.render.dx12")
endif
subdir('engine/kotek.render')
subdir('engine/kotek.render.shared')
subdir('engine/kotek.render.shared.vk')
subdir('engine/kotek.render.shared.gl')
subdir('engine/kotek.render.shared.dx')
subdir('engine/kotek.render.model')
subdir('engine/kotek.render.model.assimp')
subdir('engine/kotek.render.model.cgltf')
subdir('engine/kotek.render.vk')
subdir('engine/kotek.render.gl')
subdir('engine/kotek.render.gl.glad')
subdir('engine/kotek.render.software')
subdir('engine/kotek.render.angle.gles')
subdir('engine/kotek.render.angle.gles23')
subdir('engine/kotek.exe')
# set_property(['DIRECTORY', cmake_current_source_dir, 'PROPERTY', 'VS_STARTUP_PROJECT', 'kotek'])
