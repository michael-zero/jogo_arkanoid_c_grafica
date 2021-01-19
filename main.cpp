#include <iostream>
#include <GL/glut.h>
#include <stdio.h>
#include <cstdio>
#include <windows.h>      //usada para reproduzir sons de fundo
#include <mmsystem.h>    //usada para reproduzir sons de fundo

//============= Texturas e obj ===================
#define STB_IMAGE_IMPLEMENTATION//usada para carregar textura das imagens
#include "stb_image.h" //usada para carregar textura das imagens
//#include "glm.h"//usada para carregar os objetos(obj) do jogo
//================================================

using namespace std;
#define BLOCOS 18

float cx=2,cy=8,cz=25.5; 
float inimigoX = 2, inimigoY = 8, inimigoZ = 19.5; 
float  zoom = -30;

float blocoX = -2.30, blocoY = 8.0, blocoZ = 15;
float velX = 0.5;
float velZ = 0.5;

struct Bloco{
    float x;
    float z;
    float y;
    bool vivo;
};



Bloco blocos[BLOCOS];
void DesenhaBlocos();
void iniciaBlocos();






void criaCubo(float x) {
	// Desenhas as linhas das "bordas" do cubo
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(1.6f);
	glBegin(GL_LINE_LOOP);	// frontal
	glVertex3f(x, x, x);
	glVertex3f(-x, x, x);
	glVertex3f(-x, -x, x);
	glVertex3f(x, -x, x);
	glEnd();
	glBegin(GL_LINE_LOOP);	//  posterior
	glVertex3f(x, x, -x);
	glVertex3f(x, -x, -x);
	glVertex3f(-x, -x, -x);
	glVertex3f(-x, x, -x);
	glEnd();
	glBegin(GL_LINES);	//  laterais
	glVertex3f(-x, x, -x);
	glVertex3f(-x, x, x);
	glVertex3f(-x, -x, -x);
	glVertex3f(-x, -x, x);
	glVertex3f(x, x, -x);
	glVertex3f(x, x, x);
	glVertex3f(x, -x, -x);
	glVertex3f(x, -x, x);
	glEnd();

	// Desenha as faces do cubo preenchidas
	// Face frontal
	glBegin(GL_QUADS);
	
	
	glNormal3f(0.0, 0.0, 1.0);	// Normal da face
	glColor3f(1.0f, 1.0f, 0.0f);
	 glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(x, x, x);
	
	glColor3f(0.0f, 1.0f, 0.0f);
	 glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-x, x, x);
	
	glColor3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-x, -x, x);


	glColor3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, -x, x);
	
	
	
	// Face posterior
	glNormal3f(0.0, 0.0, -1.0);
	glColor3f(1.0f, 1.0f, 1.0f);
   // glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(x, x, -x);

	glColor3f(1.0f, 0.0f, 1.0f);
   // glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, -x, -x);

	glColor3f(0.0f, 0.0f, 1.0f);
  //  glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-x, -x, -x);

	glColor3f(0.0f, 1.0f, 1.0f);
//	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-x, x, -x);

	// Face lateral esquerda
	glNormal3f(-1.0, 0.0, 0.0);
	glColor3f(0.0f, 1.0f, 0.0f);
	 glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-x, x, x);
	
   

	glColor3f(0.0f, 1.0f, 1.0f);
	 glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-x, x, -x);

   
	
	glColor3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-x, -x, -x);
	
	 

	glColor3f(0.0f, 0.0f, 0.0f);
	 glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-x, -x, x);
	
	

	// Face lateral direita
	glNormal3f(1.0, 0.0, 0.0);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(x, x, x);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x, -x, x);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(x, -x, -x);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(x, x, -x);
	
	
	// Face superior
	glNormal3f(0.0, 1.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-x, x, -x);
  
    

	glColor3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-x, x, x);



	glColor3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, x, x);

	

	glColor3f(1.0f, 1.0f, 1.0f);
	 glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, x, -x);
  
   

	//Iluminação
	glNormal3f(0.0, -1.0, 0.0);
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(-x, -x, -x);
	glTexCoord2f(0, 1); //atribui coordenada de textura ao objeto
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(x, -x, -x);
	glTexCoord2f(0, 0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x, -x, x);
	glTexCoord2f(1, 0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-x, -x, x);
	glTexCoord2f(1, 1);
	
	glEnd();
}

