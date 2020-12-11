#include "checkers.h"
//FONCTIONS QUI ORCHESTRE LE JEU

checkers game;
move m;
int max;
int winner;
int tabl_piece[10][10];
int developer_mode=-1;


move initMove(move m){

  m.x1 = -1;
  m.y1 = -1;
  m.x2 = -1;
  m.y2 = -1;
  m.type_piece = -1;
  m.prise = -1;
  m.x3 = -1;
  m.y3 = -1;

  return m;

}

int win(){

  if(game.stock1==0 && game.stock2==0){
    if(game.queen1 > game.queen2){
      message=9;
      return 1;

    }
    if(game.stock2 > game.stock1){
      message=10;
      return 2;
    }
    message=8;
    return 3;
  }

  else if(game.stock1==0 && game.queen1==0){
    message=10;
    return 2;
  }
  else if(game.stock2==0 && game.queen2==0){
    message=9;
    return 1;
  }
  return 0;
}


void reset_tabl(){

  int i, j;

  for(i=0 ; i<10 ; i++){
    for(j=0 ; j<10 ; j++){
      tabl_piece[j][i] = 0;
    }
  }
}

void tabl_piece_possible(){

  int i, j;

  reset_tabl();

  for(j=0;j<10;j++){
    for(i=0;i<10;i++){
      if(choicePiecePossible_cpy(i,j)==1){
  tabl_piece[j][i] = 1;
      }
    }
  }
}


void tabl_move_possible(){

  int i, j;

  reset_tabl();

  for(i=0;i<game.t->nbfils;i++){
    printf("alphaaa\n");
    if(game.t->fils[i]->x == xx && game.t->fils[i]->y == yy){
      for(j=0 ; j<game.t->fils[i]->nbfils ; j++){
	printf("betaaa\n");
	printf("\n%d\n",game.t->fils[i]->fils[j]->score-1);
	printf("\n%d\n",game.score);
	if(game.t->fils[i]->fils[j]->score-1 == game.score){
	  printf("gammma\n");
	  tabl_piece[game.t->fils[i]->fils[j]->y][game.t->fils[i]->fils[j]->x] = 1;
	}
      }
    }
  }
}



void initboard(){

  int i, j;

  for(j=0 ; j<10 ; j++){
    for(i=0 ; i<10 ; i++){
      game.board[j][i] = 0;
    }
  }

  
  for(j=0 ; j<3 ; j++){
    for(i=(j+1)%2 ; i<10 ; i+=2){
      game.board[j][i]=1;
    }
  }
  for(j=6 ; j<10 ; j++){
    for(i=(j+1)%2 ; i<10 ; i+=2){
      game.board[j][i]=2;
    }
  }
  game.player = 1;
  game.end = 0;
  game.stock1 = 20;
  game.stock2 = 20;
  game.queen1 = 0;
  game.queen2 = 0; 
}


void createQueen(){

  if(game.player==1 && m.y2 == 9 && game.board[m.y2][m.x2]==1){
    game.board[m.y2][m.x2] += 2;
    game.stock1--;
    game.queen1++;
  }

  if(game.player==2 && m.y2 == 0 && game.board[m.y2][m.x2]==2){
    game.board[m.y2][m.x2] += 2;
    game.stock2--;
    game.queen2++;
  }
}




