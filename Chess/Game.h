#ifndef GAME_H
#define GAME_H

//������Ҫ��ͷ�ļ�#include <iostream>
#include <SFML/Graphics.hpp>
#include "Piece.h"//��������ͷ�ļ�


//�����Ҫ�ĺ�
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
	
	Game();//����Ĭ�Ϲ��캯��
	~Game();//����Ĭ����������
	typedef void (Game::*logicFncPtr)(Piece*);//�Զ����������� Game�� logic��ĺ���ָ��
	typedef std::map<PieceType, logicFncPtr> LogicCall;//�Զ����������� Map����logic��ĺ���ָ�룬��ʹ��PieceType����
	
	LogicCall logicCall;//�����߼�����ָ�룬ʹ��PieceType����

	sf::RenderWindow window;	

	
	Piece* board[BOARD_HEIGHT][BOARD_WIDTH];//��Ϸ��������
	std::vector<std::vector<std::vector<Piece*>>> vectBoard;//��������ÿһ�������� ���ڻ���
	Piece* lastFirstMovePawn;//��һ��������һ���ƶ������Ҳ�������ı�
	
	Clock clock = Clock::Clock();//��ʱ��
	Font font;Text text;//����
	int //�����ϴ�������
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
		isGameBegin,//��Ϸ�Ƿ�ʼ
		isChessBegin,//��ʼ����
		isGameover,//��Ϸ�Ƿ����
		isGamequit,//�Ƿ��˳���Ϸ
		isPieceClick,//��һ�ε���Ƿ�������
		isMoveClick,//�Ƿ����ƶ�����
		isEatClick,//�Ƿ��ǳ��Ӳ���
		isEnPassant,//�Ƿ��ܽ��гԹ�·������
		isWhiteCastling,//�׷��ܷ����������λ����
		isBlackCastling;//�ڷ��ܷ����������λ����
	Camp
		currentSelectCamp,//��ǰѡ������ӵ���Ӫ
		currentOperateCamp;//��ǰӦ�ý��в�������Ӫ
	Texture//��������ʵ��
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
	Sprite//��������ʵ��
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

	int searchType[8][2]{//�������͵�Ԥ��������
		{1,1},//����
		{-1,-1},//����
		{-1,1},//����
		{1,-1},//����
		{0,1},//��
		{0,-1},//��
		{1,0},//��
		{-1,0}//��
	};
	int knightMove[8][2]{//����ƶ�Ԥ��������
		{-1,-2},
		{-1, 2},
		{-2,-1},
		{-2, 1},
		{1,-2},
		{1, 2},
		{2,-1},
		{2, 1}
	};
	int targetPosition[2];//Ŀ���ƶ�λ������ �к���
	
	void Initial();//��ʼ���ܺ���
	void initBoard();//��ʼ������
	void initMedia();//������;���
	void initPrompt();//��ʼ��״̬����������
	void initFntMapping();//��ʼ������ָ��ӳ��

	void Logic();//��Ϸ�߼�������
	void logicTurnCamp();//�ı���Ӫ�߼�����
	void logicKing(Piece* piece);//�����߼�����
	void logicQueen(Piece* piece);//����߼�����
	void logicRook(Piece* piece);//�����߼�����
	void logicBishop(Piece* piece);//����߼�����
	void logicKnight(Piece* piece);//����߼�����
	void logicPawn(Piece* piece);//�����߼�����
	void logicEnPassant(int row, int column, Pawn* pawn);
	void logicPromotion(Pawn* pawn);//�������߼�����
	void logicCastling();//������λ���� ʩ����
	void logicSearch(int row, int column, int searchType[]);//�߼��ݹ���Һ���
	void logicMove(int targetRow, int targetColumn, Piece* piece);//�߼��ƶ�����
	void logicEat(int targetRow, int targetColumn, Piece* piece);//�߼����Ӻ��� �����߼��ƶ�����
	void logicUndo();//�߼����庯��
	void logicRestart();//�߼��ؿ�����
	void logicSave();//�߼����溯��
	void logicCheckLive();//�߼��������

	void Input();//��Ϸ����������
	void RButtonDown(Vector2i mPoint);//����Ҽ����
	void LButtonDown(Vector2i mPoint);//���������

	void Draw();//��Ϸ����������
	void drawInitial();//���Ƴ�ʼ����
	void drawBoard();//��������
	void drawPrompt();//����״̬��
	void drawPieces();//��������
	void drawDie();//��������
	void drawText();//��������
	void drawSprite(Sprite sprite, int x, int y);//���ƾ���Ĺ��ߺ��� ��Ҫָ�������λ��

	void Run();//��Ϸ������ں���

	/// <summary>
	/// �����ຯ�� ��������²�����
	/// </summary>
	/// <param name="sprite"></param>
	void CheckSprite(Sprite* sprite);//���Sprite ������λ�ú�����
	void CheckCamp(Piece* piece);//���Piece��������Ӫ
	void CheckClick();//����������������
	void CheckPieceByRC(int row, int column);//ͨ���к��д�ӡ��Ӧ���ӵ�����
	void CheckPieceByPtr(Piece* piece);//ͨ��ָ���ӡ��Ӧ���ӵ�����
	void CheckLastFirstMovePawn();//��ӡ��һ���ƶ�����ı�
	void CheckCastling();//����Ƿ��ܽ���������λ
	void CheckLive();//��ӡ���ϴ����
};
#endif // !GAME_H