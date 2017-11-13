#ifndef LABIRINTO3D_H
#define LABIRINTO3D_H

#include <iostream>
#include "Labirinto.hpp"

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
    void Status();
private:
    int **matriz;
    int Altura;
    int Largura;
    int Dim;
};

Labirinto3D::Labirinto3D(int n, int m){
    Labirinto *Lab;

    Lab = new Labirinto(n, m);

    this->matriz = (int**)malloc(Lab->GetN()*sizeof(int*));

    for(int i = 0; i < Lab->GetM(); i++){
        this->matriz[i] = (int*)malloc(Lab->GetM()*sizeof(int));
    }

    Lab->GetLabirinto(this->matriz);
    SetAltura(Lab->GetN());
    SetLargura(Lab->GetM());

    Dim = 5;

    ExibeMatriz();
    Conversor3D();
}

Labirinto3D::Labirinto3D(){
    int n = 10, m = 10;
    Labirinto *Lab;

    Lab = new Labirinto(n, m);

    this->matriz = (int**)malloc(Lab->GetN()*sizeof(int*));

    for(int i = 0; i < Lab->GetM(); i++){
        this->matriz[i] = (int*)malloc(Lab->GetM()*sizeof(int));
    }

    Lab->GetLabirinto(this->matriz);
    SetAltura(Lab->GetN());
    SetLargura(Lab->GetM());

    Dim = 5;

    ExibeMatriz();
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
            if(this->matriz[i][j] == 0) cout << "[]";
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
                    if(matriz[i][j+1] == 1){
                        cout << "[" << i << "]" << "[" << j << "] Direita Aberta " << endl;
                        cont++;
                    }
                    else{
                        cout << "[" << i << "]" << "[" << j << "] Direita Fechada " << endl;
                        cont++;
                    }
                }
                else if(j < Largura){
                    if(matriz[i][j] == 1){
                        cout << "[" << i << "]" << "[" << j << "] Esquerda Aberta " << endl;
                        cont++;
                    }
                    else{
                        cout << "[" << i << "]" << "[" << j << "] EsquerdaFechada " << endl;
                        cont++;
                    }
                }
                if(i < Altura-1){
                    if(matriz[i+1][j] == 1){
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

void Labirinto3D::Conversor3D(){
    //Status();
    for(int i = 0; i < this->Altura; i++){
        for(int j = 0; j < this->Largura; j++){
            if(i == 0){
                //cout << "[" << i << "]" << "[" << j << "] Direita Fechada " << endl;
                //cout << "[" << i << "]" << "[" << j << "] Inferior Fechado " << endl;
            }
            else if(j == 0){
                //cout << "[" << i << "]" << "[" << j << "] Direita Fechada " << endl;
                //cout << "[" << i << "]" << "[" << j << "] Inferior Fechado " << endl;
            }
            else{
                if(j < Largura-1){
                    if(matriz[i][j+1] == 0){
                        //cout << "[" << i << "]" << "[" << j << "] Direita Direita Fechada " << endl;
                    }
                }
                else if(j < Largura){
                    if(matriz[i][j] == 0){
                        //cout << "[" << i << "]" << "[" << j << "] Esquerda Fechada " << endl;
                    }
                }
                if(i < Altura-1){
                    if(matriz[i+1][j] == 0){
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