tree * build_tree(tree * t, checkers game, int x, int y, int prof){

  //DEUX VARIABLES

  printf("BUILD TREE / PROF == %d\n",prof);
  printf("X==%d  /  Y==%d\n",x,y);
  
  int i, j;
  
  t = malloc(sizeof(*t));
  t->x = x;
  t->y = y;
  t->nbfils = 0;
  t->score = prof;

  for(i=0 ; i<20 ; i++){
    t->fils[i] = NULL;
  }

  if(game.board[y][x] == game.player){
    if(x+2<10 && y+2<10 && game.board[y+1][x+1]==game.player%2+1 && game.board[y+2][x+2]==0){
      printf("AAA\n");
      game.board[y][x]=0;
      game.board[y+1][x+1]*=-1; // etat-zombie
      game.board[y+2][x+2]=game.player;
      t->fils[t->nbfils] = build_tree(t->fils[t->nbfils],game,x+2,y+2,prof+1);
      t->nbfils+=1;
      //On remet le board a l etat precedent:
      game.board[y][x]=game.player;
      game.board[y+1][x+1]*=-1;
      game.board[y+2][x+2]=0;
    }

    if(x-2>=0 && y-2>=0 && game.board[y-1][x-1]==game.player%2+1 && game.board[y-2][x-2]==0){
      printf("BBB\n");
      game.board[y][x]=0;
      game.board[y-1][x-1]*=-1; // etat-zombie
      game.board[y-2][x-2]=game.player;
      t->fils[t->nbfils] = build_tree(t->fils[t->nbfils],game,x-2,y-2,prof+1);
      t->nbfils+=1;
      //On remet le board a l etat precedent:
      game.board[y][x]=game.player;
      game.board[y-1][x-1]*=-1;
      game.board[y-2][x-2]=0;
    }

    if(x-2>=0 && y+2<10 && game.board[y+1][x-1]==game.player%2+1 && game.board[y+2][x-2]==0){
      printf("CCC\n");
      game.board[y][x]=0;
      game.board[y+1][x-1]*=-1; // etat-zombie
      game.board[y+2][x-2]=game.player;
      t->fils[t->nbfils] = build_tree(t->fils[t->nbfils],game,x-2,y+2,prof+1);
      t->nbfils+=1;
      //On remet le board a l etat precedent:
      game.board[y][x]=game.player;
      game.board[y+1][x-1]*=-1;
      game.board[y+2][x-2]=0;
    }

    if(x+2<10 && y-2>=0 && game.board[y-1][x+1]==game.player%2+1 && game.board[y-2][x+2]==0){
      printf("DDD\n");
      game.board[y][x]=0;
      game.board[y-1][x+1]*=-1; // etat-zombie
      game.board[y-2][x+2]=game.player;
      t->fils[t->nbfils] = build_tree(t->fils[t->nbfils],game,x+2,y-2,prof+1);
      t->nbfils+=1;
      //On remet le board a l etat precedent:
      game.board[y][x]=game.player;
      game.board[y-1][x+1]*=-1;
      game.board[y-2][x+2]=0;
    }
  }

  /////// DAME :
  if(game.board[y][x]>2){
    printf("DAME\n");
    i = 1;
    j = 1;
    while(y+i+1<10 && x+i+1<10 && (game.board[y+i][x+i]==0 || game.board[y+i][x+i]==game.player%2+1)){
      if(game.board[y+i][x+i]==game.player%2+1){
	while(game.board[y+i+j][x+i+j]==0 && y+i+j<10 && x+i+j<10){
	  game.board[y][x]=0;
          game.board[y+i][x+i]*=-1; // etat-zombie
	  game.board[y+i+j][x+i+j]=game.player+2;
	  printf("400\n");
	  t->fils[t->nbfils] = build_tree(t->fils[t->nbfils],game,x+i+j,y+i+j,prof+1);
	  t->nbfils+=1;
	  //On remet le board a l etat precedent:
	  game.board[y][x]=game.player+2;
	  game.board[y+i][x+i]*=-1;
	  game.board[y+i+j][x+i+j]=0;

	  j++;
	}
	break;
      }
      i++;
    }

    i = 1;
    j = 1;
    while(y-i-1<10 && x-i-1<10 && (game.board[y-i][x-i]==0 || game.board[y-i][x-i]==game.player%2+1)){
      if(game.board[y-i][x-i]==game.player%2+1){
        while(game.board[y-i-j][x-i-j]==0 && y-i-j>=0 && x-i-j>=0){
	  game.board[y][x]=0;
	  game.board[y-i][x-i]*=-1; // etat-zombie
	  game.board[y-i-j][x-i-j]=game.player+2;
	  printf("500\n");
	  t->fils[t->nbfils] = build_tree(t->fils[t->nbfils],game,x-i-j,y-i-j,prof+1);
	  t->nbfils+=1;
	  //On remet le board a l etat precedent:
	  game.board[y][x]=game.player+2;
	  game.board[y-i][x-i]*=-1;
	  game.board[y-i-j][x-i-j]=0;

	  j++;
	}
	break;
      }
      i++;
    }

    i = 1;
    j = 1;
    while(y-i-1<10 && x+i+1<10 && (game.board[y-i][x+i]==0 || game.board[y-i][x+i]==game.player%2+1)){
      if(game.board[y-i][x+i]==game.player%2+1){
	while(game.board[y-i-j][x+i+j]==0 && y-i-j>=0 && x+i+j<10){
	  game.board[y][x]=0;
	  game.board[y-i][x+i]*=-1; // etat-zombie
	  game.board[y-i-j][x+i+j]=game.player+2;
	  printf("600\n");
	  t->fils[t->nbfils] = build_tree(t->fils[t->nbfils],game,x+i+j,y-i-j,prof+1);
	  t->nbfils+=1;
	  //On remet le board a l etat precedent:
	  game.board[y][x]=game.player+2;
	  game.board[y-i][x+i]*=-1;
	  game.board[y-i-j][x+i+j]=0;

	  j++;
	}
	break;
      }
      i++;
    }

    i = 1;
    j = 1;
    while(y+i+1<10 && x-i-1<10 && (game.board[y+i][x-i]==0 || game.board[y+i][x-i]==game.player%2+1)){
      if(game.board[y+i][x-i]==game.player%2+1){
	while(game.board[y+i+j][x-i-j]==0 && y+i+j<10 && x-i-j>=0){
	  game.board[y][x]=0;
	  game.board[y+i][x-i]*=-1; // etat-zombie
	  game.board[y+i+j][x-i-j]=game.player+2;
	  printf("700\n");
	  t->fils[t->nbfils] = build_tree(t->fils[t->nbfils],game,x-i-j,y+i+j,prof+1);
	  t->nbfils+=1;
	  //On remet le board a l etat precedent:
	  game.board[y][x]=game.player+2;
	  game.board[y+i][x-i]*=-1;
	  game.board[y+i+j][x-i-j]=0;

	  j++;
	}
	break;
      }
      i++;
    }
  }

  return t;
}



