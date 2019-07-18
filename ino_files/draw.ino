void colour(int farbe){  // Farbdefinitionen - selbsterklärend
  switch(farbe){
    case RED:
      myScreen.fill(0,0,255);
      myScreen.stroke(0,0,255); break;
    case GREEN:
      myScreen.fill(0,255,0);
      myScreen.stroke(0,255,0); break;
    case BLUE:
      myScreen.fill(255,0,0);
      myScreen.stroke(255,0,0); break;
    case LIGHTBLUE:
      myScreen.fill(255,128,128);
      myScreen.stroke(255,128,128);break;
    case GREY:
      myScreen.fill(64,64,64);
      myScreen.stroke(64,64,64);break;
    case BLACK:
      myScreen.fill(0,0,0);
      myScreen.stroke(0,0,0); break;
    default:
      myScreen.stroke(0,0,255);  
  }
}

void drawBall() { // Das Bedarf einer gesonderten Erklärung, siehe Beitrag
  int formerBallXPos, formerBallYPos;
  switch (currentFlightDir) {
    case DIR_LU:
      formerBallXPos = currentBallXPos + 2;
      formerBallYPos = currentBallYPos + 1;
      myScreen.rect(formerBallXPos - 2, formerBallYPos, BALL_WIDTH, BALL_WIDTH);
      colour(BLACK);
      myScreen.rect(formerBallXPos + 2, formerBallYPos, 2, 4);
      delayMicroseconds(BALLDELAY);
      colour(GREEN);
      myScreen.rect(formerBallXPos - 2, formerBallYPos - 1, BALL_WIDTH, BALL_WIDTH);
      colour(BLACK);
      myScreen.line(formerBallXPos - 2, formerBallYPos + 3, formerBallXPos + 2, formerBallYPos + 3);
      delayMicroseconds(BALLDELAY2);
      break;

    case DIR_LD:
      formerBallXPos = currentBallXPos + 2;
      formerBallYPos = currentBallYPos - 1;
      myScreen.rect(formerBallXPos - 2, formerBallYPos, BALL_WIDTH, BALL_WIDTH);
      colour(BLACK);
      myScreen.rect(formerBallXPos + 2, formerBallYPos, 2, 4);
      delayMicroseconds(BALLDELAY);
      colour(GREEN);
      myScreen.rect(formerBallXPos - 2, formerBallYPos + 1, BALL_WIDTH, BALL_WIDTH);
      colour(BLACK);
      myScreen.line(formerBallXPos - 2, formerBallYPos, formerBallXPos + 2, formerBallYPos);
      delayMicroseconds(BALLDELAY2);
      break;

    case DIR_RU:
      formerBallXPos = currentBallXPos - 2;
      formerBallYPos = currentBallYPos + 1;
      myScreen.rect(formerBallXPos + 2, formerBallYPos, BALL_WIDTH, BALL_WIDTH);
      colour(BLACK);
      myScreen.rect(formerBallXPos, formerBallYPos, 2, 4);
      delayMicroseconds(BALLDELAY);
      colour(GREEN);
      myScreen.rect(formerBallXPos + 2, formerBallYPos - 1, BALL_WIDTH, BALL_WIDTH);
      colour(BLACK);
      myScreen.line(formerBallXPos + 2, formerBallYPos + 3, formerBallXPos + 6, formerBallYPos + 3);
      delayMicroseconds(BALLDELAY2);
      break;

    case DIR_RD:
      formerBallXPos = currentBallXPos - 2;
      formerBallYPos = currentBallYPos - 1;
      myScreen.rect(formerBallXPos + 2, formerBallYPos, BALL_WIDTH, BALL_WIDTH);
      colour(BLACK);
      myScreen.rect(formerBallXPos, formerBallYPos, 2, 4);
      delayMicroseconds(BALLDELAY);
      colour(GREEN);
      myScreen.rect(formerBallXPos + 2, formerBallYPos + 1, BALL_WIDTH, BALL_WIDTH);
      colour(BLACK);
      myScreen.line(formerBallXPos + 2, formerBallYPos, formerBallXPos + 6, formerBallYPos);
      delayMicroseconds(BALLDELAY2);
      break;
  }
  colour(GREEN);
}

void deleteBall(){ // Geht ein Ball über die "Torlinie", muss er komplett gelöscht werden
  colour(BLACK);
  myScreen.rect(currentBallXPos, currentBallYPos, BALL_WIDTH, BALL_WIDTH);
}

void drawRacket(racketSide racket) { // zeichnet einen neuen Schläger
  colour(GREEN);
  switch (racket) {
    case LEFT:
      myScreen.rect(LEFT_RACKET_XPOS, currentLeftRacketYPos, RACKET_WIDTH, RACKET_HEIGHT);
      break;
    case RIGHT:
      myScreen.rect(RIGHT_RACKET_XPOS, currentRightRacketYPos, RACKET_WIDTH, RACKET_HEIGHT);
      break;
  }
}

