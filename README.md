# 🐈 kotek

Kotek Engine is a modern, extensible C++ framework designed to facilitate the creation of games and interactive applications. It emphasizes modularity, cross-platform compatibility, and ease of use, making it suitable for both rapid prototyping and production-ready projects.

## 🎯 Who Is This For?

- **Students & Researchers**\
  Run experiments in graphics or AI without wrestling with engine plumbing.

- **Indie & Professional Teams**\
  Prototype fast, maintain long‑term stability, and avoid platform lock‑in.

- **Anyone Tired of “Hello, World” Engines**\
  Start with production‑grade quality out of the box.

## 🚀 Getting Started

### CMake

> :warning: CMake 3.19.1 version is required :warning:

- git clone https://github.com/wh1t3lord/kotek.git
- mkdir build
- cd build
- cmake ..

## ✨ Features

1.	**Modular Design and Project Separation**
>	Each component (core, API, casting, filesystem, resource manager, input, rendering, UI, etc.) is organized into its own project. This promotes independent development, testing, and maintenance.

2.	**Abstraction via Interfaces**
>	Many subsystems are defined by abstract interfaces. These interfaces encapsulate the implementation details, allowing for multiple implementations (such as different renderer backends for OpenGL, Vulkan, DirectX, or even software solutions).

3.	**Dependency Injection and Central Coordination**
>	The ktkMainManager serves as the central hub that manages various components. It aggregates pointers to components (like filesystem, input, resource, rendering, UI, etc.) and injects these dependencies into modules that need them. This setup makes it easy to swap, extend, or override parts of the engine as needed.

4.	**Extensibility and Multi-Renderer Support**
>	The rendering subsystem (described in kotek_render.h) provides functions to initialize and shut down the render module.	It supports multiple graphics APIs. The engine can be configured (at startup or via configuration files/command-line arguments) to use OpenGL, Vulkan, DirectX, or even fallback to less modern renderers. The design even anticipates fallback mechanisms, selecting renderer versions if the user-specified one fails to initialize.

5.	**Cross-Platform and Modern C++ Practices**
> The engine is implemented using C++20, taking advantage of modern language features for safety, performance, and clarity.	Preprocessor macros and namespaces help abstract platform-specific behavior (e.g., filesystem handling, window management).

6. **Plugin System**
> Easily extend or override engine features via plugins. Due to interfaces user can provide own outside of framework libraries in order to override current implementations of framework.

The architecture is designed for robustness, flexibility, and ease of extension. It keeps the system decoupled, making it easier to maintain, swap out components, and add new features—qualities that are valuable for both production-level game engines and evolving projects.


## 📑 Documentation

- [User Guide](docs/user_guide.md)
- [FAQ](docs/faq.md)

## 🛠  Development

### Roadmap

#### 🌐 Status

| Platform         | Status            |
| ---------------- | ----------------- |
| Windows 10/11    | ✅                |
| Ubuntu 22.04     | ⚠️ WIP            |
| macOS            | ⚠️ WIP            |
| Android / iOS    | ⚠️ WIP           |
| Consoles (PS/XB) | ⚠️ WIP            |

| Graphics API  | Status  |
| ------------- | ------- |
| OpenGL ES 3.1 (ANGLE) | ✅      |
| Vulkan        | ⚠️ WIP  |
| DirectX 12    | ⚠️ WIP |
| DirectX 11    | ⚠️ WIP |
| DirectX 10    | ⚠️ WIP |
| DirectX 9     | ⚠️ WIP |


| Animation Backends | Status  |
| ------------- | ------- |
| OzzAnimation | ⚠️ WIP     |

| Physics Backends | Status  |
| ------------- | ------- |
| Jolt | ⚠️ WIP     |
| NVIDIA PhysX  | ⚠️ WIP  |

| Sound Backends | Status  |
| ------------- | ------- |
| Miniaudio | ⚠️ WIP     |

| UI Backends | Status  |
| ------------- | ------- |
| ImGui | ✅     |
| RmlUi | ⚠️ WIP  |

## 📄 License

I choose Apache 2.0 license to provide people the full freedom as much as possible. If a some person can patent the fork, the project or any other part of my work I would be really happy :=)  

## 🗣 Contact

- **Discord:** https://discord.gg/h89dyGQFnN
- **Twitter:** [@wh1t3lord](https://twitter.com/wh1t3lord)