tree * make_tree(tree * t, checkers game){

  int i, j;

  t=malloc(sizeof(*t));
  t->x=-1;
  t->y=-1;
  t->nbfils=0;

  for(i=0 ; i<20 ; i++){
    t->fils[i] = NULL;
  }


  for(j=0; j<10; j++){
    for(i=0; i<10; i++){
      if(game.board[j][i]==game.player || game.board[j][i]==game.player+2){
        //printf("%d %d\n",i,j);

        t->fils[t->nbfils] = build_tree(t->fils[t->nbfils],game,i,j,1);
	t->nbfils+=1;
	//printf("FILS:%d\n",t->nbfils);
      }
    }
  }


  return t;
}



void profondeur(tree * t){

  //printf("PROFONDEUR\n");
  //printf("X==%d / Y==%d\n",t->x,t->y);
  //printf("NBFILS == %d\n",t->nbfils);

  int i;

  for(i=0 ; i<t->nbfils ; i++){
    profondeur(t->fils[i]);
    if((t->score) < (t->fils[i]->score)){
      t->score = t->fils[i]->score;
    }
  }
}


int afficher_score(tree t){

  int i;
  int max = 0;

  for(i=0 ; i<t.nbfils ; i++){
    //printf("X==%d / Y ==%d  -------->   score == %d\n",t.fils[i]->x,t.fils[i]->y,t.fils[i]->score);
    if(max<t.fils[i]->score){
      max = t.fils[i]->score;
    }
  }

  printf("\n  ==============================================\n");
  printf("\t  VOUS DEVEZ PRENDRE %d PIECE(S)\n",max-1);
  printf("  ==============================================\n\n");
  //printf("NBFILS == %d\n",t.nbfils);

  return max-1;
}



int diago(){

  printf("\n\n APPEL DIAGO() \n\n");
  printf("m.x1 == %d \t m.y1 == %d\n", m.x1, m.y1);
  printf("m.x2 == %d \t m.y2 == %d\n", m.x2, m.y2);

  int i,j;
  i=m.x2;
  j=m.y2;

  while(i<10 && j<10){
    if(i==m.x1 && j==m.y1){
      return 1;
    }
    ++i;
    ++j;
  }

  i=m.x2;
  j=m.y2;
  while(i>=0 && j<10){
    if(i==m.x1 && j==m.y1){
      return 2;
    }
    --i;
    ++j;
  }

  i=m.x2;
  j=m.y2;
  while(i>=0 && j>=0){
    if(i==m.x1 && j==m.y1){
      return 3;
    }
    --i;
    --j;
  }

  i=m.x2;
  j=m.y2;
  while(i<10 && j>=0){
    if(i==m.x1 && j==m.y1){
      return 4;
    }
    ++i;
    --j;
  }

  return 0;
}



