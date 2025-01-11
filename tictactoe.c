#include <stdio.h>
#include <stdbool.h>

void flushStdin(char* response);
int matchEvent();
char charSelect();
bool tutorial();
int match(char p1char, char p2char);
void move(char board[3][3], char* Move, int player);
bool check1(char board[3][3], int xPos, int yPos);
bool check2(char top, char mid, char bot);

int main() {

    printf("\n1V1 3X3 TIC-TAC-TOE\n");
    printf("\nMade by c4tu5 https://github.com/Bl4p\n");
    printf("\n\\ A B C\n\n1  | | \n  -----\n2  | | \n  -----\n3  | | \n\n");

    char response[3];
    while (1) {

        printf("Would you like to play a match? (enter 'y' or 'Y' for Yes and 'n' or 'N' for No): ");
        fgets(response, 3, stdin);
        
        flushStdin(response);

        while(1) {

            if ((response[0] == 'y' || response[0] == 'Y' || response[0] == 'n' || response[0] == 'N' ) && response[1] == '\n') break;

            printf("Invalid input! Enter 'y' or 'Y' for Yes if you would like to play a match and 'n' or 'N' for No: ");
            fgets(response, 3, stdin);

            flushStdin(response);
        }

        if (response[0] == 'n' || response[0] == 'N') break;

        int event = matchEvent();

        if (event == 0) break;
        if (event == 1) {

            while (1) {

                if (event == 0) {

                    printf("\nSee you next time!");
                    return 0;
                }

                printf("Would you like to play another match? (enter 'y' or 'Y' for Yes and 'n' or 'N' for No): ");
                fgets(response, 3, stdin);
        
                flushStdin(response);

                while(1) {

                    if ((response[0] == 'y' || response[0] == 'Y' || response[0] == 'n' || response[0] == 'N' ) && response[1] == '\n') break;

                    printf("Invalid input! Enter 'y' or 'Y' for Yes if you would like to play another match and 'n' or 'N' for No: ");
                    fgets(response, 3, stdin);

                    flushStdin(response);
                }

                if (response[0] == 'n' || response[0] == 'N') {
                
                    printf("\nSee you next time!");

                    return 0;
                }

                event = matchEvent();
            }
        }
    }

    printf("\nSee you next time!");

    return 0;
}

void flushStdin(char* response) {

    bool newline;
    for (int i = 0; i < 3; i++) {

        if (*(response + i) == '\n') newline = true;
    }

    if (newline == false) {

        int c; 
        while ((c = getchar()) != '\n' && c != EOF) {} 
    }
}

int matchEvent() {

    char p1char = 'x', p2char = 'o';

    printf("P1\n");
    p1char = charSelect();
    if (p1char == '\\') return 0;
    if (p1char == '\n') p1char = 'x';

    printf("P2\n");
    p2char = charSelect();

    while (1) {

        if (p2char != p1char) break;

        printf("P2's character must be different from P1's !\n");
        p2char = charSelect();

        if (p2char == '\\') return 0;
    }

    if (p2char == '\n') p2char = 'o';

    char response[3];

    printf("Would you like to read the tutorial? enter 'y' or 'Y' for Yes and 'n' or 'N' for No and 'q' or 'Q' to quit the game: ");
    fgets(response, 3, stdin);
        
        flushStdin(response);

        while(1) {

            if ((response[0] == 'y' || response[0] == 'Y' || response[0] == 'n' || response[0] == 'N' || response[0] == 'q' || response[0] == 'Q') && response[1] == '\n') break;

            printf("Invalid input! Enter 'y' or 'Y' for Yes if you would like to read the tutorial and 'n' or 'N' for No and 'q' or 'Q' to quit the game: ");
            fgets(response, 3, stdin);

            flushStdin(response);
        }

    if (response[0] == 'q' ||  response[0] == 'Q') return 0;

    int result;
    if (response[0] == 'Y' ||  response[0] == 'y') {

        if (tutorial() == false) return 0;
    }
    
    result = match(p1char, p2char);

    if (result == 0) printf("DRAW\n");
    if (result == 2) printf("P2 Wins!\n");
    if (result == 1) printf("P1 Wins\n");

    if (result == 3) return 0;

    return 1;
}

