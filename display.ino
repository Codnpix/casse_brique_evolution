//DISPLAY

void displayGame() {
  gb.display.clear();
  drawBackground(currentLevel);
  
  //ligne limite bas
  gb.display.setColor(DARKGRAY);
  gb.display.drawLine(0, PAD_Y + PAD_H, gb.display.width(), PAD_Y + PAD_H);
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
