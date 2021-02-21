//
// Created by user on 13/08/2018.
//

#ifndef NEWEX2_BATTLESHIPS_H
#define NEWEX2_BATTLESHIPS_H

#define EMPTY_SLOT (-1)
#define SUCCESSFUL_HIT 5
#define MISSED_HIT 6
#define DEAD_SHIP 7
#define SPACE 32
#define X 'x'
#define O 'o'
#define UNDER_SCORE '_'
#define MINIMAL_ROW 97


#define TRUE 1
#define FALSE 0

typedef struct Board
{
    int size;
    int **board;
} Board;

static Board my_board;

void printBoard();
Board* initializeBoard(int size);
int hit(int column, int row);
int isGameOver();
void freeBoard(Board *my_board);




#endif //NEWEX2_BATTLESHIPS_H
