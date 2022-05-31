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
int board[8][8];    // 盤面用の変数
int turn_count = 1; // ターン数用の変数

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
    float board_color[2][4] = {
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
            glMaterialfv(GL_FRONT, GL_DIFFUSE, board_color[abs(i + j) % 2]);
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
    int i, j, k;
    if (board[7 - (y - 130) / 75][(x - 205) / 75] == 0)
    {
        if (turn_count % 2 == 0)
        {
            board[7 - (y - 130) / 75][(x - 205) / 75] = 1;
        }
        else
        {
            board[7 - (y - 130) / 75][(x - 205) / 75] = -1;
        }
        // 石をひっくり返す処理
        for (i = -1; i <= 1; i++)
        {
            for (j = -1; j <= 1; j++)
            {
                if (board[7 - (y - 130) / 75 + i][(x - 205) / 75 + j] != board[7 - (y - 130) / 75][(x - 205) / 75] && board[7 - (y - 130) / 75 + i][(x - 205) / 75 + j] != 0)
                {
                    for (k = 2; k < 8; k++)
                    {
                        if (board[7 - (y - 130) / 75 + k * i][(x - 205) / 75 + k * j] == board[7 - (y - 130) / 75][(x - 205) / 75])
                        {
                            board[7 - (y - 130) / 75 + i][(x - 205) / 75 + j] = board[7 - (y - 130) / 75][(x - 205) / 75];
                        }
                    }
                }
            }
        }
        turn_count += 1;
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
    // 初期配置
    if (turn_count == 1)
    {
        board[3][4] = board[4][3] = 1;
        board[3][3] = board[4][4] = -1;
    }
    glutInit(&argc, argv);
    myInit(argv[0]);
    glutReshapeFunc(myReshape);
    glutMouseFunc(myMouse);
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}