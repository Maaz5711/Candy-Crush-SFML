#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>

constexpr int ROWS = 9;
constexpr int COLS = 9;
constexpr int CELL_SIZE = 70;
constexpr int NUM_COLORS = 5;

// special candy base IDs
constexpr int STRIPED = 10;
constexpr int WRAPPED = 20;
constexpr int COLORBOMB = 30;

using Grid = std::array<std::array<int, COLS>, ROWS>;

extern Grid candies;
extern sf::RenderWindow window;
extern std::array<sf::Texture, NUM_COLORS> textures;
extern std::array<sf::Texture, NUM_COLORS> specialTextures;
extern sf::Font font;
extern sf::Text scoreText, movesText;

void loadTextures();
void initGrid();
bool trySwap(int r1, int c1, int r2, int c2);
bool findMatches();
void removeMatches();
void applyGravity();
void spawnSpecialIfNeeded();
void updateScoreText();
void updateMovesText();
void saveGame(int score, int moves);
bool loadGame(int& score, int& moves);
