#include <string.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#define PI    3.14159265358979323846

GLfloat kx = 700,ky = -12;// posição inicial do boneco
GLfloat vx = -60, vy= -12;// posição inicial da vacina

GLfloat tx = -40, ty = -12 ;// posição inicial dos obstaculos
GLfloat mx = 120, mx2 = 200, mx3 = 300, my = -12, ny=8, nx =500, nx1= 800; // distancia entre os obstaculos
GLfloat win = 25;
GLint temp = 30, auxpause=0; 
GLint estado = 0;
char texto[30];


GLfloat wine, r, g, b;

GLfloat pontuacao=0.0, Alternar=0.0, TimerBuff = 0.0, aux; // variaveis auxiliares para ajudar na poontuação
GLfloat AlternarPersonagem = 0.0;

GLint win_width, win_height;
GLuint DataPos, imageSize;
GLsizei Width,Height;
GLuint texture_id[1];
GLfloat xf, yf,winw, aspecto;
float bon1 =255.0f , bon2 =1.0f ;
float cor1=1.0f, cor2= 1.0f, cor3= 1.5f; 
float t1 = 0.0f,t2 = 1.0f,t3 = 1.0f;// cores do tempo
int extra;
float q1=1.0f, q2 = 1.0f, q3 = 0.0f;  //Cores Sol
float luaCima1, luaCima2, luaCima3; //Cores do Círculo Superior



//static int menu_id;
static int mudarTerrenoID;  //Alterar o tipo de terreno do jogo
static int mudarCorID;  //Mudar a cor dos virus do covid
static int covidcolor = 0; //Cor inicial personagem


void jogo();
void iniciando();
void comandos();
void SobreJogo();

void mudarTerreno();
void mudarCor();











void DesenhaTexto(void *font, char *string) // função usada para mostrar texto na tela
{
	// Exibe caractere a caractere
	while(*string)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*string++); 
}
                     
void Timer(int value)// função usada para a movimentação e a contagem da pontuação do boneco
{
    mx = mx-1;
    mx2 = mx2-1;
    mx3 = mx3-1;
    nx = nx-.6;
    nx1 = nx1-1.5;
	kx = kx - 1;
	
	if(kx < -70)
		kx = 700;
    if(mx < -80)
        mx = 100;
    if(mx2 < -80)
        mx2 = 100;
    if(nx < -80)
    	nx = 100;
    if(nx1 <-80)
    	nx1 = 100;
    if(mx3 < -80){
        mx3 = 100;
        if(temp > 10)
            temp=temp-5;
    }
	pontuacao+=0.2;
	Alternar += 0.1;
	AlternarPersonagem += 0.1;
	if(extra== 1){
		TimerBuff += 0.1; 
	}	
		
	glutTimerFunc(temp,Timer,1);	//função callback para facilitar o processo para fazer a animação
    glutPostRedisplay();
}


void Pular2(int value)//Função usada para fazer suavizar a transiçao dos obstaculos 
{
    if(ty != -12){
        if(ty == 0){
            ty--;
            glutTimerFunc(50,Pular2,1);
    }else{
        ty--;
        glutTimerFunc(20,Pular2,1);
    }
    }

    glutPostRedisplay();
}

void GameOver() // função para mostrar o texto quando o jogador perde
{
    glColor3f(1,1,1);
    glRasterPos2f(30,10);
    char* p = (char*) "GAME OVER!!";
    
    while (*p != '\0')
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p++);
    temp = 30;
    estado++;
    
}

void Pause()// função usada para pausar o jogo
{
    temp = 30;
    aux=pontuacao;
    estado++;
    
}

void Pular1(int value)
{
    if(ty < 0){
        ty++;
        glutTimerFunc(10,Pular1,1);
    }else if(ty == 0 || ty < 3)
    {
        ty++;
        glutTimerFunc(30,Pular1,1);
    }else
        glutTimerFunc(10,Pular2,1);

    glutPostRedisplay();
}


