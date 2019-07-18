#ifndef BALL_H
#define BALL_H

#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

enum BallDir {DIR_LU = 1, DIR_LD, DIR_RU, DIR_RD, NEW_BALL};// Flugrichtung des Balls left up, etc.

class Ball{
	public:
		Ball();
		void setFlightDir(BallDir);
		void setXPos(int);
		void setYPos(int);
		int getXPos();
		int getYPos();
		BallDir getFlightDir();
		void newBall();
		void newBall(BallDir);
		void move();
		void fenceCheck();
		bool goalCheck();
		void racketHitCheck(const int&, int&, const int&, int&, const int&, const int&, const int&);
	private:
		int leftScreenBorder = -2;
		int rightScreenBorder = 158; 
		int topScreenBorder = 0;
		int downScreenBorder = 124;
		int xPos, yPos;
		BallDir flightDir = NEW_BALL;
};

#endif

