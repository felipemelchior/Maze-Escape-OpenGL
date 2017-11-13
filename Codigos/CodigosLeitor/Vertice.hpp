#ifndef VERTICE_H
#define VERTICE_H

#include <iostream>
using namespace std;

class Vertices{
	public:
		Vertices();
		~Vertices();
		Vertices(float X, float Y, float Z);
		int getX();
		int getY();
		int getZ();
	private:
		float PontoX;
		float PontoY;
		float PontoZ;
};

Vertices::Vertices(){
}

Vertices::~Vertices(){
}

Vertices::Vertices(float X, float Y, float Z){
	this->PontoX = X;
	this->PontoY = Y;
	this->PontoZ = Z;
}

int Vertices::getX(){
	return PontoX;
}

int Vertices::getY(){
	return PontoY;
}

int Vertices::getZ(){
	return PontoZ;
}

#endif 