void Pontuacao() // função responsavel pela placar que é mostrado no canto esquerdo da tela
{	
		glColor3f(0,0,0);
	
	glPushMatrix();
    glColor3f(1.0,0.0,0.0);
    if(pontuacao > 0)
    	sprintf(texto, "Pontuacao: %.1f", pontuacao);

    
    glTranslatef(-58.0f, 22.0f,0.0f);
    glRasterPos2f(0,0);
    DesenhaTexto(GLUT_BITMAP_9_BY_15,texto);
    glPopMatrix();

}

void desenhaMeiaLua(GLfloat rx,GLfloat ry,GLfloat cx,GLfloat cy) // função usada para criar um circulo 
{
	 glBegin(GL_TRIANGLE_FAN);
 	 for(int i = 0;i<=100;i++){
    	float angle = 2*3.1416*i/100;
    	float x = rx*cosf(angle);
   		float y=ry*sinf(angle);
   		glVertex2f(x+cx,y+cy);
	
 	 }
 glEnd();
}

// Função para desenhar um obstaculo
void DesenhaObstaculo() // 
{
	glLineWidth(2);
	//glBegin(GL_QUADS);
	
	if(covidcolor==0) //Alterar cor do virus
	{
	  //glColor3f(1.0f,0.0f,0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);	
	}		
	else if(covidcolor==1)
	{	
	 glColor3f(0.0f, 0.0f, 1.0f);
	}
	else
	 glColor3f(0.0f, 2.0f, 0.0f);
	/*	glVertex2f(0,3);
		glVertex2f(0,-3);
		glVertex2f(3,-3);
		glVertex2f(3,3);*/
		desenhaMeiaLua(2,2,0,0);
		glBegin(GL_LINES);
		glColor3f(255.0f, 192.0f, 203.0f);
		//Lados
			glVertex2f(-2,0);
			glVertex2f(-3,0);
			
			glVertex2f(2,0);
			glVertex2f(3,0);
		// Cima e Baixo
			glVertex2f(0,2);
			glVertex2f(0,3);
			
			glVertex2f(0,-2);
			glVertex2f(0,-3);
			
		//De trevessa
			glVertex2f(-1.5,1);
			glVertex2f(-2.5,2);
			
			glVertex2f(1.5,1);
			glVertex2f(2.5,2);
	
			glVertex2f(-1.5,-1);
			glVertex2f(-2.5,-2);
			
			glVertex2f(1.5,-1);
			glVertex2f(2.5,-2);
			
		// Pontos

			glVertex2f(1.0,0.0);
			glVertex2f(1.5,0.5);
			
			glVertex2f(-0.5,0.5);
			glVertex2f(-1.0,1.0);
			
			glVertex2f(-0.5,-0.5);
			glVertex2f(-1.0,-1.0);
			
			glVertex2f(0.5,-0.0);
			glVertex2f(1.0,-0.5);
			
			glVertex2f(0.0,0.5);
			glVertex2f(1.0,1.0);
			
			
	glEnd();
	
}

// Função para desenhar a vacina
void DesenhaVacina()
{
	int vacinaOn = 1;
	glLineWidth(2);
	

	
	//Desenho retangulo
	glBegin(GL_QUADS);
	

	 glColor3f(105.0f,105.0f,105.0f);
		glVertex2f(10,2);
		glVertex2f(10,-2);
		glVertex2f(12,-2);
		glVertex2f(12,2);
	glEnd();
	
	
		//Desenho retangulo liquido dentro da vacina
	glBegin(GL_QUADS);
	 glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(10,1);
		glVertex2f(10,-2);
		glVertex2f(12,-2);
		glVertex2f(12,1);
	glEnd();
		
	//Desenho reta horizontal base
	glBegin(GL_LINES);
	glColor3f(105.0f,105.0f,105.0f);
	glVertex2i(10,-3);
	glVertex2i(12,-3);
	glEnd();
	
	//Desenho reta interliga base linha e retangulo
	glBegin(GL_LINES);
	glColor3f(105.0f,105.0f,105.0f);
	glVertex2i(11,-3);
	glVertex2i(11,-2);
	glEnd();
	
	//Desenha reta vertical em cima do retangulo (ponta da seringa)
	glBegin(GL_LINES);
	glColor3f(105.0f,105.0f,105.0f);
	glVertex2i(11,2);
	glVertex2i(11,4);
	glEnd();
	
	
	

	
	
	
}





