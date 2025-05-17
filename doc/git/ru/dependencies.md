# Список зависимостей

Необходимо понимать что лицензирование текущего проекта при обновлении его же зависимостей может повлечь к состоянию когда текущая лицензия этого проекта будет несовместимой с новой лицензией какой-либо зависимости. Поэтому здесь приводится список всех лицензий всех зависимостей, и текущая лицензия которая используется

kotek-engine's (not this repository) license is Apache 2.0

ATTENTION: We appreciate your help in case when you show us where we're wrong and have incompatibale license with what we have

| Dependency's name | License | Compatibility with project's license | Explanation | 
| ----------- | ----------- | ----------- | ----------- |
| [Boost](https://github.com/boostorg/boost) | Boost Software license - Version 1.0 | Yes |  |
| [Bullet](https://github.com/bulletphysics/bullet3) | Zlib license | Yes |  |
| [DirectXMath](https://github.com/microsoft/DirectXMath) | MIT license | Yes |  |
| [Eigen](https://gitlab.com/libeigen/eigen) | MPL 2.0 license | Yes |  |
| [FMT](https://github.com/fmtlib/fmt) | MIT license | Yes | |
| [glfw3](https://github.com/glfw/glfw) | Zlib license | Yes |  |
| [glm](https://github.com/g-truc/glm) | MIT license | Yes |  |
| [ImGui](https://github.com/ocornut/imgui) | MIT license | Yes |  |
| [KTX-Software](https://github.com/KhronosGroup/KTX-Software) | Apache-2.0 license | The same as project's license |  |
| [mimalloc](https://github.com/microsoft/mimalloc) | MIT license | Yes | Yes |
| [Tracy](https://github.com/wolfpld/tracy) | 3-clause BSD license | Yes |  |
| [shaderc](https://github.com/google/shaderc) | Apache-2.0 license | The same as project's license |  |
| [SPIRV-Reflect](https://github.com/KhronosGroup/SPIRV-Reflect) | Apache-2.0 license | The same as project's license |  |
| [oneTBB](https://github.com/oneapi-src/oneTBB) | Apache-2.0 license | The same as project's license |  |
| [Visual Leak Detector](https://github.com/KindDragon/vld) | LGPL-2.1 license | Yes | We don't change the code and use only library for linking only and use dll file for 'working with library' |
| [wxWidgets](https://github.com/wxWidgets/wxWidgets) | wxWidgets license  | Yes | We don't alter the source code of WxWidgets library and use only for linking their pre-build static and dynamic libraries. As the result user gets only dynamic libraries after building the project. |
| [Google's ANGLE](https://github.com/google/angle) | Custom license | Yes |  |
| [NVIDIA PhysX](https://github.com/NVIDIA-Omniverse/PhysX) | Custom license | Yes | vcpkg doesn't support this version yet. |

- [На главную страницу](README.md)