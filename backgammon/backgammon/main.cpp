#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h> 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <string>

#define PLAYER1_SYM '1'
#define PLAYER2_SYM '2'
#define BLANK       '-'

using namespace std;

void openingRoll(int* whoStarts);
void setPawnsDefault(struct GameState* gameState);
void printMenu(struct GameState* gameState);
void printFieldHighlights(int x, bool highlight[24]);
void printBoard(struct GameState* gameState, bool highlight[24]);
void fieldDecryption(int* field);
int getNumericInput(struct GameState* gameState, int field, int pawn, bool highlight[24], int whoStarts);
void clearScreen();
void highlightFields(char x, struct GameState* gameState, bool highlight[24]);
void undoHighlight(char x, struct GameState* gameState, bool highlight[24]);
void saveGameState(const char* filename, struct GameState* gameState);
void loadGameState(const char* filename, struct GameState* gameState);
int isFileEmpty(const char* filename, struct GameState* gameState);
void ifDeadPawns(int field, int pawn, struct GameState* gameState, bool highlight[24], int whoStarts);
int rollingDie(struct GameState* gameState);
void endingMove(int field, int pawn, struct GameState* gameState, bool highlight[24], int nextPlayer, int whoStarts);
int pawnInput(int player, string board, struct GameState* gameState, int pawn, int field);
int enterFieldNumber(int field, struct GameState* gameState, bool highlight[24], int pawn, int whoStarts);
void endGame(struct GameState* gameState);
void playerMovement(int field, int pawn, struct GameState* gameState, bool highlight[24], int whoStarts);
void printMenuChoice();
char getInput();
void entryMenuChoice(int field, int pawn, struct GameState* gameState, bool highlight[24], int whoStarts);

struct GameState {
    char topBoard[12][5];
    char bottomBoard[12][5];
    int whoseTurn;
    int p1DeadPawns;
    int p2DeadPawns;
    int p1BornPawns;
    int p2BornPawns;
};

void openingRoll(int* whoStarts) {
    int rollOne = rand() % 6 + 1;
    int rollTwo = rand() % 6 + 1;
    if (rollOne > rollTwo) {
        (*whoStarts) = 1;
    }
    else if (rollOne == rollTwo) {
        openingRoll(whoStarts);
    }
    else {
        (*whoStarts) = 2;
    }
}

void setPawnsDefault(struct GameState* gameState) {
    gameState->p1DeadPawns = 0;
    gameState->p2DeadPawns = 0;
    gameState->p1BornPawns = 0;
    gameState->p2BornPawns = 0;
    //two dimensional array
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 12; i++) {
            gameState->topBoard[i][j] = BLANK;
            if (i == 0 || (i == 11 && j < 2)) {
                gameState->topBoard[i][j] = PLAYER1_SYM;
            }
            if ((i == 4 && j < 3) || i == 6) {
                gameState->topBoard[i][j] = PLAYER2_SYM;
            }
        }
    }
    printf("\n");
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 12; i++) {
            gameState->bottomBoard[i][j] = BLANK;
            if (i == 0 || (i == 11 && j > 2)) {
                gameState->bottomBoard[i][j] = PLAYER2_SYM;
            }
            if ((i == 4 && j > 1) || i == 6) {
                gameState->bottomBoard[i][j] = PLAYER1_SYM;
            }
        }
    }
}

void printMenu(struct GameState* gameState) {
    printf("     PRESS [S] AND ENTER TO SAVE GAME STATE   \n");
    printf("  --------------------------------------------\n");
    printf("  > PLA1 - bornPawns: [%d] - deadPawns: [%d] <\n\n", gameState->p1BornPawns, gameState->p1DeadPawns);
    printf("  > PLA2 - bornPawns: [%d] - deadPawns: [%d] <\n", gameState->p2BornPawns, gameState->p2DeadPawns);
    printf("  --------------------------------------------\n\n");
}

