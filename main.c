#include "sudoku.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void inputBoard(Sudoku *s) {
    printf("Enter your Sudoku puzzle (use 0 or space for empty cells, and press Enter when a row is done)\n");
    for (int i = 0; i < SIZE; i++) {
        printf("Row %d :\n", i + 1);

        char rowCheck[SIZE + 1] = {0};
        char line[SIZE + 2];
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = 0;

        if (strlen(line) != SIZE) {
            printf("Error: Each line must contain exactly 9 digits or spaces.\n");
            exit(1);
        }

        for (int j = 0; j < SIZE; j++) {
            char input = line[j];

            if (input == '0' || input == ' ') {
                s->board[i][j] = ' ';
            } else if (input >= '1' && input <= '9') {
                if (rowCheck[input - '0']) {
                    printf("Error: Duplicate number");
                    exit(1);
                }
                rowCheck[input - '0'] = 1;
                s->board[i][j] = input;
            } else {
                printf("Error: Invalid input. Please enter numbers between 1-9 or 0 or space for empty.\n");
                exit(1);
            }
        }
    }

    if (!validateInitialBoard(s)) {
        printf("Error: Invalid Sudoku puzzle. Conflicts found. Please check your input.\n");
        exit(1);
    }
}

void inputBoardFromTxt(Sudoku *s, char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found.\n");
        return;
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            char input = fgetc(file);

            if (input == '\n') {
                j--;
                continue;
            }

            if (input == '0' || input == ' ') {
                s->board[i][j] = ' ';
            } else {
                s->board[i][j] = input;
            }
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    Sudoku s;
    int steps = 0;

    if (argc == 2) {
        inputBoardFromTxt(&s, argv[1]);
    } else {
        inputBoard(&s);
    }

    if (solveSudoku(&s, &steps)) {
        printGrid(&s);
        printf("Sudoku solved in %d steps.\n", steps);
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}
