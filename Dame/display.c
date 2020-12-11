#include "checkers.h"
//CODE D'AFFICHAGE GLUT

//VARIABLES////////////////////////

int message=-1;
int victoire = 0;

float squaresize = 0.18;
float xborder = 0.1;
float yborder = 0.1;

int xx=0;
int yy=0;

int xx2=0;
int yy2=0;

int time1;
float speed = 1.0f;
int blink = 100000;

int choosingpiece = 1;
int graby,grabx,placey,placex;

float move_unit = 0.18f;

int menu=1;
int hints=-1;
int selected=-1;

int selectedx;
int selectedy;

//FONCTIONS/////////////////////////



void gameoverman(){

  printf("GMMMOVR\n");
 
  int i;
  float x1,y1;

  char noir[]="NOIR";
  char rouge[]="ROUGE";
  char player[]="JOUEUR";//TOUR DU JOUEUR
  char won[]="A GAGNE!!";
  char cont[]="REJOUER? Y/N";
  char tie[]="MATCH NUL!";

  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.0, 0.0);
  glVertex2f(-0.6, 0.6);
  glVertex2f(-0.6, -0.6);
  glVertex2f(0.6, -0.6);
  glVertex2f(0.6, 0.6);
  glEnd();


  glColor3f(1.0,1.0,1.0);

  if(victoire==3){
    for(x1=-0.37, y1=0.3, i=0 ; i<10; i++, x1+=0.08){//GAUCHE
      glRasterPos2f(x1,y1);
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, tie[i]);
    }
  }
 

 

  
  if(victoire==1 || victoire==2){
    for(x1=-0.37, y1=0.3, i=0 ; i<6; i++, x1+=0.08){//GAUCHE
      glRasterPos2f(x1,y1);
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, player[i]);
    }

    for(x1=-0.3, y1=-0.0, i=0 ; i<9; i++, x1+=0.08){//DROITE
      glRasterPos2f(x1,y1);
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, won[i]);
    }
  }

  if(victoire==2){
    for(x1=-0.0, y1=0.15, i=0 ; i<4; i++, x1+=0.08){//GAUCHE
      glRasterPos2f(x1,y1);
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, noir[i]);
    }
  }


  if(victoire==1){
    for(x1=-0.0, y1=0.15, i=0 ; i<5; i++, x1+=0.08){//GAUCHE
      glRasterPos2f(x1,y1);
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, rouge[i]);
    }
  }

  if(victoire>0){
    for(x1=-0.45, y1=-0.35, i=0 ; i<12; i++, x1+=0.08){//DROITE
      glRasterPos2f(x1,y1);
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, cont[i]);
    }
  }

}





void display_menu(){

  int n;

  char ligne1[]="MANUAL";
  char ligne2[]="Utilisez les fleches pour deplacer le curseur de selection.";
  char ligne3[]="Utilisez la barre d'espace pour (de)selectionner une case.";
  char ligne4[]="Le jeu vous oblige a faire la meilleure suite de coups.";
  char ligne5[]="Soyez attentif aux informations situees au dessus du plateau.";
  char ligne6[]="Pour afficher ou enlever les indices, appuyez sur H.";
  char ligne7[]="Pour quitter ou revenir sur le menu appuyez sur M.";
  char ligne8[]="Cree par Emmanuel, Theo, Thomas et Adil.";

  //background
  //middle
  glBegin(GL_POLYGON);
  glColor3f(0.0, 0.0, 0.0);
  glVertex2f(-1.0,-0.9);
  glVertex2f(-1.0,0.9);
  glVertex2f(1.0, 0.9);
  glVertex2f(1.0, -0.9);
  glEnd();

  glColor3f(1.0, 1.0, 1.0);
  //top
  glBegin(GL_POLYGON);
  glVertex2f(1.0,1.0);
  glVertex2f(-1.0,1.0);
  glVertex2f(-1.0, 0.9);
  glVertex2f(1.0, 0.9);
  glEnd();
  //bottom
  glBegin(GL_POLYGON);
  glVertex2f(1.0,-0.9);
  glVertex2f(-1.0,-0.9);
  glVertex2f(-1.0, -1.0);
  glVertex2f(1.0, -1.0);
  glEnd();

  //text

  glColor3f(0.0, 0.0, 0.0);
  glRasterPos2f(-0.11,0.93);
  for(n=0 ; n<6; n++){
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne1[n]);
  }

  glColor3f(1.0, 1.0, 1.0);
  glRasterPos2f(-0.8,0.64);
  for(n=0 ; n<59; n++){
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne2[n]);
  }

  glRasterPos2f(-0.8,0.39);
  for(n=0 ; n<58; n++){
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne3[n]);
  }

  glRasterPos2f(-0.8,0.14);
  for(n=0 ; n<55; n++){
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne4[n]);
  }

  glRasterPos2f(-0.8, -0.11);
  for(n=0 ; n<53; n++){
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne6[n]);
  }

  glRasterPos2f(-0.8, -0.36);
  for(n=0 ; n<53; n++){
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne7[n]);
  }

  glColor3f(1.0, 0.0, 0.0);
  glRasterPos2f(-0.8,-0.61);
  for(n=0 ; n<63; n++){
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne5[n]);
  }

  glColor3f(0.0, 0.0, 0.0);
  glRasterPos2f(-0.8,-0.97);
  for(n=0 ; n<40; n++){
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, ligne8[n]);
  }
}






