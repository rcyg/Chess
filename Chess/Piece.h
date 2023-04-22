#ifndef PIECE_H
#define PIECE_H
#include <string>
#include <iostream>
#include <utility>
#include <stack>
#include <typeinfo>
#include <map>

enum class Camp{//����������Ӫʹ��ö�����������
	White = 0,//�׷�
	Black,//�ڷ�
	Null,//�յ�
};

enum class PieceType {//���ӵ�����ʹ��ö�����ͱ�������
	King = 0,//��
	Queen,//��
	Rook,//��
	Bishop,//��
	Knight,//��
	Pawn,//��
	Null//�յ�
};

class Piece {//������
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

	bool isEmpty = true;//�Ƿ��ǿյ�
	bool isPress = false;//�Ƿ񱻵��
	bool isHighlighted = false;//�Ƿ񱻸���
	bool isTargetd = false;//�Ƿ񱻳���
	Camp camp = Camp::Null;//������Ӫ
	std::pair<int, int> position;//���ӵ�λ��

};
class King : public Piece {//����
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

	bool isMoved = false;//�Ƿ��ƶ�
};
class Queen : public Piece {//����
public:
	virtual PieceType GetPieceType() {
		return PieceType::Queen;
	}

	Queen();
	~Queen();
	Queen(bool isEmy, Camp camp, std::pair<int, int> position);
};
class Rook : public Piece {//����
public:
	virtual PieceType GetPieceType() {
		return PieceType::Rook;
	}

	Rook();
	~Rook();
	Rook(bool isEmpty, Camp camp, std::pair<int, int> position);

	bool isMoved = false;//�Ƿ��ƶ�
};
class Bishop : public Piece {//����
public:
	virtual PieceType GetPieceType() {
		return PieceType::Bishop;
	}

	Bishop();
	~Bishop();
	Bishop(bool isEmpty, Camp camp, std::pair<int, int> position);
};
class Knight : public Piece {//����
public:
	virtual PieceType GetPieceType() {
		return PieceType::Knight;
	}

	Knight();
	~Knight();
	Knight(bool isEmpty, Camp camp, std::pair<int, int> position);
};
class Pawn : public Piece {//����
public:
	virtual PieceType GetPieceType() {
		return PieceType::Pawn;
	}

	Pawn();
	~Pawn();
	Pawn(bool isEmpty, Camp camp, std::pair<int, int> position,bool isFirstMove);
	bool isFirstMove;//���Ƿ��ǵ�һ���ƶ�
	bool isPromoted = false;//���Ƿ��ܱ����� 
};
#endif // !PIECE_H
