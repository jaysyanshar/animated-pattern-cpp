/**
	BGIGRAPH by Muhammad Jaysy Ansharulloh
	November 2019 Version
	Using Object Oriented Programming Concept
*/

#include "bgigraph.h"

/****************************/
/*			POINT			*/
/****************************/

// Constructor
Point::Point() {
	setX(0);
	setY(0);
	setColor(WHITE);
}

Point::Point(int x, int y) {
	setX(x);
	setY(y);
	setColor(WHITE);
}

Point::Point(int x, int y, colors color) {
	setX(x);
	setY(y);
	setColor(color);
}

// Translate
void Point::translate(int xInc, int yInc) {
	setX(x + xInc);
	setY(y + yInc);
}

/****************************/
/*			LINE			*/
/****************************/

// Constructor
Line::Line(Point a, Point b, colors color) {
	setA(a);
	setB(b);
	setColor(color);
}

// Draw using DDA Algorithm
void Line::drawDDA() {
	int dx = b.getX() - a.getX();
	int dy = b.getY() - a.getY();
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	float xInc = dx / (float) steps;
	float yInc = dy / (float) steps;
	float x = a.getX();
	float y = a.getY();
	
	for(int i = 0; i <= steps; i++) {
		putpixel(x, y, color);
		x += xInc;
		y += yInc;
	}
}

// Draw using Bresenham Algorithm
void Line::drawBresenham() {
	int dx = abs(a.getX() - b.getX());
	int dy = abs(a.getY() - b.getY());
	int p = 2 * dy - dx;
	int twoDy = 2 * dy;
	int twoDyDx = 2 * (dy - dx);
	int x, y, xEnd;
	
	if(a.getX() > b.getX()) {
		x = b.getX();
		y = b.getY();
		xEnd = a.getX();
	}
	else {
		x = a.getX();
		y = a.getY();
		xEnd = b.getX();
	}
	
	putpixel(x, y, color);
	while(x < xEnd) {
		x++;
		if(p < 0) {
			p += twoDy;
		}
		else {
			y++;
			p += twoDyDx;
		}
		
		putpixel(x, y, color);
	}
}

// Rotate from Point A
void Line::rotateA(float angle) {
	angle = -angle;
	float rad = angle * 0.01745;
	int xR = (int) (a.getX() + ((b.getX() - a.getX()) * cos(rad) - (b.getY() - a.getY()) * sin(rad)));
	int yR = (int) (a.getY() + ((b.getX() - a.getX()) * sin(rad) + (b.getY() - a.getY()) * cos(rad)));
	b.setX(xR);
	b.setY(yR);
}

// Rotate from Point B
void Line::rotateB(float angle) {
	angle = - angle;
	float rad = angle * 0.01745;
	int xR = (int) (b.getX() + ((a.getX() - b.getX()) * cos(rad) - (a.getY() - b.getY()) * sin(rad)));
	int yR = (int) (b.getY() + ((a.getX() - b.getX()) * sin(rad) + (a.getY() - b.getY()) * cos(rad)));
	a.setX(xR);
	a.setY(yR);
}

/****************************/
/*			QUAD			*/
/****************************/

// Constructor
Quad::Quad(Point a, Point b, Point c, Point d, colors color) {
	setA(a);
	setB(b);
	setC(c);
	setD(d);
	setColor(color);
}

// Draw using DDA Algorithm
void Quad::drawDDA() {
	Line line = Line(a, b, color);
	line.drawDDA();
	
	line.setA(b);
	line.setB(c);
	line.drawDDA();
	
	line.setA(c);
	line.setB(d);
	line.drawDDA();
	
	line.setA(d);
	line.setB(a);
	line.drawDDA();
}

void Quad::drawBresenham() {
	Line line = Line(a, b, color);
	line.drawBresenham();
	
	line.setA(b);
	line.setB(c);
	line.drawBresenham();
	
	line.setA(c);
	line.setB(d);
	line.drawBresenham();
	
	line.setA(d);
	line.setB(a);
	line.drawBresenham();
}

void Quad::rotateFrom(Point weightPoint, float angle) {
	angle = -angle;
	float rad = angle * 0.01745;
	
	// Translate A
	Line line = Line(weightPoint, a, color);
	line.rotateA(angle);
	a = line.getB();
	
	// Translate B
	line = Line(weightPoint, b, color);
	line.rotateA(angle);
	b = line.getB();
	
	// Translate C
	line = Line(weightPoint, c, color);
	line.rotateA(angle);
	c = line.getB();
	
	// Translate D
	line = Line(weightPoint, d, color);
	line.rotateA(angle);
	d = line.getB();
}

/****************************/
/*			CIRCLE			*/
/****************************/

// Constructor
Circle::Circle(Point mid, int rad, colors color) {
	setMid(mid);
	setRad(rad);
	setColor(color);
}

// Plot point with putpixel()
void Circle::plotPoint(int x, int y, colors color) {
	putpixel(mid.getX() + x, mid.getY() + y, color);
    putpixel(mid.getX() + y, mid.getY() + x, color);
    putpixel(mid.getX() - y, mid.getY() + x, color);
    putpixel(mid.getX() - x, mid.getY() + y, color);
    putpixel(mid.getX() - x, mid.getY() - y, color);
    putpixel(mid.getX() - y, mid.getY() - x, color);
    putpixel(mid.getX() + y, mid.getY() - x, color);
    putpixel(mid.getX() + x, mid.getY() - y, color);
}

// Draw using Mid Point Algorithm
void Circle::drawMidPoint() {
	int x = rad;
	int y = 0;
	int err = 0;
	
	while(x >= y) {
		plotPoint(x, y, color);
		if(err <= 0) {
			y++;
			err += 2 * y + 1;
		}
		else {
			x--;
			err -= 2 * x + 1;
		}
	}
}

/****************************/
/*			ELLIPSE			*/
/****************************/

// Constructor
Ellipse::Ellipse(Point mid, int radX, int radY, colors color) {
	setMid(mid);
	setRadX(radX);
	setRadY(radY);
	setColor(color);
}

// Plot point with putpixel()
void Ellipse::plotPoint(int x, int y, colors color) {
	 putpixel(mid.getX() + x, mid.getY() + y, color);
	 putpixel(mid.getX() - x, mid.getY() + y, color);
	 putpixel(mid.getX() + x, mid.getY() - y, color);
	 putpixel(mid.getX() - x, mid.getY() - y, color);
}

// Draw using mid point algorithm
void Ellipse::drawMidPoint() {
	int radXsqr = pow(radX, 2);
	int radYsqr = pow(radY, 2);
	int twoRadXsqr = 2 * radXsqr;
	int x0 = 2 * radYsqr;
	int p;
	int x = 0;
	int y = radY;
	int px = 0;
	int py = twoRadXsqr * y;
	
	plotPoint(x, y, color);
	
	// Region 1
	p = round(radYsqr - (radXsqr * radY) + (0.25 * radXsqr));
	while(px < py) {
		x++;
		px += x0;
		if(p < 0) {
			p += radYsqr + px;
		}
		else {
			y--;
			py -= twoRadXsqr;
			p += radYsqr + px - py;
		}
		plotPoint(x, y, color);
	}
	
	// Region 2
	p = round(radYsqr * (x + 0.5) * (x + 0.5) + radXsqr * (y - 1) * (y - 1) - radXsqr * radYsqr);
	while(y > 0) {
		y--;
		py -= twoRadXsqr;
		if(p > 0) {
			p += radXsqr - py;
		}
		else {
			x++;
			px += x0;
			p += radXsqr - py + px;
		}
		plotPoint(x, y, color);
	}
}