void displayboard(void){

  int i,j;

  float x1,x2,y1,y2;

  char noir[]="NOIR";
  char rouge[]="ROUGE";
  //  char nombre[]="0123456789";
  char piece[]="VOUS DEVEZ PRENDRE   PIECE(S).";//NOMBRE PIECES A PRENDRE
  char player[]="TOUR DU JOUEUR ";//TOUR DU JOUEUR


  x1 = -1 + xborder;

  y1 = 1 - yborder;

  //  float squaresize = y1/5;

  
  for(j=0;j<5;j++){

    
    for(i=0;i<10;i++){
 
      x2 = x1+squaresize;
      y2 = y1-squaresize;

      if(i%2==0){
	glColor3f(0.9, 0.9, 0.8);
      } else {
	glColor3f(0.50, 0.22, 0);
      }
      glBegin(GL_QUADS);
      glVertex2f(x2,y1);
      glVertex2f(x1,y1);
      glVertex2f(x1,y2);
      glVertex2f(x2,y2);
      glEnd();

      x1 += squaresize;
    
    }
      
    x1 = -1 + xborder;

    y1 -= squaresize;
      

    for(i=0;i<10;i++){
 
      x2 = x1+squaresize;
      y2 = y1-squaresize;

      if(i%2==1){
	glColor3f(0.9, 0.9, 0.8);
      } else {
	glColor3f(0.50, 0.22, 0);
      }
      glBegin(GL_QUADS);
      glVertex2f(x2,y1);
      glVertex2f(x1,y1);
      glVertex2f(x1,y2);
      glVertex2f(x2,y2);
      glEnd();

      x1 += squaresize;
    }

      
    x1 = -1 + xborder;

    y1 -= squaresize;
  }

  glColor3f(1.0,1.0,1.0);


  /*for(x1=-0.83, y1=0.93, i=0 ; i<11; i++, x1+=0.18){//HAUT
    glRasterPos2f(x1,y1);  	
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, lettre[i]);
    }*/

  /*
  for(x1=-0.97, y1=0.8, i=0 ; i<11; i++, y1-=0.18){//GAUCHE
    glRasterPos2f(x1,y1);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, nombre[i]);
  }

  for(x1=0.93, y1=0.8, i=0 ; i<11; i++, y1-=0.18){//DROITE
    glRasterPos2f(x1,y1);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, nombre[i]);
  }

  */

  if(message==6)
    glColor3f(1.0,0,0);

  glRasterPos2f(-0.9,-0.97); 
  for(i=0 ; i<16; i++){	
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, player[i]);
  }
  
  glRasterPos2f(-0.42,-0.97);
  if(game.player==1){
    for(i=0; i<6; i++){
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, rouge[i]);
    }
  }
  else{
    for(i=0; i<5; i++){
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, noir[i]);
    }
  }

  glColor3f(1.0,1.0,1.0);
  piece[19]=(char) max+49;

  if(message==5 || message==2 || message==7)
    glColor3f(1.0,0.0,0.0);
  
  if (game.score!=0){
    glRasterPos2f(0,-0.97);
    for(i=0 ; i<30; i++){	
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, piece[i]);
    }
  }

}

