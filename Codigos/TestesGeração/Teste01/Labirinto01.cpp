
/*Para compilar => g++ -std=c++98 Nome.cpp -o Executavel */

#include <fstream>
#include <iostream>
#include <vector>
#include <climits>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <cstring>

using namespace std;

struct Nodo_adj{
    int index;
    bool visited;
};

struct pixel
{
    int r;
    int g;
    int b;
};

class Labirinto{
public:
    Labirinto(int n, int m);
    void SetN(int n);
    void SetM(int m);
    void ExibeMatriz();
    int GetPonto(int i, int j);
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

class image
{
public:
    image();
    ~image();
    image(int nwidth, int nheight);
    image(int r, int g, int b, int nwidth, int nheight, int nmaxcolor);
    void loadimage(string nombre);
    void saveimage(string nombre);
    void putpixel(int i,int j,int red,int green,int blue);
    int signal(float x);
    int getred(int x, int y);
    int getgreen(int x, int y);
    int getblue(int x, int y);
private:
    int width;
    int height;
    int maxcolor;

    vector< vector<pixel> > buffer;

};

image::image()
{
    buffer.resize(1920,vector<pixel> (1080));
}

image::image(int r, int g, int b, int nwidth, int nheight, int nmaxcolor){
    width = nwidth;
    height = nheight;
    maxcolor = nmaxcolor;

    buffer.resize(nwidth,vector<pixel> (nheight));
    for(int j = 0; j < nheight; j++){
        for(int i = 0; i < nwidth; i++){
            buffer[i][j].r = r;
            buffer[i][j].g = g;
            buffer[i][j].b = b;
        }
    }
}

image::image(int nwidth, int nheight)
{
    buffer.resize(nwidth,vector<pixel> (nheight));
}

image::~image()
{
}

int image::getred(int i, int j)
{
    return  buffer[i][j].r;
}
int image::getgreen(int i, int j)
{
    return  buffer[i][j].g;
}
int image::getblue(int i, int j)
{
    return  buffer[i][j].b;
}

void image::putpixel(int i,int j,int red=0,int green=0,int blue=0)
{
    buffer[i][j].r=red;
    buffer[i][j].g=green;
    buffer[i][j].b=blue;
}

void image::loadimage(string nombre)
{
    int red,green,blue;
    cout << "Arquivo de entrada "<< nombre <<endl;
    ifstream iFile(nombre.c_str());

    if (iFile==NULL)
    {
        cout << "Missing file!" << endl;
        exit(-1);
    }

    iFile.ignore(INT_MAX, '\n');
    //iFile.ignore(INT_MAX, '\n'); // REMOVED BECAUSE OF imagemagick-CONVERT NOT INSERTING COMMENT LINE IN IMAGE
    //IF USING IRFANVIEW, UNCOMMENT LINE ABOVE

    iFile >> width;
    iFile >> height;
    iFile >> maxcolor;
    buffer.resize(width,vector<pixel> (height));
    cout << width << " " << height << endl << maxcolor << endl;

    for(int j=0; j<height; j++)
        for(int i=0; i<width; i++)
        {

            iFile >> red;
            iFile >> green;
            iFile >> blue;

            putpixel(i,j,red,green,blue);
        }

    iFile.close();
}
void image::saveimage(string nombre)
{
    ofstream oFile(nombre.c_str());

    if (oFile==NULL)
    {
        cout << "Missing file!" << endl;
        exit(0);
    }
    oFile << "P3\n" << width << " " << height << "\n" << maxcolor << "\n";


    for(int j=0; j<height; j++)
    {
        for(int i=0; i<width; i++)
        {
            oFile << getred(i,j) << " " << getgreen(i,j) << " " << getblue(i,j) << " ";
        }
        oFile << endl;
    }

    oFile.close();
}

void Labirinto::SetN(int n){
    this->N = (2*n)+1;
    this->Altura = n;
}

void Labirinto::SetM(int m){
    this->M = (2*m)+1;
    this->Largura = m;
}

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
        this->lab[i] = (int*)malloc(N*sizeof(int));
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

int Labirinto::GetPonto(int i, int j){
    if((i > -1)&&(j > -1)&&(i < Altura)&&(j < Largura))
        return this->lab[i][j];
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

void Labirinto::Save(){

    ofstream oFile("Labirinto.txt");

    oFile << N << " " << M << endl;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            oFile << this->lab[i][j] << " ";
        }
        oFile << endl;
    }

    int altura, largura, indiceX, indiceY;

    image* fig1=new image(0, 0, 0, 16, 16, 255);
    image* fig2=new image(0, 0, 0, 16, 16, 255);

    ifstream iFile1("Labirinto.txt");
    iFile1 >> largura;
    iFile1 >> altura;

    image* fig3=new image(0, 0, 0, 16*largura, 16*altura, 255);

    int matriz[largura][altura];

    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
            iFile1 >> matriz[i][j];
        }
    }

    fig1->loadimage("b2.ppm");
    fig2->loadimage("b3.ppm");

    for(int i = 0; i < altura; i++){
        for(int j = 0; j < largura; j++){
            if(i == 0){
                if(j == 0){
                    indiceX = 0;
                    indiceY = 0;
                }
                else{
                    indiceX = j * 16;
                    indiceY = 0;
                }
            }
            else{
                if(j == 0){
                    indiceX = 0;
                    indiceY = i * 16;
                }
                else{
                    indiceX = i * 16;
                    indiceY = j * 16;
                }

            }
            if(matriz[i][j] == 0){
                for(int k = 0; k < 16; k++){
                    for(int l = 0; l < 16; l++){
                        fig3->putpixel(indiceX + k, indiceY + l, fig1->getred(k,l), fig1->getgreen(k,l), fig1->getblue(k,l));
                    }
                }
            }
            else{
                for(int k = 0; k < 16; k++){
                    for(int l = 0; l < 16; l++){
                        fig3->putpixel(indiceX + k, indiceY + l, fig2->getred(k,l), fig2->getgreen(k,l), fig2->getblue(k,l));
                    }
                }
            }
        }
    }

    fig3->saveimage("LabirintoPerfeito.ppm");

    delete fig1;
    delete fig2;
    delete fig3;
}

int main(int argc, char **argv){
    Labirinto *Lab;
    if(argc < 3){
        cout << "Use: " << argv[0] << " N M" << endl;
        exit(1);
    }

    Lab = new Labirinto(atoi(argv[1]), atoi(argv[2]));
    Lab->Save();
    //Lab->ExibeMatriz();

    return 0 ;
}
