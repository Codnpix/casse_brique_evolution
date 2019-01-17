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
  if (!launched) {
    ballX = padX + PAD_W / 2 - BALL_SIZE / 2;
  }
  displayGame();
}
