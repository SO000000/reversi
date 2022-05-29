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
int turn_count = 1; // 何ターン目か数える変数

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
// いい方法が思いつかなかったからかなり雑
void myMouse(int button, int state, int x, int y)
{
    if ((x - 205) / 75 == 0)
    {
        if ((y - 130) / 75 == 0)
        {
            if (board[7][0] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[7][0] = 1;
                }
                else
                {
                    board[7][0] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 1)
        {
            if (board[6][0] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[6][0] = 1;
                }
                else
                {
                    board[6][0] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 2)
        {
            if (board[5][0] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[5][0] = 1;
                }
                else
                {
                    board[5][0] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 3)
        {
            if (board[4][0] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[4][0] = 1;
                }
                else
                {
                    board[4][0] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 4)
        {
            if (board[3][0] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[3][0] = 1;
                }
                else
                {
                    board[3][0] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 5)
        {
            if (board[2][0] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[2][0] = 1;
                }
                else
                {
                    board[2][0] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 6)
        {
            if (board[1][0] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[1][0] = 1;
                }
                else
                {
                    board[1][0] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 7)
        {
            if (board[0][0] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[0][0] = 1;
                }
                else
                {
                    board[0][0] = -1;
                }
                turn_count += 1;
            }
        }
    }
    else if ((x - 205) / 75 == 1)
    {
        if ((y - 130) / 75 == 0)
        {
            if (board[7][1] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[7][1] = 1;
                }
                else
                {
                    board[7][1] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 1)
        {
            if (board[6][1] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[6][1] = 1;
                }
                else
                {
                    board[6][1] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 2)
        {
            if (board[5][1] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[5][1] = 1;
                }
                else
                {
                    board[5][1] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 3)
        {
            if (board[4][1] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[4][1] = 1;
                }
                else
                {
                    board[4][1] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 4)
        {
            if (board[3][1] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[3][1] = 1;
                }
                else
                {
                    board[3][1] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 5)
        {
            if (board[2][1] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[2][1] = 1;
                }
                else
                {
                    board[2][1] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 6)
        {
            if (board[1][1] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[1][1] = 1;
                }
                else
                {
                    board[1][1] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 7)
        {
            if (board[0][1] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[0][1] = 1;
                }
                else
                {
                    board[0][1] = -1;
                }
                turn_count += 1;
            }
        }
    }
    else if ((x - 205) / 75 == 2)
    {
        if ((y - 130) / 75 == 0)
        {
            if (board[7][2] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[7][2] = 1;
                }
                else
                {
                    board[7][2] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 1)
        {
            if (board[6][2] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[6][2] = 1;
                }
                else
                {
                    board[6][2] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 2)
        {
            if (board[5][2] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[5][2] = 1;
                }
                else
                {
                    board[5][2] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 3)
        {
            if (board[4][2] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[4][2] = 1;
                }
                else
                {
                    board[4][2] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 4)
        {
            if (board[3][2] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[3][2] = 1;
                }
                else
                {
                    board[3][2] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 5)
        {
            if (board[2][2] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[2][2] = 1;
                }
                else
                {
                    board[2][2] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 6)
        {
            if (board[1][2] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[1][2] = 1;
                }
                else
                {
                    board[1][2] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 7)
        {
            if (board[0][2] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[0][2] = 1;
                }
                else
                {
                    board[0][2] = -1;
                }
                turn_count += 1;
            }
        }
    }
    else if ((x - 205) / 75 == 3)
    {
        if ((y - 130) / 75 == 0)
        {
            if (board[7][3] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[7][3] = 1;
                }
                else
                {
                    board[7][3] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 1)
        {
            if (board[6][3] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[6][3] = 1;
                }
                else
                {
                    board[6][3] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 2)
        {
            if (board[5][3] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[5][3] = 1;
                }
                else
                {
                    board[5][3] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 5)
        {
            if (board[2][3] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[2][3] = 1;
                }
                else
                {
                    board[2][3] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 6)
        {
            if (board[1][3] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[1][3] = 1;
                }
                else
                {
                    board[1][3] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 7)
        {
            if (board[0][3] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[0][3] = 1;
                }
                else
                {
                    board[0][3] = -1;
                }
                turn_count += 1;
            }
        }
    }
    else if ((x - 205) / 75 == 4)
    {
        if ((y - 130) / 75 == 0)
        {
            if (board[7][4] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[7][4] = 1;
                }
                else
                {
                    board[7][4] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 1)
        {
            if (board[6][4] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[6][4] = 1;
                }
                else
                {
                    board[6][4] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 2)
        {
            if (board[5][4] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[5][4] = 1;
                }
                else
                {
                    board[5][4] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 5)
        {
            if (board[2][4] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[2][4] = 1;
                }
                else
                {
                    board[2][4] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 6)
        {
            if (board[1][4] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[1][4] = 1;
                }
                else
                {
                    board[1][4] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 7)
        {
            if (board[0][4] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[0][4] = 1;
                }
                else
                {
                    board[0][4] = -1;
                }
                turn_count += 1;
            }
        }
    }
    else if ((x - 205) / 75 == 5)
    {
        if ((y - 130) / 75 == 0)
        {
            if (board[7][5] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[7][5] = 1;
                }
                else
                {
                    board[7][5] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 1)
        {
            if (board[6][5] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[6][5] = 1;
                }
                else
                {
                    board[6][5] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 2)
        {
            if (board[5][5] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[5][5] = 1;
                }
                else
                {
                    board[5][5] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 3)
        {
            if (board[4][5] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[4][5] = 1;
                }
                else
                {
                    board[4][5] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 4)
        {
            if (board[3][5] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[3][5] = 1;
                }
                else
                {
                    board[3][5] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 5)
        {
            if (board[2][5] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[2][5] = 1;
                }
                else
                {
                    board[2][5] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 6)
        {
            if (board[1][5] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[1][5] = 1;
                }
                else
                {
                    board[1][5] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 7)
        {
            if (board[0][5] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[0][5] = 1;
                }
                else
                {
                    board[0][5] = -1;
                }
                turn_count += 1;
            }
        }
    }
    else if ((x - 205) / 75 == 6)
    {
        if ((y - 130) / 75 == 0)
        {
            if (board[7][6] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[7][6] = 1;
                }
                else
                {
                    board[7][6] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 1)
        {
            if (board[6][6] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[6][6] = 1;
                }
                else
                {
                    board[6][6] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 2)
        {
            if (board[5][6] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[5][6] = 1;
                }
                else
                {
                    board[5][6] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 3)
        {
            if (board[4][6] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[4][6] = 1;
                }
                else
                {
                    board[4][6] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 4)
        {
            if (board[3][6] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[3][6] = 1;
                }
                else
                {
                    board[3][6] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 5)
        {
            if (board[2][6] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[2][6] = 1;
                }
                else
                {
                    board[2][6] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 6)
        {
            if (board[1][6] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[1][6] = 1;
                }
                else
                {
                    board[1][6] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 7)
        {
            if (board[0][6] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[0][6] = 1;
                }
                else
                {
                    board[0][6] = -1;
                }
                turn_count += 1;
            }
        }
    }
    else if ((x - 205) / 75 == 7)
    {
        if ((y - 130) / 75 == 0)
        {
            if (board[7][7] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[7][7] = 1;
                }
                else
                {
                    board[7][7] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 1)
        {
            if (board[6][7] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[6][7] = 1;
                }
                else
                {
                    board[6][7] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 2)
        {
            if (board[5][7] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[5][7] = 1;
                }
                else
                {
                    board[5][7] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 3)
        {
            if (board[4][7] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[4][7] = 1;
                }
                else
                {
                    board[4][7] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 4)
        {
            if (board[3][7] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[3][7] = 1;
                }
                else
                {
                    board[3][7] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 5)
        {
            if (board[2][7] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[2][7] = 1;
                }
                else
                {
                    board[2][7] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 6)
        {
            if (board[1][7] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[1][7] = 1;
                }
                else
                {
                    board[1][7] = -1;
                }
                turn_count += 1;
            }
        }
        else if ((y - 130) / 75 == 7)
        {
            if (board[0][7] == 0)
            {
                if (turn_count % 2 == 0)
                {
                    board[0][7] = 1;
                }
                else
                {
                    board[0][7] = -1;
                }
                turn_count += 1;
            }
        }
    }
    glutPostRedisplay();
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
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}