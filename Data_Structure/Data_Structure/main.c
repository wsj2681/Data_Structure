#define _CRT_SECURE_NO_WARNINGS
#define BOARD 19
#define BLACK 1
#define WHITE -1 

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

typedef struct PutStack
{
    int x;
    int y;

}stack;

typedef struct StoneInfo
{

    const int type;   // 0: BLACK, 1: WHITE
    int totalCount;

    int rowStoneCount[BOARD];
    int colStoneCount[BOARD];
    int rdStoneCount[BOARD * 2];
    int ruStoneCount[BOARD * 2];

    int rowComboCount[BOARD];
    int colComboCount[BOARD];
    int rdComboCount[BOARD * 2];    // right Down
    int ruComboCount[BOARD * 2];    // right Up

    stack stack[BOARD];
    int stackIndex;

    stack backUpStack[BOARD];
    int backUpIndex;

}stone;

void ClearStone(stone* black, stone* white);
void InitBoard(int board[][BOARD]);
void PrintBoard(int board[][BOARD], stone* black, stone* white, int flag);
void PrintSituationBoard(int board[][BOARD], stone* black, stone* white);

void CheckBoard(int board[][BOARD], stone* black, stone* white);
void RowCheck(int board[][BOARD], stone* black, stone* white);
void ColumnCheck(int board[][BOARD], stone* black, stone* white);
void RightUpCheck(int board[][BOARD], stone* black, stone* white);
void RightDownCheck(int board[][BOARD], stone* black, stone* white);
void Save(int board[][BOARD], stone* black, stone* white, int flag);
void Load(int board[][BOARD], stone* black, stone* white, int* flag);
void Undo(int board[][BOARD], stone* black, stone* white, int* flag);
void UndoUndo(int board[][BOARD], stone* black, stone* white, int* flag);

int main()
{
    int x, y;

    int board[BOARD][BOARD];

    int flag = 1;

    stone black = { 0, 0, 0, 0, 0 };
    stone white = { 1, 0, 0, 0, 0 };

    InitBoard(board);

    while (1)
    {
        CheckBoard(board, &black, &white);
        PrintBoard(board, &black, &white, flag);

        scanf_s("%d %d", &y, &x);

        if (y == -1)
        {
            break;
        }

        if (y == 100)
        {
            Save(board, &black, &white, flag);
            continue;
        }

        if (y == 101)
        {
            Load(board, &black, &white, &flag);
            continue;
        }

        if (y == 102)
        {
            Undo(board, &black, &white, &flag);
            continue;
        }

        if (y == 103)
        {
            UndoUndo(board, &black, &white, &flag);
            continue;
        }

        if ((x < 0 || x > BOARD) || (y < 0 || y > BOARD))
        {
            printf("범위를 벗어났습니다.\n");
            continue;
        }

        if (board[y][x] != 0)
        {
            printf("이미 돌이 놓여있습니다.\n");
            continue;
        }

        if (flag == BLACK)
        {
            board[y][x] = BLACK;
            black.totalCount++;
            black.stack[black.stackIndex].x = x;
            black.stack[black.stackIndex].y = y;
            black.stackIndex++;
        }

        else if (flag == WHITE)
        {
            board[y][x] = WHITE;
            white.totalCount++;
            white.stack[white.stackIndex].x = x;
            white.stack[white.stackIndex].y = y;
            white.stackIndex++;
        }

        flag *= -1;
    }
    return 0;
}



void ClearStone(stone* black, stone* white)
{
    for (int i = 0; i < BOARD; ++i)
    {
        black->rowStoneCount[i] = 0;
        black->colStoneCount[i] = 0;
        white->rowStoneCount[i] = 0;
        white->colStoneCount[i] = 0;
    }

    for (int i = 0; i < BOARD * 2; ++i)
    {
        black->rdStoneCount[i] = 0;
        black->ruStoneCount[i] = 0;
        white->rdStoneCount[i] = 0;
        white->ruStoneCount[i] = 0;
    }
}

void InitBoard(int board[][BOARD])
{
    for (int i = 0; i < BOARD; ++i)
    {
        for (int j = 0; j < BOARD; ++j)
        {
            memset(&board[i][j], 0, sizeof(int));
        }
    }

}

void PrintBoard(int board[][BOARD], stone* black, stone* white, int flag)
{
    for (int i = 0; i < BOARD; ++i)
    {
        for (int j = 0; j < BOARD; ++j)
        {
            if (board[j][i] == 0)
            {
                printf("╂ ");
            }
            else if (board[j][i] == 1)
            {
                printf("○");
            }
            else if (board[j][i] == -1)
            {
                printf("●");
            }
        }
        printf("\n");
    }

    if (flag == 1)
        printf("검은돌 차례입니다.\n");
    if (flag == -1)
        printf("흰돌 차례입니다.\n");
}

