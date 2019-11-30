/**
	Animated Pattern by Muhammad Jaysy Ansharulloh
	25 November 2019 Version
	Using BGIGRAPH library by Muhammad Jaysy Ansharulloh
*/

#include <iostream>
#include "bgigraph.h"

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void drawStar(Point mid, int rad, float angle, colors color) {
	Quad rect = Quad(Point(mid.getX()-rad, mid.getY()-rad), Point(mid.getX()+rad, mid.getY()-rad), Point(mid.getX()+rad, mid.getY()+rad), Point(mid.getX()-rad, mid.getY()+rad), color);
	rect.rotateFrom(mid, angle);
	
	Quad rhomb = rect;
	rhomb.rotateFrom(mid, 45);
	
	rect.drawDDA();
	rhomb.drawDDA();
}

void drawSquare(Point mid, int rad, float angle, colors color) {
	Quad rect = Quad(Point(mid.getX()-rad, mid.getY()-rad), Point(mid.getX()+rad, mid.getY()-rad), Point(mid.getX()+rad, mid.getY()+rad), Point(mid.getX()-rad, mid.getY()+rad), color);
	rect.rotateFrom(mid, angle);
	rect.drawDDA();
}

void bgiBegin() {
	unsigned int screenWidth = 500;
	unsigned int screenHeight = 500;
	initwindow(screenWidth, screenHeight);
}

