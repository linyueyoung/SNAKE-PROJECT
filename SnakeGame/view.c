#include "view.h"
#include <stdio.h>
#include <windows.h>
#include "common.h"  // <--- 一定要有這行，才能讀到正確的大小
// 這裡定義邊框大小，要跟 logic.c 的邏輯一致
// 如果 logic.c 用的是 20x20，這裡也要是 20x20


void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void initScreen() {
    system("mode con cols=60 lines=30"); // 設定視窗大小
    system("title Snake Project");
    hideCursor();
}

// view.c

void clearScreen() {
    system("cls");  // <--- 加上這一行！這會把舊的畫面擦乾淨
}
void drawBorder() {
    // 畫上牆
    for (int i = 0; i < WIDTH + 2; i++) {
        gotoXY(i, 0); printf("#");
        gotoXY(i, HEIGHT + 1); printf("#");
    }
    // 畫左右牆
    for (int i = 0; i < HEIGHT + 2; i++) {
        gotoXY(0, i); printf("#");
        gotoXY(WIDTH + 1, i); printf("#");
    }
}

// 【關鍵修正】這裡改成接收 GameState 指標，並用 Linked List 畫蛇
void drawSnake(GameState* game) {
    SnakeNode* current = game->head;
    while (current != NULL) {
        gotoXY(current->x, current->y);

        if (current == game->head) {
            printf("O"); // 蛇頭
        }
        else {
            printf("o"); // 蛇身
        }

        current = current->next; // 移動到下一個節點
    }
}

void drawFood(int x, int y) {
    gotoXY(x, y);
    printf("$");
}

void drawScore(int score) {
    gotoXY(WIDTH + 5, 2); // 把分數畫在右邊
    printf("Score: %d", score);
}

void clearTail(int x, int y) {
    gotoXY(x, y);
    printf(" ");
}