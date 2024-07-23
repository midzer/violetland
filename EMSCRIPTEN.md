# Emscripten

## Build

```
mkdir build
cd build
emcmake cmake -DDATA_INSTALL_DIR=./ ..
emmake make
```

## Link

```
em++ -flto -O3 libGL.a *.o */*.o */*/*.o */*/*/*.o -o index.html -sUSE_SDL=2 -sUSE_SDL_IMAGE=2 -sSDL2_IMAGE_FORMATS=png -sUSE_SDL_MIXER=2 -sSDL2_MIXER_FORMATS=ogg -sUSE_SDL_TTF=2 -sUSE_BOOST_HEADERS=1 -lGL -sFULL_ES2 -sASYNCIFY -sASYNCIFY_IGNORE_INDIRECT -sASYNCIFY_ONLY=@../../../../funcs.txt -sENVIRONMENT=web --preload-file ../../../../fonts/@fonts/ --preload-file ../../../../images/@images/ --preload-file ../../../../monsters/@monsters/ --preload-file ../../../../music/@music/ --preload-file ../../../../sounds/@sounds/ --preload-file ../../../../weapon/@weapon/ --preload-file ../../../../icon-light.png@icon-light.png -Wl,-u,fileno --closure 1
```
