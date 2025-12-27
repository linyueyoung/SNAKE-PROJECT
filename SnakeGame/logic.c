#include "logic.h"

void initGame(GameState* game) {
    game->head = (SnakeNode*)malloc(sizeof(SnakeNode));
    game->head->x = WIDTH / 2;
    game->head->y = HEIGHT / 2;
    game->head->next = NULL;
    game->tail = game->head;

    game->length = 1;
    game->dir = RIGHT;
    game->score = 0;
    game->isGameOver = 0;

    generateFood(game);
}

void generateFood(GameState* game) {
    int valid = 0;
    while (!valid) {
        valid = 1;
        game->foodX = (rand() % WIDTH) + 1;
        game->foodY = (rand() % HEIGHT) + 1;

        SnakeNode* current = game->head;
        while (current != NULL) {
            if (current->x == game->foodX && current->y == game->foodY) {
                valid = 0;
                break;
            }
            current = current->next;
        }
    }
}

void updateSnake(GameState* game) {
    int newX = game->head->x;
    int newY = game->head->y;

    switch (game->dir) {
    case UP: newY--; break;
    case DOWN: newY++; break;
    case LEFT: newX--; break;
    case RIGHT: newX++; break;
    }

    if (newX <= 0 || newX >= WIDTH + 1 || newY <= 0 || newY >= HEIGHT + 1) {
        game->isGameOver = 1;
        return;
    }

    SnakeNode* current = game->head;
    while (current != NULL) {
        if (current->x == newX && current->y == newY) {
            game->isGameOver = 1;
            return;
        }
        current = current->next;
    }

    SnakeNode* newHead = (SnakeNode*)malloc(sizeof(SnakeNode));
    newHead->x = newX;
    newHead->y = newY;
    newHead->next = game->head;
    game->head = newHead;

    if (newX == game->foodX && newY == game->foodY) {
        game->score += 10;
        game->length++;
        generateFood(game);
    }
    else {
        SnakeNode* temp = game->head;
        while (temp->next->next != NULL) {
            temp = temp->next;
        }
        free(temp->next);
        temp->next = NULL;
        game->tail = temp;
    }
}

void freeSnake(GameState* game) {
    SnakeNode* current = game->head;
    while (current != NULL) {
        SnakeNode* temp = current;
        current = current->next;
        free(temp);
    }
}