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

#endif