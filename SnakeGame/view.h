#ifndef VIEW_H
#define VIEW_H

#include "common.h" // 必須包含這個，因為裡面有 GameState 的定義

// 游標控制
void gotoXY(int x, int y);
void hideCursor();
void initScreen();
void clearScreen();

// 繪圖函式 (配合 main.c 的呼叫方式)
void drawBorder();
void drawSnake(GameState* game); // 這裡改成了傳入指標
void drawFood(int x, int y);
void drawScore(int score);
void clearTail(int x, int y);

#endif