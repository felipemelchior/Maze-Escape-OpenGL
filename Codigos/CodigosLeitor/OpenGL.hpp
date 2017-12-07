#ifndef OPENGL_H
#define OPENGL_H

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

GLfloat xRotated, yRotated, zRotated;
float angle=0.0;
/*float Ox = 7.5f, Oy = 7.5f, Oz = 15.0f;
float Cx = 7.5f, Cy = 4.0f, Cz = 7.5f;
float Ux = 0.0f, Uy = 0.0f, Uz = 90.0f;*/
/*
GLdouble Ox = 7.5f, Oy = 17.5f, Oz = 7.5f;
GLdouble Cx = 7.5f, Cy = 5.0f, Cz = -15.0f;
GLdouble Ux = 0.0f, Uy = 90.0f, Uz = 0.0f;
*/

//GLdouble Ux = 0.0f, Uy = 90.0f, Uz = 0.0f;
int **caminho;

float scale = 0.01f;
int x = 1, y = 1;
struct Ponto{
	int x;
	int y;
	int z;
};

Ponto **P1;
int altura;
int largura;

GLuint texture[2]; //the array for our texture

GLuint LoadTexture2( const char * filename, int width, int height )
{

    /* FUNCIONA APENAS COM PPM ASCII GERADO SEM COMENTARIOS, COMO NO CASO DO IMAGEMAGICK */

    GLuint texture;
    unsigned char * data;
    FILE * file;
    char linha2[255];
    int r,g,b;

    file = fopen( filename, "rb" );
    if ( file == NULL ) return 0;
    data = (unsigned char *)malloc( sizeof(char)*width * height * 3 );

    fgets(linha2,sizeof linha2, file);  // ignora P3
    fgets(linha2,sizeof linha2, file);  // ignora dimensoes
    fgets(linha2,sizeof linha2, file);  // ignora colordepth


    for (int i=0; i<(width*height*3); i+=3)
    {
        fscanf(file,"%i %i %i",&r,&g,&b);
        data[i]=(unsigned char)r;
        data[i+1]=(unsigned char)g;
        data[i+2]=(unsigned char)b;
    }

    fclose( file );

    glGenTextures( 1, &texture ); //gera a textura
    glBindTexture( GL_TEXTURE_2D, texture ); // faz o binding da texture com o array

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE , GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);

    //glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

////

    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

    free( data );
    return texture;
}

void init(void){
	//glClearColor(0,0,0,0);
    glEnable(GL_LIGHT2);
    //glEnable(GL_DEPTH_TEST);
    glEnable (GL_TEXTURE_2D );
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

}

void DrawCube(void){
    xRotated = 90.0f;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	//gluLookAt(	Ox, Oy, Oz,
		//		Cx, Cy, Cz,
			//	Ux, Uy, Uz);
    glPushMatrix();

    glClear(GL_COLOR_BUFFER_BIT);

    glTranslatef(0.0,0.0,-10.5);
    glRotatef(xRotated,1.0,0.0,0.0);
    glRotatef(yRotated,0.0,1.0,0.0);
    //glRotatef(zRotated,0.0,0.0,1.0);

	//gluLookAt(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	glBegin(GL_POLYGON);
	glColor3f(117.0f,50.0f,17.0f);
	glTexCoord2f(0.0, 0.0); glVertex3f(0*scale, 0*scale, 0*scale);
	glTexCoord2f(0.0, 1.0); glVertex3f(0*scale, 0*scale, 205*scale);
	glTexCoord2f(1.0, 0.0); glVertex3f(205*scale, 0*scale, 205*scale);
	glTexCoord2f(1.0, 1.0); glVertex3f(205*scale, 0*scale, 0*scale);
	glEnd();

    for(int i = 0; i < altura; i++){
        glBindTexture(GL_TEXTURE_2D, texture[1] );
        glBegin (GL_POLYGON);
		glColor3f(1.0f,0.5f,0.0f);
        glTexCoord2f(0.0, 0.0); glVertex3f(P1[i][0].x*scale, P1[i][0].y*scale, P1[i][0].z*scale);
        glTexCoord2f(0.0, 1.0); glVertex3f(P1[i][1].x*scale, P1[i][1].y*scale, P1[i][1].z*scale);
        glTexCoord2f(1.0, 0.0); glVertex3f(P1[i][2].x*scale, P1[i][2].y*scale, P1[i][2].z*scale);
        glTexCoord2f(1.0, 1.0); glVertex3f(P1[i][3].x*scale, P1[i][3].y*scale, P1[i][3].z*scale);
        glEnd();
    }

	glBegin(GL_POLYGON);
	glColor3f(255.0f,0.0f,0.0f);
	glTexCoord2f(0.0, 0.0); glVertex3f(5*x*scale, 0, 5*y*scale);
	glTexCoord2f(0.0, 1.0); glVertex3f(5*x*scale, 0, ((5*y)+5)*scale);
	glTexCoord2f(1.0, 0.0); glVertex3f(((5*x)+5)*scale, 0, ((5*y)+5)*scale);
	glTexCoord2f(1.0, 1.0); glVertex3f(((5*x)+5)*scale, 0, 5*y*scale);
	glEnd();

    glPopMatrix();
    glFlush();
    glutSwapBuffers();
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

    gluPerspective(40.0,(GLdouble)x/(GLdouble)y,0.5,20.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0,0,x,y);  //Use the whole window for rendering
}

void processSpecialKeys(int key, int xx, int yy) {
	float ponto = 0.0;

	switch (key) {
		case GLUT_KEY_LEFT:
			if(caminho[x-1][y] == 1)
			x--;
		break;
		case GLUT_KEY_RIGHT:
			if(caminho[x+1][y] == 1)
			x++;
		break;
		case GLUT_KEY_UP:
			if(caminho[x][y-1] == 1)
			y--;
		break;
		case GLUT_KEY_DOWN:
			if(caminho[x][y+1] == 1)
			y++;
		break;
	}
	DrawCube();
}

void processNormalKeys(unsigned char key, int x, int y){
	switch (key) {
		case 27:
			exit(0);
		break;
	}
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
