//DISPLAY
void drawBackground(int index) {
  //gb.display.drawImage(0,0, bg_1, gb.display.width(), gb.display.height());
  gb.display.drawImage(0,0, backgrounds[index - 1], gb.display.width(), gb.display.height());
}

void displayWinLose(char winOrLose[5]) {
  
  if (winOrLose == "lose") {
    gb.display.clear();
    drawBackground(currentLevel);
    gb.display.fontSize = 2;
    gb.display.setCursor(25, gb.display.height() / 4);
    gb.display.println("You");
    gb.display.setCursorX(10);
    gb.display.println("lose ...");
  }
  else if (winOrLose == "win") {
    gb.display.clear();
    drawBackground(currentLevel);
    gb.display.fontSize = 2;
    gb.display.setCursor(25, gb.display.height() / 4);
    gb.display.println("You");
    gb.display.setCursorX(20);
    gb.display.println("win !");
    currentLevel ++;
  }

  delay(1000);
  win = false;
  lose = false;
  initGame();
}

void displayGame() {

  if (lose) {
    displayWinLose("lose");
  }
  else if (win) {
    displayWinLose("win");
  }
  else if (levelNameScreen) {
    displayLevelName();
  }
  else {
    gb.display.clear();
    drawBackground(currentLevel);
    //palette
    gb.display.setColor(GRAY);
    gb.display.fillRect(padX, PAD_Y, PAD_W, PAD_H);
    //balle
    gb.display.setColor(YELLOW);
    gb.display.fillRect(ballX, ballY, BALL_SIZE, BALL_SIZE);
    //briques
    for (int rangee = 0; rangee < NB_RANGEES; rangee ++) {
      for (int colonne = 0; colonne < NB_COLONNES; colonne++) {
        if (briques[rangee][colonne].state <= 0 && briques[rangee][colonne].state > -2) { //ne pas redessiner les briques détruites
          continue;
        } else {
          gb.display.drawImage(briques[rangee][colonne].x, briques[rangee][colonne].y, briques[rangee][colonne].img, BRICK_W, BRICK_H);
        }
      }
    }
  }
}

void displayLevelName() {
  gb.display.clear();
  drawBackground(currentLevel);
  gb.display.fontSize = 2;
  gb.display.setCursor(14, gb.display.height() / 2);
  gb.display.print("LEVEL ");
  gb.display.print(currentLevel);
  delay(800);
  levelNameScreen = false;
}
