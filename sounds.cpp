#include "sounds.h"


const Gamebuino_Meta::Sound_FX destroyBrick[] = {
  {Gamebuino_Meta::Sound_FX_Wave::NOISE,1,203,-6,61,96,5},
  {Gamebuino_Meta::Sound_FX_Wave::NOISE,0,69,-3,29,208,5},
};


const Gamebuino_Meta::Sound_FX collideWall[] = {
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,92,-15,90,425,4},
};


const Gamebuino_Meta::Sound_FX collideBrick[] = {
  {Gamebuino_Meta::Sound_FX_Wave::NOISE,0,94,-7,30,128,8},
};

const Gamebuino_Meta::Sound_FX bouncePaddle[] = {
  {Gamebuino_Meta::Sound_FX_Wave::NOISE,1,56,-4,27,224,2},
  {Gamebuino_Meta::Sound_FX_Wave::SQUARE,0,58,-7,126,636,10},
};
