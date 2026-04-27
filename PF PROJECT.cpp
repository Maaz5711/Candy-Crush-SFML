#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <array>
#include <cstdlib>
using namespace std;
using namespace sf;

// Constants
const int ROW = 9;
const int COL = 9;
const int CELL_SIZE = 80;
const int TOTAL_TEXTURES = 5;
const int SPECIAL_TEXTURES = 11;
// Grid offset
const int GRID_OFFSET_X = 0;
const int GRID_OFFSET_Y = 0;
const string ASSET_ROOT = "../../../images/";

// Globals
typedef array<array<int, COL>, ROW> Grid;
typedef array<array<bool, COL>, ROW> Mask;
Grid candies;
Mask assigned_toBurst;
RenderWindow window(VideoMode(1398, 896), "Candy Crush Saga", Style::Close);
array<Texture, TOTAL_TEXTURES> textures;
array<Texture, SPECIAL_TEXTURES> specialTextures;
Texture backgroundTexture;
Sprite backgroundSprite;
Font font;
Text scoreText;       // displays score
Text movestext;       // displays moves left
int score = 0;
int movesLeft = 20;

// Forward declaration
void updateUI();

// Save/Load functions
void saveGame() {
    ofstream ofs("save.txt");
    ofs << score << " " << movesLeft << '\n';
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) ofs << candies[i][j] << " ";
        ofs << '\n';
    }
}
bool loadGame() {
    ifstream ifs("save.txt");
    if (!ifs) return false;
    ifs >> score >> movesLeft;
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j)
            ifs >> candies[i][j];
    updateUI();
    return true;
}

// Load textures
void loadTextures() {
    for (int i = 0; i < TOTAL_TEXTURES; ++i) {
        string path = ASSET_ROOT + "candies/" + to_string(i) + ".jpg";
        if (!textures[i].loadFromFile(path)) { cerr << "Failed candy: " << path << endl; exit(1); }
    }
    for (int j = 0; j < SPECIAL_TEXTURES; ++j) {
        string path = ASSET_ROOT + "Special1/" + to_string(j) + ".jpg";
        if (!specialTextures[j].loadFromFile(path)) { cerr << "Failed special: " << path << endl; exit(1); }
    }
    string bg = ASSET_ROOT + "background/background.png";
    if (backgroundTexture.loadFromFile(bg)) {
        backgroundSprite.setTexture(backgroundTexture);
        backgroundSprite.setScale(1398.0f / backgroundTexture.getSize().x,
            896.0f / backgroundTexture.getSize().y);
    }
}

// Initialize grid
void initializeGrid() {
    srand((unsigned)time(nullptr));
    for (int i = 0; i < ROW; ++i)
        for (int j = 0; j < COL; ++j) {
            candies[i][j] = rand() % TOTAL_TEXTURES;
            assigned_toBurst[i][j] = false;
        }
}

// UI update
void updateUI() {
    scoreText.setString("Score: " + to_string(score));
    movestext.setString("Moves: " + to_string(movesLeft));
}

// Match detection with specials (striped and wrapped)
bool findMatches() {
    bool any = false;
    for (auto& r : assigned_toBurst) r.fill(false);
    static const int stripedMap[5] = { 7,9,0,4,3 };
    static const int wrappedMap[5] = { 6,10,2,5,8 };
    // Straight lines
    for (int i = 0; i < ROW; ++i) for (int j = 0; j < COL; ) {
        int v = candies[i][j], len = 1; while (j + len < COL && candies[i][j + len] == v) ++len;
        if (len >= 3) {
            any = true;
            if (len == 4) { candies[i][j] = TOTAL_TEXTURES + stripedMap[v]; for (int k = 1; k < 4; ++k) assigned_toBurst[i][j + k] = true; }
            else if (len >= 5) { candies[i][j] = TOTAL_TEXTURES + 1; for (int k = 1; k < len; ++k) assigned_toBurst[i][j + k] = true; }
            else for (int k = 0; k < 3; ++k) assigned_toBurst[i][j + k] = true;
        }
        j += max(1, len);
    }
    for (int j = 0; j < COL; ++j) for (int i = 0; i < ROW; ) {
        int v = candies[i][j], len = 1; while (i + len < ROW && candies[i + len][j] == v) ++len;
        if (len >= 3) {
            any = true;
            if (len == 4) { candies[i][j] = TOTAL_TEXTURES + stripedMap[v]; for (int k = 1; k < 4; ++k) assigned_toBurst[i + k][j] = true; }
            else if (len >= 5) { candies[i][j] = TOTAL_TEXTURES + 1; for (int k = 1; k < len; ++k) assigned_toBurst[i + k][j] = true; }
            else for (int k = 0; k < 3; ++k) assigned_toBurst[i + k][j] = true;
        }
        i += max(1, len);
    }
    // L & T shapes
    for (int i = 0; i < ROW - 2; ++i) for (int j = 0; j < COL - 2; ++j) {
        int v = candies[i][j];
        bool t1 = (candies[i][j] == v && candies[i][j + 1] == v && candies[i][j + 2] == v && candies[i + 1][j + 1] == v && candies[i + 2][j + 1] == v);
        bool t2 = (candies[i + 1][j] == v && candies[i + 1][j + 1] == v && candies[i + 1][j + 2] == v && candies[i][j + 1] == v && candies[i + 2][j + 1] == v);
        if (t1 || t2) { any = true; candies[i + 1][j + 1] = TOTAL_TEXTURES + wrappedMap[v]; assigned_toBurst[i][j] = assigned_toBurst[i][j + 1] = assigned_toBurst[i][j + 2] = true; assigned_toBurst[i + 1][j + 1] = assigned_toBurst[i + 2][j + 1] = true; }
        bool l1 = (candies[i][j] == v && candies[i + 1][j] == v && candies[i + 2][j] == v && candies[i + 2][j + 1] == v);
        bool l2 = (candies[i][j + 1] == v && candies[i][j + 2] == v && candies[i + 1][j + 2] == v && candies[i + 2][j + 2] == v);
        bool l3 = (candies[i + 1][j] == v && candies[i + 2][j] == v && candies[i][j + 1] == v && candies[i][j + 2] == v);
        bool l4 = (candies[i][j] == v && candies[i + 1][j] == v && candies[i + 2][j] == v && candies[i][j + 1] == v);
        if (l1 || l2 || l3 || l4) { any = true; candies[i + 1][j] = TOTAL_TEXTURES + wrappedMap[v]; assigned_toBurst[i][j] = assigned_toBurst[i + 1][j] = assigned_toBurst[i + 2][j] = true; assigned_toBurst[i + 1][j + 1] = assigned_toBurst[i + 1][j + 2] = true; }
    }
    return any;
}

