# kotek

kotek framework is written in C++20 and using OpenGL ES (ANGLE backend) and Vulkan graphics API (DirectX is in plans for now). The whole purpose of a such framework for making crossplatform development and general developing for various systems easy and productive ready.

This project might be useful for those who doesn't want to spend time for making own architecture, how to design and literally waste a large time for that thing. For young (and not) scientists in computation/informatics field, especially for those who want to make some experiments fast and doesn't want to spend time for writting "core" part just for writting "business logic", you just take it and write own business logic and it doesn't matter you write your AI, Graphics or something else. 

## How to build

### PC (personal computer)

#### Windows

> :warning: You're required to have CMake 3.19.1 version at least :warning:

> :warning: Also you're required to have stable internet connection otherwise you need to use offline compilation :warning:


Steps to reproduce:

- git clone https://github.com/wh1t3lord/kotek.git
- mkdir build
- cd build
- cmake ..

#### Linux

> :warning: You're required to have CMake 3.19.1 version at least :warning:

> :warning: Also you're required to have stable internet connection otherwise you need to use offline compilation :warning:


Steps to reproduce:

- git clone https://github.com/wh1t3lord/kotek.git
- mkdir build
- cd build
- cmake ..

#### MacOS

> :warning: You're required to have CMake 3.19.1 version at least :warning:

> :warning: Also you're required to have stable internet connection otherwise you need to use offline compilation :warning:


Steps to reproduce:

- git clone https://github.com/wh1t3lord/kotek.git
- mkdir build
- cd build
- cmake ..

### Phones

#### Android

#### IPhone

### Game consoles

#### Playstation

#### XBox

#### Nintendo Switch

## Features

- Absolutely modular design;
- CMake usage;
- Autogenerating namespaces;
- Rich Embedded library of containers/implementations and etc;
- Unit testing out of box;
- Making real for executing applications on older systems like Windows XP built with C++20 standard (MinGW compilation);
- Plugin system;
- Different built types;
- Ability to replace any existed thing in engine;
- No ANY Global variables in whole solution (Except for external libraries);

And many other features. 

### Motivation

In 2021 I had an idea to make a universal engine like if you go to some gov. and say like I want to provide for the whole state a game engine that being standardized then it is interesting life quest. And it means you have to solve a lot of problems of course.

First of all, I noticed a tendency that modern toolsets, engines can't work with various platforms especially when they do some upgrades in terms of language, or language's standard (in case of C++) or updating libraries for engine and etc. By that mean standardized engine must be able to run under all possible platforms or at least provide ecosystem and approaches to compile for a such systems. It is really important feature like you are able to upgrade your "ecosystem" and easily maintain the possibility to run under older systems. In business world it is really useful, your product can out-live you and you like started from Windows XP and then 20 years later you can kill your product just because of "updating" your ecosystem but it wasn't even developed in mind for a such task thus you will loose your life product.

Secondly, it is really nice design for making a possibility to isolate business code from core part. In business code you can re-write it, you can send to outsource or hire a new dev team and it reduces time to develop the whole engine from scratch, like we made a game, we were young and naive and we did many wrong things in our business code, BUT the whole engine doesn't suffer, you just only need to re-write your part or whole business logic inside it (what defines your AI bot, your network interconnection, your optimizations and etc), I will explain in detail what is that "business logic" in kotek's architecture.

Thirdly, just test myself, my abilities and understand how I can be a professional in software development, it is really a nice thing to make a challenge life and go for broke. I hope that this work can be useful for anyone, for experienced professionals and for those who just begins their journey in software development world.

Fourthly, and probably one of the most important details of this framework, the ability to replace ANY implementation of any entity in the engine. From the physics engine to the class responsible for flags when processing commands from the application. IMO that's what supposed to do any standardize thing to provide to user an ability to make custom things OR replace any existed thing of ecosystem.

All in all, it can be used for serious needs (at some point you need to make a pull requests or at least to commit an issue) or for learning purposes.

### Supported Platforms 

#### Windows NT

