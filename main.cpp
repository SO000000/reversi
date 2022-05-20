#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// mac用
#include <GLUT/glut.h>
#include <OpenGL/glu.h>

// -------windows用 -------
// #include <GL/glut.h>
// #include <GL/glu.h>
// ------------------------

int winw, winh;
int board[8][8]; // 盤面用の変数  

// カメラの位置と注視点の変数
double EYE_X = 0.0;
double EYE_Y = -10.0;
double EYE_Z = 5.0;

const double TARGET_X = 0.0;
const double TARGET_Y = 0.0;
const double TARGET_Z = 0.0;

const double UP_X = 0.0;
const double UP_Y = 1.0;
const double UP_Z = 0.0;

// 盤面の描画
void Board()
{
    float ground[2][4] = {
        {0.6f, 0.6f, 0.6f, 1.0f},
        {0.3f, 0.3f, 0.3f, 1.0f}};
    int i, j;
    int x, y;
    // 1×1の正方形を8×8で描画
    glBegin(GL_QUADS);
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            y = i - 4;
            x = j - 4;
            glMaterialfv(GL_FRONT, GL_DIFFUSE, ground[abs(i + j) % 2]);
            glVertex3d((double)x, (double)y, 0.0);
            glVertex3d((double)(x + 1), (double)y, 0.0);
            glVertex3d((double)(x + 1), (double)(y + 1), 0.0);
            glVertex3d((double)x, (double)(y + 1), 0.0);
        }
    }
    glEnd();
}

void Display()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (double)winw / (double)winh, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        EYE_X, EYE_Y, EYE_Z, 
        TARGET_X, TARGET_Y, TARGET_Z,
        UP_X, UP_Y, UP_Z
    );
    Board();
    glutSwapBuffers();
}

// 十字キーで視点移動
void mySkey(int key, int x , int y)
{
    switch(key){
        // ↑で真上からの視点に移動
        case 101:
            EYE_Y = 0.0;
            EYE_Z = 10.0;
            break;
        // ↓で正面からの視点に移動
        case 103:
            EYE_Y = -10.0;
            EYE_Z = 5.0;
            break;
        default:
            break;
    }
	glutPostRedisplay();
}

void myReshape(int width, int height)
{
    winw = width;
    winh = height;
    glViewport(0, 0, winw, winh);
}

void myInit(char *progname)
{
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(progname);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    myInit(argv[0]);
    glutReshapeFunc(myReshape);
    glutSpecialFunc(mySkey);
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}