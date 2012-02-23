/********************************************************************
* Universidad Nacional Mayor de San Marcos
* Facultad de Ingenieria de Sistemas
* Curso Computacion Grafica
* 2do Examen de Laboratorio
* Alumno: Quispe Aracayo Jose Luis
* Codigo: 06200153
* IDE: DevC++ v4.9.9.2
********************************************************************
* EL  PROBLEMA  SOLO  FUNCIONA  ACTIVANDO  LA  TECLA  DE  MAYUSCULA,
* PRESIONANDO LA TECLA ADECUADA o ELIGIENDO UNA OPCION DEL MENU
********************************************************************/
#define ON true
#define OFF false

#define HORARIO 1
#define ANTIHORARIO 0

#define ALAMBRICO 1
#define PLANO 0

#define LENTO 2
#define NORMAL 4
#define RAPIDO 11

#define PASO 0.2 // Avanza o retrocede
#define ANGULO 5 // se gira un cierto angulo
#define ALTURA 0.2 // cuando se sube o se baja

#define ACERC_ALEJ 0.2

#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
using namespace std;
struct Color{
  int ROJO;
  int VERDE;
  int AZUL;
};
//------------Variables Zoom
bool Zoom=OFF;
float ZoomAumentDismin=1;
//------------Variables Base
int Grid=ALAMBRICO;
Color Base;
//------------Variables Molino
int Giro=HORARIO;
float angMolino=0;
Color Molino;
//------------Variables Helicoptero
bool HMovAspa=ON;
float angAspa=0;
Color HAspa;
Color HCabina;
int HVelocidadAspa=NORMAL;
float Adelante=0;

float adelanteAtras=0;
float IzqDer=0;
float giraIzqDer=0;
float ArribaAbajo=0;
//Declaracion de Funciones
void dibujarMolino();
void dibujarElicoptero();
void DibujarTerreno();
void dibujarElicoptero();
void dibujarMolino();
void InicializarVariables();
void menuPartesColor(int opc);
void Menus();
void teclado(unsigned char key, int x, int y);
void EventosPrincipales(int opc);

//funciones de opengl
void reshape (int w, int h);
void display(void) ;
void ejes();
void dibujo();
void teclado(unsigned char key, int x, int y);
void EventosPrincipales(int opc);
void Menus();


void display(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    dibujo();
    glutSwapBuffers();
}
void update(int value)
{
    //Vemos el helice del Molino
    if(Giro==HORARIO)
    {
        angMolino -= 2.0f;
    	if (angMolino <-360) {
    		angMolino += 360;
    	}    	
    }
    else
    {
        angMolino += 2.0f;
    	if (angMolino > 360) {
    		angMolino -= 360;
    	}    	
    }
    //Vemos el Helice del Helicoptero
    if(HMovAspa==OFF)
    {
       angAspa=0;
    }
    else
    {
        angAspa += HVelocidadAspa;
   	    if (angAspa > 360) {
    		angAspa -= 360;
    	}
    }  
	
	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}