void PrintSituationBoard(int board[][BOARD], stone* black, stone* white)
{
    for (int i = 0; i < BOARD * 2; ++i)
    {
        if ((black->rowStoneCount[i] != 0) || (white->rowStoneCount[i] != 0) ||
            (black->colStoneCount[i] != 0) || (white->colStoneCount[i] != 0) ||
            (black->ruStoneCount[i] != 0) || (white->ruStoneCount[i] != 0) ||
            (black->rdStoneCount[i] != 0) || (white->rdStoneCount[i] != 0))
        {
            if ((black->rowStoneCount[i] != 0) || (white->rowStoneCount[i] != 0))
            {
                printf("%d열-검은돌:%d, 흰돌:%d, ", i, black->rowStoneCount[i], white->rowStoneCount[i]);

                if (black->rowComboCount[i] > white->rowComboCount[i])
                {
                    printf("연속 돌 = 흑돌 %d/ ", black->rowComboCount[i]);
                }
                else if (black->rowComboCount[i] < white->rowComboCount[i])
                {
                    printf("연속 돌 = 백돌 %d/ ", white->rowComboCount[i]);
                }
                else if (black->rowComboCount[i] < white->rowComboCount[i])
                {
                    printf("두돌 연속갯수 %d/ ", white->rowComboCount[i]);
                }
            }

            if ((black->colStoneCount[i] != 0) || (white->colStoneCount[i] != 0))
            {
                printf("%d행-검은돌:%d, 흰돌:%d, ", i, black->colStoneCount[i], white->colStoneCount[i]);

                if (black->colComboCount[i] > white->colComboCount[i])
                {
                    printf("연속 돌 = 흑돌 %d/ ", black->colComboCount[i]);
                }
                else if (black->colComboCount[i] < white->colComboCount[i])
                {
                    printf("연속 돌 = 백돌 %d/ ", white->colComboCount[i]);
                }
                else if (black->colComboCount[i] < white->colComboCount[i])
                {
                    printf("두돌 연속갯수 %d/ ", white->colComboCount[i]);
                }
            }

            if ((black->ruStoneCount[i] != 0) || (white->ruStoneCount[i] != 0))
            {
                printf("%d우상향-검은돌:%d, 흰돌:%d, ", i, black->ruStoneCount[i], white->ruStoneCount[i]);

                if (black->ruComboCount[i] > white->ruComboCount[i])
                {
                    printf("연속 돌 = 흑돌 %d/ ", black->ruComboCount[i]);
                }
                else if (black->ruComboCount[i] < white->ruComboCount[i])
                {
                    printf("연속 돌 = 백돌 %d/ ", white->ruComboCount[i]);
                }
                else if (black->ruComboCount[i] < white->ruComboCount[i])
                {
                    printf("두돌 연속갯수 %d/ ", white->ruComboCount[i]);
                }
            }

            if ((black->rdStoneCount[i] != 0) || (white->rdStoneCount[i] != 0))
            {
                printf("%d우하향-검은돌:%d, 흰돌:%d, ", i, black->rdStoneCount[i], white->rdStoneCount[i]);

                if (black->rdComboCount[i] > white->rdComboCount[i])
                {
                    printf("연속 돌 = 흑돌 %d/", black->rdComboCount[i]);
                }
                else if (black->rdComboCount[i] < white->rdComboCount[i])
                {
                    printf("연속 돌 = 백돌 %d/", white->rdComboCount[i]);
                }
                else if (black->rdComboCount[i] < white->rdComboCount[i])
                {
                    printf("두돌 연속갯수 %d/", white->rdComboCount[i]);
                }
            }
            printf("\n");
        }
    }
    for (int i = 0; i < BOARD; ++i)
    {
        printf("%d ", black->colComboCount[i]);
    }

    printf("\n");

    for (int i = 0; i < BOARD; ++i)
    {
        printf("%d ", black->rowComboCount[i]);
    }

    printf("\n");

    for (int i = 0; i < BOARD * 2; ++i)
    {
        printf("%d ", black->ruComboCount[i]);
    }

    printf("\n");

    for (int i = 0; i < BOARD * 2; ++i)
    {
        printf("%d ", black->rdComboCount[i]);
    }

    printf("\n");

    for (int i = 0; i < BOARD; ++i)
    {
        printf("%d ", white->colComboCount[i]);
    }

    printf("\n");

    for (int i = 0; i < BOARD; ++i)
    {
        printf("%d ", white->rowComboCount[i]);
    }

    printf("\n");

    for (int i = 0; i < BOARD * 2; ++i)
    {
        printf("%d ", white->ruComboCount[i]);
    }

    printf("\n");

    for (int i = 0; i < BOARD * 2; ++i)
    {
        printf("%d ", white->rdComboCount[i]);
    }

    printf("\n");

    int index = 0;
    int max = 0;
    for (int i = 0; i < BOARD; ++i)
    {
        if (max < black->colComboCount[i])
        {
            index = i;
            max = black->colComboCount[i];
        }
    }
    printf("%d 행 검은돌 최대 콤보 : %d\n", index, max);

    index = 0;
    max = 0;

    for (int i = 0; i < BOARD; ++i)
    {
        if (max < white->colComboCount[i])
        {
            index = i;
            max = white->colComboCount[i];
        }
    }
    printf("%d 행 흰돌 최대 콤보 : %d\n", index, max);

    index = 0;
    max = 0;

    for (int i = 0; i < BOARD; ++i)
    {
        if (max < black->rowComboCount[i])
        {
            index = i;
            max = black->rowComboCount[i];
        }
    }
    printf("%d 열 검은돌 최대 콤보 : %d\n", index, max);

    index = 0;
    max = 0;

    for (int i = 0; i < BOARD; ++i)
    {
        if (max < white->rowComboCount[i])
        {
            index = i;
            max = white->rowComboCount[i];
        }
    }
    printf("%d 열 흰돌 최대 콤보 : %d\n", index, max);

    index = 0;
    max = 0;

    for (int i = 0; i < BOARD * 2; ++i)
    {
        if (max < white->ruComboCount[i])
        {
            index = i;
            max = white->ruComboCount[i];
        }
    }
    printf("%d 우상향 흰돌 최대 콤보 : %d\n", index, max);


    index = 0;
    max = 0;

    for (int i = 0; i < BOARD * 2; ++i)
    {
        if (max < black->ruComboCount[i])
        {
            index = i;
            max = black->ruComboCount[i];
        }
    }
    printf("%d 우상향 검은돌 최대 콤보 : %d\n", index, max);

    index = 0;
    max = 0;

    for (int i = 0; i < BOARD * 2; ++i)
    {
        if (max < white->rdComboCount[i])
        {
            index = i;
            max = white->rdComboCount[i];
        }
    }
    printf("%d 우하향 흰돌 최대 콤보 : %d\n", index, max);


    index = 0;
    max = 0;

    for (int i = 0; i < BOARD * 2; ++i)
    {
        if (max < black->rdComboCount[i])
        {
            index = i;
            max = black->rdComboCount[i];
        }
    }
    printf("%d 우하향 검은돌 최대 콤보 : %d\n", index, max);
}

