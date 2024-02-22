#include <gl/glut.h>
#include <string.h>
#include <stdio.h>

// Constantes
#define QUADRADO 1
#define TRIANGULO 2
#define LOSANGO   3

// Variáveis
char texto[30];
GLfloat win, r, g, b;
GLint view_w, view_h, primitiva;
void DesenhaQuadrado(void){// Função que desenha um quadrado
     glBegin(GL_QUADS);
               glVertex2f(-25.0f, -25.0f);
               glVertex2f(-25.0f, 25.0f);
               glVertex2f(25.0f, 25.0f);
               glVertex2f(25.0f, -25.0f);               
     glEnd();
}
void DesenhaTriangulo(void){// Função que desenha um triângulo
     glBegin(GL_TRIANGLES);
               glVertex2f(-25.0f, -25.0f);
               glVertex2f(0.0f, 25.0f);
               glVertex2f(25.0f, -25.0f);              
     glEnd();
}
void DesenhaLosango(void){// Função que desenha um losango
     glBegin(GL_POLYGON);
               glVertex2f(-25.0f, 0.0f);
               glVertex2f(0.0f, 25.0f);
               glVertex2f(25.0f, 0.0f);
               glVertex2f(0.0f, -25.0f);               
     glEnd();
}
void DesenhaTexto(char *string) {// Desenha um texto na janela GLUT  
        glPushMatrix();
        // Posição no universo onde o texto será colocado          
        glRasterPos2f(-win,win-(win*0.08)); 
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,*string++); 
	glPopMatrix();
}
void Desenha(void){ // Função callback chamada para fazer o desenho
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glClear(GL_COLOR_BUFFER_BIT);
     glColor3f(r,g,b); // Define a cor corrente   
     switch (primitiva) {// Desenha uma primitiva 
            case QUADRADO:  DesenhaQuadrado(); break;
            case TRIANGULO: DesenhaTriangulo(); break;
            case LOSANGO:   DesenhaLosango(); break;
     }
     glColor3f(1.0f,1.0f,1.0f); // Exibe a posição do mouse na janela
     DesenhaTexto(texto);
     glutSwapBuffers();
}
void Inicializa (void) {// Inicializa parâmetros de rendering
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    win=150.0f;
    primitiva = QUADRADO;
    r = 0.0f;     g = 0.0f;    b = 1.0f;
    strcpy(texto, "(0,0)");
}
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{ 
    glViewport(0, 0, w, h); // Especifica as dimensões da Viewport
    view_w = w;    view_h = h;                   
    glMatrixMode(GL_PROJECTION); // Inicializa o sistema de coordenadas
    glLoadIdentity();
    gluOrtho2D (-win, win, -win, win);
}
// Função callback chamada sempre que o mouse é movimentado sobre a janela GLUT com um botão pressionado
void MoveMouseBotaoPressionado(int x, int y){
     sprintf(texto, "Botao pressionado (%d,%d)", x, y);
     glutPostRedisplay();
}
// Função callback chamada sempre que o mouse é movimentado sobre a janela GLUT 
void MoveMouse(int x, int y){
     sprintf(texto, "(%d,%d)", x, y);
     glutPostRedisplay();
}
// Função callback chamada para gerenciar eventos do teclado para teclas especiais, tais como F1, PgDn e Home
void TeclasEspeciais(int key, int x, int y){
    if(key == GLUT_KEY_UP) {
           win -= 10;
           if (win < 10) win = 10;
           glMatrixMode(GL_PROJECTION);   glLoadIdentity();
           gluOrtho2D (-win, win, -win, win);
    }
    if(key == GLUT_KEY_DOWN) {
           win += 10;
           if (win > 500) win = 500;
           glMatrixMode(GL_PROJECTION);    glLoadIdentity();
           gluOrtho2D (-win, win, -win, win);
    }
    glutPostRedisplay();
}
// Gerenciamento do menu com as opções de cores           
void MenuCor(int op)
{
   switch(op) {
            case 0:
                     r = 1.0f;  g = 0.0f; b = 0.0f;  break;
            case 1:
                     r = 0.0f;  g = 1.0f; b = 0.0f; break;
            case 2:
                     r = 0.0f;  g = 0.0f; b = 1.0f; break;
    }
    glutPostRedisplay();
} 
void MenuPrimitiva(int op) // Gerenciamento do menu com as opções de cores
{
   switch(op) {
            case 0:
                     primitiva = QUADRADO; break;
            case 1:
                     primitiva = TRIANGULO;  break;
            case 2:
                     primitiva = LOSANGO;  break;
    }
    glutPostRedisplay();
}   
void MenuPrincipal(int op) // Gerenciamento do menu principal           
{
}

void CriaMenu() // Criação do Menu
{
    int menu,submenu1,submenu2;

    submenu1 = glutCreateMenu(MenuCor);
    glutAddMenuEntry("Vermelho",0);
    glutAddMenuEntry("Verde",1);
    glutAddMenuEntry("Azul",2);

    submenu2 = glutCreateMenu(MenuPrimitiva);
    glutAddMenuEntry("Quadrado",0);
    glutAddMenuEntry("Triângulo",1);
    glutAddMenuEntry("Losango",2);

    menu = glutCreateMenu(MenuPrincipal);
    glutAddSubMenu("Cor",submenu1);
    glutAddSubMenu("Primitivas",submenu2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
} 
// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y){        
    if (button == GLUT_RIGHT_BUTTON)
         if (state == GLUT_DOWN)   
		 CriaMenu();
    glutPostRedisplay();
}

// Programa Principal 
int main(void)
{
     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);     
     glutInitWindowSize(350,300);
     glutInitWindowPosition(10,10);
     glutCreateWindow("Exemplo de Menu e Exibição de Caracteres");
     glutDisplayFunc(Desenha);
     glutReshapeFunc(AlteraTamanhoJanela);
     glutMotionFunc(MoveMouseBotaoPressionado); 
     glutPassiveMotionFunc(MoveMouse);
     glutMouseFunc(GerenciaMouse);    
     glutSpecialFunc(TeclasEspeciais); 
     Inicializa();
     glutMainLoop();
} 

