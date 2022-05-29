#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// ---------mac用----------
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
// ------------------------

// -------windows用 -------
// #include <GL/glut.h>
// #include <GL/glu.h>
// ------------------------

int winw, winh;
int board[8][8]; // 盤面用の変数

// カメラの位置と注視点の変数
double EYE_X = 0.0;
double EYE_Y = 0.0;
double EYE_Z = 10.0;

const double TARGET_X = 0.0;
const double TARGET_Y = 0.0;
const double TARGET_Z = 0.0;

double UP_X = 0.0;
double UP_Y = 1.0;
double UP_Z = 0.0;

// 盤面の描画
void Board()
{
    float board[2][4] = {
        {1.0f, 1.0f, 1.0f, 1.0f},
        {0.3f, 0.3f, 0.3f, 1.0f}};
    int i, j;
    int x, y;
    glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, 1.0);
    // 1×1の正方形を8×8描画
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            y = i - 4;
            x = j - 4;
            // i + j　が偶数の時に白，奇数の時に黒を描画
            glMaterialfv(GL_FRONT, GL_DIFFUSE, board[abs(i + j) % 2]);
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
    // 石の色
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
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
        UP_X, UP_Y, UP_Z);
    Board();

    int i, j;
    double posy, posx;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (board[i][j] != 0)
            {
                posy = (double)i - 4.0 + 0.5;
                posx = (double)j - 4.0 + 0.5;
                glPushMatrix();
                glTranslated(posx, posy, 0.5);
                if (board[i][j] > 0)
                    glMaterialfv(GL_FRONT, GL_DIFFUSE, black);
                else
                    glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
                glutSolidSphere(0.5, 10, 10);
                glPopMatrix();
            }
        }
    }
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT0);
    glutSwapBuffers();
}

void myReshape(int width, int height)
{
    winw = width;
    winh = height;
    glViewport(0, 0, winw, winh);
}

// マウスクリックで石を置く
void myMouse(int button, int state, int x, int y)
{
	printf(" Mouse\n");
	printf("x,y = %d %d\n", x, y);
	printf("button = %d\n", button);
	printf("state = %d\n", state);
    if (x > 205 && x < 280){
        if (y > 130 && y < 205) {
            board[7][0] = 1;
        }
    }
	glutPostRedisplay();
}

// 十字キーで視点移動
void mySkey(int key, int x, int y)
{
    switch (key)
    {
    // ↑で真上からの視点に移動
    case 101:
        EYE_Y += 1.0;
        EYE_Z += 0.5;
        UP_Y = 0.0;
        UP_Z = 1.0;
        glutPostRedisplay();
        break;
    // ↓で正面からの視点に移動
    case 103:
        EYE_Y = -10.0;
        EYE_Z = 5.0;
        glutPostRedisplay();
        break;
    case 'q':
        exit(1);
    default:
        break;
    }
}

void myInit(char *progname)
{
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow(progname);
}

int main(int argc, char *argv[])
{
    board[3][4] = board[4][3] = 1;
    board[3][3] = board[4][4] = -1;
    glutInit(&argc, argv);
    myInit(argv[0]);
    glutReshapeFunc(myReshape);
    glutMouseFunc(myMouse);
    glutSpecialFunc(mySkey);
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}