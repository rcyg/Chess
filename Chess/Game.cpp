#include "Game.h"

Game::Game() {
	window.create(//创建窗口
		VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), L"Chess by berrySoda"
	);
}
Game::~Game() {

}

void Game::Initial() {
	window.setFramerateLimit(60);//设置目标帧数
	isGameBegin = false;
	isChessBegin = false;
	isGameover = false;
	isGamequit = false;
	isPieceClick = false;
	isMoveClick = false;
	isEatClick = false;
	isEnPassant = false;
	isWhiteCastling = false;
	isBlackCastling = false;
	lastFirstMovePawn = NULL;
	currentSelectCamp = Camp::Null;
	currentOperateCamp = Camp::White;//白方先行
	initBoard();
	initMedia();
	initFntMapping();
	clock.restart();//重开计时器
}
void Game::initPrompt() {
	/// <summary>
	/// 先初始化为零 之后使用logicCheckLive函数异步更新
	/// </summary>
	whiteKing = blackKing = 0;
	whiteQueen = blackQueen = 0;
	whiteRook = blackRook = 0;
	whiteKnight = blackKnight = 0;
	whiteBishop = blackBishop = 0;
	whitePawn = blackPawn = 0;
}
void Game::initBoard() {
	vectBoard.clear();//清空棋盘记录数组
	for (int i = 0; i < BOARD_HEIGHT; ++i) {
		for (int j = 0; j < BOARD_WIDTH; ++j) {
			switch (i)
			{
			case 0://第一行 黑方
				switch (j){
					case 0://黑车
					case 7:
						board[i][j] = new Rook(false, Camp::Black, std::make_pair(i, j));
						break;
					case 1://黑马
					case 6:
						board[i][j] = new Knight(false, Camp::Black, std::make_pair(i, j));
						break;
					case 2://黑象
					case 5:
						board[i][j] = new Bishop(false, Camp::Black, std::make_pair(i, j));
						break;
					case 3://黑王
						board[i][j] = new Queen(false, Camp::Black, std::make_pair(i, j));
						break;
					case 4://黑后
						board[i][j] = new King(false, Camp::Black, std::make_pair(i, j));
						break;
					default:
						break;
				}
				break;
			case 1://第二行 均为黑兵
				board[i][j] = new Pawn(false, Camp::Black, std::make_pair(i,j),true);
				break;
			case 6://第七行 均为白兵
				board[i][j] = new Pawn(false, Camp::White, std::make_pair(i, j),true);
				break;
			case 7://第八行 白方
				switch (j){
					case 0://白车
					case 7:
						board[i][j] = new Rook(false, Camp::White, std::make_pair(i, j));
						break;
					case 1://白马
					case 6:
						board[i][j] = new Knight(false, Camp::White, std::make_pair(i, j));
						break;
					case 2://白象
					case 5:
						board[i][j] =  new Bishop(false, Camp::White, std::make_pair(i, j));
						break;
					case 3://白后
						board[i][j] = new Queen(false, Camp::White, std::make_pair(i, j));						
						break;
					case 4://白王
						board[i][j] = new King(false, Camp::White, std::make_pair(i, j));
						break;
					default:
						break;
				}
				break;
			default://初始化为空地
				board[i][j] = new Piece(true, Camp::Null, std::make_pair(i, j));
				break;
			}
		/*	std::cout << "isEmpty: " << (board[i][j]->isEmpty ? "true" : "false") << std::endl;
			std::cout << "isPress: " << (board[i][j]->isPress ? "true" : "false") << std::endl;
			std::cout << "row: " << board[i][j]->position.first << " column: " << board[i][j]->position.second << std::endl;
			std::cout << (board[i][j]->camp == Camp::Null ? "Null" : (board[i][j]->camp == Camp::Black ? "Black" : "White")) << std::endl;*/
		}
	}
	//system("pause");
}
void Game::initMedia() {
	//从data文件夹中加载字体
	if (!font.loadFromFile("data/font/Inter-VariableFont_slnt,wght.ttf"))
		std::cout << "字体 未找到" << std::endl;
	text.setFont(font);
	//从data文件夹中加载棋盘和棋子的纹理
	if (!tInitial.loadFromFile("data/texture/Map/InitialMasked.png"))
		std::cout << "初始界面 未找到" << std::endl;
	if (!tTitle.loadFromFile("data/texture/Map/Title.png"))
		std::cout << "Chess标题 未找到" << std::endl;
	if (!tBeginText.loadFromFile("data/texture/Map/beginText.png"))
		std::cout << "beginText 未找到" << std::endl;
	if (!tBoard.loadFromFile("data/texture/Map/pink.png"))
		std::cout << "棋盘 未找到" << std::endl;
	if (!tHighlighted.loadFromFile("data/texture/Map/highlighted.png"))
		std::cout << "高亮格 未找到" << std::endl;
	if (!tHighlightedWithBorder.loadFromFile("data/texture/Map/highlightedWithBorder.png"))
		std::cout << "高亮格(白边） 未找到" << std::endl;
	if (!tSelected.loadFromFile("data/texture/Map/selected.png"))
		std::cout << "选择格 未找到" << std::endl;
	if (!tSelectedWithBorder.loadFromFile("data/texture/Map/selectedWithBorder.png"))
		std::cout << "选择格（白边） 未找到" << std::endl;
	if (!tPrompt_Background.loadFromFile("data/texture/Prompt/prompt_background.png"))
		std::cout << "状态栏 背景 未找到" << std::endl;
	if (!tPrompt_CampWhite.loadFromFile("data/texture/Prompt/prompt_camp_white.png"))
		std::cout << "状态栏 白方 未找到" << std::endl;
	if (!tPrompt_CampBlack.loadFromFile("data/texture/Prompt/prompt_camp_black.png"))
		std::cout << "状态栏 黑方 未找到" << std::endl;
	if (!tPrompt_BlackClock.loadFromFile("data/texture/Prompt/BlackClock.png"))
		std::cout << "状态栏 BlackClock 未找到" <<std::endl;
	if (!tPrompt_WhiteClock.loadFromFile("data/texture/Prompt/WhiteClock.png"))
		std::cout << "状态栏 WhiteClock 未找到" << std::endl;
	if (!tPrompt_BlackIcon.loadFromFile("data/texture/Prompt/BlackIcon.png"))
		std::cout << "状态栏 BlackIcon 未找到" << std::endl;
	if (!tPrompt_WhiteIcon.loadFromFile("data/texture/Prompt/WhiteIcon.png"))
		std::cout << "状态栏 WhiteIcon 未找到" << std::endl;
	if (!tPrompt_BlackPieces.loadFromFile("data/texture/Prompt/BlackPieces.png"))
		std::cout << "状态栏 BlackPieces 未找到" << std::endl;
	if (!tPrompt_WhitePieces.loadFromFile("data/texture/Prompt/WhitePieces.png"))
		std::cout << "状态栏 WhitePieces 未找到" << std::endl;
	if (!tPrompt_Restart.loadFromFile("data/texture/Prompt/Restart.png"))
		std::cout << "状态栏 Restart 未找到" << std::endl;
	if (!tPrompt_Undo.loadFromFile("data/texture/Prompt/Undo.png"))
		std::cout << "状态栏 Undo 未找到" << std::endl;
	if (!tPrompt_Die.loadFromFile("data/texture/Prompt/Die.png"))
		std::cout << "状态栏 Die 未找到" << std::endl;
	if (!tWhiteKing.loadFromFile("data/texture/White/king.png"))
		std::cout << "白王 未找到" << std::endl;
	if (!tWhiteQueen.loadFromFile("data/texture/White/queen.png"))
		std::cout << "白后 未找到" << std::endl;
	if (!tWhiteRook.loadFromFile("data/texture/White/rook.png"))
		std::cout << "白车 未找到" << std::endl;
	if (!tWhiteBishop.loadFromFile("data/texture/White/bishop.png"))
		std::cout << "白象 未找到" << std::endl;
	if (!tWhiteKnight.loadFromFile("data/texture/White/knight.png"))
		std::cout << "白马 未找到" << std::endl;
	if (!tWhitePawn.loadFromFile("data/texture/White/pawn.png"))
		std::cout << "白兵 未找到" << std::endl;
	if (!tBlackKing.loadFromFile("data/texture/Black/king.png"))
		std::cout << "黑王 未找到" << std::endl;
	if (!tBlackQueen.loadFromFile("data/texture/Black/queen.png"))
		std::cout << "黑后 未找到" << std::endl;
	if (!tBlackRook.loadFromFile("data/texture/Black/rook.png"))
		std::cout << "黑车 未找到" << std::endl;
	if (!tBlackBishop.loadFromFile("data/texture/Black/bishop.png"))
		std::cout << "黑象 未找到" << std::endl;
	if (!tBlackKnight.loadFromFile("data/texture/Black/knight.png"))
		std::cout << "黑马 未找到" << std::endl;
	if (!tBlackPawn.loadFromFile("data/texture/Black/pawn.png"))
		std::cout << "黑兵 未找到" << std::endl;
	//给每一个精灵绑定纹理 并设置放缩
	sInitial.setTexture(tInitial);sInitial.setScale(SCALE, SCALE);//
	sTitle.setTexture(tTitle);sTitle.setScale(SCALE, SCALE);
	sBeginText.setTexture(tBeginText);sBeginText.setScale(SCALE, SCALE);
	sBoard.setTexture(tBoard);sBoard.setScale(SCALE, SCALE);
	sHighlighted.setTexture(tHighlighted);sHighlighted.setScale(SCALE, SCALE);
	sHighlightedWithBorder.setTexture(tHighlightedWithBorder);sHighlightedWithBorder.setScale(SCALE, SCALE);
	sSelected.setTexture(tSelected);sSelected.setScale(SCALE, SCALE);
	sSelectedWithBorder.setTexture(tSelectedWithBorder);sSelectedWithBorder.setScale(SCALE, SCALE);
	sPrompt_Background.setTexture(tPrompt_Background);sPrompt_Background.setScale(SCALE, SCALE);
	sPrompt_CampWhite.setTexture(tPrompt_CampWhite);sPrompt_CampWhite.setScale(0.5, 0.5);
	sPrompt_CampBlack.setTexture(tPrompt_CampBlack);sPrompt_CampBlack.setScale(0.5, 0.5);
	sPrompt_BlackClock.setTexture(tPrompt_BlackClock);sPrompt_BlackClock.setScale(SCALE,SCALE);
	sPrompt_WhiteClock.setTexture(tPrompt_WhiteClock);sPrompt_WhiteClock.setScale(SCALE, SCALE);
	sPrompt_BlackIcon.setTexture(tPrompt_BlackIcon);sPrompt_BlackIcon.setScale(SCALE, SCALE);
	sPrompt_WhiteIcon.setTexture(tPrompt_WhiteIcon);sPrompt_WhiteIcon.setScale(SCALE, SCALE);
	sPrompt_BlackPieces.setTexture(tPrompt_BlackPieces);sPrompt_BlackPieces.setScale(SCALE, SCALE);
	sPrompt_WhitePieces.setTexture(tPrompt_WhitePieces);sPrompt_WhitePieces.setScale(SCALE, SCALE);
	sPrompt_Restart.setTexture(tPrompt_Restart);sPrompt_Restart.setScale(SCALE, SCALE);
	sPrompt_Undo.setTexture(tPrompt_Undo);sPrompt_Undo.setScale(SCALE, SCALE);
	sPrompt_Die.setTexture(tPrompt_Die);sPrompt_Die.setScale(SCALE, SCALE);
	sWhiteKing.setTexture(tWhiteKing);sWhiteKing.setScale(SCALE, SCALE);
	sWhiteQueen.setTexture(tWhiteQueen);sWhiteQueen.setScale(SCALE, SCALE);
	sWhiteRook.setTexture(tWhiteRook);sWhiteRook.setScale(SCALE, SCALE);
	sWhiteBishop.setTexture(tWhiteBishop);sWhiteBishop.setScale(SCALE, SCALE);
	sWhiteKnight.setTexture(tWhiteKnight);sWhiteKnight.setScale(SCALE, SCALE);
	sWhitePawn.setTexture(tWhitePawn);sWhitePawn.setScale(SCALE, SCALE);
	sBlackKing.setTexture(tBlackKing);sBlackKing.setScale(SCALE, SCALE);
	sBlackQueen.setTexture(tBlackQueen);sBlackQueen.setScale(SCALE, SCALE);
	sBlackRook.setTexture(tBlackRook);sBlackRook.setScale(SCALE, SCALE);
	sBlackBishop.setTexture(tBlackBishop);sBlackBishop.setScale(SCALE, SCALE);
	sBlackKnight.setTexture(tBlackKnight);sBlackKnight.setScale(SCALE, SCALE);
	sBlackPawn.setTexture(tBlackPawn);sBlackPawn.setScale(SCALE, SCALE);
}
void Game::initFntMapping() {
	logicCall[PieceType::King] = &Game::logicKing;
	logicCall[PieceType::Queen] = &Game::logicQueen;
	logicCall[PieceType::Rook] = &Game::logicRook;
	logicCall[PieceType::Knight] = &Game::logicKnight;
	logicCall[PieceType::Bishop] = &Game::logicBishop;
	logicCall[PieceType::Pawn] = &Game::logicPawn;
}

