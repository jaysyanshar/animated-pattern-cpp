/**
	Animated Pattern by Muhammad Jaysy Ansharulloh
	1 December 2019 Version
	Using BGIGRAPH library by Muhammad Jaysy Ansharulloh
*/

#include <iostream>
#include "bgigraph.h"

using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

// Draw Star Object
void drawStar(Point mid, int rad, float angle, colors color) {
	Quad rect = Quad(Point(mid.getX()-rad, mid.getY()-rad), Point(mid.getX()+rad, mid.getY()-rad), Point(mid.getX()+rad, mid.getY()+rad), Point(mid.getX()-rad, mid.getY()+rad), color);
	rect.rotateFrom(mid, angle);
	
	Quad rhomb = rect;
	rhomb.rotateFrom(mid, 45);
	
	rect.drawDDA();
	rhomb.drawDDA();
}

// Draw Square Object
void drawSquare(Point mid, int rad, float angle, colors color) {
	Quad rect = Quad(Point(mid.getX()-rad, mid.getY()-rad), Point(mid.getX()+rad, mid.getY()-rad), Point(mid.getX()+rad, mid.getY()+rad), Point(mid.getX()-rad, mid.getY()+rad), color);
	rect.rotateFrom(mid, angle);
	rect.drawDDA();
}

// Get Random Color
colors randColor() {
	return static_cast<colors>(rand() % 16);
}

// Start BGI Window
void bgiBegin() {
	unsigned int screenWidth = 500;
	unsigned int screenHeight = 500;
	initwindow(screenWidth, screenHeight);
}