void displayMessage(){//MESSAGES UTILISATEUR

  int n;
  char message0[]="CETTE CASE EST EN DEHORS DU PLATEAU";
  char message1[]="CETTE CASE EST DEJA PRISE";
  char message2[]="CE MOUVEMENT N'EST PAS OPTIMAL";
  char message3[]="MOVE IMPOSSIBLE";
  char message4[]="IL N'Y A PAS DE PIECE SUR CETTE CASE";
  char message5[]="LA PIECE NE FAIT PAS PARTIE DU COUP OPTIMAL";
  char message6[]="CETTE PIECE NE VOUS APPARTIENT PAS";
  char message7[]="AUCUN COUP POSSIBLE AVEC LA PIECE CHOISIE OU CASE CHOISIE INVALIDE";
  char message8[]="EGALITE";
  char message9[]="VICTOIRE J1";
  char message10[]="VICTOIRE J2";

  glColor3f(1,1,1);
  glRasterPos2f(-0.9,0.93);
  

  

  switch(message){

  case 0: 
    for(n=0 ; n<34; n++){ 
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message0[n]);
    }
    break;

  case 1: 
    for(n=0 ; n<25; n++){ 
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message1[n]);
    }
    break;

  case 2: 
    for(n=0 ; n<30; n++){ 
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message2[n]);
    }
    break;

  case 3: 
    for(n=0 ; n<15; n++){ 
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message3[n]);
    }
    break;

  case 4: 
    for(n=0 ; n<36; n++){ 
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message4[n]);
    }
    break;

  case 5: 
    for(n=0 ; n<43; n++){ 
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message5[n]);
    }
    break;

  case 6: 
    for(n=0 ; n<34; n++){ 
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message6[n]);
    }
    break;

  case 7: 
    for(n=0 ; n<66; n++){ 
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message7[n]);
    }
    break;

  case 8: 
    for(n=0 ; n<7; n++){ 
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message8[n]);
    }
    break;

  case 9: 
    for(n=0 ; n<11; n++){ 
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message9[n]);
    }
    break;

  case 10: 
    for(n=0 ; n<11; n++){ 
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message10[n]);
    }
    break;
  }
}


void rect(){

  /*
    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, -0.5);
    glEnd();

  */


  /*
  
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 0.0);
    glVertex2f(-1+xborder+posX, 1-yborder+posY);
    glVertex2f(-1.0+xborder+posX, 1-yborder-squaresize+posY);
    glVertex2f(-1+xborder+squaresize+posX, 1-yborder-squaresize+posY);
    glVertex2f(-1+xborder+squaresize+posX, 1-yborder+posY);
    glEnd();

  */



  glBegin(GL_POLYGON);
  glColor3f(1.0, 1.0, 0.65);
  glVertex2f(-1+xborder+squaresize*(float)xx, 1-yborder-squaresize*(float)yy);
  glVertex2f(-1.0+xborder+squaresize*(float)xx, 1-yborder-squaresize-squaresize*(float)yy);
  glVertex2f(-1+xborder+squaresize+squaresize*(float)xx, 1-yborder-squaresize-squaresize*(float)yy);
  glVertex2f(-1+xborder+squaresize+squaresize*(float)xx, 1-yborder-squaresize*(float)yy);
  glEnd();
 
}



void selectedrect(){
  glBegin(GL_POLYGON);
  glColor3f(1.0, 1.0, 0.65);
  glVertex2f(-1+xborder+squaresize*(float)selectedx, 1-yborder-squaresize*(float)selectedy);
  glVertex2f(-1.0+xborder+squaresize*(float)selectedx, 1-yborder-squaresize-squaresize*(float)selectedy);
  glVertex2f(-1+xborder+squaresize+squaresize*(float)selectedx, 1-yborder-squaresize-squaresize*(float)selectedy);
  glVertex2f(-1+xborder+squaresize+squaresize*(float)selectedx, 1-yborder-squaresize*(float)selectedy);
  glEnd();
}

void animate(int value) {
  glutTimerFunc(speed, animate, 0);
  time1++;
  if (time1 >= blink)
    time1 = 0;        // time is in tenths of a second
  glutPostRedisplay();
}


void movepiece(){



  if(choosingpiece==-1){
    graby=(int)yy;
    grabx=(int)xx;
    printf("\nGRAB yy=%d xx=%d\n", (int)yy, (int)xx);
  }

  if(choosingpiece==1){
    placey=(int)yy;
    placex=(int)xx;

    printf("\nPLACE yy=%d xx=%d\n", (int)yy, (int)xx);
    
    game.board[placey][placex]=game.board[graby][grabx];
    game.board[graby][grabx]=0;
    
  }
}


