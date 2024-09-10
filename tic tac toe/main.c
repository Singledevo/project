#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
char winner = ' ';
char Board[3][3];
const char PLAYER ='X';
const char COMPUTER ='O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMoves();
void computerMoves();
char checkWinner();
void printWinner(char);

 int main()
 {
    char winner = ' ';


    resetBoard();
    while (winner == ' ' && checkFreeSpaces() !=0)
    {
        printBoard();
        playerMoves();
        winner = checkWinner();
        if (winner != ' ' || checkFreeSpaces() == 0)
        {
            break;
        }
        computerMoves();
        winner = checkWinner();
        if (winner != ' ' || checkFreeSpaces() == 0)
        {
            break;
        }
        
    }
     printBoard();
     printWinner(winner);
    
    return 0;
 }

void resetBoard()
{
    for ( int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            Board[i][j]= ' ';
        }
        
    }
    
}
void printBoard()
{
    printf("%c | %c | %c", Board[0][0],Board[0][1],Board[0][1]);
    printf("\n--|---|--\n");
    printf("%c | %c | %c", Board[1][0],Board[1][1],Board[1][2]);
    printf("\n--|---|--\n");
    printf("%c | %c | %c", Board[2][0],Board[2][1],Board[2][2]);
    printf("\n");
}
int checkFreeSpaces()
{
    int freeSpace =9;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(Board[i][j] != ' ')
            freeSpace--;

        }
        
    }
   return freeSpace; 
}
void playerMoves()
{
    int x;
    int y;

   do
   {
     printf("Enter in row @(1-3): ");
    scanf("%d", &x);
    x--;
    printf("Enter in column @(1-3): ");
    scanf("%d", &y);
    y--;

    if(Board[x][y] != ' ')
    {
        printf("Invalid Move!\n");
    }
    else
    {
        Board[x][y] = PLAYER;
        break;
    }
   } while (Board[x][y] != ' ');
   
}
void computerMoves()
{
    srand(time(0));
    int x;
    int y;

    if(checkFreeSpaces() > 0)
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (Board[x][y] != ' ');

        Board[x][y] = COMPUTER;

        
    }
    else{
        printWinner(' ');
    }

}
char checkWinner()
{
    //for rows
    for (int i = 0; i < 3; i++)
    {
        if (Board[i][0]==Board[i][1] && Board[i][0]==Board[i][2])
        {
            return Board[i][0];
        }
        
    }
    //for columns
    for (int i = 0; i < 3; i++)
    {
        if(Board[0][i]==Board[1][i] && Board[0][i]==Board[2][i])
        
        {
         return Board[0][i];
        }      
    }
    // for diagonals
    for (int i = 0; i < 3; i++)
    {
        if (Board[0][0]== Board[1][1] && Board[0][0]==Board[2][2])
        {
            return Board[0][0];

        }
        
    }
    // for bottom diagonal
    for (int i = 0; i < 3; i++)
    {
        if (Board[0][2]== Board[1][1] && Board[0][2]==Board[2][0])
        {
            return Board[0][2];

        }
        return ' ';
        
    }
}
void printWinner(char winner)
{
    if (winner ==PLAYER)
    {
        printf("YOU WIN");
    }
    else if (winner == COMPUTER)
    {
        printf("YOU LOSS");
    }

    else
    {
        printf("IT'S A TIE");
    }
    
     
}
