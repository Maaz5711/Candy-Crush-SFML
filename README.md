# Candy Crush Saga (SFML, C++)

A desktop Candy Crush-style match-3 game built with C++ and SFML.

## Project Overview

This project implements a 9x9 candy board with classic match-3 gameplay, special candy generation, score tracking, move limits, and save/load support.

## Gameplay Features

- Match-3 core mechanics on a 9x9 grid
- Special candy creation for 4 and 5 matches
- Additional special handling for L/T style patterns
- Score and remaining moves display
- Mouse-based candy selection and swapping
- Save and load game state through text files
- Custom candy and background textures

## Screenshot

![Candy Crush Gameplay](https://github.com/user-attachments/assets/11f7c02a-2824-49e8-be20-6c881f48199a)

## Controls

- Left click one candy to select it
- Left click an adjacent candy to swap
- Click Save Game to write the current state to save.txt
- Click Load Game to restore state from save.txt

## Tech Stack

- Language: C++
- Graphics: SFML Graphics module
- Data persistence: Standard file I/O (save.txt, load.txt)

## Project Structure

- PF PROJECT.cpp: Game logic and rendering loop
- functions.h: Header definitions used by the project
- images/: Candy, background, and font assets
- include/: SFML header files
- lib/: SFML library files and CMake config
- NewProject.sln / NewProject.vcxproj: Visual Studio build files

## Build Notes (Visual Studio)

1. Open NewProject.sln in Visual Studio.
2. Select x64 and Debug (or Release).
3. Build and run.

## Notes

- This version does not include gameplay sound/audio features.
- Keep images, include, and lib folders in place for correct asset and library resolution.
