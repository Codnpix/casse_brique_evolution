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

uint8_t currentLevel;
uint8_t lastUnlockedLevel;
uint8_t chosenLevel;
const uint8_t NB_LEVELS = 6;

//bricks
const uint8_t BRICK_H = 4;//hauteur d'une brique
const uint8_t NB_COLONNES = 8;//nb colonnes tableau de briques
const uint8_t NB_RANGEES = 8;//nb rangees tableau de briques
const uint8_t BRICK_W = (gb.display.width() / NB_COLONNES) - 1;//largeur d'une brique

//structure donnée pour les briques
struct Brique {
  int8_t x;
  int8_t y;
  uint8_t _w;//largeur
  uint8_t _h;//hauteur
  uint8_t type;
  int8_t state;
  Image img;
  float speedX;
  int8_t speedY;
  unsigned long deathTime;
};

//the array of actual bricks
struct Brique briques[NB_RANGEES][NB_COLONNES];

//this array will be filled from levels array on loadLevel()
uint8_t types_set[NB_RANGEES][NB_COLONNES] = {};

//ball
float ballX;
float speedX;//declarés en float pour pouvoir calculer une variation d'angle
float ballY;
float speedY;
const uint8_t BALL_SIZE = 2;//balle carrée 2 px coté
const float ANGLE_CORRECTOR = 0.20;//ajouter une valeur d'angle lors du prochain rebond si l'angle renvoyé par la palette est trop faible
const float MAX_SPEED_X = 0.7;

//paddle
const uint8_t PAD_W = 14;
const uint8_t PAD_H = 3;
const uint16_t PAD_Y = gb.display.height() - PAD_H - 4;
int16_t padX;

uint8_t track = -1;
bool songPlaying;
bool winOrLosePlaying;
bool menuSongPlaying;
