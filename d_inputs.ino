//INPUTS
void getInputs() {
  if (gameOn) {
    if (gb.buttons.pressed(BUTTON_A)) {
      launched = true;
    }
    if (gb.buttons.repeat(BUTTON_LEFT,0)) {
      movePad("left");
    }
    if (gb.buttons.repeat(BUTTON_RIGHT,0)) {
      movePad("right");
    }
    if (gb.buttons.pressed(BUTTON_MENU)) {
      gameOn = false;
    }
  } else {//menu actions
    if (gb.buttons.released(BUTTON_LEFT)) {
      if (currentLevel == 1) currentLevel = NB_LEVELS;
      else currentLevel --;
    }
    if (gb.buttons.released(BUTTON_RIGHT)) {
      if (currentLevel == NB_LEVELS) currentLevel = 1;
      else currentLevel ++;
    }
    if (gb.buttons.released(BUTTON_A)) {
      gameOn = true;
      initGame(); 
    }
  }
}
