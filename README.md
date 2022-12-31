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

# Building (Visual Studio 17 2022) (Broken)
1. Install cmake
2. Install Visual Studio
3. Install vcpkg to `C:\vcpkg` by:
```
cd C:\
git clone https://github.com/Microsoft/vcpkg.git
.\vcpkg\bootstrap-vcpkg.bat
```
4. Add `C:\vcpkg` to `PATH` environment variable
5. Install libpng: `vcpkg install libpng:x64-windows`
6. Open `Developer PowerShell`, change directory to tgs2png repo and execute:
```
mkdir build
cd build
cmake CMakeLists.txt -G "Visual Studio 17 2022" ..
```
7. Open `build/tgs2png.vcxproj` with `Visual Studio`
8. On top bar, change `Debug` to `Release`
9. On left bar, right click on "Solution 'tgs2png'" and press "Build Solution"
10. In `Developer PowerShell` you had open, run: `cp .\rlottie\Release\* .\Release\`
11. Copy `msvcp140.dll`, `vcruntime140.dll` and `vcruntime140_1.dll` into `tgs2png/build/Release`. They should be in somewhere like `C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Redist\MSVC\14.34.31931\x64\Microsoft.VC143.CRT`
12. For sharing, use "tgs2png/build/Release/tgs2png.exe"

- The resulting png file is broken

# Building (Windows MSYS2 MINGW64) (Broken)

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

- `cmake -DCMAKE_EXE_LINKER_FLAGS="-static-libgcc -static-libstdc++ -static" -G "MinGW Makefiles" ..` will result in errors like `libpng16.a undefined reference to 'deflate'`
- Running -h is normal
- Able to create png file but freeze after conversion
- The resulting png file is broken
- Note that -d will print the debug messages normally, then freeze after finishing

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
