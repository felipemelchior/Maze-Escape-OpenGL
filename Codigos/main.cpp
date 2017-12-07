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
#include "GeracaoLabirinto/Labirinto3D.hpp"

using namespace std;

int main(int argc, char **argv){
	Labirinto3D* lab = new Labirinto3D(20,20);

	glutInit(&argc, argv);
	//we initizlilze the glut. functions
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1366,768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(DrawCube);

	texture[0]=LoadTexture2("../../Texturas/TexturaGrama.ppm", 1024,1024);
    texture[1]=LoadTexture2("../../Texturas/TexturaParede.ppm", 512,512);

	glutReshapeFunc(reshape);
	//Set the function for the animation.
	//glutIdleFunc(animation);
	glutMainLoop();

	return 0;
}
