#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ERR_MOVE    -1
#define ROW 7
#define COL 7

char board[ROW][COL];
char position[COL];

void init_game()
{
    for(int i=0; i<ROW; i++)
    {
        for(int j=0; j<COL; j++)
        {
            board[i][j] = '.';
        }
    }
    for(int i=1; i<COL; i++)
    {
        board[0][i] = 'A'+i-1;
        board[i][0] = '0'+i;
    }
    board[0][0] = ' ';

    for(int i=1; i<COL; i++) position[i] = ROW - 1;
}

void draw_board()
{
    system("clear");

    for(int i=0; i<ROW; i++)
    {
        for(int j=0; j<COL; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int check_game(char col, char sym)
{
    int count = 1;
    int top = position[col] + 1;
    int disks = ROW - position[col] - 1;
    int identical = 1;

    // column checking
    if(disks >= 4)
    {
        for(int i=1; board[top+i][col]==sym && i<4;i++)
        {
            count++;
        }
        if(count == 4) return 1;
        else count = 1;
    }

    // row checking
    for(int i=1; board[top][col-i]==sym && (col-i)>0; i++)
    {
        count++;
    }
    for(int i=1; board[top][col+i]==sym && (col+i)<COL; i++)
    {
        count++;
    }
    if(count == 4) return 1;
    else count = 1;

    // diagonal(down-left to up-right) checking
    for(int i=1; board[top+i][col-i]==sym && (col-i)>0 && (top+i)<ROW; i++)
    {
        count++;
    }
    for(int i=1; board[top-i][col+i]==sym && (col+i)<COL && (top-i)>0; i++)
    {
        count++;
    }
    if(count == 4) return 1;
    else count = 1;

    // diagonal(up-left to down-right) checking
    for(int i=1; board[top-i][col-i]==sym && (col-i)>0 && (top-i)>0; i++)
    {
        count++;
    }
    for(int i=1; board[top+i][col+i]==sym && (col+i)<COL && (top+i)<ROW; i++)
    {
        count++;
    }
    if(count == 4) return 1;
    else count = 1;

    return 0;
}

int player_move(char col, char sym)
{
    col = col - 'A' + 1;
    int row = position[col]--;

    if(row < 1 ) return ERR_MOVE;

    board[row][col] = sym;
    draw_board();

    return check_game(col, sym);
}

int main()
{
    init_game();
    draw_board();

    int moves = 0;
    while(moves++ < (ROW-1)*(COL-1))
    {
        char p;
        int move;
        do
        {
            printf("player 1 move: ");
            scanf(" %c", &p);
            move = player_move(p, 'O');
        } while(move == ERR_MOVE);

        if(move == 1)
        {
            printf("Game Over!!!\nWINNER: Player 1!\n");
            break;
        }

        do
        {
            printf("player 2 move: ");
            scanf(" %c", &p);
            move = player_move(p, 'X');
        } while (move == ERR_MOVE);

        if(move == 1)
        {
            printf("Game Over!!!\nWINNER: Player 2!\n");
            break;
        }
    }

    return 0;
}