int queenMove(){

  printf("\n\n HHHHIIIII \n\n");
  printf("m.x1 == %d \t m.y1 == %d\n", m.x1, m.y1);
  printf("m.x2 == %d \t m.y2 == %d\n", m.x2, m.y2);
  
  int diagon = diago();
  printf("HEEELLOOO\n");
  printf("DIAGO == %d\n",diagon);
  
  int x3, y3;
  int i, j;
  int nbpiece;
  i = m.x2;
  j = m.y2;
  //nbpiece compte le nombre de piece du joueur adverse entre la position de depart et d arrivee
  nbpiece = 0;

  if(diagon==1){
    do{
      ++i;
      ++j;

      //Si on trouve une piece alliee on sort de la fonction:
      if(game.board[j][i]==game.player){
        return 0;
      }
      
      if(game.board[j][i]==game.player%2+1){
	++nbpiece;
	x3 = i;
	y3 = j;
      }
      
    }while(i!=m.x1);
    if(nbpiece>1){
      return 0;
    }
    nbpiece==0 ? m.prise=0 : (m.prise=1, m.x3=x3, m.y3=y3); 
  }

  if(diagon==2){
    do{
      --i;
      ++j;

      //Si on trouve une piece alliee on sort de la fonction:
      if(game.board[j][i]==game.player){
        return 0;
      }
      
      if(game.board[j][i]==game.player%2+1){
	++nbpiece;
	x3 = i;
	y3 = j;
      }
      
    }while(i!=m.x1);
    if(nbpiece>1){
      return 0;
    }
    nbpiece==0 ? m.prise=0 : (m.prise=1, m.x3=x3, m.y3=y3);
  }

  if(diagon==3){
    do{
      --i;
      --j;

      //Si on trouve une piece alliee on sort de la fonction:
      if(game.board[j][i]==game.player){
        return 0;
      }
      
      if(game.board[j][i]==game.player%2+1){
	++nbpiece;
	x3 = i;
	y3 = j;
      }
      
    }while(i!=m.x1);
    if(nbpiece>1){
      return 0;
    }
    nbpiece==0 ? m.prise=0 : (m.prise=1, m.x3=x3, m.y3=y3);
  }

  if(diagon==4){
    do{
      ++i;
      --j;

      //Si on trouve une piece alliee on sort de la fonction:
      if(game.board[j][i]==game.player){
        return 0;
      }
      
      if(game.board[j][i]==game.player%2+1){
	++nbpiece;
	x3 = i;
	y3 = j;
      }
      
    }while(i!=m.x1);
    if(nbpiece>1){
      return 0;
    }
    nbpiece==0 ? m.prise=0 : (m.prise=1, m.x3=x3, m.y3=y3);
  }

  return 1;
}




