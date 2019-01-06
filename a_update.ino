//UPDATE
void updateGame() {

  bool touched = false;
  
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
    float dist = (ballX + BALL_SIZE / 2) - (padX + PAD_W / 2);//calculer la position de la balle par rapport au centre de la palette
    float inv_speedX;
    if (dist != 0) {//éviter la division par 0
      speedX = 1 / (1/ dist);//calculer le sens et la valeur de l'angle du rebond en fonction de la position de la balle
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
    lose = true;
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

      if (ballRight >= briqueLeft
      && ballLeft <= briqueRight
      && ballTop <= briqueBottom
      && ballBottom >= briqueTop) {//si la balle entre en collision avec une des 4 côtés de la brique
        if (!touched) {
          if (ballTop <= briqueBottom - 1
          && ballBottom >= briqueTop + 1) {//si la balle est à hauteur des côtés de la brique
            if (ballRight > briqueRight) {//côté droit
              if (abs(speedX) < 0.35) speedX = (1+ ANGLE_CORRECTOR);//si l'angle en X est trop faible, le corriger un peu
              else speedX = 1;
            }
            else if (ballLeft < briqueLeft) {//côté gauche
              if (abs(speedX) < 0.35) speedX = -(1+ ANGLE_CORRECTOR);
              else speedX = -1;
            }
            
          }
          else if (ballTop >= briqueBottom - 1) {//si la balle tape le bas de la brique
            speedY = 1;
          }
          else if (ballBottom <= briqueTop + 1) {//si la balle tape le haut de la brique
            speedY = -1;
          }

          //quelle que soit l'endroit de la collision
          gb.sound.playTick();
          briques[rangee][colonne].state --;//abimer ou détruire la brique
          touched = true;//pour ne pas risquer de rerentrer en boucle dans la condition de collision
        }
        else continue;//si pas de collision, ne rien faire
      }

      //changer l'image des brique dures quand elles ont pris un coup mais pas encore détruite
      if (briques[rangee][colonne].type == 2 && briques[rangee][colonne].state == 1) {
        briques[rangee][colonne].img = brick2_dmg;
      }
      if (briques[rangee][colonne].type == 5 && briques[rangee][colonne].state == 2) {
        briques[rangee][colonne].img = brick5_dmg;
      }
      if (briques[rangee][colonne].type == 5 && briques[rangee][colonne].state == 1) {
        briques[rangee][colonne].img = brick5_dmg2;
      }
      if (briques[rangee][colonne].type == 4 && briques[rangee][colonne].state == 1) {
        briques[rangee][colonne].img = brick4_dmg;
      }
      
      //jouer un son quand une brique est détruite
      if (briques[rangee][colonne].state <=0 && briques[rangee][colonne].state > -2) {
        gb.sound.playOK();
      }

      //briques défilantes (types 4 et 5)
      if (briques[rangee][colonne].type == 4 || briques[rangee][colonne].type == 5) {
        briques[rangee][colonne].x += 1;
        if (briques[rangee][colonne].x >= gb.display.width()) {
          briques[rangee][colonne].x = 0 - BRICK_W;
        }
      }
      //brique défilantes en cercle (types 6 et 7)
      if (briques[rangee][colonne].type == 6 || briques[rangee][colonne].type == 7) {
          if (angle >= 360) angle = 0;
          angle += 1;
          briques[rangee][colonne].x = int(cos(angle * PI/180) * radius) + (colonne * BRICK_W + 1) + 1;
          briques[rangee][colonne].y = int(sin(angle * PI/180) * radius) + (rangee * BRICK_H + 1) + 1;
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
        //currentLevel ++;
        win = true;
      }
    }
  }
  speedX = calc_speedX(speedX);//recalculer speedX pour qu'il ne dépasse jamais sa vitesse max
  
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