void CheckBoard(int board[][BOARD], stone* black, stone* white)
{
    ClearStone(black, white);
    RowCheck(board, black, white);
    ColumnCheck(board, black, white);
    RightUpCheck(board, black, white);
    RightDownCheck(board, black, white);
}

void RowCheck(int board[][BOARD], stone* black, stone* white)
{
    for (int i = 0; i < BOARD; ++i)
    {
        for (int j = 0; j < BOARD; ++j)
        {
            if (board[i][j] == BLACK)
            {
                black->rowStoneCount[i]++;
            }
            else if (board[i][j] == WHITE)
            {
                white->rowStoneCount[i]++;
            }
            else if (board[i][j] == 0)
            {
                continue;
            }

            int comboCount = 0;
            int nowType = board[i][j];

            for (int k = j; j < BOARD; ++k)
            {
                if (board[i][k] == nowType)
                {
                    comboCount++;
                }
                else
                {
                    break;
                }
            }

            if (nowType == BLACK)
            {
                if (black->rowComboCount[i] < comboCount)
                {
                    black->rowComboCount[i] = comboCount;
                }
            }
            else if (nowType == WHITE)
            {
                if (white->rowComboCount[i] < comboCount)
                {
                    white->rowComboCount[i] = comboCount;
                }
            }
        }
    }

}

