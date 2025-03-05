# P88l
A simple version of eight-ball written in C++ using SFML 2.5.1 for graphics and audio and cmake as the bulding system.

## Prerequisites
You need to have `git`, `cmake`, and a C++ compiler (e.g., g++ or MSVC from Visual Studio) installed on your machine.
### Extra dependencies (Linux only)
You need to download SFML version 2.5 from your package manager.
If you cannot do so, the library will be fetched and built from source, but it depends on some development libraries.
You can download them with the following command.
For apt:
`sudo apt install libx11-dev libxrandr-dev libxcursor-dev libxinerama-dev libxi-dev \
                  libgl1-mesa-dev libopenal-dev libvorbis-dev libogg-dev libflac-dev \
                  libfreetype6-dev libudev-dev`
For dnf:
`sudo dnf install libX11-devel libXrandr-devel libXcursor-devel libXinerama-devel libXi-devel \
                  mesa-libGL-devel openal-soft-devel libvorbis-devel libogg-devel flac-devel \
                  freetype-devel systemd-devel`

## Building
Open a terminal (or command prompt) and enter the following commands:
- clone the repository;
  `git clone https://github.com/tlikulin/P88l && cd P88l`
- build the project with cmake;
  `cmake -S . -B build -DCMAKE_BUILD_TYPE=Release`
  `cmake --build build --config Release`
- the executable will be in build/bin.

Tested on Windows Pro 10 64-bit (Visual Studio 2022), Fedora Workstation 41 (g++), and Ubuntu 24.04.2 LTS (g++). 

## Credits
This project uses the MesloLGS NF font, which is based on Meslo LG (licensed under Apache License 2.0) and includes modifications from the Nerd Fonts project.
