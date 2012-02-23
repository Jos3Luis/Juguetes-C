#include "stdafx.h"
/********************************************************************
* Universidad Nacional Mayor de San Marcos
* Facultad de Ingenieria de Sistemas
* Curso Computacion Grafica
 by Winjoseswf
* 3er Examen de Computacion Grafica
********************************************************************/
struct Bola{
	//Posiciones
	float x;
	float y;
	float z;
};
#define TIME 200
#define RADIO 0.05
#define TOTAL 255
#define INC 0.05 //valor a incrementar en su desplazamiento

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define pi  3.141592
#include "imageloader.h"
using namespace std;

//Declaracion de Funciones
void initBola();

void PintarCaraI();
void PintarCaraII();
void PintarCaraIII();
void PintarCaraIV();
void PintarCaraV();
void PintarCaraVI();

void Paralelepipedo();
void dibujarEsferas();

int ChocaCara(float x,float y,float z);
void InvertirDireccion();
void Menus();
void EventosPrincipales(int opc);

void Iluminar();
GLuint loadTexture(Image* image);

//Varibles globales
GLuint idTextura; //El id de la textura
Bola bola;
float incrX,incrY,incrZ;
bool pintar1,pintar2,pintar3,pintar4,pintar5,pintar6;
bool COLOR;
bool TEXTURA;
//funciones de opengl
void reshape (int w, int h);
void display(void) ;
void dibujo();
void EventosPrincipales(int opc);
void Menus();


void display(void) {
    glClearColor(1.0, 1.0, 1.0, 0.5);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(TEXTURA){
      Iluminar();//------------------------------------------------------
    }
    dibujo();
    glutSwapBuffers();
}
void update(int value)
{
    //Vemos si choca en alguna cara
	int pos=ChocaCara(bola.x,bola.y,bola.z);
	switch(pos){
		case 1:{
			PintarCaraI();
			incrY=-INC;//Existe un Impulso Vertical Hacia Abajo
	   }break;
		case 2:{
			PintarCaraII();
			incrX=-INC;//Existe un Impulso en el EjeX Hacia la Izquierda
	   }break;
		case 3:{
			PintarCaraIII();
			incrZ=-INC;	   
	   }break;
		case 4:{
			PintarCaraIV();
			incrX=INC;
	   }break;
		case 5:{
			PintarCaraV();
			incrY=INC;
	   }break;
		case 6:{
			PintarCaraVI();
			incrZ=INC;	   
	   }break;
	}
	bola.x+=incrX;
	bola.y+=incrY;
	bola.z+=incrZ;
	glutPostRedisplay();

	glutTimerFunc(TIME, update, 0);
	
}
//Metodo que Avisa en que cara Choca
int ChocaCara(float x,float y,float z){
	if((-2<=x<=2) && (-1<=z<=1) && (y<=-1)){
		return 5;//pared V
	}else{
		if((-1<=z<=1) && (-1<=y<=1) && (x>=2)){
			return 2;//pared II
		}else{
			if((-2<=x<=2) && (-1<=z<=1) && (y>=1)){			
				return 1;//pared I
			}else{
				if((-2<=x<=2) && (-1<=y<=1) && (z<=-1)){
					return 6;//pared VI
				}else{
					if((-1<=y<=1) && (-1<=z<=1) && (x<=-2)){
						return 4;//pared IV
					}else{
						if((-2<=x<=2) && (-1<=y<=1) && (z>=1)){
							return 3;//pared III
						}else{
							if(x>=2 || x<=-2 || y>=1 || y<=-1|| z>=1 || z<=-1){
							   cout<<"-Salio ";
							   cout<<"("<<bola.x<<","<<bola.y<<","<<bola.z<<")\n";
							}
							return -1;
						}					
					}				
				}
			}		
		}	
	}
}
//Dibuja Las 8 Esferas colocadas en cada esquina del cubo
void dibujarEsferas()
{  
	//Dibujo de las esferas
	glColor3ub(241,185,14);
	glPushMatrix();	
	glTranslatef(-2,1,-1);
	glutWireSphere(RADIO, 8, 8);
    glPopMatrix();

	glPushMatrix();	
	glTranslatef(2,1,-1);
	glutWireSphere(RADIO, 8, 8);
    glPopMatrix();

	glPushMatrix();	
	glTranslatef(2,1,1);
	glutWireSphere(RADIO, 8, 8);
    glPopMatrix();

	glPushMatrix();	
	glTranslatef(-2,1,1);
	glutWireSphere(RADIO, 8, 8);
    glPopMatrix();

	glPushMatrix();	
	glTranslatef(-2,-1,-1);
	glutWireSphere(RADIO, 8, 8);
    glPopMatrix();

	glPushMatrix();	
	glTranslatef(2,-1,-1);
	glutWireSphere(RADIO, 8, 8);
    glPopMatrix();

	glPushMatrix();	
	glTranslatef(2,-1,1);
	glutWireSphere(RADIO, 8, 8);
    glPopMatrix();

	glPushMatrix();	
	glTranslatef(-2,-1,1);
	glutWireSphere(RADIO, 8, 8);
    glPopMatrix();

}
//Dibujo En la escena
void dibujo(){
glPushMatrix();
glScalef(0.75,0.75,0.75);
	if(pintar1){
		PintarCaraI();
	}
	if(pintar2){
		PintarCaraII();
	}
	if(pintar3){
		PintarCaraIII();
	}
	if(pintar4){
		PintarCaraIV();
	}
	if(pintar5){
		PintarCaraV();
	}
	if(pintar6){
		PintarCaraVI();
	}

Paralelepipedo();
dibujarEsferas();
	glPushMatrix();
	glTranslatef(bola.x,bola.y,bola.z);
	glColor3f(0,0,0);
	glutWireSphere(RADIO, 6, 8);
	glPopMatrix();
glPopMatrix();
}
void Paralelepipedo(){ //Dibujo de los Objetos
	glColor3f(0,0,0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(-2,1,-1);
	glVertex3f(2,1,-1);
	glVertex3f(2,1,1);
	glVertex3f(-2,1,1);
	glVertex3f(-2,1,-1);//repite
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-2,-1,-1);
	glVertex3f(2,-1,-1);
	glVertex3f(2,-1,1);
	glVertex3f(-2,-1,1);
	glVertex3f(-2,-1,-1);
	glVertex3f(-2,-1,-1);//repite
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(-2,1,1);
	glVertex3f(-2,1,-1);
	glVertex3f(-2,-1,-1);
	glVertex3f(-2,-1,1);
	glVertex3f(-2,1,1);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glVertex3f(2,1,1);
	glVertex3f(2,1,-1);
	glVertex3f(2,-1,-1);
	glVertex3f(2,-1,1);
	glVertex3f(2,1,1);
	glEnd();
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
    glViewport(0,0,900, 800);
}

