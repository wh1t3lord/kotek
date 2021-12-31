# Before READING
THIS PROJECT DOESNT HAVE THE 1.0v. It means if you want to use it for serious development you need to understand that you will get break-changes if you want to use engine without any break-changes you need to wait for 1.0v release!

1.0v means:
* Авторы проверили движок на названия функций и заявили что это их конечное состояние (то есть не будет никаких переименований от слова совсем)
* Авторы проверили движок на очень сильном тесте (реализация полноценной игры)
* Авторы завершили рефакторинг всех компонент которые не будут меняться (не имеется в виду что конечный рефакторинг, но тот который явно можно сделать, сейчас)
* Авторы имеют полное и завершенное представление о системе тем самым выпуская эту версию
* Авторы реализовали все последние техники, и те функции которые могли бы вызывать break-changes
* Авторы полностью проверили все места, которые вероятно всего придётся расширять и самое главное они способны к такому расширению, чтобы не вызывать break-changes
* Авторы создают опрос среди сообщества, чтобы сообщество помогло найти проблемные места, либо высказать своё мнение о том, имеет ли движок способность к break-changes или нет
* Авторы уделили достаточное количество времени, чтобы сделать выпуск версии 1.0v, однако необходимо сделать пред-официальный выпуск и сделать тесты среди сообщество, желательно чтобы сообщество делало не только проекты об играх

Что это значит? 
Все последующие версии не будут иметь никаких break-changes начиная с этой версии (1.0v)

# How to use