void DesenhaPersonagem()
{
	
	
	
	//Corpo
	glBegin(GL_LINES);
	glColor3f(105.0f,105.0f,105.0f);
	glVertex2i(0,2);
	glVertex2i(0,0);
	glEnd();
	
	
	//Braço Esquerdo
	glBegin(GL_LINES);
	glColor3f(1.0f,bon2,0.0f);
	glVertex2i(0,2);
	glVertex2i(-1,0);
	glEnd();
	
	
	
	//Braço Direito
	glBegin(GL_LINES);
	glColor3f(1.0f,bon2,0.0f);
	glVertex2i(0,2);
	glVertex2i(1,0);
	glEnd();
	
	
	//Cabeça
	int o = 0;
	GLfloat x = 0.0f;
	GLfloat y = 4.0f;
	GLfloat radius = 2.0f;
	int triangleAmount = 40;
	
	GLfloat twicePi = 2.0f * PI;
	
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(255.0f, bon1, 0.0f);
			glVertex2f(x, y);
			for(o = 0; o <= triangleAmount; o++)
			{
				glVertex2f(
					x + (radius * cos(o * twicePi / triangleAmount)),
					y + (radius * sin(o * twicePi / triangleAmount))
				
				);
				
			}
		glEnd();
		glFlush();
		glFlush();
		
   	//Perna Direita
	glBegin(GL_LINES);
	glColor3f(1.0f,bon2,0.0f);
	glVertex2i(0,0); 
	glVertex2i(2,-2);
	glEnd();
	
		
	//Perna Esquerda
	glBegin(GL_LINES);
	glColor3f(1.0f,bon2,0.0f);
	glVertex2i(0,0);
	glVertex2i(-1,-2); 
	glEnd();

   
	//Prancha Skate (sk8)
	glBegin(GL_LINES);
	glColor3f(0.0f,0.0f,1.0f);
	glVertex2i(-1,-2);
	glVertex2i(3,-2);
	glEnd();
	
	//Roda esquerda
	int l = 0;
	GLfloat lx = -0.5f;
	GLfloat ly = -2.8f; 
	GLfloat lradius = 0.5f; 
	int ltriangleAmount = 40; 
	
	GLfloat ltwicePi = 2.0f * PI;
	
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(251.0f, 235.0f, 20.0f);
			glVertex2f(lx, ly);
			for(l = 0; l <= ltriangleAmount; l++)
			{
				glVertex2f(
					lx + (lradius * cos(l * ltwicePi / ltriangleAmount)),
					ly + (lradius * sin(l * ltwicePi / ltriangleAmount))
				
				);
				
			}
		glEnd();
		glFlush();
		glFlush();
		
	//Roda Direita
	int z = 0;
	GLfloat zx = 2.5f;
	GLfloat zy = -2.80f; 
	GLfloat zradius = 0.5f; 
	int ztriangleAmount = 40; 
	
	GLfloat ztwicePi = 2.0f * PI;
	
	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(251.0f, 235.0f, 20.0f);
			glVertex2f(zx, zy);
			for(z = 0; z <= ztriangleAmount; z++)
			{
				glVertex2f(
					zx + (lradius * cos(z * ztwicePi / ztriangleAmount)),
					zy + (lradius * sin(z * ztwicePi / ztriangleAmount))
				
				);
				
			}
		glEnd();
		glFlush();
		glFlush();
		
	
//	glLineWidth(5);
//	glBegin(GL_LINES);
	//Alterar cor do personagem
	/*
	if(personagemcolor==0)
	{
	  //glColor3f(1.0f,0.0f,0.0f);
		glColor3f(1.0f, 0.0f, 0.0f);	
	}		
	else if(personagemcolor==1)
	{	
	 glColor3f(0.0f, 0.0f, 1.0f);
	}
	else
	 glColor3f(0.0f, 2.0f, 0.0f);
	*/
//	glColor3f(255, 121, 51);
//	glVertex2f(0.0,-3.0);
//	glVertex2f(0.0,5.0);
//	glEnd();
	
	
	
}



