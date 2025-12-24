#ifndef LOGIC_H
#define LOGIC_H
#include "common.h"

void initGame(GameState* game);
void updateSnake(GameState* game);
void generateFood(GameState* game);
void freeSnake(GameState* game);

#endif