bool tutorial() {

    char response[3];

    while (1) {

        if (response[0] == 'q' || response[0] == 'Q') return false;
        if (response[0] == 'n' || response[0] == 'N') break;
        printf("\nTutorial:\n");
        printf("\n\\ A B C\n\n1  | | \n  -----\n2  | | \n  -----\n3  | | \n");
        printf("\n This is the 3-by-3 grid on which 2 players will compete to see who is the winner, which is the one who has 3 instances of their chosen character next to each other (horizontally, vertically or diagonally).\n");
        printf("Example: \n\\ A B C\n\n1 x|x|x\n  -----\n2  | | \n  -----\n3  | | \n");
        printf("\n\\ A B C\n\n1  |x| \n  -----\n2  |x| \n  -----\n3  |x| \n");
        printf("\n\\ A B C\n\n1 x| | \n  -----\n2  |x| \n  -----\n3  | |x\n");
        printf("Each player will take turns marking their desired location with their character by typing the address of said location when prompted\n");
        printf("Example:\n");
        printf("\tInput: A1\n");
        printf("\tOutput:\n");
        printf("\n\\ A B C\n\n1 x| | \n  -----\n2  | | \n  -----\n3  | | \n");
        printf("\n(Scroll up until you see \"Tutorial:\" to reach the beginning or the tutorial)\n");
        printf("That's the end of the tutorial. Would you like to read again (enter 'y' or 'Y'), begin the match (enter 'n' or 'N') or quit the game (enter 'q' or 'Q')? : ");

        fgets(response, 3, stdin);
        
        flushStdin(response);

        while(1) {

            if ((response[0] == 'y' || response[0] == 'Y' || response[0] == 'n' || response[0] == 'N' || response[0] == 'q' || response[0] == 'Q') && response[1] == '\n') break;

            printf("Invalid input! Enter 'y' or 'Y' for Yes if you would like to read the tutorial again and 'n' or 'N' for No. If you want to quit, enter 'q' or 'Q': ");
            fgets(response, 3, stdin);

            flushStdin(response);
        }

        if (response[0] == 'y' || response[0] == 'Y') continue;
    }

    return true;
}

char charSelect() {

    char pChar[3];

    printf("Please select your preferred character (press enter to use the default options P1 - 'x', P2 - 'o') or enter \\ to quit the game (you CANNOT choose one of the following: '1', '2', '3', 'A', 'B', 'C', '|', '-',' '): ");
    fgets(pChar, 3, stdin);

    flushStdin(pChar);

    while (1) {

        if (pChar[1] == '\n' && (pChar[0] < 1 || (pChar[0] > 3 && pChar[0] < 'A') || pChar[0] > 'C' || pChar[0] != '|' || pChar[0] != '-' || pChar[0] != ' ') || pChar[0] == '\n') break;

        printf("Invalid input!\n");
        printf("Please select your preferred character again (press enter to use the default options P1 - 'x', P2 - 'o') or enter \\ to quit the game (you CANNOT choose one of the following: '1', '2', '3', 'A', 'B', 'C', '|', '-', ' '): ");

        fgets(pChar, 3, stdin);

        flushStdin(pChar);
    }

    return pChar[0];
}

