
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define EMPTY_SLOT (-1)
#define UP 0
#define DOWN 2
#define LEFT 1
#define RIGHT 3
#define NUM_OF_DIRECTIONS 4
#define NUM_OF_SHIPS 5
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

static int vessels[5] = {5, 4, 3, 3, 2};

typedef struct Board
{
    int size;
    int **board;
} Board;

static Board my_board;

int horizontalCheck(int direction, int rowCoord, int colCoord, int ship, int index)
{
    int i;
    if (direction == LEFT)
    {
        if ((colCoord - ship + 1) < 0)
        {
            return FALSE;
        }
        for (i = 0; i < ship; i++)
        {
            if ((my_board.board[rowCoord][colCoord - i] != EMPTY_SLOT) || (colCoord - i < 0))
            {
                return FALSE;
            }
        }
        for (i = 0; i < ship; i++)
        {
            my_board.board[rowCoord][colCoord - i] = index;
        }
    }
    else if (direction == RIGHT)
    {
        if ((colCoord + ship) > my_board.size)
        {
            return FALSE;
        }
        for (i = 0; i < ship; i++)
        {
            if ((my_board.board[rowCoord][colCoord + i] != EMPTY_SLOT) || (colCoord + i >= my_board.size))
            {
                return FALSE;
            }
        }
        for (i = 0; i < ship; i++)
        {
            my_board.board[rowCoord][colCoord + i] = index;
        }
    }
    return TRUE;
}

int verticalCheck(int direction, int rowCoord, int colCoord, int ship, int index)
{
    int i;
    if (direction == UP)
    {
        if ((rowCoord - ship + 1) < 0)
        {
            return FALSE;
        }
        for (i = 0; i < ship; i++)
        {
            if ((my_board.board[rowCoord - i][colCoord] != EMPTY_SLOT)||(rowCoord - i < 0))
            {
                return FALSE;
            }
        }
        for (i = 0; i < ship; i++)
        {
            my_board.board[rowCoord - i][colCoord] = index;
        }
    }
    else if (direction == DOWN)
    {
        if ((rowCoord + ship) > my_board.size)
        {
            return FALSE;
        }
        for (i = 0; i < ship; i++)
        {
            if ((my_board.board[rowCoord + i][colCoord] != EMPTY_SLOT)||(rowCoord + i >= my_board.size))
            {
                return FALSE;
            }
        }
        for (i = 0; i < ship; i++)
        {
            my_board.board[rowCoord + i][colCoord] = index;
        }
    }
    return TRUE;
}

void randomizeFleetLocation()
{
    int size = my_board.size;
    int i;
    for (i = 0; i < NUM_OF_SHIPS; i++)
    {
        int vessel = vessels[i], test = 0;
        while (!test)
        {
            int rowCoord = rand() % size;
            int colCoord = rand() % size;
            int randDirection = rand() % NUM_OF_DIRECTIONS;
            if (randDirection % 2 == 0)
            {
                test = verticalCheck(randDirection, rowCoord, colCoord, vessel, i);
            }
            else
            {
                test = horizontalCheck(randDirection, rowCoord, colCoord, vessel, i);
            }
        }
    }
}

void printBoard()
{
    int row, col;
    for (col = 0; col <= my_board.size ; col++)
    {
        if (!col)
        {
            printf("\n%2c", (char)SPACE);
        }
        else
        {
            printf("%d ", col);
        }
    }
    printf("\n");
    for (row = 0; row < my_board.size ; row++)
    {
        for (col = -1; col < my_board.size ; col++)
        {
            if (col == -1)
            {
                printf("%c ", (char)(row+MINIMAL_ROW));
            }
            else
            {
                int value = my_board.board[row][col];
                if (value == SUCCESSFUL_HIT)
                {
                    printf("%c ", X);
                } else if (value == MISSED_HIT)
                {
                    printf("%c ", O);
                } else
                {
                    printf("%c ", UNDER_SCORE);
                }
            }
        }
        printf("\n");
    }
}

void initializeHelper(int size, int **board)
{
    int col = 0, row = 0;
    for (row = 0; row < size; ++row)
    {
        for (col = 0; col < size; ++col)
        {
            board[row][col] = EMPTY_SLOT;
        }
    }
}

Board* initializeBoard(int size)
{
    int **board = (int **) malloc(size * sizeof(int*));
    int row;
    for (row = 0; row < size; row++)
    {
        board[row] = (int *) malloc(size * sizeof(int));
    }
    initializeHelper(size, board);
    Board *my_ptr;
    my_ptr = (Board *) malloc(sizeof(Board));
    *my_ptr = my_board;
    my_board.size = size;
    my_board.board = board;
    randomizeFleetLocation();
    return my_ptr;
}

int hit(int column, int row){
    if ((column < my_board.size) && (column >= 0) && (row < my_board.size) && (row >= 0))
    {
        int hitLocation = my_board.board[row][column];
        if (hitLocation == EMPTY_SLOT)
        {
            my_board.board[row][column] = MISSED_HIT;
            return MISSED_HIT;
        }
        else if ((hitLocation >= 0) && (hitLocation < NUM_OF_SHIPS))
        {
            my_board.board[row][column] = SUCCESSFUL_HIT;
            vessels[hitLocation]--;
            if (vessels[hitLocation] == 0)
            {
                return DEAD_SHIP;
            }
            return SUCCESSFUL_HIT;
        }
    }
    return FALSE;
}

void freeBoard(Board *my_board)
{
    int i;
    for (i = 0; i < (*my_board).size; i++)
    {
        free((*my_board).board[i]);
    }
    free((*my_board).board);
    free(my_board);
}

int isGameOver()
{
    int i;
    for (i = 0; i < NUM_OF_SHIPS; i++)
    {
        if (vessels[i] != 0)
        {
            return FALSE;
        }
    }
    return TRUE;
}