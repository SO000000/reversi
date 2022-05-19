#include <stdlib.h>
/* mac用 */
#include <GLUT/glut.h>
#include <OpenGL/glu.h>
// windows用 #include <GL/glut.h>

int winw, winh; // ウィンドウサイズ用の変数
int board[8][8]; // 盤面用の変数  

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
    gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    Board();
    glutSwapBuffers();
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
    glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}