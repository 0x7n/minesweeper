#pragma once
#include "../defs.h"
#include <SFML/Graphics.hpp>

class Grid {
public:
    static constexpr int MAX_SIZE = 30;

public:
    void setupGrid(int width, int height, int mines) {
        currentW = width;
        currentH = height;
        currentMines = mines;

        for (int i = 0; i < currentW; i++) {
            for (int j = 0; j < currentH; j++) {
                grid[i][j] = NONE;
                states[i][j] = HIDDEN;
            }
        }

        std::srand(static_cast<unsigned>(std::time(nullptr)));
        int placed = 0;
        while (placed < currentMines) {
            int x = std::rand() % currentW;
            int y = std::rand() % currentH;
            if (grid[x][y] != MINE) {
                grid[x][y] = MINE;
                placed++;
            }
        }

        for (int x = 0; x < currentW; x++) {
            for (int y = 0; y < currentH; y++) {
                if (grid[x][y] == MINE) continue;
                int count = 0;
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        int nx = x + i;
                        int ny = y + j;
                        if (nx >= 0 && nx < currentW && ny >= 0 && ny < currentH) {
                            if (grid[nx][ny] == MINE) count++;
                        }
                    }
                }
                grid[x][y] = count;
            }
        }
    }

    void flagCell(int x, int y) {
        if (x < 0 || x >= currentW || y < 0 || y >= currentH) return;
        if (states[x][y] == REVEALED) return;

        if (states[x][y] == FLAGGED) {
            states[x][y] = HIDDEN;
            return;
        }

        states[x][y] = FLAGGED;
    }

    void revealCell(int x, int y) {
        if (x < 0 || x >= currentW || y < 0 || y >= currentH) return;
        if (states[x][y] == REVEALED) return;

        states[x][y] = REVEALED;

        if (grid[x][y] == NONE) {
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    if (i == 0 && j == 0) continue;
                    revealCell(x + i, y + j);
                }
            }
        }
    }

    int getWidth() const { return currentW; }
    int getHeight() const { return currentH; }
    int getMineCount() const { return currentMines; }

    int getState(int x, int y) { return states[x][y]; }
    int getCellAtPosition(int x, int y) { return grid[x][y]; }

private:
    int grid[MAX_SIZE][MAX_SIZE];
    CellState states[MAX_SIZE][MAX_SIZE];
    int currentW, currentH, currentMines;
};