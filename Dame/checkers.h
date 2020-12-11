#include <stdio.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>


//STRUCTURES

struct tree{

  int x;
  int y;
  int nbfils;
  int score;
  struct tree * fils[20];
};
typedef struct tree tree;

struct move{

  int x1;
  int y1;
  int x2;
  int y2;
  int type_piece;
  int prise;
  int x3;
  int y3;
};
typedef struct move move;


struct checkers{

  int board[10][10];
  int player;
  int end;
  int stock1;
  int stock2;
  int queen1;
  int queen2;
  tree * t;
  int score;
};
typedef struct checkers checkers;


//PROTOTYPES FONCTIONS

//fonctions.c

move initMove(move);
void initboard();
void createQueen();
tree * build_tree(tree *, checkers, int, int, int);
tree * make_tree(tree *, checkers);
void profondeur(tree *);
int afficher_score(tree);
int choicePiecePossible();
int diago();
int queenMove();
int chooseMovePossible();
checkers initpieces(checkers);
void actualisation_board();
void remove_pieces();
void reset_tabl();
void tabl_piece_possible();
void tabl_move_possible();
int win();
int choicePiecePossible_cpy(int, int);


//display.c

void display_menu();
void displayboard(void);
void rect();
void animate(int);
void movepiece();
void showpieces(checkers);
void display();
void init();
void keyboardown(int, int, int);
void processNormalKeys(unsigned char, int, int);
void displayMessage();
void crown();
void show();



//VARIABLES GLOBALES

extern int xx;
extern int yy;
extern checkers game;
extern move m;
extern int max;
extern int message;
extern int menu;
extern int hints;
extern int selected;
extern int selectedx;
extern int selectedy;
extern int developer_mode;
extern int tabl_piece[10][10];

