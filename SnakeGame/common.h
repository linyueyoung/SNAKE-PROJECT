#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define WIDTH 40
#define HEIGHT 20

typedef enum { UP, DOWN, LEFT, RIGHT } Direction;

typedef struct SnakeNode {
    int x;
    int y;
    struct SnakeNode* next;
} SnakeNode;

typedef struct {
    SnakeNode* head;
    SnakeNode* tail;
    int length;
    Direction dir;
    int score;
    int foodX;
    int foodY;
    int isGameOver;
} GameState;

#endif