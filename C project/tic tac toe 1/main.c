#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>


int board[3][3];

char winner = ' ';
char player1 ='X';
char player2 ='O';


void resetBoard();
void printBoard();
int checkFreeSpace();
void player1Move();
void player2Move();
char checkWinner();
void printWinner(char);


int main()
{
    char winner =' '; //winner = ' ' -> iska meaning= winner k jagha black space hai,
    //means ab tk kooi winner nhi bana
     resetBoard();

    while (winner == ' ' && checkFreeSpace() !=0)
    {
         printBoard();

         player1Move();
         winner=checkWinner();
         if (winner != ' ' && checkFreeSpace()==0)
         {
            break;
         }
         
         player2Move();
         winner = checkWinner();
         if (winner != ' ' && checkFreeSpace()==0)
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
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
        
    }
    
}

void printBoard()
{
    printf(" %c | %c | %c ",board[0][0],board[0][1],board[0][2]);
    printf("\n---|---|--\n");
    printf(" %c | %c | %c ",board[1][0],board[1][1],board[1][2]);
    printf("\n---|---|--\n");
    printf(" %c | %c | %c ",board[2][0],board[2][1],board[2][2]);
    printf("\n");
    

}

void player1Move()
{
    int x;
    int y;
    
   do
   {
     printf(" Player1 :Select the row (1-3) : ");
    scanf("%d",&x);
    x--;
    
    printf(" Player1 :Select the column (1-3) : ");
    scanf("%d",&y);
    y--;

    if (board[x][y] != ' ')
    {
        printf("Invalid Move!");
    }
    else{
        board[x][y] = player1;
    }
   } while (board[x][y] != ' ');
   
    
}

void player2Move()
{
    int x;
    int y;
    
   if (checkFreeSpace>0)
   {
    do
   {
     printf(" Player2 : Select the row (1-3) : ");
    scanf("%d",&x);
    x--;
    
    printf(" Player2 :Select the column (1-3) : ");
    scanf("%d",&y);
    y--;

    if (board[x][y] != ' ')
    {
        printf("Invalid Move!");
    }
    else{
        board[x][y] = player2;
    }
   } while (board[x][y] != ' ');
   
   }
   
}
int checkFreeSpace()
{
    int freespace =9;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j <3; j++)
        {
            board[i][j] != ' ';
            freespace--;
        }
        
    }
    return freespace;
}

char checkWinner()
{
    //for row

    for (int i = 0; i < 3; i++)
    {
        if (board[i][0]==board[i][1] && board[i][0] ==board[i][2])
        {
            return board[i][0];
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i]==board[1][i] && board[0][i]==board[2][i])
        {
            return board[0][i];
        }
        
    }
    for (int i = 0; i < 3; i++)
    {
        if (board[0][0]==board[1][1] && board[0][0]==board[2][2])
        {
            return board[0][0];
        }
        
    }
    for (int i = 0; i < 3; i++)
    {
        if (board[2][0]==board[1][1] && board[2][0]==board[0][2])
        {
            return board[2][0];
        }
        
    }

    return ' ';
    
}

void printWinner(char)
{
   if (winner== player1)
   {
    printf("Player1 winner!");
   } 
   else if (winner==player2)
   {
    printf("Player2 is Winner!");
   }
   else
   {
    printf("It's a Tie!");
   }
   
   
}