void EventosPrincipales(int opc){
     switch(opc){  
/*******************    ********************/                   
         case   0: //
                COLOR=false;
				TEXTURA=true;
                break;
         case   1:
                COLOR=true;
				TEXTURA=false;
                break;
		 case   2:
				InvertirDireccion();
                break;                        
		 case   3: 
			 exit(0);
                break;  
     } 
     glutPostRedisplay();        
}
void Menus(){//Creacion de los Menus
    int SubMenuImpacto= glutCreateMenu(EventosPrincipales);
    glutAddMenuEntry("IMAGEN",0);
    glutAddMenuEntry("COLOR",1);

    glutCreateMenu(EventosPrincipales);
    glutAddSubMenu("CONFIGURAR IMPACTO",SubMenuImpacto);
	glutAddMenuEntry("INVERTIR DIRECCION",2);	
    glutAddMenuEntry("SALIR",3);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void PintarCaraI(){
	pintar1=true;
	pintar2=false;
	pintar3=false;
	pintar4=false;
	pintar5=false;
	pintar6=false;
	
    if(COLOR){
	glColor3ub(181,146,61);
	glBegin(GL_QUADS);
	glVertex3f(-2,1,-1);
	glVertex3f(2,1,-1);
	glVertex3f(2,1,1);
	glVertex3f(-2,1,1);
	glEnd();              
    }
    if(TEXTURA){
	//glColor3ub(181,146,61);	
	glBegin(GL_QUADS);		
	glNormal3f( 0, 1, 0);
    glVertex3f(-2,1,-1);
	glVertex3f(2,1,-1);
	glTexCoord2f(0,1); glVertex3f(2,1,1);
	glVertex3f(-2,1,1);
	glEnd();        
    }
}
void PintarCaraII(){
	pintar1=false;
	pintar2=true;
	pintar3=false;
	pintar4=false;
	pintar5=false;
	pintar6=false;
	
    if(COLOR){
	glColor3ub(226,84,16);
	glBegin(GL_QUADS);
	glVertex3f(2,1,1);
	glVertex3f(2,1,-1);
	glVertex3f(2,-1,-1);
	glVertex3f(2,-1,1);
	glEnd();              
    }
    if(TEXTURA){
	//glColor3ub(226,84,16);
	glBegin(GL_QUADS);
	glNormal3f( 2, 0, 0);
	glVertex3f(2,1,1);
	glVertex3f(2,1,-1);
	glVertex3f(2,-1,-1);
	glVertex3f(2,-1,1);
	glEnd();                
    }    
}
void PintarCaraIII(){
	pintar1=false;
	pintar2=false;
	pintar3=true;
	pintar4=false;
	pintar5=false;
	pintar6=false;
	
    if(COLOR){
	glColor3ub(95,230,13);
	glBegin(GL_QUADS);
	glVertex3f(-2,1,1);
	glVertex3f(2,1,1);
	glVertex3f(2,-1,1);
	glVertex3f(-2,-1,1);
	glEnd();              
    }
    if(TEXTURA){
	//glColor3ub(95,230,13);
	glBegin(GL_QUADS);
	glNormal3f( 0, 0, 1);
	glTexCoord2f(-2,1); glVertex3f(-2,1,1);
	glTexCoord2f(0,1); glVertex3f(2,1,1);
	glTexCoord2f(0,0); glVertex3f(2,-1,1);
	glTexCoord2f(-2,0); glVertex3f(-2,-1,1);
	glEnd();                                
    }
}
void PintarCaraIV(){
	pintar1=false;
	pintar2=false;
	pintar3=false;
	pintar4=true;
	pintar5=false;
	pintar6=false;

    if(COLOR){
	glColor3ub(77,219,123);
	glBegin(GL_QUADS);
	glVertex3f(-2,1,1);
	glVertex3f(-2,1,-1);
	glVertex3f(-2,-1,-1);
	glVertex3f(-2,-1,1);
	glEnd();
    }
    if(TEXTURA){    
//	glColor3ub(77,219,123);
	glBegin(GL_QUADS);
	glNormal3f( -2, 0, 0);
	glVertex3f(-2,1,1);
	glVertex3f(-2,1,-1);
	glVertex3f(-2,-1,-1);
	glVertex3f(-2,-1,1);
	glEnd();           
    }

}
void PintarCaraV(){
	pintar1=false;
	pintar2=false;
	pintar3=false;
	pintar4=false;
	pintar5=true;
	pintar6=false;
	
    if(COLOR){
	glColor3ub(27,10,233);
	glBegin(GL_QUADS);
	glVertex3f(-2,-1,-1);
	glVertex3f(2,-1,-1);
	glVertex3f(2,-1,1);
	glVertex3f(-2,-1,1);
	glEnd();
    }
    if(TEXTURA){
	//glColor3ub(27,10,233);
	glBegin(GL_QUADS);
	glNormal3f( 0, -1, 0);	
	glVertex3f(-2,-1,-1);
	glVertex3f(2,-1,-1);
	glVertex3f(2,-1,1);
	glVertex3f(-2,-1,1);
	glEnd();                
    }

}
void PintarCaraVI(){
	pintar1=false;
	pintar2=false;
	pintar3=false;
	pintar4=false;
	pintar5=false;
	pintar6=true;
    if(COLOR){
	glColor3ub(217,26,213);
	glBegin(GL_QUADS);
	glVertex3f(-2,1,-1);
	glVertex3f(2,1,-1);
	glVertex3f(2,-1,-1);
	glVertex3f(-2,-1,-1);
	glEnd();    
    }
    if(TEXTURA){//Listo
	//glColor3ub(217,26,213);
	glBegin(GL_QUADS);
	glNormal3f( 0, 1, -1);
	glTexCoord2f(-2,1); glVertex3f(-2,1,-1);
	glTexCoord2f(0,1); glVertex3f(2,1,-1);
	glTexCoord2f(0,0); glVertex3f(2,-1,-1);
	glTexCoord2f(-2,0); glVertex3f(-2,-1,-1);
	glEnd(); 
    }
}


void initBola(){
	int puntos=0;
do{	
	//-----------Posicion Aleatoria---------------------
	time_t t;
	struct tm *hora;
	time(&t);
	hora = localtime(&t);
	int segundos=hora->tm_sec;
	//cout<<"Semilla:"<<segundos<<"\n"; //Calculo "Los segundos" actuales del sistema
	
	srand(segundos);//Para cada segundo diferente mostrara un random diferente en la funcion rand()
	//Pequeña forma de calcular reales aleatorios
	//formula:
	//m=a+ (b-a)*(float)rand()/RAND_MAX;  //Donde a: Limite Inferior, b=Limite Superior
	bola.x=-2+4*(float)rand()/RAND_MAX; //-2<=x<=2
	bola.y=-1+2*(float)rand()/RAND_MAX; //-1<=y<=1
	bola.z=-2+4*(float)rand()/RAND_MAX; //-1<=z<=1
	cout<<"\n\nPosicion Inicial: P=("<<bola.x<<","<<bola.y<<","<<bola.z<<")";
//-----------Direccion Aleatoria (Sentido en 3D)---------------------
	int val;
	
		val=1+rand()%61;
		if(val<20){
			incrX=INC;
		}else{
			incrX=-INC;
		}
		if(20<val && val<40){
			incrY=INC;
		}else{
			incrY=-INC;
		}
		if(val<60){
			incrZ=INC;
		}else{
			incrZ=-INC;
		}
		puntos++;
		system("cls");
		//cout<<"\nSalio-MAL : "<<bola.x+incrX<<"-"<<bola.y+incrY<<"-"<<bola.z+incrZ;
		cout<<"Generando Aleatorios, Espere";
		for(int i=0;i<puntos;i++){
		   cout<<".";
		}
	}while(-2>(bola.x+incrX )|| (bola.x+incrX)>2  ||  -1>(bola.y+incrY )|| (bola.y+incrY)>1  ||  -1>(bola.z+incrZ) || (bola.z+incrZ)>1);
	//Pues puede darse el caso de que  la posicion aleadoria + un incremento aleatorio de direccion
	//se salga del interior del cubo (Habria que generar otra posicion)
	cout<<"\nPosicion Inicial P=("<<bola.x<<","<<bola.y<<","<<bola.z<<")\n";
	pintar1=false;
	pintar2=false;
	pintar3=false;
	pintar4=false;
	pintar5=false;
	pintar6=false;

	COLOR=true;
    TEXTURA=false;
}
void InvertirDireccion(){
	cout<<"\nInvertir\n";
	cout<<incrX<<","<<incrY<<","<<incrZ<<"\n";
	cout<<bola.x<<","<<bola.y<<","<<bola.z<<"\n";
	incrX=-incrX;
	incrY=-incrY;
	incrZ=-incrZ;
	cout<<incrX<<","<<incrY<<","<<incrZ<<"\n";	
	
}
/*--------------Funciones para la textura---------------*/

GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId); //Informa a OpenGL cual textura a editar
	//Mapea la imagen a la textura
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->width, image->height,0,GL_RGB,GL_UNSIGNED_BYTE,image->pixels);
	return textureId; //Returns the id of the texture
}
void Iluminar(){
//	GLfloat ambientLight[] = {-3, 0.0f, 0.0f, 0.0f};
	GLfloat ambientLight[] = {0.2f, 0.2f, 0.2f, 1.0f};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	
	GLfloat directedLight[] = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat directedLightPos[] = {-10.0f, 15.0f, 20.0f, 0.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
	glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, idTextura);//Lo primero es decirle a OpenGL qué textura vamos a utilizar con glBindTexture
	
	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//Con la función glTexParameteri OpenGL nos permite establecer el filtro de ampliación y de reducción (GL_TEXTURE_MAG_FILTER y GL_TEXTURE_MIN_FILTER)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
}
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	
	Image* image = loadBMP("foto.bmp");
	idTextura = loadTexture(image);
	delete image;
}
int main(int argc, char** argv)
{
initBola();
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
glutInitWindowSize(800, 800);
glutInitWindowPosition(20, 20);
glutCreateWindow("Tercera Practica de Laboratorio - FISI UNMSM");
Menus();
glutAttachMenu(GLUT_RIGHT_BUTTON);//Añado el Menu
glutDisplayFunc(display);
glutReshapeFunc(reshape);
glutTimerFunc(TIME, update, 0); //Añado el timer
glutMainLoop();

return 0;
}
