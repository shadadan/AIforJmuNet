// Jingziqi.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include<stdio.h>
#include<Windows.h>

const int ROW = 3;
const int COL = 3;
int chessboard[ROW][COL];
int score[ROW][COL];

void Initmap();
void Showmap();        //��ӡ���
bool isWin();        //�ж��Ƿ���һ����ʤ
bool isFull();        //�ж������Ƿ�Ϊ��
void PcPlay();        //��������
void HumanPlay();    //������

int main()
{
    Initmap();
    Showmap();
    while ((!isFull()) && (!isWin()))
    {
        HumanPlay();
      
        Showmap();
        if (isWin())
            break;

        Sleep(500);    //ģ��ʵ�ʹ��̣��õ������㣬hh
        PcPlay();
   
        Showmap();
    }

    if (isFull())
        printf("\n\n201621123066�͵���������\n");

    system("pause");
    return 0;
}

void Initmap()
{
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            chessboard[i][j] = 1;
}

void Showmap()
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (chessboard[i][j] == 1)    //"1"�����
                printf(" |");
            if (chessboard[i][j] == 2)    //"2"������
                printf("x|");
            if (chessboard[i][j] == 5)    //"5"�������
                printf("o|");
        }
        printf("\n");
    }
}

bool isWin()
{
    int sum = 0;
    for (int i = 0; i < ROW; i++)      //��ÿ���ж��Ƿ��ʤ
    {
        for (int j = 0; j < COL; j++)
            sum += chessboard[i][j];

        if (sum == 6)
        {
            printf("201621123066��ʤ��\n");
            return true;
        }
        if (sum == 15)
        {
            printf("AI��ʤ��\n");
            return true;
        }
        sum = 0;
    }

    for (int j = 0; j < ROW; j++)      //��ÿ���ж��Ƿ��ʤ
    {
        for (int i = 0; i < COL; i++)
            sum += chessboard[i][j];

        if (sum == 6)
        {
            printf("201621123066��ʤ��ʤ��\n");
            return true;
        }
        if (sum == 15)
        {
            printf("AI��ʤ��\n");
            return true;
        }
        sum = 0;
    }

    for (int i = 0; i < ROW; i++)     //�ԶԽ����ж��Ƿ��ʤ
        sum += chessboard[i][i];
    if (sum == 6)
    {
        printf("201621123066��ʤ��ʤ��\n");
        return true;
    }
    if (sum == 15)
    {
        printf("AI��ʤ��\n");
        return true;
    }

    sum = 0;
    for (int i = 0; i < ROW; i++)     //�Է��Խ����ж��Ƿ��ʤ
        sum += chessboard[i][2 - i];
    if (sum == 6)
    {
        printf("201621123066��ʤ��ʤ��\n");
        return true;
    }
    if (sum == 15)
    {
        printf("AI��ʤ��\n");
        return true;
    }

    return false;
}

bool isFull()
{
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            if (chessboard[i][j] == 1)
                return false;
    return true;
}

void HumanPlay()
{
    int x, y;
    printf("���������ӵĺ�����X:");
    scanf_s("%d", &x);
    printf("���������ӵ�������Y:");
    scanf_s("%d", &y);

    while (x < 1 || x>3 || y < 1 || y>3)
    {
        printf("\n����ȷ���룡\n");
        printf("x,y������1~3\n\n");

        printf("���������ӵĺ�����X:");
        scanf_s("%d", &x);
        printf("���������ӵ�������Y:");
        scanf_s("%d", &y);
    }

    while (chessboard[x-1][y- 1] != 1)
    {
        printf("\n\n��λ���ѱ�ռ�ã�\n");
        printf("��ѡ����ȷ��λ��\n\n");
        Sleep(1000);

        printf("\n���������ӵĺ�����X:");
        scanf_s("%d", &x);
        printf("���������ӵ�������Y:");
        scanf_s("%d", &y);
    }

    chessboard[x-1][y - 1] = 2;
}

