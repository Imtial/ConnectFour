#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ERR_MOVE    -9999999
#define INF 999999
#define ROW 7
#define COL 8

int moves;
int game_score;
char board[ROW][COL];
char position[COL];

int _pow_(int x, int n)
{
    for(int i=1; i<n;i++) x *= x;
    return x;
}

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
        board[ROW-i][0] = '0'+i;
    }
    board[0][0] = ' ';

    for(int i=1; i<COL; i++) position[i] = ROW - 1;
}

void draw_board(const char board[ROW][COL])
{
    // system("clear");

    for(int i=0; i<ROW; i++)
    {
        for(int j=0; j<COL; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int evaluate_board(const char board[ROW][COL], int col, int last_score)
{
    int in_a_row = 1;
    int opcount = 0;
    int score = 0;
    int top = position[col]+1;
    char sym = board[top][col];
    char opsym = (sym=='O')?'X':'O';
    int i;

    // column checking for symbol in a row
    for(i=1; board[top+i][col]==sym && i<4;i++)
    {
        in_a_row++;
    }
    if(in_a_row == 4)
    {
        if(sym == 'O') return -INF;
        else return +INF;
    }
    else
    {
        // printf("Column: %d\n", _pow_(in_a_row, in_a_row));
        score += _pow_(in_a_row, in_a_row);
        in_a_row = 1;
    }
    // column checking for opposite symbol in a row
    for(i=1; board[top+i][col]==opsym && i<4;i++)
    {
        opcount++;
    }
    if(opcount>2)
    {
        // printf("Op-Column: %d\n", _pow_(opcount, opcount) +10);
        score += _pow_(opcount, opcount) +10;
    }
    opcount = 0;

    // row checking
    for(i=1; board[top][col-i]==sym  && (col-i)>0; i++)
    {
        in_a_row++;
    }
    for(i=1; board[top][col+i]==sym  && (col+i)<COL; i++)
    {
        in_a_row++;
    }
    if(in_a_row == 4)
    {
        if(sym=='O') return -INF;
        else return +INF;
    }
    else
    {
        // printf("Row: %d\n", _pow_(in_a_row, in_a_row));
        score += _pow_(in_a_row, in_a_row);
        in_a_row = 1;
    }

    // row checking for oposite symbols in a row
    for(i=1; board[top][col-i]==opsym  && (col-i)>0; i++)
    {
        opcount++;
    }
    for(i=1; board[top][col+i]==opsym  && (col+i)<COL; i++)
    {
        opcount++;
    }
    if(opcount>2)
    {
        // printf("Op-Row: %d\n", _pow_(opcount, opcount) +10);
        score += _pow_(opcount, opcount) +10;
    }
    opcount = 0;

    // diagonal(down-left to up-right) checking
    for(i=1; board[top+i][col-i]==sym  && (col-i)>0 && (top+i)<ROW; i++)
    {
        in_a_row++;
    }
    for(i=1; board[top-i][col+i]==sym  && (col+i)<COL && (top-i)>0; i++)
    {
        in_a_row++;
    }
    if(in_a_row == 4)
    {
        if(sym=='O') return -INF;
        else return +INF;
    }
    else
    {
        // printf("Diagonal-1: %d\n", _pow_(in_a_row, in_a_row));
        score += _pow_(in_a_row, in_a_row);
        in_a_row = 1;
    }

    // diagonal(down-left to up-right) checking oposite symbols in a row
    for(i=1; board[top+i][col-i]==opsym  && (col-i)>0 && (top+i)<ROW; i++)
    {
        opcount++;
    }
    for(i=1; board[top-i][col+i]==opsym  && (col+i)<COL && (top-i)>0; i++)
    {
        opcount++;
    }
    if(opcount>2)
    {
        // printf("Op-Diagonal-1: %d\n", _pow_(opcount, opcount) +10);
        score += _pow_(opcount, opcount) +10;
    }
    opcount = 0;

    // diagonal(up-left to down-right) checking
    for(i=1; board[top-i][col-i]==sym  && (col-i)>0 && (top-i)>0; i++)
    {
        in_a_row++;
    }
    for(i=1; board[top+i][col+i]==sym && (col+i)<COL && (top+i)<ROW; i++)
    {
        in_a_row++;
    }
    if(in_a_row == 4)
    {
        if(sym=='O') return -INF;
        else return +INF;
    }
    else
    {
        // printf("Diagonal-2: %d\n", _pow_(in_a_row, in_a_row));
        score += _pow_(in_a_row, in_a_row);
    }

    // diagonal(up-left to down-right) checking for oposite symbols in a row
    for(i=1; board[top-i][col-i]==opsym  && (col-i)>0 && (top-i)>0; i++)
    {
        opcount++;
    }
    for(i=1; board[top+i][col+i]==opsym && (col+i)<COL && (top+i)<ROW; i++)
    {
        opcount++;
    }
    if(opcount>2)
    {
        // printf("Op-Diagonal-2: %d\n", _pow_(opcount, opcount) +10);
        score += _pow_(opcount, opcount) +10;
    }

    for(i=1; position[i]==0 && i<COL; i++);
    if(i == COL) return 0; // tie condition

    if(sym == 'O') return last_score - score;
    else return last_score + score;

}

int player_move(char col, char sym)
{
    int col_val = col - 'A' + 1;
    if(position[col_val] == 0) return ERR_MOVE;

    int row = position[col_val]--;

    board[row][col_val] = sym;
    game_score = evaluate_board(board, col_val, game_score);

    return game_score;
}

int minimax(char board[ROW][COL], char sym, int col, int depth, int board_score)
{
    int score = evaluate_board(board, col, board_score);
    // printf("Depth: %d, Sym: %c, Pre-Score: %d, Post-Score: %d\n", depth, sym, board_score, score);

    if(depth < 0) return score;

    // Maximizer won the game
    if(score == +INF) return +INF;

    // Minimizer won the game
    if(score == -INF) return -INF;

    // Draw game
    if(score == 0)  return 0;

    // if this is maximizer's move
    if(sym=='X')
    {
        int best = -INF;

        for(int c=1; c<COL;c++)
        {
            if(position[c] != 0)
            {
                int row = position[c]--;
                board[row][c] = sym;

                int debug_score = evaluate_board(board, c, score);
                // draw_board(board);
                // printf("Depth: %d, Sym: %c, Pre-Score: %d, Post-Score: %d\n", depth, sym, score, debug_score);

                int val = minimax(board, 'O', c, depth-1, score);
                if(val > best) best = val;

                board[row][c] = '.';
                position[c]++;
            }
        }
        return best;
        // return best-depth;
    }
    // if this is minimizer's move
    else
    {
        int best = +INF;

        for(int c=1; c<COL;c++)
        {
            if(position[c] != 0)
            {
                int row = position[c]--;
                board[row][c] = sym;

                int debug_score = evaluate_board(board, c, score);
                // draw_board(board);
                // printf("Depth: %d, Sym: %c, Pre-Score: %d, Post-Score: %d\n", depth, sym, score, debug_score);

                int val = minimax(board, 'X', c, depth-1, score);

                if(val < best) best = val;

                board[row][c] = '.';
                position[c]++;
            }
        }
        return best;
        // return best+depth;
    }

}

char ai_move(char board[ROW][COL], int depth)
{
    int best = -INF;
    char col = -1;
    char sym = 'X';
    char opsym = 'O';

    for(int c=1; c<COL; c++)
    {
        if(position[c]>0)
        {
            int row = position[c]--;
            board[row][c] = sym;

            int move_score = minimax(board, opsym, c, depth-1, game_score);
            // draw_board(board);
            // printf("Prev: %d, Post: %d\n", game_score, move_score);

            board[row][c] = '.';
            position[c]++;

            if(move_score > best)
            {
                best = move_score;
                col = c;
            }
        }
    }
    // printf("Best : %d\n", best);
    return col+'A'-1;
}

int main()
{
    init_game();
    draw_board(board);

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
            // move = player_move(ai_move(board, 'X', 5)+'A'-1, 'X');
        } while(move == ERR_MOVE);

        draw_board(board);

        if(move == -INF)
        {
            printf("Game Over!!!\nWINNER: Player 1!\n");
            break;
        }

        do
        {
            // printf("player 2 move: ");
            // scanf(" %c", &p);
            // move = player_move(p, 'O');
            move = player_move(ai_move(board, 2), 'X');
        } while (move == ERR_MOVE);

        printf("Computer move done\n");
        draw_board(board);

        if(move == +INF)
        {
            printf("Game Over!!!\nWINNER: Player 2!\n");
            break;
        }
    }
    return 0;
}