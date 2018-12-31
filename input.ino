//INPUTS
void getInputs() {
  if (gb.buttons.pressed(BUTTON_A)) {
    launched = true;
  }
  if (gb.buttons.repeat(BUTTON_LEFT,0)) {
    movePad("left");
  }
  if (gb.buttons.repeat(BUTTON_RIGHT,0)) {
    movePad("right");
  }
}