//A - inimigo
//B - personagem ou outro elemento
bool colisao(float Ax, float Ay, float Acomp, float Aalt, float Bx, float By, float Bcomp, float Balt){
	
    if(Ay+Aalt < By) return false;
    else if(Ay > By+Balt) return false; //bater embaixo
    else if(Ax + Acomp < Bx) return false;
    else if(Ax > Bx + Bcomp) return false;

    return true;
}

/*bool colisao(float Ax, float Ay, float Az,float Bx, float By, float Bz){
    
	if(Ay < By) return false;
    else if(Ay > By+Bz) return false; 
    else if(Ax + Az < Bx) return false;
    else if(Ax > Bx + Bz) return false;

    return true;
}*/
	
	


void update(int value){
	
	inimigoX+=velX;
//  printf("x[%d] = %.2lf %.2lf %.2lf\n",0, blocos[0].x, blocos[0].y, blocos[0].z );
    for(int n = 0; n < BLOCOS; n++){
	    if(blocos[n].vivo){
	        if(colisao(inimigoX,inimigoZ,0.7,0.7,blocos[n].x,blocos[n].z,0.9,0.9) == true){
	        		printf("colidiu\n");
	            velX = -velX; //bateu no bloco, volta
	            blocos[n].vivo = false;
	            break;
	        }
	    }
    }
	
	
	
	inimigoZ+=velZ;
	
	   for(int n = 0; n < BLOCOS; n++){
		if(blocos[n].vivo){
		    if(colisao(inimigoX,inimigoZ,0.7,0.7,blocos[n].x,blocos[n].z,0.9,0.9) == true){
		    		printf("colidiu\n");
		    	PlaySound(TEXT("col.wav"), NULL, SND_ASYNC);
					//PlaySound(TEXT("col.wav"), NULL, SND_ASYNC | SND_LOOP);  //Inicia o áudio de fundo do jogo
		        velZ = -velZ; //bateu no bloco, volta
		        blocos[n].vivo = false;
		        break;
		    }
		}
	}
	
	
	
	
	if(inimigoX >= 8){ //se bater na lateral direita
		velX = -velX;
	}
	
	if(inimigoX <= -3){ //se bater na lateral esquerda.
		velX = -velX;
		 inimigoX = -2.0;
		/*	if(cx - 1 <= -3){ //Lado esq. inferior
			cx = -2.3;
		}else{
			cx-=0.5;
		}*/
	}
	
	if(inimigoZ >= 26){ //se bater embaixo
		velZ = -velZ;
	    //toca som
	    PlaySound(TEXT("error.wav"), NULL, SND_ASYNC);
		iniciaBlocos();
		DesenhaBlocos();

	}
	
	if(inimigoZ <= 15){ //tocar em cima
		velZ = -velZ;
	}
	
	if(colisao(inimigoX,inimigoZ,0.7,0.7,cx,cz,1,1) == true){
   			printf("colidiu\n");
			printf(" perso %.2lf %.lf %.lf\n",cx,cy,cz);
            printf(" inimigo %.2lf %.2lf %.2lf\n",inimigoX,inimigoY,inimigoZ);
	
        velZ = -velZ;
	}
	
	
	
	

	glutPostRedisplay();
	glutTimerFunc(200, update, 0);
}

