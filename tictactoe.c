#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

char replaceEmpty(char character){
    if(character == '0'){
        return ' ';
    }
    return character;
}
void printBoard(char board[3][3]){
    printf("\n  1 2 3 X");
    printf("\n1 %c %c %c", replaceEmpty(board[0][0]), replaceEmpty(board[1][0]), replaceEmpty(board[2][0]));
    printf("\n2 %c %c %c", replaceEmpty(board[0][1]), replaceEmpty(board[1][1]), replaceEmpty(board[2][1]));
    printf("\n3 %c %c %c", replaceEmpty(board[0][2]), replaceEmpty(board[1][2]), replaceEmpty(board[2][2]));
    printf("\nY");
}
bool isgamegoing(char board[3][3]){
    int turn = 0;
    while(turn < 2){
        bool won = false;
        char c;
        if(turn == 0){
            c = 'O';
        }
        else{
            c = '#';
        }
        //Schrägen kontrollieren
        if(board[0][0] == c && board[1][1] == c && board[2][2] == c){
            won = true;
        }
        //Zeilen und Spalten kontrollieren
        for(int i = 0; i < 4; i++){
            if(board[0][i] == c && board[1][c] == c && board[2][c] == c){
                won = true;
            }
            if(board[i][0] == c && board[i][1] == c && board[i][2] == c){
                won = true;
            }
        }
        if(won){
            printf("\nSpieler %c hat gewonnen!\n", c);
            return false;
        }
        turn++;
    }
    return true; //REPLACEMENT
}
void clearBuffer(){
    while(getchar() != '\n');
}
bool checkValid(char charx, char chary, char board[3][3]){
    int x = charx - '0';
    int y = chary - '0';
    if(x > 0 && x < 4 && y > 0 && y < 4){
        if(board[x - 1][y - 1] == '0'){
            return true;
        }
    }
    return false;
}
void updateboard(char board[3][3], char xChar, char yChar, char player){
    char xStr[2] = {xChar, '\0'};
    char yStr[2] = {yChar, '\0'};
    int x = xChar - '0';
    int y = yChar -'0';
    board[x - 1][y - 1] = player;
}
int main(){
    setlocale(LC_ALL, "");
    int turn = 0;
    char board[3][3] = {
        {'0', '0', '0'},
        {'0', '0', '0'},
        {'0', '0', '0'}
    };
    while(isgamegoing(board)){
                #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        printBoard(board);
        if(turn % 2 == 0){
            bool valid = false;
            printf("\nSpieler O ist am Zug!");
            while(true){
                printf("\n\nGib die X-Koordinate des ausgewählten Feldes ein: ");
                char x;
                scanf(" %c", &x);
                clearBuffer();
                printf("Gib die Y-Koordinate des ausgewählten Feldes ein: ");
                char y;
                scanf(" %c", &y);
                clearBuffer();
                valid = checkValid(x, y, board);
                if(valid){
                    updateboard(&board, x, y, 'O');
                    break;
                }
                printf("\n\nDie eingegeben Werte sind inkorrekt! Erneute Eingabe erforderlich!");
            }
            
        }
        else{
            printf("\nSpieler # ist am Zug!");
            bool valid = false;
            while(true){
                printf("\n\nGib die X-Koordinate des ausgewählten Feldes ein: ");
                char x;
                scanf(" %c", &x);
                clearBuffer();
                printf("Gib die Y-Koordinate des ausgewählten Feldes ein: ");
                char y;
                scanf(" %c", &y);
                clearBuffer();
                valid = checkValid(x, y, board);
                if(valid){
                    updateboard(&board, x, y, '#');
                    break;
                }
                printf("\n\nDie eingegeben Werte sind inkorrekt! Erneute Eingabe erforderlich!\n");
                printf("%c %c", x, y);
            }
        }
        turn++;
        if(turn == 9){
            printf("\nUnentschieden! Kein Spieler hat gewonnen!");
            break;
        }
    }
    scanf("%s");
    return 0;
}
