project('kotek.core.math', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
if '${KOTEK_DEPS_FOLDER_ENABLE}', 'STREQUAL', 'ON'
  if '${KOTEK_MATH_LIBRARY}', 'STREQUAL', 'GLM'
    if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
      glm_dep = dependency('glm')
    else
      glm_dep = dependency('glm')
    endif
  elif '${KOTEK_MATH_LIBRARY}', 'STREQUAL', 'DXM'
    if '${KOTEK_DEPS_FOLDER}', 'STREQUAL', 'vcpkg'
      directxmath_dep = dependency('directxmath')
    else
      directxmath_dep = dependency('directxmath')
    endif
  endif
endif
# message('[${PROJECT_NAME}]: math library is '${KOTEK_MATH_LIBRARY}'')
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_std_alias_math.h', 'include/kotek_std_math_vector1f.h', 'include/kotek_std_math_vector2f.h', 'include/kotek_std_math_vector3f.h', 'include/kotek_std_math_vector4f.h', 'include/kotek_std_math_quaternionf.h', 'include/kotek_std_math_matrix_2x2_f.h', 'include/kotek_std_math_matrix_3x3_f.h', 'include/kotek_std_math_matrix_4x4_f.h', 'include/kotek_std_math.h', 'include/kotek_core_math.h', 'tests/kotek_core_test_math.cpp', 'src/main_core_math_dll.cpp')
if '${KOTEK_MATH_LIBRARY}', 'STREQUAL', 'GLM'
  # target_include_directories([project_name, 'PUBLIC', 'glm::glm'])
elif '${KOTEK_MATH_LIBRARY}', 'STREQUAL', 'DXM'
  # target_include_directories([project_name, 'PUBLIC', 'Microsoft::DirectXMath'])
endif
if '${KOTEK_MATH_LIBRARY}', 'STREQUAL', 'GLM'
  # target_link_libraries([project_name, 'PUBLIC', 'glm::glm'])
elif '${KOTEK_MATH_LIBRARY}', 'STREQUAL', 'DXM'
  # target_link_libraries([project_name, 'PUBLIC', 'Microsoft::DirectXMath'])
endif
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.math'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines_dependent.assert'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.types.numerics'])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.utility'])
