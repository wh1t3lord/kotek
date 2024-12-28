# kotek

kotek framework is written in C++20 and using OpenGL ES (ANGLE backend) and Vulkan graphics API (DirectX is in plans for now). The whole purpose of a such framework for making crossplatform development and general developing for various systems easy and productive ready.

This project might be useful for those who doesn't want to spend time for making own architecture, how to design and literally waste a large time for that thing. For young (and not) scientists in computation/informatics field, especially for those who want to make some experiments fast and doesn't want to spend time for writting "core" part just for writting "business logic", you just take it and write own business logic and it doesn't matter you write your AI, Graphics or something else. 

## How to build

### PC (personal computer)

#### Windows

> You're required to have CMake 3.19.1 version at least

> Also you're required to have stable internet connection otherwise you need to use offline compilation


Steps to reproduce:

- git clone https://github.com/wh1t3lord/kotek.git
- mkdir build
- cd build
- cmake ..

#### Linux

> You're required to have CMake 3.19.1 version at least

> Also you're required to have stable internet connection otherwise you need to use offline compilation


Steps to reproduce:

- git clone https://github.com/wh1t3lord/kotek.git
- mkdir build
- cd build
- cmake ..

#### MacOS

> You're required to have CMake 3.19.1 version at least

> Also you're required to have stable internet connection otherwise you need to use offline compilation


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

And many other features. It will sound huge only when you understand the amount of code what was written ha-ha :slightly_smiling_face:. 

### Motivation

In 2021 I had an idea to make a universal engine like if you go to some gov. and say like I want to provide for the whole state a game engine that being standardized then it is interesting life quest. And it means you have to solve a lot of problems of course.

First of all, I noticed a tendency that modern toolsets, engines can't work with various platforms especially when they do some upgrades in terms of language, or language's standard (in case of C++) or updating libraries for engine and etc. By that mean standardized engine must be able to run under all possible platforms or at least provide ecosystem and approaches to compile for a such systems. It is really important feature like you are able to upgrade your "ecosystem" and easily maintain the possibility to run under older systems. In business world it is really useful, your product can out-live you and you like started from Windows XP and then 20 years later you can kill your product just because of "updating" your ecosystem but it wasn't even developed in mind for a such task thus you will loose your life product.

Secondly, it is really nice design for making a possibility to isolate business code from core part. In business code you can re-write it, you can send to outsource or hire a new dev team and it reduces time to develop the whole engine from scratch, like we made a game, we were young and naive and we did many wrong things in our business code, BUT the whole engine doesn't suffer, you just only need to re-write your part or whole business logic inside it (what defines your AI bot, your network interconnection, your optimizations and etc), I will explain in detail what is that "business logic" in kotek's architecture.

Thirdly, just test myself, my abilities and understand how I can be a professional in software development, it is really a nice thing to make a challenge life and go for broke. I hope that this work can be useful for anyone, for experienced professionals and for those who just begins their journey in software development world.

Fourthly, and probably one of the most important details of this framework, the ability to replace ANY implementation of any entity in the engine. From the physics engine to the class responsible for flags when processing commands from the application. IMO that's what supposed to do any standardize thing to provide to user an ability to make custom things OR replace any existed thing of ecosystem.

All in all, it can be used for serious needs (at some point you need to make a pull requests or at least to commit an issue) or for learning purposes.

### Supported Platforms 

#### Windows NT

| Windows XP    | Windows Vista | Windows 7 | Windows 8 | Windows 10 | Windows 11 |
| ------------- | ------------- |------------- |------------- |------------- |------------- |
| Not tested, see roadmap  | Not tested, see roadmap  | Not tested, see roadmap  | Not tested, see roadmap  | Supported  | Supported  |

#### Linux

#### Ubuntu

| Ubuntu 14.04 LTS | Ubuntu 16.04 LTS | Ubuntu 18.04 LTS | Ubuntu 20.04 LTS | Ubuntu 22.04 LTS | Ubuntu 24.04 LTS  |
| ------------- | ------------- |------------- |------------- |------------- |------------- |
| Not tested, see roadmap  | Not tested, see roadmap  | Not tested, see roadmap  | Not tested, see roadmap  | Supported  | Supported  |

#### MacOS

| Mac OS X 10.4 | OS X 10.8 | macOS 10.12 | macOS 10.15 | macOS 11 | macOS 15  |
| ------------- | ------------- |------------- |------------- |------------- |------------- |
| Not tested, see roadmap  | Not tested, see roadmap  | Not tested, see roadmap  | Not tested, see roadmap  | Not tested, see roadmap  | Not tested, see roadmap  |

#### Android

#### Nintendo Switch 

| Nintendo Switch SDK |  
| ------------- |  
| Not tested, see roadmap  |  

#### Playstation

For sane reasons, I want to support and test on modern Playstation systems, but community can provide plugins and implementations for supporting older Playstation versions.

| Playstation 1 | Playstation 2 | Playstation 3 | Playstation 4 | Playstation 5 | 
| ------------- | ------------- |------------- |------------- |------------- | 
| Expected community implementation  | Expected community implementation  | Not tested, see roadmap  | Not tested, see roadmap  | Not tested, see roadmap  |  

#### XBox

For sane reasons, I want to support and test on modern XBox systems, but community can provide plugins and implementations for supporting older XBox versions. 

| Xbox | Xbox 360 | Xbox One | Xbox Series S | Xbox Series X | 
| ------------- | ------------- |------------- |------------- |------------- | 
| Expected community implementation  | Expected community implementation  | Not tested, see roadmap  | Not tested, see roadmap  | Not tested, see roadmap  |  

### Supported Backends

#### Graphics

| DirectX 9 | DirectX 10 | DirectX 11 | DirectX 12 | OpenGL 3.3 | OpenGL ES 3.1  | Vulkan |
| ------------- | ------------- |------------- |------------- |------------- |------------- |------------- |
| Not implemented  | Not implemented  | Not implemented  | WIP (planned)  | Supported  | Supported  | WIP  | 

#### Animation

| OzzAnimation | Own Embedded implementation |
| ------------- |  ------------- | 
| WIP  |  Not implemented  | 

#### Physics

| Jolt | Bullet | NVIDIA PhysX | Own Embedded implemenetation
| ------------- |  ------------- |   ------------- |    ------------- | 
| WIP  |  Not implemented  |   Not implemented  |   Not implemented  |

#### Sound

| Miniaudio | FMOD | Wwise | Own Embedded implemenetation
| ------------- |  ------------- |   ------------- |    ------------- | 
| WIP  |  Not implemented  |   Not implemented  |   Not implemented  |

### Architecture design



## Development

### Roadmap

## License

I choose Apache 2.0 license to provide people the full freedom as much as possible. If a some person can patent the fork, the project or any other part of my work I would be really happy :=)  

## Community

I have my personal discord server for chatting, I welcome everyone. 

Just click on discord button.

## Alternative translation pages

- [Русский](documentation/git/ru/README.md)
- [Polska](documentation/git/pl/README.md)
- [Ελληνική](documentation/git/gr/README.md)