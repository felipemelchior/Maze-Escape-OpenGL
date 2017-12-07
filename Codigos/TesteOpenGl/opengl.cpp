#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void displayCB(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex2i(200,125);
	glVertex2i(100,375);
	glVertex2i(300,375);
	glEnd();
	glFlush();
}

void keyCB(unsigned char key, int x, int y){
	if(key == 'q') exit(0);
}

int main(int argc, char** argv){
	int win;

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(1366,768);
	win = glutCreateWindow("Triangule");

	glClearColor(0.0,0.0,0.0,0.0);
	gluOrtho2D(0,400,0,500);
	glutDisplayFunc(displayCB);
	glutKeyboardFunc(keyCB);

	glutMainLoop();
}