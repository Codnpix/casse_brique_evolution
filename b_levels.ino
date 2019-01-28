//LEVELS (types of bricks arrays)
const uint8_t levels[NB_LEVELS][NB_RANGEES][NB_COLONNES] = {
  {
    {0,1,1,1,1,1,1,0},
    {0,2,0,2,1,0,2,0},
    {0,1,0,1,2,0,1,0},
    {0,2,2,3,3,2,2,0},
    {0,1,0,1,2,0,1,0},
    {0,2,0,2,1,0,2,0},
    {0,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,0}
  },
  {
    {1,0,0,2,0,0,0,0},
    {1,1,0,2,0,0,2,0},
    {1,1,1,2,0,0,2,0},
    {1,3,1,1,2,0,2,2},
    {1,0,1,3,1,2,2,2},
    {1,0,1,0,1,1,2,1},
    {1,1,1,1,1,3,1,1},
    {0,0,0,0,0,0,0,0}
  },
  {
    {0,0,0,1,1,0,0,0},
    {0,1,1,2,2,1,1,0},
    {1,2,2,3,3,2,2,1},
    {0,1,1,2,2,1,1,0},
    {0,0,0,1,1,0,0,0},
    {1,0,2,3,3,2,0,1},
    {0,2,1,2,2,1,2,0},
    {2,0,2,0,0,2,0,2}
  },
  {
    {1,1,2,2,2,2,1,1},
    {4,5,5,0,0,5,5,4},
    {2,0,3,2,2,3,0,2},
    {5,4,0,5,5,0,4,5},
    {2,0,3,2,2,3,0,2},
    {4,5,0,5,5,0,5,4},
    {2,2,1,1,1,1,2,2},
    {0,0,0,0,0,0,0,0}
  },
  {
    {7,0,7,0,7,0,7,0},
    {0,0,0,0,0,0,0,0},
    {0,6,0,6,0,6,0,6},
    {0,6,0,6,0,6,0,6},
    {7,0,7,0,7,0,7,0},
    {7,0,7,0,7,0,7,0},
    {0,0,0,0,0,0,0,0},
    {3,0,3,0,3,0,3,0}
  },
  {
    {11,10,0,0,0,0,0,0},
    {10,11,0,0,0,0,0,0},
    {0,0,1,1,1,1,0,0},
    {0,0,1,3,3,1,0,0},
    {0,0,1,3,3,1,0,0},
    {0,0,1,1,1,1,0,0},
    {0,0,0,0,0,0,9,8},
    {0,0,0,0,0,0,8,9}
  }
};

//bricks moves values for each level {startX, startY, endX, endY, startSpeedX, StartSpeedY, endSpeedX, endSpeedY}
int8_t edgesXY[NB_LEVELS][8] = {
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,-1,1,-1,1,1,-1},
  {0,0,-6,-6,0,0,0,0}
  };
  

int8_t seqLvl6[4][2] = {//speedX and speedY valued pattern for level6 (just for trying...)
    {0,-1},
    {-1,0},
    {0,1},
    {1,0}
  };
int8_t seqLvl6inv[4][2] = {//same for the second group of moving bricks
  {0,1},
  {1,0},
  {0,-1},
  {-1,0}
};
const uint16_t RESPAWN_INTERVAL = 18000;//bricks (type 8 9 10 11) respawn after 18s in level6


const Image backgrounds[NB_LEVELS] = {
  bg_1, bg_2, bg_3, bg_4, bg_5, bg_6
};

const char * levelNames[NB_LEVELS] = {
  " Down Town ",
  " Industrial ",
  "Space Colony",
  "  Railway  ",
  "Diesel Power",
  "  Reactor  "
  };

const char* levelSongs[NB_LEVELS] = {
  "gb_breakout_lv1.wav",
  "gb_breakout_lv2.wav",
  "gb_breakout_lv3.wav",
  "gb_breakout_lv4.wav",
  "gb_breakout_lv5.wav",
  "gb_breakout_lv6.wav"
};
const char* winSound = "gb_breakout_win.wav";
const char* loseSound = "gb_breakout_lose.wav";
const char* menuSong = "gb_breakout_menu.wav";
