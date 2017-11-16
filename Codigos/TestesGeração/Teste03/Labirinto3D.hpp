#ifndef LABIRINTO3D_H
#define LABIRINTO3D_H

#include <iostream>
#include "Labirinto.hpp"

using namespace std;

struct Ponto{
    int x;
    int y;
    int z;
};

class Labirinto3D{
public:
    Labirinto3D(int n, int m);
    Labirinto3D();
    ~Labirinto3D();
    void SetAltura(int altura);
    void SetLargura(int largura);
    void ExibeMatriz();
    void Conversor3D();
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

    ExibeMatriz();
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
    //Status();
    for(int i = 0; i < this->Altura; i++){
        for(int j = 0; j < this->Largura; j++){
            if(i == 0){
                //cout << "[" << i << "]" << "[" << j << "] Inferior Fechado " << endl;
            }
            else if(j == 0){
                //cout << "[" << i << "]" << "[" << j << "] Direita Fechada " << endl;
            }
            else{
                if(j < Largura-1){
                    if(Matriz[i][j+1] == 0){
                        //cout << "[" << i << "]" << "[" << j << "] Direita Fechada " << endl;
                    }
                }
                else if(j < Largura){
                    if(Matriz[i][j] == 0){
                        //cout << "[" << i << "]" << "[" << j << "] Esquerda Fechada " << endl;
                    }
                }
                if(i < Altura-1){
                    if(Matriz[i+1][j] == 0){
                        //cout << "[" << i << "]" << "[" << j << "] Inferior Fechado " << endl;
                    }
                }
                else{
                    //cout << "[" << i << "]" << "[" << j << "] Inferior Fechado " << endl;
                }
            }
        }
    }
}
#endif