int match(char p1char, char p2char) {

    printf("You can enter -1 to quit at any time.\n");
    printf("Good luck and have fun!\n");
    printf("BEGIN\n");

    char board[3][3] = {
        {' ',' ',' '},
        {' ',' ',' '},
        {' ',' ',' '}
    };

    printf("\n\\ A B C\n1 %c|%c|%c\n  -----\n2 %c|%c|%c\n  -----\n3 %c|%c|%c\n\n", board[0][0], board[0][1], board[0][2], board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);

    char p1[4], p2[4];
    int xPos, yPos;
    bool result;
    for (int i = 0; i < 9; i++) {

        if (i%2 == 0) {

            move(board, p1, 1);

            if (p1[0] == '-' && p1[1] == '1') return 3;

            if (p1[0] >= 'a' && p1[0] <= 'c') p1[0] -= ('a' - 'A');

            xPos = (int) (p1[0] - 'A');
            yPos = (int) (p1[1] - '1');

            if (board[yPos][xPos] != ' ') {

                while (1) {

                    if (board[yPos][xPos] == ' ') break;

                    printf("That position has already been taken! Try another.\n");
                    printf("\n\\ A B C\n1 %c|%c|%c\n  -----\n2 %c|%c|%c\n  -----\n3 %c|%c|%c\n\n", board[0][0], board[0][1], board[0][2], board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);
                    
                    move(board, p1, 1);

                    if (p1[0] == '-' && p1[1] == '1') return 3;

                    if (p1[0] >= 'a' && p1[0] <= 'c') p1[0] -= ('a' - 'A');

                    xPos = (int) (p1[0] - 'A');
                    yPos = (int) (p1[1] - '1');
                }
            }

            board[yPos][xPos] = p1char;
        }
        else {

            move(board, p2, 2);

            if (p2[0] == '-' && p2[1] == '1') return 3;

            if (p2[0] >= 'a' && p2[0] <= 'c') p2[0] -= ('a' - 'A');

            xPos = (int) (p2[0] - 'A');
            yPos = (int) (p2[1] - '1');

            if (board[yPos][xPos] != ' ') {

                while (1) {

                    if (board[yPos][xPos] == ' ') break;

                    printf("That position has already been taken! Try another.\n");
                    printf("\n\\ A B C\n1 %c|%c|%c\n  -----\n2 %c|%c|%c\n  -----\n3 %c|%c|%c\n\n", board[0][0], board[0][1], board[0][2], board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);
                    
                    move(board, p2, 2);

                    if (p2[0] == '-' && p2[1] == '1') return 3;

                    if (p2[0] >= 'a' && p2[0] <= 'c') p2[0] -= ('a' - 'A');

                    xPos = (int) (p2[0] - 'A');
                    yPos = (int) (p2[1] - '1');
                }
            }

            board[yPos][xPos] = p2char;
            }

        printf("\n\\ A B C\n1 %c|%c|%c\n  -----\n2 %c|%c|%c\n  -----\n3 %c|%c|%c\n\n", board[0][0], board[0][1], board[0][2], board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);

        if (i > 3) {

            result = check1(board, xPos, yPos);

            if (result == true) {
                    
            if (i%2 == 0) return 1;
            else return 2;
            }
        }
    }

    if (result != true) return 0;

    return 0;
}

void move(char board[3][3], char* Move, int player) {

    printf("P%i: ", player);
    fgets(Move, 4, stdin);

    flushStdin(Move);
        
        while (1) {

        if ((*Move == '-' && *(Move + 1) == '1') || (*(Move + 2) == '\n' && ((*Move >= 'A' && *Move <= 'C') || (*Move >= 'a' && *Move <= 'c')) && (*(Move + 1) >= '1' && *(Move + 1) <= '3'))) break;

        if (*(Move + 2) != '\n' || (*Move < 'A' || (*Move > 'C' && *Move < 'a') || *Move > 'c') || (*(Move + 1) < '1' || *(Move + 1) > '3')) printf("Invalid input! Try again.\n");

        printf("\n\\ A B C\n1 %c|%c|%c\n  -----\n2 %c|%c|%c\n  -----\n3 %c|%c|%c\n\n", board[0][0], board[0][1], board[0][2], board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);

        printf("P%i: ", player);
        fgets(Move, 4, stdin);

        flushStdin(Move);
        }
}


bool check1(char board[3][3], int xPos, int yPos) {

    bool win;

    if (yPos == 2 && xPos == 2) {
        win = check2(board[0][0], board[1][1], board[2][2]);
        if (win == true)
            return true;
            
        win = check2(board[0][2], board[1][1], board[2][0]);
        if (win == true)
            return true;
    }

    if (xPos == yPos + 2 || yPos == xPos + 2) {
        win = check2(board[0][2], board[1][1], board[2][0]);
        if (win == true)
            return true;
    }
    if (xPos == yPos && xPos != 2) {
        win = check2(board[0][0], board[1][1], board[2][2]);
        if (win == true)
            return true;
    }

    win = check2(board[yPos][0], board[yPos][1], board[yPos][2]);
    if (win == true)
        return true;

    win = check2(board[0][xPos], board[1][xPos], board[2][xPos]);
    if (win == true)
        return true;

    return false;
}

bool check2(char top, char mid, char bot) {

    if (top == mid && mid == bot) return true;

    return false;
}