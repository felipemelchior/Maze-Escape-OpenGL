#ifndef LEITOROBJ_H
#define LEITOROBJ_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <string>
#include <climits>

#include "Vertice.hpp"
#include "Face.hpp"
#include "OpenGL.hpp"

using namespace std;

class Leitor{
	public:
		Leitor();
		~Leitor();
		void readObj(Ponto* verticesLab, int** facesLab, int cont, int pontos);
		void imprimeObj();
		void copia();
	private:
		vector <Vertices> vertices;
		vector <Faces> faces;
};

Leitor::Leitor(){
}

Leitor::~Leitor(){
}

void Leitor::readObj(Ponto* verticesLab, int** facesLab, int cont, int pontos){
	float PontoX, PontoY, PontoZ;
	int aux;
	vector <int> aux2;

	for(int i = 0; i < pontos; i++){
		PontoX = verticesLab[i].x;
		PontoY = verticesLab[i].y;
		PontoZ = verticesLab[i].z;

		vertices.push_back(Vertices(PontoX, PontoY, PontoZ));
	}

	for(int i = 0; i < cont; i++){
		for(int j = 0; j < 4; j++){
			aux = facesLab[i][j];
			aux2.push_back(aux);

		}
		faces.push_back(Faces(aux2));

		aux2.clear();
	}
	//imprimeObj();
	copia();
}

void Leitor::copia(){
	P1 = (Ponto**)malloc(faces.size()*sizeof(Ponto*));
	for(int i = 0; i < faces.size(); i++)
		P1[i] = (Ponto*)malloc(4*sizeof(Ponto));

	for(int i = 0; i < faces.size(); i++){
		for(int j = 0; j < 4; j++){
			P1[i][j].x = vertices[faces[i].getElemento(j)-1].getX();
			P1[i][j].y = vertices[faces[i].getElemento(j)-1].getY();
			P1[i][j].z = vertices[faces[i].getElemento(j)-1].getZ();
		}
	}
	altura = faces.size();
	largura = 4;
	//ImprimeP1();
}

void Leitor::imprimeObj(){
	for(int i = 0; i < vertices.size(); i++){
		cout << "v " << vertices[i].getX() << " " << vertices[i].getY() << " " << vertices[i].getZ() << endl;
	}

	for(int i = 0; i < faces.size(); i++){
		cout << "f ";
		for(int j = 0; j < faces[i].getTamElemento(); j++){
			cout << faces[i].getElemento(j) << " ";
		}
		cout << endl;
	}
}

#endif
