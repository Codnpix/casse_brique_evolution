//MENU
void displayMenu() {
  
  gb.display.clear();
  drawBackground(chosenLevel);
  chooseLevel();
  
  gb.display.fontSize = 2;
  gb.display.setCursor(13, gb.display.height() / 3);
  gb.display.print("LEVEL ");
  gb.display.println(chosenLevel);

  gb.display.setCursor(0, gb.display.height() / 2);
  gb.display.print("<");

  gb.display.setCursor(gb.display.width() -8, gb.display.height() / 2);
  gb.display.print(">");
  
  gb.display.fontSize = 1;
  gb.display.setColor(YELLOW);
  gb.display.setCursorX(16);
  gb.display.println(levelNames[chosenLevel - 1]);
}

void chooseLevel() {
  bool isUnlocked = true;
  
  if (gb.buttons.released(BUTTON_LEFT)) {
      if (chosenLevel == 1) chosenLevel = NB_LEVELS;
      else chosenLevel --;
    }
    if (gb.buttons.released(BUTTON_RIGHT)) {
      if (chosenLevel == NB_LEVELS) chosenLevel = 1;
      else chosenLevel ++;
    }
    
    if (chosenLevel<= lastUnlockedLevel) {
      isUnlocked = true;
    } else {
      isUnlocked = false;
    }

    if (gb.buttons.released(BUTTON_A)) {
      launchLevel(chosenLevel, isUnlocked);
    }
    
}

void launchLevel(int chosenLvl, bool isUnlocked) {
  if (isUnlocked) {
    currentLevel = chosenLevel;
    gameOn = true;
    initGame();
  } else {
    gb.display.setColor(RED);
    gb.display.println("locked");
    delay(500);
  }
}
