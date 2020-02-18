// Compiling: g++ demo.cpp -o a.out -lGL -lglut -lGLU

#include <GL/glut.h>
#include <cmath>  // abs()
#include <assert.h>
#include <iterator>

using namespace std;

void BresenhamLineAlgorithm(float x1, float y1, float x2, float y2, float xoffset);
void MyDrawLine(float xPoints[], float yPoints[]);
void DrawLineOfSymmetry();
void DrawWAKE();

void MyDrawLine(float xPoints[], float yPoints[]) {
	//assert(sizeof(xPoints)/sizeof(*xPoints) == sizeof(yPoints)/sizeof(*yPoints));

	float offset = -1;

	// Assumes that the size of xPoints = size of yPoints
	for (int i = 0; i <= 3; i++) {
		BresenhamLineAlgorithm(xPoints[i], yPoints[i], xPoints[i+1], yPoints[i+1], offset);
	}
}

void GLLine(float x0, float y0, float x1, float y1, float xoffset) {
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex2f((x0 * 0.01) + xoffset, y0 * 0.01);
		glVertex2f((x1 * 0.01) + xoffset, y1 * 0.01);
	glEnd();
}

void BresenhamLineAlgorithm(float x0, float y0, float x1, float y1, float xoffset) {
	//x1 += xoffset;
	//x2 += xoffset;

	float dx = abs(x1 - x0);	// 10
	float signX = (x0 < x1) ? 1 : -1;	// 1
	float dy = -abs(y1 - y0);	// -10
	float signY = (y0 < y1) ? 1 : -1;	// 1
	float error = dx + dy; // 0
	while (true) {
		glBegin(GL_POINTS);
		 		glColor3f(1.0f, 1.0f, 1.0f);
		 		glVertex2f((x0 * 0.01) + xoffset,y0 * 0.01); // (0,0) , (1, 0) , (1,1)
		glEnd();
		if (x0 == x1 && y0 == y1) {
			break;
		}
		float error2 = 2*error; // 0 , -20
		if (error2 >= dy) {
			error += dy;	// -10
			x0 += signX;    // 1
		}
		error2 = 2*error;
		if (error2 <= dx) {
			error += dx;	// -10
			y0 += signY;	// 1
		}
	}
}

void DrawLineOfSymmetry() {
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
		glVertex2f(0, 1);
		glVertex2f(0, -1);
	glEnd();
}

void DrawWAKE() {
	float xOffset = 0;
	float lhsStart = -0.9;
	float rhsStart = 0.35;

	DrawLineOfSymmetry();

	// Letter: 'W' xRange = (0,20) yRange = (0, -10)
	BresenhamLineAlgorithm(0, 0, 5, -10, lhsStart);
	BresenhamLineAlgorithm(5, -10, 10, -5, lhsStart);
	BresenhamLineAlgorithm(10, -5, 15, -10, lhsStart);
	BresenhamLineAlgorithm(15, -10, 20, 0, lhsStart);

	GLLine(0, 0, 5, -10, rhsStart);
	GLLine(5, -10, 10, -5, rhsStart);
	GLLine(10, -5, 15, -10, rhsStart);
	GLLine(15, -10, 20, 0, rhsStart);

	xOffset = 25;

	// Letter: 'A' xRange = (25, 35) yRange = (0,-10)
	BresenhamLineAlgorithm(xOffset, -10, xOffset + 5, 0, lhsStart);
	BresenhamLineAlgorithm(xOffset + 5, 0, xOffset + 10, -10, lhsStart);
	BresenhamLineAlgorithm(xOffset + 2.5, -5, xOffset + 7.5, -5, lhsStart);

	GLLine(xOffset, -10, xOffset + 5, 0, rhsStart);
	GLLine(xOffset + 5, 0, xOffset + 10, -10, rhsStart);
	GLLine(xOffset + 2.5, -5, xOffset + 7.5, -5, rhsStart);


	xOffset += 15;

	// Letter: 'K' xRange = (40, 45) yRange = (0,-10)
	BresenhamLineAlgorithm(xOffset, 0, xOffset, -10, lhsStart);
	BresenhamLineAlgorithm(xOffset, -5, xOffset + 5, 0, lhsStart);
	BresenhamLineAlgorithm(xOffset, -5, xOffset + 5, -10, lhsStart);

	GLLine(xOffset, 0, xOffset, -10, rhsStart);
	GLLine(xOffset, -5, xOffset + 5, 0, rhsStart);
	GLLine(xOffset, -5, xOffset + 5, -10, rhsStart);

	xOffset += 10;

	// Letter: "E" xRange = (50, 55) yRange = (0,-10)
	BresenhamLineAlgorithm(xOffset, 0, xOffset, -10, lhsStart);
	BresenhamLineAlgorithm(xOffset, 0, xOffset + 5, 0, lhsStart);
	BresenhamLineAlgorithm(xOffset, -5, xOffset + 2, -5, lhsStart);
	BresenhamLineAlgorithm(xOffset, -10, xOffset + 5, -10, lhsStart);

	GLLine(xOffset, 0, xOffset, -10, rhsStart);
	GLLine(xOffset, 0, xOffset + 5, 0, rhsStart);
	GLLine(xOffset, -5, xOffset + 2, -5, rhsStart);
	GLLine(xOffset, -10, xOffset + 5, -10, rhsStart);
}

void display() {
    // First - set background color to black
    // Second - Clear color buffer for later usage
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
	DrawWAKE();	// Draw WAKE on lhs using BresenhamLineAlgorithm and on rhs using GL_LINES
	glFlush(); // Render now
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Hello CS460/560");
    glutInitWindowSize(500, 500);
	glutReshapeWindow(200, 200);
    glutInitWindowPosition(200,200);
    glutDisplayFunc(display);
	glutMainLoop();	// Enter event processing loop
	return 0;
}
