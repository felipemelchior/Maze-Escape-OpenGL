#ifndef LABIRINTO3D_H
#define LABIRINTO3D_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Labirinto.hpp"
#include "../CodigosLeitor/leitorObj.hpp"

using namespace std;

class Labirinto3D{
public:
    Labirinto3D(int n, int m);
    Labirinto3D();
    ~Labirinto3D();
    void SetAltura(int altura);
    void SetLargura(int largura);
    void ExibeMatriz();
    void Conversor3D();
    void Trajetoria();
    void Status();
    void DefinePontos();
private:
    Ponto *Vertices;
    int **Matriz;
    int Altura;
    int Largura;
    int Dim;
    int Pontos;
};

Labirinto3D::Labirinto3D(int n, int m){
    Labirinto *Lab;

    Lab = new Labirinto(n, m);

    this->Matriz = (int**)malloc(Lab->GetN()*sizeof(int*));

    for(int i = 0; i < Lab->GetM(); i++){
        this->Matriz[i] = (int*)malloc(Lab->GetM()*sizeof(int));
    }

    Lab->GetLabirinto(this->Matriz);
    SetAltura(Lab->GetN());
    SetLargura(Lab->GetM());

    Dim = 5;

    //ExibeMatriz();
    DefinePontos();
    Conversor3D();
}

Labirinto3D::Labirinto3D(){
    int n = 20, m = 20;
    Labirinto *Lab;

    Lab = new Labirinto(n, m);

    this->Matriz = (int**)malloc(Lab->GetN()*sizeof(int*));

    for(int i = 0; i < Lab->GetM(); i++){
        this->Matriz[i] = (int*)malloc(Lab->GetM()*sizeof(int));
    }

    Lab->GetLabirinto(this->Matriz);
    SetAltura(Lab->GetN());
    SetLargura(Lab->GetM());

    Dim = 5;

    //ExibeMatriz();
    DefinePontos();
    Conversor3D();
}

void Labirinto3D::SetAltura(int n){
    this->Altura = n;
}

void Labirinto3D::SetLargura(int m){
    this->Largura = m;
}