| Windows XP :x:    | Windows Vista :x: | Windows 7 :x: | Windows 8 :x: | Windows 10 :white_check_mark: | Windows 11 :white_check_mark: |
| ------------- | ------------- |------------- |------------- |------------- |------------- |
| Not tested (implemented), see roadmap  | Not tested (implemented), see roadmap  | Not tested (implemented), see roadmap  | Not tested (implemented), see roadmap  | Supported  | Supported  |

#### Linux

#### Ubuntu

| Ubuntu 14.04 LTS :x: | Ubuntu 16.04 LTS :x: | Ubuntu 18.04 LTS :x: | Ubuntu 20.04 LTS :x: | Ubuntu 22.04 LTS :warning: | Ubuntu 24.04 LTS :warning: |
| ------------- | ------------- |------------- |------------- |------------- |------------- |
| Not tested (implemented), see roadmap  | Not tested (implemented), see roadmap  | Not tested (implemented), see roadmap  | Not tested (implemented), see roadmap  | WIP  | WIP  |

#### MacOS

| Mac OS X 10.4 :x: | OS X 10.8 :x: | macOS 10.12 :x: | macOS 10.15 :x: | macOS 11 :x: | macOS 15 :x:  |
| ------------- | ------------- |------------- |------------- |------------- |------------- |
| Not tested (implemented), see roadmap  | Not tested (implemented), see roadmap  | Not tested (implemented), see roadmap  | Not tested (implemented), see roadmap  | Not tested (implemented), see roadmap  | Not tested (implemented), see roadmap  |

#### Android

#### Nintendo Switch 

| Nintendo Switch SDK :x: |  
| ------------- |  
| Not tested, see roadmap  |  

#### Playstation

For sane reasons, I want to support and test on modern Playstation systems, but community can provide plugins and implementations for supporting older Playstation versions.

| Playstation 1 :watch: | Playstation 2 :watch: | Playstation 3 :x: | Playstation 4 :x: | Playstation 5 :x: | 
| ------------- | ------------- |------------- |------------- |------------- | 
| Expected community implementation  | Expected community implementation  | Not tested (implemented), see roadmap  | Not tested (implemented), see roadmap  | Not tested (implemented), see roadmap  |  

#### XBox

For sane reasons, I want to support and test on modern XBox systems, but community can provide plugins and implementations for supporting older XBox versions. 

| Xbox :watch: | Xbox 360 :watch: | Xbox One :x: | Xbox Series S :x: | Xbox Series X :x: | 
| ------------- | ------------- |------------- |------------- |------------- | 
| Expected community implementation  | Expected community implementation  | Not tested (implemented), see roadmap  | Not tested (implemented), see roadmap  | Not tested (implemented), see roadmap  |  

### Supported Backends

#### Graphics

| DirectX 9 :x: | DirectX 10 :x: | DirectX 11 :x: | DirectX 12 :x: | OpenGL 3.3 :white_check_mark: | OpenGL ES 3.1 :white_check_mark:  | Vulkan :warning: |
| ------------- | ------------- |------------- |------------- |------------- |------------- |------------- |
| Not implemented  | Not implemented  | Not implemented  | Not implemented  | Supported  | Supported  | WIP  | 

#### Animation

| OzzAnimation :warning: | Own Embedded implementation :x: |
| ------------- |  ------------- | 
| WIP  |  Not implemented  | 

#### Physics

| Jolt :warning: | Bullet :x: | NVIDIA PhysX :x: | Own Embedded implemenetation :x:
| ------------- |  ------------- |   ------------- |    ------------- | 
| WIP  |  Not implemented  |   Not implemented  |   Not implemented  |

#### Sound

| Miniaudio :warning: | FMOD :x: | Wwise :x: | 
| ------------- |  ------------- |   ------------- | 
| WIP  |  Not implemented  |   Not implemented  |  

### Architecture design



## Development

### Roadmap

## License

I choose Apache 2.0 license to provide people the full freedom as much as possible. If a some person can patent the fork, the project or any other part of my work I would be really happy :=)  

## Community

I have my personal discord server for chatting, I welcome everyone. 

Just click on discord button.

## Alternative translation pages

- [Русский](doc/git/ru/README.md)
- [Polska](doc/git/pl/README.md)
- [Ελληνική](doc/git/gr/README.md)