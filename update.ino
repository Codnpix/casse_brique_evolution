//UPDATE
void updateGame() {

  bool touched = false;
  bool pushed = false;
  
  int int_ballX = floor(ballX);
  int int_ballY = floor(ballY);
  int ballTop = int_ballY;
  int ballBottom = int_ballY + BALL_SIZE;
  int ballLeft = int_ballX;
  int ballRight = int_ballX + BALL_SIZE;

  //collision balle/palette
  if (int_ballX + BALL_SIZE > padX
  && int_ballX - BALL_SIZE < padX + PAD_W
  && ballBottom > PAD_Y) {
    float dist = (padX + PAD_W / 2) - (ballX + BALL_SIZE / 2);
    if (dist != 0) {//éviter la division par 0
      speedX = - 1 / dist;
      if (abs(speedX) < MAX_SPEED_X) {
        if (speedX < 0) speedX -= 0.50;
        else if (speedX > 0) speedX += 0.50;
      } else if (abs(speedX) >= MAX_SPEED_X) {
        if (speedX < 0) speedX = -MAX_SPEED_X;
        else if (speedX > 0) speedX = MAX_SPEED_X;
      }
    } else {
      speedX = 0;
    }
    speedY *= -1;
  }
  
  if (ballTop <= 0) {//collision plafond
    speedY *= -1;
  }
    
  if (ballRight >= gb.display.width() || ballLeft <= 0) {//collision murs
    if (speedX > 0) {
      if (fabs(speedX <= 0.35)) {
        speedX += ANGLE_CORRECTOR;
      }
    } else if (speedX < 0) {
      if (fabs(speedX <= 0.35)) {
        speedX -= ANGLE_CORRECTOR;
      }
    } else {
      speedX = speedX;
    }
    speedX *= -1;
  }
  //perdu !(si on passe en dessous de la ligne sous la palette
  if (ballY + BALL_SIZE > PAD_Y + PAD_H + 1) {
    initGame();
  }

  //collisions briques
  for (int rangee = 0; rangee < NB_RANGEES; rangee++) {
    for (int colonne = 0; colonne < NB_COLONNES; colonne++) {

      int briqueLeft = briques[rangee][colonne].x;
      int briqueTop = briques[rangee][colonne].y;
      int briqueBottom = briques[rangee][colonne].y + BRICK_H;
      int briqueRight = briques[rangee][colonne].x + BRICK_W;

      //si la brique a été détruite, ignorer la collision (sauf pour -2 car c'est l'état par défaut des briques métal);
      if(briques[rangee][colonne].state <= 0 && briques[rangee][colonne].state > -2 ) continue;
      
      if (touched) continue;

      if (ballRight >= briqueLeft - 1
      && ballLeft <= briqueRight + 1
      && ballTop <= briqueBottom + 1
      && ballBottom >= briqueTop - 1) {//si la balle entre en collision avec une des 4 côtéds de la brique
        if (!touched) {
          if (ballTop <= briqueBottom - 1
          && ballBottom >= briqueTop + 1
          && ballLeft <= briqueRight + 1
          && ballRight >= briqueLeft - 1) {
            if (abs(speedX) < 0.35) {
              speedX *= -(1+ ANGLE_CORRECTOR);
              if (!pushed) {
                /*repousser la balle de 1 en cas de collision pour qu'elle sorte de la 
                 * condition de collision et éviter de tomber dans une boucle infinie de 
                 * changement de directions
                 */
                if (speedX > 0) ballX += 1.0;
                else if (speedX < 0) ballX -= 1.0;
                pushed = true;
              }
            }
            else {
              speedX *= -1;
              if (!pushed) {
                if (speedX > 0) ballX += 1.0;
                else if (speedX < 0) ballX -= 1.0;
                pushed = true;
              }
            }
          }
          else {
            speedY *= -1;
            if (!pushed) {
              if (speedY > 0) ballY += 1.0;
              else if (speedY < 0) ballY -= 1.0;
              pushed = true;
            }
          }
          gb.sound.playTick();
          briques[rangee][colonne].state --;//abimer ou détruire la brique
          touched = true;
        }
      }

      //changer l'image des brique dures quand elles ont pris un coup mais pas encore détruite
      if (briques[rangee][colonne].type == 2 && briques[rangee][colonne].state == 1) {
        briques[rangee][colonne].img = brick2_dmg;
      }
      
      //jouer un son quand une brique est détruite
      if (briques[rangee][colonne].state <=0 && briques[rangee][colonne].state > -2) {
        gb.sound.playOK();
      }
      
      bool zeroBriques = true;
      //verifier s'il reste des briques (sauf metal)
      for (int x = 0; x < NB_RANGEES; x++) {
        for (int y = 0; y < NB_COLONNES; y++) {
          if (briques[x][y].state > 0) {
            zeroBriques = false;
          }
        }
      }
      if (zeroBriques) {
        currentLevel ++;
        initGame();
      }
    }
  }
  speedX = calc_speedX(speedX);
  //speedY = calc_speedY(speedY);
  ballX += speedX;
  ballY += speedY;
}

//bouger la palette
void movePad(char dir[6]) {
  if (dir == "left") {
    if (padX <=0) {
      padX = 0;
    } else {
      padX -= 2;
    }
  }
  else if (dir == "right") {
    if (padX + PAD_W >= gb.display.width()) {
      padX = gb.display.width() - PAD_W;
    } else {
      padX += 2;
    }
  } else {
    padX = padX;
  }
}

float calc_speedX(float speedX) {
  float valX = fabs(speedX);
  if (speedX > 0) {
    if (valX >= MAX_SPEED_X) {
      speedX = MAX_SPEED_X;
    }
  } else if (speedX < 0) {
    if (valX >= MAX_SPEED_X) {
      speedX = -MAX_SPEED_X;
    }
  }
  return speedX;
}

/*float calc_speedY(float speedY) {
  float valY = 1.5 - fabs(speedX);
  if (speedY > 0) {
    speedY = valY;
  } else if (speedY < 0) {
    speedY =  - valY;
  }
  return speedY;
}*/
