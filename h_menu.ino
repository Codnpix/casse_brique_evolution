//MENU
void displayMenu() {
  
  gb.display.clear();
  drawBackground(currentLevel);
  
  gb.display.fontSize = 2;
  gb.display.setCursor(13, gb.display.height() / 3);
  gb.display.print("LEVEL ");
  gb.display.println(currentLevel);

  gb.display.setCursor(0, gb.display.height() / 2);
  gb.display.print("<");

  gb.display.setCursor(gb.display.width() -8, gb.display.height() / 2);
  gb.display.print(">");
  
  gb.display.fontSize = 1;
  gb.display.setColor(YELLOW);
  gb.display.setCursorX(16);
  gb.display.println(levelNames[currentLevel - 1]);
}
