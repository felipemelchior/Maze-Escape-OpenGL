#ifndef OPENGL_H
#define OPENGL_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

GLfloat xRotated, yRotated, zRotated;
GLuint texture[1]; //the array for our texture

struct Ponto{
	int x;
	int y;
	int z;
};

Ponto **P1;
int altura;
int largura;

void init(void){
	glClearColor(0,0,0,0);
}

void DrawCube(void){
    xRotated = 90.0f;
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0,0.0,-10.5);
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    glRotatef(zRotated,0.0,0.0,1.0);

    for(int i = 0; i < altura; i++){
        glBindTexture( GL_TEXTURE_2D, texture[0] );
        glBegin (GL_POLYGON);
        glTexCoord2f(0.0, 0.0); glVertex3f(P1[i][0].x*0.01f, P1[i][0].y*0.01f, P1[i][0].z*0.01f);    // Top Right Of The Quad (Top)
        glTexCoord2f(0.0, 1.0); glVertex3f(P1[i][1].x*0.01f, P1[i][1].y*0.01f, P1[i][1].z*0.01f);    // Top Left Of The Quad (Top)
        glTexCoord2f(1.0, 0.0); glVertex3f(P1[i][2].x*0.01f, P1[i][2].y*0.01f, P1[i][2].z*0.01f);    // Bottom Left Of The Quad (Top)
        glTexCoord2f(1.0, 1.0); glVertex3f(P1[i][3].x*0.01f, P1[i][3].y*0.01f, P1[i][3].z*0.01f);    // Bottom Right Of The Quad (Top)
        glEnd();
    }

    glFlush();
}

void animation(void){
    yRotated += 0.01;
    xRotated += 0.02;
    DrawCube();
}

void reshape(int x, int y){
    if (y == 0 || x == 0) return;  //Nothing is visible then, so return
    //Set a new projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //Angle of view:40 degrees
    //Near clipping plane distance: 0.5
    //Far clipping plane distance: 20.0

    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

void ImprimeP1(){
	int cont = 1;
	for(int i = 0; i < altura; i++){
		for(int j = 0; j < 4; j++){
			cout << "v " << P1[i][j].x << " " << P1[i][j].y << " " << P1[i][j].z << endl;
		}
		cout << "f " << cont << " " << cont+1 << " " << cont+2 << " " << cont+3 << endl;
		cont+=4;
	}
}

#endif
