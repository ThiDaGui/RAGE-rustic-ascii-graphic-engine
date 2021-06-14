# RAGE Rustic Ascii Graphic Engine

## To Compile

Inside the root directory run CMake:

```
~$ cmake .
```

After this you need to compile project using the generated Makefile as follows:

```
~$ make
```

That's it! If everything went right, you should see a lot of text, and RAGE should be compiled and ready to be executed!

## Running RAGE

After compilation, execute the generated `rage_app` file with the .obj file you desire to visualize.

```
~$ ./rage_app -f .models/suzanne.obj
```

Usage `--usage`:

```
Usage: rage_app [-?] [-f FILE] [--filename=FILE] [--fov=float] [--help] [--usage]
```

For a detailed description of the arguments use the argument `--help`.

```
~$ ./rage_app --help
Usage: rage_app [OPTION...] 
Convert an input .obj model into ASCII art.

  -f, --filename=FILE        Image to transform into ASCII
      --fov=float            Field of view of the camera
  -?, --help                 Give this help list
      --usage                Give a short usage message
```

## Site Web

Un site web contenant les derniers détails du projet et des liens de téléchargement est disponible à l'adresse suivante :

https://damien.didier.pages.epita.fr/rage-rustic-ascii-graphic-engine/