void showpieces(checkers game){

  int j,k;
  int edges = 25;
  float radius = 0.07;
  float crownx, crowny;
  
  GLfloat centerx, centery, temp;

  float squaresize = 0.18;

  for(j=0 ; j<10 ; j++){
    for(k=(j+1)%2 ; k<10 ; k+=2){	  
      if(game.board[j][k]==1){
	glColor3f(0.8, 0, 0);
	glBegin(GL_POLYGON);
	temp = 360.0 / (float)edges;
	for(float i = 0; i < 360; i+=temp){
	  centerx = radius * cos(i * M_PI / 180.0f) - 4.5 * squaresize;
	  centery = radius * sin(i * M_PI / 180.0f) + 3.5 * squaresize;

	  centerx += squaresize*k;
	  centery -= squaresize*(j-1);
	
	  glVertex2f(centerx, centery);
	  centerx = 0;
	  centery = 0;
	}
	glEnd();
      }
      if(game.board[j][k]==3){
	glColor3f(0.8, 0, 0);
	glBegin(GL_POLYGON);
	temp = 360.0 / (float)edges;
	for(float i = 0; i < 360; i+=temp){
	  centerx = radius * cos(i * M_PI / 180.0f) - 4.5 * squaresize;
	  centery = radius * sin(i * M_PI / 180.0f) + 3.5 * squaresize;

	  centerx += squaresize*k;
	  centery -= squaresize*(j-1);
	
	  glVertex2f(centerx, centery);
	  centerx = 0;
	  centery = 0;
	}
	glEnd();
      }
      if(game.board[j][k]==2){
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	temp = 360.0 / (float)edges;
	for(float i = 0; i < 360; i+=temp){
	  centerx = radius * cos(i * M_PI / 180.0f) - 4.5 * squaresize;
	  centery = radius * sin(i * M_PI / 180.0f) + 4.5 * squaresize;

	  centerx += squaresize*k;
	  centery -= squaresize*j;
	
	  glVertex2f(centerx, centery);
	  centerx = 0;
	  centery = 0;
	}
	glEnd();
      }
      if(game.board[j][k]==4){
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	temp = 360.0 / (float)edges;
	for(float i = 0; i < 360; i+=temp){
	  centerx = radius * cos(i * M_PI / 180.0f) - 4.5 * squaresize;
	  centery = radius * sin(i * M_PI / 180.0f) + 4.5 * squaresize;

	  centerx += squaresize*k;
	  centery -= squaresize*j;
	
	  glVertex2f(centerx, centery);
	  centerx = 0;
	  centery = 0;
	}
	glEnd();
      }
      if(game.board[j][k]==-1){
	glColor3f((0.50*3+0.8*3)/6, 0.22/1.5, 0/1.5);
	glBegin(GL_POLYGON);
	temp = 360.0 / (float)edges;
	for(float i = 0; i < 360; i+=temp){
	  centerx = radius * cos(i * M_PI / 180.0f) - 4.5 * squaresize;
	  centery = radius * sin(i * M_PI / 180.0f) + 4.5 * squaresize;

	  centerx += squaresize*k;
	  centery -= squaresize*j;
	
	  glVertex2f(centerx, centery);
	  centerx = 0;
	  centery = 0;
	}
	glEnd();
      }
      if(game.board[j][k]==-2){
	glColor3f(0.50/1.5, 0.22/1.5, 0/1.5);
	glBegin(GL_POLYGON);
	temp = 360.0 / (float)edges;
	for(float i = 0; i < 360; i+=temp){
	  centerx = radius * cos(i * M_PI / 180.0f) - 4.5 * squaresize;
	  centery = radius * sin(i * M_PI / 180.0f) + 4.5 * squaresize;

	  centerx += squaresize*k;
	  centery -= squaresize*j;
	
	  glVertex2f(centerx, centery);
	  centerx = 0;
	  centery = 0;
	}
	glEnd();
      }
      if(game.board[j][k]==3 || game.board[j][k]==4){

	crownx=-0.81+k*squaresize;
	crowny=0.82-j*squaresize;

	glColor3f(1.0, 0.83, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(crownx+0.001,crowny+0.06);
	glVertex2f(crownx+0.02,crowny+0.04);
	glVertex2f(crownx+0.055,crowny+0.05);
	glVertex2f(crownx+0.06,crowny+0.078);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(crownx-0.06,crowny+0.078);
	glVertex2f(crownx-0.055,crowny+0.05);
	glVertex2f(crownx-0.02,crowny+0.04);
	glVertex2f(crownx-0.01,crowny+0.06);
	glEnd();
  
	glColor3f(1.0, 0.923, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(crownx,crowny+0.08);
	glVertex2f(crownx-0.055,crowny+0.02);
	glVertex2f(crownx,crowny+0.01);
	glVertex2f(crownx+0.055,crowny+0.02);
	glEnd(); 
  
	glBegin(GL_POLYGON);
	glVertex2f(crownx+0.03,crowny+0.015);
	glVertex2f(crownx+0.065,crowny+0.025);
	glVertex2f(crownx+0.085,crowny+0.06);
	glVertex2f(crownx+0.01,crowny+0.04);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex2f(crownx-0.01,crowny+0.04);
	glVertex2f(crownx-0.085,crowny+0.06);
	glVertex2f(crownx-0.065,crowny+0.025);
	glVertex2f(crownx-0.03,crowny+0.015);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(crownx-0.01,crowny+0.04);
    glVertex2f(crownx-0.01,crowny+0.02);
    glVertex2f(crownx+0.01,crowny+0.02);
    glVertex2f(crownx+0.01,crowny+0.04);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(crownx-0.01,crowny+0.04);
    glVertex2f(crownx-0.01,crowny+0.02);
    glVertex2f(crownx+0.01,crowny+0.02);
    glVertex2f(crownx+0.01,crowny+0.04);
    glEnd();
  
      }
    } 
  }	
}


void display(){

  //printf("Victoire == %d\n", victoire);
  //printf("%d %d %d %d\n",game.stock1, game.stock2, game.queen1, game.queen2);

  glClear(GL_COLOR_BUFFER_BIT);

  if(menu==1){
    display_menu();
  }

  

  else{

    displayboard();
    
    if(hints==1)
      show();

    rect();


    if (choosingpiece==-1){
      if (time1 > 300)
	selectedrect();
    }
    
    showpieces(game);
    // crown();
    //gameoverman();

    if(message!=-1)
      displayMessage();

    if(victoire>0){
      gameoverman();
    }
      
  }
  glFlush();
}

void init(){
  // set clear color to black
  glClearColor(0.0, 0.0, 0.0, 0.0);

  // set fill color to white
  glColor3f(1.0, 1.0, 1.0);
}

void keyboardown(int key, int x, int y)
{
  switch (key){
  case GLUT_KEY_RIGHT:
    xx+=1.0;
    if(xx>9)
      xx=0;
    xx2+=1.0;
    if(xx2>9)
      xx2=0;
    break;

  case GLUT_KEY_LEFT:
    xx-=1.0;
    if(xx<0)
      xx=9;
    xx2-=1.0;
    if(xx2<0)
      xx2=9;
    break;

  case GLUT_KEY_UP:
    yy-=1.0;
    if(yy<0)
      yy=9.0;
    yy2-=1.0;
    if(yy2<0)
      yy2=9.0;
    break;

  case GLUT_KEY_DOWN:
    yy+=1.0;
    if(yy>9.0)
      yy=0;
    yy2+=1.0;
    if(yy2>9.0)
      yy2=0;
    break;
    
  case GLUT_KEY_END:

    choosingpiece*=-1;
    movepiece();

    
    break;

  default:
    break;
  }
  message=-1;
  glutPostRedisplay();
}










void processNormalKeys(unsigned char key, int x, int y) {


  if (key == ' ' && (choosingpiece==1) && choicePiecePossible()==1 && victoire==0){

    m.x1 = xx;//
    m.y1 = yy;

    
    
    m.type_piece = game.board[yy][xx];

    printf("\nm.x1=%d  m.y1=%d \n", m.x1, m.y1);
    printf("\nm.x2=%d  m.y2=%d \n", m.x2, m.y2);

    selectedx=xx;
    selectedy=yy;


    selected*=-1;
    choosingpiece*=-1;
    tabl_move_possible();


  }

  else if (key==' ' && xx2==m.x1 && yy2==m.y1 && victoire==0){
    choosingpiece *= -1;
  }

  else if (key==' ' && victoire==0){
    
    printf("\nxx2 == %d, yy2 == %d\n",xx2,yy2);
    m.x2 = xx2;
    m.y2 = yy2;
    reset_tabl();
    if ((choosingpiece==-1) && chooseMovePossible()==1){

      printf("\nm.x1=%d  m.y1=%d \n", m.x1, m.y1);
      printf("\nm.x2=%d  m.y2=%d \n", m.x2, m.y2);

      actualisation_board();
      createQueen(game);

      if(game.score<2){
	remove_pieces();
	game.player=game.player%2+1;
	victoire = win();
      }

      
      game.t = make_tree(game.t, game);
      profondeur(game.t);
      game.score = afficher_score(*(game.t));

      choosingpiece*=-1;

    }
    createQueen(game);
    game.t = make_tree(game.t, game);
    game.score=0;
    profondeur(game.t);
    game.score = afficher_score(*(game.t));
    tabl_piece_possible();
  }

  if(choosingpiece==-1){
    blink=600;
    //    tabl_piece_possible();
  }else{
    blink=100000;
    //    reset_tabl;
  }

  if (key=='m')
    menu*=-1;
  
  if (key=='h')
    hints*=-1;
  
  if (key==27){
    exit(0);
  }

  if (key=='y'){
    if(victoire>0){
      message=-1;
      xx=0;
      yy=0;
      xx2=0;
      yy2=0;
      victoire = 0;
      initboard();
      game = initpieces(game);
      m = initMove(m);
      game.t = make_tree(game.t, game);
      game.score = 0;
      printf("\n\n m.x1=%d m.y1=%d \n\n", m.x1, m.y2);
      tabl_piece_possible();
    
      
    }
  }

  // DEVELOPER MODE FOR TESTING. TYPE % TO ACTIVATE

  if (key=='%')
    developer_mode*=-1;

  
  if (key=='f'){
    if(developer_mode==1)
      game.stock1--;
  }


  if (key=='g'){
    if(developer_mode==1)
      game.stock2--;
  }

  //CHANGE ANY PIECE TO A QUEEN
  
  if (key=='q'){
    if(developer_mode==1){
      if(game.board[yy][xx]==1){
	game.board[yy][xx]+=2;
	game.queen1++;
      }
      if(game.board[yy][xx]==2){
	game.board[yy][xx]+=2;
	game.queen2++;
      }
    }
  }
  
  if (key=='n'){
    if(victoire>0)
      exit(0);
  }



  glutPostRedisplay();
}


void crown(){

  float x=-0.09;
  float y=0.27;

  glColor3f(1.0, 0.83, 0.0);
  glBegin(GL_POLYGON);
  glVertex2f(x+0.001,y+0.06);
  glVertex2f(x+0.02,y+0.04);
  glVertex2f(x+0.055,y+0.05);
  glVertex2f(x+0.06,y+0.078);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(x-0.06,y+0.078);
  glVertex2f(x-0.055,y+0.05);
  glVertex2f(x-0.02,y+0.04);
  glVertex2f(x-0.01,y+0.06);
  glEnd();
  
  glColor3f(1.0, 0.923, 0.0);
  glBegin(GL_POLYGON);
  glVertex2f(x,y+0.08);
  glVertex2f(x-0.055,y+0.02);
  glVertex2f(x,y+0.01);
  glVertex2f(x+0.055,y+0.02);
  glEnd(); 
  
  glBegin(GL_POLYGON);
  glVertex2f(x+0.03,y+0.015);
  glVertex2f(x+0.065,y+0.025);
  glVertex2f(x+0.085,y+0.06);
  glVertex2f(x+0.01,y+0.04);
  glEnd();

  glBegin(GL_POLYGON);
  glVertex2f(x-0.01,y+0.04);
  glVertex2f(x-0.085,y+0.06);
  glVertex2f(x-0.065,y+0.025);
  glVertex2f(x-0.03,y+0.015);
  glEnd();

  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POLYGON);
  glVertex2f(x-0.01,y+0.02);
  glVertex2f(x-0.01,y+0.01);
  glVertex2f(x+0.01,y+0.02);
  glVertex2f(x+0.01,y+0.01);
  glEnd();


  
}







void show(){

  int j,i;


  
  for(j=0;j<10;j++){
    for(i=0;i<10;i++){
      if(tabl_piece[j][i]==1){
	glBegin(GL_POLYGON);
	glColor3f(0.50, 0.42, 0.2);
	glVertex2f(-1+xborder+squaresize*(float)i, 1-yborder-squaresize*(float)j);
	glVertex2f(-1.0+xborder+squaresize*(float)i, 1-yborder-squaresize-squaresize*(float)j);
	glVertex2f(-1+xborder+squaresize+squaresize*(float)i, 1-yborder-squaresize-squaresize*(float)j);
	glVertex2f(-1+xborder+squaresize+squaresize*(float)i, 1-yborder-squaresize*(float)j);
	glEnd();
      }
    }
  }
}
 