int chooseMovePossible(){

  int i, j;
  int test_coup = 0;

  printf("CASE FINALE : x==%d  /  y==%d\n",m.x2,m.y2);
  printf("VALEUR DE LA CASE FINALE ==  %d\n",game.board[m.y2][m.x2]);

  //La case choisie est en dehors du plateau:
  if(m.x2<0 || m.x2>9 || m.y2<0 || m.y2>9){
    printf("\nm.x2 == %d, m.y2 == %d\n",m.x2,m.y2);
    printf("Cette case est en dehors du plateau\n");
    message=0;
    return 0;
  }


  //Il y a deja une piece sur la case choisie:
  if(game.player==1 && m.x2==m.x1+1 && m.y2==m.y1+1 && game.board[m.y2][m.x2]!=0){
    printf("Cette case est deja prise\n");
    message=1;
    return 0;
  }
  
  if(game.player==1 && m.x2==m.x1-1 && m.y2==m.y1+1 && game.board[m.y2][m.x2]!=0){
    printf("Cette case est deja prise\n");
    message=1;
    return 0;
  }
  
  if(game.player==2 && m.x2==m.x1-1 && m.y2==m.y1-1 && game.board[m.y2][m.x2]!=0){
    printf("Cette case est deja prise\n");
    message=1;
    return 0;
  }
  
  if(game.player==2 && m.x2==m.x1+1 && m.y2==m.y1-1 && game.board[m.y2][m.x2]!=0){
    printf("Cette case est deja prise\n");
    message=1;
    return 0;
  }

  /*
  //La piece ne fait pas partie du coup le plus optimal: 
  for(i=0 ; i<game.t->nbfils ; i++){ 
    if(game.t->fils[i]->x==x && game.t->fils[i]->y==y && game.score!=game.t->fils[i]->score-1){ 
      printf("SCORE == %d\t SCORE_FILS == %d\n", game.score, game.t->fils[i]->score-1);
      printf("La piece ne fait pas partie du coup le plus optimal\n");
      return 0;
    }
  }
  */

  /////////REGARDER

  //Recherche dans l arbre pour savoir si le coup est un coup optimal et donc possible:
  if(game.score>0){
    for(i=0 ; i<game.t->nbfils ; i++){
      if(game.t->fils[i]->x==m.x1 && game.t->fils[i]->y==m.y1){
	for(j=0 ; j<game.t->fils[i]->nbfils ; j++){
	  if(game.t->fils[i]->fils[j]->x==m.x2 && game.t->fils[i]->fils[j]->y==m.y2){
	    test_coup = 1;
	  }
	}
      }
    }
    if(test_coup == 0){
      printf("Ce move n est pas optimal 1\n");
      message=3;
      return 0;
    }

    for(i=0 ; i<game.t->nbfils ; i++){
      if(game.t->fils[i]->x==m.x1 && game.t->fils[i]->y==m.y1){
	for(j=0 ; j<game.t->fils[i]->nbfils ; j++){
	  if(game.t->fils[i]->fils[j]->x==m.x2 && game.t->fils[i]->fils[j]->y==m.y2 && game.score!=game.t->fils[i]->fils[j]->score-1){
	    printf("Ce move n est pas optimal 2\n");
	    message=3;
	    return 0;
	  }
	}
      }
    }
  }
	

  //Cas de deplacement sans prise de pion:
  if(game.player==1 && m.x2==m.x1+1 && m.y2==m.y1+1 && game.board[m.y2][m.x2]==0){
    m.prise = 0;
    return 1;
  }

  if(game.player==1 && m.x2==m.x1-1 && m.y2==m.y1+1 && game.board[m.y2][m.x2]==0){
    m.prise = 0;
    return 1;
  }

  if(game.player==2 && m.x2==m.x1-1 && m.y2==m.y1-1 && game.board[m.y2][m.x2]==0){
    m.prise = 0;
    return 1;
  }

  if(game.player==2 && m.x2==m.x1+1 && m.y2==m.y1-1 && game.board[m.y2][m.x2]==0){
    m.prise = 0;
    return 1;
  }

  

  //Prise possible pour un pion (donc valable pour une dame):
  if(m.x2==m.x1+2 && m.y2==m.y1+2 && game.board[m.y2][m.x2]==0 && game.board[m.y1+1][m.x1+1]==game.player%2+1){
    m.prise = 1;
    m.x3 = m.x1+1;
    m.y3 = m.y1+1;
    return 1;
  }
  if(m.x2==m.x1-2 && m.y2==m.y1+2 && game.board[m.y2][m.x2]==0 && game.board[m.y1+1][m.x1-1]==game.player%2+1){
    m.prise = 1;
    m.x3 = m.x1-1;
    m.y3 = m.y1+1;
    return 1;
  }
  if(m.x2==m.x1-2 && m.y2==m.y1-2 && game.board[m.y2][m.x2]==0 && game.board[m.y1-1][m.x1-1]==game.player%2+1){
    m.prise = 1;
    m.x3 = m.x1-1;
    m.y3 = m.y1-1;
    return 1;
  }
  if(m.x2==m.x1+2 && m.y2==m.y1-2 && game.board[m.y2][m.x2]==0 && game.board[m.y1-1][m.x1+1]==game.player%2+1){
    m.prise = 1;
    m.x3 = m.x1+1;
    m.y3 = m.y1-1;
    return 1;
  }

  if(m.type_piece>2){
    m.prise = -1;
    
    queenMove();
    if(m.prise>=0){
      message=0;
      return 1;
    }
  }
  
  //Move impossible:
  printf("MOVE IMPOSSIBLE\n");
  message=3;
  return 0;

}





