[![CI test](https://github.com/zevlg/tgs2png/workflows/CI/badge.svg)](https://github.com/zevlg/tgs2png/actions)
[![AUR version](https://img.shields.io/aur/version/tgs2png-git)](https://aur.archlinux.org/packages/tgs2png-git)

# tgs2png

Convert Telegram's animated stickers in TGS format into series of PNG
images.

Requires:
* librlottie `$ apt install librlottie-dev`
* libpng `$ apt install libpng-dev`

# Building (*nix)

```console
$ mkdir build
$ cd build
$ cmake ..
$ make
# copy tgs2png somewhere into $PATH
```

# Building (Windows)

1. Install MSYS2
2. Run `MSYS2 MINGW64`
3. Run `pacman -Sy mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake mingw-w64-x86_64-libpng git`
4. git clone this repo
5. Run the following
```
cd tgs2png
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
mingw32-make
mkdir ../dist
cp tgs2png.exe ../dist
cp rlottie/librlottie.dll ../dist
cp /mingw64/bin/libpng*.dll ../dist
cp /mingw64/bin/libwinpthread*.dll ../dist
cp /mingw64/bin/zlib*.dll ../dist
cp /mingw64/bin/libstdc++*.dll ../dist
cp /mingw64/bin/libgcc_s_seh*.dll ../dist
```
6. Result is in `dist` folder

Note: `cmake -DCMAKE_EXE_LINKER_FLAGS="-static-libgcc -static-libstdc++ -static" -G "MinGW Makefiles" ..` will result in errors like `libpng16.a undefined reference to 'deflate'`

# Running

NOTE: Telegram's TGS format is a gzipped rlottie file.

Get info about TGS file:
```console
$ gunzip -c sample.tgs | tgs2png -i -
```

Extract 10's frame:
```console
$ gunzip -c sample.tgs | tgs2png -o 10 -n 1 - > frame10.png
```
