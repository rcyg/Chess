#include "Game.h"

Game::Game() {
	window.create(//��������
		VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), L"Chess by berrySoda"
	);
}
Game::~Game() {

}

void Game::Initial() {
	window.setFramerateLimit(60);//����Ŀ��֡��
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
	currentOperateCamp = Camp::White;//�׷�����
	initBoard();
	initMedia();
	initFntMapping();
	clock.restart();//�ؿ���ʱ��
}
void Game::initPrompt() {
	/// <summary>
	/// �ȳ�ʼ��Ϊ�� ֮��ʹ��logicCheckLive�����첽����
	/// </summary>
	whiteKing = blackKing = 0;
	whiteQueen = blackQueen = 0;
	whiteRook = blackRook = 0;
	whiteKnight = blackKnight = 0;
	whiteBishop = blackBishop = 0;
	whitePawn = blackPawn = 0;
}
void Game::initBoard() {
	vectBoard.clear();//������̼�¼����
	for (int i = 0; i < BOARD_HEIGHT; ++i) {
		for (int j = 0; j < BOARD_WIDTH; ++j) {
			switch (i)
			{
			case 0://��һ�� �ڷ�
				switch (j){
					case 0://�ڳ�
					case 7:
						board[i][j] = new Rook(false, Camp::Black, std::make_pair(i, j));
						break;
					case 1://����
					case 6:
						board[i][j] = new Knight(false, Camp::Black, std::make_pair(i, j));
						break;
					case 2://����
					case 5:
						board[i][j] = new Bishop(false, Camp::Black, std::make_pair(i, j));
						break;
					case 3://����
						board[i][j] = new Queen(false, Camp::Black, std::make_pair(i, j));
						break;
					case 4://�ں�
						board[i][j] = new King(false, Camp::Black, std::make_pair(i, j));
						break;
					default:
						break;
				}
				break;
			case 1://�ڶ��� ��Ϊ�ڱ�
				board[i][j] = new Pawn(false, Camp::Black, std::make_pair(i,j),true);
				break;
			case 6://������ ��Ϊ�ױ�
				board[i][j] = new Pawn(false, Camp::White, std::make_pair(i, j),true);
				break;
			case 7://�ڰ��� �׷�
				switch (j){
					case 0://�׳�
					case 7:
						board[i][j] = new Rook(false, Camp::White, std::make_pair(i, j));
						break;
					case 1://����
					case 6:
						board[i][j] = new Knight(false, Camp::White, std::make_pair(i, j));
						break;
					case 2://����
					case 5:
						board[i][j] =  new Bishop(false, Camp::White, std::make_pair(i, j));
						break;
					case 3://�׺�
						board[i][j] = new Queen(false, Camp::White, std::make_pair(i, j));						
						break;
					case 4://����
						board[i][j] = new King(false, Camp::White, std::make_pair(i, j));
						break;
					default:
						break;
				}
				break;
			default://��ʼ��Ϊ�յ�
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
	//��data�ļ����м�������
	if (!font.loadFromFile("data/font/Inter-VariableFont_slnt,wght.ttf"))
		std::cout << "���� δ�ҵ�" << std::endl;
	text.setFont(font);
	//��data�ļ����м������̺����ӵ�����
	if (!tInitial.loadFromFile("data/texture/Map/InitialMasked.png"))
		std::cout << "��ʼ���� δ�ҵ�" << std::endl;
	if (!tTitle.loadFromFile("data/texture/Map/Title.png"))
		std::cout << "Chess���� δ�ҵ�" << std::endl;
	if (!tBeginText.loadFromFile("data/texture/Map/beginText.png"))
		std::cout << "beginText δ�ҵ�" << std::endl;
	if (!tBoard.loadFromFile("data/texture/Map/pink.png"))
		std::cout << "���� δ�ҵ�" << std::endl;
	if (!tHighlighted.loadFromFile("data/texture/Map/highlighted.png"))
		std::cout << "������ δ�ҵ�" << std::endl;
	if (!tHighlightedWithBorder.loadFromFile("data/texture/Map/highlightedWithBorder.png"))
		std::cout << "������(�ױߣ� δ�ҵ�" << std::endl;
	if (!tSelected.loadFromFile("data/texture/Map/selected.png"))
		std::cout << "ѡ��� δ�ҵ�" << std::endl;
	if (!tSelectedWithBorder.loadFromFile("data/texture/Map/selectedWithBorder.png"))
		std::cout << "ѡ��񣨰ױߣ� δ�ҵ�" << std::endl;
	if (!tPrompt_Background.loadFromFile("data/texture/Prompt/prompt_background.png"))
		std::cout << "״̬�� ���� δ�ҵ�" << std::endl;
	if (!tPrompt_CampWhite.loadFromFile("data/texture/Prompt/prompt_camp_white.png"))
		std::cout << "״̬�� �׷� δ�ҵ�" << std::endl;
	if (!tPrompt_CampBlack.loadFromFile("data/texture/Prompt/prompt_camp_black.png"))
		std::cout << "״̬�� �ڷ� δ�ҵ�" << std::endl;
	if (!tPrompt_BlackClock.loadFromFile("data/texture/Prompt/BlackClock.png"))
		std::cout << "״̬�� BlackClock δ�ҵ�" <<std::endl;
	if (!tPrompt_WhiteClock.loadFromFile("data/texture/Prompt/WhiteClock.png"))
		std::cout << "״̬�� WhiteClock δ�ҵ�" << std::endl;
	if (!tPrompt_BlackIcon.loadFromFile("data/texture/Prompt/BlackIcon.png"))
		std::cout << "״̬�� BlackIcon δ�ҵ�" << std::endl;
	if (!tPrompt_WhiteIcon.loadFromFile("data/texture/Prompt/WhiteIcon.png"))
		std::cout << "״̬�� WhiteIcon δ�ҵ�" << std::endl;
	if (!tPrompt_BlackPieces.loadFromFile("data/texture/Prompt/BlackPieces.png"))
		std::cout << "״̬�� BlackPieces δ�ҵ�" << std::endl;
	if (!tPrompt_WhitePieces.loadFromFile("data/texture/Prompt/WhitePieces.png"))
		std::cout << "״̬�� WhitePieces δ�ҵ�" << std::endl;
	if (!tPrompt_Restart.loadFromFile("data/texture/Prompt/Restart.png"))
		std::cout << "״̬�� Restart δ�ҵ�" << std::endl;
	if (!tPrompt_Undo.loadFromFile("data/texture/Prompt/Undo.png"))
		std::cout << "״̬�� Undo δ�ҵ�" << std::endl;
	if (!tPrompt_Die.loadFromFile("data/texture/Prompt/Die.png"))
		std::cout << "״̬�� Die δ�ҵ�" << std::endl;
	if (!tWhiteKing.loadFromFile("data/texture/White/king.png"))
		std::cout << "���� δ�ҵ�" << std::endl;
	if (!tWhiteQueen.loadFromFile("data/texture/White/queen.png"))
		std::cout << "�׺� δ�ҵ�" << std::endl;
	if (!tWhiteRook.loadFromFile("data/texture/White/rook.png"))
		std::cout << "�׳� δ�ҵ�" << std::endl;
	if (!tWhiteBishop.loadFromFile("data/texture/White/bishop.png"))
		std::cout << "���� δ�ҵ�" << std::endl;
	if (!tWhiteKnight.loadFromFile("data/texture/White/knight.png"))
		std::cout << "���� δ�ҵ�" << std::endl;
	if (!tWhitePawn.loadFromFile("data/texture/White/pawn.png"))
		std::cout << "�ױ� δ�ҵ�" << std::endl;
	if (!tBlackKing.loadFromFile("data/texture/Black/king.png"))
		std::cout << "���� δ�ҵ�" << std::endl;
	if (!tBlackQueen.loadFromFile("data/texture/Black/queen.png"))
		std::cout << "�ں� δ�ҵ�" << std::endl;
	if (!tBlackRook.loadFromFile("data/texture/Black/rook.png"))
		std::cout << "�ڳ� δ�ҵ�" << std::endl;
	if (!tBlackBishop.loadFromFile("data/texture/Black/bishop.png"))
		std::cout << "���� δ�ҵ�" << std::endl;
	if (!tBlackKnight.loadFromFile("data/texture/Black/knight.png"))
		std::cout << "���� δ�ҵ�" << std::endl;
	if (!tBlackPawn.loadFromFile("data/texture/Black/pawn.png"))
		std::cout << "�ڱ� δ�ҵ�" << std::endl;
	//��ÿһ����������� �����÷���
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
	/// �߼�����
	/// ��Ҫ���������ƶ������������ӵ����
	/// </summary>
	logicCheckLive();
	if (isPieceClick) {//���������ѡ��״̬
		for (auto& row : board) {
			for (auto& piece : row) {
				if (piece->isEmpty == false //���Ӳ�Ϊ��
					&& piece->isPress == true //�����Ѿ���ѡ��
					&& currentSelectCamp == currentOperateCamp) {//ѡ�е������뵱ǰ������Ӫ��ͬ
					if (!isMoveClick && !isEatClick) {//����δ�ƶ�
						piece->isHighlighted = true;//��������������ĸ���
						(this->*logicCall[piece->GetPieceType()])(piece);
						switch (piece->GetPieceType()) {//���������������ö�Ӧ���ӵĸ���
							case PieceType::King:
								//logicKing(piece);//����Ƿ���������λ
								if (isWhiteCastling) 
									board[7][7]->isHighlighted = true;//�������½ǵĳ�����
								if (isBlackCastling) 
									board[0][0]->isHighlighted = true;//�������Ͻǵĳ�����
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
					else if(isMoveClick){//�����ƶ�
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
						logicTurnCamp();//�ı������Ӫ
					}
					else if (isEatClick) {//���Ӳ���
						logicEat(targetPosition[0], targetPosition[1], piece);
						isPieceClick = false;
						isEatClick = false;
						logicTurnCamp();//�ı������Ӫ
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
	//��ȡ�����ڵ��к���
	int row = piece->position.first;
	int column = piece->position.second;
	for (int i = row - 1; i < row + 2; ++i) {//���İ��������
		for (int j = column - 1; j < column + 2; ++j) {
			if (i >= 0 && i < BOARD_HEIGHT && j >= 0 && j < BOARD_WIDTH) {//��ֹ����Խ��
				if (board[i][j]->isEmpty == true || board[i][j]->camp != piece->camp)//���Ϊ�գ������
					board[i][j]->isHighlighted = true;
				
			}
		}
	}

}
void Game::logicQueen(Piece* piece){
	//��ȡ�����ڵ��к���
	int row = piece->position.first;
	int column = piece->position.second;
	
	for (auto& searchType : searchType) {
		logicSearch(row, column, searchType);
	}
}
void Game::logicRook(Piece* piece) {
	//��ȡ�����ڵ��к���
	int row = piece->position.first;
	int column = piece->position.second;

	for (int i = 4; i < 8; ++i) {
		logicSearch(row, column, searchType[i]);
	}
}
void Game::logicBishop(Piece* piece) {
	//��ȡ�����ڵ��к���
	int row = piece->position.first;
	int column = piece->position.second;
	for (int i = 0; i < 4; ++i) {
		logicSearch(row, column, searchType[i]);
	}
}
void Game::logicKnight(Piece* piece) {
	//��ȡ�����ڵ��к���
	int row = piece->position.first;
	int column = piece->position.second;
	//L���ƶ� ����Ψһһ������Խ�����ӵ�����
	//̫���� ��ֻ�ü��˸���
	for (auto& moveType : knightMove) {//Ԥ�ȶ�������ƶ�����
		if (row + moveType[0] >= 0//��ֹ����Խ��
			&& row + moveType[0] < BOARD_HEIGHT
			&& column + moveType[1] >= 0
			&& column + moveType[1] < BOARD_WIDTH) {
			if (board[row + moveType[0]][column + moveType[1]]->isEmpty == true 
				|| board[row + moveType[0]][column + moveType[1]]->camp != board[row][column]->camp) {//��Ϊ�գ������
				board[row + moveType[0]][column + moveType[1]]->isHighlighted = true;
			}
		}
	}
}
void Game::logicPawn(Piece* piece) {
	//��ȡ�����ڵ��к���
	Pawn* pawn = dynamic_cast<Pawn*>(piece);//��ת��Ϊָ�����͵�ָ��
	int row = pawn->position.first;
	int column = pawn->position.second;
	//����һ�ο����ƶ�������Ҫ����Ƿ��ǵ�һ���ƶ�
	//���������ƶ�
	switch (pawn->camp){
	case Camp::White:
		if (pawn->isFirstMove) {
			if (row - 1 >= 0
				&& row - 1 < BOARD_HEIGHT) {//�Ϸ�һ��
				if (board[row - 1][column]->isEmpty == true) {
					board[row - 1][column]->isHighlighted = true;
					if (row - 2 >= 0
						&& row - 2 < BOARD_HEIGHT) {//�Ϸ�����
						if (board[row - 2][column]->isEmpty == true)
							board[row - 2][column]->isHighlighted = true;
					}
				}	
			}
		}
		else {
			if (row - 1 >= 0
				&& row - 1 < BOARD_HEIGHT) {//�Ϸ�һ��
				if (board[row - 1][column]->isEmpty == true) {
					board[row - 1][column]->isHighlighted = true;
				}

			}
		}
		if (row - 1 >= 0
			&& row - 1 < BOARD_HEIGHT
			&& column - 1 >= 0
			&& column - 1 < BOARD_WIDTH) {//���Ϸ�
			if (board[row - 1][column - 1]->isEmpty == false
				&& board[row - 1][column - 1]->camp != pawn->camp)
				board[row - 1][column - 1]->isHighlighted = true;
		}
		if (row - 1 >= 0
			&& row - 1 < BOARD_HEIGHT
			&& column + 1 >= 0
			&& column + 1 < BOARD_WIDTH) {//���Ϸ�
			if (board[row - 1][column + 1]->isEmpty == false
				&& board[row - 1][column + 1]->camp != pawn->camp)
				board[row - 1][column + 1]->isHighlighted = true;
		}
		break;
	case Camp::Black:
		if (pawn->isFirstMove) {
			if (row + 1 >= 0
				&& row + 1 < BOARD_HEIGHT) {//�·�һ��
				if (board[row + 1][column]->isEmpty == true) {
					board[row + 1][column]->isHighlighted = true;
					if (row + 2 >= 0
						&& row + 2 < BOARD_HEIGHT) {//�·�����
						if (board[row + 2][column]->isEmpty == true)
							board[row + 2][column]->isHighlighted = true;
					}
				}

			}
		}
		else {
			if (row + 1 >= 0
				&& row + 1 < BOARD_HEIGHT) {//�·�һ��
				if (board[row + 1][column]->isEmpty == true) {
					board[row + 1][column]->isHighlighted = true;
				}

			}
		}
		if (row + 1 >= 0
			&& row + 1 < BOARD_HEIGHT
			&& column - 1 >= 0
			&& column - 1 < BOARD_WIDTH) {//���·�
			if (board[row + 1][column - 1]->isEmpty == false
				&& board[row + 1][column - 1]->camp != pawn->camp)
				board[row + 1][column - 1]->isHighlighted = true;
		}
		if (row + 1 >= 0
			&& row + 1 < BOARD_HEIGHT
			&& column + 1 >= 0
			&& column + 1 < BOARD_WIDTH) {//���·�
			if (board[row + 1][column + 1]->isEmpty == false
				&& board[row + 1][column + 1]->camp != pawn->camp)
				board[row + 1][column + 1]->isHighlighted = true;
		}
		break;
	default:
		break;
	}
	logicEnPassant(row, column, pawn);//�Թ�·�����

}
void Game::logicEnPassant(int row, int column, Pawn* pawn) {
	//�Թ�·������ en passant
	//˵��
	//�����һ���ƶ��ǵз����ĵ�һ���ƶ� ������ͬһ�е���������֮һ
	//�����Թ�·���Ļ����ж�
	//�ڰ׷��ֱ��ж�
	//�����ö�Ӧбǰ���ո�ĸ�����
	//��Logic()�����м����Ӧ��Pawn���͵ļ����ʵ�ֶ�isEnPassant������
	if (lastFirstMovePawn != NULL) {//��Ϊ�� ������һ���ƶ������ǵз����ĵ�һ���ƶ�
		if (lastFirstMovePawn->camp != pawn->camp//Ϊ��ͬ��Ӫ
			&& lastFirstMovePawn->position.first == pawn->position.first//��ͬһ��
			&& abs(lastFirstMovePawn->position.second - pawn->position.second) == 1) {//����߻��ұ�һ���λ��
			switch (pawn->camp) {
			case Camp::White:
				if (lastFirstMovePawn->position.second - pawn->position.second == -1) {//�з��������
					if (board[row - 1][column - 1]->isEmpty == true)//���Ϸ�Ϊ��
						board[row - 1][column - 1]->isHighlighted = true;
				}
				else {//�з������Ҳ�
					if (board[row - 1][column + 1]->isEmpty == true)//���Ϸ�Ϊ��
						board[row - 1][column + 1]->isHighlighted = true;
				}
				break;
			case Camp::Black:
				if (lastFirstMovePawn->position.second - pawn->position.second == -1) {//�з��������
					if (board[row + 1][column - 1]->isEmpty == true)//���·�Ϊ��
						board[row + 1][column - 1]->isHighlighted = true;
				}
				else {//�з������Ҳ�
					if (board[row + 1][column + 1]->isEmpty == true)//���·�Ϊ��
						board[row + 1][column + 1]->isHighlighted = true;
				}
				break;
			}
		}
	}
}
void Game::logicPromotion(Pawn* pawn) {
	//���Ľ��� 
	switch (pawn->camp) {
	case Camp::White:
		if (pawn->position.first == 0)//�׷����ִ��һ��
			pawn->isPromoted = true;
		break;
	case Camp::Black:
		if (pawn->position.first == 7)//�ڷ����ִ�ڰ���
			pawn->isPromoted = true;
		break;
	}
	if (pawn->isPromoted)
		board[pawn->position.first][pawn->position.second] = new Queen(false, pawn->camp, pawn->position);
	
}
void Game::logicCastling() {
	//������λ��⺯�� ����������� ������ѡ��ʱ ͬʱ�������ͳ�
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
void Game::logicSearch(int row, int column, int* searchType) {//��Ϊ�� �Ҳ�Խ��
	int newRow = row + searchType[0], newColumn = column + searchType[1];
	if (newRow >= 0 && newRow < BOARD_HEIGHT && newColumn >= 0 && newColumn < BOARD_WIDTH) {
		if ((board[newRow][newColumn]->camp != currentSelectCamp
			&& board[newRow][newColumn]->isEmpty == false)) {//����ǵз��������ƶ���Χ��
			board[newRow][newColumn]->isHighlighted = true;//����Ϊ����
		}
		if (board[newRow][newColumn]->isEmpty == true) {
			board[newRow][newColumn]->isHighlighted = true;//����Ϊ����
			logicSearch(newRow, newColumn, searchType);//�ݹ�����
		}
	}
}
void Game::logicMove(int targetRow, int targetColumn, Piece* piece) {
	
	logicSave();
	board[piece->position.first][piece->position.second] = new Piece(true, Camp::Null, std::make_pair(piece->position.first, piece->position.second));//���ԭ��λ��Ϊ�յ�
	std::pair<int, int> previousPosition = piece->position;//�洢��һ��λ�� ���ڱ��ĳԹ�·���߼��ж�
	piece->Move(targetPosition[0], targetPosition[1]);//��������λ��
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
		if (lastFirstMovePawn != NULL) {//����һ�ε��ƶ��Ǳ��ĵ�һ���ƶ�
			if (isEnPassant) {//����ǳԹ��ӱ�����
				board[lastFirstMovePawn->position.first][lastFirstMovePawn->position.second] 
					= new Piece(true, Camp::Null, lastFirstMovePawn->position);//�ѱ��Ա����
				isEnPassant = false;
			}
			lastFirstMovePawn = NULL;
		}

		board[targetPosition[0]][targetPosition[1]] = new Pawn(piece->isEmpty, piece->camp, piece->position,dynamic_cast<Pawn*>(piece)->isFirstMove);//�����ƶ�λ��Ϊ��
		
		if (abs(previousPosition.first - targetPosition[0]) == 2) {//����һ�����ƶ������� ������ΪlastFirstMovePawn
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
void Game::logicUndo() {//�߼����庯��
	if (!vectBoard.empty()) {//����������������
		for (int i = 0; i < BOARD_HEIGHT; ++i) {
			for (int j = 0; j < BOARD_WIDTH; ++j) {
				board[i][j] = vectBoard.back()[i][j];//���α������ʵ���һ�����������ݣ����θ�ֵ
			}
		}
		vectBoard.pop_back();//�ָ��󣬽��������ݵ���
		logicTurnCamp();//�л���Ӫ
	}
}
void Game::logicRestart() {//�߼��ؿ�����
	Initial();//���³�ʼ��
	isGameBegin = true;//����Ϊtrue ���᷵�س�ʼ����
}
void Game::logicSave() {//�߼��������� ����vectBoard
	std::vector<std::vector<Piece*>> multiple;//��ʱvector
	for (int i = 0; i < BOARD_HEIGHT; ++i) {
		std::vector<Piece*> single;//��ʱvector
		for (int j = 0; j < BOARD_WIDTH; ++j) {
			
			switch (board[i][j]->GetPieceType())//������� ����copy
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
		multiple.push_back(single);//push����һ���vector
		single.clear();//push������
	}
	vectBoard.push_back(multiple);//push����������ȥ
	multiple.clear();//push������
	
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
		if (event.type == Event::Closed) {//�رմ���
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
		//�Ҽ�ȡ�����еĵ���͸������������̽�isPressȫ��Ϊfalse
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
	//��ȡ��������겢ת��Ϊ�к���
	int column = mPoint.x / GRIDSIZE;
	int row = mPoint.y / GRIDSIZE;
	if (isGameBegin) {
		if (!isChessBegin) {
			isChessBegin = true;
			clock.restart();	
		}
			
		if (row >= 0 && row < BOARD_HEIGHT && column >= 0 && column < BOARD_WIDTH) {//��ֹ����Խ�� ��ǳ���Ҫ
			CheckPieceByRC(row, column);//��ӡ���ǰ��״̬
			if (isPieceClick == false) {//�����û��ѡ������
				if (board[row][column]->isEmpty == false) {//��Ϊ�գ�������
					if (board[row][column]->camp == currentOperateCamp) {//ѡ��������ǵ�ǰ��Ӫ��
						board[row][column]->isPress = true;//����isPressΪtrue�������������
						currentSelectCamp = board[row][column]->camp;//���õ�ǰ�Ѿ�ѡ�и���Ӫ
						isPieceClick = true;//��ǰΪ������ѡ�� δ�ƶ�״̬
					}
				}
			}
			else {//��ǰ�Ѿ�ѡ��������
				if (board[row][column]->isEmpty == true
					&& board[row][column]->isHighlighted == true) {//���Ϊ�յ��Ҹ��� ��ζ���ǿ��е��ƶ�·��
					isMoveClick = true;//�ƶ���������
					targetPosition[0] = row;
					targetPosition[1] = column;

				}
				else if (board[row][column]->camp != currentSelectCamp
					&& board[row][column]->isEmpty == false
					&& board[row][column]->isHighlighted == true) {//���ѡ��ĸ�Ϊ������Ӫ��ͬ �����
					//board[row][column]->isTargetd = true;//����Ӧ��������ΪҪ���Ե�
					isEatClick = true;//���Ӳ�������
					targetPosition[0] = row;
					targetPosition[1] = column;
				}
				else if (board[row][column]->GetPieceType() == PieceType::Rook //������ǳ�
					&& (isWhiteCastling || isBlackCastling)) {//��һ������λ����
					isMoveClick = true;
					targetPosition[0] = row;
					targetPosition[1] = column;
				}
				else {
					for (auto& row : board) {//����˼������ӱ����Ǹ����� ȡ���ƶ�����
						for (auto& piece : row) {
							piece->isHighlighted = false;
							piece->isPress = false;
							isPieceClick = false;
							currentSelectCamp = Camp::Null;
						}
					}
				}
			}
			CheckPieceByRC(row, column);//��ӡ������״̬
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
	window.clear();//����
	if (isGameBegin) {
		drawBoard();//��������
		drawPrompt();//����״̬��
		drawPieces();//��������
	}
	else {
		drawInitial();//���Ƴ�ʼ����
	}
	window.display();//��ʾ��������
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
	sBoard.setPosition(0, 0);//�������̵�λ��
	window.draw(sBoard);//��������
	for (auto& row : board) {//���ø���
		for (auto& column : row) {
			if (column->isHighlighted == true) {//�����������������ڸ�
				drawSprite(sHighlighted, column->position.second * GRIDSIZE, column->position.first*GRIDSIZE);
			}
		}
	}
}
void Game::drawPrompt() {

	
	//���������޸ĸú������κ�prompt�ྫ���λ�� 
	//Background 800,0
	//BlackClock 825,20
	//WhiteClock 825,680
	//BlackIcon 1075,20
	//WhiteIcon 1075,680
	//BlackPieces 800,175
	//WhitePieces 800,505
	//Undo 825,350
	//Restart 1075,350

	sPrompt_Background.setPosition(8 * GRIDSIZE, 0);//����λ������
	window.draw(sPrompt_Background);
	sPrompt_BlackClock.setPosition(825, 20);//�ڼ�ʱ��λ������
	window.draw(sPrompt_BlackClock);
	sPrompt_WhiteClock.setPosition(825, 680);//�׼�ʱ��λ������
	window.draw(sPrompt_WhiteClock);
	sPrompt_BlackIcon.setPosition(1075, 20);//�ڱ�־λ������
	window.draw(sPrompt_BlackIcon);
	sPrompt_WhiteIcon.setPosition(1075, 680);//�ױ�־λ������
	window.draw(sPrompt_WhiteIcon);
	sPrompt_BlackPieces.setPosition(800, 175);//����λ������
	window.draw(sPrompt_BlackPieces);
	sPrompt_WhitePieces.setPosition(800, 505);//����λ������
	window.draw(sPrompt_WhitePieces);
	sPrompt_Undo.setPosition(825, 350);//���尴ťλ������
	window.draw(sPrompt_Undo);
	sPrompt_Restart.setPosition(1075, 350);//�ؿ���ťλ������
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
	//���������������
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
	for (auto& row: board) {//ʹ��foreach �� auto ѭ����������
		for (auto& column : row) {
			//column->GetPieceData();//������
			int drawPosition_X = column->position.second * GRIDSIZE;
			int drawPosition_Y = column->position.first * GRIDSIZE;
			switch (column->GetPieceType()) {
			case PieceType::Null://�յ�
				break;
			case PieceType::King://��
				if (column->camp == Camp::Black)
					drawSprite(sBlackKing, drawPosition_X, drawPosition_Y);
				else
					drawSprite(sWhiteKing, drawPosition_X, drawPosition_Y);
				break;
			case PieceType::Queen://��
				if (column->camp == Camp::Black)
					drawSprite(sBlackQueen, drawPosition_X, drawPosition_Y);
				else
					drawSprite(sWhiteQueen, drawPosition_X, drawPosition_Y);
				break;
			case PieceType::Rook://��
				if (column->camp == Camp::Black)
					drawSprite(sBlackRook, drawPosition_X, drawPosition_Y);
				else
					drawSprite(sWhiteRook, drawPosition_X, drawPosition_Y);
				break;
			case PieceType::Bishop://��
				if (column->camp == Camp::Black)
					drawSprite(sBlackBishop, drawPosition_X, drawPosition_Y);
				else
					drawSprite(sWhiteBishop, drawPosition_X, drawPosition_Y);
				break;
			case PieceType::Knight://��
				if (column->camp == Camp::Black)
					drawSprite(sBlackKnight, drawPosition_X, drawPosition_Y);
				else
					drawSprite(sWhiteKnight, drawPosition_X, drawPosition_Y);
				break;
			case PieceType::Pawn://��
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
	/// ��ӡ������صĲ���
	/// (x,y)����
	/// ����ϵ��
	/// �����С
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
	/// ��ӡ������������Ӫ
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