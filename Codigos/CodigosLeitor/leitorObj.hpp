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
#include "../GeracaoLabirinto/Labirinto3D.hpp"

using namespace std;

class Leitor{
	public:
		Leitor();
		~Leitor();
		void readObj(Ponto* verticesLab, int** facesLab);
	private:
		vector <Vertices> vertices;
		vector <Faces> faces;
};

Leitor::Leitor(){
}

Leitor::~Leitor(){
}

void Leitor::readObj(Ponto* verticesLab, int** facesLab, int cont){	
	float PontoX, PontoY, PontoZ;
	int aux;
	vector <int> aux2;


	cout << "Vertices" << endl;
	for(int i = 0; verticesLab != NULL; i++){
		PontoX = verticesLab[i].x  
		PontoY = verticesLab[i].y  
		PontoZ = verticesLab[i].z  
		
		cout << PontoX << " " << PontoY << " " << PontoZ << endl; 

		vertices.push_back(Vertices(PontoX, PontoY, PontoZ));
	}

	cout << "Faces" << endl;
	for(int i = 0; i < cont; i++){
		for(int j = 0; j < 4; j++){
			aux = facesLab[i][j];
			aux2.push_back(aux)
			cout << aux << " " ;
		}

		cout << endl;
		faces.push_back(Faces(aux2));
		aux2.clear();
	}
}

#endif 