void printFieldHighlights(int x, bool highlight[24]) {
    if (x == 1) {
        printf("  ");
        for (int i = 0; i <= 5; i++) {
            if (highlight[i] == true) {
                printf("  #");
            }
            else {
                printf("   ");
            }
        }
        printf("     ");
        for (int i = 6; i <= 11; i++) {
            if (highlight[i] == true) {
                printf("  #");
            }
            else {
                printf("   ");
            }
        }
        printf(" \n");
    }

    else if (x == 2) {
        printf("\n  ");
        for (int i = 12; i <= 17; i++) {
            if (highlight[i] == true) {
                printf("  #");
            }
            else {
                printf("   ");
            }
        }
        printf("     ");
        for (int i = 18; i <= 23; i++) {
            if (highlight[i] == true) {
                printf("  #");
            }
            else {
                printf("   ");
            }
        }
        printf(" \n");
    }
}

void printBoard(struct GameState* gameState, bool highlight[24]) {
    printMenu(gameState);
    printFieldHighlights(1, highlight);
    printf("   13 14 15 16 17 18      19 20 21 22 23 24  \n");//3 5 1; every number print space; if highlight[field] = true print [#] if false print #
    printf("  +-----------------------------------------+\n");
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 12; i++) {
            if (i == 0) {
                printf("%d | ", j + 1);
            }
            if (i == 11 || i == 5) {
                printf("%c", gameState->topBoard[i][j]);
            }
            else {
                printf("%c  ", gameState->topBoard[i][j]);
            }
            if (i == 11) {
                printf(" | %d", j + 1);
            }
            if (i == 5) {
                printf(" |   | ");
            }
        }
        printf("\n");
    }
    printf("  |                  | B |                  |\n");
    printf("  |                  | A |                  |\n");
    printf("  |                  | R |                  |\n");
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 12; i++) {
            if (i == 0) {
                printf("%d | ", 5 - j);
            }
            if (i == 11 || i == 5) {
                printf("%c", gameState->bottomBoard[i][j]);
            }
            else {
                printf("%c  ", gameState->bottomBoard[i][j]);
            }
            if (i == 11) {
                printf(" | %d", 5 - j);
            }
            if (i == 5) {
                printf(" |   | ");
            }
        }
        printf("\n");
    }
    printf("  +-----------------------------------------+\n");
    printf("   12 11 10  9  8  7       6  5  4  3  2  1  ");
    printFieldHighlights(2, highlight);
    printf("\n");
}

void fieldDecryption(int *field) {
    if (*field <= 24 && *field >= 13) {
        *field -= 13;
    }
    else if (*field <= 12 && *field >= 1) {
        *field -= 12;
        if (*field < 0) {
            *field = -*field;
        }
    }
}

int getNumericInput(struct GameState* gameState, int field, int pawn, bool highlight[24], int whoStarts) {
    char input[3]; // We need space for two digits and the null terminator
    int digit;

    fgets(input, sizeof(input), stdin); // Read input as a string

    // Check if the input is 's'
    if (input[0] == 's' || input[0] == 'S' && (input[1] == '\n' || input[1] == '\0')) {
        printf("Saving the game...\n");
        saveGameState("game_state.bin", gameState);
        printf("[Q] - close app\n");
        printf("[R] - play again\n");
        printf("Choose next action: ");
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'Q' || input[0] == 'q' && (input[1] == '\n' || input[1] == '\0')) {
            exit(0);
        }
        else if (input[0] == 'R' || input[0] == 'r' && (input[1] == '\n' || input[1] == '\0')) {
            clearScreen();
            printMenuChoice();
            entryMenuChoice(field, pawn, gameState, highlight, whoStarts);
        }
    }

    // Clear the input buffer
    if (input[strlen(input) - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }

    // Convert string to integer
    digit = atoi(input);

    // Check if the input is within the double-digit range
    if (digit >= 1 && digit <= 24) {
        return digit;
    }
    else {
        return -1;
    }
}

void clearScreen() {
    system("cls");
}

void highlightFields(char x, struct GameState* gameState, bool highlight[24]) {
    for (int i = 0; i <= 11; i++) {
        if (gameState->topBoard[i][0] == x) {
            highlight[i] = true;
        }
        if (gameState->bottomBoard[i][4] == x) {
            highlight[i+12] = true;
        }
    }
}

