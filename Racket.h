#ifndef RACKET_H
#define RACKET_H

#include<TFT.h>
#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif
#include<Ball.h>

class Racket{
	public:
		Racket();
		Racket(int, int);
		void setXPos(int);
		int getXPos();
		int getYPos();
		void move();
		
	private:
		int xPos;
		int yPos;
		int potiPin;
		const int racketHeight = 12;
		const int topScreenBorder = 0;
		const int downScreenBorder = 127;
		const int minPotiVal = 160;
		const int maxPotiVal = 700;
};

#endif

