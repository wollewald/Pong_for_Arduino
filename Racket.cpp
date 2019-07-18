#include "Racket.h"

Racket::Racket(){	
}

Racket::Racket(int xp, int pp){
	xPos = xp;
	potiPin = pp;
}

void Racket::setXPos(int xp){
	xPos = xp;
}

int Racket::getXPos(){
	return xPos;
}

int Racket::getYPos(){
	int yPosRaw; 
	yPosRaw = analogRead(potiPin);
	if (yPosRaw<minPotiVal) yPosRaw = minPotiVal;
	if (yPosRaw>maxPotiVal) yPosRaw = maxPotiVal;
	return(map(yPosRaw,minPotiVal,maxPotiVal,0,downScreenBorder-racketHeight)); 
}



