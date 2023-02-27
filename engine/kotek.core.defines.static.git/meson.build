project('kotek.core.defines.static.git', 'version', '1', 'languages', 'cpp', default_options : ['default_library=static'])
cmake_cxx_standard = '20'
cmake_cxx_standard_required = 'ON'
Git_dep = dependency('Git')
if 'GIT_FOUND'
  # list(['APPEND', 'KOTEK_OUTPUT_FLAGS', '-DKOTEK_GIT_WAS_FOUND'])
  # execute_process(['COMMAND', git_executable, 'rev-parse', 'HEAD', 'WORKING_DIRECTORY', cmake_current_source_dir, 'RESULT_VARIABLE', 'kotek_git_status', 'OUTPUT_VARIABLE', 'KOTEK_GIT_CURRENT_COMMIT', 'OUTPUT_STRIP_TRAILING_WHITESPACE'])
  if 'kotek_git_status'
    # message('[${PROJECT_NAME}]: failed to get current commit, status: '${kotek_git_status}'')
  endif
  # execute_process(['COMMAND', git_executable, 'rev-parse', '--abbrev-ref', 'HEAD', 'WORKING_DIRECTORY', cmake_current_source_dir, 'RESULT_VARIABLE', 'kotek_git_status', 'OUTPUT_VARIABLE', 'KOTEK_GIT_CURRENT_BRANCH_NAME', 'OUTPUT_STRIP_TRAILING_WHITESPACE'])
  if 'kotek_git_status'
    # message('[${PROJECT_NAME}]: failed to get current branch name, status: '${kotek_git_status}'')
  endif
  # execute_process(['COMMAND', git_executable, 'rev-list', '--count', 'HEAD', 'WORKING_DIRECTORY', cmake_current_source_dir, 'RESULT_VARIABLE', 'kotek_git_status', 'OUTPUT_VARIABLE', 'KOTEK_GIT_CURRENT_COMMIT_COUNT_FOR_CURRENT_BRANCH', 'OUTPUT_STRIP_TRAILING_WHITESPACE'])
  if 'kotek_git_status'
    # message('[${PROJECT_NAME}]: failed to get current commit count, status: '${kotek_git_status}'')
  endif
  # string(['TIMESTAMP', 'KOTEK_WHEN_YOU_GENERATED_SOLUTION', '%w %A %B %Y %H:%M:%S'])
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once

	#ifdef KOTEK_GIT_WAS_FOUND
		#define KOTEK_USE_GIT_CURRENT_COMMIT ${KOTEK_GIT_CURRENT_COMMIT}
		#define KOTEK_USE_GIT_CURRENT_BRANCH_NAME ${KOTEK_GIT_CURRENT_BRANCH_NAME}
		#define KOTEK_USE_GIT_CURRENT_COMMIT_COUNT_FOR_CURRENT_BRANCH ${KOTEK_GIT_CURRENT_COMMIT_COUNT_FOR_CURRENT_BRANCH}
		#define KOTEK_USE_WHEN_YOU_GENERATED_SOLUTION ${KOTEK_WHEN_YOU_GENERATED_SOLUTION}
	#endif
	'])
else
  # message(['WARNING', '[${PROJECT_NAME}]: can't find Git for generating preprocessors!'])
  # file(['WRITE', kotek_filename_for_generating_preprocessors, '#pragma once'])
endif
PROJECT_NAME_lib = static_library(project_name, 'include/kotek_std_preprocessors.h', 'include/kotek_core_defines_static_git.h', 'src/main_core_defines_static_git_dll.cpp')
# target_compile_definitions([project_name, 'PUBLIC', kotek_output_flags])
# target_link_libraries([project_name, 'PUBLIC', 'kotek.core.defines.static.cpp'])
