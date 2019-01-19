void setup() {
  gb.begin();
  
  //gb.save.config(savefileDefaults);
  
  lastUnlockedLevel = max(1, gb.save.get(SAVE_LAST_UNLOCKED_LEVEL));

  currentLevel = lastUnlockedLevel;

  chosenLevel = currentLevel;
  displayMenu();
}

void loop() {
  
  while(!gb.update());

  getInputs();
  
  if (launched && gameOn) {
    updateGame();
  }
  if (!launched) {
    ballX = padX + PAD_W / 2 - BALL_SIZE / 2;
  }
  displayGame();
}
