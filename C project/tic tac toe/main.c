#include<stdio.h>
int board[3][3];

void PrintBoard();
int main()
{
    PrintBoard();
    return 0;
}
void PrintBoard()
{
    printf(" %c | %c | %c ",board[0][0],board[0][1],board[0][2]);
    printf("\n--|--|--\n");
    printf(" %c | %c | %c ",board[1][0],board[1][1],board[1][2]);
    printf("\n--|--|--\n");
    printf(" %c | %c | %c ",board[2][0],board[2][1],board[2][2]);
    printf("\n");
}