#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h> 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

using namespace std;


//kazdy gracz ma po 16 pionkow 
//pionki numeruje w aplikacji od home boarda od dolu do gory


//niektorzy u kolaka robili wszystko w jednej strukturze


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

void setPawnsDefault(char topBoard[][5], char bottomBoard[][5]) {
    //two dimensional array
    char p1 = '1';
    char p2 = '2';
    char sup = '-';
    char sdown = '-';
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 12; i++) {
            topBoard[i][j] = sdown;
            if (i == 0 || (i == 11 && j < 2)) {
                topBoard[i][j] = p1;
            }
            if ((i == 4 && j < 3) || i == 6) {
                topBoard[i][j] = p2;
            }
        }
    }


    printf("\n");

    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 12; i++) {
            bottomBoard[i][j] = sup;
            if (i == 0 || (i == 11 && j > 2)) {
                bottomBoard[i][j] = p2;
            }
            if ((i == 4 && j > 1) || i == 6) {
                bottomBoard[i][j] = p1;
            }
        }
    }
}

void printMenu(int p1DeadPawns, int p2DeadPawns, int p1Points, int p2Points) {
    printf("  > PLA1 - bornPawns: [%d] - deadPawns: [%d] <\n\n", p1Points, p1DeadPawns);
    printf("  > PLA2 - bornPawns: [%d] - deadPawns: [%d] <\n\n", p2Points, p2DeadPawns);
}

void printFieldHighlights(int x, bool highlight[24]) {
    if (x == 1) {
        printf("    ");
        for (int i = 13; i <= 18; i++) {
            if (highlight[i] == 1) {
                printf("_ ");
            }
            else {
                printf("  ");
            }
        }
        printf("      ");
        for (int i = 19; i <= 24; i++) {
            if (highlight[i] == 1) {
                printf("_ ");
            }
            else {
                printf("  ");
            }
        }
        printf(" \n");
    }

    else if (x == 2) {
        printf("\n    ");
        for (int i = 12; i <= 7; i--) {
            if (highlight[i] == 1) {
                printf("_ ");
            }
            else {
                printf("  ");
            }
        }
        printf("      ");
        for (int i = 6; i <= 1; i--) {
            if (highlight[i] == 1) {
                printf("_ ");
            }
            else {
                printf("  ");
            }
        }
        printf(" ");
    }
}

