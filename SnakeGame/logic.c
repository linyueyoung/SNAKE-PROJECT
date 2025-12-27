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

// logic.c 的 generateFood 函式

void generateFood(GameState* game) {
    int valid = 0;
    while (!valid) {
        // 【關鍵修改】
        // 原本可能只有 (rand() % WIDTH)
        // 改成 (WIDTH - 4) + 2，這代表：
        // "最左邊空 2 格，最右邊也空 2 格"，絕對不會碰到牆壁！

        game->foodX = (rand() % (WIDTH - 4)) + 2;
        game->foodY = (rand() % (HEIGHT - 4)) + 2;

        valid = 1;

        // 檢查有沒有長在蛇身上 (防呆機制)
        SnakeNode* current = game->head;
        while (current != NULL) {
            if (current->x == game->foodX && current->y == game->foodY) {
                valid = 0; // 重疊了，重抽一次
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

    // 檢查撞牆 (配合 view.c 的牆壁位置)
        // view.c 的牆壁在 0 和 WIDTH+1，所以我們要這些地方設為禁區
// logic.c 的 updateSnake 函式裡面

    // 【修正後】檢查 "下一步 (newX, newY)" 會不會撞牆
    if (newX <= 0 || newX >= WIDTH + 1 ||
        newY <= 0 || newY >= HEIGHT + 1) {

        game->isGameOver = 1;
        return; // 【關鍵！】直接結束函式，絕對不要讓下面的程式碼把蛇移到牆壁上！
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