// Process matches
void processMatches() { for (int j = 0; j < COL; ++j) { int w = ROW - 1; for (int i = ROW - 1; i >= 0; --i) if (!assigned_toBurst[i][j]) candies[w--][j] = candies[i][j]; while (w >= 0) candies[w--][j] = rand() % TOTAL_TEXTURES; } score += 30; updateUI(); }

int main() {
    loadTextures(); initializeGrid();
    if (!font.loadFromFile(ASSET_ROOT + "text/Lato-Black.ttf")) { cerr << "Font fail"; return 1; }
    scoreText.setFont(font); scoreText.setPosition(1000, 50);
    movestext.setFont(font); movestext.setPosition(1000, 100);
    // Style buttons text black
    Text saveText("Save Game", font, 20); saveText.setPosition(1000, 155); saveText.setFillColor(Color::Black);
    Text loadText("Load Game", font, 20); loadText.setPosition(1000, 205); loadText.setFillColor(Color::Black);
    updateUI(); Sprite sprite; sprite.setScale(CELL_SIZE / float(textures[0].getSize().x), CELL_SIZE / float(textures[0].getSize().y));
    // Buttons
    RectangleShape saveBtn(Vector2f(120, 40)); saveBtn.setPosition(1000, 150);
    RectangleShape loadBtn(Vector2f(120, 40)); loadBtn.setPosition(1000, 200);
    int selR = -1, selC = -1; window.setFramerateLimit(60);
    while (window.isOpen()) {
        Event e;
        while (window.pollEvent(e)) {
            if (e.type == Event::Closed) window.close();
            if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left) {
                Vector2f mp(e.mouseButton.x, e.mouseButton.y);
                if (saveBtn.getGlobalBounds().contains(mp)) { saveGame(); }
                else if (loadBtn.getGlobalBounds().contains(mp)) { if (loadGame()) cout << "Game loaded\n"; }
                else {
                    int mx = e.mouseButton.x - GRID_OFFSET_X, my = e.mouseButton.y - GRID_OFFSET_Y;
                    int c = mx / CELL_SIZE, r = my / CELL_SIZE;
                    if (mx >= 0 && my >= 0 && c < COL && r < ROW) {
                        if (selR < 0) { selR = r; selC = c; }
                        else { if (abs(selR - r) + abs(selC - c) == 1) { swap(candies[selR][selC], candies[r][c]); if (findMatches()) { movesLeft--; updateUI(); processMatches(); if (movesLeft <= 0) window.close(); } else swap(candies[selR][selC], candies[r][c]); } selR = selC = -1; }
                    }
                }
            }
        }
        window.clear(); window.draw(backgroundSprite);
        for (int i = 0; i < ROW; ++i) for (int j = 0; j < COL; ++j) { int v = candies[i][j]; sprite.setTexture(v < TOTAL_TEXTURES ? textures[v] : specialTextures[v - TOTAL_TEXTURES]); sprite.setPosition(j * CELL_SIZE, i * CELL_SIZE); window.draw(sprite); if (i == selR && j == selC) { RectangleShape hl({ float(CELL_SIZE),float(CELL_SIZE) }); hl.setPosition(j * CELL_SIZE, i * CELL_SIZE); hl.setOutlineColor(Color::Red); hl.setOutlineThickness(3); window.draw(hl); } }
        window.draw(saveBtn); window.draw(loadBtn);
        window.draw(saveText); window.draw(loadText);
        window.draw(scoreText); window.draw(movestext);
        window.display();
    }
    return 0;
}
