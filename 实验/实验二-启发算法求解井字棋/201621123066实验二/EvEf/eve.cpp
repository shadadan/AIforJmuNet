// EvEf.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include<conio.h> 
#include<stdlib.h>
#define COM -1 
#define MAN 1
#define STEP 9 
#define DRAW 0 
#define ROW 3 
#define COL 3
#define MAX_NUM 1000;
 
 
struct Move
{
	int x;
	int y;
 
};
 
//棋盘
int board[3][3] = { { 0,0,0 },
					{ 0,0,0 },
					{ 0,0,0 }
};
int tempBoard[3][3] = { { 0,0,0 },
						{ 0,0,0 },
						{ 0,0,0 }
};

//最好的一步
Move bestMove;
//当前深度
int currentDepth;
//谁先走
bool MAN_first = true;
 
 
//判断输赢
int isWin() {
	int i, j;
 
	for (int i = 0; i < 3; i++)
	{
		if (board[i][0] + board[i][1] + board[i][2] == 3)
			return 1;
		else if (board[i][0] + board[i][1] + board[i][2] == -3)
			return -1;
	}
	for (int j = 0; j < 3; j++)
	{
		if (board[0][j] + board[1][j] + board[2][j] == 3)
			return 1;
		else if (board[0][j] + board[1][j] + board[2][j] == -3)
			return -1;
	}
	if (board[0][0] + board[1][1] + board[2][2] == 3 || board[0][2] + board[1][1] + board[2][0] == 3)
		return 1;
	else if (board[0][0] + board[1][1] + board[2][2] == -3 || board[0][2] + board[1][1] + board[2][0] == -3)
		return -1;
	else  return 0;
 
}
 
//评估函数
int evaluteMap() {
 
	bool flag = true;
	int i, j;
 
	if (isWin() == COM)
		return MAX_NUM;//如果计算机赢了，返回最大值 
	if (isWin() == MAN)
		return -MAX_NUM;//如果计算机输了，返回最小值 
	//for (i = 0; i < 3; i++)
	//	for (j = 0; j < 3; j++)
	//		if (board[i][j] == 0)
	//		{
	//			flag = false;
	//			break;
	//		}
	//if (flag)  //如果Flag为真  ， 棋盘都满了  就退出  
	//	return 0;
 
 
	int count = 0;//该变量用来表示评估函数的值
				  //将棋盘中的空格填满自己的棋子，既将棋盘数组中的0变为1
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			if (board[i][j] == 0)
				tempBoard[i][j] = COM;
			else
				tempBoard[i][j] = board[i][j];
		}
	//电脑一方
	//计算每一行中有多少行的棋子连成3个的
	for (i = 0; i < 3; i++)
		count += (tempBoard[i][0] + tempBoard[i][1] + tempBoard[i][2]) / 3;
	for (i = 0; i < 3; i++)
		count += (tempBoard[0][i] + tempBoard[1][i] + tempBoard[2][i]) / 3;
	count += (tempBoard[0][0] + tempBoard[1][1] + tempBoard[2][2]) / 3;
	count += (tempBoard[2][0] + tempBoard[1][1] + tempBoard[0][2]) / 3;
 
 
 
	//将棋盘中的空格填满对方的棋子，既将棋盘数组中的0变为-1
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			if (board[i][j] == 0)
				tempBoard[i][j] = MAN;
			else tempBoard[i][j] = board[i][j];
		}
	//对方
	//计算每一行中有多少行的棋子连成3个的
	for (i = 0; i < 3; i++)
		count += (tempBoard[i][0] + tempBoard[i][1] + tempBoard[i][2]) / 3;
	for (i = 0; i < 3; i++)
		count += (tempBoard[0][i] + tempBoard[1][i] + tempBoard[2][i]) / 3;
	count += (tempBoard[0][0] + tempBoard[1][1] + tempBoard[2][2]) / 3;
	count += (tempBoard[2][0] + tempBoard[1][1] + tempBoard[0][2]) / 3;
 
 
 
 
	return count;
}
 
 

 
//得到有空位的集合
int getMoveList(Move moveList[]) {
	int moveCount = 0;
	int i, j;
	for (i = 0; i < COL; i++)
	{
		for (j = 0; j < ROW; j++)
		{
			if (board[i][j] == 0)
			{
				moveList[moveCount].x = i;
				moveList[moveCount].y = j;
				moveCount++;
			}
 
		}
	}
	return moveCount; //返回一共多少个空的位置 
}
 
 void makeMove(Move curMove)
{
	board[curMove.x][curMove.y] = 0;

}
 
void unMakeMove(Move curMove) {
	board[curMove.x][curMove.y] =1;
}

int miniMaxsearch(int depth)
{
	int value;  //估值 
	int bestValue = 0; //最好的估值
	int moveCount = 0;
	int i; int m, n;
	Move moveList[9];//保存可以下子的位置
	if (isWin() == COM || isWin() == MAN)
	{
		return evaluteMap();  //一般是返回极大极小值
	}
	//如果搜索深度耗尽 ， 返回估值 
	if (depth == 0)
	{
		return evaluteMap();
	}
	if (depth==3) {
		bestValue = -MAX_NUM;
	}
	else if (depth==2)
	{
		bestValue = MAX_NUM;
	}

 
	//一共多少步
	moveCount = getMoveList(moveList);
 
	for (i = 0; i < moveCount; i++)
	{
		Move curMove = moveList[i];
 
		makeMove(curMove);
		value = miniMaxsearch(depth - 1);
		unMakeMove(curMove);
 
		if (depth==2)
		{
			if (value > bestValue)
			{
				bestValue = value;
				if (depth == currentDepth)
				{
					bestMove = curMove;
				}
			}
		}
		else if (depth==3)
		{
			if (value < bestValue)
			{
				bestValue = value;
				if (depth == currentDepth)
				{
					bestMove = curMove;
				}
			}
		}
 
	}
	 
	return bestValue;
}
 
 
//打印棋盘 电脑X  ，玩家O 
void printBoard() {
	int i, j;
	for (i = 0; i < COL; i++)
	{
		printf("-------------\n");
		for (j = 0; j < ROW; j++)
		{
			if (board[i][j] == COM)
			{
				printf("| X ");
			}
			else if (board[i][j] == MAN)
			{
				printf("| O ");
			}
			else
			{
				printf("|   ");
			}
 
		}
		printf("|\n");
	}
	printf("-------------\n");
 
}
 
 
 
void  com_play1(int currentDepth) {
	miniMaxsearch(currentDepth);
	board[bestMove.x][bestMove.y] = COM;
   
}
 void  com_play2(int currentDepth) {
	miniMaxsearch(currentDepth);
	board[bestMove.x][bestMove.y] = MAN;
	
}

 
 
 
 
 
 

 
 
void main()
{   int win =0;
    int lose=0;
	int equ=0;
	int pc1depth  =3;
	int pc2depth  =2;
	for(int i=0;i<50;i++){
	 for(int step=0;step<9;){
		 com_play1(pc1depth);
		 if(-1==isWin()){
			 printBoard();
			 printf("电脑1赢啦");
			 win++;
			 break;
		 }
		 step++;
		  if (step ==10) {
			  printBoard();
				printf("平局 ~~~");
				equ++;
				break;
			}
		 com_play2(pc2depth);
		 if(1==isWin()){
			 printBoard();
			 printf("电脑1输啦");
			 lose++;
			 break;
		 }
		 step++;
		
	}	
}
	printf("平局次数%d,pc1赢得次数%d,输得次数%d",equ,win,lose);
	system("pause");
	
}