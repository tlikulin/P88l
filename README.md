# P88l
A simple version of eight-ball written in C++ using SFML 2.5.1 for graphics and audio and cmake as the bulding system.

![Screenshot from menu](/media/screenshots/screenshot_menu.png)    
![Screenshot from game](/media/screenshots/screenshot_game.png)

## Prerequisites
You need to have `git`, `cmake`, and a _C++_ compiler (e.g., g++ or MSVC from Visual Studio) installed on your machine.
### Extra dependencies (Linux only)
You need to download SFML version 2.5 from your package manager.    
If you cannot do so, the library will be fetched and built from source, but it depends on some development libraries.    
You can download them with the following commands.

For apt:

```bash
sudo apt install libx11-dev libxrandr-dev libxcursor-dev libxinerama-dev libxi-dev
sudo apt install libgl1-mesa-dev libopenal-dev libvorbis-dev libogg-dev libflac-dev
sudo apt install libfreetype6-dev libudev-dev
```

For dnf:

```bash
sudo dnf install libX11-devel libXrandr-devel libXcursor-devel libXinerama-devel libXi-devel
sudo dnf install mesa-libGL-devel openal-soft-devel libvorbis-devel libogg-devel flac-devel
sudo dnf install freetype-devel systemd-devel
```

## Building
Open a terminal (or command prompt) and enter the following commands:
1. clone the repository;
   ```bash
   git clone https://github.com/tlikulin/P88l && cd P88l
   ```

2. build the project with cmake;
   ```bash
   cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
   cmake --build build --config Release
   ```

3. the executable will be in **build/bin**.

Tested on Windows Pro 10 64-bit (Visual Studio 2022), Fedora Workstation 41 (g++), and Ubuntu 24.04.2 LTS (g++). 

## How to play
- You start in the menu where you need to choose the mode: "2 Players" (both controlled manually) or "Against Bot" (one is controlled by the computer). There is also a ??? button...
- While playing, the scores and the current state are displayed.
- The goal is to pot all balls of your color, followed by the eight-ball.
    - If you have potted balls of your color only during a turn, you get an extra turn.
    - Potted cue ball and eight-ball are replaced at a random position. However, should you pot both in one turn, you lose (foul).
- When it's your turn, drag at the cue ball to aim. A trajectory preview will be displayed (does not take into account collisions with other balls but can calculate reflections).
    - You can control the power, which is shown by the trajectory, although not precisely. If you reach the maximum power, it turns red.
    - If you don't have enough space, you can release the mouse at the cue ball (your turn will not be wasted) and move the window.
- The game finishes once a player who have potted all balls of their color pots the eight-ball. You are brought back to the menu, and the game result is displayed.
- Extra controls:
    - **P** to cycle through the trajectory modes (including invisible).
    - **~** to turn on/off the fps counter (locked at 200 for consistency).
    - **Shift+Esc** to abandon the current game and go to the menu.

PS You might want to temporarily set scaling on your screen to 100% for better experience (e.g., System>Display>Scale and Layout>"Change the size of text, apps, and other items" on Windows 10).

## Credits
This project uses the MesloLGS NF font, which is based on Meslo LG (licensed under Apache License 2.0) and includes modifications from the Nerd Fonts project.
