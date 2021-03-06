#include <stdio.h>
#include<iostream>
#include <gl/glut.h>
#include <string>
#include<stdlib.h>
#include"imageloader.h"



GLfloat spin = 0.0; //fan rotation variable
static GLfloat spin_speed = 5.0;
float spin_x = 0;
float spin_y = 0;
float spin_z = 1;
float translate_x = -142.0;
float translate_y = 100.0;
float translate_z = -50.0;




GLfloat skyWidth, skyHeight;
GLfloat x, y;
GLfloat skySpeed;




GLfloat  skyX = -400;
GLfloat skyY = 200;
bool begin = true;

bool skyMoveRight;

GLuint texture1;
GLuint texture2;


void initialize() {

	skyWidth = -10.0f; skyHeight = 10.0f;

	skySpeed = 3.0f;
	skyMoveRight = true;
}


GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
											 //Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
						  //as unsigned numbers
		image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

void myInit(void)
{
	glClearColor(1, 1, 1, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);

	gluPerspective(45, 1.00, 1.0, 0.0);
	Image* image = loadBMP("texture.bmp");
	Image* image2 = loadBMP("ground.bmp");

	texture1 = loadTexture(image);
	texture2 = loadTexture(image2);


	delete image, image2;
}

//house
void house() {
	glBegin(GL_QUADS);
	glColor3f(0.9f, 0.9f, 0.8f); //1
	glVertex2i(210, -5);
	glVertex2i(355, -10);
	glVertex2i(355, -100);
	glVertex2i(210, -90);
	glEnd();
	glFlush();

	glBegin(GL_TRIANGLES);
	glColor3f(0.9f, 0.9f, 0.8f); //2	
	glVertex2i(275, 70);
	glVertex2i(355, -10);
	glVertex2i(210, -5);
	glEnd();
	glFlush();

	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 0.9f); //3
	glVertex2i(350, -100);
	glVertex2i(450, -90);
	glVertex2i(450, -5);
	glVertex2i(350, -10);
	glEnd();
	glFlush();


	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.2f, 0.2f); //roof
	glVertex2i(265, 80);
	glVertex2i(380, 75);
	glVertex2i(465, -5);
	glVertex2i(350, -10);
	glEnd();
	glFlush();

	glBegin(GL_QUADS);
	glColor3f(0.7f, 0.1f, 0.1f); //small roof
	glVertex2i(275, 70);
	glVertex2i(265, 80);
	glVertex2i(190, -15);
	glVertex2i(210, -15);
	glEnd();
	glFlush();

	//window
	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.1f, 0.1f);
	glVertex2i(260, -67);
	glVertex2i(260, -22);
	glVertex2i(300, -24);
	glVertex2i(300, -70);
	glEnd();
	glFlush();

	//door
	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.1f, 0.1f);
	glVertex2i(380, -97);
	glVertex2i(380, -22);
	glVertex2i(420, -20);
	glVertex2i(420, -93);
	glEnd();
	glFlush();

	//border1
	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.1f, 0.1f);
	glVertex2i(200, -95);
	glVertex2i(200, -85);
	glVertex2i(350, -100);
	glVertex2i(350, -110);
	glEnd();
	glFlush();

	//border2
	glBegin(GL_QUADS);
	glColor3f(0.2f, 0.1f, 0.1f);
	glVertex2i(350, -100);
	glVertex2i(350, -110);
	glVertex2i(455, -95);
	glVertex2i(455, -85);

	glEnd();
	glFlush();
}

//treebody
void treebody()
{
	glColor3f(0.3, 0, 0);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex2f(130, 90);
	glVertex2f(100, 90);
	glVertex2f(130, -100);
	glVertex2f(100, -100);
	glEnd();
}

//treeleaf
void treecircle(int k, int r, int h) {
	glColor3f(0.0f, 0.5f, 0.0f);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < 700; i++)
	{
		x = r * cos(i*3.1416) - h;
		y = r * sin(i*3.1416) + k;
		glVertex2f(y, x);

		x = r * cos(i + 3.1416) - h;
		y = r * sin(i + 3.1416) + k;
		glVertex2f(y, x);
	}
	glEnd();
	glFlush();
}