void  parede(){
	
		  	    	int w, h;
    	GLuint texture2;
	    unsigned char *uc2 = stbi_load("bloco.jpeg", &w, &h, NULL, 0);
	    glGenTextures(1, &texture2); //gera nomes identificadores de texturas
	    glBindTexture(GL_TEXTURE_2D, texture2); //Ativa a textura atual
	
	    // Cria a textura lateral de cada bloco
	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h,
	                 0, GL_RGB, GL_UNSIGNED_BYTE, uc2);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	    glEnable(GL_TEXTURE_2D); //Ativando textura
	

	
		glPushMatrix(); //ymax
			glColor3f(1,1,0);
			glScalef(39.0,1.0,1.0);
			glTranslatef(0.25,0.0,0.0);
			criaCubo(0.25);
			//glutSolidCube(0.5);
		glPopMatrix();
	


		
	
	
		glPushMatrix(); //xmin
			glColor3f(0,0,1);
			glScalef(1.0,1.0,40.0);
			glTranslatef(0.0,0.0,0.24);
	        criaCubo(0.25);
 	 	   //glutSolidCube(0.5);
		glPopMatrix();
		
		
      
	

		glPushMatrix();
			glColor3f(1,1,0);
			glScalef(39.0,1.0,1.0);
			glTranslatef(0.25,0.0,19.0);
			criaCubo(0.25);
		//	glutSolidCube(0.5);
		glPopMatrix();
		glPushMatrix();
			glColor3f(1,1,0);
			glScalef(1.0,1.0,39.0);
			glTranslatef(19.0,0.0,0.25);
			criaCubo(0.25);
		//	glutSolidCube(0.5);
		glPopMatrix();
		
		  glDisable(GL_TEXTURE_2D);  //desativa a textura dos blocos
		
		 
	
}

void inimigo(){
	
    	int w, h;
	GLuint texture2;
    unsigned char *uc2 = stbi_load("p.jpeg", &w, &h, NULL, 0);
    glGenTextures(1, &texture2); //gera nomes identificadores de texturas
    glBindTexture(GL_TEXTURE_2D, texture2); //Ativa a textura atual

    // Cria a textura lateral de cada bloco
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h,
                 0, GL_RGB, GL_UNSIGNED_BYTE, uc2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glEnable(GL_TEXTURE_2D); //Ativando textura
	
		//Inimigo
    glPushMatrix();
		glColor3f(1,0,0);
		glTranslatef(inimigoX, inimigoY, inimigoZ);
		criaCubo(0.4);
		//glutSolidCube(0.7);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);  //desativa a textura dos blocos
}

void teste(){
	
    glPushMatrix();
		glColor3f(1,0,0);
		//8 = y
		glTranslatef(2, 15,19.5);
		glutSolidCube(0.7);
	glPopMatrix();	
}

void personagem(){
	
 
    GLuint texture2;
	int w, h;
    unsigned char *uc2 = stbi_load("cubo.jpeg", &w, &h, NULL, 0);
    glGenTextures(1, &texture2); //gera nomes identificadores de texturas
    glBindTexture(GL_TEXTURE_2D, texture2); //Ativa a textura atual

    // Cria a textura lateral de cada bloco
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h,
                 0, GL_RGB, GL_UNSIGNED_BYTE, uc2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glEnable(GL_TEXTURE_2D); //Ativando textura

	//Desenha Personagem 
	glPushMatrix();
		//glColor3f(1,1,1);
		glTranslatef(cx,cy,cz);
		//printf("cx %.2lf %.2lf %.2lf\n",cx,cy,cz);
	//==================================================================	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT4);
	
	criaCubo(0.4);
	glDisable(GL_LIGHTING);
	
		//glutSolidCube(0.7);
	glPopMatrix();
	//glDeleteTextures(1, & texture1);
    //stbi_image_free(uc2);
    
    //========== FIM DESENHA PERSONAGEM ====================
    
 	glDisable(GL_TEXTURE_2D);  //desativa a textura dos blocos

	parede();
}

