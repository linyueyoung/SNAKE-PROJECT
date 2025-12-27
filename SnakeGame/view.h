#ifndef VIEW_H
#define VIEW_H
#include "common.h"

void initScreen();
void gotoXY(int x, int y);
void hideCursor();
void drawBorder();
void drawSnake(GameState* game);
void drawFood(int x, int y);
void drawScore(int score);
void clearScreen();
void clearTail(int x, int y);

#endif
