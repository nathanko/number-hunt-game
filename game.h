#ifndef GAME_H
#define GAME_H

#define GRID_SIZE 175
#define GRID_WIDTH 25
#define GRID_HEIGHT 7
#define LCD_WIDTH 13
#define LCD_HEIGHT 3

/***********/
#ifdef __cplusplus
extern "C" {
#endif

/****GRID*****/

typedef struct
{
  int playerX;
  int playerY;
  char *arr;
  int playerHeading[2];
  int score;
} grid;

void welcome(int button);
void gridInit(grid *g);
void gridPrint(grid *g);
void playerDoMove(grid *g);
void playerSetHeading(grid *g, int x, int y);
void scoreCell(grid *g, int wait, int button);
void checkGameEndCase(grid *g, int button);

/********I/O*****************/
void drawGrid(grid *g, int x, int y);
void GameUIInit();
char readInputs(int a, int b, int c, int d);

/***********/
#ifdef __cplusplus
}
#endif
/***********/

#endif
