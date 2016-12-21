#include "delay.h"
#include "FillPat.h"
#include "LaunchPad.h"
#include "OrbitBoosterPackDefs.h"
#include "OrbitOled.h"
#include "OrbitOledChar.h"
#include "OrbitOledGrph.h"

#include "game.h"

const uint32_t Potentiometer = PE_3;
const uint32_t RightSwitch = PA_7;
const uint32_t LeftSwitch = PA_6;
const uint32_t TopButton = PE_0;
const uint32_t LowButton = PD_2;
const uint32_t LeftButton = PF_4;
const uint32_t RightButton = PF_0;

grid g; //object oriented thinking lol

void setup()
{

  /***SETUP I/O****/
  pinMode(RightSwitch, INPUT);
  pinMode(LeftSwitch, INPUT);
  pinMode(TopButton, INPUT);
  pinMode(LowButton, INPUT);
  pinMode(LeftButton, INPUT);
  pinMode(RightButton, INPUT);
  GameUIInit();
  /*****/

  Serial.begin(9600);
  Serial.println("begin!!\n");
  gridInit(&g);
  g.playerX = 1;
  g.playerY = 1;

  /**************************************************************
   * Display a welcome message and quick instructions
   *************************************************************/
  welcome(LowButton);

  gridPrint(&g);

  //IMPLEMENT HERE
}

void loop()
{
  char input;                                                          //movement input
  int wait = (int)(7095.0 / (analogRead(Potentiometer) + 3000) * 350); //amount to wait before each new player movement
  
  Serial.print(wait);

  int TopButtonState = digitalRead(TopButton);
  if (TopButtonState == HIGH)
    playerSetHeading(&g, 0, -1);

  int LowButtonState = digitalRead(LowButton);
  if (LowButtonState == HIGH)
    playerSetHeading(&g, 0, 1);

  int LeftSwitchState = digitalRead(LeftSwitch);
  if (LeftSwitchState == HIGH)
    playerSetHeading(&g, -1, 0);

  int RightSwitchState = digitalRead(RightSwitch);
  if (RightSwitchState == HIGH)
    playerSetHeading(&g, 1, 0);

  playerDoMove(&g);
  scoreCell(&g, wait, LowButton); 
  gridPrint(&g);
  delay(wait);
  checkGameEndCase(&g, LowButton); //IMPLEMENT IN GRID.C
}
