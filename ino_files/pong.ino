#include <TFT.h>
#include <SPI.h>
#include <Ball.h>  // Bibliothek für den Ball
#include <Racket.h>  // Bibliothek für den Schläger
#define CS   10 // Chip Select Pin
#define DC   8  // Data / Command Pin
#define RESET  9  // Reset Pin
#define TAST_PIN 2  // Taster Pin für Game Reset
#define RED 1  // Farbendefinition -> siehe colour funktion
#define BLUE 2
#define GREEN 3
#define BLACK 4
#define LIGHTBLUE 5
#define GREY 6
#define RIGHT_RACKET_XPOS 148  // x-Position rechter Schlaeger
#define RIGHT_RACKET_POTI_PIN 1 // der Pin für den Poti vom rechten Schlaeger
#define LEFT_RACKET_XPOS 10 // x-Position linker Schlaeger
#define LEFT_RACKET_POTI_PIN 0 // der Pin für den Poti vom linken Schlaeger 
#define WINSCORE 15 // Bei 15 gewinnt man
#define BALLDELAY 1000 // Verzögerungswert 1
#define BALLDELAY2 6500 // Verzögerungswert 2

volatile bool gameReset; // steuert den Spielreset, wird "TRUE" bei Tasterdruck (Interrupt)
const int RACKET_WIDTH = 2; // Schlaeger Breite
const int RACKET_HEIGHT = 12; // Schlaeger Hoehe
const int BALL_WIDTH = 4; // Der Ball ist 4x4 Pixel groß
int currentLeftRacketYPos; // y Position linker Schlaeger 
int currentRightRacketYPos; // y Position rechter Schlager
int currentBallXPos; // x Position Ball
int currentBallYPos; // y Position Ball
// Position bedeutet: Koordinaten der linken oberen Ecke
int score[2]={0,0}; // Spielstand
BallDir currentFlightDir; // Flugrichtung des Balls (in Ball.h definiert)

TFT myScreen = TFT(CS, DC, RESET);
Ball myBall;
Racket leftRacket(LEFT_RACKET_XPOS, LEFT_RACKET_POTI_PIN);
Racket rightRacket(RIGHT_RACKET_XPOS, RIGHT_RACKET_POTI_PIN);
enum racketSide {LEFT=0,RIGHT} racket;

void setup(){
  pinMode(TAST_PIN, INPUT_PULLUP); // Tasterpin: bei Low ist aktiv
  attachInterrupt(digitalPinToInterrupt(TAST_PIN), gameResetPress, FALLING);
  myScreen.begin();  // Bildschirm wird initialisiert
  myScreen.setRotation(1); // Bildchirm wird gedreht (0/0 = oben links)
  myScreen.setTextSize(4); // Textgroesse fuer Spielstand
  myScreen.background(0,0,0);  // einmal Bildschirm schwarz machen
  showScore(); // Spielstand (hier 0:0) wird angezeigt
  resetField(); // das Spielfeld wird angelegt, die Schläger erscheinen
  myBall.newBall(); // jetzt komt der Ball ins Spiel
  gameReset = false; // kein Reset bis Tasterduck 
}

void loop(){  
  myBall.move(); // Der Ball macht einen Schritt
  checkPositions(); // die Position der Schläger, des Balls und die Flugrichtung werden ermittelt
  drawBall(); // der Ball wird an der neuen Position "gemalt" und die alten Pixel gelöscht
  myBall.fenceCheck(); // Check ob der Ball die Bande berührt
  // Check, ob der Ball einen Schläger (von der richtigen Seite!) berührt
  myBall.racketHitCheck(LEFT_RACKET_XPOS, currentLeftRacketYPos, RIGHT_RACKET_XPOS, currentRightRacketYPos, BALL_WIDTH, RACKET_HEIGHT, RACKET_WIDTH);
  moveRacketsToNewPos(false); // der Schläger bewegt sich zur aktuellen Position
  if(myBall.goalCheck()){ // Wenn der Ball ueber die Linie geht, dann.....
    deleteBall(); // Randpixel beseitigen
    if((currentFlightDir==DIR_RU)||(currentFlightDir==DIR_RD)) score[0]++; // wessen Punkt?
    else score[1]++;
    showScore();
    if(!gameReset){ // nächste Runde innerhalb eines Spiels
      resetField();
      myBall.newBall();
    }
    else newGame(); // neues Spiel 
  }
}

void gameResetPress(){  // Routine für den Interrupt
  gameReset=true; 
}

void newGame(){ // Routine für neues Spiel - selbsterklärend
   myBall.newBall(NEW_BALL);
   score[0]=0; score[1]=0;
   showScore();
   resetField();
   gameReset=false;  
}

void checkPositions(){ // Positionsermittlungen
  currentLeftRacketYPos = leftRacket.getYPos();
  currentRightRacketYPos = rightRacket.getYPos();
  currentBallXPos = myBall.getXPos();
  currentBallYPos = myBall.getYPos(); 
  currentFlightDir = myBall.getFlightDir(); 
}