void ColumnCheck(int board[][BOARD], stone* black, stone* white)
{
    for (int i = 0; i < BOARD; ++i)
    {
        for (int j = 0; j < BOARD; ++j)
        {
            if (board[j][i] == BLACK)
            {
                black->colStoneCount[i]++;
            }
            else if (board[j][i] == WHITE)
            {
                white->colStoneCount[i]++;
            }
            else if (board[j][i] == 0)
            {
                continue;
            }

            int comboCount = 0;
            int nowType = board[i][j];

            for (int k = j; j < BOARD; ++k)
            {
                if (board[k][i] == nowType)
                {
                    comboCount++;
                }
                else
                {
                    break;
                }
            }

            if (nowType == BLACK)
            {
                if (black->colComboCount[i] < comboCount)
                {
                    black->colComboCount[i] = comboCount;
                }
            }
            else if (nowType == WHITE)
            {
                if (white->colComboCount[i] < comboCount)
                {
                    white->colComboCount[i] = comboCount;
                }
            }
        }
    }
}

void RightUpCheck(int board[][BOARD], stone* black, stone* white)
{
    int rightUpIndex = 0;
    for (int i = 0; i < BOARD; ++i, ++rightUpIndex)
    {
        for (int j = 0; j < i + 1; ++j)
        {
            if (board[j][i] == BLACK)
            {
                black->ruStoneCount[rightUpIndex]++;
            }
            else if (board[j][i] == WHITE)
            {
                white->ruStoneCount[rightUpIndex]++;
            }
            else if (board[j][i] == 0)
            {
                continue;
            }

            int comboCount = 0;
            int nowType = board[i - j][j];

            for (int k = j; k < i + 1; ++k)
            {
                if (board[i - j][j] == nowType)
                {
                    comboCount++;
                }
                else
                {
                    break;
                }
            }

            if (nowType == BLACK)
            {
                if (black->ruComboCount[rightUpIndex] < comboCount)
                {
                    black->ruComboCount[rightUpIndex] = comboCount;
                }
            }
            else if (nowType == WHITE)
            {
                if (white->ruComboCount[rightUpIndex] < comboCount)
                {
                    white->ruComboCount[rightUpIndex] = comboCount;
                }
            }
        }
    }

    for (int i = 1; i < BOARD; ++i, ++rightUpIndex)
    {
        for (int j = BOARD - 1; j >= i; --j)
        {
            if (board[j][(BOARD - 1) + (i - j)] == BLACK)
            {
                black->ruStoneCount[rightUpIndex]++;
            }
            else if (board[j][(BOARD - 1) + (i - j)] == WHITE)
            {
                white->ruStoneCount[rightUpIndex]++;
            }
            else if (board[j][(BOARD - 1) + (i - j)] == 0)
            {
                continue;
            }

            int comboCount = 0;
            int nowType = board[i - j][(BOARD - 1) + (i - j)];

            for (int k = j; k >= i + 1; --k)
            {
                if (board[k][(BOARD - 1) + (i - k)] == nowType)
                {
                    comboCount++;
                }
                else
                {
                    break;
                }
            }

            if (nowType == BLACK)
            {
                if (black->ruComboCount[rightUpIndex] < comboCount)
                {
                    black->ruComboCount[rightUpIndex] = comboCount;
                }
            }
            else if (nowType == WHITE)
            {
                if (white->ruComboCount[rightUpIndex] < comboCount)
                {
                    white->ruComboCount[rightUpIndex] = comboCount;
                }
            }
        }
    }
}

void RightDownCheck(int board[][BOARD], stone* black, stone* white)
{
    int rightDownIndex = 0;
    for (int i = BOARD - 1; i >= 0; --i, ++rightDownIndex)
    {
        for (int j = 0; j < BOARD - i; ++j)
        {
            if (board[i + j][i] == BLACK)
            {
                black->rdStoneCount[rightDownIndex]++;
            }
            else if (board[i + j][i] == WHITE)
            {
                white->rdStoneCount[rightDownIndex]++;
            }
            else if (board[i + j][i] == 0)
            {
                continue;
            }

            int comboCount = 0;
            int nowType = board[i + j][j];

            for (int k = j; k < i + 1; ++k)
            {
                if (board[i + k][j] == nowType)
                {
                    comboCount++;
                }
                else
                {
                    break;
                }
            }

            if (nowType == BLACK)
            {
                if (black->rdComboCount[rightDownIndex] < comboCount)
                {
                    black->rdComboCount[rightDownIndex] = comboCount;
                }
            }
            else if (nowType == WHITE)
            {
                if (white->rdComboCount[rightDownIndex] < comboCount)
                {
                    white->rdComboCount[rightDownIndex] = comboCount;
                }
            }
        }
    }

    for (int i = 1; i < BOARD; ++i, ++rightDownIndex)
    {
        for (int j = 0; j < BOARD - 1; ++j)
        {
            if (board[j][i + j] == BLACK)
            {
                black->rdStoneCount[rightDownIndex]++;
            }
            else if (board[j][i + j] == WHITE)
            {
                white->rdStoneCount[rightDownIndex]++;
            }
            else if (board[j][i + j] == 0)
            {
                continue;
            }

            int comboCount = 0;
            int nowType = board[j][i + j];

            for (int k = j; k < BOARD - i; ++k)
            {
                if (board[k][i + k] == nowType)
                {
                    comboCount++;
                }
                else
                {
                    break;
                }
            }

            if (nowType == BLACK)
            {
                if (black->rdComboCount[rightDownIndex] < comboCount)
                {
                    black->rdComboCount[rightDownIndex] = comboCount;
                }
            }
            else if (nowType == WHITE)
            {
                if (white->rdComboCount[rightDownIndex] < comboCount)
                {
                    white->rdComboCount[rightDownIndex] = comboCount;
                }
            }
        }
    }
}

