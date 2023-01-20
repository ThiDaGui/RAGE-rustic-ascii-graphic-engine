# RAGE Rustic Ascii Graphic Engine

## Description

RAGE (Rustic Ascii Graphic Engine) is a 3D object visualizer in console written in C, using a fixed function pipeline inspired by the GPU pipeline. The project should be evolving in a full graphic engine in the near future.
RAGE support the wavefront .obj file format.

## Getting started

### Requirements

RAGE is being developped with linux in mind and has not been tested on other OSs.

To compile and run RAGE, you will need:
* A C99 compiler.
* The CMake build system.
* The nCurses library.

### Compile

Inside the root directory run CMake:

#### DEBUG MOD
```
~$ cmake -S . -B build -D CMAKE_BUILD_TYPE=Debug
```

#### RELEASE MOD
```
~$ cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
```

After this you need to compile project as follows:

```
cmake --build build/
```

That's it! If everything went right, you should see a lot of text, and RAGE should be compiled and ready to be executed!

### Running RAGE

After compilation, execute the generated `rage_app` (in `build/`) file with the .obj file you desire to visualize.

```
./build/rage_app -f .models/suzanne.obj
```

Usage `--usage`:

```
Usage: rage_app [-?] [-f FILE] [--filename=FILE] [--fov=float] [--help] [--usage]
```

For a detailed description of the arguments use the argument `--help`.

```
./rage_app --help
Usage: rage_app [OPTION...] 
Convert an input .obj model into ASCII art.

  -f, --filename=FILE        Image to transform into ASCII
      --fov=float            Field of view of the camera
  -?, --help                 Give this help list
      --usage                Give a short usage message
```