void moveRacketsToNewPos(bool newField) {  // zieht den Schläger in die aktuelle Position
  static int prevLeftYPos = currentLeftRacketYPos;
  static int prevRightYPos = currentRightRacketYPos;

  if(newField){
    prevLeftYPos = currentLeftRacketYPos;
    prevRightYPos = currentRightRacketYPos;
  }

  while (prevLeftYPos < currentLeftRacketYPos) { //fuege Balken oben zu, loesche untere Balken
    colour(GREEN);
    myScreen.line(LEFT_RACKET_XPOS, prevLeftYPos + RACKET_HEIGHT, LEFT_RACKET_XPOS + RACKET_WIDTH , prevLeftYPos + RACKET_HEIGHT);
    colour(BLACK);
    myScreen.line(LEFT_RACKET_XPOS, prevLeftYPos, LEFT_RACKET_XPOS + RACKET_WIDTH , prevLeftYPos);
    prevLeftYPos++;
  }
  while (currentLeftRacketYPos < prevLeftYPos) { // andersrum
    colour(BLACK);
    myScreen.line(LEFT_RACKET_XPOS, prevLeftYPos + RACKET_HEIGHT, LEFT_RACKET_XPOS + RACKET_WIDTH , prevLeftYPos + RACKET_HEIGHT);
    colour(GREEN);
    myScreen.line(LEFT_RACKET_XPOS, prevLeftYPos, LEFT_RACKET_XPOS + RACKET_WIDTH , prevLeftYPos);
    prevLeftYPos--;
  }
  while (prevRightYPos < currentRightRacketYPos) { //fuege Balken oben zu, loesche untere Balken
    colour(GREEN);
    myScreen.line(RIGHT_RACKET_XPOS, prevRightYPos + RACKET_HEIGHT, RIGHT_RACKET_XPOS + RACKET_WIDTH , prevRightYPos + RACKET_HEIGHT);
    colour(BLACK);
    myScreen.line(RIGHT_RACKET_XPOS, prevRightYPos, RIGHT_RACKET_XPOS + RACKET_WIDTH , prevRightYPos);
    prevRightYPos++;
  }
  while (currentRightRacketYPos < prevRightYPos) { // andersrum
    colour(BLACK);
    myScreen.line(RIGHT_RACKET_XPOS, prevRightYPos + RACKET_HEIGHT, RIGHT_RACKET_XPOS + RACKET_WIDTH , prevRightYPos + RACKET_HEIGHT);
    colour(GREEN);
    myScreen.line(RIGHT_RACKET_XPOS, prevRightYPos, RIGHT_RACKET_XPOS + RACKET_WIDTH , prevRightYPos);
    prevRightYPos--;
  }
  colour(GREEN);
}

void showScore(){ // zeige den Spielstand
  char buf[3];
  int leftScoreXPos;// x Position der Punkte des linken Spielers 
  int rightScoreXPos;
  (score[0]<10)?(leftScoreXPos=35):(leftScoreXPos=20); // Position in Abhaegigkeit ein-/zweistellig
  (score[1]<10)?(rightScoreXPos=115):(rightScoreXPos=100);
  myScreen.background(0,0,0);
  colour(LIGHTBLUE);
  if(score[0]<WINSCORE && score[1]<WINSCORE){ //wenn noch kein Endstand erreicht ist
    itoa(score[0], buf, 10);
    myScreen.text(buf,leftScoreXPos,50);
    itoa(score[1], buf, 10);
    myScreen.text(buf,rightScoreXPos,50);
    myScreen.text(":",75,50);
    delay(1500);
  }
  else{
    if(score[0]==WINSCORE) colour(GREEN); // Endstand erreicht
    else colour(RED);
    itoa(score[0], buf, 10);
    myScreen.text(buf,leftScoreXPos,50);
    colour(LIGHTBLUE);
    myScreen.text(":",75,50);
    if(score[1]==WINSCORE) colour(GREEN);
    else colour(RED);
    itoa(score[1], buf, 10);
    myScreen.text(buf,rightScoreXPos,50);
    while(!gameReset){/*WAIT*/}
  }
}

void resetField(){
  unsigned long prevTime = millis();
  myScreen.background(0,0,0);
  delay(100);  
  colour(GREEN);  
  checkPositions();
  drawRacket(LEFT);
  drawRacket(RIGHT);
  moveRacketsToNewPos(true);
  while((millis()-prevTime) < 1000){
    delay(5);
    checkPositions();
    moveRacketsToNewPos(false);
  }
}
