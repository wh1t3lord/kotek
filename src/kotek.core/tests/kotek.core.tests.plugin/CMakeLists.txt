cmake_minimum_required(VERSION 3.21)

project(kotek.core.tests.plugin VERSION 1 LANGUAGES CXX)

# test double of a user-provided override dll for the plugin override system
# (task K21). NOT kotek_add_library: the target must stay a plain SHARED dll
# in EVERY linkage mode (it emulates an external replacement dll that the
# tests copy into a plugins/ folder), but it still registers its module
# entries into the generated registry (kotek_plugin_registry.h) so the
# override tests resolve it by module name like any other known module.
add_library(${PROJECT_NAME} SHARED "src/plugin_override_double.cpp")

set_property(GLOBAL APPEND PROPERTY KOTEK_MODULE_REGISTRATION_ORDER "${PROJECT_NAME}")
set_property(GLOBAL PROPERTY KOTEK_MODULE_INIT_${PROJECT_NAME} "InitializeModule_Core_Tests_Plugin")
set_property(GLOBAL PROPERTY KOTEK_MODULE_SHUTDOWN_${PROJECT_NAME} "ShutdownModule_Core_Tests_Plugin")
set_property(GLOBAL PROPERTY KOTEK_MODULE_HAS_SERIALIZE_${PROJECT_NAME} "TRUE")
set_property(GLOBAL PROPERTY KOTEK_MODULE_HAS_DESERIALIZE_${PROJECT_NAME} "TRUE")

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "framework/tests")