void Save(int board[][BOARD], stone* black, stone* white, int flag)
{
    FILE* fp;

    fp = fopen("saveData.bin", "wb");

    for (int i = 0; i < BOARD; ++i)
    {
        for (int j = 0; j < BOARD; ++j)
        {
            fprintf(fp, "%d ", board[i][j]);
        }
    }
    fprintf(fp, "%d ", flag);
    fclose(fp);
}

void Load(int board[][BOARD], stone* black, stone* white, int* flag)
{
    InitBoard(board);
    FILE* fp;

    fp = fopen("saveData.bin", "rb");

    for (int i = 0; i < BOARD; ++i)
    {
        for (int j = 0; j < BOARD; ++j)
        {
            fscanf(fp, "%d ", &board[i][j]);

            if (board[i][j] == BLACK)
            {
                black->stack[black->stackIndex].x = j;
                black->stack[black->stackIndex].y = i;
                black->stackIndex++;
            }
            else if (board[i][j] == WHITE)
            {
                white->stack[white->stackIndex].x = j;
                white->stack[white->stackIndex].y = i;
                white->stackIndex++;
            }
        }
    }

    fscanf(fp, "%d ", flag);

    fclose(fp);
}

void Undo(int board[][BOARD], stone* black, stone* white, int* flag)
{
    if (*flag == WHITE)
    {
        if (black->stackIndex-- <= 0)
        {
            printf("BLACK Stack UnderFlow\n");
            return;
        }

        black->backUpStack[black->backUpIndex].x = black->stack[black->stackIndex].x;
        black->backUpStack[black->backUpIndex].y = black->stack[black->stackIndex].y;
        black->backUpIndex++;

        board[black->stack[black->stackIndex].y][black->stack[black->stackIndex].x] = 0;
        memset(&black->stack[black->stackIndex], 0, sizeof(stack));
        *flag *= -1;
    }
    else if (*flag == BLACK)
    {
        if (white->stackIndex-- <= 0)
        {
            printf("WHITE Stack UnderFlow\n");
            return;
        }

        white->backUpStack[white->backUpIndex].x = white->stack[white->stackIndex].x;
        white->backUpStack[white->backUpIndex].y = white->stack[white->stackIndex].y;
        white->backUpIndex++;

        board[white->stack[white->stackIndex].y][white->stack[white->stackIndex].x] = 0;
        memset(&white->stack[white->stackIndex], 0, sizeof(stack));
        *flag *= -1;
    }
    else
    {

    }
}

void UndoUndo(int board[][BOARD], stone* black, stone* white, int* flag)
{
    if (*flag == BLACK)
    {
        if (black->backUpIndex-- <= 0)
        {
            printf("BLACK Stack UnderFlow\n");
            return;
        }

        board[black->backUpStack[black->backUpIndex].y][black->backUpStack[black->backUpIndex].x] = BLACK;
        black->stackIndex++;
        black->backUpStack[black->backUpIndex].x = 0;
        black->backUpStack[black->backUpIndex].y = 0;
        *flag *= -1;
    }
    else if (*flag == WHITE)
    {
        if (white->backUpIndex-- <= 0)
        {
            printf("WHITE Stack UnderFlow\n");
            return;
        }

        board[white->backUpStack[white->backUpIndex].y][white->backUpStack[white->backUpIndex].x] = WHITE;
        white->stackIndex++;
        white->backUpStack[white->backUpIndex].x = 0;
        white->backUpStack[white->backUpIndex].y = 0;
        *flag *= -1;
    }
    else
    {

    }
}