void bgiLoop() {
	// Window settings
	char esc = 0;
	int page = 0;
	
	// Transition settings
	float angle = 0;
	bool clockwise = false;
	int thickness = 1;
	float scaling = 0.005;
	bool scaleDown = true;
	unsigned int delaymsec = 0;
	unsigned int maxdelay = 200;
	unsigned int delayinc = maxdelay / 10;
	
	// Object settings
	int midX = round(getmaxx() / 2);
	int midY = round(getmaxy() / 2);
	int totalPileOfStars = 4;
	int maxPileOfStars = 10;
	
	// Mid Star Object
	int midRadInit;
	midX < midY ? midRadInit = midX - 75 : midRadInit = midY - 75;
	int midRad = midRadInit;
	int midRadDec = midRadInit / totalPileOfStars;
	float midSize = 1;
	
	// Side Star Objects
	int sideRadInit = midRadInit / 2;
	int sideRad = sideRadInit;
	int sideRadDec = sideRadInit / totalPileOfStars;
	float sideSize = 0;
	
	// Outside Square Object
	int outSquareRad;
	midX < midY ? outSquareRad = midX - midX / 3 : outSquareRad = midY - midY / 3;
	
	// Instruction
	cout << "====================================================" << endl;
	cout << "== Animated Pattern by Muhammad Jaysy Ansharulloh ==" << endl;
	cout << "==                             Version 2019-11-27 ==" << endl;
	cout << "====================================================" << endl;
	cout << "   Instructions:" << endl;
	cout << "   > KEY_UP\t: Speed up" << endl;
	cout << "   > KEY_DOWN\t: Slow down" << endl;
	cout << "   > KEY_LEFT\t: Simplify Stars" << endl;
	cout << "   > KEY_RIGHT\t: Complicate Stars" << endl;
	cout << "   > KEY_ESC\t: Exit program" << endl;
	cout << "====================================================" << endl;
	
	while(esc != KEY_ESC) {
		while(midRad > 0) {
			clockwise = !clockwise;
			
			// Outside Square Object
			drawSquare(Point(midX, midY), outSquareRad, angle, WHITE);
			drawSquare(Point(midX, midY), outSquareRad, -angle, WHITE);
			
			if(clockwise) { // TODO masih ada bug ketika pile 1, 3, 7, 10
				for(int thick = 0; thick < thickness; thick++) {
					// Mid Star Object
					drawStar(Point(midX, midY), (midRad-thick) * midSize, angle, static_cast<colors>(rand() % 15 + 1));
					
					// Side Star Objects
					drawStar(Point(midX-midX/2, midY-midY/2), (sideRad-thick) * sideSize, angle, static_cast<colors>(rand() % 15 + 1));
					drawStar(Point(midX+midX/2, midY-midY/2), (sideRad-thick) * sideSize, -angle, static_cast<colors>(rand() % 15 + 1));
					drawStar(Point(midX-midX/2, midY+midY/2), (sideRad-thick) * sideSize, angle, static_cast<colors>(rand() % 15 + 1));
					drawStar(Point(midX+midX/2, midY+midY/2), (sideRad-thick) * sideSize, -angle, static_cast<colors>(rand() % 15 + 1));
				}
			}
			else {
				for(int thick = 0; thick < thickness; thick++) {
					// Mid Star Object
					drawStar(Point(midX, midY), (midRad-thick) * midSize, -angle, static_cast<colors>(rand() % 15 + 1));
					
					// Side Star Objects
					drawStar(Point(midX-midX/2, midY-midY/2), (sideRad-thick) * sideSize, -angle, static_cast<colors>(rand() % 15 + 1));
					drawStar(Point(midX+midX/2, midY-midY/2), (sideRad-thick) * sideSize, angle, static_cast<colors>(rand() % 15 + 1));
					drawStar(Point(midX-midX/2, midY+midY/2), (sideRad-thick) * sideSize, -angle, static_cast<colors>(rand() % 15 + 1));
					drawStar(Point(midX+midX/2, midY+midY/2), (sideRad-thick) * sideSize, angle, static_cast<colors>(rand() % 15 + 1));
				}
			}
			midRad -= midRadDec;
			sideRad -= sideRadDec;
			
			if(midSize >= 0 && midSize <= 1) {
				if(scaleDown) {
					midSize -= scaling;
					sideSize += scaling;
				}
				else {
					midSize += scaling;
					sideSize -= scaling;
				}
			} else {
				scaleDown = !scaleDown;
				if(scaleDown) {
					midSize = 1;
					sideSize = 0;
				}
				else {
					midSize = 0;
					sideSize = 1;
				}
			}
		}
		midRad = midRadInit;
		sideRad = sideRadInit;
		angle < 360 ? angle++ : angle = 0;
		
		if(kbhit()) {
			cout << ">";
			switch(getch()) {
				case KEY_ESC: {
					esc = KEY_ESC;
					cout << "Exiting Program..." << endl;
					break;
				}
				case KEY_UP: {
					if(delaymsec > 0) delaymsec -= delayinc;
					cout << "Delay\t: " << delaymsec << "ms" << endl;
					break;
				}
				case KEY_DOWN: {
					if(delaymsec < maxdelay) delaymsec += delayinc;
					cout << "Delay\t: " << delaymsec << "ms" << endl;
					break;
				}
				case KEY_LEFT: {
					if(totalPileOfStars > 1) totalPileOfStars--;
					midRadDec = midRadInit / totalPileOfStars;
					sideRadDec = sideRadInit / totalPileOfStars;
					cout << "Star Piles\t: " << totalPileOfStars << endl;
					break;
				}
				case KEY_RIGHT: {
					if(totalPileOfStars < maxPileOfStars) totalPileOfStars++;
					midRadDec = midRadInit / totalPileOfStars;
					sideRadDec = sideRadInit / totalPileOfStars;
					cout << "Star Piles\t: " << totalPileOfStars << endl;
					break;
				}
				case KEY_SPACE: {
					bool pause = true;
					cout << "Program Paused." << endl;
					while(pause) {
						if(kbhit()) {
							if(getch() == KEY_SPACE) pause = false;
						}
					}
					cout << ">Program Resumed." << endl;
					break;
				}
			}
		}
		
		delay(delaymsec);
		setactivepage(page);
		setvisualpage(1-page);
		page = 1 - page;
		cleardevice();
	}
	esc = 0;
}

void bgiEnd() {
	cleardevice();
	closegraph();
}

int main(int argc, char** argv) {
	bgiBegin();
	bgiLoop();
	bgiEnd();
	return 0;
}
