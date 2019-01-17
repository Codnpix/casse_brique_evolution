void loadLevel(int myLevel) {
   
  for (int rangee = 0; rangee < NB_RANGEES; rangee++) {
      for (int colonne = 0; colonne < NB_COLONNES; colonne++) {
        types_set[rangee][colonne] = levels[myLevel][rangee][colonne];
      }
    }
}

void initBricks() {
    for (int rangee = 0; rangee < NB_RANGEES; rangee ++) {
    for (int colonne = 0; colonne < NB_COLONNES; colonne++) {
      briques[rangee][colonne].type = types_set[rangee][colonne];
      briques[rangee][colonne].x = colonne * (BRICK_W + 1) + 1;
      briques[rangee][colonne].y = rangee * (BRICK_H + 1) + 1;
      if (briques[rangee][colonne].type == 1) {
        briques[rangee][colonne].state = 1;
        briques[rangee][colonne].img = brick1;
      } else if (briques[rangee][colonne].type == 2) {
        briques[rangee][colonne].state = 2;
        briques[rangee][colonne].img = brick2;
      } else if (briques[rangee][colonne].type == 3) {
        briques[rangee][colonne].state = -2;
        briques[rangee][colonne].img = brick3;
      } else if (briques[rangee][colonne].type == 4) {
        briques[rangee][colonne].state = 2; 
        briques[rangee][colonne].img = brick4;
      } else if (briques[rangee][colonne].type == 5) {
          briques[rangee][colonne].state = 3; 
          briques[rangee][colonne].img = brick5;
      } else if (briques[rangee][colonne].type == 6) {
          briques[rangee][colonne].state = 2; 
          briques[rangee][colonne].img = brick6;
          briques[rangee][colonne].speedX = edgesXY[currentLevel-1][4];
      } else if (briques[rangee][colonne].type == 7) {
          briques[rangee][colonne].state = 2; 
          briques[rangee][colonne].img = brick7;
          briques[rangee][colonne].speedY = edgesXY[currentLevel-1][5];
      } else if (briques[rangee][colonne].type == 8) {
          briques[rangee][colonne].state = 1; 
          briques[rangee][colonne].img = brick8;
          briques[rangee][colonne].speedY = seqLvl6[0][1];
          briques[rangee][colonne].speedX = seqLvl6[0][0];
      } else if (briques[rangee][colonne].type == 9) {
          briques[rangee][colonne].state = 2; 
          briques[rangee][colonne].img = brick9;
          briques[rangee][colonne].speedY = seqLvl6[0][1];
          briques[rangee][colonne].speedX = seqLvl6[0][0];
      } else if (briques[rangee][colonne].type == 10) {
          briques[rangee][colonne].state = 1; 
          briques[rangee][colonne].img = brick10;
          briques[rangee][colonne].speedY = seqLvl6inv[0][1];
          briques[rangee][colonne].speedX = seqLvl6inv[0][0];
      } else if (briques[rangee][colonne].type == 11) {
          briques[rangee][colonne].state = 2; 
          briques[rangee][colonne].img = brick11;
          briques[rangee][colonne].speedY = seqLvl6inv[0][1];
          briques[rangee][colonne].speedX = seqLvl6inv[0][0];
      } else if (briques[rangee][colonne].type == 0) {//les briques dont le type est zéro sont détruite d'entrée de jeu pour laisser un espace vide.
        briques[rangee][colonne].state = -1;
      }
      
    }
  }
}

void initGame() {
  if (!gameOn) levelNameScreen = true;
  
  if (currentLevel > NB_LEVELS) {
    currentLevel = 1;
  }

  launched = false;
  loadLevel(currentLevel - 1);

  padX = gb.display.width() / 2 - PAD_W / 2;
  
  ballX = padX + (PAD_W / 2) - (BALL_SIZE / 2);
  ballY = PAD_Y - BALL_SIZE - 1;
  speedX = 0;
  speedY = 1;

  initBricks();
}