void Game::Logic() {
	/// <summary>
	/// 逻辑函数
	/// 主要处理棋子移动、高亮、吃子的情况
	/// </summary>
	logicCheckLive();
	if (isPieceClick) {//如果是棋子选中状态
		for (auto& row : board) {
			for (auto& piece : row) {
				if (piece->isEmpty == false //棋子不为空
					&& piece->isPress == true //棋子已经被选中
					&& currentSelectCamp == currentOperateCamp) {//选中的棋子与当前操作阵营相同
					if (!isMoveClick && !isEatClick) {//棋子未移动
						piece->isHighlighted = true;//先设置棋子自身的高亮
						(this->*logicCall[piece->GetPieceType()])(piece);
						switch (piece->GetPieceType()) {//根据棋子类型设置对应棋子的高亮
							case PieceType::King:
								//logicKing(piece);//检测是否能王车易位
								if (isWhiteCastling) 
									board[7][7]->isHighlighted = true;//设置右下角的车高亮
								if (isBlackCastling) 
									board[0][0]->isHighlighted = true;//设置左上角的车高亮
								break;
							case PieceType::Queen:
								//logicQueen(piece);
								break;
							case PieceType::Rook:
								//logicRook(piece);
								break;
							case PieceType::Bishop:
								//logicBishop(piece);
								break;
							case PieceType::Knight:
								//logicKnight(piece);
								break;
							case PieceType::Pawn:
								//logicPawn(dynamic_cast<Pawn*>(piece));
								break;
						}
					}
					else if(isMoveClick){//棋子移动
						if (lastFirstMovePawn != NULL)
							if (piece->GetPieceType() == PieceType::Pawn) {
								switch (piece->camp)
								{
								case Camp::White:
									if (targetPosition[0] == lastFirstMovePawn->position.first - 1
										&& targetPosition[1] == lastFirstMovePawn->position.second)
										isEnPassant = true;
										break;
								case Camp::Black:
									if (targetPosition[0] == lastFirstMovePawn->position.first + 1
										&& targetPosition[1] == lastFirstMovePawn->position.second)
										isEnPassant = true;
									break;
								default:
									break;
								}
							}
								
						logicMove(targetPosition[0], targetPosition[1], piece);
						isPieceClick = false;
						isMoveClick = false;
						logicTurnCamp();//改变操作阵营
					}
					else if (isEatClick) {//吃子操作
						logicEat(targetPosition[0], targetPosition[1], piece);
						isPieceClick = false;
						isEatClick = false;
						logicTurnCamp();//改变操作阵营
					}
					
				}
			}
		}
		logicCastling();
	}
	else {
		for(auto& row: board)
			for (auto& piece : row) {
				piece->isHighlighted = false;
			}
		
	}
}
void Game::logicTurnCamp() {
	currentSelectCamp = Camp::Null;
	if (currentOperateCamp == Camp::White)
		currentOperateCamp = Camp::Black;
	else
		currentOperateCamp = Camp::White;
	clock.restart();
}
void Game::logicKing(Piece* piece){
	//获取王所在的行和列
	int row = piece->position.first;
	int column = piece->position.second;
	for (int i = row - 1; i < row + 2; ++i) {//王的八邻域遍历
		for (int j = column - 1; j < column + 2; ++j) {
			if (i >= 0 && i < BOARD_HEIGHT && j >= 0 && j < BOARD_WIDTH) {//防止数组越界
				if (board[i][j]->isEmpty == true || board[i][j]->camp != piece->camp)//如果为空，则高亮
					board[i][j]->isHighlighted = true;
				
			}
		}
	}

}
void Game::logicQueen(Piece* piece){
	//获取后所在的行和列
	int row = piece->position.first;
	int column = piece->position.second;
	
	for (auto& searchType : searchType) {
		logicSearch(row, column, searchType);
	}
}
void Game::logicRook(Piece* piece) {
	//获取车所在的行和列
	int row = piece->position.first;
	int column = piece->position.second;

	for (int i = 4; i < 8; ++i) {
		logicSearch(row, column, searchType[i]);
	}
}
void Game::logicBishop(Piece* piece) {
	//获取象所在的行和列
	int row = piece->position.first;
	int column = piece->position.second;
	for (int i = 0; i < 4; ++i) {
		logicSearch(row, column, searchType[i]);
	}
}
void Game::logicKnight(Piece* piece) {
	//获取马所在的行和列
	int row = piece->position.first;
	int column = piece->position.second;
	//L型移动 马是唯一一个可以越过棋子的棋子
	//太好啦 马只用检测八个点
	for (auto& moveType : knightMove) {//预先定义的马移动数组
		if (row + moveType[0] >= 0//防止数组越界
			&& row + moveType[0] < BOARD_HEIGHT
			&& column + moveType[1] >= 0
			&& column + moveType[1] < BOARD_WIDTH) {
			if (board[row + moveType[0]][column + moveType[1]]->isEmpty == true 
				|| board[row + moveType[0]][column + moveType[1]]->camp != board[row][column]->camp) {//若为空，则高亮
				board[row + moveType[0]][column + moveType[1]]->isHighlighted = true;
			}
		}
	}
}
void Game::logicPawn(Piece* piece) {
	//获取兵所在的行和列
	Pawn* pawn = dynamic_cast<Pawn*>(piece);//先转换为指定类型的指针
	int row = pawn->position.first;
	int column = pawn->position.second;
	//兵第一次可以移动两格，需要检测是否是第一次移动
	//兵的正常移动
	switch (pawn->camp){
	case Camp::White:
		if (pawn->isFirstMove) {
			if (row - 1 >= 0
				&& row - 1 < BOARD_HEIGHT) {//上方一格
				if (board[row - 1][column]->isEmpty == true) {
					board[row - 1][column]->isHighlighted = true;
					if (row - 2 >= 0
						&& row - 2 < BOARD_HEIGHT) {//上方两格
						if (board[row - 2][column]->isEmpty == true)
							board[row - 2][column]->isHighlighted = true;
					}
				}	
			}
		}
		else {
			if (row - 1 >= 0
				&& row - 1 < BOARD_HEIGHT) {//上方一格
				if (board[row - 1][column]->isEmpty == true) {
					board[row - 1][column]->isHighlighted = true;
				}

			}
		}
		if (row - 1 >= 0
			&& row - 1 < BOARD_HEIGHT
			&& column - 1 >= 0
			&& column - 1 < BOARD_WIDTH) {//左上方
			if (board[row - 1][column - 1]->isEmpty == false
				&& board[row - 1][column - 1]->camp != pawn->camp)
				board[row - 1][column - 1]->isHighlighted = true;
		}
		if (row - 1 >= 0
			&& row - 1 < BOARD_HEIGHT
			&& column + 1 >= 0
			&& column + 1 < BOARD_WIDTH) {//右上方
			if (board[row - 1][column + 1]->isEmpty == false
				&& board[row - 1][column + 1]->camp != pawn->camp)
				board[row - 1][column + 1]->isHighlighted = true;
		}
		break;
	case Camp::Black:
		if (pawn->isFirstMove) {
			if (row + 1 >= 0
				&& row + 1 < BOARD_HEIGHT) {//下方一格
				if (board[row + 1][column]->isEmpty == true) {
					board[row + 1][column]->isHighlighted = true;
					if (row + 2 >= 0
						&& row + 2 < BOARD_HEIGHT) {//下方两格
						if (board[row + 2][column]->isEmpty == true)
							board[row + 2][column]->isHighlighted = true;
					}
				}

			}
		}
		else {
			if (row + 1 >= 0
				&& row + 1 < BOARD_HEIGHT) {//下方一格
				if (board[row + 1][column]->isEmpty == true) {
					board[row + 1][column]->isHighlighted = true;
				}

			}
		}
		if (row + 1 >= 0
			&& row + 1 < BOARD_HEIGHT
			&& column - 1 >= 0
			&& column - 1 < BOARD_WIDTH) {//左下方
			if (board[row + 1][column - 1]->isEmpty == false
				&& board[row + 1][column - 1]->camp != pawn->camp)
				board[row + 1][column - 1]->isHighlighted = true;
		}
		if (row + 1 >= 0
			&& row + 1 < BOARD_HEIGHT
			&& column + 1 >= 0
			&& column + 1 < BOARD_WIDTH) {//右下方
			if (board[row + 1][column + 1]->isEmpty == false
				&& board[row + 1][column + 1]->camp != pawn->camp)
				board[row + 1][column + 1]->isHighlighted = true;
		}
		break;
	default:
		break;
	}
	logicEnPassant(row, column, pawn);//吃过路兵检测

}
void Game::logicEnPassant(int row, int column, Pawn* pawn) {
	//吃过路兵机制 en passant
	//说明
	//如果上一次移动是敌方兵的第一次移动 而且在同一行的左右两格之一
	//则进入吃过路兵的机制判断
	//黑白方分别判断
	//在设置对应斜前方空格的高亮后，
	//在Logic()函数中加入对应对Pawn类型的检测来实现对isEnPassant的设置
	if (lastFirstMovePawn != NULL) {//不为空 首先上一次移动必须是敌方兵的第一次移动
		if (lastFirstMovePawn->camp != pawn->camp//为不同阵营
			&& lastFirstMovePawn->position.first == pawn->position.first//在同一行
			&& abs(lastFirstMovePawn->position.second - pawn->position.second) == 1) {//在左边或右边一格的位置
			switch (pawn->camp) {
			case Camp::White:
				if (lastFirstMovePawn->position.second - pawn->position.second == -1) {//敌方兵在左侧
					if (board[row - 1][column - 1]->isEmpty == true)//左上方为空
						board[row - 1][column - 1]->isHighlighted = true;
				}
				else {//敌方兵在右侧
					if (board[row - 1][column + 1]->isEmpty == true)//右上方为空
						board[row - 1][column + 1]->isHighlighted = true;
				}
				break;
			case Camp::Black:
				if (lastFirstMovePawn->position.second - pawn->position.second == -1) {//敌方兵在左侧
					if (board[row + 1][column - 1]->isEmpty == true)//左下方为空
						board[row + 1][column - 1]->isHighlighted = true;
				}
				else {//敌方兵在右侧
					if (board[row + 1][column + 1]->isEmpty == true)//右下方为空
						board[row + 1][column + 1]->isHighlighted = true;
				}
				break;
			}
		}
	}
}
void Game::logicPromotion(Pawn* pawn) {
	//兵的晋升 
	switch (pawn->camp) {
	case Camp::White:
		if (pawn->position.first == 0)//白方兵抵达第一行
			pawn->isPromoted = true;
		break;
	case Camp::Black:
		if (pawn->position.first == 7)//黑方兵抵达第八行
			pawn->isPromoted = true;
		break;
	}
	if (pawn->isPromoted)
		board[pawn->position.first][pawn->position.second] = new Queen(false, pawn->camp, pawn->position);
	
}
void Game::logicCastling() {
	//王车易位检测函数 如果符合条件 在王被选择时 同时高亮王和车
	if (currentOperateCamp == Camp::Black) {
		if (board[0][0]->camp == Camp::Black
			&& board[0][4]->camp == Camp::Black
			&& board[0][0]->GetPieceType() == PieceType::Rook
			&& board[0][4]->GetPieceType() == PieceType::King
			&& board[0][1]->isEmpty
			&& board[0][2]->isEmpty
			&& board[0][3]->isEmpty
			)
			isBlackCastling = true;
		else
			isBlackCastling = false;
	}
	else {
		if (board[7][7]->camp == Camp::White
			&& board[7][4]->camp == Camp::White
			&& board[7][7]->GetPieceType() == PieceType::Rook
			&& board[7][4]->GetPieceType() == PieceType::King
			&& board[7][5]->isEmpty
			&& board[7][6]->isEmpty
			)
			isWhiteCastling = true;
		else
			isWhiteCastling = false;
	}
}
void Game::logicSearch(int row, int column, int* searchType) {//若为空 且不越界
	int newRow = row + searchType[0], newColumn = column + searchType[1];
	if (newRow >= 0 && newRow < BOARD_HEIGHT && newColumn >= 0 && newColumn < BOARD_WIDTH) {
		if ((board[newRow][newColumn]->camp != currentSelectCamp
			&& board[newRow][newColumn]->isEmpty == false)) {//如果是敌方棋子在移动范围内
			board[newRow][newColumn]->isHighlighted = true;//设置为高亮
		}
		if (board[newRow][newColumn]->isEmpty == true) {
			board[newRow][newColumn]->isHighlighted = true;//设置为高亮
			logicSearch(newRow, newColumn, searchType);//递归搜索
		}
	}
}
void Game::logicMove(int targetRow, int targetColumn, Piece* piece) {
	
	logicSave();
	board[piece->position.first][piece->position.second] = new Piece(true, Camp::Null, std::make_pair(piece->position.first, piece->position.second));//清空原来位置为空地
	std::pair<int, int> previousPosition = piece->position;//存储上一次位置 用于兵的吃过路兵逻辑判断
	piece->Move(targetPosition[0], targetPosition[1]);//更新棋子位置
	switch (piece->GetPieceType())
	{
	case PieceType::King:
		if (isWhiteCastling
			&&targetPosition[0] == 7
			&&targetPosition[1] == 7
			&&board[7][7]->GetPieceType()==PieceType::Rook
			&&board[7][7]->camp == Camp::White) {
			board[7][6] = new King(false, Camp::White, std::make_pair(7,6));
			dynamic_cast<King*>(board[7][6])->isMoved = false;
			board[7][5] = new Rook(false, Camp::White, std::make_pair(7, 5));
			board[7][7] = new Piece(true, Camp::Null, std::make_pair(7, 7));
			isWhiteCastling = false;
		}
		else if (isBlackCastling
			&&targetPosition[0] == 0
			&&targetPosition[1] == 0
			&&board[0][0]->GetPieceType()==PieceType::Rook
			&&board[0][0]->camp == Camp::Black) {
			board[0][2] = new King(false, Camp::Black, std::make_pair(0,2));
			dynamic_cast<King*>(board[0][2])->isMoved = false;
			board[0][3] = new Rook(false, Camp::Black, std::make_pair(0, 3));
			board[0][0] = new Piece(true, Camp::Null, std::make_pair(0, 0));
			isBlackCastling = false;
		}
		else {
			board[targetPosition[0]][targetPosition[1]] = new King(piece->isEmpty, piece->camp, piece->position);
			dynamic_cast<King*>(board[targetPosition[0]][targetPosition[1]])->isMoved = false;
		}
		break;
	case PieceType::Queen:
		board[targetPosition[0]][targetPosition[1]] = new Queen(piece->isEmpty, piece->camp, piece->position);
		break;
	case PieceType::Rook:
		board[targetPosition[0]][targetPosition[1]] = new Rook(piece->isEmpty, piece->camp, piece->position);
		dynamic_cast<Rook*>(board[targetPosition[0]][targetPosition[1]])->isMoved = false;
		break;
	case PieceType::Bishop:
		board[targetPosition[0]][targetPosition[1]] = new Bishop(piece->isEmpty, piece->camp, piece->position);
		break;
	case PieceType::Knight:
		board[targetPosition[0]][targetPosition[1]] = new Knight(piece->isEmpty, piece->camp, piece->position);
		break;
	case PieceType::Pawn:
		if (lastFirstMovePawn != NULL) {//当上一次的移动是兵的第一次移动
			if (isEnPassant) {//如果是吃过河兵操作
				board[lastFirstMovePawn->position.first][lastFirstMovePawn->position.second] 
					= new Piece(true, Camp::Null, lastFirstMovePawn->position);//把被吃兵清空
				isEnPassant = false;
			}
			lastFirstMovePawn = NULL;
		}

		board[targetPosition[0]][targetPosition[1]] = new Pawn(piece->isEmpty, piece->camp, piece->position,dynamic_cast<Pawn*>(piece)->isFirstMove);//更新移动位置为兵
		
		if (abs(previousPosition.first - targetPosition[0]) == 2) {//若有一个兵移动了两格 则设置为lastFirstMovePawn
			lastFirstMovePawn = board[targetPosition[0]][targetPosition[1]];
		}
		dynamic_cast<Pawn*>(board[targetPosition[0]][targetPosition[1]])->isFirstMove = false;
		logicPromotion(dynamic_cast<Pawn*>(board[targetPosition[0]][targetPosition[1]]));
		break;
	default:
		std::cout << "Null" << std::endl;
		break;
	}
	
}
void Game::logicEat(int targetRow, int targetColumn, Piece* piece) {
	logicMove(targetRow, targetColumn, piece);
	currentSelectCamp = Camp::Null;
}
void Game::logicUndo() {//逻辑悔棋函数
	if (!vectBoard.empty()) {//存在以往棋盘数据
		for (int i = 0; i < BOARD_HEIGHT; ++i) {
			for (int j = 0; j < BOARD_WIDTH; ++j) {
				board[i][j] = vectBoard.back()[i][j];//依次遍历访问到上一步的棋盘数据，依次赋值
			}
		}
		vectBoard.pop_back();//恢复后，将棋盘数据弹出
		logicTurnCamp();//切换阵营
	}
}
void Game::logicRestart() {//逻辑重开函数
	Initial();//重新初始化
	isGameBegin = true;//设置为true 不会返回初始界面
}
void Game::logicSave() {//逻辑储存数组 更新vectBoard
	std::vector<std::vector<Piece*>> multiple;//临时vector
	for (int i = 0; i < BOARD_HEIGHT; ++i) {
		std::vector<Piece*> single;//临时vector
		for (int j = 0; j < BOARD_WIDTH; ++j) {
			
			switch (board[i][j]->GetPieceType())//检测类型 创建copy
			{
				case PieceType::King:
					single.push_back(new King(false, board[i][j]->camp, board[i][j]->position));
					break;
				case PieceType::Queen:
					single.push_back(new Queen(false, board[i][j]->camp, board[i][j]->position));
					break;
				case PieceType::Rook:
					single.push_back(new Rook(false, board[i][j]->camp, board[i][j]->position));
					break;
				case PieceType::Bishop:
					single.push_back(new Bishop(false, board[i][j]->camp, board[i][j]->position));
					break;
				case PieceType::Knight:
					single.push_back(new Knight(false, board[i][j]->camp, board[i][j]->position));
					break;
				case PieceType::Pawn:
					single.push_back(new Pawn(false, board[i][j]->camp, board[i][j]->position,dynamic_cast<Pawn*>(board[i][j])->isFirstMove));
					break;
				case PieceType::Null:
					single.push_back(new Piece(true, board[i][j]->camp, board[i][j]->position));
					break;
				default:
					break;
			}
		}
		multiple.push_back(single);//push到上一层的vector
		single.clear();//push完后清空
	}
	vectBoard.push_back(multiple);//push到总数据中去
	multiple.clear();//push完后清空
	
}
void Game::logicCheckLive() {
	initPrompt();
	for (auto& row : board) {
		for (auto& piece : row) {
			switch (piece->GetPieceType())
			{
			case PieceType::King:
				if (piece->camp == Camp::White)
					whiteKing++;
				else
					blackKing++;
				break;
			case PieceType::Queen:
				if (piece->camp == Camp::White)
					whiteQueen++;
				else
					blackQueen++;
				break;
			case PieceType::Rook:
				if (piece->camp == Camp::White)
					whiteRook++;
				else
					blackRook++;
				break;
			case PieceType::Bishop:
				if (piece->camp == Camp::White)
					whiteBishop++;
				else
					blackBishop++;
				break;
			case PieceType::Knight:
				if (piece->camp == Camp::White)
					whiteKnight++;
				else
					blackKnight++;
				break;
			case PieceType::Pawn:
				if (piece->camp == Camp::White)
					whitePawn++;
				else
					blackPawn++;
				break;
			case PieceType::Null:
				break;
			default:
				break;
			}
		}
	}
}