//trees
void tree1() {

	treecircle(115, 40, -130); //top leaf1
	treecircle(80, 35, -110); //top leaf2
	treecircle(80, 35, -80); //top leaf3
	treecircle(115, 40, -70); //top leaf4
	treecircle(150, 35, -110); //top leaf5
	treecircle(150, 35, -80); //top leaf6

	treecircle(80, 30, 10);  //left leaf
	treecircle(140, 20, 35);  //right leaf
}

void tree2() {
	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.8f, 0.0f); //tree00
	glVertex2i(350, 140);
	glVertex2i(385, 70);
	glVertex2i(350, 70);

	glVertex2i(350, 110);
	glVertex2i(390, 40);
	glVertex2i(350, 40);

	glVertex2i(350, 80);
	glVertex2i(395, 10);
	glVertex2i(350, 10);

	glEnd();
	glFlush();

}

void tree3() {
	glBegin(GL_TRIANGLES);
	glColor3f(0.4f, 0.6f, 0.0f); //tree01
	glVertex2i(350, 140);
	glVertex2i(315, 70);
	glVertex2i(350, 70);

	glVertex2i(350, 110);
	glVertex2i(310, 40);
	glVertex2i(350, 40);

	glEnd();
	glFlush();

}

//fan

void setSpin(float x, float y, float z)
{
	spin_x = x;
	spin_y = y;
	spin_z = z;
}

void reset()
{
	spin_x = 0;
	spin_y = 1;
	spin_z = 0;
	/*translate_x = 0.0;
	translate_y = 0.0;
	translate_z = -20.0;*/
}


/*void stop() {

glBegin(GL_TRIANGLES);
glColor3f(1, 1, 1);
glVertex2f(0, 0);
glVertex2f(1, -20);
glVertex2f(-1, -20);
glEnd();

}*/
void fan()
{
	glPushMatrix();

	glBegin(GL_TRIANGLES);  //fan
	glColor3f(1.0f, 0.6f, 0.0f);
	glVertex2i(-90, 80);	//top fan
	glVertex2i(-100, 110);
	glVertex2i(-80, 110);


	/*glVertex2i(-92, 60);//bottom fan
	glVertex2i(-100, 10);
	glVertex2i(-80, 10);*/


	/*glVertex2i(-92, 60);//	right
	glVertex2i(-40, 70);
	glVertex2i(-40, 50);


	glVertex2i(-92, 60); //left
	glVertex2i(-140, 70);
	glVertex2i(-140, 50);*/

	glEnd();
	glFlush();

	glPopMatrix();
}


void fanpole() {

	glPushMatrix();



	//glScalef(0.6, 1.0, 0.6);
	//lTranslatef(180.0, 0, 0);

	glBegin(GL_TRIANGLES);  //fanpole
	glColor3f(0.8f, 0.8f, 0.8f);
	glVertex2i(-142, 110);
	glVertex2i(-150, -90);
	glVertex2i(-130, -90);
	glEnd();
	glPopMatrix();

}

//water 
void water() {
	glColor3f(0.0f, 0.6f, 0.9f);
	glBegin(GL_POLYGON);
	glVertex2i(-250, -80);
	glVertex2i(250, -250);
	glVertex2i(-250, -250);
	glVertex2i(60, -150);

	glEnd();
	glFlush();

}

