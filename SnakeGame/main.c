#include "common.h"
#include "view.h"
#include "logic.h"
#include "file.h"

int main() {
    srand((unsigned)time(NULL));

    initScreen();
    int highScore = loadHighScore();

    printf("=== SNAKE GAME ===\n");
    printf("Highest Score: %d\n", highScore);
    printf("Press ANY KEY to start...");
    _getch();
    clearScreen();

    GameState game;
    initGame(&game);
    drawBorder();

    // --- 請把 main.c 裡的 while 迴圈換成這一段 ---

    while (!game.isGameOver) {
        if (_kbhit()) {
            char key = _getch();
            switch (key) {
            case 'w': case 'W': if (game.dir != DOWN) game.dir = UP; break;
            case 's': case 'S': if (game.dir != UP) game.dir = DOWN; break;
            case 'a': case 'A': if (game.dir != RIGHT) game.dir = LEFT; break;
            case 'd': case 'D': if (game.dir != LEFT) game.dir = RIGHT; break;
            }
        }

        // 1. 【關鍵！】先記住還沒移動前的「舊尾巴」座標
        int oldTailX = -1, oldTailY = -1;
        if (game.tail != NULL) {
            oldTailX = game.tail->x;
            oldTailY = game.tail->y;
        }

        // 2. 蛇開始移動 (更新資料)
        updateSnake(&game);

        // 3. 畫出新位置的蛇、食物、分數
        if (!game.isGameOver) {
            drawSnake(&game);
            drawFood(game.foodX, game.foodY);
            drawScore(game.score);

            // 4. 【關鍵！】如果蛇移動了（尾巴座標變了），才把「舊尾巴」擦掉
            // 這樣就不會留下殘影，也不會誤刪剛長出來的尾巴
            if (game.tail != NULL) {
                if (oldTailX != -1 && (game.tail->x != oldTailX || game.tail->y != oldTailY)) {
                    clearTail(oldTailX, oldTailY);
                }
            }
        }

        Sleep(100); // 控制速度
    }
    saveHighScore(game.score);
    freeSnake(&game);

    clearScreen();
    gotoXY(WIDTH / 2 - 5, HEIGHT / 2);
    printf("GAME OVER!");
    gotoXY(WIDTH / 2 - 5, HEIGHT / 2 + 1);
    printf("Final Score: %d", game.score);

    while (1) {
        if (_kbhit()) break;
    }
    system("pause");
    return 0;
}