void Game::Input() {
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {//关闭窗口
			window.close();
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			LButtonDown(Mouse::getPosition(window));
		}
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
			RButtonDown(Mouse::getPosition(window));
		}
	}		
}
void Game::RButtonDown(Vector2i mPoint) {
	if (isGameBegin) {
		//右键取消所有的点击和高亮，遍历棋盘将isPress全设为false
		for (auto& row : board) {
			for (auto& column : row) {
				column->isPress = false;
				column->isHighlighted = false;
				isPieceClick = false;
				isMoveClick = false;
			}
		}
	}
	else
		isGameBegin = true;
	
}
void Game::LButtonDown(Vector2i mPoint) {
	//获取鼠标点击坐标并转换为行和列
	int column = mPoint.x / GRIDSIZE;
	int row = mPoint.y / GRIDSIZE;
	if (isGameBegin) {
		if (!isChessBegin) {
			isChessBegin = true;
			clock.restart();	
		}
			
		if (row >= 0 && row < BOARD_HEIGHT && column >= 0 && column < BOARD_WIDTH) {//防止数组越界 这非常重要
			CheckPieceByRC(row, column);//打印点击前的状态
			if (isPieceClick == false) {//如果还没有选中棋子
				if (board[row][column]->isEmpty == false) {//不为空，是棋子
					if (board[row][column]->camp == currentOperateCamp) {//选择的棋子是当前阵营的
						board[row][column]->isPress = true;//设置isPress为true，方便后续高亮
						currentSelectCamp = board[row][column]->camp;//设置当前已经选中该阵营
						isPieceClick = true;//当前为棋子已选中 未移动状态
					}
				}
			}
			else {//当前已经选中了棋子
				if (board[row][column]->isEmpty == true
					&& board[row][column]->isHighlighted == true) {//如果为空地且高亮 意味着是可行的移动路线
					isMoveClick = true;//移动操作发生
					targetPosition[0] = row;
					targetPosition[1] = column;

				}
				else if (board[row][column]->camp != currentSelectCamp
					&& board[row][column]->isEmpty == false
					&& board[row][column]->isHighlighted == true) {//如果选择的格不为空且阵营不同 则吃子
					//board[row][column]->isTargetd = true;//将对应棋子设置为要被吃掉
					isEatClick = true;//吃子操作发生
					targetPosition[0] = row;
					targetPosition[1] = column;
				}
				else if (board[row][column]->GetPieceType() == PieceType::Rook //点击的是车
					&& (isWhiteCastling || isBlackCastling)) {//任一王车易位可行
					isMoveClick = true;
					targetPosition[0] = row;
					targetPosition[1] = column;
				}
				else {
					for (auto& row : board) {//点击了己方棋子本身或非高亮格 取消移动操作
						for (auto& piece : row) {
							piece->isHighlighted = false;
							piece->isPress = false;
							isPieceClick = false;
							currentSelectCamp = Camp::Null;
						}
					}
				}
			}
			CheckPieceByRC(row, column);//打印点击后的状态
		}
		else {
			if (mPoint.x >= 825 && mPoint.x <= 925 && mPoint.y >= 350 && mPoint.y <= 450) {
				std::cout << "Undo button pressed" << std::endl;
				logicUndo();
			}
			if (mPoint.x >= 1075 && mPoint.x <= 1175 && mPoint.y >= 350 && mPoint.y <= 450) {
				//std::cout << "Restart button pressed" << std::endl;
				logicRestart();
			}
	
		}
	}
	else
		isGameBegin = true;
	
}

