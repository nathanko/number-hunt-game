#include "game.h"

#include "delay.h"
#include "FillPat.h"
#include "LaunchPad.h"
#include "OrbitBoosterPackDefs.h"
#include "OrbitOled.h"
#include "OrbitOledChar.h"
#include "OrbitOledGrph.h"
#include <stdlib.h>
#include <stdio.h>

void drawGrid(grid *g, int x, int y)
{ 
  char *str = g->arr;
  for (int i = 0; i < 3; i++)
  {
    OrbitOledMoveTo(0, 10 * i);
    OrbitOledDrawString(str + x + y * GRID_WIDTH + i * GRID_WIDTH);
    
    OrbitOledMoveTo((g->playerX - x) * 8, (g->playerY - y) * 10);
        char *playerAvatar = "O";
    OrbitOledDrawString(playerAvatar);
    


    OrbitOledMoveTo((LCD_WIDTH)*8, 10*i);
    char *blank= "        ";
    OrbitOledDrawString(blank);
  
  }
  
    char scoreStr[3];
    sprintf(scoreStr, "%0d", g->score);
    OrbitOledMoveTo((LCD_WIDTH)*8, 10*(LCD_HEIGHT-3));
    OrbitOledDrawString(scoreStr);

    
    OrbitOledUpdate();
}

void GameUIInit()
{
  OrbitOledInit();
  OrbitOledClear();
  OrbitOledClearBuffer();
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledSetDrawMode(modOledSet);
  OrbitOledSetCharUpdate(0);
}

char readInputs(int r1, int r2, int r3, int r4)
{
  char button;
  if (digitalRead(r1))
    button = 'w';
  else if (digitalRead(r2))
    button = 's';
  else if (digitalRead(r4))
    button = 'd';
  else if (digitalRead(r3))
    button = 'a';
  else
    button = ' ';
  return button;
}
