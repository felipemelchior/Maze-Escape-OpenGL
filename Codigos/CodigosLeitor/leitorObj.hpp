#ifndef LEITOROBJ_H
#define LEITOROBJ_H

#include <iostream>
#include <fstream>
#include <vector>

#include "Vertice.hpp"
#include "Face.hpp"

using namespace std;

class Leitor{
	public:
		Leitor();
		~Leitor();
		void readObj(string Nome);
	private:
		vector <Vertices> vertices;
		vector <Faces> faces;
};

Leitor::Leitor(){
}

Leitor::~Leitor(){
}

void Leitor::readObj(string Nome){
	ifstream iFile.open(Nome.c_str());
	float PontoX, PontoY, PontoZ;
	int aux, letra;
	vector <int> aux2;

	if(!iFile.is_open()){
		cout << "Erro ao abrir o arquivo" << endl;
		exit(1);
	}

	while(!iFile.eof()){
		iFile >> letra;

		if(letra == "#") iFile.ignore(INT_MAX, '\n');

		else if(letra == "v"){
			iFile >> PontoX;
			iFile >> PontoY;
			iFile >> PontoZ;

			vertices.push_back(Vertices(PontoX, PontoY, PontoZ));
		}

		else if(letra == "f"){
			for(int i = 0; i < 4; i++){
				iFile >> aux;
				aux2.push_back(aux);
			}

			faces.push_back(Faces(aux2));
			aux2.clear();
		}
		else iFile.ignore(INT_MAX, '\n');
	}

	iFile.close();
}

#endif 