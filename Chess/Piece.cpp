#include "Piece.h"	

Piece::Piece() {}
Piece::Piece(bool isEmpty, Camp camp, std::pair<int, int> position) {
	this->isEmpty = isEmpty;
	this->camp = camp;
	this->position = position;
	this->isPress = false;
}
Piece::~Piece() {}

King::King(){}
King::King(bool isEmpty, Camp camp, std::pair<int, int> position) {
	this->isEmpty = isEmpty;
	this->camp = camp;
	this->position = position;
	this->isPress = false;
}
King::~King(){}

Queen::Queen(){}
Queen::Queen(bool isEmpty, Camp camp, std::pair<int, int> position) {
	this->isEmpty = isEmpty;
	this->camp = camp;
	this->position = position;
	this->isPress = false;
}
Queen::~Queen(){}

Rook::Rook(){}
Rook::Rook(bool isEmpty, Camp camp, std::pair<int, int> position) {
	this->isEmpty = isEmpty;
	this->camp = camp;
	this->position = position;
	this->isPress = false;
}
Rook::~Rook(){}

Bishop::Bishop(){}
Bishop::Bishop(bool isEmpty, Camp camp, std::pair<int, int> position) {
	this->isEmpty = isEmpty;
	this->camp = camp;
	this->position = position;
	this->isPress = false;
}
Bishop::~Bishop(){}

Knight::Knight(){}
Knight::Knight(bool isEmpty, Camp camp, std::pair<int, int> position) {
	this->isEmpty = isEmpty;
	this->camp = camp;
	this->position = position;
	this->isPress = false;
}
Knight::~Knight(){}

Pawn::Pawn(){}
Pawn::Pawn(bool isEmpty, Camp camp, std::pair<int, int> position,bool isFirstMove) {
	this->isEmpty = isEmpty;
	this->camp = camp;
	this->position = position;
	this->isPress = false;
	this->isFirstMove = isFirstMove;
}
Pawn::~Pawn(){}
