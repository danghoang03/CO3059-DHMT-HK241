#include <windows.h>
#include <math.h>
#include <gl\glut.h>
#include <algorithm>

const int screenWidth = 650;
const int screenHeight = 650;
GLfloat mat_ambient[]={0.2f, 0.2f, 0.2f, 1.0f};
GLfloat mat_diffuse[]={1.0f, 0.0f, 0.0f, 1.0f};
GLfloat mat_specular[]={1.0f, 1.0f, 1.0f, 1.0f};
GLfloat mat_shininess[] = {50.0f};

void init(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.2, 1.2, -1.2, 1.2, 0.1, 100);
}
void setLight(){
    GLfloat lightAmbient[]={0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat lightDiffuse[]={0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat lightSpecular[]={1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_position[]={2, 1, 2, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
}
void setMaterial(){
    glMaterialfv(GL_FRONT,GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT,GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT,GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}
void setCamera(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(2, 1, 2, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void drawAxis(){
    glDisable(GL_LIGHTING);
    float xmax = 1.0, ymax = 1.0, zmax = 1.0;
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(-xmax, 0, 0);
    glVertex3f(xmax, 0, 0);
    glVertex3f(0, -ymax, 0);
    glVertex3f(0, ymax, 0);
    glVertex3f(0, 0, -zmax);
    glVertex3f(0, 0, zmax);
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    void * font = GLUT_BITMAP_TIMES_ROMAN_24;
    glRasterPos3f(1.0, 0, 0);
    glutBitmapCharacter(font, 'X');
    glRasterPos3f(0, 1.0, 0);
    glutBitmapCharacter(font, 'Y');
    glRasterPos3f(0, 0, 1.0);
    glutBitmapCharacter(font, 'Z');
}
void display()
{
    glClearColor(1.0,1.0,1.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    setCamera();
    drawAxis();
    setLight();
    setMaterial();
    glutSolidTeapot(0.5);
    glFlush();
}
void myKeyboard(unsigned char key, int x, int y){
    if(key == '1'){
        GLfloat new_mat_ambient[]={0.0f, 0.0f, 0.0f, 1.0f};
        GLfloat new_mat_diffuse[]={0.01f, 0.01f, 0.01f, 1.0f};
        GLfloat new_mat_specular[]={0.5f, 0.5f, 0.5f, 1.0f};
        mat_shininess[0] = 32.0f;
        std::copy(new_mat_ambient, new_mat_ambient + 4, mat_ambient);
        std::copy(new_mat_diffuse, new_mat_diffuse + 4, mat_diffuse);
        std::copy(new_mat_specular, new_mat_specular + 4, mat_specular);
    }
    else if (key == '2'){
        GLfloat new_mat_ambient[]= {0.329412f, 0.223529f, 0.027451f, 1.0f};
        GLfloat new_mat_diffuse[]={0.780392f, 0.568627f, 0.113725f, 1.0f};
        GLfloat new_mat_specular[]={0.992157f, 0.941176f, 0.807843f, 1.0f};
        mat_shininess[0] = 27.8974f;
        std::copy(new_mat_ambient, new_mat_ambient + 4, mat_ambient);
        std::copy(new_mat_diffuse, new_mat_diffuse + 4, mat_diffuse);
        std::copy(new_mat_specular, new_mat_specular + 4, mat_specular);
    }
    else if (key == '3'){
        GLfloat new_mat_ambient[]= {0.2125f, 0.01275f, 0.027451f, 1.0f};
        GLfloat new_mat_diffuse[]={0.714f, 0.4284f, 0.18144f, 1.0f};
        GLfloat new_mat_specular[]={0.393548f, 0.271906f, 0.166721f, 1.0f};
        mat_shininess[0] = 25.6f;
        std::copy(new_mat_ambient, new_mat_ambient + 4, mat_ambient);
        std::copy(new_mat_diffuse, new_mat_diffuse + 4, mat_diffuse);
        std::copy(new_mat_specular, new_mat_specular + 4, mat_specular);
    }
    if(key == '4'){
        GLfloat new_mat_ambient[]={0.25f, 0.25f, 0.25f, 1.0f};
        GLfloat new_mat_diffuse[]={0.4f, 0.4f, 0.4f, 1.0f};
        GLfloat new_mat_specular[]={0.774597f, 0.774597f, 0.774597f, 1.0f};
        mat_shininess[0] = 76.8f;
        std::copy(new_mat_ambient, new_mat_ambient + 4, mat_ambient);
        std::copy(new_mat_diffuse, new_mat_diffuse + 4, mat_diffuse);
        std::copy(new_mat_specular, new_mat_specular + 4, mat_specular);
    }
    if(key == '5'){
        GLfloat new_mat_ambient[]={0.19125f, 0.0735f, 0.025f, 1.0f};
        GLfloat new_mat_diffuse[]={0.7038f, 0.27048f, 0.0828f, 1.0f};
        GLfloat new_mat_specular[]={0.256777f, 0.137622f, 0.086014f, 1.0f};
        mat_shininess[0] = 12.8f;
        std::copy(new_mat_ambient, new_mat_ambient + 4, mat_ambient);
        std::copy(new_mat_diffuse, new_mat_diffuse + 4, mat_diffuse);
        std::copy(new_mat_specular, new_mat_specular + 4, mat_specular);
    }
    if(key == '6'){
        GLfloat new_mat_ambient[]={0.24725f, 0.1995f, 0.0745f, 1.0f};
        GLfloat new_mat_diffuse[]={0.75164f, 0.60648f, 0.22648f, 1.0f};
        GLfloat new_mat_specular[]={0.628281f, 0.555802f, 0.366065f, 1.0f};
        mat_shininess[0] = 51.2f;
        std::copy(new_mat_ambient, new_mat_ambient + 4, mat_ambient);
        std::copy(new_mat_diffuse, new_mat_diffuse + 4, mat_diffuse);
        std::copy(new_mat_specular, new_mat_specular + 4, mat_specular);
    }
    if(key == '7'){
        GLfloat new_mat_ambient[]={0.10588f, 0.058824f, 0.113725f, 1.0f};
        GLfloat new_mat_diffuse[]={0.427451f, 0.470588f, 0.541176f, 1.0f};
        GLfloat new_mat_specular[]={0.3333f, 0.3333f, 0.521569f, 1.0f};
        mat_shininess[0] = 9.84615f;
        std::copy(new_mat_ambient, new_mat_ambient + 4, mat_ambient);
        std::copy(new_mat_diffuse, new_mat_diffuse + 4, mat_diffuse);
        std::copy(new_mat_specular, new_mat_specular + 4, mat_specular);
    }
    if(key == '8'){
        GLfloat new_mat_ambient[]={0.19225f, 0.19225f, 0.19225f, 1.0f};
        GLfloat new_mat_diffuse[]={0.50754f, 0.50754f, 0.50754f, 1.0f};
        GLfloat new_mat_specular[]={0.508273f, 0.508273f, 0.508273f, 1.0f};
        mat_shininess[0] = 51.2f;
        std::copy(new_mat_ambient, new_mat_ambient + 4, mat_ambient);
        std::copy(new_mat_diffuse, new_mat_diffuse + 4, mat_diffuse);
        std::copy(new_mat_specular, new_mat_specular + 4, mat_specular);
    }
    if(key == '9'){
        GLfloat new_mat_ambient[]={0.23125f, 0.23125f, 0.23125f, 1.0f};
        GLfloat new_mat_diffuse[]={0.2775f, 0.2775f, 0.2775f, 1.0f};
        GLfloat new_mat_specular[]={0.773911f, 0.773911f, 0.773911f, 1.0f};
        mat_shininess[0] = 89.6f;
        std::copy(new_mat_ambient, new_mat_ambient + 4, mat_ambient);
        std::copy(new_mat_diffuse, new_mat_diffuse + 4, mat_diffuse);
        std::copy(new_mat_specular, new_mat_specular + 4, mat_specular);
    }


    glutPostRedisplay();
}
int main(int argc, _TCHAR* argv[])
{
    glutInit(&argc, (char**)argv); //initialize the tool kit
    glutInitDisplayMode(GLUT_SINGLE |GLUT_RGB |GLUT_DEPTH);//set the display mode
    glutInitWindowSize(screenWidth, screenHeight); //set window size
    glutInitWindowPosition(0, 0); // set window position on screen
    glutCreateWindow("Hoàng Minh Hải Đăng - 2110120"); // open the screen window
    glutKeyboardFunc(myKeyboard);
    glutDisplayFunc(display);
    init();
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
