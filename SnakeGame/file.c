#include "file.h"

void saveHighScore(int score) {
    int currentHigh = loadHighScore();
    if (score > currentHigh) {
        FILE* f = fopen("highscore.txt", "w");
        if (f != NULL) {
            fprintf(f, "%d", score);
            fclose(f);
        }
    }
}

int loadHighScore() {
    FILE* f = fopen("highscore.txt", "r");
    int score = 0;
    if (f != NULL) {
        fscanf(f, "%d", &score);
        fclose(f);
    }
    return score;
}