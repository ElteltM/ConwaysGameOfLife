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

int logWidth1=7;
int logHeight1=7;
int logWidth2=194;
int logHeight2=194;
int centerX1 = logWidth1/2, centerY1 = logHeight1/2;
int centerX2 = logWidth2/2, centerY2 = logHeight2/2;
int sqWid=5;
bool sqUp=true;
int sqDelta1=0;
int sqDelta2=500;

bool cells[50][50];
bool newCells[50][50];
int mouseX;
int mouseY;

void Timer(int value) {
    if(value==0){
    glutTimerFunc(700, Timer, value);
    glutPostRedisplay();
    }
}
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
    if(x ==0)
    gluOrtho2D(0.0,100.0,0.0,100.0);
    else
        gluOrtho2D(0.0,9.99,0.0,10.9);

}

void drawSquare_up(){
        glColor3f(1.0f, 1.0f, 1.0f);
        for (int i=0; i<1000 ;i+=6)
        {
            glBegin(GL_POLYGON); // Each set of 4 vertices form a quad
            glVertex2f(centerX1-sqWid/2, centerY1-sqWid/2+sqDelta1-i); // x, y
            glVertex2f(centerX1+sqWid/2, centerY1-sqWid/2+sqDelta1-i); // x, y
            glVertex2f(centerX1+sqWid/2, centerY1+sqWid/2+sqDelta1-i); // x, y
            glVertex2f(centerX1-sqWid/2, centerY1+sqWid/2+sqDelta1-i); // x, y
            glEnd();
            sqDelta1+=1;
        }
}

void drawSquare_down(){
        glColor3f(1.0f, 1.0f, 1.0f);
        for (int i=0; i<1000 ;i+=6)
        {
            glBegin(GL_POLYGON); // Each set of 4 vertices form a quad
            glVertex2f(centerX2-sqWid/2, centerY2-sqWid/2-sqDelta2-i); // x, y
            glVertex2f(centerX2+sqWid/2, centerY2-sqWid/2-sqDelta2-i); // x, y
            glVertex2f(centerX2+sqWid/2, centerY2+sqWid/2-sqDelta2-i); // x, y
            glVertex2f(centerX2-sqWid/2, centerY2+sqWid/2-sqDelta2-i); // x, y
            glEnd();
            sqDelta2-=1;
        }
}

void menuDisplay(){
        glClear(GL_COLOR_BUFFER_BIT);
        printtext("Conway's Game Of Life",30,75);
//--------------------------------------------------------
        glColor3f(0.419, 0.184, 0.976); //Set Color for objects to be drawn later to wanted color
        glBegin(GL_QUADS);
            glVertex2i(38,47);
            glVertex2i(38,55);
            glVertex2i(55,55);
            glVertex2i(55,47);
        glEnd();
        glColor3f(1,1,1); //Set Color for objects to be drawn later to wanted color
        glBegin(GL_QUADS);
            glVertex2i(39,48);
            glVertex2i(39,54);
            glVertex2i(54,54);
            glVertex2i(54,48);
        glEnd();

        glColor3f(0.231, 0.325, 0.870);
        printtext("Play",44,50);

//-----------------------------------------------------------------
        glColor3f(0.419, 0.184, 0.976); //Set Color for objects to be drawn later to wanted color
        glBegin(GL_QUADS);
            glVertex2i(38,22);
            glVertex2i(38,30);
            glVertex2i(55,30);
            glVertex2i(55,22);
        glEnd();
        glColor3f(1,1,1); //Set Color for objects to be drawn later to wanted color
        glBegin(GL_QUADS);
            glVertex2i(39,23);
            glVertex2i(39,29);
            glVertex2i(54,29);
            glVertex2i(54,23);
        glEnd();


    glColor3f(0.231, 0.325, 0.870);

    printtext("Exit",44,25);

    drawSquare_up();
    drawSquare_down();

    glutSwapBuffers();
    glFlush();
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

void mouseClickMenu(int btn, int state, int x, int y)
{
    //left mouse click to change cell state
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN) {
        mouseX = x;
        mouseX=0.5+1.0*mouseX;
        mouseY = window_height - y;
        mouseY=0.5+1.0*mouseY;
        printf("%d %d\n", mouseX/10, mouseY/10);
        if (mouseX/10>19 && mouseX/10 <27 && mouseY/10>26 && mouseY/10<29){
            logWidth=500.0;
            logHeight=550.0;
            backgrundFunc(1, 1, 1, 1);
            glutDisplayFunc(display); //grid
            glutIdleFunc(display);
            glutSpecialFunc(specialKeyboard);//reads right key input
            glutMouseFunc(mouseClick); //reads left click
            glutMainLoop();
        }
        if (mouseX/10>19 && mouseX/10 <27 && mouseY/10>12 && mouseY/10<16){
            exit(0);
        }
    glutPostRedisplay();
    }

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


	glutDisplayFunc(menuDisplay); //grid

    //glutSpecialFunc(specialKeyboard);//reads right key input
    glutMouseFunc(mouseClickMenu); //reads left click
    Timer(0);

	glutMainLoop();
}