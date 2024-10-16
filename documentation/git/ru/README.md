# Как использовать

0. Создайте папку и назовите её как хотите, потому что туда вы должны будете положить три папки. Одна для репозитория, другая для зависимостей и третья для сборки решения (используется CMake).
> mkdir kek
> cd kek

1. Клонируете репозиторий в папку.
> git clone https://gitlab.com/wh1t3lord/kotek.git

2. Переходите в проект (корневой каталог репозитория, где он у вас лежит). Как возможный вариант.
> cd C:/projects/kek/kotek

3. Далее переключаетесь на главную ветку (если у вас вдруг устаревшая ветка)
> git checkout main

4. Теперь вы можете устанавливать зависимости для сборки через vcpkg, или через любой другой пакетный менеджер или вы можете скачать уже скомпилированные зависимости для работы, список приведен здесь.

5. В корневом каталоге создаете папку где вам CMake сгенерирует решение. Как возможный вариант папку назвать build.
> mkdir build

6. Переходите в созданный каталог
> cd build

## Зависимости 

### Предустановленные 
7. Обращаетесь к CMake и генерируете решение. Очень важно, что вы должны указать тип сборки (Debug, Release, MinSizeRel, RelWithDebInfo). Предположим, что вы хотите сгенерировать решение для Debug сборки и при этом название папки где хранятся зависимости называется kotek-engine-deps-win32-vs19-full, тогда:
> cmake -DCMAKE_BUILD_TYPE=Debug -DKOTEK_DEPS_FOLDER="kotek-engine-deps-win32-vs19-full" ..

### vcpkg 
7.1 Примечание, вы можете использовать vcpkg вместо скачивания предустановленных библиотек из официальных репозиториев для этого вы ничего не должны делать а только указать тип сборки.

> git clone https://github.com/microsoft/vcpkg

Необходимо заменить исходные triplets на triplets из пути documentation/git/vcpkg/triplets потому что по умолчанию vcpkg может собрать некоторые зависимости при самой старой visual studio. Это стоит учитывать при работе с vcpkg.

> .\vcpkg\bootstrap-vcpkg.bat

или если линух, мак

> ./vcpkg/bootstrap-vcpkg.sh

Список команд для vcpkg если хотите full для 

#### Windows
```
.\vcpkg\vcpkg install boost:x64-windows
.\vcpkg\vcpkg install bullet3:x64-windows
.\vcpkg\vcpkg install directxmath:x64-windows
.\vcpkg\vcpkg install eigen3:x64-windows
.\vcpkg\vcpkg install glfw3:x64-windows
.\vcpkg\vcpkg install glm:x64-windows
.\vcpkg\vcpkg install ktx:x64-windows
.\vcpkg\vcpkg install mimalloc:x64-windows
.\vcpkg\vcpkg install tracy:x64-windows
.\vcpkg\vcpkg install shaderc:x64-windows
.\vcpkg\vcpkg install spirv-reflect:x64-windows
.\vcpkg\vcpkg install tbb:x64-windows
.\vcpkg\vcpkg install wxwidgets:x64-windows
.\vcpkg\vcpkg install angle:x64-windows
.\vcpkg\vcpkg install assimp:x64-windows
.\vcpkg\vcpkg install cgltf:x64-windows
.\vcpkg\vcpkg install rmlui[freetype]:x64-windows

# You can add it, but last time it couldn't build successful
# .\vcpkg\vcpkg install usd:x64-windows

.\vcpkg\vcpkg.exe install entt:x64-windows
.\vcpkg\vcpkg.exe install etl:x64-windows
.\vcpkg\vcpkg.exe install dav1d:x64-windows
.\vcpkg\vcpkg.exe install spdlog:x64-windows
.\vcpkg\vcpkg.exe install utfcpp:x64-windows

# for shared configuration
.\vcpkg\vcpkg install boost:x64-windows bullet3:x64-windows directxmath:x64-windows glfw3:x64-windows eigen3:x64-windows glm:x64-windows ktx:x64-windows mimalloc:x64-windows tracy:x64-windows shaderc:x64-windows spirv-reflect:x64-windows tbb:x64-windows wxwidgets:x64-windows wxwidgets:x64-windows angle:x64-windows assimp:x64-windows cgltf:x64-windows rmlui[freetype]:x64-windows entt:x64-windows

# for static
.\vcpkg\vcpkg install boost:x64-windows-static-md bullet3:x64-windows-static-md directxmath:x64-windows-static-md glfw3:x64-windows-static-md eigen3:x64-windows-static-md glm:x64-windows-static-md ktx:x64-windows-static-md mimalloc:x64-windows-static-md tracy:x64-windows-static-md shaderc:x64-windows-static-md spirv-reflect:x64-windows-static-md tbb:x64-windows-static-md wxwidgets:x64-windows-static-md wxwidgets:x64-windows-static-md angle:x64-windows-static-md assimp:x64-windows-static-md cgltf:x64-windows-static-md rmlui[freetype]:x64-windows-static-md entt:x64-windows-static-md
```

Если вы устанавливали пакеты с помощью x64-windows то нужна такая команда:

> cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=./kotek/vcpkg/scripts/buildsystems/vcpkg.cmake ..

Иначе если использовали x64-windows-static-md:

> cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE="./kotek/vcpkg/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows-static-md ..

#### Others

```

# Linux

./vcpkg/vcpkg install boost:x64-linux
./vcpkg/vcpkg install bullet3:x64-linux
./vcpkg/vcpkg install directxmath:x64-linux
./vcpkg/vcpkg install eigen3:x64-linux
./vcpkg/vcpkg install glfw3:x64-linux
./vcpkg/vcpkg install glm:x64-linux
./vcpkg/vcpkg install ktx:x64-linux
./vcpkg/vcpkg install mimalloc:x64-linux
./vcpkg/vcpkg install tracy:x64-linux
./vcpkg/vcpkg install shaderc:x64-linux
./vcpkg/vcpkg install spirv-reflect:x64-linux
./vcpkg/vcpkg install tbb:x64-linux
./vcpkg/vcpkg install wxwidgets:x64-linux
./vcpkg/vcpkg install angle:x64-linux
./vcpkg/vcpkg install assimp:x64-linux
./vcpkg/vcpkg install cgltf:x64-linux
./vcpkg/vcpkg install rmlui[freetype]:x64-linux

# You can add it, but last time it couldn't build successful
# ./vcpkg/vcpkg install usd:x64-linux

./vcpkg/vcpkg install entt:x64-linux
./vcpkg/vcpkg install fmt:x64-linux
./vcpkg/vcpkg install etl:x64-linux

## If you want to build for Windows XP

You need to install mingw for appropriate architecture

./vcpkg/vcpkg install boost:x64-mingw-dynamic
./vcpkg/vcpkg install bullet3:x64-mingw-dynamic
./vcpkg/vcpkg install directxmath:x64-mingw-dynamic
./vcpkg/vcpkg install eigen3:x64-mingw-dynamic
./vcpkg/vcpkg install glfw3:x64-mingw-dynamic
./vcpkg/vcpkg install glm:x64-mingw-dynamic
./vcpkg/vcpkg install ktx:x64-mingw-dynamic
./vcpkg/vcpkg install mimalloc:x64-mingw-dynamic
./vcpkg/vcpkg install tracy:x64-mingw-dynamic
./vcpkg/vcpkg install shaderc:x64-mingw-dynamic
./vcpkg/vcpkg install spirv-reflect:x64-mingw-dynamic
./vcpkg/vcpkg install tbb:x64-mingw-dynamic
./vcpkg/vcpkg install wxwidgets:x64-mingw-dynamic
./vcpkg/vcpkg install angle:x64-mingw-dynamic
./vcpkg/vcpkg install assimp:x64-mingw-dynamic
./vcpkg/vcpkg install cgltf:x64-mingw-dynamic
./vcpkg/vcpkg install rmlui[freetype]:x64-mingw-dynamic

# You can add it, but last time it couldn't build successful
# ./vcpkg/vcpkg install usd:x64-mingw-dynamic

./vcpkg/vcpkg install entt:x64-mingw-dynamic

# Mac


# TODO: add other dependencies, sdl2, miniaudio, fmod, physx, 
```


Сейчас vcpkg имеет некоторые нестабильные зависимости это:

