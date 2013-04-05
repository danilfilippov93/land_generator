#include <GL/glut.h>

void draw(void) {

    // Black background
    glClearColor(0.2f,0.2f,0.2f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glRotatef(6,2,3,1);
    glBegin(GL_QUADS);
    glColor3f(1,0,0);
    glVertex3f(-50,-50,-50);
    glVertex3f(50,-50,-50);
    glVertex3f(50,50,-50);
    glVertex3f(-50,50,-50);
    glVertex3f(-50,-50,-50);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1,1,0);
    glVertex3f(-50,-50,50);
    glVertex3f(50,-50,50);
    glVertex3f(50,50,50);
    glVertex3f(-50,50,50);
    glVertex3f(-50,-50,50);
    glEnd();

    glBegin(GL_LINES);
    glColor3f(0,0,0);
    glVertex3f(-50,-50,50);
    glVertex3f(-50,-50,-50);
    glVertex3f(50,-50,50);
    glVertex3f(50,-50,-50);
    glVertex3f(50,50,50);
    glVertex3f(50,50,-50);
    glVertex3f(-50,50,50);
    glVertex3f(-50,50,-50);
    glEnd();

    glutSwapBuffers();
    glFlush();

}

void timer(int a){
	draw();
	glutTimerFunc(10,timer,a);
}
//Main program

int main(int argc, char **argv) {

    glutInit(&argc, argv);

    /*Setting up  The Display
    /    -RGB color model + Alpha Channel = GLUT_RGBA
    */
    glutInitDisplayMode(GLUT_RGBA|GLUT_SINGLE);

    //Configure Window Postion
    glutInitWindowPosition(50, 25);

    //Configure Window Size
    glutInitWindowSize(480,480);

    //Create Window
    glutCreateWindow("Cube");

    glClearColor(0, 0, 0.2f, 1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100,100,-100,100,-100,100);


    //Call to the drawing function
    glutDisplayFunc(draw);
    timer(0);
    // Loop require by OpenGL
    glutMainLoop();
    return 0;
}