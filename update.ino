//UPDATE
void updateGame() {

  //collision balle/palette
  if (ballX >= padX && ballX <= padX + PAD_W && ballY + BALL_RADIUS >= PAD_Y) {
      if ((ballX >= padX && ballX <= padX + PAD_W && ballY + BALL_RADIUS >= gb.display.height() - PAD_H)) {

      float dist_edgePad_left = ballX - padX;//distance balle/côté gauche pad
      float dist_edgePad_right = (padX + PAD_W) - ballX;//distance ball/côté droit pad
        
        if (dist_edgePad_right > dist_edgePad_left) {//si la balle tape du côté gauche de la palette
          speedX = max(-1 / dist_edgePad_left, -1);//speedX augmente si on se rapproche du bord(speeX max = -1)(la balle part vers la gauche)
        }
        else if (dist_edgePad_left > dist_edgePad_right) {//si elle tape du côté gauche
          speedX = min(1 / dist_edgePad_right, 1);//speedX augmente si on se rapproche du bord(speeX max = 1)(ball part vers la droite)
        } 
        else {
          speedX = 0;//si on tape au milieu, la balle rebondit verticalement.
        }

      speedY *= -1;
    }
  }
  if (ballY - BALL_RADIUS <= 0) {//collision plafond
    speedY *= -1;
  }
    
  else if (ballX + BALL_RADIUS +1 >= gb.display.width() || ballX - BALL_RADIUS -1 <= 0) {//collision murs
    speedX *= -1;
  }
  //perdu !
  else if (ballY + BALL_RADIUS >= gb.display.height()) {
    initGame();
  }

  //collisions briques
  for (int rangee = 0; rangee < NB_RANGEES; rangee++) {
    for (int colonne = 0; colonne < NB_COLONNES; colonne++) {
      
      int briqueX = briques[rangee][colonne].x;
      int briqueY = briques[rangee][colonne].y;
      int briqueTop = briqueY;
      int briqueBottom = briques[rangee][colonne].y + BRICK_H;
      int briqueLeft = briqueX;
      int briqueRight = briques[rangee][colonne].x + BRICK_W;
      float ballTop = ballY - BALL_RADIUS + 1;
      float ballBottom = ballY + BALL_RADIUS - 1;
      float ballLeft = ballX - BALL_RADIUS + 1;
      float ballRight = ballX + BALL_RADIUS - 1;

      bool touched = false;
      
      if(briques[rangee][colonne].state <= 0 && briques[rangee][colonne].state > -2 ) {
        //si la brique a été détruite, ignorer la collision (sauf pour -2 car c'est l'état par défaut des briques métal);
        continue;
      }
      
      //pour les collision par le dessus ou le dessous des briques
      //commencer par vérifier si la balle est en face de la brique verticalement
      if ((ballRight >= briqueLeft && ballLeft <= briqueRight)
      && (ballTop <= briqueBottom + 1 && ballBottom >= briqueTop - 1)) {//puis vérifier si il y a un chevauchement en y
        if (!touched) {//pour que ça ne s'execute qu'une fois par collision
          speedY *= -1;//faire rebondir la balle
          gb.sound.playTick();
          briques[rangee][colonne].state --;//abimer ou détruire la brique
          if (briques[rangee][colonne].state <=0 && briques[rangee][colonne].state > -2) {
            gb.sound.playOK();
          }
          touched = true;
        }
      }
      
      //pour les collisions sur les côtés des briques
      //vérifier si on est aligné horizontalement avec la brique
      if ((ballTop <= briqueBottom && ballBottom >= briqueTop) 
      && (ballRight >= briqueLeft - 1 && ballLeft <= briqueRight + 1)) {//puis vérifier le chevauchement en x
        if (!touched) {
          speedX *= -1; //faire rebondir la balle
          gb.sound.playTick();
          briques[rangee][colonne].state --;//abimer ou détruire la brique
          if (briques[rangee][colonne].state <=0 && briques[rangee][colonne].state > -2) {
            gb.sound.playOK();
          }
          touched = true;
        }
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
      if (touched == true) {
        continue;
      }
    }
  }

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
