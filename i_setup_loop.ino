void setup() {
  gb.begin();
  displayMenu();
}

void loop() {
  
  while(!gb.update());

  getInputs();
  
  if (launched) {
    updateGame();
  }
  if (!launched) {//tant que la balle n'est pas lancée, la déplacer en même temps que la palette, pour choisir l'endroit ou on lance.
    ballX = padX + PAD_W / 2 - BALL_SIZE / 2;
  }
  displayGame();
}