void drawGrid(){
	int i;
	for(i = 0; i<40;i++)
	{
		glPushMatrix();
		if(i<20){
			glTranslatef(0,0,i);
			}
			
        if(i>=20){
			glTranslatef(i-20,0,0); glRotatef(-90,0,1,0);
			}
			
	   glBegin(GL_LINES);
		   glColor3f(0.01,0.01,0.71);
		   glLineWidth(1);
		   glVertex3f(0,-0.1,0);
		   glVertex3f(19,-0.1,0);
	   glEnd();	
       glPopMatrix();
	}
}

void DesenhaBlocos(){

		
	   	  	    // blocos[9].vivo = false;
	   
	  	    	int w, h;
	  	    	GLuint texture2;
			    unsigned char *uc2 = stbi_load("l.jpeg", &w, &h, NULL, 0);
			    glGenTextures(1, &texture2); //gera nomes identificadores de texturas
			    glBindTexture(GL_TEXTURE_2D, texture2); //Ativa a textura atual
			
			    // Cria a textura lateral de cada bloco
			    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h,
			                 0, GL_RGB, GL_UNSIGNED_BYTE, uc2);
			    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
			    glEnable(GL_TEXTURE_2D); //Ativando textura
	   
	  
	    for(int i = 0; i < BLOCOS; i++){
		    if(blocos[i].vivo){	//se o bloco NÃO foi tocado -> desenha
		    	
		    	// fim textura
		    	glPushMatrix();
		    		//glEnable(GL_LIGHTING);
		    		 //glEnable(GL_LIGHT0);
					glColor3f(0,0,1);
					glTranslatef(blocos[i].x,8, blocos[i].z);
					criaCubo(0.4);
					//glutSolidCube(0.9);
					glDisable(GL_LIGHTING);
		        glPopMatrix();
		        
    		
			}
	   }
	   
	   	glDisable(GL_TEXTURE_2D);  //desativa a textura dos blocos
}

void display(){
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	
  	glTranslatef(-13,0,-45);
	glRotatef(40,1,1,0);
	


   	drawGrid();
   	inimigo();
 //   teste();
	personagem();   
//	criaCubo(2);
	DesenhaBlocos();
	glutSwapBuffers();
}

void init(){
//	PlaySound("s.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(35,1.0f,0.1f,1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0,0,0,1);
	glEnable(GL_COLOR_MATERIAL);
   
   // glEnable(GL_LIGHTING);
   // glShadeModel(GL_SMOOTH);

    //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  //  glEnable(GL_LIGHT0);
//	glShadeModel(GL_SMOOTH);	

}

void keyboard(unsigned char key, int x, int y){
	
	// Frente / para tras 
	// Não move pra frente 
	if(key == 'w'){
		if(cz <= 15){
			cz = 15;
		}else{
			cz-=1;
		}
		
   } //frente
	
    if(key == 's'){
		if(cz + 0.5 >= 25){
			cz = 25.5;
		}else{
			cz+=0.5;
		}
	} //forward / back 
    //Fim do frente tras 

    //left / right
	if(key == 'a'){
		if(cx - 1 <= -3){ //Lado esq. inferior
			cx = -2.3;
		}else{
			cx-=0.5;
		}
	} if(key == 'd'){ //Lado dir. inferior
	   if(cx + 0.5 >= 9){
		   cx = cx;
	   }else{
		   	cx+=0.5;
	   }
	//==== FIM left / right
    }
   
   /*/ if(key == 'q'){cy+=1;} if(key == 'z'){cy-=1;} //up   / down */
    	
    glutPostRedisplay();
}

void iniciaBlocos(){
	//cria blocos
    float x = -2.3, z = 15.5; 
    for(int n = 0;  n < BLOCOS; n++){

        if(x > 8.5){
            x = -2.3;
            z +=2;
        }

        blocos[n].x = x;
        blocos[n].z = z;
        blocos[n].y = 8;
        blocos[n].vivo = true;
        x+=1.3;
    }
}

int main(int argc, char** argv)
{
    iniciaBlocos();
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800,600);
	glutCreateWindow("");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	init();
	glutTimerFunc(25, update, 0);
	glutMainLoop();
	return 0;
}