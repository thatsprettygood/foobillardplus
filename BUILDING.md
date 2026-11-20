# Building FooBillard++ with CMake

CMake 3.16 or newer and a C compiler are required. The build also needs SDL2,
OpenGL (including GLU), libpng, and FreeType. SDL2_net is required when network
support is enabled, and SDL2_mixer is required when sound support is enabled.
On Debian/Ubuntu, the development packages are typically named `libsdl2-dev`,
`libsdl2-net-dev`, `libsdl2-mixer-dev`, `libgl-dev`, `libglu1-mesa-dev`,
`libpng-dev`, `libfreetype-dev`, `pkg-config`, and `cmake`.

Configure and build from the repository root:

```sh
cmake -S . -B build
cmake --build build
```

To install, optionally set a prefix (the default is CMake's normal
`/usr/local`):

```sh
cmake -S . -B build -DCMAKE_INSTALL_PREFIX=/usr/local
cmake --build build
cmake --install build
```

The executable is installed under `bin` and game assets under `data` within the
install prefix. This matches the game's data-directory lookup. Use
`-DCMAKE_INSTALL_PREFIX=/usr/games/foobillardplus` if you want to keep the
traditional non-Debian layout.

Available options (all are CMake `-DNAME=ON|OFF` options):

- `FOOBILLARDPLUS_MATH_SINGLE` (default `ON`): use single-precision vector math.
- `FOOBILLARDPLUS_NETWORK` (default `ON`): include network play; requires SDL2_net.
- `FOOBILLARDPLUS_SOUND` (default `ON`): include sound/music; requires SDL2_mixer.
- `FOOBILLARDPLUS_TOUCH` (default `OFF`): enable generic touch-device support.
- `FOOBILLARDPLUS_WETAB` (default `OFF`): enable WeTab-specific support and touch.
- `FOOBILLARDPLUS_SSE` (default `OFF`): enable x86 SSE intrinsics and single precision.
- `FOOBILLARDPLUS_FAST_MATH` (default `OFF`): use approximate fast-math routines.
- `FOOBILLARDPLUS_NVIDIA` (default `OFF`): enable NVIDIA-specific extensions.

For example, build without optional network and audio dependencies:

```sh
cmake -S . -B build -DFOOBILLARDPLUS_NETWORK=OFF -DFOOBILLARDPLUS_SOUND=OFF
cmake --build build
```
