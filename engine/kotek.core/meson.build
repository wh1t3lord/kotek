project('kotek.core', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
# add_compile_options('$<$<CXX_COMPILER_ID:MSVC>:/MP>')
if '${KOTEK_DEPS_FOLDER_ENABLE}', 'STREQUAL', 'ON'
  if '${KOTEK_STD_LIBRARY}', 'STREQUAL', 'BOOST'
    if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
      Boost_dep = dependency('Boost')
    else
      Boost_dep = dependency('Boost')
    endif
  endif
endif
if '${KOTEK_TESTS}', 'STREQUAL', 'ON', 'AND', '${KOTEK_TESTS_RUNTIME}', 'STREQUAL', 'ON'
  # message('[${PROJECT_NAME}]: adding tests for runtime in project ${PROJECT_NAME}')
  to_include_tests = ['tests/kotek_core_test_filesystem.cpp', 'tests/kotek_core_test_json.cpp']
elif '${KOTEK_TESTS}', 'STREQUAL', 'ON', 'AND', '${KOTEK_TESTS_RUNTIME}', 'STREQUAL', 'OFF'
  # TODO: add support for own projects for unit testing
  # message('[${PROJECT_NAME}]: creating test projects for project ${PROJECT_NAME}')
  to_include_tests = ''
else
  # message('[${PROJECT_NAME}]: tests are disabled for project ${PROJECT_NAME}')
  to_include_tests = ''
endif
# message('[${PROJECT_NAME}]: files to attach (KOTEK_TESTS): ${to_include_tests}')
PROJECT_NAME_lib = static_library(project_name, 'src/main_core_dll.cpp', 'include/kotek_core.h', 'include/kotek_json_casting_math_matrix.h', 'include/kotek_json_casting_math_vector.h', 'include/kotek_json_casting_std_vector.h', 'include/kotek_json_casting_std_map.h', 'include/kotek_json_casting_string.h', 'include/kotek_json_casting_other.h', to_include_tests)
if '${KOTEK_STD_LIBRARY}', 'STREQUAL', 'BOOST'
  # target_link_libraries([project_name, 'PUBLIC', 'Boost::headers', 'Boost::json', 'Boost::unit_test_framework', 'Boost::filesystem'])
endif
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.enum'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.api'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.casting'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.containers'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.constants'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.console'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.memory'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.math'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.filesystem'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.format'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.types'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.os'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.log'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.main_manager'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.resource_manager'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.window_manager'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.ecs'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.input'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.utility'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.profilers'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.engine_config'])