// Funçao que faz a colisão com a vacina
void ColisaoVacina(GLint  x)// aqui vai vir outro parametro, caso sejar verdadeiro tudo aquilo ali não entra,isso
{
    float px = vx;
    float py = vy;

    float obx = x;
    float oby = ky;
    
    if(px == x && py == oby)
	{		
		pontuacao+=10;	
		extra = 1;
	}
    else if(px == x+1 && py == oby)
    {
		pontuacao+=10;	
		extra = 1;
	}
    else if(px == x+1 && py == oby+1)
    {
		pontuacao+=10;	
		extra = 1;
	}
    else if(px == x+2 && py == oby+2)
    {
		pontuacao+=10;	
		extra = 1;
	}
    else if(px == x && py == oby+2)
    {
		pontuacao+=10;	
		extra = 1;
		
	}else if(px == x && py == oby+3)
    {
		pontuacao+=10;
		extra = 1;	
	
	}else if(px == x+1 && py == oby+3)
    {
		pontuacao+=10;	
		extra = 1;
	}
	else if(px == x+2 && py == oby+3)
    {
		pontuacao+=10;	
		extra = 1;
	}
	else if(px == x+3 && py == oby+3)
    {
		pontuacao+=10;	
		extra = 1;
	}

}





void Colisao(GLint  x, int ver)// Função responsavel pela colisão com os obstaculos 
{
    float px = tx;
    float py = ty;

    float obx = x;
    float oby = my;
    if(extra == 1){
    	bon1= 0.0f;
    	bon2 = 0.0f;
    	if(TimerBuff >= 20){
    		bon1 = 255.0f;
			bon2 = 1.0f;
			extra = 0;
    		TimerBuff = 0;
		}
    	
	}else{
		
	    if(px == x && py == oby)
		{
			pontuacao=0.0;
			GameOver(); 
		}
	    else if(px == x+1 && py == oby)
	    {
			pontuacao=0.0;
			GameOver(); 
		}
	    else if(px == x+1 && py == oby+1)
	    {
			pontuacao=0.0;
			GameOver(); 
		}
	    else if(px == x+2 && py == oby+2)
	    {
			pontuacao=0.0;
			GameOver(); 
		}
	    else if(px == x && py == oby+2)
	    {
			pontuacao=0.0;
			GameOver(); 
		}else if(px == x && py == oby+3)
	    {
			pontuacao=0.0;
			GameOver(); 
		}else if(px == x+1 && py == oby+3)
	    {
			pontuacao=0.0;
			GameOver(); 
		}
		else if(px == x+2 && py == oby+3)
	    {
			pontuacao=0.0;
			GameOver(); 
		}
		else if(px == x+3 && py == oby+3)
	    {
			pontuacao=0.0;
			GameOver(); 
		}
	}
}