- git clone this repo
- navigate to repo
- git checkout main (kotek-engine-deps-win32 too!!!!)
- mkdir build (or create manually through File Explorer)
- git submodule update --init --recursive --remote
- cd build
- cmake .. (but it's better to check Building section before writing this command)
- Build the project 
- Run the project

# Project overview

- Использует С++20 как основной стандарт, движок не предназначен для отката на старые стандарты (то есть ниже 20), то есть это первоночальный стандарт который движок обязан поддерживать независимо от каких-либо условий, если выйдет С++30 (если данный стандарт не имеет break-changes), то в таком случае С++20 это стандартный стандарт который будет работать.
- Движок не стремиться иметь хоть какое-либо legacy, то есть мы постоянно обновляем движок и всего соответствующие компоненты, а сам код мы только расширяем, но ничего не меняем, либо меняем только приватные части, чтобы не возникало break-changes или legacy как такового.
- Монолитно-модульная система
- Основная библиотека типов основана на stl и ей подобных библиотеках (к примеру Boost)
- Иметь возможность смены каких-либо компонент, к примеру математическую библиотеку заменить на Eigen или glm или DirectX и т.п.
- Две экосистемы, одна для игры, другая для движка
- Поддерживает пока что Windows

# Build status

| Platform | Compiler | Configuration | CMake commands | Description | Status |
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| Windows 10 | Visual Studio 2019 | Debug |  "-DCMAKE_BUILD_TYPE=Debug" | This configuration generating the solution with full defaults arguments. So check the section 'Default arguments' in order to understand what values takes cmake by itself | |
| Windows 10 | Visual Studio 2019 | Release |  "-DCMAKE_BUILD_TYPE=Release" | This configuration generating the solution with full defaults arguments. So check the section 'Default arguments' in order to understand what values takes cmake by itself | |
| Windows 10 | Visual Studio 2019 | Debug |  "-DCMAKE_BUILD_TYPE=Debug -DKOTEK_MATH_LIBRARY=GLM" | This solution uses GLM as math library | |

# Building

This project is based on cmake version 3.19.3 and for generating solution you need to understand the following commands before write "cmake -DCMAKE_BUILD_TYPE=YOUR_BUILD_TYPE .."

It's really important! You must write -DCMAKE_BUILD_TYPE=... without it the cmake can't generate the solution properly.

What will it be if you just write "cmake -DCMAKE_BUILD_TYPE=YOUR_BUILD_TYPE .."?

All other flags will be set ON or any other parameter that somehow specifies it.

## Default arguments
Defaults if you don't specify them

LINUX Platform:

| Flag | Release | Debug |
| ----------- | ----------- | ----------- |
| -DKOTEK_UNICODE | ON |  ON |
| -DKOTEK_SDK | ON |  ON |
| -DKOTEK_CPU_PROFILER | ON |  OFF |
| -DKOTEK_GPU_PROFILER | ON |  OFF |
| -DKOTEK_MATH_LIBRARY | GLM |  GLM |
| -DKOTEK_MATH_PRECISION | FLOAT |  FLOAT |
| -DKOTEK_USER_DEPS_ENGINE | nothing |  nothing |
| -DKOTEK_USER_DEPS_GAME | nothing |  nothing |
| -DKOTEK_TESTS | OFF |  ON |
| -DKOTEK_TESTS_RUNTIME | OFF |  ON |

WINDOWS Platform:

| Flag | Release | Debug |
| ----------- | ----------- | ----------- |
| -DKOTEK_UNICODE | ON |  ON |
| -DKOTEK_SDK | ON |  ON |
| -DKOTEK_CPU_PROFILER | ON |  OFF |
| -DKOTEK_GPU_PROFILER | ON |  OFF |
| -DKOTEK_MATH_LIBRARY | DXM | DXM |
| -DKOTEK_MATH_PRECISION | FLOAT |  FLOAT |
| -DKOTEK_USER_DEPS_ENGINE | nothing |  nothing |
| -DKOTEK_USER_DEPS_GAME | nothing |  nothing |
| -DKOTEK_TESTS | OFF |  ON |
| -DKOTEK_TESTS_RUNTIME | OFF |  ON |


* -DCMAKE_BUILD_TYPE=STATUS
With this command you can specify the building type and if you don't know what they are you need to learn by your own.

For example: "-DCMAKE_BUILD_TYPE=Debug" will generate a Debug project.

ATTENTION: YOU MUST SPECIFY ARGUMENT FOR THIS COMMAND IN ACCORDING TO THAT TABLE. It means you can't write -DCMAKE_BUILD_TYPE=debug or -DCMAKE_BUILD_TYPE=DeBuG.

| DCMAKE_BUILD_TYPE=STATUS |
| ----------- |
| Debug |
| Release |
| MinSizeRel |
| RelWithDebInfo |

DEFAULT VALUE: there's no default value. You must specify this flag.

* -DKOTEK_UNICODE=STATUS
With this command you specify char type for ktk::string class and what it will use.

But you need to understand that by our standard ktk::string supports char by default. So if you use project with UNICODE it means ktk::string can accept your unicode string and "char" string too. If you don't use UNICODE it means ktk::string supports only "char".

| char_type | DKOTEK_UNICODE=STATUS | PLATFORM | Explanation |
| ----------- | ----------- | ----------- | ----------- |
| char16_t | ON       | WINDOWS | Engine uses unicode support and adding the appropriate global definitions like -DUNICODE for Windows. |
| char     | OFF      | WINDOWS | Engine doesn't use unicode. You have only char strings. |
| char32_t | ON       | LINUX | Engine uses unicode support and adding the appropriate global definitions like -DUNICODE for Linux. |
| char     | OFF        | LINUX | Engine doesn't use unicode. You have only char strings. |

DEFAULT VALUE: If flag is not specified the cmake will use -DKOTEK_UNICODE=ON. So by default cmake generating solution with unicode.

* -DKOTEK_SDK=STATUS
With this command you specify that project use SDK (Toolkit as level editor and etc) or not.

| DKOTEK_SDK=STATUS | Explanation |
| ----------- | ----------- |
| ON | Engine uses sdk. So when you compile the project you will have sdk in project. |
| OFF | Engine doesn't use sdk. So when you compile the project you can't have sdk at all. |

DEFAULT VALUE: If flag is not specified the cmake will use -DKOTEK_SDK=ON. So by default cmake generating solution with SDK.

* -DKOTEK_CPU_PROFILER=STATUS
With this command you can enable or to not use profiler for CPU.

| DKOTEK_CPU_PROFILER=STATUS | Explanation |
| ----------- | ----------- |
| ON | Engine uses profiler for CPU. The results of CPU profiling you will get in user_data folder. |
| OFF | Engine doesn't use profiler for CPU. The results of CPU profiling will not be generated. |

DEFAULT VALUE: If flag is not specified the cmake will use -DKOTEK_CPU_PROFILER=ON. So by default cmake generating solution with CPU profiler.

* -DKOTEK_GPU_PROFILER=STATUS
With this command you can enable or to not use profiler for CPU. But this command depends on CPU_PROFILER flag, so it means if you set CPU_PROFILER=OFF the GPU profiler won't be added! Keep in mind this fact.

| DKOTEK_GPU_PROFILER=STATUS | Explanation |
| ----------- | ----------- |
| ON | Engine uses profiler for GPU. The results of GPU profiling you will get in user_data folder. |
| OFF | Engine doesn't use profiler for GPU. The results of GPU profiling will not be generated. |

DEFAULT VALUE: If flag is not specified the cmake will use -DKOTEK_GPU_PROFILER=ON. So by default cmake generating solution with GPU profiler.

* -DKOTEK_MATH_LIBRARY=STATUS
With this command you choose your base math library, by default it's GLM.

ATTENTION: This feature doesn't support now

| DKOTEK_MATH_LIBRARY=STATUS | Explanation |
| ----------- | ----------- |
| GLM | Engine uses [OpenGL Mathematics](https://github.com/g-truc/glm/releases) |
| DXM | Engine uses [DirectXMath](https://github.com/microsoft/DirectXMath/releases) |
| EIGEN | Engine uses [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page) |

DEFAULT VALUE: If flag is not specified the cmake will use -DKOTEK_MATH_LIBRARY=GLM. So by default cmake generating solution with GLM math library.

* -DKOTEK_MATH_PRECISION=STATUS
With this command you choose your base type for math library.

| DKOTEK_MATH_PRECISION=STATUS | Explanation |
| ----------- | ----------- |
| FLOAT | Engine uses float type based types of current math library |
| DOUBLE | Engine uses double type based types of current math library |

DEFAULT VALUE: If flag is not specified the cmake will use -DKOTEK_MATH_PRECISION=FLOAT. So by default cmake generating solution with float base type in math library.

* -DKOTEK_USER_DEPS_ENGINE=STATUS
With this command you choose your deps folder location. But you need to create dependency folder in kotek-engine folder, so like where original deps folder is located.

ATTENTION: This feature doesn't support now

| DKOTEK_USER_DEPS_ENGINE=STATUS | Explanation |
| ----------- | ----------- |
| YOUR_FOLDER_NAME | Engine uses your folder name. WARNING! You must not to specify the path of folder you need to write your name of folder! |

DEFAULT VALUE: there's no default value, but if you specify this flag cmake will search packages in that folder that you place in root of your repository.

* -DKOTEK_USER_DEPS_GAME=STATUS
With this command you choose your deps folder location. But you need to create dependency folder in your game-repo folder, so like where original deps folder is located.

ATTENTION: This feature doesn't support now

| DKOTEK_USER_DEPS_GAME=STATUS | Explanation |
| ----------- | ----------- |
| YOUR_FOLDER_NAME | Game uses your folder name. WARNING! You must not to specify the path of folder you need to write your name of folder! |

DEFAULT VALUE: there's no default value, but if you specify this flag cmake will search packages in that folder that you place in root of your repository (it's not the root folder of kotek-engine).

* -DKOTEK_TESTS=STATUS
With this command you can enable or to not use tests.

| DKOTEK_TESTS=STATUS | Explanation |
| ----------- | ----------- |
| ON | Engine uses tests |
| OFF | Engine doesn't use tests |

DEFAULT VALUE: If flag is not specified the cmake will use -DKOTEK_TESTS=ON. So by default cmake generating solution with tests. But you need to read the next flag in order to understand the difference between two status for flag DKOTEK_TESTS_RUNTIME.

* -DKOTEK_TESTS_RUNTIME=STATUS
With this command you can enable or to not use tests like they integrated in project what we test and all tests run when you start your game otherwise cmake generating separated projects for testing.

| DKOTEK_TESTS_RUNTIME=STATUS | Explanation |
| ----------- | ----------- |
| ON | Engine uses files and integrates them into project what we want to test. All tests run when you run the project. |
| OFF | Engine creates separated projects for testing |

DEFAULT VALUE: If flag is not specified the cmake will use -DKOTEK_TESTS_RUNTIME=ON. So by default cmake generating solution with runtime tests.