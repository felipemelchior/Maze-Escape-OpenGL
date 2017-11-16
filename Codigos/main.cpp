/*
	AUTORES
		FELIPE HOMRICH MELCHIOR
		LUCAS ANTUNES DE ALMEIDA
		LUCAS MATEUS DOS SANTOS MELO
		RAFAEL FERNANDES DA SILVA


	UNIPAMPA - CAMPUS ALEGRETE
*/

#include <iostream>

//#include "menu.hpp"
#include "CodigosLeitor/leitorObj.hpp"
//#include "TestesGeração/Teste03/Labirinto.obj"

using namespace std;

int main(int argc, char **argv){
	//Menu *menu = new Menu();
	Leitor *leitor = new Leitor();

	//leitor->testeArquivo();
	leitor->readObj("Labirinto.obj");
	leitor->imprimeObj();

	//menu->exibeMenu();

	return 0;
}