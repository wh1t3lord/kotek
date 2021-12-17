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
- mkdir build (or create manually through File Explorer)
- cd build
- cmake .. (but it's better to check Building section before writing this command)
- Build the project 
- Place all appropriate wxWidget's dlls into output bin folder (repo/build/bin/CMAKE_BUILD_TYPE/)
- Run the project

# Project overview

- Использует С++20 как основной стандарт, движок не предназначен для отката на старые стандарты (то есть ниже 20), то есть это первоночальный стандарт который движок обязан поддерживать независимо от каких-либо условий, если выйдет С++30 (если данный стандарт не имеет break-changes), то в таком случае С++20 это стандартный стандарт который будет работать.
- Движок не стремиться иметь хоть какое-либо legacy, то есть мы постоянно обновляем движок и всего соответствующие компоненты, а сам код мы только расширяем, но ничего не меняем, либо меняем только приватные части, чтобы не возникало break-changes или legacy как такового.
- Монолитно-модульная система
- Основная библиотека типов основана на stl и ей подобных библиотеках (к примеру Boost)
- Иметь возможность смены каких-либо компонент, к примеру математическую библиотеку заменить на Eigen или glm или DirectX и т.п.
- Две экосистемы, одна для игры, другая для движка
- Поддерживает пока что Windows

# Why do you write it?

- Основные идеи для написания движка были три
	- Это создание собственной игры
	- Это предоставление такого движка, который можно было использовать в коммерции и не задумываться над используемыми библиотеками. То есть в целом идея в том, что можно было конструировать содержимое движка и на каких библиотеках он будет основываться. То есть свой конструктор движка по сути, если так можно сказать вообще.
	- Данная идея была вызвана тем, что кому-то захочется перенести или восстановить какие-то очень устаревшие игры, но при этом описывать и задумываться над написанием своего движка особо не хочется, особенно когда есть такое огромное количество готовых библиотек, что смотря на всё это хочется взять и объединить их, поэтому движок имеет пустой шаблон или шаблон для 3д игр, где пользователь либо описывает свой игровой код (в том числе как именно будет работать ваш рендер) или пользователь уже имеет всё готовое и если его это всё устраивает то он использует это делает те вещи которые ему нужны. Но самое главное что с одной стороны это можно использовать в сфере разработки игры, но в тоже время это подспорье для тех, кто хочет делать свои научные работы где требуется визуализация и использование физики или искуственного интеллекта в таком случае как навигационный меш, может быть нейронные сети. То есть как это всё понимать, к примеру человеку хочется взять такой движок, где всё уже настроено, но нужно лишь описывать свой СДК, и при этом описать свой собственный рендер, но ему не надо задумываться над всеми оптимизациями и всего прочего это на уровне взял и сразу начал делать "бизнес-логику" или наоборот взять уже готовый шаблон и работать с ним.
	- Для портфолио (lol)

- ! Очень важно !

Я понимаю ваш прагматичный настрой по этому поводу, что есть все готовые движки и мол зачем ты всё это делал, но здесь смысл был в том, чтобы сделать такой open-source движок, который имел строго одну эко-систему в виде одного языка С++, и при этом его легко можно было использовать, к тому же имел вот именно такое представление которое у него есть. Поэтому всё что здесь реализовано это усилие одного человека, как и многих других людей которые непосредственно делают правки в движок и те люди которые сделали свои open-source библиотеки, которые движок использует. То есть по сути движок для программистов, но и для пользователей тоже, потому что существуют готовые шаблоны. То есть в идеале, что имелось в виду, всё сообщество может создавать вокруг этого движка свои проекты, которые могут реализовывать тот или иной функционал или запускать те или иные игры, не зря было сказано что здесь выделяется две эко-системы. Одна для движка, другая для игры. И именно часть про игру, и будет являться таким вот шаблоном, что если оно используется в open-source, то любой желающий может выкачать это содержимое и начать над этим работать или использовать. Соответственно мы формируем таким образом репозитории движков, а вернее часть игрового кода, который описывает ту или иную игру, либо это готовые шаблоны которые созданы для программистов, чтобы могли сразу над этим работать и выстраивать свой игровой код таким образом, чтобы получалась их игра. 

Но самое важное сделать проект, который сможет пережить самого автора.

Самое главное, что добивается движок это использование в коммерции соответственно вы можете также не открывать свой игровой код, либо использовать свою собственную версию движокого кода, но в таком случае вы отказываете от парадигмы "не иметь break-changes". То есть авторы в таком случае не несут ответственности и не имеют никакого интереса, если вдруг вы создали сами у себя состояние которое будет порождать тот самый "break-changes".

И конечно смысл в том, чтобы движок имел возможность всегда поддерживаться, соответственно в данном случае будет выступать сообщество и те ответственные люди, которые смогут принимать pull requests.

В каком-то архитектурном роде мы добиваемся состояние state-of-art, в том плане, что теперь можно интерпретировать всю архитектуру на другие языки, ибо вы сторого имеете представление о системе.

И какой ещё есть плюс. По нашему стандарту движок имеет способность только обновляться или возвращаться к C++20 только. Но если вдруг каким-то людям, нужно иметь движок который способен компилироваться под С++03 или ещё более ранние стандарты, то сообщество в таком случае (но кто-то один конечно) создает репозиторий и ведет свою работу по downgrade, но здесь очень важно чтобы люди не делали лишннюю работу, когда уже оно есть и стоит подключиться к существущему проекту нежели делать какие-то разные версии движков которые ставят перед собой задачу чтобы компилироваться под С++03, но здесь будут trusted репозитории где мы показываем коммьюнити где можно найти те или иные шаблоны, игры, и движки, то есть это такие репозитории которые получили хорошие отзовы от пользователей и имеют наибольший спрос и популярность. Поэтому авторам стоит связываться с нами по различным контактам, которые мы имеем (есть специальный раздел).

# Building

This project is based on cmake version 3.19.3 and for generating solution you need to understand the following commands before write "cmake -DCMAKE_BUILD_TYPE=YOUR_BUILD_TYPE .."

It's really important! You must write -DCMAKE_BUILD_TYPE=... without it the cmake can't generate the solution properly.

What will it be if you just write "cmake -DCMAKE_BUILD_TYPE=YOUR_BUILD_TYPE .."?

All other flags will be set ON or any other parameter that somehow specifies it.

Defaults if you don't specify them

| Flag | Value |
| ----------- | ----------- |
| -DKOTEK_UNICODE | ON |
| -DKOTEK_SDK | ON |
| -DKOTEK_CPU_PROFILER | ON |
| -DKOTEK_GPU_PROFILER | ON |
| -DKOTEK_MATH_LIBRARY | GLM |
| -DKOTEK_MATH_PRECISION | FLOAT |
| -DKOTEK_USER_DEPS_ENGINE | nothing |
| -DKOTEK_USER_DEPS_GAME | nothing |
| -DKOTEK_TESTS | ON |
| -DKOTEK_TESTS_RUNTIME | ON |


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

# Boost vs STD

Конечно справедливо спросить, что если движок может использовать различные компоненты, то какие есть альтернативы стд? Есть ли здесь заменяемость компонент? Мы считаем, что лучше всего поддерживать только две библиотеки это то что предоставляет стд и то что предоставляет буст. Почему? Потому что бессмысленно иметь 1000 различных проектов, которые пытаются конкрурировать с такими мастодонтами как стд и буст, это просто бессмысленно и не имеет ни какого смысла. Сейчас буст иметь больше возможностей чем стд, однако мы полагаем что в скором времени использование стд полностью покроет буст, таким образом, мы считаем что буст может слиться с стд в одно целое. То есть по факту все основные контейнеры и возможные реализации будут основаны на стд, однако мы поддерживаем буст тоже, если стд сможет полностью заменить буст, то мы удалим буст. 

# Dependencies (already "offline" installed)

Offline installed libraries are libraries that install with command "cmake --install . --config YOUR_CMAKE_BUILD_TYPE".
It means we support only those plaforms that we develop on. 

Manually installed means that dependency was manually downloaded and was built and was installed with CMake. So if you want to have your own versions of dependencies that are built with different macros or compilers you need to make it on your own, because these dependencies are built and installed only for Windows development.

So if you see no in the field "manually installed" it means it's a header only dependency.

You need to remember that we don't change any source code of dependency that we use. It's really important, because some projects require the statement to not change the source code of project that you use.

| Dependency name | Version | Manually installed |
| ----------- | ----------- | ----------- |
| Boost | 1.77 | Yes |
| Bullet | 3.17 | Yes |
| CMake | 3.19.3 | By User on your local machine |
| DirectXMath | 3.16 | No |
| Eigen | 3.4.0 | No |
| FMT | 8.0.1 | Yes |
| glfw3 | 3.3.5 | Yes |
| glm | 0.9.9.8 | No |
| imgui | 1.85 (No docking) | No |
| KTX-Software | 4.0.0 | Yes |
| mimalloc | 1.7 | Yes |
| Tracy | 0.7.8 | No |
| shaderc | 1.5.5 | Yes |
| SPIRV-Reflect | Not stated | No |
| oneTBB | 2021.6.0 | Yes |
| Visual Leak Detector | 2.5.1 | No (Windows only) |
| wxWidgets | 3.1.5  | Yes |

# License status 

Необходимо понимать что лицензирование текущего проекта при обновлении его же зависимостей может повлечь к состоянию когда текущая лицензия этого проекта будет несовместимой с новой лицензией какой-либо зависимости. Поэтому здесь приводится список всех лицензий всех зависимостей, и текущая лицензия которая используется

Project's license is Apache 2.0

ATTENTION: We appreciate your help in case when you show us where we're wrong and have incompatibale license with what we have

| Dependency's name | License | Compatibility with project's license | Explanation | 
| ----------- | ----------- | ----------- | ----------- |
| Boost | Boost Software license - Version 1.0 | Yes |  |
| Bullet | Zlib license | Yes |  |
| DirectXMath | MIT license | Yes |  |
| Eigen | MPL 2.0 license | Yes |  |
| FMT | MIT license | Yes | Yes |
| glfw3 | Zlib license | Yes |  |
| glm | MIT license | Yes |  |
| imgui | MIT license | Yes |  |
| KTX-Software | Apache-2.0 license | The same as project's license |  |
| mimalloc | MIT license | Yes | Yes |
| Tracy | 3-clause BSD license | Yes |  |
| shaderc | Apache-2.0 license | The same as project's license |  |
| SPIRV-Reflect | Apache-2.0 license | The same as project's license |  |
| oneTBB | Apache-2.0 license | The same as project's license |  |
| Visual Leak Detector | LGPL-2.1 license | Yes | We don't change the code and use only library for linking only and use dll file for 'working with library' |
| wxWidgets | wxWidgets license  | Yes | We don't alter the source code of WxWidgets library and use only for linking their pre-build static and dynamic libraries. As the result user gets only dynamic libraries after building the project. |