void Colisaosup(GLint  x, int ver) // colisão com os obstaculos que estão no céu 
{
    float px = tx;
    float py = ty;

    float obx = x;
    float oby = ny;
    if(extra == 1){
    	if(TimerBuff >= 20){
			extra = 0;
    		TimerBuff = 0;
		}
    	
	}else{
	    if(px == x && py == oby)
		{
			pontuacao=0.0;
			GameOver(); 
		}
	    else if(px == x+1 && py+8 == oby)
	    {
			pontuacao=0.0;
			GameOver(); 
		}
	    else if(px == x+1 && py+8 == oby+1)
	    {
			pontuacao=0.0;
			GameOver(); 
		}
	    else if(px == x+2 && py+8 == oby+2)
	    {
			pontuacao=0.0;
			GameOver(); 
		}
	    else if(px == x && py+8 == oby+2)
	    {
			pontuacao=0.0;
			GameOver(); 
		}else if(px == x && py+8 == oby+3)
	    {
			pontuacao=0.0;
			GameOver(); 
		}else if(px == x+1 && py+8 == oby+3)
	    {
			pontuacao=0.0;
			GameOver(); 
		}
		else if(px == x+2 && py+8 == oby+3)
	    {
			pontuacao=0.0;
			GameOver(); 
		}
		else if(px == x+3 && py+8 == oby+3)
	    {
			pontuacao=0.0;
			GameOver(); 
		}
	}
}

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	


    if(estado == 0){
	// Muda para o sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa a matriz de transformação corrente
	glLoadIdentity();

	// Limpa a janela de visualização com a cor
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);
	
	//Desenha Ceu
	if(Alternar >= 20){
		t1 = 0.0f;
		t2 = 0.0f;
		t3 = 0.0f;
	}
	if(Alternar >= 40){	// De acordo com a distancia colocada aqui, ele vai mudando.
		t1 = 0.0f;
		t2 = 1.0f;
		t3 = 1.0f; 
		Alternar = 0;
	}
		glLineWidth(3);
		glBegin(GL_QUADS);
	        glColor3f(t1,t2,t3); // parametros de cor, ai quando der a distância programada eles mudam.
			glVertex2f(-100,-30);
			glVertex2f(100,-30);
			glVertex2f(-100,1500);
			glVertex2f(100,1500);
		glEnd();
		



    // Desenha o chão
    
		glLineWidth(3);
		glBegin(GL_QUADS);
	        glColor3f(cor1,cor2,cor3);
			glVertex2f(-100,-15);
			glVertex2f(100,-15);
			glColor3f(0.0f,0.0f,0.0f);
			glVertex2f(100,-30);
			glVertex2f(-100,-30);
		glEnd();
		
	
	
	//Desenha a Lua
	 glBegin(GL_TRIANGLE_FAN);
 	 glClear(GL_COLOR_BUFFER_BIT);
 	 
     //Lua de Baixo
     if(Alternar>=0 && Alternar <19.9)  
     {     	
     	q1 = 0.0f;
		q2 = 1.0f;
		q3 = 1.0f;	
		
	 }else if(Alternar>=20 && Alternar <39.9)
	 {
	 	q1 = 255.0f;
	 	q2 = 255.0f;
	 	q3 = 255.0f;
	 	
	 }else if(Alternar >= 40 && Alternar <60){
	 	q1 = 0.0f;
		q2 = 1.0f;
		q3 = 1.0f;
		
		Alternar = 0;
	 }
	 
	  glColor3f(q1,q2,q3);
     desenhaMeiaLua(8,8,16,16);
     
     //lua de Cima
     if(Alternar>=0 && Alternar <19.9)
     {
     	luaCima1 = 1.0f;
     	luaCima2 = 1.0f;
     	luaCima3 = 0.0f;
   	 }else if(Alternar>=20 && Alternar<39.9)
	 {
		luaCima1 = 0.0f;
		luaCima2 = 0.0f;
		luaCima3 = 0.0f; 
	 }else if(Alternar >= 40 && Alternar < 60){
	 	luaCima1 = 1.0f;
	 	luaCima2 = 1.0f;
	 	luaCima1 = 0.0f;
	 	
	 	Alternar = 0;
	 }
	 glColor3f(luaCima1,luaCima2,luaCima3);
     desenhaMeiaLua(8,8,19,19);
     glFlush();
	 glEnd();	
	
	
	// Desenha um objeto modelado com transformações hierárquicas
	//glPushMatrix e glPopMatrix são usados para salvar e restaurar o sistema de coordenadas não traduzido.
	glPushMatrix();
	glTranslatef(tx,ty,0.0f);

	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	DesenhaPersonagem();
    glPopMatrix();

   
    glPopMatrix();

   

    //Desenha obstaculos no chão
	
//Desenha vacina no chão

	glPushMatrix();
	glTranslatef(kx,ky,0.0f);
	glColor3f(0.0f,0.0f,0.0f);
    DesenhaVacina();
    ColisaoVacina(kx);
    glPopMatrix();
  