void Game::Draw() {
	window.clear();//清屏
	if (isGameBegin) {
		drawBoard();//绘制棋盘
		drawPrompt();//绘制状态栏
		drawPieces();//绘制棋子
	}
	else {
		drawInitial();//绘制初始界面
	}
	window.display();//显示绘制内容
}
void Game::drawInitial() {
	sInitial.setPosition(0, 0);
	window.draw(sInitial);
	sTitle.setPosition(300, 110);
	window.draw(sTitle);
	sBeginText.setPosition(358, 578);
	window.draw(sBeginText);
}
void Game::drawBoard() {
	sBoard.setPosition(0, 0);//设置棋盘的位置
	window.draw(sBoard);//绘制棋盘
	for (auto& row : board) {//设置高亮
		for (auto& column : row) {
			if (column->isHighlighted == true) {//如果被点击，高亮所在格
				drawSprite(sHighlighted, column->position.second * GRIDSIZE, column->position.first*GRIDSIZE);
			}
		}
	}
}
void Game::drawPrompt() {

	
	//请勿随意修改该函数中任何prompt类精灵的位置 
	//Background 800,0
	//BlackClock 825,20
	//WhiteClock 825,680
	//BlackIcon 1075,20
	//WhiteIcon 1075,680
	//BlackPieces 800,175
	//WhitePieces 800,505
	//Undo 825,350
	//Restart 1075,350

	sPrompt_Background.setPosition(8 * GRIDSIZE, 0);//背景位置设置
	window.draw(sPrompt_Background);
	sPrompt_BlackClock.setPosition(825, 20);//黑计时器位置设置
	window.draw(sPrompt_BlackClock);
	sPrompt_WhiteClock.setPosition(825, 680);//白计时器位置设置
	window.draw(sPrompt_WhiteClock);
	sPrompt_BlackIcon.setPosition(1075, 20);//黑标志位置设置
	window.draw(sPrompt_BlackIcon);
	sPrompt_WhiteIcon.setPosition(1075, 680);//白标志位置设置
	window.draw(sPrompt_WhiteIcon);
	sPrompt_BlackPieces.setPosition(800, 175);//黑棋位置设置
	window.draw(sPrompt_BlackPieces);
	sPrompt_WhitePieces.setPosition(800, 505);//白棋位置设置
	window.draw(sPrompt_WhitePieces);
	sPrompt_Undo.setPosition(825, 350);//悔棋按钮位置设置
	window.draw(sPrompt_Undo);
	sPrompt_Restart.setPosition(1075, 350);//重开按钮位置设置
	window.draw(sPrompt_Restart);

	Sprite* temp = new Sprite;
	if (currentOperateCamp == Camp::White) 
		*temp = sPrompt_CampWhite;
	else
		*temp = sPrompt_CampBlack;
	temp->setPosition(950, 350);
	window.draw(*temp);
	delete temp;

	drawText();
	drawDie();
}
void Game::drawDie() {
	//暴力绘制死亡情况
	if (whiteQueen == 0)
		drawSprite(sPrompt_Die, 950, 575);
	if (blackQueen == 0)
		drawSprite(sPrompt_Die, 950, 175);
	if (whiteRook < 2)
		drawSprite(sPrompt_Die, 800, 575);
	if (whiteRook == 0)
		drawSprite(sPrompt_Die, 1150, 575);
	if (blackRook < 2)
		drawSprite(sPrompt_Die, 800, 175);
	if (blackRook == 0)
		drawSprite(sPrompt_Die, 1150, 175);
	if (whiteKnight < 2)
		drawSprite(sPrompt_Die, 850, 575);
	if (whiteKnight == 0)
		drawSprite(sPrompt_Die, 1100, 575);
	if (blackKnight < 2)
		drawSprite(sPrompt_Die, 850, 175);
	if (blackKnight == 0)
		drawSprite(sPrompt_Die, 1100, 175);
	if (whiteBishop < 2)
		drawSprite(sPrompt_Die, 900, 575);
	if (whiteBishop == 0)
		drawSprite(sPrompt_Die, 1050, 575);
	if (blackBishop < 2)
		drawSprite(sPrompt_Die, 900, 175);
	if (blackBishop == 0)
		drawSprite(sPrompt_Die, 1050, 175);
	if (whitePawn < 8)
		drawSprite(sPrompt_Die, 800, 505);
	if (whitePawn < 7)
		drawSprite(sPrompt_Die, 850, 505);
	if (whitePawn < 6)
		drawSprite(sPrompt_Die, 900, 505);
	if (whitePawn < 5)
		drawSprite(sPrompt_Die, 950, 505);
	if (whitePawn < 4)
		drawSprite(sPrompt_Die, 1000, 505);
	if (whitePawn < 3)
		drawSprite(sPrompt_Die, 1050, 505);
	if (whitePawn < 2)
		drawSprite(sPrompt_Die, 1100, 505);
	if (whitePawn == 0)
		drawSprite(sPrompt_Die, 1150, 505);
	if (blackPawn < 8)
		drawSprite(sPrompt_Die, 800, 245);
	if (blackPawn < 7)
		drawSprite(sPrompt_Die, 850, 245);
	if (blackPawn < 6)
		drawSprite(sPrompt_Die, 900, 245);
	if (blackPawn < 5)
		drawSprite(sPrompt_Die, 950, 245);
	if (blackPawn < 4)
		drawSprite(sPrompt_Die, 1000, 245);
	if (blackPawn < 3)
		drawSprite(sPrompt_Die, 1050, 245);
	if (blackPawn < 2)
		drawSprite(sPrompt_Die, 1100, 245);
	if (blackPawn == 0)
		drawSprite(sPrompt_Die, 1150, 245);
}
void Game::drawSprite(Sprite sprite, int x, int y) {
	Sprite* tempSprite = new Sprite;
	*tempSprite = sprite;
	tempSprite->setPosition(x, y);
	window.draw(*tempSprite);
	delete tempSprite;
}
void Game::drawText() {
	if (isChessBegin) {
		int time = clock.getElapsedTime().asSeconds();
		time = TIMELIMIT - time;
		int second = time % 60;
		int minute = time / 60;
		std::string minutes = std::to_string(minute);
		std::string seconds = second < 10 ? (second == 0 ? "00" : "0"+std::to_string(second)) : std::to_string(second);
		text.setString(minutes + ":" + seconds);
		text.setCharacterSize(48);
		if (currentOperateCamp == Camp::White){
			text.setPosition(953, 701);
			text.setFillColor(Color::Color(255, 255, 255, 255));
		}
		else {
			text.setPosition(953, 41);text.setFillColor(Color::Color(0, 0, 0, 255));
		}
		window.draw(text);
	}
}
void Game::drawPieces() {
	for (auto& row: board) {//使用foreach 和 auto 循环棋盘数组
		for (auto& column : row) {
			//column->GetPieceData();//测试用
			int drawPosition_X = column->position.second * GRIDSIZE;
			int drawPosition_Y = column->position.first * GRIDSIZE;
			switch (column->GetPieceType()) {
			case PieceType::Null://空地
				break;
			case PieceType::King://王
				if (column->camp == Camp::Black)
					drawSprite(sBlackKing, drawPosition_X, drawPosition_Y);
				else
					drawSprite(sWhiteKing, drawPosition_X, drawPosition_Y);
				break;
			case PieceType::Queen://后
				if (column->camp == Camp::Black)
					drawSprite(sBlackQueen, drawPosition_X, drawPosition_Y);
				else
					drawSprite(sWhiteQueen, drawPosition_X, drawPosition_Y);
				break;
			case PieceType::Rook://车
				if (column->camp == Camp::Black)
					drawSprite(sBlackRook, drawPosition_X, drawPosition_Y);
				else
					drawSprite(sWhiteRook, drawPosition_X, drawPosition_Y);
				break;
			case PieceType::Bishop://象
				if (column->camp == Camp::Black)
					drawSprite(sBlackBishop, drawPosition_X, drawPosition_Y);
				else
					drawSprite(sWhiteBishop, drawPosition_X, drawPosition_Y);
				break;
			case PieceType::Knight://马
				if (column->camp == Camp::Black)
					drawSprite(sBlackKnight, drawPosition_X, drawPosition_Y);
				else
					drawSprite(sWhiteKnight, drawPosition_X, drawPosition_Y);
				break;
			case PieceType::Pawn://兵
				if (column->camp == Camp::Black)
					drawSprite(sBlackPawn, drawPosition_X, drawPosition_Y);
				else
					drawSprite(sWhitePawn, drawPosition_X, drawPosition_Y);
				break;
			}
		}
	}

}

