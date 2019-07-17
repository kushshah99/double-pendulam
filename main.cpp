#include<windows.h>
#include<GL/glut.h>
#include<GL/gl.h>
#include<math.h>
#include<stdio.h>
#define PI 3.141592653
int width = 1000, height = 750;
float r1=40, r2=20, g=1, len1=200, len2=400, i, theta1=(100*PI)/180, theta2=(130*PI)/180, X1, Y1, X2, Y2;
float a1,a2,w1=0,w2=0;
void drawline(float x1, float ye, float x2, float y2)
{

    glColor3f(0.5,0.5,1);
    glBegin(GL_LINES);
    glVertex2f(x1,ye);
    glVertex2f(x2,y2);
    glEnd();
}
void drawcircle(float x, float y, float r)
{

    glColor3f(0.5,0.5,1);
    glBegin(GL_LINES);
     for(i=0;i<=2*PI;i+=0.0001)
    {
        glVertex2f(x,y);
        glVertex2f(x+r*cos(i),y+r*sin(i));
    }
    glEnd();
}
void drawSystem(float theta1,float theta2)
{
    glTranslatef(0,200,0);

    X1 = len1*sin(theta1);
    Y1 = -len1*cos(theta1);
    X2 = X1 + len2*sin(theta2);
    Y2 = Y1 - len2*cos(theta2);
    glColor3f(0,0,0);
    glPointSize(3);
    glBegin(GL_POINTS);
    glVertex2i(0,0);
    glEnd();
    drawline(0,0,X1,Y1);
    drawcircle(X1,Y1,r1);
    drawline(X1,Y1,X2,Y2);
    drawcircle(X2,Y2,r2);
    glTranslatef(0,-200,0);
}
void display()
{

    glClear(GL_COLOR_BUFFER_BIT);

    float n1 = -g*(2*r1+r2)*sin(theta1);
    float n2 = -g*r2*sin(theta1-2*theta2);
    float n3 = -2*r2*sin(theta1-theta2);
    float n4 = (w2*w2*len2) + (w1*w1*len1*cos(theta1-theta2));
    float d = len1 * (2*r1 + r2*(1-cos(2*(theta1-theta2))));
    a1=(n1+n2+n3*n4)/d;

    n1=2*sin(theta1-theta2);
    n2=w1*w1*len1*(r1+r2);
    n3=g*cos(theta1)*(r1+r2);
    n4=w2*w2*len2*r2*cos(theta1-theta2);
    d = len2 * (2*r1 + r2*(1-cos(2*(theta1-theta2))));


    a2=(n1*(n2+n3+n4))/d;
    w1+=a1;
    w2+=a2;

    theta1+=w1;
    theta2+=w2;
    drawSystem(theta1,theta2);
    printf("a2=%f w2=%f theta2=%f \n",a2,w2,theta2);

    glFlush();
    glutPostRedisplay();



}

void init(float r, float g, float b)
{
    glClearColor(r,g,b,1);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-width,width,-height,height);
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Ball");
    init(0,0,0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
