//UPDATE
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

void updateGame() {
  
  bool touched = false;
  unsigned long currentTime = millis();
  
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
    float dist = (ballX + BALL_SIZE / 2) - (padX + PAD_W / 2);
    if (dist != 0) {//éviter la division par 0
      speedX = 1 / (1/ dist);
    } else {
      speedX = 0;
    }
    speedY *= -1;
  }
  
  if (ballTop <= -2) {//collide top wall
    speedY *= -1;
  }
    
  if (ballRight >= gb.display.width() || ballLeft <= 0) {//collide side walls
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
  //passed bellow paddle, you lose!
  if (ballY + BALL_SIZE > PAD_Y + PAD_H + 1) {
    lose = true;
  }

  
  for (int rangee = 0; rangee < NB_RANGEES; rangee++) {
    for (int colonne = 0; colonne < NB_COLONNES; colonne++) {

      int briqueLeft = briques[rangee][colonne].x;
      int briqueTop = briques[rangee][colonne].y;
      int briqueBottom = briques[rangee][colonne].y + BRICK_H;
      int briqueRight = briques[rangee][colonne].x + BRICK_W;

      //ignore destroyed bricks
      if(briques[rangee][colonne].state <= 0 && briques[rangee][colonne].type != 3 ) {
        //respawn bricks type 8 9 10 11 after interval is passed
        if (briques[rangee][colonne].type == 8 
        || briques[rangee][colonne].type == 9 
        || briques[rangee][colonne].type == 10 
        || briques[rangee][colonne].type == 11) {
          if (currentTime > briques[rangee][colonne].deathTime + RESPAWN_INTERVAL) {
            if (briques[rangee][colonne].type == 8 
            || briques[rangee][colonne].type == 10) briques[rangee][colonne].state = 1;
            else briques[rangee][colonne].state = 2;
          }
        }
        continue;
      }
      
      //collide ball-brick
      if (ballRight >= briqueLeft
      && ballLeft <= briqueRight
      && ballTop <= briqueBottom
      && ballBottom >= briqueTop) {
        if (!touched) {
          if (ballTop <= briqueBottom - 1
          && ballBottom >= briqueTop + 1) {
            if (ballRight > briqueRight) {
              if (abs(speedX) < 0.35) speedX = (1+ ANGLE_CORRECTOR);
              else speedX = 1;
            }
            else if (ballLeft < briqueLeft) {
              if (abs(speedX) < 0.35) speedX = -(1+ ANGLE_CORRECTOR);
              else speedX = -1;
            }
            
          }
          else if (ballTop >= briqueBottom - 1) {
            speedY = 1;
          }
          else if (ballBottom <= briqueTop + 1) {
            speedY = -1;
          }
          
          gb.sound.playTick();
          briques[rangee][colonne].state --;
          touched = true;
        }
        else continue;
      }

      //update images for damaged bricks - not destroyed yet
      if (briques[rangee][colonne].type == 2 && briques[rangee][colonne].state == 1) {
        briques[rangee][colonne].img = brick2_dmg;
      }
      if (briques[rangee][colonne].type == 5 && briques[rangee][colonne].state == 2) {
        briques[rangee][colonne].img = brick5_dmg;
      }
      if (briques[rangee][colonne].type == 5 && briques[rangee][colonne].state == 1) {
        briques[rangee][colonne].img = brick5_dmg2;
      }
      if (briques[rangee][colonne].type == 6 && briques[rangee][colonne].state == 1) {
        briques[rangee][colonne].img = brick6_dmg;
      }
      if (briques[rangee][colonne].type == 4 && briques[rangee][colonne].state == 1) {
        briques[rangee][colonne].img = brick4_dmg;
      }
      if (briques[rangee][colonne].type == 7 && briques[rangee][colonne].state == 1) {
        briques[rangee][colonne].img = brick7_dmg;
      }
      if (briques[rangee][colonne].type == 9 && briques[rangee][colonne].state == 1) {
        briques[rangee][colonne].img = brick9_dmg;
      }
      if (briques[rangee][colonne].type == 11 && briques[rangee][colonne].state == 1) {
        briques[rangee][colonne].img = brick11_dmg;
      }
      if (briques[rangee][colonne].type == 9 && briques[rangee][colonne].state >1) {//rétablir l'image de début si respawn (type 8 9 10 11)
        briques[rangee][colonne].img = brick9;
      }
      if (briques[rangee][colonne].type == 11 && briques[rangee][colonne].state >1) {
        briques[rangee][colonne].img = brick11;
      }
      
      //play sound when a brick is destroyed
      if (briques[rangee][colonne].state <=0 && briques[rangee][colonne].type != 3) {
        gb.sound.playOK();
      }
      //noter l'heure de la destruction des briques type 8 9 10 11 pour les faire respawner après l'interval.
        if (briques[rangee][colonne].type == 8 || briques[rangee][colonne].type == 9 
        || briques[rangee][colonne].type == 10 || briques[rangee][colonne].type == 11 
        && briques[rangee][colonne].state <=0) {
          briques[rangee][colonne].deathTime = millis();
        }
      

      //moving bricks, linear loop left to right(types 4 et 5)
      if (briques[rangee][colonne].type == 4 || briques[rangee][colonne].type == 5) {
        briques[rangee][colonne].x += 1;
        if (briques[rangee][colonne].x >= gb.display.width()) {
          briques[rangee][colonne].x = - BRICK_W;
        }
      }
      
      //moving bricks, switch left to right then right to left... (types 6 et 7)
      //6 : mvt horizontal
      if (briques[rangee][colonne].type == 6) {
        briques[rangee][colonne].x += briques[rangee][colonne].speedX;
        if (briques[rangee][colonne].x >= (colonne + edgesXY[currentLevel-1][0]) * (BRICK_W + 1) + 1) {
          briques[rangee][colonne].speedX = edgesXY[currentLevel-1][4];
        } else if (briques[rangee][colonne].x <= (colonne + edgesXY[currentLevel-1][2]) * (BRICK_W + 1) + 1) {
          briques[rangee][colonne].speedX = edgesXY[currentLevel-1][6];
        }
      }
      //7 : mvt vertical
      if (briques[rangee][colonne].type == 7) {
        briques[rangee][colonne].y += briques[rangee][colonne].speedY;
        if (briques[rangee][colonne].y <= (rangee + edgesXY[currentLevel-1][1]) * (BRICK_H + 1) + 1) {
          briques[rangee][colonne].speedY = edgesXY[currentLevel-1][5];
        } else if (briques[rangee][colonne].y >= (rangee + edgesXY[currentLevel-1][3]) * (BRICK_H + 1) + 1) {
          briques[rangee][colonne].speedY = edgesXY[currentLevel-1][7];
        }
      }
      //bricks types 8 and 9, rectangle move
      if (briques[rangee][colonne].type == 8 || briques[rangee][colonne].type == 9) {
        briques[rangee][colonne].y += briques[rangee][colonne].speedY;
        briques[rangee][colonne].x += briques[rangee][colonne].speedX;
        
        //downright to upright
        if ((briques[rangee][colonne].x >= (colonne + edgesXY[currentLevel - 1][0]) * (BRICK_W + 1) + 1)
        && (briques[rangee][colonne].y >= (rangee + edgesXY[currentLevel - 1][1]) * (BRICK_H + 1) + 1)){
          briques[rangee][colonne].speedX = seqLvl6[0][0];
          briques[rangee][colonne].speedY = seqLvl6[0][1];
        } 
        //upright to upleft
        else if ((briques[rangee][colonne].x >= (colonne + edgesXY[currentLevel - 1][0]) * (BRICK_W + 1) + 1)
        && (briques[rangee][colonne].y <= (rangee + edgesXY[currentLevel - 1][3]) * (BRICK_H + 1) + 1)){
          briques[rangee][colonne].speedX = seqLvl6[1][0];
          briques[rangee][colonne].speedY = seqLvl6[1][1];
        }
        //upleft to downleft
        else if ((briques[rangee][colonne].x <= (colonne + edgesXY[currentLevel - 1][2]) * (BRICK_W + 1) + 1)
        && (briques[rangee][colonne].y <= (rangee + edgesXY[currentLevel - 1][3]) * (BRICK_H + 1) + 1)){
          briques[rangee][colonne].speedX = seqLvl6[2][0];
          briques[rangee][colonne].speedY = seqLvl6[2][1];
        }
        //downleft to downright
        else if ((briques[rangee][colonne].x <= (colonne + edgesXY[currentLevel - 1][2] ) * (BRICK_W + 1) + 1)
        && (briques[rangee][colonne].y >= (rangee + edgesXY[currentLevel - 1][1]) * (BRICK_H + 1) + 1)){
          briques[rangee][colonne].speedX = seqLvl6[3][0];
          briques[rangee][colonne].speedY = seqLvl6[3][1];
        }
      }
       //bricks types 10 and 11, rectangle move (invert from types 8 9)
      if (briques[rangee][colonne].type == 10 || briques[rangee][colonne].type == 11) {
        briques[rangee][colonne].y += briques[rangee][colonne].speedY;
        briques[rangee][colonne].x += briques[rangee][colonne].speedX;
        //upleft to downleft
        if ((briques[rangee][colonne].x <= (colonne + edgesXY[currentLevel - 1][0]) * (BRICK_W + 1) + 1)
        && (briques[rangee][colonne].y <= (rangee + edgesXY[currentLevel - 1][1]) * (BRICK_H + 1) + 1)){
          briques[rangee][colonne].speedX = seqLvl6inv[0][0];
          briques[rangee][colonne].speedY = seqLvl6inv[0][1];
        } 
        //downleft to downright
        else if ((briques[rangee][colonne].x <= (colonne + edgesXY[currentLevel - 1][0]) * (BRICK_W + 1) + 1)
        && (briques[rangee][colonne].y >= (rangee - edgesXY[currentLevel - 1][3]) * (BRICK_H + 1) + 1)){
          briques[rangee][colonne].speedX = seqLvl6inv[1][0];
          briques[rangee][colonne].speedY = seqLvl6inv[1][1];
        }
        //downright to upright
        else if ((briques[rangee][colonne].x >= (colonne - edgesXY[currentLevel - 1][2]) * (BRICK_W + 1) + 1)
        && (briques[rangee][colonne].y >= (rangee - edgesXY[currentLevel - 1][3]) * (BRICK_H + 1) + 1)){
          briques[rangee][colonne].speedX = seqLvl6inv[2][0];
          briques[rangee][colonne].speedY = seqLvl6inv[2][1];
        }
        //upright to upleft
        else if ((briques[rangee][colonne].x >= (colonne - edgesXY[currentLevel - 1][2]) * (BRICK_W + 1) + 1)
        && (briques[rangee][colonne].y <= (rangee + edgesXY[currentLevel - 1][1]) * (BRICK_H + 1) + 1)){
          briques[rangee][colonne].speedX = seqLvl6inv[3][0];
          briques[rangee][colonne].speedY = seqLvl6inv[3][1];
        }
      }
      
      bool zeroBriques = true;
      //check remaining bricks (except for metal bricks)
      for (int x = 0; x < NB_RANGEES; x++) {
        for (int y = 0; y < NB_COLONNES; y++) {
          if (briques[x][y].state > 0) {
            zeroBriques = false;
          }
        }
      }
      if (zeroBriques) {
        win = true;
      }
    }
  }
  
  speedX = calc_speedX(speedX);
  
  ballX += speedX;
  ballY += speedY;

}
