#include "game.h"
//#include "Timer.h"

/***********/
#ifdef __cplusplus
extern "C" {
#endif
/***********/
void welcome(int button)
{
  OrbitOledMoveTo(5, 5);
  OrbitOledDrawString("WELCOME,");
  OrbitOledMoveTo(5, 15);
  OrbitOledDrawString("PRESS BTN1.");
  OrbitOledUpdate();
  while (!digitalRead(button))
  {
  }
  delay(500);
  OrbitOledMoveTo(5, 5);
  OrbitOledDrawString("GET NUMBERS      ");
  OrbitOledMoveTo(5, 15);
  OrbitOledDrawString("FOR POINTS.      ");
  OrbitOledUpdate();
  while (!digitalRead(button))
  {
  }
  delay(500);
  OrbitOledMoveTo(5, 5);
  OrbitOledDrawString("TOUCH + TO        ");
  OrbitOledMoveTo(5, 15);
  OrbitOledDrawString("LOSE A POINT.      ");
  OrbitOledUpdate();
  while (!digitalRead(button))
  {
  }
  delay(500);
  OrbitOledMoveTo(5, 5);
  OrbitOledDrawString("TOUCH #,      ");
  OrbitOledMoveTo(5, 15);
  OrbitOledDrawString("YOU DIE!       ");
  OrbitOledUpdate();
  while (!digitalRead(button))
  {
  }
  delay(500);
  OrbitOledMoveTo(5, 5);
  OrbitOledDrawString("MOVE DOWN      ");
  OrbitOledMoveTo(5, 15);
  OrbitOledDrawString("WITH BTN1        ");
  OrbitOledMoveTo(5, 5);
  OrbitOledUpdate();
  while (!digitalRead(button))
  {
  }
  delay(500);
  OrbitOledMoveTo(5, 5);
  OrbitOledDrawString("MOVE UP        ");
  OrbitOledMoveTo(5, 15);
  OrbitOledDrawString("WITH BTN2      ");
  OrbitOledUpdate();
  while (!digitalRead(button))
  {
  }
  delay(500);
  OrbitOledMoveTo(5, 5);
  OrbitOledDrawString("MOVE LEFT            ");
  OrbitOledMoveTo(5, 15);
  OrbitOledDrawString("WITH SW2          ");
  OrbitOledUpdate();
  while (!digitalRead(button))
  {
  }
  delay(500);
  OrbitOledMoveTo(5, 5);
  OrbitOledDrawString("MOVE RIGHT           ");
  OrbitOledMoveTo(5, 15);
  OrbitOledDrawString("WITH SW1          ");
  OrbitOledUpdate();
  while (!digitalRead(button))
  {
  }
  delay(500);
  OrbitOledMoveTo(5, 5);
  OrbitOledDrawString("POTENTIOMETER           ");
  OrbitOledMoveTo(5, 15);
  OrbitOledDrawString("CONTROLS SPEED          ");
  OrbitOledUpdate();
  while (!digitalRead(button))
  {
  }
  delay(500);
  OrbitOledMoveTo(5, 5);
  OrbitOledDrawString("                             ");
  OrbitOledMoveTo(5, 15);
  OrbitOledDrawString("                            ");
  OrbitOledUpdate();
  delay(500);
}

void gridInit(grid *g)
{
  g->playerX = 1;
  g->playerY = 1;
  g->score = 20;
  g->playerHeading[0] = 1;
  g->arr = malloc(GRID_SIZE);

  char course[GRID_SIZE] = {//26*7
                            '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#',
                            '#', ' ', '+', '+', '5', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '+', '7', '+', '+', '+', '+', '+', '+', '9', '#',
                            '#', '+', '+', '+', '+', '+', '#', '+', '+', '+', '2', '+', '#', '+', '#', '#', '#', '#', '3', '+', '+', '#', '+', '+', '#',
                            '#', '+', '1', '#', '+', '9', '#', '5', '+', '+', '+', '+', '+', '+', '3', '+', '+', '+', '+', '+', '9', '#', '8', '9', '#',
                            '#', '+', '+', '+', '+', '+', '#', '+', '5', '+', '+', '+', '#', '#', '+', '+', '1', '+', '+', '+', '+', '+', '+', '#', '#',
                            '#', '+', '8', '+', '+', '+', '+', '+', '+', '+', '+', '+', '9', '+', '#', '+', '+', '+', '6', '+', '+', '1', '3', '9', '#',
                            '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'};

  for (int i = 0; i < GRID_SIZE; i++)
  {
    (*(g->arr + i)) = course[i];
  }
}

void playerDoMove(grid *g)
{
  int x = g->playerHeading[0];
  int y = g->playerHeading[1];
  if (g->playerX + x >= 0 && g->playerX + x < GRID_WIDTH)
    g->playerX += x;
  if (g->playerY + y >= 0 && g->playerY + y < GRID_HEIGHT)
    g->playerY += y;
}

void playerSetHeading(grid *g, int x, int y)
{
  g->playerHeading[0] = x;
  g->playerHeading[1] = y;
}

/**************************************************
 * PLEASE DONT TOUCH THIS FUNCTION; ITS EASY TO MESS UP
 * MAKE A NEW FUNCTION IF YOU NEED TO PRINT THE GRID ANOTHER WAY
 * THANKS
 **********************************************************/
//print the part of the grid what fits to screen, with player in the middle
void gridPrint(grid *g)
{

  int lowerX = g->playerX - LCD_WIDTH / 2 >= 0 ? g->playerX - LCD_WIDTH / 2 : 0;
  int upperX = lowerX + LCD_WIDTH <= GRID_SIZE ? lowerX + LCD_WIDTH : GRID_SIZE;
  int lowerY = g->playerY - LCD_HEIGHT / 2 >= 0 ? g->playerY - LCD_HEIGHT / 2 : 0;
  int upperY = lowerY + LCD_HEIGHT <= GRID_SIZE ? lowerY + LCD_HEIGHT : GRID_SIZE;

  if (lowerX + LCD_WIDTH > GRID_WIDTH)
  {
    lowerX = GRID_WIDTH - LCD_WIDTH;
  }
  if (lowerY + LCD_HEIGHT > GRID_HEIGHT)
  {
    lowerY = GRID_HEIGHT - LCD_HEIGHT;
  }


  for (int i = lowerX; i < upperX; i++)
  {
    for (int j = lowerY; j < upperY; j++)
    {
      drawGrid(g, lowerX, lowerY);
    }
  }
}

/**************************************************************
     * Take the appropriate steps to score points for landing on this cell (use g->playerX, g->playerY)
     * If it's a trap (#), player must do a challenge
     * If its a positive number, player scores points
     * If it's a + sign, player loses points
     *  Every time player lands on a number or a + symbol, but not a #,*  erase the symbol off the grid
     *  Ensure the player doesn't re-lose/gain points if they enter an erased cell
     *  Use g->playerX, g->playerY, g->score
     **************************************************************/
void scoreCell(grid *g, int wait, int button)
{
  int x = g->playerX;
  int y = g->playerY;
  int position = y * GRID_WIDTH + x;

  switch (g->arr[position])
  {
  case '#':
    trap(*g, wait, button);
    break;
  case '+':
    g->score--;
    break;
  case '0':
    g->score += 0;
    break;
  case '1':
    g->score += 1;
    break;
  case '2':
    g->score += 2;
    break;
  case '3':
    g->score += 3;
    break;
  case '4':
    g->score += 4;
    break;
  case '5':
    g->score += 5;
    break;
  case '6':
    g->score += 6;
    break;
  case '7':
    g->score += 7;
    break;
  case '8':
    g->score += 8;
    break;
  case '9':
    g->score += 9;
    break;
  default:
    break;
  }
  eraseCell(g, position);
}

void eraseCell(grid *g, int position)
{
  g->arr[position] = ' ';
}

void trap(grid *g, int wait, int button)
{
  OrbitOledMoveTo(5, 5);
  OrbitOledDrawString("YOU DIED");
  OrbitOledMoveTo(5, 15);
  OrbitOledDrawString("GAME OVER.");
  OrbitOledUpdate();
  while (1)
  {
  }

}
/************************************************************
       * Implement the end condition (all positive numbers are erased) 
       * and then show final score
       * Ask player if they want to play again, otherwise say goodbye message
       * It should be easy to reset grid (call gridInit())
       * **********************************************************/

void checkGameEndCase(grid *g, int button) //watching for lowbutton
{
  int a = 0;
  for (int i = 0; i < GRID_SIZE; i++)
  {
    if (!((g->arr[i] == ' ') || (g->arr[i] == '#') || (g->arr[i] == '+')))
    {
      a = 1;
      break;
    }
  }
  if (!a)
  {
    OrbitOledMoveTo(5, 5);
    OrbitOledDrawString("YOU WIN.    ");
    OrbitOledUpdate();
    while (1)
    {
    }
  }
}
/***********/
#ifdef __cplusplus
}
#endif
/***********/
