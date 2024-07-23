# LkSrc

LkSrc (or LkSource) is a framework created by **Lk1** with the objective of enhancing your studies in game development.

> **Note:** LkSrc is still in development.

## How to Install

First, you need to install the following packages: **SDL2**, **SDL_Image**, **SDL_Mixer**, and **SDL_TTF**:

### Windows

You can find a zipped file named **SDL2.rar** in the path **lksrc/cmake/sdl2**. Extract it to **C:/** or any other location of your preference.
> This zipped file contains the SDL library with SDL_Image, SDL_Mixer, and SDL_TTF .lib and include files.
You can use **Visual Studio Community** for Windows and open the CMake with it.

> **Note:** Check the CMake logs in the Terminal if the paths are not empty:
> - **SDL2_INCLUDE_DIRS**
> - **SDL2_TTF_INCLUDE_DIRS**
> - **SDL2_IMAGE_INCLUDE_DIRS**
> - **SDL2_MIXER_INCLUDE_DIRS**
> - **SDL2_LIBRARIES**
> - **SDL2_TTF_LIBRARIES**
> - **SDL2_IMAGE_LIBRARIES**
> - **SDL2_MIXER_LIBRARIES**

### Linux

#### Debian/Ubuntu-based Systems

- **SDL2**
  > sudo apt install libsdl2-dev
- **SDL2_Image**
  > sudo apt install libsdl2-image-dev
- **SDL2_Mixer**
  > sudo apt install libsdl2-mixer-dev
- **SDL2_TTF**
  > sudo apt install libsdl2-ttf-dev

Once installed, navigate to your cloned folder and follow these steps:
```shell
mkdir build
cd build
cmake ..
make