checkers initpieces(checkers game){
  
  int i, j;
  


  for(j=0 ; j<4 ; j++){
    for(i=(j+1)%2 ; i<10 ; i+=2){
      game.board[j][i]=1;
    }
  }


  for(j=6 ; j<10 ; j++){
    for(i=(j+1)%2 ; i<10 ; i+=2){
      game.board[j][i]=2;
    }
  }

  game.player = 1;
  game.end = 0;
  game.stock1 = 20;
  game.stock2 = 20;
  game.queen1 = 0;
  game.queen2 = 0;

  return game;
} 

void actualisation_board(){

  game.board[m.y2][m.x2] = game.board[m.y1][m.x1];
  game.board[m.y1][m.x1] = 0;
  if(m.prise==1){
    game.board[m.y3][m.x3] *= -1;
  }
}

void remove_pieces(){

  int i, j;

  for(i=0 ; i<10 ; i++){
    for(j=0 ; j<10 ; j++){
      if(game.board[j][i]<0){
	game.board[j][i]=0;
	if(game.player==1){
	  game.stock2--;
	}
	else{
	  game.stock1--;
	}
      }
    }
  }
}


int choicePiecePossible(){

  int i;

  printf("VALEUR DE LA CASE CHOISIE ==  %d\n\n",game.board[(int)yy][(int)xx]);
  printf("NBFILS == %d\n",game.t->nbfils);
  printf("SCORE == %d\n",game.score);

  //La case est vide:
  if(game.board[yy][xx]==0){
   printf("Il n y a pas de piece sur cette case.\n");
   message=4;
   return 0;
  } 

  //La piece ne fait pas partie du coup le plus optimal:
  if(game.score>0){
    for(i=0 ; i<game.t->nbfils ; i++){
      if(game.t->fils[i]->x==xx && game.t->fils[i]->y==yy && game.score!=game.t->fils[i]->score-1){ 
	printf("SCORE == %d\t SCORE_FILS == %d\n", game.score, game.t->fils[i]->score-1);
	printf("La piece ne fait pas partie du coup le plus optimal\n");
	message=5;
	return 0;
      }
      //La piece fait partie du coup le plus optimal: 
      if(game.t->fils[i]->x==xx && game.t->fils[i]->y==yy && game.score==game.t->fils[i]->score-1){
	printf("SCORE == %d\t SCORE_FILS == %d\n", game.score, game.t->fils[i]->score-1);
	printf("La piece fait partie du coup le plus optimal\n");
	printf("AAA\n");
	return 1;
      }
    }
  }
      

  //La piece est a l autre joueur:
  if(game.board[yy][xx]%2 != game.player%2){
    printf("Cette piece ne vous appartient pas\n");
    message=6;
    return 0;
  }
  
  //deplacement sans prise possible:
  if((game.player==1 || game.board[yy][xx]==4) && xx+1<10 && yy+1<10 && game.board[yy+1][xx+1]==0){
    printf("BBB\n");
    return 1;
  }

  if((game.player==1 || game.board[yy][xx]==4) && xx-1>=0 && yy+1<10 && game.board[yy+1][xx-1]==0){
    printf("CCC\n");
    return 1;
  }
  
  if((game.player==2 || game.board[yy][xx]==3) && xx-1>=0 && yy-1>=0 && game.board[yy-1][xx-1]==0){
    printf("DDD\n");
    return 1;
  }
  
  if((game.player==2 || game.board[yy][xx]==3) && xx+1<10 && yy-1>=0 && game.board[yy-1][xx+1]==0){
    printf("EEE\n");
    return 1;
  }

  //deplacement avec prise possible:

  if(xx+2<10 && yy+2<10 && game.board[yy+2][xx+2]==0 && game.board[yy+1][xx+1]==game.player%2+1){
    printf("FFF\n");
    return 1;
  }

  if(xx-2>=0 && yy+2<10 && game.board[yy+2][xx-2]==0 && game.board[yy+1][xx-1]==game.player%2+1){
    printf("GGG\n");
    return 1;
  }
  
  if(xx-2>=0 && yy-2>=0 && game.board[yy-2][xx-2]==0 && game.board[yy-1][xx-1]==game.player%2+1){
    printf("HHH\n");
    return 1;
  }
  
  if(xx+2<10 && yy-2>=0 && game.board[yy-2][xx+2]==0 && game.board[yy-1][xx+1]==game.player%2+1){
    printf("III\n");
    return 1;
  }

   

  //Pas de coup possible:
  printf("Aucun coup possible avec la piece choisie ou case choisie invalide.\n");
  message=7;
  return 0;
}

