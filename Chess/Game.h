#ifndef GAME_H
#define GAME_H

//包含必要的头文件#include <iostream>
#include <SFML/Graphics.hpp>
#include "Piece.h"//包含棋子头文件


//定义必要的宏
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800
#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8
#define GRIDSIZE 100
#define SCALE 1
#define TIMELIMIT 300



using namespace sf;

class Game {
public:
	
	Game();//声明默认构造函数
	~Game();//声明默认析构函数
	typedef void (Game::*logicFncPtr)(Piece*);//自定义数据类型 Game类 logic类的函数指针
	typedef std::map<PieceType, logicFncPtr> LogicCall;//自定义数据类型 Map储存logic类的函数指针，并使用PieceType访问
	
	LogicCall logicCall;//储存逻辑函数指针，使用PieceType调用

	sf::RenderWindow window;	

	
	Piece* board[BOARD_HEIGHT][BOARD_WIDTH];//游戏棋盘数组
	std::vector<std::vector<std::vector<Piece*>>> vectBoard;//储存棋盘每一步的数据 用于悔棋
	Piece* lastFirstMovePawn;//上一个做出第一次移动操作且步进两格的兵
	
	Clock clock = Clock::Clock();//计时器
	Font font;Text text;//字体
	int //棋盘上存活的棋子
		whiteKing,
		whiteQueen,
		whiteRook,
		whiteKnight,
		whiteBishop,
		whitePawn,
		blackKing,
		blackQueen,
		blackRook,
		blackKnight,
		blackBishop,
		blackPawn;
	bool
		isGameBegin,//游戏是否开始
		isChessBegin,//开始对弈
		isGameover,//游戏是否结束
		isGamequit,//是否退出游戏
		isPieceClick,//上一次点击是否是棋子
		isMoveClick,//是否是移动操作
		isEatClick,//是否是吃子操作
		isEnPassant,//是否能进行吃过路兵操作
		isWhiteCastling,//白方能否进行王车易位操作
		isBlackCastling;//黑方能否进行王车易位操作
	Camp
		currentSelectCamp,//当前选择的棋子的阵营
		currentOperateCamp;//当前应该进行操作的阵营
	Texture//创建纹理实例
		tInitial,
		tTitle,
		tBeginText,
		tBoard,
		tHighlighted,
		tHighlightedWithBorder,
		tSelected,
		tSelectedWithBorder,
		tPrompt_Background,
		tPrompt_CampWhite,
		tPrompt_CampBlack,
		tPrompt_BlackClock,
		tPrompt_WhiteClock,
		tPrompt_BlackIcon,
		tPrompt_WhiteIcon,
		tPrompt_BlackPieces,
		tPrompt_WhitePieces,
		tPrompt_Restart,
		tPrompt_Undo,
		tPrompt_Die,
		tWhiteKing,
		tWhiteQueen,
		tWhiteRook,
		tWhiteBishop,
		tWhiteKnight,
		tWhitePawn,
		tBlackKing,
		tBlackQueen,
		tBlackRook,
		tBlackBishop,
		tBlackKnight,
		tBlackPawn;
	Sprite//创建精灵实例
		sInitial,
		sTitle,
		sBeginText,
		sBoard,
		sHighlighted,
		sHighlightedWithBorder,
		sSelected,
		sSelectedWithBorder,
		sPrompt_Background,
		sPrompt_CampWhite,
		sPrompt_CampBlack,
		sPrompt_BlackClock,
		sPrompt_WhiteClock,
		sPrompt_BlackIcon,
		sPrompt_WhiteIcon,
		sPrompt_BlackPieces,
		sPrompt_WhitePieces,
		sPrompt_Restart,
		sPrompt_Undo,
		sPrompt_Die,
		sWhiteKing,
		sWhiteQueen,
		sWhiteRook,
		sWhiteBishop,
		sWhiteKnight,
		sWhitePawn,
		sBlackKing,
		sBlackQueen,
		sBlackRook,
		sBlackBishop,
		sBlackKnight,
		sBlackPawn;

	int searchType[8][2]{//搜索类型的预定义数组
		{1,1},//右下
		{-1,-1},//左上
		{-1,1},//右上
		{1,-1},//左下
		{0,1},//右
		{0,-1},//左
		{1,0},//下
		{-1,0}//上
	};
	int knightMove[8][2]{//马的移动预定义数组
		{-1,-2},
		{-1, 2},
		{-2,-1},
		{-2, 1},
		{1,-2},
		{1, 2},
		{2,-1},
		{2, 1}
	};
	int targetPosition[2];//目标移动位置数组 行和列
	
	void Initial();//初始化总函数
	void initBoard();//初始化棋盘
	void initMedia();//绑定纹理和精灵
	void initPrompt();//初始化状态栏区的数据
	void initFntMapping();//初始化函数指针映射

	void Logic();//游戏逻辑主函数
	void logicTurnCamp();//改变阵营逻辑函数
	void logicKing(Piece* piece);//王的逻辑函数
	void logicQueen(Piece* piece);//后的逻辑函数
	void logicRook(Piece* piece);//车的逻辑函数
	void logicBishop(Piece* piece);//象的逻辑函数
	void logicKnight(Piece* piece);//马的逻辑函数
	void logicPawn(Piece* piece);//兵的逻辑函数
	void logicEnPassant(int row, int column, Pawn* pawn);
	void logicPromotion(Pawn* pawn);//晋升的逻辑函数
	void logicCastling();//王车易位函数 施工中
	void logicSearch(int row, int column, int searchType[]);//逻辑递归查找函数
	void logicMove(int targetRow, int targetColumn, Piece* piece);//逻辑移动函数
	void logicEat(int targetRow, int targetColumn, Piece* piece);//逻辑吃子函数 基于逻辑移动函数
	void logicUndo();//逻辑悔棋函数
	void logicRestart();//逻辑重开函数
	void logicSave();//逻辑储存函数
	void logicCheckLive();//逻辑检查存活数

	void Input();//游戏输入主函数
	void RButtonDown(Vector2i mPoint);//鼠标右键点击
	void LButtonDown(Vector2i mPoint);//鼠标左键点击

	void Draw();//游戏绘制主函数
	void drawInitial();//绘制初始界面
	void drawBoard();//绘制棋盘
	void drawPrompt();//绘制状态栏
	void drawPieces();//绘制棋子
	void drawDie();//绘制死亡
	void drawText();//绘制字体
	void drawSprite(Sprite sprite, int x, int y);//绘制精灵的工具函数 需要指定精灵和位置

	void Run();//游戏运行入口函数

	/// <summary>
	/// 调试类函数 正常情况下不调用
	/// </summary>
	/// <param name="sprite"></param>
	void CheckSprite(Sprite* sprite);//输出Sprite 所处的位置和纹理
	void CheckCamp(Piece* piece);//输出Piece所属的阵营
	void CheckClick();//检测点击点的棋子数据
	void CheckPieceByRC(int row, int column);//通过行和列打印对应棋子的数据
	void CheckPieceByPtr(Piece* piece);//通过指针打印对应棋子的数据
	void CheckLastFirstMovePawn();//打印第一次移动两格的兵
	void CheckCastling();//检测是否能进行王车易位
	void CheckLive();//打印场上存活数
};
#endif // !GAME_H