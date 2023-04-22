#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <iostream>
#include <utility>
#include <stack>
#include <typeinfo>
#include <map>

enum class Camp{//棋子所属阵营使用枚举类便于区分
	White = 0,//白方
	Black,//黑方
	Null,//空地
};

enum class PieceType {//棋子的类型使用枚举类型便于区分
	King = 0,//王
	Queen,//后
	Rook,//车
	Bishop,//象
	Knight,//马
	Pawn,//兵
	Null//空地
};

class Piece {//棋子类
public:
	virtual PieceType GetPieceType() {
		return PieceType::Null;
	}
	Piece();
	Piece(bool isEmpty, Camp camp, std::pair<int, int> position);
	~Piece();
	void GetPieceData() {
		std::cout << "isEmpty: " << (this->isEmpty ? "true" : "false") << std::endl;
		std::cout << "isPress: " << (this->isPress ? "true" : "false") << std::endl;
		std::cout << "row: " << this->position.first << " column: " << this->position.second << std::endl;
		std::cout << (this->camp == Camp::Null ? "Null":(this->camp == Camp::Black ? "Black":"White")) << std::endl;
	}
	void Move(int targetRow, int targetColumn) {
		position.first = targetRow;
		position.second = targetColumn;
	}

	bool isEmpty = true;//是否是空地
	bool isPress = false;//是否被点击
	bool isHighlighted = false;//是否被高亮
	bool isTargetd = false;//是否被吃子
	Camp camp = Camp::Null;//所属阵营
	std::pair<int, int> position;//棋子的位置

};
class King : public Piece {//王类
public:
	virtual PieceType GetPieceType() {
		return PieceType::King;
	}
	
	King();
	~King();
	King(bool isEmpty, Camp camp, std::pair<int, int> position);
	King(const King& p) {
		this->isEmpty = p.isEmpty;
		this->isPress = p.isPress;
		this->isHighlighted = p.isHighlighted;
		this->camp = p.camp;
		this->position = p.position;
	}

	bool isMoved = false;//是否被移动
};
class Queen : public Piece {//后类
public:
	virtual PieceType GetPieceType() {
		return PieceType::Queen;
	}

	Queen();
	~Queen();
	Queen(bool isEmy, Camp camp, std::pair<int, int> position);
};
class Rook : public Piece {//车类
public:
	virtual PieceType GetPieceType() {
		return PieceType::Rook;
	}

	Rook();
	~Rook();
	Rook(bool isEmpty, Camp camp, std::pair<int, int> position);

	bool isMoved = false;//是否被移动
};
class Bishop : public Piece {//象类
public:
	virtual PieceType GetPieceType() {
		return PieceType::Bishop;
	}

	Bishop();
	~Bishop();
	Bishop(bool isEmpty, Camp camp, std::pair<int, int> position);
};
class Knight : public Piece {//马类
public:
	virtual PieceType GetPieceType() {
		return PieceType::Knight;
	}

	Knight();
	~Knight();
	Knight(bool isEmpty, Camp camp, std::pair<int, int> position);
};
class Pawn : public Piece {//兵类
public:
	virtual PieceType GetPieceType() {
		return PieceType::Pawn;
	}

	Pawn();
	~Pawn();
	Pawn(bool isEmpty, Camp camp, std::pair<int, int> position,bool isFirstMove);
	bool isFirstMove;//兵是否是第一次移动
	bool isPromoted = false;//兵是否能被晋升 
};
#endif // !PIECE_H