void undoHighlight(char x, struct GameState* gameState, bool highlight[24]) {
    for (int i = 0; i <= 11; i++) {
        if (gameState->topBoard[i][0] == x) {
            highlight[i] = false;
        }
        if (gameState->bottomBoard[i][4] == x) {
            highlight[i+12] = false;
        }
    }
}

void saveGameState(const char* filename, struct GameState* gameState) {
    FILE* file = fopen(filename, "wb"); // Open file for writing in binary mode

    if (file != NULL) {
        // Write the entire game state structure to the file
        fwrite(gameState, sizeof(struct GameState), 1, file);
        fclose(file);
    }
    else {
        printf("Failed to open file for writing.\n");
    }
}

void loadGameState(const char* filename, struct GameState* gameState) {
    FILE* file = fopen(filename, "rb"); // Open file for reading in binary mode

    if (file != NULL) {
        // Read the entire game state structure from the file
        fread(gameState, sizeof(struct GameState), 1, file);
        fclose(file);
    }
    else {
        printf("Failed to open file for reading.\n");
    }
}

int isFileEmpty(const char* filename, struct GameState* gameState) {
    FILE* file = fopen(filename, "r"); // Open the file in read mode
    if (file == NULL) {
        perror("Error opening file"); // Handle file opening error
        return -1;
    }

    // Move the file pointer to the end of the file
    fseek(file, 0, SEEK_END);

    // Get the position of the file pointer, which indicates the file size
    long size = ftell(file);

    fclose(file); // Close the file

    // Check if the file size is zero
    if (size == 0) {
        setPawnsDefault(gameState); // File is empty

    }
    else {
        loadGameState("game_state.bin", gameState); // File is not empty

    }
}

void ifDeadPawns(int field, int pawn, struct GameState* gameState, bool highlight[24], int whoStarts) {
    if (gameState->p1DeadPawns > 0 && gameState->whoseTurn == 1) {
        gameState->whoseTurn = 10;
        playerMovement(field, pawn, gameState, highlight, whoStarts);
    }
    if (gameState->p2DeadPawns > 0 && gameState->whoseTurn == 2) {
        gameState->whoseTurn = 20;
        playerMovement(field, pawn, gameState, highlight, whoStarts);
    }
}

int rollingDie(struct GameState* gameState) {
    int x;
    x = rand() % 6 + 1;
    printf("Player %d rolled %d\n", gameState->whoseTurn, x);
    return x;
}

int nextPlayer(struct GameState* gameState) {
    if (gameState->whoseTurn == 1) {
        gameState->whoseTurn = 2;
        return gameState->whoseTurn;
    }
    else if (gameState->whoseTurn == 2) {
        gameState->whoseTurn = 1;
        return gameState->whoseTurn;
    }
}

void endingMove(int field, int pawn, struct GameState* gameState, bool highlight[24], int nextPlayer, int whoStarts) {
    clearScreen();
    printBoard(gameState, highlight);
    gameState->whoseTurn = nextPlayer;
    playerMovement(field, pawn, gameState, highlight, whoStarts);
}

int pawnInput(int player, string board, struct GameState* gameState, int pawn, int field) {
    // player 1 - player = 1; 
    // player 2 - player = 2; 
    // topboard - board = 'top';
    // bottomboard - board = 'bot';
    if (board == "bottom") {
        for (int j = 0; j < 5; j++) {
            if (gameState->bottomBoard[field][j] == player) {
                pawn = j;
                break; // Exit loop once pawn is found
            }
        }
    }
    if (board == "top") {
        for (int j = 4; j >= 0; j--) {
            if (gameState->topBoard[field][j] == player) {
                pawn = j;
                break; // Exit loop once pawn is found
            }
        }
    }
    return pawn;
}

int enterFieldNumber(int field, struct GameState* gameState, bool highlight[24], int pawn, int whoStarts) {
    printf("Enter move info...");
    fflush(stdout);
    Sleep(1);
    printf("\rEnter field number: ");
    field = getNumericInput(gameState, field, pawn, highlight, whoStarts);
    return field;
}

