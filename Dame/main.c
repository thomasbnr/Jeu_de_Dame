#include "checkers.h"
//MAIN

int main(int argc, char** argv){



  
  //  initboard(game);
  game = initpieces(game);
  m = initMove(m);
  game.t = make_tree(game.t, game);
  printf("\n\n m.x1=%d m.y1=%d \n\n", m.x1, m.y2);
  tabl_piece_possible();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(700,700);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Checkers");
  glutTimerFunc(1.0, animate, 0);
  glutDisplayFunc(display);
  // glutTimerFunc(TIMERSECS, animate, 0);
  // init();
  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(keyboardown);

  glutPostRedisplay();
  glutMainLoop();
  
  
}