//Mountain
void mountain()
{
	//mountain1
	glColor3f(0.9f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(100, 50);
	glVertex2f(190, 190);
	glVertex2f(260, 50);
	glEnd();
	//
	glColor3f(0.61f, 0.3f, 0.1f);
	glBegin(GL_TRIANGLES);
	glVertex2f(100, 50);
	glVertex2f(170, 160);
	glVertex2f(265, 50);

	glColor3f(0.61f, 0.3f, 0.1f);
	glBegin(GL_TRIANGLES);
	glVertex2f(120, 50);
	glVertex2f(205, 160);
	glVertex2f(270, 50);
	glEnd();

	//mountain2
	glColor3f(0.9f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(-580 + 1000, 50);
	glVertex2f(-510 + 1000, 145);
	glVertex2f(-460 + 1000, 50);
	glEnd();

	glColor3f(0.61f, 0.3f, 0.1f);
	glBegin(GL_TRIANGLES);
	glVertex2f(-580 + 1000, 50);
	glVertex2f(-530 + 1000, 120);
	glVertex2f(-470 + 1000, 50);

	glBegin(GL_TRIANGLES);
	glVertex2f(-550 + 1000, 50);
	glVertex2f(-500 + 1000, 125);
	glVertex2f(-450 + 1000, 50);

	glEnd();
	glFlush();
}

//cloud
void cloudcircle(int k, int r, int h) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < 700; i++)
	{
		x = r * cos(i*3.1416) - h;
		y = r * sin(i*3.1416) + k;
		glVertex2f(y, x);

		x = r * cos(i + 3.1416) - h;
		y = r * sin(i + 3.1416) + k;
		glVertex2f(y, x);
	}
	glEnd();
	glFlush();
}

//sun
void suncircle(int k, int r, int h) {
	glColor3f(1.0f, 1.0f, 0.4f);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < 700; i++)
	{
		x = r * cos(i*3.1416) - h;
		y = r * sin(i*3.1416) + k;
		glVertex2f(y, x);

		x = r * cos(i + 3.1416) - h;
		y = r * sin(i + 3.1416) + k;
		glVertex2f(y, x);
	}
	glEnd();
	glFlush();
}

//road
void road() {

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1.0f, 0.8f, 0.6f);
	glVertex2i(330, -100);
	glVertex2i(350, -80);
	glVertex2i(420, -250);
	glVertex2i(480, -200);
	glEnd();
	glFlush();

}


void animation() {



	cloudcircle(290 + skyX, 25, -130);
	cloudcircle(320 + skyX, 25, -130);
	cloudcircle(350 + skyX, 25, -130);
	cloudcircle(390 + skyX, 25, -130);
	cloudcircle(310 + skyX, 25, -150);
	cloudcircle(340 + skyX, 25, -160);
	cloudcircle(370 + skyX, 25, -150);


	cloudcircle(skyX + 50, 30, skyY - 400);
	cloudcircle(skyX + 90, 30, skyY - 400);
	cloudcircle(skyX + 140, 30, skyY - 400);
	cloudcircle(skyX + 190, 30, skyY - 400);
	cloudcircle(skyX + 90, 30, skyY - 430);
	cloudcircle(skyX + 145, 30, skyY - 430);


	glEnd();
	glFlush();


}







void sky() {


	//Sun
	suncircle(590, 50, -200);

	//GLint skyX = -500;
	//GLint skyY = 500;

	//Cloud
	cloudcircle(-10, 35, -170);
	cloudcircle(30, 30, -170);
	cloudcircle(70, 30, -170);
	cloudcircle(10, 35, -200);
	cloudcircle(45, 30, -200);

	cloudcircle(360, 25, -220);
	cloudcircle(390, 25, -220);
	cloudcircle(420, 25, -220);
	cloudcircle(460, 25, -220);
	cloudcircle(380, 25, -240);
	cloudcircle(410, 25, -250);
	cloudcircle(440, 25, -240);


	cloudcircle(720, 25, -130);
	cloudcircle(750, 25, -130);
	cloudcircle(690, 25, -130);
	cloudcircle(710, 25, -150);
	cloudcircle(740, 25, -160);

	glEnd();
	glFlush();

}

