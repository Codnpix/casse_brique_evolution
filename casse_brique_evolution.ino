#include <Gamebuino-Meta.h>

bool launched;

int currentLevel = 1;
const int NB_LEVELS = 3;

//briques
const int BRICK_H = 4;//hauteur d'une brique
const int NB_COLONNES = 8;//nb colonnes tableau de briques
const int NB_RANGEES = 8;//nb rangees tableau de briques
const int BRICK_W = (gb.display.width() / NB_COLONNES) - 1;//largeur d'une brique

//structure donnée pour les briques
typedef struct Brique {
  int x;
  int y;
  int _w;//largeur
  int _h;//hauteur
  int type;
  int state;
  Image img;
};

//déclaration du tableau de briques
struct Brique briques[NB_RANGEES][NB_COLONNES];

//declaration de la carte des types de briques.
//assignée en fonction du niveau chargé dans initGame.
int types_set[NB_RANGEES][NB_COLONNES] = {};

//balle
float ballX;
float speedX;//declarés en float pour pouvoir calculer une variation d'angle
int ballY;
int speedY;
const int BALL_RADIUS = 1; //la balle sera un cercle
const float ANGLE_CORRECTOR = 0.40;//ajouter une valeur d'angle lors du prochain rebond si l'angle renvoyé par la palette est trop faible

//palette
const int PAD_W = 14;
const int PAD_H = 2;
const int PAD_Y = gb.display.height() - PAD_H;
int padX;

void setup() {
  gb.begin();
  initGame();
}

void loop() {
  while(!gb.update());
  getInputs();
  
  if (launched == true) {
    updateGame();
  }
  if (launched == false) {
    ballX = padX + PAD_W / 2;//tant que la balle n'est pas lancée, la déplacer en même temps que la palette, pour choisir l'endroit ou on lance.
  }
  displayGame();
}