//
	
	glPushMatrix();
	glTranslatef(mx,my,0.0f);
	glColor3f(0.0f,0.0f,0.0f);
    DesenhaObstaculo();
	Colisao(mx,extra);
    glPopMatrix();
  
    glPushMatrix();
	glTranslatef(mx2,my,0.0f);
	glColor3f(0.0f,0.0f,0.0f);
    DesenhaObstaculo();	
    Colisao(mx2,extra);
    glPopMatrix();

    glPushMatrix();
	glTranslatef(mx3,my,0.0f);
	glColor3f(0.0f,0.0f,0.0f);
    DesenhaObstaculo();
	Colisao(mx3,extra);
    glPopMatrix();
	
	
	    
    //Desenha obstaculos no céu
	
	glPushMatrix();
	glTranslatef(nx,ny,0.0f);
	glColor3f(0.0f,0.0f,0.0f);
    DesenhaObstaculo();
    Colisaosup(nx,extra);
    glPopMatrix();

	glPushMatrix();
	glTranslatef(nx1,ny,0.0f);
	glColor3f(0.0f,0.0f,0.0f);
    DesenhaObstaculo();	
    Colisaosup(nx1,extra);
    glPopMatrix();
    
    
    // pontuação
    Pontuacao();
    
	// Executa os comandos OpenGL
	glutSwapBuffers();
    }
}




// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;

	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as variáveis
	largura = w;
	altura = h;

	// Especifica as dimensões da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (esquerda, direita, inferior,
	// superior) mantendo a proporção com a janela de visualização
	if (largura <= altura)
	{
		gluOrtho2D (-25.0f, 25.0f, -25.0f*altura/largura, 25.0f*altura/largura);
		win = 25.0f;
	}
	else
	{
		gluOrtho2D (-25.0f*largura/altura, 25.0f*largura/altura, -25.0f, 25.0f);
		win = 25.0f*largura/altura;
	}
}



void TeclasEspeciais(int key, int x, int y)
{

	if(key == GLUT_KEY_UP)
	{
	    if(ty == -12)
            glutTimerFunc(20,Pular1,1);
	}

	glutPostRedisplay();
}



// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(0.10f, 0.77f, 1.0f, 1.0f);

}



///////////////////////////////////////////////////
void DesenhaTexto(char *string) 
{  
  	glPushMatrix();
        // Posição no universo onde o texto será colocado          
        glRasterPos2f(-win,win-(win*0.08)); 
        // Exibe caracter a caracter
        while(*string)
             glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,*string++); 
	glPopMatrix();
}


void AlteraTamanhoJanela2(GLsizei w, GLsizei h)
{ 
 
    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D (-wine, wine, -wine, wine);
}

void TeclasEspeciais2(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
           wine -= 10;
           if (wine < 10) wine = 10;
           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           gluOrtho2D (-wine, wine, -wine, wine);
    }
    if(key == GLUT_KEY_DOWN) {
           wine += 10;
           if (wine > 500) wine = 500;
           glMatrixMode(GL_PROJECTION);
           glLoadIdentity();
           gluOrtho2D (-wine, wine, -wine, wine);
    }
    glutPostRedisplay();
}

////////////////////////


 void LoadBMP(char *filename) {
    #define SAIR {fclose(fp_arquivo); return ;}
    #define CTOI(C) (*(int*)&C)
 
    GLubyte *image;
    GLubyte Header[0x54];
 
    FILE * fp_arquivo = fopen(filename,"rb");
 
    if (fread(Header,1,0x36,fp_arquivo)!=0x36)
    SAIR;
 
    Width = CTOI(Header[0x12]);
    Height = CTOI(Header[0x16]);
    ( CTOI(Header[0x0A]) == 0 ) ? ( DataPos=0x36 ) : ( DataPos = CTOI(Header[0x0A]) );
    imageSize=Width*Height*3;
 
    image = (GLubyte *) malloc ( imageSize );
    int retorno;
    retorno = fread(image,1,imageSize,fp_arquivo);
 
    int t, i;
    for ( i = 0; i < imageSize; i += 3 ) {
        t = image[i];
        image[i] = image[i+2];
        image[i+2] = t;
    }
 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    fclose (fp_arquivo);
    free (image);
    return ;
}
 
