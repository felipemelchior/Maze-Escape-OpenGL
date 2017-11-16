#ifndef FACE_H
#define FACE_H

#include <vector>
#include <iostream>

using namespace std;

class Faces{
	public:
		Faces();
		~Faces();
		Faces(vector <int> Vetor);
		int getElemento(int i);
		int getTamElemento();
	private:
		vector <int> elemento;
};

Faces::Faces(){
}

Faces::~Faces(){
}

Faces::Faces(vector <int> Vetor){
	for(int i = 0; i < Vetor.size(); i++){
		elemento.push_back(Vetor[i]);
	}
}

int Faces::getTamElemento(){
	return elemento.size();
}

int Faces::getElemento(int x){
	return elemento[x];
}

#endif