void Labirinto3D::ExibeMatriz(){
    cout << endl << this->Altura << " " << this->Largura << endl;

    for(int i = 0; i < this->Altura; i++){
        for(int j = 0; j < this->Largura; j++){
            if(this->Matriz[i][j] == 0) cout << "[]";
            else cout << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

void Labirinto3D::Status(){
    int cont = 0;
    for(int i = 0; i < this->Altura; i++){
        for(int j = 0; j < this->Largura; j++){
            if(i == 0){
                cout << "[" << i << "]" << "[" << j << "] Direita Fechada " << endl;
                cont++;
                cout << "[" << i << "]" << "[" << j << "] Inferior Fechado " << endl;
                cont++;
            }
            else if(j == 0){
                cout << "[" << i << "]" << "[" << j << "] Direita Fechada " << endl;
                cont++;
                cout << "[" << i << "]" << "[" << j << "] Inferior Fechado " << endl;
                cont++;
            }
            else{
                if(j < Largura-1){
                    if(Matriz[i][j+1] == 1){
                        cout << "[" << i << "]" << "[" << j << "] Direita Aberta " << endl;
                        cont++;
                    }
                    else{
                        cout << "[" << i << "]" << "[" << j << "] Direita Fechada " << endl;
                        cont++;
                    }
                }
                else if(j < Largura){
                    if(Matriz[i][j] == 1){
                        cout << "[" << i << "]" << "[" << j << "] Esquerda Aberta " << endl;
                        cont++;
                    }
                    else{
                        cout << "[" << i << "]" << "[" << j << "] EsquerdaFechada " << endl;
                        cont++;
                    }
                }
                if(i < Altura-1){
                    if(Matriz[i+1][j] == 1){
                        cout << "[" << i << "]" << "[" << j << "] Inferior Aberto " << endl;
                        cont++;
                    }
                    else{
                        cout << "[" << i << "]" << "[" << j << "] Inferior Fechado " << endl;
                        cont++;
                    }
                }
                else{
                    cout << "[" << i << "]" << "[" << j << "] Inferior Fechado " << endl;
                    cont++;
                }
            }
        }
    }

    cout << "Maximo de Paredes necessárias: " << cont << endl;
}

void Labirinto3D::DefinePontos(){
    int aux = this->Altura*this->Largura;

    this->Pontos = aux+this->Altura+this->Largura+1;
    this->Pontos *= 2;
    //cout << this->Pontos;

    Vertices = (Ponto*)malloc(this->Pontos*sizeof(Ponto));

    int V1[this->Pontos/2], V2[this->Pontos/2];
    aux = 0;

    for(int i = 0; i < this->Altura + 1; i++){
        for(int j = 0; j < this->Largura + 1; j++){
            //cout << i*Dim << " " << j*Dim << endl;
            V1[aux] = i*Dim;
            V2[aux] = j*Dim;
            aux++;
        }
    }

    //cout << aux << endl;
    for(int i = 0; i < aux; i++){
        //cout << V1[i] << " " << V2[i] << endl;
        Vertices[i].x = V1[i];
        Vertices[i].z = V2[i];
        Vertices[i].y = Dim*2;

        Vertices[i+(this->Pontos/2)].x = V1[i];
        Vertices[i+(this->Pontos/2)].z = V2[i];
        Vertices[i+(this->Pontos/2)].y = 0;
    }

    //for(int i = 0; i < Pontos; i++)
        //cout << Vertices[i].x << " " << Vertices[i].z << " " << Vertices[i].y << endl;

}

void Labirinto3D::Conversor3D(){
    Leitor* leitor = new Leitor();
    int cont = 0;
    Ponto *VerticesLab;
    int **FacesLab;

    for(int i = 0; i < this->Pontos; i++){
        VerticesLab = (Ponto*)malloc(this->Pontos*sizeof(Ponto));
    }


    FacesLab = (int**)malloc(((this->Altura*this->Largura)*6)*sizeof(int*));
    for(int i = 0; i < ((this->Altura*this->Largura)*6); i++){
        FacesLab[i] = (int*)malloc(4*sizeof(int));
    }

    //cout << VerticesLab.size() << " " << FacesLab.size() << " " << FacesLab[0].size() << endl;

    int aux = this->Pontos/2;
    ofstream oFile;
    oFile.open("Labirinto.obj");
    //Status();

    for(int i = 0; i < Pontos; i++){
        //cout << "v " << Vertices[i].x << " " << Vertices[i].y << " " << Vertices[i].z << endl;
        //oFile << "v " << Vertices[i].x << " " << Vertices[i].y << " " << Vertices[i].z << endl;
        VerticesLab[i].x = Vertices[i].x;
        VerticesLab[i].y = Vertices[i].y;
        VerticesLab[i].z = Vertices[i].z;
    }

    for(int i = 0; i < this->Altura; i++){
        for(int j = 0; j < this->Largura; j++){
            if(Matriz[i][j] == 0){
                /*
                oFile << "f "
                << (i*(this->Largura+1))+j+1 << " "
                << (i*(this->Largura+1))+j+2 << " "
                << (i*(this->Largura+1))+j+2+(this->Largura+1) << " "
                << (i*(this->Largura+1))+j+1+(this->Largura+1) << " "
                << endl;
                */

                FacesLab[cont][0] = (i*(this->Largura+1))+j+1;
                FacesLab[cont][1] = (i*(this->Largura+1))+j+2;
                FacesLab[cont][2] = (i*(this->Largura+1))+j+2+(this->Largura+1);
                FacesLab[cont][3] = (i*(this->Largura+1))+j+1+(this->Largura+1);
                cont++;

                /*
                oFile << "f "
                << (i*(this->Largura+1))+j+1 << " "
                << (i*(this->Largura+1))+j+2 << " "
                << (i*(this->Largura+1))+j+2+(this->Pontos/2)<< " "
                << (i*(this->Largura+1))+j+1+(this->Pontos/2)<< " "
                << endl;
                */

                if(i > 0){
                    if(Matriz[i-1][j] != 0){
                        FacesLab[cont][0] = (i*(this->Largura+1))+j+1;
                        FacesLab[cont][1] = (i*(this->Largura+1))+j+2;
                        FacesLab[cont][2] = (i*(this->Largura+1))+j+2+(this->Pontos/2);
                        FacesLab[cont][3] = (i*(this->Largura+1))+j+1+(this->Pontos/2);
                        cont++;
                    }
                }
                else{
                    FacesLab[cont][0] = (i*(this->Largura+1))+j+1;
                    FacesLab[cont][1] = (i*(this->Largura+1))+j+2;
                    FacesLab[cont][2] = (i*(this->Largura+1))+j+2+(this->Pontos/2);
                    FacesLab[cont][3] = (i*(this->Largura+1))+j+1+(this->Pontos/2);
                    cont++;
                }

                /*
                oFile << "f "
                << (i*(this->Largura+1))+j+2 << " "
                << (i*(this->Largura+1))+j+2+(this->Largura+1) << " "
                << (i*(this->Largura+1))+j+2+(this->Largura+1)+(this->Pontos/2) << " "
                << (i*(this->Largura+1))+j+2+(this->Pontos/2) << " "
                << endl;
                */

                if(j < 40){
                    if(Matriz[i][j+1] != 0){
                        FacesLab[cont][0] = (i*(this->Largura+1))+j+2;
                        FacesLab[cont][1] = (i*(this->Largura+1))+j+2+(this->Largura+1);
                        FacesLab[cont][2] = (i*(this->Largura+1))+j+2+(this->Largura+1)+(this->Pontos/2);
                        FacesLab[cont][3] = (i*(this->Largura+1))+j+2+(this->Pontos/2);
                        cont++;
                    }
                }
                else{
                    FacesLab[cont][0] = (i*(this->Largura+1))+j+2;
                    FacesLab[cont][1] = (i*(this->Largura+1))+j+2+(this->Largura+1);
                    FacesLab[cont][2] = (i*(this->Largura+1))+j+2+(this->Largura+1)+(this->Pontos/2);
                    FacesLab[cont][3] = (i*(this->Largura+1))+j+2+(this->Pontos/2);
                    cont++;
                }

                /*
                oFile << "f "
                << (i*(this->Largura+1))+j+2+(this->Largura+1) << " "
                << (i*(this->Largura+1))+j+1+(this->Largura+1) << " "
                << (i*(this->Largura+1))+j+1+(this->Largura+1)+(this->Pontos/2) << " "
                << (i*(this->Largura+1))+j+2+(this->Largura+1)+(this->Pontos/2) << " "
                << endl;
                */

                if(i < 40){
                    if(Matriz[i+1][j] != 0){
                        FacesLab[cont][0] = (i*(this->Largura+1))+j+2+(this->Largura+1);
                        FacesLab[cont][1] = (i*(this->Largura+1))+j+1+(this->Largura+1);
                        FacesLab[cont][2] = (i*(this->Largura+1))+j+1+(this->Largura+1)+(this->Pontos/2);
                        FacesLab[cont][3] = (i*(this->Largura+1))+j+2+(this->Largura+1)+(this->Pontos/2);
                        cont++;
                    }
                }
                else{
                    FacesLab[cont][0] = (i*(this->Largura+1))+j+2+(this->Largura+1);
                    FacesLab[cont][1] = (i*(this->Largura+1))+j+1+(this->Largura+1);
                    FacesLab[cont][2] = (i*(this->Largura+1))+j+1+(this->Largura+1)+(this->Pontos/2);
                    FacesLab[cont][3] = (i*(this->Largura+1))+j+2+(this->Largura+1)+(this->Pontos/2);
                    cont++;
                }

                /*
                oFile << "f "
                << (i*(this->Largura+1))+j+1 << " "
                << (i*(this->Largura+1))+j+1+(this->Largura+1) << " "
                << (i*(this->Largura+1))+j+1+(this->Largura+1)+(this->Pontos/2) << " "
                << (i*(this->Largura+1))+j+1+(this->Pontos/2) << " "
                << endl;
                */

                if(j > 0){
                    if(Matriz[i][j-1] != 0){
                        FacesLab[cont][0] = (i*(this->Largura+1))+j+1;
                        FacesLab[cont][1] = (i*(this->Largura+1))+j+1+(this->Largura+1);
                        FacesLab[cont][2] = (i*(this->Largura+1))+j+1+(this->Largura+1)+(this->Pontos/2);
                        FacesLab[cont][3] = (i*(this->Largura+1))+j+1+(this->Pontos/2);
                        cont++;
                    }
                }
                else{
                    FacesLab[cont][0] = (i*(this->Largura+1))+j+1;
                    FacesLab[cont][1] = (i*(this->Largura+1))+j+1+(this->Largura+1);
                    FacesLab[cont][2] = (i*(this->Largura+1))+j+1+(this->Largura+1)+(this->Pontos/2);
                    FacesLab[cont][3] = (i*(this->Largura+1))+j+1+(this->Pontos/2);
                    cont++;
                }

                /*
                oFile << "f "
                << (i*(this->Largura+1))+j+1+(this->Pontos/2) << " "
                << (i*(this->Largura+1))+j+2+(this->Pontos/2) << " "
                << (i*(this->Largura+1))+j+2+(this->Largura+1)+(this->Pontos/2) << " "
                << (i*(this->Largura+1))+j+1+(this->Largura+1)+(this->Pontos/2) << " "
                << endl;
                */

                FacesLab[cont][0] = (i*(this->Largura+1))+j+1+(this->Pontos/2);
                FacesLab[cont][1] = (i*(this->Largura+1))+j+2+(this->Pontos/2);
                FacesLab[cont][2] = (i*(this->Largura+1))+j+2+(this->Largura+1)+(this->Pontos/2);
                FacesLab[cont][3] = (i*(this->Largura+1))+j+1+(this->Largura+1)+(this->Pontos/2);
                cont++;
            }
        }
    }

    leitor->readObj(VerticesLab, FacesLab, cont, Pontos);
    Trajetoria();
    for(int i = 0; i < this->Pontos; i++){
        oFile << "v " <<  VerticesLab[i].x << " " << VerticesLab[i].y << " " << VerticesLab[i].z << endl;
    }
    for(int i = 0; i < cont; i++){
        oFile << "f ";
        for(int j = 0; j < 4; j++){
            oFile << FacesLab[i][j] << " ";
        }
        oFile << endl;
    }

    oFile.close();
}

void Labirinto3D::Trajetoria(){
    caminho = (int**)malloc(this->Altura*sizeof(int*));
    for(int i = 0; i < this->Altura; i++){
        caminho[i] = (int*)malloc(this->Largura*sizeof(int));
    }

    for(int i = 0; i < this->Altura; i++){
        for(int j = 0; j < this->Largura; j++){
            caminho[i][j] = this->Matriz[i][j];
        }
    }
}

#endif
