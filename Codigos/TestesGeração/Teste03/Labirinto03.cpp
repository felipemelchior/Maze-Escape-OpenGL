#include <iostream>
#include "Labirinto3D.hpp"

using namespace std;
/*Para compilar => g++ -std=c++98 Nome.cpp -o Executavel */

int main(int argc, char **argv){
    Labirinto3D *Lab;
    if(argc < 3){
        cout << "Use: " << argv[0] << " Altura Largura" << endl;
        exit(1);
    }

    if((atoi(argv[1]) < 1)||(atoi(argv[2]) < 1))
        Lab = new Labirinto3D();
    else
        Lab = new Labirinto3D(atoi(argv[1]), atoi(argv[2]));

    return 0;
}