int choicePiecePossible_cpy(int xxx, int yyy){

  int i;

  //printf("VALEUR DE LA CASE CHOISIE ==  %d\n\n",game.board[(int)yy][(int)xx]);
  //printf("NBFILS == %d\n",game.t->nbfils);
  //printf("SCORE == %d\n",game.score);

  //La case est vide:
  if(game.board[yyy][xxx]==0){
    //printf("Il n y a pas de piece sur cette case.\n");
    return 0;
  } 

  //La piece ne fait pas partie du coup le plus optimal:
  if(game.score>0){
    for(i=0 ; i<game.t->nbfils ; i++){
      if(game.t->fils[i]->x==xxx && game.t->fils[i]->y==yyy && game.score!=game.t->fils[i]->score-1){ 
	//printf("SCORE == %d\t SCORE_FILS == %d\n", game.score, game.t->fils[i]->score-1);
	//printf("La piece ne fait pas partie du coup le plus optimal\n");
	printf("%d %d ->>>>> false\n",xxx,yyy);
	return 0;
      }
      //La piece fait partie du coup le plus optimal: 
      if(game.t->fils[i]->x==xxx && game.t->fils[i]->y==yyy && game.score==game.t->fils[i]->score-1){
	//printf("SCORE == %d\t SCORE_FILS == %d\n", game.score, game.t->fils[i]->score-1);
	//printf("La piece fait partie du coup le plus optimal\n");
	return 1;
      }
    }
  }
      

  //La piece est a l autre joueur:
  if(game.board[yyy][xxx]%2 != game.player%2){
    //printf("Cette piece ne vous appartient pas\n");
    return 0;
  }
  
  //deplacement sans prise possible:
  if((game.player==1 || game.board[yyy][xxx]==4) && xxx+1<10 && yyy+1<10 && game.board[yyy+1][xxx+1]==0){
    return 1;
  }

  if((game.player==1 || game.board[yyy][xxx]==4) && xxx-1>=0 && yyy+1<10 && game.board[yyy+1][xxx-1]==0){
    return 1;
  }
  
  if((game.player==2 || game.board[yyy][xxx]==3) && xxx-1>=0 && yyy-1>=0 && game.board[yyy-1][xxx-1]==0){
    return 1;
  }
  
  if((game.player==2 || game.board[yyy][xxx]==3) && xxx+1<10 && yyy-1>=0 && game.board[yyy-1][xxx+1]==0){
    return 1;
  }

  //deplacement avec prise possible:

  if(xxx+2<10 && yyy+2<10 && game.board[yyy+2][xxx+2]==0 && game.board[yyy+1][xxx+1]==game.player%2+1){
    return 1;
  }

  if(xxx-2>=0 && yyy+2<10 && game.board[yyy+2][xxx-2]==0 && game.board[yyy+1][xxx-1]==game.player%2+1){
    return 1;
  }
  
  if(xxx-2>=0 && yyy-2>=0 && game.board[yyy-2][xxx-2]==0 && game.board[yyy-1][xxx-1]==game.player%2+1){
    return 1;
  }
  
  if(xxx+2<10 && yyy-2>=0 && game.board[yyy-2][xxx+2]==0 && game.board[yyy-1][xxx+1]==game.player%2+1){
    return 1;
  }

   

  //Pas de coup possible:
  //printf("Aucun coup possible avec la piece choisie ou case choisie invalide.\n");
  return 0;
}