void drawScene() {

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(40, 220, -2.35f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture1);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);

	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(-500.0, 50.0, 0.0);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-500.0, 340.0, 0.0);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(500.0, 340.0, 0.0);

	glTexCoord2f(1.0, 0.0);
	glVertex3f(500.0, 50.0, 0.0);

	glEnd();
	glFlush();

	glDisable(GL_TEXTURE_2D);

	glPushMatrix();

	glScalef(0.5, 0.9, 0.5);
	// animation();
	sky();
	mountain();

	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture2);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);


	glTexCoord2f(0.0, 0.0);
	glVertex3f(-500.0, -490.0, 0.0);

	glTexCoord2f(0.0, 4.0);
	glVertex3f(-500.0, 50.0, 0.0);

	glTexCoord2f(4.0, 4.0);
	glVertex3f(500.0, 50.0, 0.0);

	glTexCoord2f(4.0, 0.0);
	glVertex3f(500.0, -490.0, 0.0);

	glEnd();
	glFlush();
	glDisable(GL_TEXTURE_2D);
	tree2();
	tree3();
	road();
	glScalef(0.6, 1.0, 0.6);
	glTranslatef(180.0, 0, 0);
	house();
	treebody();

	//glPushMatrix();
	tree1();
	fanpole();
	water();
	//glPopMatrix();

	glTranslatef(-50.0, 50, 0);
	//fan();
	//rotate();

}

void myDisplay(void)
{
	drawScene();
	animation();
	//rotate();
	glPushMatrix();
	//glTranslatef(90, -80, -50);
	//stop();
	glRotatef(spin, spin_x, spin_y, spin_z);

	//  glColor3f(0.0, 0.0, .0);
	//glPointSize(4.0);

	glBegin(GL_TRIANGLES);  //fan
	glColor3f(1.0f, 0.6f, 0.0f);
	glVertex2i(0, 0);	//top fan
	glVertex2i(-20, 100);
	glVertex2i(-50, 140);


	glVertex2i(0, 0);//bottom fan
	glVertex2i(30, 100);
	glVertex2i(60, 140);
	glEnd();
	glFlush();
	//fan();
	glTranslatef(-90, 80, 50);
	glPopMatrix();
	//glPointSize(4.0);
	glutSwapBuffers();


	if (begin) {
		initialize();

		begin = false;
	}

	//glutSwapBuffers();

	if (skyX + skyWidth >= 600)
	{
		skyMoveRight = false;
	}
	else if (skyX <= -600)
	{
		skyMoveRight = true;
	}

	if (skyMoveRight)
	{
		skyX += skySpeed;
	}
	else
	{
		skyX -= skySpeed;
	}



	//rotate();
}
void spinDisplay(void)
{
	spin = spin + spin_speed;
	if (spin>360.0)
	{
		spin = spin - 360.0;
	}
	glutPostRedisplay();
}




void spinDisplayReverse(void)
{
	spin = spin - spin_speed;
	if (spin<360.0)
	{
		spin = spin + 360.0;
	}
	glutPostRedisplay();
}




void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplay);
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN)
		{
			glutIdleFunc(NULL);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
			glutIdleFunc(spinDisplayReverse);
		break;
	default:
		break;
	}
}



void keyboard(unsigned char key, int x, int y)
{
	//-------- spin --------
	if (key == 'x')
	{
		setSpin(1.0, 0.0, 0.0);
		glutPostRedisplay();
	}
	else if (key == 'y')
	{
		setSpin(0.0, 1.0, 0.0);
		glutPostRedisplay();
	}
	else if (key == 'z')
	{
		setSpin(0.0, 0.0, 1.0);
		glutPostRedisplay();
	}
	else if (key == 'a')
	{
		setSpin(1.0, 1.0, 1.0);
		glutPostRedisplay();
	}
	//-------- spin --------
	//-------- zoom --------
	else if (key == 'i')
	{
		translate_z++;
		glutPostRedisplay();
	}
	else if (key == 'o')
	{
		translate_z--;
		glutPostRedisplay();
	}
	//-------- zoom --------
	//-------- reset -------
	else if (key == 'r')
	{
		reset();
		glutPostRedisplay();
	}
	//-------- reset -------
}



void Timer(int value) {

	glutPostRedisplay();
	glutTimerFunc(30, Timer, 0);
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1200, 680);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("PROJECT");
	glutDisplayFunc(myDisplay);

	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);

	glutTimerFunc(0, Timer, 0);
	myInit();

	glutMainLoop();
	return 0;
}

