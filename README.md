# Candy Crush Saga (SFML, C++)

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![SFML](https://img.shields.io/badge/SFML-Graphics%20%26%20Window-brightgreen)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)

A desktop Candy Crush-style match-3 game built with C++ and SFML, featuring special candy logic, cascading matches, score tracking, move limits, and save/load support.

## Description

Candy Crush Saga (SFML Edition) is a fast-paced puzzle game project that recreates the classic match-3 gameplay loop in a native C++ desktop application. The game uses custom image assets, real-time rendering with SFML, and interactive mouse controls for swapping candies, triggering combos, and chasing high scores.

### Short Description For GitHub About

Candy Crush-style match-3 game in C++ and SFML with special candies, score/moves UI, and save/load support.

## Project Overview

This project runs on a 9x9 candy grid with classic match-3 rules, special candy generation, score progression, and turn-based move limits.

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

## Quick Start

1. Open NewProject.sln in Visual Studio.
2. Select x64 and Debug (or Release).
3. Build and run.

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
