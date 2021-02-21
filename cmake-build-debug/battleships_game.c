
#include <stdio.h>
#include <memory.h>
#include "battleships.h"

#define MINIMAL_BOARD_SIZE 5
#define MAXIMAL_BOARD_SIZE 26

#define ENTER_COOR "Enter coordinates: "
#define INVALID_INPUT_MSG "Invalid move, try again. "
#define INVALID_SIZE "Error, invalid board size or input."
#define INVALID_INPUT 0
#define READY_TO_PLAY "Ready to play!"
#define MISS "Miss."
#define HIT "Hit!"
#define HIT_N_SUNK "Hit and sunk!"
#define GAME_OVER 1
#define GAME_OVER_MSG "Game over"
#define EXIT "exit"



//TODO:
//TODO 2. the fuck is valgrind
//TODO 4. the fuck is 'return value that's different than 0'

static Board my_board;
static int isExit = 0;



void messageManager(int result)
{
    switch (result)
    {
        case INVALID_INPUT:
            fprintf(stderr, "%s\n", INVALID_INPUT_MSG);
            printf("%s", ENTER_COOR);
            break;
        case MISSED_HIT:
            printf("%s", MISS);
            break;
        case SUCCESSFUL_HIT:
            printf("%s", HIT);
            break;
        case DEAD_SHIP:
            printf("%s\n", HIT_N_SUNK);
            break;
        case GAME_OVER:
            printf("%s", GAME_OVER_MSG);
            break;
        default:
            break;
    }
}

void receiveHitInput()
{
    char input[5];
    int validMove = FALSE;
    printf("%s", ENTER_COOR);
    while (!validMove)
    {
        int check1 = scanf("%s", input);
        if (strlen(input) == 4)
        {
            if (!strcmp(input, EXIT))
            {
                isExit = TRUE;
                return;
            }
        }
        else
        {
            char space, row;
            int col;
            if (strlen(input) != 1)
            {
                messageManager(FALSE);
            }
            row = input[0];
            int check2 = scanf("%c", &space);
            int check3 = scanf("%d", &col);
            if ((check1) && (check2) && (check3) && ((int)space == SPACE))
            {
                int intRow = ((int)row-MINIMAL_ROW);
                int rightCol = col - 1;
                int hitTry = hit(rightCol, intRow);
                if (hitTry)
                {
                    validMove = TRUE;
                }
                messageManager(hitTry);
            }
        }
    }
}


void runGame()
{
    int gameIsOver = isGameOver();
    while ((!gameIsOver) && (!isExit))
    {
        receiveHitInput();
        printBoard();
        gameIsOver = isGameOver();
    }
}

/**
 * main function- receives size input and runs the game
 */
int main()
{
    int size, check;
    check = scanf("%d", &size);
    if ((check) && (size >= MINIMAL_BOARD_SIZE) && (size <= MAXIMAL_BOARD_SIZE))
    {
        Board *my_ptr;
        my_ptr = initializeBoard(size);
        *my_ptr = my_board;
        printf("%s\n", READY_TO_PLAY);
        runGame();
        messageManager(GAME_OVER);
        freeBoard(my_ptr);
    }
    else
    {
        fprintf(stderr, "%s", INVALID_SIZE);
        return 1;
    }
    return 0;
}