// BGI Program
void bgiLoop() {
	// Window settings
	char esc = 0;
	int page = 0;
	setbkcolor(BLACK);
	
	// Transition settings
	float angle = 0;
	bool clockwise = true;
	bool normalDirection = true;
	int thickness = NORM_WIDTH;
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
	colors midStarColor = LIGHTGREEN;
	
	// Side Star Objects
	int sideRadInit = midRadInit / 2;
	int sideRad = sideRadInit;
	int sideRadDec = sideRadInit / totalPileOfStars;
	float sideSize = 0;
	colors sideStarColor = LIGHTRED;
	
	// Outside Square Object
	int outSquareRad;
	midX < midY ? outSquareRad = midX - midX / 3 : outSquareRad = midY - midY / 3;
	colors outSquareColor = YELLOW;
	
	// Instruction
	cout << "====================================================" << endl;
	cout << "== Animated Pattern by Muhammad Jaysy Ansharulloh ==" << endl;
	cout << "==                             Version 2019-12-01 ==" << endl;
	cout << "====================================================" << endl;
	cout << "   Instructions:" << endl;
	cout << "   > KEY_UP\t: Speed Up" << endl;
	cout << "   > KEY_DOWN\t: Slow Down" << endl;
	cout << "   > KEY_LEFT\t: Simplify Stars" << endl;
	cout << "   > KEY_RIGHT\t: Complicate Stars" << endl;
	cout << "   > KEY_TAB\t: Change Direction of Rotation" << endl;
	cout << "   > KEY_RETURN\t: Re-Randomize Color" << endl;
	cout << "   > KEY_ESCAPE\t: Exit Program" << endl;
	cout << "====================================================" << endl;
	
	while(esc != VK_ESCAPE) {
		while(midRad > 0) {
			// Outside Square Object
			drawSquare(Point(midX, midY), outSquareRad, angle, outSquareColor);
			drawSquare(Point(midX, midY), outSquareRad, -angle, outSquareColor);
			
			if(clockwise) {
				for(int thick = 0; thick < thickness; thick++) {
					// Mid Star Object
					drawStar(Point(midX, midY), (midRad-thick) * midSize, angle, midStarColor);
					
					// Side Star Objects
					drawStar(Point(midX-midX/2, midY-midY/2), (sideRad-thick) * sideSize, angle, sideStarColor);
					drawStar(Point(midX+midX/2, midY-midY/2), (sideRad-thick) * sideSize, -angle, sideStarColor);
					drawStar(Point(midX-midX/2, midY+midY/2), (sideRad-thick) * sideSize, angle, sideStarColor);
					drawStar(Point(midX+midX/2, midY+midY/2), (sideRad-thick) * sideSize, -angle, sideStarColor);
				}
			}
			else {
				for(int thick = 0; thick < thickness; thick++) {
					// Mid Star Object
					drawStar(Point(midX, midY), (midRad-thick) * midSize, -angle, midStarColor);
					
					// Side Star Objects
					drawStar(Point(midX-midX/2, midY-midY/2), (sideRad-thick) * sideSize, -angle, sideStarColor);
					drawStar(Point(midX+midX/2, midY-midY/2), (sideRad-thick) * sideSize, angle, sideStarColor);
					drawStar(Point(midX-midX/2, midY+midY/2), (sideRad-thick) * sideSize, -angle, sideStarColor);
					drawStar(Point(midX+midX/2, midY+midY/2), (sideRad-thick) * sideSize, angle, sideStarColor);
				}
			}
			midRad -= midRadDec;
			sideRad -= sideRadDec;
			clockwise = !clockwise; // TODO masih ada bug glitch ketika total piles 1, 3, 7, 10
			
			// Scaling
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
		
		// Rotate
		normalDirection ? angle++ : angle--;
		if(angle == 360) angle = 0;
		if(angle == -1) angle = 359;
		
		if(kbhit()) {
			switch(getch()) {
				case VK_ESCAPE: {
					cout << "> Exiting Program..." << endl;
					esc = VK_ESCAPE;
					break;
				}
				case KEY_UP: {
					if(delaymsec > 0) delaymsec -= delayinc;
					cout << "> Delay\t: " << delaymsec << "ms" << endl;
					break;
				}
				case KEY_DOWN: {
					if(delaymsec < maxdelay) delaymsec += delayinc;
					cout << "> Delay\t: " << delaymsec << "ms" << endl;
					break;
				}
				case KEY_LEFT: {
					if(totalPileOfStars > 1) totalPileOfStars--;
					midRadDec = midRadInit / totalPileOfStars;
					sideRadDec = sideRadInit / totalPileOfStars;
					cout << "> Star Piles\t: " << totalPileOfStars << endl;
					break;
				}
				case KEY_RIGHT: {
					if(totalPileOfStars < maxPileOfStars) totalPileOfStars++;
					midRadDec = midRadInit / totalPileOfStars;
					sideRadDec = sideRadInit / totalPileOfStars;
					cout << "> Star Piles\t: " << totalPileOfStars << endl;
					break;
				}
				case VK_SPACE: {
					bool pause = true;
					cout << "> Program Paused." << endl;
					while(pause) {
						if(kbhit()) {
							if(getch() == VK_SPACE) pause = false;
						}
					}
					cout << "> Program Resumed." << endl;
					break;
				}
				case VK_TAB: {
					cout << "> Changing Direction..." << endl;
					normalDirection = !normalDirection;
					break;
				}
				case VK_RETURN: {
					cout << "> Re-Randomizing Color..." << endl;
					setbkcolor(randColor());
					midStarColor = randColor();
					sideStarColor = randColor();
					outSquareColor = randColor();
					break;
				}
			}
		}
		
		// Responsive
		if(getmaxx() != midX * 2 || getmaxy() != midY * 2) {
			// Object settings
			midX = round(getmaxx() / 2);
			midY = round(getmaxy() / 2);
			
			// Mid Star Object
			midX < midY ? midRadInit = midX - 75 : midRadInit = midY - 75;
			midRad = midRadInit;
			midRadDec = midRadInit / totalPileOfStars;
			
			// Side Star Objects
			sideRadInit = midRadInit / 2;
			sideRad = sideRadInit;
			sideRadDec = sideRadInit / totalPileOfStars;
			
			// Outside Square Object
			midX < midY ? outSquareRad = midX - midX / 3 : outSquareRad = midY - midY / 3;
		}
		
		// Transition
		delay(delaymsec);
		setactivepage(page);
		setvisualpage(1-page);
		page = 1 - page;
		cleardevice();
	}
	esc = 0;
}

// Exit BGI Window
void bgiEnd() {
	cleardevice();
	closegraph();
}

// Main Program
int main(int argc, char** argv) {
	bgiBegin();
	bgiLoop();
	bgiEnd();
	return 0;
}