void endGame(struct GameState* gameState) {
    if (gameState->p1BornPawns == 15 || gameState->p2BornPawns == 15) {
        gameState->whoseTurn = nextPlayer(gameState);
        clearScreen();
        printf("Player %d won the game!!!", gameState->whoseTurn);
        fflush(stdout);
        Sleep(5);
        exit(0);
    }
}

void playerMovement(int field, int pawn, struct GameState* gameState, bool highlight[24], int whoStarts) {
    int dieRoll;
    int nextPos;
    endGame(gameState);
    ifDeadPawns(field, pawn, gameState, highlight, whoStarts);
    //PLAYER ONE MOVEMENT
    if (gameState->whoseTurn == 1) {
        highlightFields(PLAYER1_SYM, gameState, highlight);
        clearScreen();
        printBoard(gameState, highlight);
        dieRoll = rollingDie(gameState);
    chooseAgain1:
        field = enterFieldNumber(field, gameState, highlight, pawn, whoStarts);
        undoHighlight(PLAYER1_SYM, gameState, highlight); // only after entering field number

        if (field != -1) {
            //TOP BOARD
            if (field <= 24 && field >= 13) {
                fieldDecryption(&field);
                pawn = pawnInput(PLAYER1_SYM, "top", gameState, pawn, field);

                //PRIME DENIAL
                if (field - dieRoll >= -1) {
                    for (int i = 0; i < dieRoll; i++) {
                        if (gameState->topBoard[field - dieRoll + i][0] == PLAYER2_SYM && gameState->topBoard[field - dieRoll + i][1] == PLAYER2_SYM && gameState->topBoard[field - dieRoll + i + 1][0] == PLAYER2_SYM && gameState->topBoard[field - dieRoll + i + 1][1] == PLAYER2_SYM) {
                            printf("A prime is blocking the move. Choose again.\n");
                            goto chooseAgain1;
                        }
                    }
                }
                else if (field - dieRoll == -2) {
                    for (int i = 0; i < dieRoll; i++) {
                        if (gameState->bottomBoard[0][4] == PLAYER2_SYM && gameState->bottomBoard[0][3] == PLAYER2_SYM && gameState->topBoard[0][0] == PLAYER2_SYM && gameState->topBoard[0][1] == PLAYER2_SYM) {
                            printf("A prime is blocking the move. Choose again.\n");
                            goto chooseAgain1;
                        }
                    }
                }
                else if (field - dieRoll < -2) {
                    for (int i = 0; i < dieRoll; i++) {
                        int delta = -(field - dieRoll + 1);
                        if (gameState->bottomBoard[delta + i][0] == PLAYER2_SYM && gameState->bottomBoard[delta + i][1] == PLAYER2_SYM && gameState->bottomBoard[delta + i + 1][0] == PLAYER2_SYM && gameState->bottomBoard[delta + i + 1][1] == PLAYER2_SYM) {
                            printf("A prime is blocking the move. Choose again.\n");
                            goto chooseAgain1;
                        }
                    }
                }

                //ENEMY ANCHOR DENIAL
                if (gameState->topBoard[field - dieRoll][0] == PLAYER2_SYM && gameState->topBoard[field - dieRoll][1] == PLAYER2_SYM && field - dieRoll >= 0) {
                    printf("An anchor is blocking the move. Choose again.\n");
                    goto chooseAgain1;
                }
                else if (field - dieRoll < 0) {
                    int delta = -(field - dieRoll + 1);
                    if (gameState->bottomBoard[delta][4] == PLAYER2_SYM && gameState->bottomBoard[delta][3] == PLAYER2_SYM) {
                        printf("An anchor is blocking the move. Choose again.\n");
                        goto chooseAgain1;
                    }
                }

                //FULL SELF ANCHOR
                if (gameState->topBoard[field - dieRoll][4] == PLAYER1_SYM) {
                    printf("Cannot move pawn. Destination field is full.\n");
                    goto chooseAgain1;
                }

                //HITTING MECHANIC
                if (gameState->topBoard[field - dieRoll][0] == PLAYER2_SYM && gameState->topBoard[field - dieRoll][1] == BLANK && field - dieRoll >= 0) {
                    gameState->topBoard[field - dieRoll][0] = PLAYER1_SYM;
                    gameState->p2DeadPawns += 1;
                }

                //MOVING FROM TOP BOARD TO BOTTOM BOARD
                else if (field - dieRoll < 0) {
                    int delta = -(field - dieRoll + 1);
                    if (gameState->bottomBoard[delta][4] == PLAYER2_SYM && gameState->bottomBoard[delta][3] == BLANK) {
                        gameState->bottomBoard[delta][4] = PLAYER1_SYM;
                        gameState->p2DeadPawns += 1;
                    }
                    else {
                        gameState->topBoard[field][pawn] = BLANK;
                        for (int j = 4; j >= 0; j--) {
                            if (gameState->bottomBoard[field + delta][j] == BLANK) {
                                nextPos = j;
                                break;
                            }
                        }
                        gameState->bottomBoard[delta][nextPos] = PLAYER1_SYM;
                    }
                }

                // NORMAL MOVEMENT
                else {
                    gameState->topBoard[field][pawn] = BLANK;
                    for (int j = 0; j < 5; j++) {
                        if (gameState->topBoard[field - dieRoll][j] == BLANK) {
                            nextPos = j;
                            break;
                        }
                    }
                    gameState->topBoard[field - dieRoll][nextPos] = PLAYER1_SYM;
                }
            }

            // BOTTOM BOARD
            else if (field <= 12 && field >= 1) {
                fieldDecryption(&field);
                pawn = pawnInput(PLAYER1_SYM, "bottom", gameState, pawn, field);
                //BEARING OFF FOR PLAYER 1
                if (field + dieRoll > 11) {
                    int count = 0;
                    for (int j = 0; j < 5; j++) {
                        for (int i = 6; i <= 11; i++) {
                            if (gameState->bottomBoard[i][j] == PLAYER1_SYM) {
                                count++;
                            }
                        }
                    }
                    if (count == 15) {
                        gameState->p1BornPawns++;
                        gameState->bottomBoard[field][pawn] = BLANK;
                        printf("Player 1 has bore off a pawn.. +1 points!!");
                        Sleep(2);
                        clearScreen();
                        printBoard(gameState, highlight);
                        gameState->whoseTurn = 2;
                        playerMovement(field, pawn, gameState, highlight, whoStarts);
                    }
                    else {
                        printf("\rCan't bear off pawn. Make sure all the pawns are in the enemy home board.\n");
                        goto chooseAgain1;
                    }

                }

                // PRIME DENIAL
                for (int i = 0; i < dieRoll; i++) {
                    if (gameState->bottomBoard[field + dieRoll - i][4] == PLAYER2_SYM && gameState->bottomBoard[field + dieRoll - i][3] == PLAYER2_SYM && gameState->bottomBoard[field + dieRoll - i - 1][4] == PLAYER2_SYM && gameState->bottomBoard[field + dieRoll - i - 1][3] == PLAYER2_SYM) {
                        printf("A prime is blocking the move. Choose again.\n");
                        goto chooseAgain1;
                    }
                }

                //ENEMY ANCHOR DENIAL
                if (gameState->bottomBoard[field + dieRoll][4] == PLAYER2_SYM && gameState->bottomBoard[field + dieRoll][3] == PLAYER2_SYM) {
                    printf("An anchor is blocking the move. Choose again.\n");
                    goto chooseAgain1;
                }

                //FULL SELF ANCHOR
                if (gameState->bottomBoard[field + dieRoll][0] == PLAYER1_SYM) {
                    printf("Cannot move pawn. Destination field is full.\n");
                    goto chooseAgain1;
                }
                    //HITTING MECHANIC
                if (gameState->bottomBoard[field + dieRoll][4] == PLAYER2_SYM && gameState->bottomBoard[field + dieRoll][3] == BLANK) {
                    gameState->bottomBoard[field + dieRoll][4] = PLAYER1_SYM;
                    gameState->p2DeadPawns += 1;
                }

                //NORMAL MOVEMENT IN BOTTOM BOARD
                else {
                    gameState->bottomBoard[field][pawn] = BLANK;
                    for (int j = 4; j >= 0; j--) {
                        if (gameState->bottomBoard[field + dieRoll][j] == BLANK) {
                            nextPos = j;
                            break;
                        }
                    }
                    gameState->bottomBoard[field + dieRoll][nextPos] = PLAYER1_SYM;
                }
            }

            //ERROR MESSAGES WHEN INVALID INPUT FOR FIELD AND PAWN
        }
        else {
            printf("\rInvalid input! Please enter a numeric value.");
        }

        //ENDING MOVE
        endingMove(field, pawn, gameState, highlight, 2, whoStarts);
    }

    //PLAYER TWO MOVEMENT XXXXXXXXXXXXXXXXXX
    else if (gameState->whoseTurn == 2) {
        highlightFields(PLAYER2_SYM, gameState, highlight);

        clearScreen();
        printBoard(gameState, highlight);
        dieRoll = rollingDie(gameState);
    chooseAgain2:
        field = enterFieldNumber(field, gameState, highlight, pawn, whoStarts);
        undoHighlight(PLAYER2_SYM, gameState, highlight);

        if (field != -1) {
            //BOTTOM BOARD
            if (field <= 12 && field >= 1) {
                fieldDecryption(&field);
                pawn = pawnInput(PLAYER2_SYM, "bottom", gameState, pawn, field);
                //PRIME DENIAL
                if (field - dieRoll >= -1) {
                    for (int i = 0; i < dieRoll; i++) {
                        if (gameState->bottomBoard[field - dieRoll + i][0] == PLAYER1_SYM && gameState->bottomBoard[field - dieRoll + i][1] == PLAYER1_SYM && gameState->bottomBoard[field - dieRoll + i + 1][0] == PLAYER1_SYM && gameState->bottomBoard[field - dieRoll + i + 1][1] == PLAYER1_SYM) {
                            printf("A prime is blocking the move. Choose again.\n");
                            goto chooseAgain2;
                        }
                    }
                }
                else if (field - dieRoll == -2) {
                    for (int i = 0; i < dieRoll; i++) {
                        if (gameState->bottomBoard[0][4] == PLAYER1_SYM && gameState->bottomBoard[0][3] == PLAYER1_SYM && gameState->topBoard[0][0] == PLAYER1_SYM && gameState->topBoard[0][1] == PLAYER1_SYM) {
                            printf("A prime is blocking the move. Choose again.\n");
                            goto chooseAgain2;
                        }
                    }
                }
                else if (field - dieRoll < -2) {
                    for (int i = 0; i < dieRoll; i++) {
                        int delta = -(field - dieRoll + 1);
                        if (gameState->topBoard[delta + i][0] == PLAYER1_SYM && gameState->topBoard[delta + i][1] == PLAYER1_SYM && gameState->topBoard[delta + i + 1][0] == PLAYER1_SYM && gameState->topBoard[delta + i + 1][1] == PLAYER1_SYM) {
                            printf("A prime is blocking the move. Choose again.\n");
                            goto chooseAgain2;
                        }
                    }
                }

                //ENEMY ANCHOR DENIAL
                if (gameState->bottomBoard[field - dieRoll][4] == PLAYER1_SYM && gameState->bottomBoard[field - dieRoll][3] == PLAYER1_SYM && field - dieRoll >= 0) {
                    printf("An anchor is blocking the move. Choose again.\n");
                    goto chooseAgain2;
                }
                else if (field - dieRoll < 0) {
                    int delta = -(field - dieRoll + 1);
                    if (gameState->topBoard[delta][0] == PLAYER2_SYM && gameState->topBoard[delta][1] == PLAYER1_SYM) {
                        printf("An anchor is blocking the move. Choose again.\n");
                        goto chooseAgain2;
                    }
                }

                //FULL SELF ANCHOR
                if (gameState->bottomBoard[field - dieRoll][0] == PLAYER2_SYM) {
                    printf("Cannot move pawn. Destination field is full.\n");
                    goto chooseAgain2;
                }

                //HITTING MECHANIC
                if (gameState->bottomBoard[field - dieRoll][4] == PLAYER1_SYM && gameState->bottomBoard[field - dieRoll][3] == BLANK && field - dieRoll >= 0) {
                    gameState->bottomBoard[field - dieRoll][4] = PLAYER2_SYM;
                    gameState->p1DeadPawns += 1;
                }

                //MOVING FROM BOTTOM BOARD TO TOP BOARD
                else if (field - dieRoll < 0) {
                    int delta = -(field - dieRoll + 1);
                    if (gameState->topBoard[delta][0] == PLAYER1_SYM && gameState->topBoard[delta][1] == BLANK) {
                        gameState->topBoard[delta][0] = PLAYER2_SYM;
                        gameState->p1DeadPawns += 1;
                    }
                    else {
                        gameState->bottomBoard[field][pawn] = BLANK;
                        for (int j = 0; j < 5; j++) {
                            if (gameState->topBoard[field + delta][j] == BLANK) {
                                nextPos = j;
                                break;
                            }
                        }
                        gameState->topBoard[delta][nextPos] = PLAYER2_SYM;
                    }

                }

                //NORMAL MOVEMENT
                else {
                    gameState->bottomBoard[field][pawn] = BLANK;
                    for (int j = 4; j >= 0; j--) {
                        if (gameState->bottomBoard[field - dieRoll][j] == BLANK) {
                            nextPos = j;
                            break;
                        }
                    }
                    gameState->bottomBoard[field - dieRoll][nextPos] = PLAYER2_SYM;
                }
            }

            //TOP BOARD
            else if (field <= 24 && field >= 13) {
                fieldDecryption(&field);
                pawn = pawnInput(PLAYER2_SYM, "top", gameState, pawn, field);
                //BEARING OFF FOR PLAYER 2
                if (field + dieRoll > 11) {
                    int count = 0;
                    for (int j = 0; j < 5; j++) {
                        for (int i = 6; i <= 11; i++) {
                            if (gameState->topBoard[i][j] == PLAYER1_SYM) {
                                count++;
                            }
                        }
                    }
                    if (count == 15) {
                        gameState->p2BornPawns++;
                        gameState->topBoard[field][pawn] = BLANK;
                        printf("Player 2 has bore off a pawn.. +1 points!!");
                        Sleep(2);
                        clearScreen();
                        printBoard(gameState, highlight);
                        gameState->whoseTurn = 1;
                        playerMovement(field, pawn, gameState, highlight, whoStarts);
                    }
                    else {
                        printf("\rCan't bear off pawn. Make sure all the pawns are in the enemy home board.\n\n");
                        goto chooseAgain2;
                    }

                }

                //PRIME DENIAL
                for (int i = 0; i < dieRoll; i++) {
                    if (gameState->topBoard[field + dieRoll - i][0] == PLAYER1_SYM && gameState->topBoard[field + dieRoll - i][1] == PLAYER1_SYM && gameState->topBoard[field + dieRoll - i - 1][0] == PLAYER1_SYM && gameState->topBoard[field + dieRoll - i - 1][1] == PLAYER1_SYM) {
                        printf("A prime is blocking the move. Choose again.\n");
                        goto chooseAgain2;
                    }
                }

                //ENEMY ANCHOR DENIAL
                if (gameState->topBoard[field + dieRoll][0] == PLAYER1_SYM && gameState->topBoard[field + dieRoll][1] == PLAYER1_SYM) {
                    printf("An anchor is blocking the move. Choose again.\n");
                    goto chooseAgain2;
                }

                //FULL SELF ANCHOR
                if (gameState->topBoard[field + dieRoll][4] == PLAYER2_SYM) {
                    printf("Cannot move pawn. Destination field is full.\n");
                    goto chooseAgain2;
                }
                //HITTING MECHANIC
                if (gameState->topBoard[field + dieRoll][0] == PLAYER1_SYM && gameState->topBoard[field + dieRoll][1] == BLANK && field + dieRoll <= 24) {
                    gameState->topBoard[field + dieRoll][0] = PLAYER2_SYM;
                    gameState->p1DeadPawns += 1;
                    //goto pOneMoveEnd;
                }

                //NORMAL MOVEMENT IN TOP BOARD
                else {
                    gameState->topBoard[field][pawn] = BLANK;
                    for (int j = 0; j < 5; j++) {
                        if (gameState->topBoard[field + dieRoll][j] == BLANK) {
                            nextPos = j;
                            break;
                        }
                    }
                    gameState->topBoard[field + dieRoll][nextPos] = PLAYER2_SYM;
                }
            }

            //ERROR MESSAGES WHEN INVALID INPUT FOR FIELD AND PAWN
        }
        else {
            printf("\rInvalid input! Please enter a numeric value.");
        }

        //ENDING MOVE
        endingMove(field, pawn, gameState, highlight, 1, whoStarts);
    }
        else if (gameState->whoseTurn == 10) {
            dieRoll = rollingDie(gameState);
            int delta = 12 - dieRoll;
            if (gameState->topBoard[delta][0] == BLANK) {
                gameState->topBoard[delta][0] = PLAYER1_SYM;
                gameState->p1DeadPawns -= 1;
                clearScreen();
                printBoard(gameState, highlight);
                printf("\rPlayer One's pawn was respawned on field number %d\n", 25 - dieRoll);
                fflush(stdout);
                Sleep(2);
                endingMove(field, pawn, gameState, highlight, 2, whoStarts);
            }
            else {
                printf("\rPlayer One's pawn couldn't respawn\n");
                fflush(stdout);
                Sleep(2);
                endingMove(field, pawn, gameState, highlight, 2, whoStarts);
            }

    }

        else if (gameState->whoseTurn == 20) {
            dieRoll = rollingDie(gameState);
            int delta = 12 - dieRoll;
            if (gameState->bottomBoard[delta][4] == BLANK) {
                gameState->bottomBoard[delta][4] = PLAYER2_SYM;
                gameState->p2DeadPawns -= 1;
                clearScreen();
                printBoard(gameState, highlight);
                printf("Player Two's pawn was respawned on field number %d", dieRoll);
                fflush(stdout);
                Sleep(2);
                endingMove(field, pawn, gameState, highlight, 1, whoStarts);
            }
            else {
                printf("Player Two's pawn couldn't respawn");
                fflush(stdout);
                Sleep(2);
                endingMove(field, pawn, gameState, highlight, 1, whoStarts);
            }
    }
}

