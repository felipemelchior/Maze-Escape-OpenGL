/*Para compilar => g++ -std=c++98 Nome.cpp -o Executavel */

#include <iostream>

using namespace std;

struct Nodo_adj{
    int index;
    bool visited;
};

class Labirinto{
public:
    Labirinto(int n, int m);
    void SetN(int n);
    void SetM(int m);
    void ExibeMatriz();
    void GetLabirinto(int **matriz);
    int GetPonto(int i, int j);
    int GetN();
    int GetM();
    void SelectAdj(int i, int j);
    void MatrizAdj();
    void Save();
    ~Labirinto();
private:
    int **lab;
    Nodo_adj **Grafo;
    int N;
    int M;
    int Altura;
    int Largura;
};

Labirinto::Labirinto(int n, int m){
    int cont = 0;

    SetN(n);
    SetM(m);

    this->lab = (int**)malloc(N*sizeof(int*));
    this->Grafo = (Nodo_adj**)malloc(n*sizeof(Nodo_adj*));

    for(int i = 0; i < n; i++){
        this->Grafo[i] = (Nodo_adj*)malloc(m*sizeof(Nodo_adj));
        for(int j = 0; j < m; j++){
            this->Grafo[i][j].index = cont;
            this->Grafo[i][j].visited = false;
            cont++;
        }
    }

    for(int i = 0; i < N; i++){
        this->lab[i] = (int*)malloc(M*sizeof(int));
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if((i%2 == 1)&&(j%2 == 1)) this->lab[i][j] = 1;
            else this->lab[i][j] = 0;
        }
    }

    //ExibeMatriz();
    MatrizAdj();
}

void Labirinto::SetN(int n){
    this->N = (2*n)+1;
    this->Altura = n;
}

void Labirinto::SetM(int m){
    this->M = (2*m)+1;
    this->Largura = m;
}

int Labirinto::GetPonto(int i, int j){
    if((i > -1)&&(j > -1)&&(i < Altura)&&(j < Largura))
        return this->lab[i][j];
}

int Labirinto::GetN(){
    return this->N;
}

int Labirinto::GetM(){
    return this->M;
}

void Labirinto::GetLabirinto(int **matriz){
    //matriz = (int**)malloc(this->N*sizeof(int*));

    for(int i = 0; i < this->N; i++){
        //matriz[i] = (int*)malloc(this->M*sizeof(int));
        for(int j = 0; j < this->M; j++){
            matriz[i][j] = this->lab[i][j];
            //cout << matriz[i][j];
        }
    }

    for(int  i= 0; i < this->N; i++){
        free(this->lab[i]);
    }
    for(int i = 0; i < this->Altura; i++){
        free(this->Grafo[i]);
    }
    free(this->lab);
    free(this->Grafo);
}

void Labirinto::MatrizAdj(){
    srand(time(NULL));
    this->lab[((rand()%Altura)*2)+1][0] = 1;
    this->lab[((rand()%Altura)*2)+1][Largura*2] = 1;
    SelectAdj(rand()%Altura, rand()%Largura);
}

void Labirinto::SelectAdj(int i, int j){
    int aux = 0, direcao = 0;
    Nodo_adj *temp = &Grafo[i][j];
    Grafo[i][j].visited = true;

    aux = rand()%4;
    direcao = rand()%2;

    if(direcao == 0) direcao = -1;

    for(int k = 0; k < 4; k++){
        if((aux == 0)||(aux == 4)){
            if(i > 0){
                if(Grafo[i-1][j].visited == false){
                    this->lab[(i*2)][(j*2)+1] = 1;
                    SelectAdj(i-1, j);
                }
            }
        }
        else if((aux == 1)||(aux == -3)||(aux == 5)){
            if(j < Largura-1){
                if(Grafo[i][j+1].visited == false){
                    this->lab[(i*2)+1][(j*2)+2] = 1;
                    SelectAdj(i, j+1);
                }
            }
        }
        else if((aux == 2)||(aux == -2)||(aux == 6)){
            if(i < Altura-1){
                if(Grafo[i+1][j].visited == false){
                    this->lab[(i*2)+2][(j*2)+1] = 1;
                    SelectAdj(i+1, j);
                }
            }
        }
        else if((aux == -1)||(aux == 3)){
            if(j > 0){
                if(Grafo[i][j-1].visited == false){
                    this->lab[(i*2)+1][(j*2)] = 1;
                    SelectAdj(i, j-1);
                }
            }
        }
        aux+=direcao;
    }
}

void Labirinto::ExibeMatriz(){
    for(int i = 0; i < this->N; i++){
        for(int j = 0; j < this->M; j++){
            if(this->lab[i][j] == 0) cout << "[]";
            else cout << "  ";
        }
        cout << endl;
    }
}

int main(int argc, char **argv){
    int **matriz;
    Labirinto *Lab;
    if(argc < 3){
        cout << "Use: " << argv[0] << " N M" << endl;
        exit(1);
    }

    Lab = new Labirinto(atoi(argv[1]), atoi(argv[2]));

    //Lab->ExibeMatriz();

    matriz = (int**)malloc(Lab->GetN()*sizeof(int*));

    for(int i = 0; i < Lab->GetM(); i++){
        matriz[i] = (int*)malloc(Lab->GetM()*sizeof(int));
    }

    Lab->GetLabirinto(matriz);

    for(int i = 0; i < Lab->GetN(); i++){
        for(int j = 0; j < Lab->GetM(); j++){
            if(matriz[i][j] == 0) cout << "[]";
            else cout << "  ";
        }
        cout << endl;
    }
    return 0 ;
}
