#include "Ball.h"

Ball::Ball(){
	newBall(NEW_BALL);
}

void Ball::setFlightDir(BallDir fD){
	flightDir = fD;
}

void Ball::setXPos(int xp){
	xPos = xp;
}

void Ball::setYPos(int yp){
	yPos = yp;
}

int Ball::getXPos(){
	return xPos;
}

int Ball::getYPos(){
	return yPos;
}

BallDir Ball::getFlightDir(){
	return flightDir;
}

void Ball::newBall(){
	int randomNumber;
	randomNumber = random(0,999);
	yPos = 6 +(random((downScreenBorder-6)/2))*2;
	if(flightDir==NEW_BALL) (((random(0,999))%2)==0)?(flightDir = DIR_LU):(flightDir = DIR_RD);
	if((flightDir==DIR_LD) || (flightDir==DIR_LU)){
		(((randomNumber)%2)==0)?(flightDir = DIR_RU):(flightDir = DIR_RD);
		xPos=leftScreenBorder;	
	}
	else if((flightDir==DIR_RD) || (flightDir==DIR_RU)){
		(((randomNumber)%2)==0)?(flightDir = DIR_LU):(flightDir = DIR_LD);
		xPos=rightScreenBorder;	
	}
}

void Ball::newBall(BallDir fld){
	int randomNumber;
	randomSeed(analogRead(3));
	randomNumber = random(0,999);
	flightDir = fld;
	yPos = 6 + (random((downScreenBorder-6)/2))*2;
	if(flightDir==NEW_BALL) (((random(0,999))%2)==0)?(flightDir = DIR_LU):(flightDir = DIR_RD);
	if((flightDir==DIR_LD) || (flightDir==DIR_LU)){
		(((randomNumber)%2)==0)?(flightDir = DIR_RU):(flightDir = DIR_RD);
		xPos=leftScreenBorder;	
	}
	else if((flightDir==DIR_RD) || (flightDir==DIR_RU)){
		(((randomNumber)%2)==0)?(flightDir = DIR_LU):(flightDir = DIR_LD);
		xPos=rightScreenBorder;	
	}
}

void Ball::move(){
	switch(flightDir){
		case DIR_LU:
			xPos--; xPos--; yPos--; 
			break;
			
		case DIR_LD:
			xPos--; xPos--; yPos++;
			break;
			
		case DIR_RU:
			xPos++; xPos++; yPos--;
			break;
			
		case DIR_RD:
			xPos++; xPos++; yPos++;
			break;
	}
}

void Ball::fenceCheck(){
	if(yPos==0){
		if(flightDir==DIR_LU) flightDir = DIR_LD;
		else if(flightDir==DIR_RU) flightDir = DIR_RD;
	}
	else if(yPos==124){
		if(flightDir==DIR_LD) flightDir = DIR_LU;
		else if(flightDir==DIR_RD) flightDir = DIR_RU;
	}
}

bool Ball::goalCheck(){
	if((xPos==leftScreenBorder)&&((flightDir==DIR_LD)||(flightDir==DIR_LU))) return true;
	else if ((xPos==rightScreenBorder)&&((flightDir==DIR_RU)||(flightDir==DIR_RD))) return true;
	else return false;
	
}

void Ball::racketHitCheck(const int &left_xp, int &left_yp, const int &right_xp, int &right_yp, 
                          const int &ball_width, const int &height, const int &width){
	if((xPos==(left_xp + width)) && (yPos>=(left_yp-ball_width)) && (yPos<=(left_yp+height))){
		if(flightDir==DIR_LU) flightDir = DIR_RU;
		else if(flightDir==DIR_LD) flightDir = DIR_RD;
	}	
	else if(xPos==(right_xp-ball_width) && (yPos>=(right_yp-ball_width)) && (yPos<=(right_yp+height))){
		if(flightDir==DIR_RU) flightDir = DIR_LU;
		else if(flightDir==DIR_RD) flightDir = DIR_LD;
	}
}
	



