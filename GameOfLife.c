#include <pthread.h>
#include "raylib.h"
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <time.h>
#include <unistd.h>

typedef struct Cell {
  int x;
  int y;
  int alive;
} Cell;

#define ROWS 2500
#define COLS 2500
#define POPULATION 500000

const int width = 5000;
const int height = 5000;
const int screen_width = 1900;
const int screen_height = 1000;
const int cell_width = width / ROWS;
const int cell_height = height / COLS;

void CellDraw(Cell cell);
void CellAlive(Cell *cell);
void CellDie(Cell *cell);

int main() {
  srand(time(0));

  Cell grid[ROWS][COLS];

  InitWindow(screen_width, screen_height, "Title");

  SetTargetFPS(60);

  // Initialization of the grid
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLS; j++) {
      grid[i][j].x = i;
      grid[i][j].y = j;
      grid[i][j].alive = 0;
    }
  }

  // Populate the grid
  int m, n;
  for (int k = 0; k < POPULATION; k++) {
    // This is done in order to avoid corners and edges
    m = rand() % (ROWS - 2) + 1;
    n = rand() % (COLS - 2) + 1;

    if (grid[m][n].alive == 0) {
      CellAlive(&grid[m][n]);
    } else {
      k--;
    }
  }

  int cell_alive_counter = 0;

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    // Draw the grid
    for (int i = 0; i < ROWS; i++) {
      for (int j = 0; j < COLS; j++) {
        CellDraw(grid[i][j]);
      }
    }

    // Here begins the magic
    for (int i = 1; i < (ROWS - 1); i++) {
      for (int j = 1; j < (COLS - 1); j++) {
        int startX = grid[i][j].x - 1;
        int startY = grid[i][j].y - 1;

        for (int X = startX; X < 3 + startX; X++) {
          for (int Y = startY; Y < 3 + startY; Y++) {
            if (X == i && Y == j) {
              continue;
            }
            if (grid[X][Y].alive == 1) {
              cell_alive_counter++;
            }
          }
        }

        if (grid[i][j].alive == 1 &&
            (cell_alive_counter == 2 || cell_alive_counter == 3)) {
          CellAlive(&grid[i][j]);
        } else if (grid[i][j].alive == 0 && cell_alive_counter == 3) {
          CellAlive(&grid[i][j]);
        } else {
          CellDie(&grid[i][j]);
        }

        cell_alive_counter = 0;
      }
    }

    EndDrawing();
    // sleep(1);
  }

  CloseWindow();

  return 0;
}

void CellDraw(Cell cell) {
  if (cell.alive == 1) {
    DrawRectangle(cell.x * cell_width, cell.y * cell_height, cell_width,
                  cell_height, WHITE);
  } else if (cell.alive == 0) {
    DrawRectangle(cell.x * cell_width, cell.y * cell_height, cell_width,
                  cell_height, BLACK);
  }
}

void CellAlive(Cell *cell) { cell->alive = 1; }

void CellDie(Cell *cell) { cell->alive = 0; }
