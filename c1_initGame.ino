//charger le niveau
void loadLevel(int myLevel) {
   // inutile de parcourir la première des 3 dimensions du tableau, 
   // la valeur de l'index qu'on cherche est donnée par currentLevel passé en paramètre
   // et il ne faut pas charger tous les niveaux à chaque fois.

  for (int rangee = 0; rangee < NB_RANGEES; rangee++) {
      for (int colonne = 0; colonne < NB_COLONNES; colonne++) {
        types_set[rangee][colonne] = levels[myLevel][rangee][colonne];
      }
    }
}

//initialisation du jeu (au lancement, ou a chaque fois qu'on perd)
void initGame() {
  levelNameScreen = true;
  if (currentLevel > NB_LEVELS) {//si le niveau à charger n'existe pas (encore), on charge le 1er niveau
    currentLevel = 1;
  }
  //balle pas encore lancée
  launched = false;
  loadLevel(currentLevel - 1);//- 1 car l'index du tableau de niveau commence à 0 et currentLevel commence à compter à 1.

  //reset position palette
  padX = gb.display.width() / 2 - PAD_W / 2;
  
  //reset position et valeurs balle
  ballX = padX + (PAD_W / 2) - (BALL_SIZE / 2);
  ballY = PAD_Y - BALL_SIZE - 1;
  speedX = 0;
  speedY = 1;

  //initialiser les briques
  for (int rangee = 0; rangee < NB_RANGEES; rangee ++) {
    for (int colonne = 0; colonne < NB_COLONNES; colonne++) {
      briques[rangee][colonne].type = types_set[rangee][colonne];//type de la brique
      briques[rangee][colonne].x = colonne * (BRICK_W + 1) + 1;//position x
      briques[rangee][colonne].y = rangee * (BRICK_H + 1) + 1;//position y
      if (briques[rangee][colonne].type == 1) {//état et image selon type
        briques[rangee][colonne].state = 1;
        briques[rangee][colonne].img = brick1;
      } else if (briques[rangee][colonne].type == 2) {
        briques[rangee][colonne].state = 2;//type 2, plus solide
        briques[rangee][colonne].img = brick2;
      } else if (briques[rangee][colonne].type == 3) {
        //type 3 indestructible (brique détruite et collision ignorée quand state <= 0, mais >-2)
        briques[rangee][colonne].state = -2; 
        briques[rangee][colonne].img = brick3;
      } else if (briques[rangee][colonne].type == 4) {
        briques[rangee][colonne].state = 2; 
        briques[rangee][colonne].img = brick4;
      } else if (briques[rangee][colonne].type == 5) {
          briques[rangee][colonne].state = 3; 
          briques[rangee][colonne].img = brick5;
      } else if (briques[rangee][colonne].type == 6) {
          briques[rangee][colonne].state = 1; 
          briques[rangee][colonne].img = brick6;
      } else if (briques[rangee][colonne].type == 7) {
          briques[rangee][colonne].state = 1; 
          briques[rangee][colonne].img = brick7;
      }
    }
  }
}
