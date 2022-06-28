#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/glut.h>
#endif


#include <iostream>
#include <stdio.h>

#define WHITE 1.0, 1.0, 1.0
#define BLACK 0.0, 0.0, 0.0

#define window_width 500
#define window_height 550
float logWidth=100.0;
float logHeight=100.0;



bool cells[50][50];
bool newCells[50][50];
int mouseX;
int mouseY;


void printtext(char *str,int x,int y) {
    glColor3f (0, 0, 0);
    glRasterPos2d(x,y);
    for (int i=0;i<strlen(str);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
    glFlush();
}

void backgrundFunc (float r ,float g , float b, int x)
{
    glClearColor(r,g,b,0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,500.0,0.0,550.0);

}


void mouseClick(int btn, int state, int x, int y)
{
    //left mouse click to change cell state
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
        mouseX = x;
        mouseX=0.5+1.0*mouseX;
        mouseY = window_height - y;
        mouseY=0.5+1.0*mouseY;
        printf("%d %d\n", mouseX/10, mouseY/10);

        if (mouseY<500){
            if (cells[mouseX/10][mouseY/10]==1)
                cells[mouseX/10][mouseY/10]=0;
            else
                cells[mouseX/10][mouseY/10]=1;
        }
    }
    glutPostRedisplay();
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	printtext("Conway's Game Of Life", 150, 510);
    glColor3f(0.0,0.0,0.0);
    //draw grid of lines
    for(int y =4; y<=504; y+=10){
            glBegin(GL_LINES);
                glVertex2i(4,y);
                glVertex2i(504,y);
            glEnd();
            glBegin(GL_LINES);
                glVertex2i(y,4);
                glVertex2i(y,504);
            glEnd();
        }
    glColor3f(1.0,0.0,0.0);
    // draw red squars for alive cells only
    for(int i = 0; i<50; i++){
        for(int j = 0; j<50; j++){
            if(cells[i][j]==1){
                glBegin(GL_QUADS);
                    glVertex2i(i*10+4,j*10+5);
                    glVertex2i(i*10+4,j*10+15);
                    glVertex2i(i*10+14,j*10+15);
                    glVertex2i(i*10+14,j*10+5);
                glEnd();
            }
        }
    }
	glutSwapBuffers();
    glFlush();
}

void specialKeyboard(int key, int x, int y)
{
    // new cells array gets 0 values to reset
    for(int i = 0; i<50; i++){
        for(int j = 0; j<50; j++){
            newCells[i][j]=0;
        }
    }
    int c=0;
    if(key== GLUT_KEY_RIGHT){
        for(int i = 0; i<50; i++){
            for(int j = 0; j<50; j++){
                c=0;
                //counting number of alive cells around each cell
                // corners conditions to dodge indexOutOfBounds error
                if (i==0 && j==0){
                    if(cells[i+1][j+1]==1)
                        c++;
                    if(cells[i][j+1]==1)
                        c++;
                    if(cells[i+1][j]==1)
                        c++;
                }
                else if (i==49 && j==0){
                    if(cells[i][j+1]==1)
                        c++;
                    if(cells[i-1][j]==1)
                        c++;
                    if(cells[i-1][j+1]==1)
                        c++;
                }
                else if (i==0 && j==49){
                    if(cells[i][j]==1)
                        c++;
                    if(cells[i][j-1]==1)
                        c++;
                    if(cells[i+1][j-1]==1)
                        c++;
                }
                else if (i==49 && j==49){
                    if(cells[i-1][j-1]==1)
                        c++;
                    if(cells[i-1][j]==1)
                        c++;
                    if(cells[i][j-1]==1)
                        c++;
                }
                else {
                    // Left vertical line
                    if(i==0){
                        if(cells[i][j-1]==1)
                            c++;
                        if(cells[i][j+1]==1)
                            c++;
                        if(cells[i+1][j-1]==1)
                            c++;
                        if(cells[i+1][j]==1)
                            c++;
                        if(cells[i+1][j+1]==1)
                            c++;
                    }
                    // bottom line
                    else if (j==0){
                        if(cells[i-1][j]==1)
                            c++;
                        if(cells[i-1][j+1]==1)
                            c++;
                        if(cells[i][j+1]==1)
                            c++;
                        if(cells[i+1][j]==1)
                            c++;
                        if(cells[i+1][j+1]==1)
                            c++;
                    }
                    //right line
                    else if (i==49){
                        if(cells[i-1][j-1]==1)
                            c++;
                        if(cells[i-1][j]==1)
                            c++;
                        if(cells[i-1][j+1]==1)
                            c++;
                        if(cells[i][j-1]==1)
                            c++;
                        if(cells[i][j+1]==1)
                            c++;
                    }
                    // upper line
                    else if (j==49){
                       if(cells[i-1][j-1]==1)
                            c++;
                        if(cells[i-1][j]==1)
                            c++;
                        if(cells[i][j-1]==1)
                            c++;
                        if(cells[i+1][j-1]==1)
                            c++;
                        if(cells[i+1][j]==1)
                            c++;
                    }
                    //rest of the grid
                    else {
                        if(cells[i-1][j-1]==1)
                            c++;
                        if(cells[i-1][j]==1)
                            c++;
                        if(cells[i-1][j+1]==1)
                            c++;
                        if(cells[i][j-1]==1)
                            c++;
                        if(cells[i][j+1]==1)
                            c++;
                        if(cells[i+1][j-1]==1)
                            c++;
                        if(cells[i+1][j]==1)
                            c++;
                        if(cells[i+1][j+1]==1)
                            c++;
                    }
                }
                //New array to not disturb old one
                if(c==0 || c==1)
                    newCells[i][j]=0;
                if(c==3)
                    newCells[i][j]=1;
                if(c==2)
                    newCells[i][j]=cells[i][j];
                if(c>3)
                    newCells[i][j]=0;
            }
        }
    // Assign new cells to the main cells array
    for(int i = 0; i<50; i++){
        for(int j = 0; j<50; j++){
                cells[i][j]=newCells[i][j];
        }
    }
}
    if (key==GLUT_KEY_F1){
    for(int i = 0; i<50; i++){
        for(int j = 0; j<50; j++){
                cells[i][j]=0;
            }
        }
    }
    if (key==GLUT_KEY_F2){
    backgrundFunc(0.796, 0.396, 0.964, 0);
	glutDisplayFunc(menuDisplay);
    }

    //empty function
    if(key== GLUT_KEY_LEFT){

    }
    glutPostRedisplay();
}



int main(int argc, char **argv) {
  	glutInit(&argc, argv);
    	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(450, 210);
	glutCreateWindow("Conway's Game of Life");
    for(int i = 0; i<50; i++){
        for(int j = 0; j<50; j++){
                cells[i][j]=0;
        }
    }
	backgrundFunc(0.796, 0.396, 0.964, 0);
	glutDisplayFunc(display); //grid

   	glutSpecialFunc(specialKeyboard); //reads right arrow key input
    	glutMouseFunc(mouseClick); //reads left click

	glutMainLoop();
}