void Game::Run() {
	do {
		Initial();
		while (window.isOpen() && isGameover == false) {
			
			Input();
			Logic();
			Draw();
		}
	} while (window.isOpen() && !isGamequit);
	/*sBlackKing.setScale(SCALE, SCALE);
	window.draw(sBlackKing);
	window.display();*/
	
}

void Game::CheckSprite(Sprite* sprite) {
	/// <summary>
	/// 打印精灵相关的参数
	/// (x,y)坐标
	/// 放缩系数
	/// 纹理大小
	/// </summary>
	/// <param name="sprite"></param>
	std::cout << "x: " << sprite->getPosition().x << " ";
	std::cout << "y: " << sprite->getPosition().y << std::endl;
	//std::cout << "texture bind: " << sprite->getTexture()->bind << std::endl;
	std::cout << "texture scale: " << sprite->getScale().x << " " << sprite->getScale().y << std::endl;
	std::cout << "texture size: " << sprite->getTexture()->getSize().x 
		<< " " << sprite->getTexture()->getSize().y << std::endl;
}
void Game::CheckCamp(Piece* piece) {
	/// <summary>
	/// 打印棋子所属的阵营
	/// </summary>
	/// <param name="piece"></param>
	std::string camp;
	if (piece->camp == Camp::White)
		camp = "White";
	else if (piece->camp == Camp::Black)
		camp = "Black";
	else
		camp = "Null";
	std::cout << camp << std::endl;
}
void Game::CheckClick() {
	std::cout << "isPieceClick: " << (isPieceClick == true ? "true" : "false") << std::endl;
	std::cout << "isMoveClick: " << (isMoveClick == true ? "true" : "false") << std::endl;

}
void Game::CheckPieceByRC(int row, int column) {
	board[row][column]->GetPieceData();
	switch (board[row][column]->GetPieceType())
	{
	case PieceType::King:
		std::cout << "King" << std::endl;
		break;
	case PieceType::Queen:
		std::cout << "Queen" << std::endl;
		break;
	case PieceType::Rook:
		std::cout << "Rook" << std::endl;
		break;
	case PieceType::Bishop:
		std::cout << "Bishop" << std::endl;
		break;
	case PieceType::Knight:
		std::cout << "Knight" << std::endl;
		break;
	case PieceType::Pawn:
		std::cout << "Pawn" << std::endl;
		std::cout << (dynamic_cast<Pawn*>(board[row][column])->isPromoted ? "true" : "false") << std::endl;
		break;
	default:
		std::cout << "Null" << std::endl;
		break;
	}
}
void Game::CheckPieceByPtr(Piece* piece) {
	piece->GetPieceData();
	switch (piece->GetPieceType())
	{
	case PieceType::King:
		std::cout << "King" << std::endl;
		break;
	case PieceType::Queen:
		std::cout << "Queen" << std::endl;
		break;
	case PieceType::Rook:
		std::cout << "Rook" << std::endl;
		break;
	case PieceType::Bishop:
		std::cout << "Bishop" << std::endl;
		break;
	case PieceType::Knight:
		std::cout << "Knight" << std::endl;
		break;
	case PieceType::Pawn:
		std::cout << "Pawn" << std::endl;
		std::cout << (dynamic_cast<Pawn*>(piece)->isPromoted ? "true" : "false")<< std::endl;
		break;
	default:
		std::cout << "Null" << std::endl;
		break;
	}
}
void Game::CheckLastFirstMovePawn() {
	lastFirstMovePawn->GetPieceData();
	switch (lastFirstMovePawn->GetPieceType())
	{
	case PieceType::King:
		std::cout << "King" << std::endl;
		break;
	case PieceType::Queen:
		std::cout << "Queen" << std::endl;
		break;
	case PieceType::Rook:
		std::cout << "Rook" << std::endl;
		break;
	case PieceType::Bishop:
		std::cout << "Bishop" << std::endl;
		break;
	case PieceType::Knight:
		std::cout << "Knight" << std::endl;
		break;
	case PieceType::Pawn:
		std::cout << "Pawn" << std::endl;
		break;
	default:
		std::cout << "Null" << std::endl;
		break;
	}
}
void Game::CheckCastling() {
	std::cout << "White Castling: " << (isWhiteCastling ? "True" : "False") << std::endl;
	std::cout << "Black Castling: " << (isBlackCastling ? "True" : "Fasle") << std::endl;
}
void Game::CheckLive() {
}