void dibujarElicoptero()
{
    //Cuerpo
    glPushMatrix();
    glColor3f(HCabina.ROJO,HCabina.VERDE,HCabina.AZUL );
    glTranslatef(1,0,0);
    glScalef(0.2,0.1, 0.2);     
    glutWireDodecahedron();
    //glutWireDodecahedron();
    glPopMatrix();
    //Cola
    glPushMatrix();
    glColor3f(HCabina.ROJO,HCabina.VERDE,HCabina.AZUL );
    glTranslatef(1.5,0.1,0.1);
    glScalef(2.8/1.5,0.4/1.5, 1/1.5);     
    //glutWireCube(0.2); 
    glutWireCube(0.2);
    glPopMatrix();
    
    //Helice
    glPushMatrix();
    glColor3f(HAspa.ROJO,HAspa.VERDE,HAspa.AZUL );
    glTranslatef(1,0.158,0);
    glRotatef(angAspa,0,1,0);
    glScalef(0.2,0.1, 4);         
    glutWireCube(0.2);
    glPopMatrix();
    
    //Rotor en la cola
    glPushMatrix();
    glColor3f(HAspa.ROJO,HAspa.VERDE,HAspa.AZUL );
    glTranslatef(1.6,0.1,0.1);
    glRotatef(-90,0,1,0);
    glRotatef(angAspa,1,0,0);
    glScalef(0.15,0.05, 1);        
    glutWireCube(0.2);
    glPopMatrix();          
}
void dibujarMolino()
{
    //Creacion de la Base del Molino
    glPushMatrix();
    glColor3f(1.0,0.0,0.0);
    glRotatef(-90,1,0,0);
    glutWireCone(0.2,1, 6, 10);
    glPopMatrix();
    
    //Creacion del Helice del Molino
    glPushMatrix();
    glTranslatef(0,1,0);
    glRotatef(angMolino,1,0,0);
    glScalef(0.1,0.1, 4);     
    glutWireCube(0.2); 
    glPopMatrix();
    //Segundo rotor
    glPushMatrix();
    glTranslatef(0,1,0);
    glRotatef(angMolino+90,1,0,0);
    glScalef(0.1,0.1, 4);     
    glutWireCube(0.2); 
    glPopMatrix();

        
}
void dibujo(){ //Dibujo de los Objetos        
    DibujarTerreno();
    glPushMatrix();//Ahora Simulo una Ampliacion o Disminucion
        glScalef(ZoomAumentDismin,ZoomAumentDismin,ZoomAumentDismin);
        dibujarMolino();
        glPushMatrix();
            glRotatef(giraIzqDer,0,1,0);//Giro 
            glTranslatef(adelanteAtras,ArribaAbajo,IzqDer);//Avanzo, Subo o Retrocedo
            dibujarElicoptero();
        glPopMatrix();
    glPopMatrix();
     
}
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)height / (GLfloat)width, 1.0, 128.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    float z=3;
    gluLookAt (7.0/z, 5.0/z, 10.0/z, 0.0, 0.0, 0.0, 0.0, 1.0/z, 0);//Cambio la ubicacion de la camara
    glViewport(0,0,800, 800);
}
void DibujarTerreno(){ //Ahora DIbujo el Piso, una cuadricula 1 For
int D=20; //Limite del PISO 
    if(Grid==ALAMBRICO){       
        glBegin(GL_LINES);
        glColor3f(Base.ROJO,Base.VERDE,Base.AZUL);
                                
        for(int i=0;i<=D;i++){
           glVertex3f(-D,0,i);
           glVertex3f(D,0,i);   
             
           glVertex3f(-D,0 ,-i);
           glVertex3f(D,0 ,-i);
           
           glVertex3f(i,0 ,D);
           glVertex3f(i,0 ,-D);
           
           glVertex3f(-i,0 ,D);
           glVertex3f(-i,0 ,-D);                           
           }
        glEnd();
       
    }else{
          //Dibujo de un plano
        glBegin(GL_POLYGON);
        glColor3f(Base.ROJO,Base.VERDE,Base.AZUL);                        
        glVertex3f(-D,0,D);
        glVertex3f(-D,0,-D);   
             
        glVertex3f(D,0,-D);   
        glVertex3f(D,0 ,D);       
        glEnd();
        
    }  

}
void EventosPrincipales(int opc){
     switch(opc){  
/*******************   Zomm  ********************/                   
         case   0: //Movimiento Activado
                Zoom=ON;
                break;
         case   1: //Movimiento Desactivado
                Zoom=OFF;
                break;
/******************     Base  *******************/
//Grid:                            
         case   2: //Plano
                Grid=PLANO;
                break;
         case   3: //Alambrico
                Grid=ALAMBRICO;
                break; 
//Color
         case   4: //Rojo
                Base.ROJO=1;
                Base.VERDE=0;
                Base.AZUL=0;
                break;                         
         case   5: //Verde
                Base.ROJO=0;
                Base.VERDE=1;
                Base.AZUL=0;
                break;
         case   6: //Azul
                Base.ROJO=0;
                Base.VERDE=0;
                Base.AZUL=1;
                break; 
/******************     Molino  **********************/
//Giro
         case   7: //Horario
                Giro=HORARIO;
                break;
         case   8: //Antihorario
                Giro=ANTIHORARIO;
                break;
//Color                
         case   9: //Rojo
                Molino.ROJO=1;
                Molino.VERDE=0;
                Molino.AZUL=0;
                break; 
         case   10: //Verde
                Molino.ROJO=0;
                Molino.VERDE=1;
                Molino.AZUL=0;
                break; 
         case   11: //Azul
                Molino.ROJO=0;
                Molino.VERDE=0;
                Molino.AZUL=1;
                break;
/******************     Helicoptero  ********************/
//Movimiento de Aspa
         case   12: 
                HMovAspa=ON;
                break;
         case   13: 
                HMovAspa=OFF;
                break;
//Color Aspa                
         case   14: //Color Rojo
                HAspa.ROJO=1;
                HAspa.VERDE=0;
                HAspa.AZUL=0;
                break;
         case   15: //Color Verde
                HAspa.ROJO=0;
                HAspa.VERDE=1;
                HAspa.AZUL=0;
                break;
         case   16: //Color Azul
                HAspa.ROJO=0;
                HAspa.VERDE=0;
                HAspa.AZUL=1;
                break;
//Color Cabina                
         case   17: //Color Rojo
                HCabina.ROJO=1;
                HCabina.VERDE=0;
                HCabina.AZUL=0;                
                break;
         case   18: //Color Verde
                HCabina.ROJO=0;
                HCabina.VERDE=1;
                HCabina.AZUL=0;
                break;                                                                                                
         case   19: //Color Azul
                HCabina.ROJO=0;
                HCabina.VERDE=0;
                HCabina.AZUL=1;
                break;
//Velocidad de Aspa 
//Lento                            
         case   20: 
                HVelocidadAspa=LENTO;
                break;
//Normal                
         case   21: 
                HVelocidadAspa=NORMAL;
                break;
//Rapido                
         case   22: 
                HVelocidadAspa=RAPIDO;
                break;
         case   23: 
                exit(0);
                break;                         
     } 
     glutPostRedisplay();        
}
void Menus(){//Creacion de los Menus
    int SubMenuZoom= glutCreateMenu(EventosPrincipales);
    glutAddMenuEntry("On",0);
    glutAddMenuEntry("Off",1);
    
    int SubMenuBaseGrid= glutCreateMenu(EventosPrincipales);
    glutAddMenuEntry("Plano",2);
    glutAddMenuEntry("Alambrico",3);
    
    int SubMenuBaseColor= glutCreateMenu(EventosPrincipales);
    glutAddMenuEntry("Rojo",4);
    glutAddMenuEntry("Verde",5);
    glutAddMenuEntry("Azul",6);
    
    int SubMenuBase= glutCreateMenu(EventosPrincipales);
    glutAddSubMenu("Grid",SubMenuBaseGrid);
    glutAddSubMenu("Color",SubMenuBaseColor);
    //--
    int SubMenuMolinoGiro= glutCreateMenu(EventosPrincipales);
    glutAddMenuEntry("Horario",7);
    glutAddMenuEntry("Antihorario",8);
    
    int SubMenuMolinoColor= glutCreateMenu(EventosPrincipales);
    glutAddMenuEntry("Rojo",9);
    glutAddMenuEntry("Verde",10);
    glutAddMenuEntry("Azul",11);
    
    int SubMenuMolino= glutCreateMenu(EventosPrincipales);
    glutAddSubMenu("Giro",SubMenuMolinoGiro);
    glutAddSubMenu("Color",SubMenuMolinoColor);
    
    //
    int SubMenuMovAspa= glutCreateMenu(EventosPrincipales);
    glutAddMenuEntry("On",12);
    glutAddMenuEntry("Off",13);
    
    int SubmenuColorAspa= glutCreateMenu(EventosPrincipales); 
        glutAddMenuEntry("Rojo",14);
        glutAddMenuEntry("Verde",15);
        glutAddMenuEntry("Azul",16);
        
     int SubmenuColorCabina= glutCreateMenu(EventosPrincipales); 
        glutAddMenuEntry("Rojo",17);
        glutAddMenuEntry("Verde",18);
        glutAddMenuEntry("Azul",19);   
    
    int SubmenuVelocidadAspa= glutCreateMenu(EventosPrincipales); 
        glutAddMenuEntry("Lento",20);
        glutAddMenuEntry("Normal",21);
        glutAddMenuEntry("Rapido",22);
        
    
    int SubmenuHelicoptero= glutCreateMenu(EventosPrincipales);
    glutAddSubMenu("Movimiento Aspa",SubMenuMovAspa); 
    glutAddSubMenu("Color Aspa",SubmenuColorAspa);
    glutAddSubMenu("Color Cabina",SubmenuColorCabina);
    glutAddSubMenu("Velocidad de Aspas",SubmenuVelocidadAspa);
    
    
    glutCreateMenu(EventosPrincipales);
    glutAddSubMenu("Zoom",SubMenuZoom);
    glutAddSubMenu("Base",SubMenuBase);
    glutAddSubMenu("Molino",SubMenuMolino);
    glutAddSubMenu("Helicoptero",SubmenuHelicoptero);
    glutAddMenuEntry("Salir",23);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void teclado(unsigned char key, int x, int y){
    switch (key){              
        case 'W': //W: Hacia adelante
             adelanteAtras=adelanteAtras-PASO;
        break;                
        case 'X':  //X: Hacia Atras
             adelanteAtras=adelanteAtras+PASO;
        break;                           
        case 'A':  //A: Hacia la Izquierda, No gira
             IzqDer=IzqDer+PASO;
        break;   
        case 'D':  //D:Hacia la derecha, No gira
             IzqDer=IzqDer-PASO;            
        break;
//------------------------------------------------------------                
        case 'J': //J: Gira hacia la Izquierda
             giraIzqDer=giraIzqDer-ANGULO;             
        break;   
        case 'K':  //K:Gira haciala derecha
             giraIzqDer=giraIzqDer+ANGULO;              
        break;
        case 'I': //L: Gira Hacia Arriba, (Levanta la Nariz)
             ArribaAbajo=ArribaAbajo+ALTURA;
        break;        
        case 'M': //M: Gira Hacia Abajo, (Baja la Nariz)
             ArribaAbajo=ArribaAbajo-ALTURA;             
        break;        
        case '+':
            if(Zoom==ON)      
               ZoomAumentDismin=ZoomAumentDismin+ACERC_ALEJ;                 
        break;
        case '-':
            if(Zoom==ON)
               ZoomAumentDismin=ZoomAumentDismin-ACERC_ALEJ; // Reducir                         
        break;          
   }    
        glutPostRedisplay();

}
void InicializarVariables(){
    Base.ROJO=0;
    Base.VERDE=0;
    Base.AZUL=0;
     
    Molino.ROJO=1;
    Molino.VERDE=0;
    Molino.AZUL=0;
            
    HAspa.ROJO=0;
    HAspa.VERDE=0;
    HAspa.AZUL=1;
    
    HCabina.ROJO=1;
    HCabina.VERDE=0;
    HCabina.AZUL=0;
    
    HMovAspa=OFF;
    Giro=HORARIO;
    angAspa=0;
    giraIzqDer=0;
}
int main(int argc, char** argv)
{
InicializarVariables();
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
glutInitWindowSize(800, 800);
glutInitWindowPosition(20, 20);
glutCreateWindow("Segunda Practica de Laboratorio - FISI UNMSM");
Menus();
glutAttachMenu(GLUT_RIGHT_BUTTON);//Añado el Menu
glutKeyboardFunc(teclado); //Añado el evento del teclado
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutTimerFunc(25, update, 0); //Añado el timer
glutMainLoop();

return 0;
}