void PcPlay(int num)
{
    int sum = 0;
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            score[i][j] = 0;

    // ��ÿ�н��з���ͳ��
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
            sum += chessboard[i][j];

        switch (sum)
        {
        case 3:                     //1+1+1;��Ҫ�ԣ����;Ȩ�أ�1
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[i][k] == 1)
                    score[i][k] += 1;
            }
            break;
        case 4:                     //1+1+2;��Ҫ�ԣ��ε�;Ȩ�أ�10
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[i][k] == 1)
                    score[i][k] += 10;
            }
            break;
        case 8:                    //1+2+5;��Ҫ�ԣ��ϵͣ�Ȩֵ50
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[i][k] == 1)
                    score[i][k] += 50;
            }
            break;
        case 7:                     //1+1+5;��Ҫ�ԣ��ϸ�;Ȩ�أ�200
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[i][k] == 1)
                    score[i][k] += 200;     //�����е���Ҫ�ԱȶԽ��߸�
            }
            break;
        case 5:                     //1+2+2;��Ҫ�ԣ��θ�;Ȩ�أ�500
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[i][k] == 1)
                    score[i][k] += 500;
            }
            break;
        case 11:                     //1+5+5;��Ҫ�ԣ����;Ȩ�أ�1000
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[i][k] == 1)
                    score[i][k] += 1000;
            }
            break;
        }
        sum = 0;
    }

    // ��ÿ�н��з���ͳ��
    for (int j = 0; j < COL; j++)
    {
        for (int i = 0; i < ROW; i++)
            sum += chessboard[i][j];

        switch (sum)
        {
        case 3:                   
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[k][j] == 1)
                    score[k][j] += 1;
            }
            break;
        case 4:                    
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[k][j] == 1)
                    score[k][j] += 10;
            }
            break;
        case 8:                    
            for (int k = 0; k <
                COL; k++)
            {
                if (chessboard[k][j] == 1)
                    score[k][j] += 50;
            }
            break;
        case 7:                    
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[k][j] == 1)     //1+1+5;��Ҫ�ԣ��ϸ�;Ȩ�أ�200
                    score[k][j] += 200;  
            }
            break;
        case 5:                    
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[k][j] == 1)
                    score[k][j] += 500;
            }
            break;
        case 11:                  
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[k][j] == 1)
                    score[k][j] += 1000;
            }
            break;
        }
        sum = 0;
    }

    // �ԶԽ��߽��з���ͳ��
    for (int i = 0; i < ROW; i++)
        sum += chessboard[i][i];
    switch (sum)
    {
    case 3:                    
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][i] == 1)
                score[i][i] += 1;
        }
        break;
    case 4:                   
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][i] == 1)
                score[i][i] += 10;
        }
        break;
    case 8:                
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][i] == 1)
                score[i][i] += 50;
        }
        break;
    case 7:                     //1+1+5;Ȩ�أ�100
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][i] == 1)
                score[i][i] += 100;
        }
        break;
    case 5:                
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][i] == 1)
                score[i][i] += 500;
        }
        break;
    case 11:                    
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][i] == 1)
                score[i][i] += 1000;
        }
        break;
    }

    // �Է��Խ��߽��з���ͳ��
    sum = 0;
    for (int i = 0; i < ROW; i++)
        sum += chessboard[i][2 - i];
    switch (sum)
    {
    case 3:                    
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][2 - i] == 1)
                score[i][2 - i] += 1;
        }
        break;
    case 4:                    
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][2 - i] == 1)
                score[i][2 - i] += 10;
        }
        break;
    case 8:
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][2 - i] == 1)
                score[i][2 - i] += 50;
        }
        break;
    case 7:                     
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][2 - i] == 1)    //1+1+5;Ȩ�أ�100
                score[i][2 - i] += 100;
        }
        break;
    case 5:                   
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][2 - i] == 1)
                score[i][2 - i] += 500;
        }
        break;
    case 11:                    
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][2 - i] == 1)
                score[i][2 - i] += 1000;
        }
        break;
    }

    int maxRow = 0, maxCol = 0;
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
        {
            if (score[i][j] > score[maxRow][maxCol])
            {
                maxRow = i;
                maxCol = j;
            }
        }
		chessboard[maxRow][maxCol] = num;
}