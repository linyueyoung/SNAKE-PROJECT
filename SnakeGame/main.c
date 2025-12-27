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

        updateSnake(&game);

        if (!game.isGameOver) {
            drawSnake(&game);
            drawFood(game.foodX, game.foodY);
            drawScore(game.score);

            if (game.tail != NULL && game.head->x != game.foodX) {
                clearTail(game.tail->x, game.tail->y);
            }

            Sleep(100);
        }
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
    return 0;
}