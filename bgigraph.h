/**
	BGIGRAPH by Muhammad Jaysy Ansharulloh
	November 2019 Version
	Using Object Oriented Programming Concept
*/

#ifndef BGIGRAPH_H
#define BGIGRAPH_H

#include <cstdlib>
#include <cmath>
#include <graphics.h>

#define round(a) ((int) (a + 0.5))

#define KEY_ESC 27
#define KEY_SPACE 32

/****************************/
/*			POINT			*/
/****************************/

class Point {
	private:
		int x;
		int y;
		colors color;
		
	public:
		Point();
		Point(int x, int y);
		Point(int x, int y, colors color);
		
		void setX(int x) { this->x = x; }
		void setY(int y) { this->y = y; }
		void setColor(colors color) { this->color = color; }
		
		int getX() { return x; }
		int getY() { return y; }
		colors getColor() { return color; }
		
		// Translate point from current position
		void translate(int xInc, int yInc);
};

/****************************/
/*			LINE			*/
/****************************/

class Line {
	private:
		Point a;
		Point b;
		colors color;
		
	public:
		Line(Point a, Point b, colors color);
		
		void setA(Point a) { this->a = a; }
		void setB(Point b) { this->b = b; }
		void setColor(colors color) { this->color = color; }
		
		Point getA() { return a; }
		Point getB() { return b; }
		colors getColor() { return color; }
		
		// Draw using DDA Algorithm
		void drawDDA();
		
		// Draw using Bresenham Algorithm
		void drawBresenham();
		
		// Rotate from point A
		void rotateA(float angle);
		
		// Rotate from point B
		void rotateB(float angle);
};

/****************************/
/*			QUAD			*/
/****************************/

class Quad {
	private:
		Point a;
		Point b;
		Point c;
		Point d;
		colors color;
		
	public:
		Quad(Point a, Point b, Point c, Point d, colors color);
		
		void setA(Point a) { this->a = a; }
		void setB(Point b) { this->b = b; }
		void setC(Point c) { this->c = c; }
		void setD(Point d) { this->d = d; }
		void setColor(colors color) { this->color = color; }
		
		Point getA() { return a; }
		Point getB() { return b; }
		Point getC() { return c; }
		Point getD() { return d; }
		colors getColor() { return color; }
		
		// Draw using DDA Algorithm
		void drawDDA();
		
		// Draw using Bresenham Algorithm
		void drawBresenham();
		
		// Rotate from mid
		void rotateFrom(Point weightPoint, float angle);
};

/****************************/
/*			CIRCLE			*/
/****************************/

class Circle {
	private:
		Point mid;
		int rad;
		colors color;
		
		// Plot point with putpixel()
		void plotPoint(int x, int y, colors color);
		
	public:
		Circle(Point mid, int rad, colors color);
		
		void setMid(Point mid) { this->mid = mid; }
		void setRad(int rad) { this->rad = rad; }
		void setColor(colors color) { this->color = color; }
				
		Point getMid() { return mid; }
		int getRad() { return rad; }
		colors getColor() { return color; }
		
		// Draw using Mid Point
		void drawMidPoint();
};

/****************************/
/*			ELLIPSE			*/
/****************************/

class EllipseShape {
	private:
		Point mid;
		int radX;
		int radY;
		colors color;
		
		// Plot point with putpixel()
		void plotPoint(int x, int y, colors color);
		
	public:
		EllipseShape(Point mid, int radX, int radY, colors color);
		
		void setMid(Point mid) { this->mid = mid; }
		void setRadX(int radX) { this->radX = radX; }
		void setRadY(int radY) { this->radY = radY; }
		void setColor(colors color) { this->color = color; }
		
		Point getMid() { return mid; }
		int getRadX() { return radX; }
		int getRadY() { return radY; }
		colors getColor() { return color; }
		
		// Draw using Mid Point
		void drawMidPoint();
};

#endif
