12345



#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <stack>
using namespace std;



const int MAX_LEN = 10;										//	地图行列数最大值
State Map[MAX_LEN][MAX_LEN] = { BLOCK };					//	地图
MapPos Parent[MAX_LEN][MAX_LEN] = { {-1, -1} };				//	记录每个节点的父节点
int PathLen[MAX_LEN][MAX_LEN] = { -1 };						//	记录每个节点距起始点的路径长度
const int   rule[][2] = { {-1, 0},		//  上				//	访问规则（访问规则）
{0, -1},		//  左
{1, 0},			//	下
{0, 1} };		//	右
MapPos fromPos, endPos;										//	起始节点、目的节点
int m = 0, n = 0;											//	输入地图的行列数
hello, lyf
void Input( int m, int n );
int IsAccess( const MapPos *pos );
int Bfs( MapPos SrcPos, MapPos DstPos );


int _tmain(int argc, _TCHAR* argv[])
{

	char c = '\0';											//	控制循环退出
	int Len = 0, i = 0;
	stack<MapPos> Path;										//	记录路径
	MapPos tmp;

	while( 1 )
	{
		scanf( "%d", &m );
		scanf( "%d", &n );
		fflush( stdin );

		Input( m, n );													//	获取地图

		if( 1 == Bfs( fromPos, endPos ) )								//	给出BFS搜索结果
		{
			printf( "Y\n");												

			printf( "The shortest Pathlenth is : %d\n", Len = PathLen[endPos.x][endPos.y] );	//	给出最短路径长度

			printf( "The Path is:  " );															//	给出最短搜索路径
			tmp = endPos;
			for( i=0; i<Len+1; i++ )
			{
				Path.push( tmp );
				tmp = Parent[tmp.x][tmp.y];
			}
			while( !Path.empty() )
			{
				tmp = Path.top();
				Path.pop();
				printf( "( %d, %d ) ", tmp.x, tmp.y );
			}
		}
		else
		{
			printf( "N" );
		}
		fflush( stdin );																	//	控制循环输入或退出
		printf( "\n输入字符q退出 or 任意其他字符开始\n" );
		scanf( "%c", &c );
		if( 'q' == c )
			break;

		//	复位
		memset( Map, BLOCK, MAX_LEN * MAX_LEN *sizeof(int) );
	}

	system( "pause" );
	return 0;
}


/**************************************************************************************
* Author：				Sky
* Date:					2014/08/25
* Functiuon：			input          
* Description：			根据输入构建地图（所谓构建地图，就是对每个点/路径着状态）    
* Access Level：			NULL
* Input：				m ---- 地图大小（行数）  
n ---- 地图大小（列数）
* Output：				NULL       
* Return：				NULL      
**************************************************************************************/
void Input( int m, int n )
{
	int i = 0, j = 0;
	char tmp[MAX_LEN] = {'\0'};

	for( i=0; i<m; i++ )
	{

		gets( tmp );

		for( j=0; j<n; j++ )
		{
			switch( tmp[j] )
			{
			case '-':
				Map[i][j] = PASS;
				break;
			case '#':
				Map[i][j] = BLOCK;
				break; 
			case 'B':
				Map[i][j] = PASS;
				fromPos.x = i;
				fromPos.y = j;
				break;
			case 'H':
				Map[i][j] = PASS;
				endPos.x = i;
				endPos.y = j;
				break;
			default:
				break;
			}
		}
	}
}

/************************************************************************************** 
* Author：               Sky 
* Date:                  2014/08/26
* Functiuon：            Bfs
* Description：          以SrcPos为起点进行广度优先搜索，知道搜索到DstPos为止     
* Access Level：			 NULL
* Input：				 SrcPos ------- 搜索起点                  
DstPos ------- 搜索目的点
* Output：               NULL      
* Return：				 0/1    -------  失败/成功 
**************************************************************************************/  
int Bfs( MapPos SrcPos, MapPos DstPos )
{
	int x = SrcPos.x, y = SrcPos.y;
	queue<MapPos> Q;									//	记录发现点（灰色）
	MapPos CurPos;										//	当前位置节点
	MapPos AdjPos;										//	暂存当前节点的邻接节点
	int IsArrive = 0;									//	是否到达目的节点
	int i = 0;

	Map[SrcPos.x][SrcPos.y] = VISITED;					//	发现起始点
	Q.push( SrcPos );									//	将起始点加入发现队列
	Parent[SrcPos.x][SrcPos.y].x = -1;					//	保存起始点的父节点（无）
	Parent[SrcPos.x][SrcPos.y].y = -1;
	PathLen[SrcPos.x][SrcPos.y] = 0;					//	保存起始点距离起始点的路径长度
	while( !Q.empty() )
	{
		//	如果到达目的节点，不再搜索
		if( 1 == IsArrive )
			break;

		//	取出队头节点
		CurPos = Q.front();
		Q.pop();

		for( i=0; i<4; i++ )
		{

			if( 1 == IsArrive )
				break;

			AdjPos.x = CurPos.x + rule[i][0];
			AdjPos.y = CurPos.y + rule[i][1];

			if( AdjPos.x == DstPos.x && AdjPos.y == DstPos.y )
			{
				IsArrive = 1;													//	到达目的节点

				Map[AdjPos.x][AdjPos.y] = VISITED;								//	着色

				Parent[AdjPos.x][AdjPos.y].x = CurPos.x;						//	记录父节点
				Parent[AdjPos.x][AdjPos.y].y = CurPos.y;

				PathLen[AdjPos.x][AdjPos.y] = PathLen[CurPos.x][CurPos.y] + 1;	//	记录路径长度

				break;															//	停止搜索
			}
			else
			{
				if( 1 == IsAccess( &AdjPos ) )					//	可访问的邻接节点（发现邻接节点）
				{

					Map[AdjPos.x][AdjPos.y] = VISITED;			//	置状态已发现（白色）
					Parent[AdjPos.x][AdjPos.y].x = CurPos.x;	//	记录父节点
					Parent[AdjPos.x][AdjPos.y].y = CurPos.y;
					PathLen[AdjPos.x][AdjPos.y] = PathLen[CurPos.x][CurPos.y] + 1;	//	记录路径长度

					Q.push( AdjPos );							//	加入发现队列
				}
			}

		}
	}

	return IsArrive;
}


/************************************************************************************** 
* Author：               Sky 
* Date:                  2014/08/26 
* Functiuon：            IsAccess
* Description：          当前节点是否可被访问/发现，若可访问返回1，不可访问则返回0     
* Access Level：         NULL
* Input：                Pos ----- 节点位置                          
* Output：               NULL       
* Return：				0/1  ----- 不可访问/可访问
**************************************************************************************/  
int IsAccess( const MapPos *pos )
{
	int x = pos->x, y = pos->y;
	int rt = 1;

	if( x<0 || x>=m || y<0 || y>=n )
		rt = 0;

	if( VISITED == Map[x][y] )
		rt = 0;
	else if( BLOCK == Map[x][y] )
		rt = 0;

	return rt;
}