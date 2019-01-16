void displayMenu() {
  gb.display.clear();
  drawBackground(currentLevel);
  gb.display.fontSize = 2;
  gb.display.setCursor(14, gb.display.height() / 3);
  gb.display.print("LEVEL ");
  gb.display.println(currentLevel);
  gb.display.fontSize = 1;
  gb.display.setColor(YELLOW);
  gb.display.setCursorX(20);
  gb.display.println(levelNames[currentLevel - 1]);
}