void printMenuChoice() {
    string text = "[N] - NEW GAME\n[L] - LOAD SAVED GAME";
    // Get the width of the terminal
    int terminalWidth = static_cast<int>(cout.rdbuf()->in_avail());

    // Calculate padding
    int padding = (terminalWidth - text.length()) / 2;

    // Print padding followed by text
    for (int i = 0; i < padding; ++i) {
        cout << " ";
    }
    cout << text << endl;
}

char getInput() {
    char input;
    input = _getch();
    if (input != 110 && input != 108 && input != 78 && input != 76) {
        printf("Wrong button pressed.");
    }
    else {
        return input;
    }
}

void entryMenuChoice(int field, int pawn, struct GameState* gameState, bool highlight[24], int whoStarts) {
    int input = getInput();
    if (input == 108 || input == 76) {  // l
        clearScreen();
        loadGameState("game_state.bin", gameState);
        printBoard(gameState, highlight);
        playerMovement(field, pawn, gameState, highlight, whoStarts);
    }   
    else if (input == 110 || input == 78) { // n
        clearScreen();
        setPawnsDefault(gameState);
        openingRoll(&whoStarts);
        gameState->whoseTurn = whoStarts;
        printBoard(gameState, highlight);
        playerMovement(field, pawn, gameState, highlight, whoStarts);
    }
}

int main() {
    int whoStarts = 0; //  1 - player 1 starts, 2 - player 2 starts
    bool highlight[24];
    int field = 0;
    int pawn = 0;
    struct GameState gameState;

    srand(time(NULL));
    printMenuChoice();
    entryMenuChoice(field, pawn, &gameState, highlight, whoStarts);

    return 0;
}