- shaderc, оно при генерации решения добавляет не действительный путь до SPIRV-Tools.lib из-за чего вам надо добавлять вручную или удалять лишнее поле. Проблема [здесь](https://github.com/microsoft/vcpkg/issues/28144) (исправлено)
- mimalloc, оно просто не корректно собирает решение, требуется версия с override но vcpkg не собирает, проблема адресована [здесь](https://github.com/microsoft/vcpkg/pull/25069)

Поэтому предлагается такая команда:

P.S. стоит учитывать что это временное решение, ибо данные проблемы должны быть решены...

> cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_TOOLCHAIN_FILE=./kotek/vcpkg/scripts/buildsystems/vcpkg.cmake -DKOTEK_MEMORY_ALLOCATOR_CPU=OFF -DKOTEK_STARTUP_RENDERER=OpenGLES_SpecifiedByUser -DKOTEK_STARTUP_RENDERER_VERSION=OpenGLES_3_1 ..

7.2 Примечание, на текущий момент времени conan не поддерживается, однако планируется для добавления

8. Теперь вы должны иметь сгенерированное решение. На этом все!

## Краткий обзор проекта

Лучше обратиться к документации для полного представления о проекте.

Если сформулировать кратко суть проекта, то он был создан для:

- Упрощенной разработки при портировании старых игр;
- Упрощенной разработки своего движка;
- Упрощенной разработки любого другого приложения, которому требуется использование графического API.

При этом должны быть удовлетворены следующие требования при такой разработке:

- Не иметь легаси;
- Модульность;
- Производительность;
- Простота;
- Смена "движка" не ломая совместимость с пользовательской частью;
- Система плагинов для добавления новых возможностей со стороны пользователей, а также поддержка движка в условиях когда сам движок не поддерживается.

## Заметки

### Команды для CMake

#### Смена типа разработки

Предположим, что вам захотелось иметь один "экзешник" в котором просто всё, вам не надо иметь игру которая представлена в виде отдельного dll/so/etc (см. документацию о разделе архитектуры). Тогда обращаемся к следующим параметрам, которые мы должны указать:

- KOTEK_DEVELOPMENT_TYPE 

Данный параметр принимает либо SHARED (по умолчанию), либо STATIC, в нашем случае мы пишем так

> -DKOTEK_DEVELOPMENT_TYPE=STATIC

##### Если у нас KOTEK_DEVELOPMENT_TYPE=STATIC

Далее, требуется указать следующие параметры:

- KOTEK_USER_GAME_PROJECT_NAME

Здесь мы указываем наименование папки, корневого каталога (см. раздел документации о стандарте разработки), а также смотрите пример в [zircon](https://gitlab.com/wh1t3lord/zircon).

На примере zircon мы пишем название папки такое

> -DKOTEK_USER_GAME_PROJECT_NAME=zircon

- KOTEK_USER_GAME_MODULE_FOR_LINK_NAME

Здесь мы также указываем уже наименование проекта которые нужно линковать к kotek.game проекту. 

На примере zircon будет так

> -DKOTEK_USER_GAME_MODULE_FOR_LINK_NAME="zircon.game"

- KOTEK_GAME_MODULE_FUNCTIONS_FILE

Здесь мы указываем путь до файла который содержит стандартные функции при обращении к модулю (см. документацию о стандарте разработке для пользователя).

На примере zircon будет

> -DKOTEK_GAME_MODULE_FUNCTIONS_FILE="<game/zircon_game.h>"

Таким образом, конечная команда для генерации решения для статической разработки то получаем следующее:

На примере zircon

> cmake -DCMAKE_BUILD_TYPE=Debug -DKOTEK_DEPS_FOLDER="kotek-engine-deps-win32-vs19-full" -DKOTEK_DEVELOPMENT_TYPE=STATIC -DKOTEK_USER_GAME_PROJECT_NAME=zircon -DKOTEK_USER_GAME_MODULE_FOR_LINK_NAME="zircon.game" -DKOTEK_GAME_MODULE_FUNCTIONS_FILE="<game/zircon_game.h>" ..

Если у вас свои функции для определения модуля, то вы должны определить наименования через соответствующие макросы:

- KOTEK_USER_FUNCTION_IMG

По умолчанию стоит параметр:

> -DKOTEK_USER_FUNCTION_IMG=InitializeModule_Game

- KOTEK_USER_FUNCTION_SMG

По умолчанию стоит параметр:

> -DKOTEK_USER_FUNCTION_SMG=ShutdownModule_Game

- KOTEK_USER_FUNCTION_UMG

По умолчанию стоит параметр:

> -DKOTEK_USER_FUNCTION_UMG=UpdateModule_Game

- KOTEK_USER_FUNCTION_IMR

По умолчанию стоит параметр:

> -DKOTEK_USER_FUNCTION_IMR=InitializeModule_Render

Чтобы сменить имя файла для сохранения пользовательских настрок то:

> -DKOTEK_USER_DATA_CONFIG_NAME=somenamehere

По умолчанию (если ничего не передавать при генерации в cmake) статические версии контейнеров для разработки встраиваемых систем используются по умолчанию (основываются на библиотеке etl), то есть такая опция включена.

> -DKOTEK_STD_LIBRARY_STATIC_CONTAINERS=ON/OFF

### Работа с проектами

- Не используйте файлы с форматом ".c" которые относятся строго к языку С, потому что cmake будет генерировать precompiled header files как для С++ так и для С из-за этого вы не сможете собрать свое решение успешно.
- Не скачивайте Chromium Embedded Framework скомпилированные версии (сборки), потому что они имеют флаг /MT или /MTd что не будет согласовываться с обычной генерацией cmake. Это обусловлено тем, что все решения генерируются по дефолту то есть "cmake ..", то есть если при такой записи на Windows NT генерируются типы сборок (Debug, Release, MinSizeRel, RelWithDebInfo) с флагами /MD; /MDd, то и получается что все зависимости должны быть собраны с такими же флагами. Поэтому собираете CEF (Chromium Embedded Framework) своими руками. И это связано ещё с тем, что все остальные зависимости которые лежат в репозиториях зависимостей они собраны вручную то есть cmake .. и у них при сборке флаги были /MD (/MDd).
- Пользователь должен сам включать расширения для GL,EGL,VK. Ибо стандартизировать это невозможно. Поэтому glad'ы были сгененированы без расширений.
- Описывать GLES2 или GLES3 можно разделяя пассы которые будут использовать функции только для GLES2 и пассы которые уже основаны на GLES3. 

### Документация 

Для того чтобы сгенерировать документацию о проекте вы должны воспользоваться инструментом doxygen. На примере мы воспользуемся GUI инструментом doxygen называется DoxyWizard. С помощью него сгенерируем документацию проекта, она будет располагаться в корневом каталоге репозитория kotek по пути kotek/documentation/, то есть находится в папке documentation.



### Список зависимостей

- [Кликните на надпись чтобы перейти в раздел](dependencies.md)