void printBoard(char topBoard[][5], char bottomBoard[][5], int p1DeadPawns, int p2DeadPawns, int p1Points, int p2Points, bool highlight[24]) {
    printMenu(p1DeadPawns, p2DeadPawns, p1Points, p2Points);
    printFieldHighlights(1, highlight);
    printf("   13 14 15 16 17 18      19 20 21 22 23 24  \n");//3 5 1; every number print space; if highlight[field] = true print [#] if false print #
    printf("  +-----------------------------------------+\n");
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < 12; i++) {
            if (i == 0) {
                printf("%d | ", j + 1);
            }
            if (i == 11 || i == 5) {
                printf("%c", topBoard[i][j]);
            }
            else {
                printf("%c  ", topBoard[i][j]);
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
                printf("%c", bottomBoard[i][j]);
            }
            else {
                printf("%c  ", bottomBoard[i][j]);
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
    printf("   12 11 10  9  8  7       6  5  4  3  2  1  \n\n");
    printFieldHighlights(2, highlight);
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

// void pawnDecryption(int field, int pawn) {
//     if (field <= 24 && field >= 13) {
//         pawn -= 1;
//     }
//     else if (field <= 12 && field >= 1) {
//         pawn -= 5;
//         if (pawn < 0) {
//             pawn = -pawn;
//         }
//     }
// }

int getNumericInput() {
    char input[3]; // We need space for two digits and the null terminator
    int digit;

    fgets(input, sizeof(input), stdin); // Read input as a string

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

// void nextMatchQuestion() {
//     //after a player has won a match both the players get a question if they want to continue and go for BEST OF 3
//     if (p1Points == 1 || p2Points == 1) {
//         char p1a, p2a;
//         clearScreen();
//         printf("\rYou can either finish your game here or continue to best of 3!!");
//         fflush(stdout); 
//         Sleep(2);
//         printf("\rBoth players have to agree to the best of 3.");
//         fflush(stdout); 
//         Sleep(2);
//         printf("\rDoes player 1 agree to the best of 3?");
//         fflush(stdout); 
//         Sleep(1);
//         printf("\rClick Y or N: ");;
//         scanf("%s", p1a);
//         fflush(stdout); 
//         Sleep(2);
//         printf("\rDoes player 2 agree to the best of 3?");
//         fflush(stdout); 
//         Sleep(1);
//         printf("\rClick Y or N: ");;
//         scanf("%s", p2a);
//     }

//     if (p1a == 'y' && p2a == 'y') {
//         printBoard(topBoard, bottomBoard);
//         playerMovement(field, pawn, topBoard, bottomBoard, whoStarts, p1DeadPawns, p2DeadPawns);
//     }

// }

void highlightFields(char x, char topBoard[][5], char bottomBoard[][5], bool highlight[24]) {
    int field;
    for (int i = 0; i <= 11; i++) {
        if (topBoard[i][0] == x) {
            field = i;
            fieldDecryption(&field);
            highlight[field] = true;
        }
    }

    for (int i = 0; i <= 11; i++) {
        if (bottomBoard[i][4] == x) {
            field = i;
            fieldDecryption(&field);
            highlight[field] = true;
        }
    }
}

void undoHighlight(char x, char topBoard[][5], char bottomBoard[][5], bool highlight[24]) {
    int field;
    for (int i = 0; i <= 11; i++) {
        if (topBoard[i][0] == x) {
            field = i;
            fieldDecryption(&field);
            highlight[field] = false;
        }
    }

    for (int i = 0; i <= 11; i++) {
        if (bottomBoard[i][4] == x) {
            field = i;
            fieldDecryption(&field);
            highlight[field] = false;
        }
    }
}

/*void forceHit() {

}*/


//movement for player 1 'O'
void playerMovement(int field, int pawn, char topBoard[][5], char bottomBoard[][5], int whoseTurn, int p1DeadPawns, int p2DeadPawns, int p1Points, int p2Points, bool highlight[24]) {
    int dieRoll;
    int nextPos;
    char p1 = '1';
    char p2 = '2';
    if (p1DeadPawns > 0 && whoseTurn == 1) {
        playerMovement(field, pawn, topBoard, bottomBoard, 10, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
    }
    if (p2DeadPawns > 0 && whoseTurn == 2) {
        playerMovement(field, pawn, topBoard, bottomBoard, 20, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
    }
    //PLAYER ONE MOVEMENT OOOOOOOOOOOOO
    if (whoseTurn == 1) {
        dieRoll = rand() % 6 + 1;
        highlightFields(p1, topBoard, bottomBoard, highlight);
        clearScreen();
        printBoard(topBoard, bottomBoard, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
        printf("Player 1 rolled [%d]\n", dieRoll);
        Sleep(3);
    chooseAgain1:
        printf("Enter move info...");
        fflush(stdout);
        Sleep(1);
        printf("\rEnter field number: ");
        field = getNumericInput();
        undoHighlight(p1, topBoard, bottomBoard, highlight);
        if (field != -1) {
            //TOP BOARD
            if (field <= 24 && field >= 13) {
                //pawnDecryption(&field, &pawn);
                fieldDecryption(&field);
                for (int j = 4; j >= 0; j--) {
                    if (topBoard[field][j] == '1') {
                        pawn = j;
                        break; // Exit loop once pawn is found
                    }
                }
                Sleep(2);

                //PRIME DENIAL
                if (field - dieRoll >= -1) {
                    for (int i = 0; i < dieRoll; i++) {
                        if (topBoard[field - dieRoll + i][0] == '2' && topBoard[field - dieRoll + i][1] == '2' && topBoard[field - dieRoll + i + 1][0] == '2' && topBoard[field - dieRoll + i + 1][1] == '2') {
                            printf("A prime is blocking the move. Choose again.\n");
                            goto chooseAgain1;
                        }
                    }
                }
                else if (field - dieRoll == -2) {
                    for (int i = 0; i < dieRoll; i++) {
                        if (bottomBoard[0][4] == '2' && bottomBoard[0][3] == '2' && topBoard[0][0] == '2' && topBoard[0][1] == '2') {
                            printf("A prime is blocking the move. Choose again.\n");
                            goto chooseAgain1;
                        }
                    }
                }
                else if (field - dieRoll < -2) {
                    for (int i = 0; i < dieRoll; i++) {
                        int delta = -(field - dieRoll + 1);
                        if (bottomBoard[delta + i][0] == '2' && bottomBoard[delta + i][1] == '2' && bottomBoard[delta + i + 1][0] == '2' && bottomBoard[delta + i + 1][1] == '2') {
                            printf("A prime is blocking the move. Choose again.\n");
                            goto chooseAgain1;
                        }
                    }
                }

                //ENEMY ANCHOR DENIAL
                if (topBoard[field - dieRoll][0] == '2' && topBoard[field - dieRoll][1] == '2' && field - dieRoll >= 0) {
                    printf("An anchor is blocking the move. Choose again.\n");
                    goto chooseAgain1;
                }
                else if (field - dieRoll < 0) {
                    int delta = -(field - dieRoll + 1);
                    if (bottomBoard[delta][4] == '2' && bottomBoard[delta][3] == '2') {
                        printf("An anchor is blocking the move. Choose again.\n");
                        goto chooseAgain1;
                    }
                }

                //FULL SELF ANCHOR
                if (topBoard[field - dieRoll][4] == '1') {
                    printf("Cannot move pawn. Destination field is full.\n");
                    goto chooseAgain1;
                }

                //CHOOSING SPACE DENIAL, CHOOSING WRONG TEAM DENIAL, CHOOSING A PAWN THATS NOT ON THE TOP OF THE STACK DENIAL
                //if (topBoard[field][pawn + 1] != '1' && topBoard[field][pawn] != '-' && topBoard[field][pawn] != '2') {
                    //HITTING MECHANIC
                    if (topBoard[field - dieRoll][0] == '2' && topBoard[field - dieRoll][1] == '-' && field - dieRoll >= 0) {
                        topBoard[field - dieRoll][0] = '1';
                        p2DeadPawns += 1;
                        //goto pOneMoveEnd;
                    }

                    //MOVING FROM TOP BOARD TO BOTTOM BOARD
                    else if (field - dieRoll < 0) {
                        int delta = -(field - dieRoll + 1);
                        if (bottomBoard[delta][4] == '2' && bottomBoard[delta][3] == '-') {
                            bottomBoard[delta][4] = '1';
                            p2DeadPawns += 1;
                        }
                        else {
                            topBoard[field][pawn] = '-';
                            for (int j = 4; j >= 0; j--) {
                                if (bottomBoard[field + delta][j] == '-') {
                                    nextPos = j;
                                    break;
                                }
                            }
                            bottomBoard[delta][nextPos] = '1';
                        }
                    }

                    // NORMAL MOVEMENT
                    else {
                        topBoard[field][pawn] = '-';
                        for (int j = 0; j < 5; j++) {
                            if (topBoard[field - dieRoll][j] == '-') {
                                nextPos = j;
                                break;
                            }
                        }
                        topBoard[field - dieRoll][nextPos] = '1';
                    }
                //}
                //else {
                    //printf("Illegal pawn choice. Choose again.\n");
                    //goto chooseAgain1;
                //}

            }

            // BOTTOM BOARD
            else if (field <= 12 && field >= 1) {
                //pawnDecryption(&field, &pawn)
                fieldDecryption(&field);
                for (int j = 0; j < 5; j++) {
                    if (bottomBoard[field][j] == '1') {
                        pawn = j;
                        break; // Exit loop once pawn is found
                    }
                }

                //BEARING OFF FOR PLAYER 1
                if (field + dieRoll > 11) {
                    int count = 0;
                    for (int j = 0; j < 5; j++) {
                        for (int i = 6; i <= 11; i++) {
                            if (bottomBoard[i][j] == '1') {
                                count++;
                            }
                        }
                    }
                    if (count == 15) {
                        p1Points++;
                        bottomBoard[field][pawn] = '-';
                        printf("Player 1 has bore off a pawn.. +1 points!!");
                        Sleep(2);
                        clearScreen();
                        printBoard(topBoard, bottomBoard, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
                        playerMovement(field, pawn, topBoard, bottomBoard, 2, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
                    }
                    else {
                        printf("Can't bear off pawn. Make sure all the pawns are in the enemy home board.\n");
                        goto chooseAgain1;
                    }

                }

                // PRIME DENIAL
                for (int i = 0; i < dieRoll; i++) {
                    if (bottomBoard[field + dieRoll - i][4] == '2' && bottomBoard[field + dieRoll - i][3] == '2' && bottomBoard[field + dieRoll - i - 1][4] == '2' && bottomBoard[field + dieRoll - i - 1][3] == '2') {
                        printf("A prime is blocking the move. Choose again.\n");
                        goto chooseAgain1;
                    }
                }

                //ENEMY ANCHOR DENIAL
                if (bottomBoard[field + dieRoll][4] == '2' && bottomBoard[field + dieRoll][3] == '2') {
                    printf("An anchor is blocking the move. Choose again.\n");
                    goto chooseAgain1;
                }

                //FULL SELF ANCHOR
                if (bottomBoard[field + dieRoll][0] == '1') {
                    printf("Cannot move pawn. Destination field is full.\n");
                    goto chooseAgain1;
                }

                //CHOOSING SPACE DENIAL, CHOOSING WRONG TEAM DENIAL, CHOOSING A PAWN THATS NOT ON THE TOP OF THE STACK DENIAL
                //if (bottomBoard[field][pawn - 1] != '1' && bottomBoard[field][pawn] != '-' && bottomBoard[field][pawn] != '2') {
                    //HITTING MECHANIC
                if (bottomBoard[field + dieRoll][4] == '2' && bottomBoard[field + dieRoll][3] == '-') {
                    bottomBoard[field + dieRoll][4] = '1';
                    p2DeadPawns += 1;
                    //goto pOneMoveEnd;
                }

                    //NORMAL MOVEMENT IN BOTTOM BOARD
                else {
                    bottomBoard[field][pawn] = '-';
                    for (int j = 4; j >= 0; j--) {
                        if (bottomBoard[field + dieRoll][j] == '-') {
                            nextPos = j;
                            break;
                        }
                    }
                    bottomBoard[field + dieRoll][nextPos] = '1';
                }
            //}
                //else {
                    //printf("Illegal pawn choice. Choose again.\n");
                    //goto chooseAgain1;
                //}
        }

            //ERROR MESSAGES WHEN INVALID INPUT FOR FIELD AND PAWN
        }
        else {
            printf("\rInvalid input! Please enter a numeric value.");
        }

        //ENDING MOVE
        //pOneMoveEnd:
        clearScreen();
        printBoard(topBoard, bottomBoard, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
        playerMovement(field, pawn, topBoard, bottomBoard, 2, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
    }

    //PLAYER TWO MOVEMENT XXXXXXXXXXXXXXXXXX
    else if (whoseTurn == 2) {
        dieRoll = rand() % 6 + 1;
        highlightFields(p2, topBoard, bottomBoard, highlight);
        clearScreen();
        printBoard(topBoard, bottomBoard, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
        printf("Player 2 rolled [%d]\n", dieRoll);
        Sleep(3);
    chooseAgain2:
        printf("Enter move info...");
        fflush(stdout);
        Sleep(1);
        printf("\rEnter field number: ");
        field = getNumericInput();
        undoHighlight(p2, topBoard, bottomBoard, highlight);
        if (field != -1) {
            //BOTTOM BOARD
            if (field <= 12 && field >= 1) {
                //pawnDecryption(&field, &pawn);


                fieldDecryption(&field);
                for (int j = 0; j < 5; j++) {
                    if (bottomBoard[field][j] == '2') {
                        pawn = j;
                        break; // Exit loop once pawn is found
                    }
                }

                //PRIME DENIAL
                if (field - dieRoll >= -1) {
                    for (int i = 0; i < dieRoll; i++) {
                        if (bottomBoard[field - dieRoll + i][0] == '1' && bottomBoard[field - dieRoll + i][1] == '1' && bottomBoard[field - dieRoll + i + 1][0] == '1' && bottomBoard[field - dieRoll + i + 1][1] == '1') {
                            printf("A prime is blocking the move. Choose again.\n");
                            goto chooseAgain2;
                        }
                    }
                }
                else if (field - dieRoll == -2) {
                    for (int i = 0; i < dieRoll; i++) {
                        if (bottomBoard[0][4] == '1' && bottomBoard[0][3] == '1' && topBoard[0][0] == '1' && topBoard[0][1] == '1') {
                            printf("A prime is blocking the move. Choose again.\n");
                            goto chooseAgain2;
                        }
                    }
                }
                else if (field - dieRoll < -2) {
                    for (int i = 0; i < dieRoll; i++) {
                        int delta = -(field - dieRoll + 1);
                        if (topBoard[delta + i][0] == '1' && topBoard[delta + i][1] == '1' && topBoard[delta + i + 1][0] == '1' && topBoard[delta + i + 1][1] == '1') {
                            printf("A prime is blocking the move. Choose again.\n");
                            goto chooseAgain2;
                        }
                    }
                }

                //ENEMY ANCHOR DENIAL
                if (bottomBoard[field - dieRoll][4] == '1' && bottomBoard[field - dieRoll][3] == '1' && field - dieRoll >= 0) {
                    printf("An anchor is blocking the move. Choose again.\n");
                    goto chooseAgain2;
                }
                else if (field - dieRoll < 0) {
                    int delta = -(field - dieRoll + 1);
                    if (topBoard[delta][0] == '2' && topBoard[delta][1] == '1') {
                        printf("An anchor is blocking the move. Choose again.\n");
                        goto chooseAgain2;
                    }
                }

                //FULL SELF ANCHOR
                if (bottomBoard[field - dieRoll][0] == '2') {
                    printf("Cannot move pawn. Destination field is full.\n");
                    goto chooseAgain2;
                }

                //CHOOSING SPACE DENIAL, CHOOSING WRONG TEAM DENIAL, CHOOSING A PAWN THATS NOT ON THE TOP OF THE STACK DENIAL
                //if (bottomBoard[field][pawn - 1] != '2' && bottomBoard[field][pawn] != '-' && bottomBoard[field][pawn] != '1') {
                    //HITTING MECHANIC
                    if (bottomBoard[field - dieRoll][4] == '1' && bottomBoard[field - dieRoll][3] == '-' && field - dieRoll >= 0) {
                        bottomBoard[field - dieRoll][4] = '2';
                        p1DeadPawns += 1;
                        //goto pTwoMoveEnd;
                    }

                    //MOVING FROM BOTTOM BOARD TO TOP BOARD
                    else if (field - dieRoll < 0) {
                        int delta = -(field - dieRoll + 1);
                        if (topBoard[delta][0] == '1' && topBoard[delta][1] == '-') {
                            topBoard[delta][0] = '2';
                            p1DeadPawns += 1;
                        }
                        else {
                            bottomBoard[field][pawn] = '-';
                            for (int j = 0; j < 5; j++) {
                                if (topBoard[field + delta][j] == '-') {
                                    nextPos = j;
                                    break;
                                }
                            }
                            topBoard[delta][nextPos] = '2';
                        }

                    }

                    //NORMAL MOVEMENT
                    else {
                        bottomBoard[field][pawn] = '-';
                        for (int j = 4; j >= 0; j--) {
                            if (bottomBoard[field - dieRoll][j] == '-') {
                                nextPos = j;
                                break;
                            }
                        }
                        bottomBoard[field - dieRoll][nextPos] = '2';
                    }
                //}
                //else {
                    //printf("Illegal pawn choice. Choose again.\n");
                    //goto chooseAgain2;
                //}

            }

            //TOP BOARD
            else if (field <= 24 && field >= 13) {
                //pawnDecryption(&field, &pawn);
                fieldDecryption(&field);
                for (int j = 4; j >= 0; j--) {
                    if (topBoard[field][j] == '2') {
                        pawn = j;
                        break; // Exit loop once pawn is found
                    }
                }

                //BEARING OFF FOR PLAYER 2
                if (field + dieRoll > 11) {
                    int count = 0;
                    for (int j = 0; j < 5; j++) {
                        for (int i = 6; i <= 11; i++) {
                            if (topBoard[i][j] == '1') {
                                count++;
                            }
                        }
                    }
                    if (count == 15) {
                        p2Points++;
                        topBoard[field][pawn] = '-';
                        printf("Player 2 has bore off a pawn.. +1 points!!");
                        Sleep(2);
                        clearScreen();
                        printBoard(topBoard, bottomBoard, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
                        playerMovement(field, pawn, topBoard, bottomBoard, 1, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
                    }
                    else {
                        printf("Can't bear off pawn. Make sure all the pawns are in the enemy home board.");
                        goto chooseAgain2;
                    }

                }

                //PRIME DENIAL
                for (int i = 0; i < dieRoll; i++) {
                    if (topBoard[field + dieRoll - i][0] == '1' && topBoard[field + dieRoll - i][1] == '1' && topBoard[field + dieRoll - i - 1][0] == '1' && topBoard[field + dieRoll - i - 1][1] == '1') {
                        printf("A prime is blocking the move. Choose again.\n");
                        goto chooseAgain2;
                    }
                }

                //ENEMY ANCHOR DENIAL
                if (topBoard[field + dieRoll][0] == '1' && topBoard[field + dieRoll][1] == '1') {
                    printf("An anchor is blocking the move. Choose again.\n");
                    goto chooseAgain2;
                }

                //FULL SELF ANCHOR
                if (topBoard[field + dieRoll][4] == '2') {
                    printf("Cannot move pawn. Destination field is full.\n");
                    goto chooseAgain2;
                }


                //CHOOSING SPACE DENIAL, CHOOSING WRONG TEAM DENIAL, CHOOSING A PAWN THATS NOT ON THE TOP OF THE STACK DENIAL
                //if (topBoard[field][pawn + 1] != '2' && topBoard[field][pawn] != '-' && topBoard[field][pawn] != '1') {
                    // HITTING MECHANIC
                    if (topBoard[field + dieRoll][0] == '1' && topBoard[field + dieRoll][1] == '-') {
                        topBoard[field + dieRoll][0] = '2';
                        p1DeadPawns += 1;
                        //goto pTwoMoveEnd;
                    }

                    //NORMAL MOVEMENT
                    else {
                        topBoard[field][pawn] = '-';
                        for (int j = 0; j < 5; j++) {
                            if (topBoard[field + dieRoll][j] == '-') {
                                nextPos = j;
                                break;
                            }
                        }
                        topBoard[field + dieRoll][nextPos] = '2';
                    }
                //}
                //else {
                    //printf("Illegal pawn choice. Choose again.\n");
                    //goto chooseAgain2;
                //}

            }

            //ERROR MESSAGES FOR INPUTTING FIELD 
        }
        else {
            printf("\rInvalid input! Please enter a numeric value.");
        }
        //ENDING MOVE
        //pTwoMoveEnd:
        clearScreen();
        printBoard(topBoard, bottomBoard, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
        playerMovement(field, pawn, topBoard, bottomBoard, 1, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
    }

    else if (whoseTurn == 10) {
        dieRoll = rand() % 6 + 1;
        printf("Player 1 rolled %d\n", dieRoll);
        int delta = 12 - dieRoll;
        if (topBoard[delta][0] == '-') {
            topBoard[delta][0] = '1';
            p1DeadPawns -= 1;
            clearScreen();
            printBoard(topBoard, bottomBoard, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
            printf("\rPlayer One's pawn was respawned on field number %d\n", 25 - dieRoll);
            fflush(stdout);
            Sleep(2);
            playerMovement(field, pawn, topBoard, bottomBoard, 2, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
        }
        else {
            printf("\rPlayer One's pawn couldn't respawn\n");
            fflush(stdout);
            Sleep(2);
            playerMovement(field, pawn, topBoard, bottomBoard, 2, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
        }

    }

    else if (whoseTurn == 20) {
        dieRoll = rand() % 6 + 1;
        printf("Player 2 rolled %d\n", dieRoll);
        int delta = 12 - dieRoll;
        if (bottomBoard[delta][4] == '-') {
            bottomBoard[delta][4] = '2';
            p2DeadPawns -= 1;
            clearScreen();
            printBoard(topBoard, bottomBoard, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
            printf("Player Two's pawn was respawned on field number %d", dieRoll);
            fflush(stdout);
            Sleep(2);
            playerMovement(field, pawn, topBoard, bottomBoard, 1, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
        }
        else {
            printf("Player Two's pawn couldn't respawn");
            fflush(stdout);
            Sleep(2);
            playerMovement(field, pawn, topBoard, bottomBoard, 1, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
        }

    }

}

int main() {
    int whoStarts; //  1 - player 1 starts, 2 - player 2 starts
    char topBoard[12][5]; // board[24][5]
    char bottomBoard[12][5];
    bool highlight[24];
    int field = 0;
    int pawn = 0;
    int p1DeadPawns = 0;
    int p2DeadPawns = 0;
    int p1Points = 0;
    int p2Points = 0;

    srand(time(NULL));

    setPawnsDefault(topBoard, bottomBoard);
    openingRoll(&whoStarts);
    printBoard(topBoard, bottomBoard, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);
    playerMovement(field, pawn, topBoard, bottomBoard, whoStarts, p1DeadPawns, p2DeadPawns, p1Points, p2Points, highlight);

    //  for (int j = 0; j < 5; j++) {
    //     for (int i = 0; i < 12; i++) {
    //         printf("%d %d %c\n", i, j, bottomBoard[i][j]);
    //     }
    //  }

    return 0;
}