void T_Quads(GLuint *t_quad, int i, int x, int y, int w, int h) {
    glBindTexture ( GL_TEXTURE_2D, t_quad[i] );
    glBegin(GL_QUADS);
 
    glTexCoord2f(0.0f, 0.0f);  glVertex2f(x, y);
    glTexCoord2f(1.0f, 0.0f);  glVertex2f(x+w, y);
    glTexCoord2f(1.0f, 1.0f);  glVertex2f(x+w, y+h);
    glTexCoord2f(0.0f, 1.0f);  glVertex2f(x, y+h);
    glEnd();
}
 // Desenho da tela iniciaç
void Draw(void) {
 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glViewport(0,0,win_width,win_height);
    glEnable (GL_TEXTURE_2D);
    gluOrtho2D (0,win_width, 0, win_height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 
    glGenTextures ( 1, texture_id );
    glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
 
    LoadBMP("TelaInicialNovo.bmp");
    T_Quads( texture_id, 0, 0, 0, win_width, win_height);
 
    glutSwapBuffers();
}
// Desenho da tela de comandos
void Draw2(void) {
 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glViewport(0,0,win_width,win_height);
    glEnable (GL_TEXTURE_2D);
    gluOrtho2D (0,win_width, 0, win_height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 
    glGenTextures ( 1, texture_id );
    glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
 
    LoadBMP("comandosNovo.bmp");
    T_Quads( texture_id, 0, 0, 0, win_width, win_height);
 
    glutSwapBuffers();
}
// Desenho da tela sobre o jogo
void Draw3(void) {
 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glViewport(0,0,win_width,win_height);
    glEnable (GL_TEXTURE_2D);
    gluOrtho2D (0,win_width, 0, win_height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 
    glGenTextures ( 1, texture_id );
    glBindTexture ( GL_TEXTURE_2D, texture_id[0] );
 
    LoadBMP("sobreojogo.bmp");
    T_Quads( texture_id, 0, 0, 0, win_width, win_height);
 
    glutSwapBuffers();
}


 
void Anima(int value) {
 
    glutPostRedisplay();
    glutTimerFunc(120,Anima, 1);
 
}
 // Função de recebimento de informações do mouse
void MouseManager(int button, int state, int x, int y) {
 
    glutPostRedisplay();
}
 
void SpecialKeys(int key, int x, int y){
 
    glutPostRedisplay();
}
 
void ModifyWindownsSize(GLsizei w, GLsizei h) {
    if(h == 0) h = 1;
 
    win_width = w;
    win_height = h;
 
    aspecto = (float) win_width/win_height;
 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
 
    gluOrtho2D (-winw*aspecto, winw*aspecto, -winw, winw);
}
 // inicialização do jogo
void Start (void) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    winw = 50.0f;
}

//teclas
void Teclado( unsigned char key, int x, int y)
{
		
	switch(key)
	{
		case 27:
			exit(0);
			break;
		case 'I':
		case 'i':
			iniciando();			
			break;
		case 13:
			tx = -40, ty = -12;
			mx = 120, mx2 = 200, mx3 = 300, my = -12, ny=10 ,nx =500, nx1= 800;
			win = 25;
			temp = 30;
			estado = 0;
			pontuacao=0.0;
			break;	
		case 'P':
		case 'p':
			Pause();
			glutPostRedisplay();
			break;
		case 'R':
		case 'r':
		pontuacao=aux;
		estado=0;
			break;
		}	
		
	glutPostRedisplay();	
}

// Gerenciamento do menu principal           


/*
void menu(int num){
	if(num == 0){
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3d(1.0,1.0,1.0);
		exit(0);
	}
	else{
		value = num;
		
	}
	glutPostRedisplay();
}
*/
void menu(int key1)
{	
	switch(key1)
	{
		case 1: //Iniciar
		tx = -40, ty = -12;
			mx = 120, mx2 = 200, mx3 = 300, my = -12, ny=10 ,nx =500, nx1= 800;
			win = 25;
			temp = 30;
			estado = 0;
			pontuacao=0.0;

				jogo();				
			
			break;
		
		case 2: //Sobre o Jogo
		    SobreJogo();
			break;
		    
		case 3: //Comandos    
			comandos();
			break;
		case 4: exit(0);
		    break;	
	}	
}

void mudarTerreno(int key2)  //Mudar terreno do jogo
{
	switch(key2)
	{
		case 1:	
			cor1 = 1.5f;
			cor2 = 1.0f;
			cor3 = 0.5f; 
			break;
		case 2:
			cor1= 1.32f;
			cor2= 0.3f;
			break;
	}
}

void mudarCor(int key3)  //Mudar cor do jogo
{
	switch(key3)
	{
		case 1:	
		    covidcolor = 0;
			break;
		case 2:	
		    covidcolor = 1;
			break;
		case 3:	
		    covidcolor = 2;
			break;
	}
}	



              
// Criacao do Menu
void menuSystem() 
{

    
    mudarTerrenoID = glutCreateMenu(mudarTerreno);
    glutAddMenuEntry("Deserto",1);
	glutAddMenuEntry("Arid",2);
    
    
    mudarCorID = glutCreateMenu(mudarCor);
    glutAddMenuEntry("Vermelho",1);
	glutAddMenuEntry("Azul",2);
	glutAddMenuEntry("Verde",3);
	
	
    glutCreateMenu(menu);
    glutAddMenuEntry("Iniciar",1);
    glutAddSubMenu("Ambiente",mudarTerrenoID);
    glutAddSubMenu("Cor do Virus",mudarCorID);
    glutAddMenuEntry("Sobre o Jogo",2);
    glutAddMenuEntry("Comandos",3);
    glutAddMenuEntry("Sair",4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{        
    if (button == GLUT_RIGHT_BUTTON)
         if (state == GLUT_DOWN) 
            menuSystem();
         
    glutPostRedisplay();
}











// jogo
	
void jogo()
{

			glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
			glutInitWindowPosition(5,5);
			glutInitWindowSize(1200,500);
			glutCreateWindow("Covid Scape");
			glutDisplayFunc(Desenha);
			glutReshapeFunc(AlteraTamanhoJanela);
			glutKeyboardFunc (Teclado);
			glutSpecialFunc(TeclasEspeciais);   
		    glutTimerFunc(60, Timer, 1);
			Inicializa();
			glutMainLoop();
			
					

}

// tela inicio

void iniciando()
{
		    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
		    glutInitWindowPosition(5,5);
		    glutInitWindowSize(1200,500);
		    glutCreateWindow("Covid Scape");
		    glutReshapeFunc(ModifyWindownsSize);
		    glutDisplayFunc(Draw);
		    glutMouseFunc(MouseManager);
		    glutSpecialFunc(SpecialKeys);
		    glutTimerFunc(150, Anima, 1);
		    Start();
			glutSpecialFunc(TeclasEspeciais2); 
			glutMouseFunc(GerenciaMouse);    
		    glutMainLoop();
}

void comandos()
{
		    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
			glutInitWindowPosition(5,5);
			glutInitWindowSize(1200,500);
			glutCreateWindow("Covid Scape");
			glutDisplayFunc(Draw2);
			glutReshapeFunc(ModifyWindownsSize);
			glutMouseFunc(MouseManager);
			glutSpecialFunc(SpecialKeys);
			glutTimerFunc(150, Anima, 1);
			Start();
			glutSpecialFunc(TeclasEspeciais2);    
			glutKeyboardFunc (Teclado);
			glutMainLoop();	

}


void SobreJogo()
{
		    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
			glutInitWindowPosition(5,5);
			glutInitWindowSize(1200,500);
			glutCreateWindow("Covid Scape");
			glutDisplayFunc(Draw3);
			glutReshapeFunc(ModifyWindownsSize);
			glutMouseFunc(MouseManager);
			glutSpecialFunc(SpecialKeys);
			glutTimerFunc(150, Anima, 1);
			Start();
			glutSpecialFunc(TeclasEspeciais2);    
			glutKeyboardFunc (Teclado);
			glutMainLoop();	

}


// Programa Principal
int main(int argc,char **argv)
{	
	glutInit(&argc,argv);
	iniciando();
	menuSystem();
    
	return 0;
}





