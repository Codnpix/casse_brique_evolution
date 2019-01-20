#include <Gamebuino-Meta.h>
#include "sounds.h"

//save config
#define SAVE_LAST_UNLOCKED_LEVEL 0

//DECALARATIONS

bool gameOn;
bool launched;
bool win;
bool lose;
bool levelNameScreen;

int currentLevel;
int lastUnlockedLevel;
int chosenLevel;
const int NB_LEVELS = 6;

//bricks
const int BRICK_H = 4;//hauteur d'une brique
const int NB_COLONNES = 8;//nb colonnes tableau de briques
const int NB_RANGEES = 8;//nb rangees tableau de briques
const int BRICK_W = (gb.display.width() / NB_COLONNES) - 1;//largeur d'une brique

//structure donnée pour les briques
struct Brique {
  int x;
  int y;
  int _w;//largeur
  int _h;//hauteur
  int type;
  int state;
  Image img;
  int speedX;
  int speedY;
  unsigned long deathTime;
};

//the array of actual bricks
struct Brique briques[NB_RANGEES][NB_COLONNES];

//this array will be filled from levels array on loadLevel()
int types_set[NB_RANGEES][NB_COLONNES] = {};

//ball
float ballX;
float speedX;//declarés en float pour pouvoir calculer une variation d'angle
float ballY;
float speedY;
const int BALL_SIZE = 2;//balle carrée 2 px coté
const float ANGLE_CORRECTOR = 0.25;//ajouter une valeur d'angle lors du prochain rebond si l'angle renvoyé par la palette est trop faible
const float MAX_SPEED_X = 0.7;

//paddle
const int PAD_W = 14;
const int PAD_H = 3;
const int PAD_Y = gb.display.height() - PAD_H - 4;
int padX;
