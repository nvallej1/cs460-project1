#include <GL/glut.h>
#include <cmath>  // abs()
#include <assert.h>
#include <iterator>
#include <iostream>
#include <vector>

using namespace std;

vector<pair<float, float>> controlPoints;
pair<float,float> dummyVertex(-1,-1);
pair<float,float> previousControlPoint (dummyVertex);
bool drawDynamicLine = false;
bool pressedLeftButton = false;

void BresenhamLineAlgorithm(float x1, float y1, float x2, float y2, float xoffset);
void DrawLineOfSymmetry();
void DrawWAKE();
void glLine(float x0, float y0, float x1, float y1, float xoffset);
void LButtonDown();
void RButtonDown();
void MouseMove();
void MouseFunc(int button, int state, int x, int y);

void glLine(float x0, float y0, float x1, float y1, float xoffset) {
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

	glLine(0, 0, 5, -10, rhsStart);
	glLine(5, -10, 10, -5, rhsStart);
	glLine(10, -5, 15, -10, rhsStart);
	glLine(15, -10, 20, 0, rhsStart);

	xOffset = 25;

	// Letter: 'A' xRange = (25, 35) yRange = (0,-10)
	BresenhamLineAlgorithm(xOffset, -10, xOffset + 5, 0, lhsStart);
	BresenhamLineAlgorithm(xOffset + 5, 0, xOffset + 10, -10, lhsStart);
	BresenhamLineAlgorithm(xOffset + 2.5, -5, xOffset + 7.5, -5, lhsStart);

	glLine(xOffset, -10, xOffset + 5, 0, rhsStart);
	glLine(xOffset + 5, 0, xOffset + 10, -10, rhsStart);
	glLine(xOffset + 2.5, -5, xOffset + 7.5, -5, rhsStart);


	xOffset += 15;

	// Letter: 'K' xRange = (40, 45) yRange = (0,-10)
	BresenhamLineAlgorithm(xOffset, 0, xOffset, -10, lhsStart);
	BresenhamLineAlgorithm(xOffset, -5, xOffset + 5, 0, lhsStart);
	BresenhamLineAlgorithm(xOffset, -5, xOffset + 5, -10, lhsStart);

	glLine(xOffset, 0, xOffset, -10, rhsStart);
	glLine(xOffset, -5, xOffset + 5, 0, rhsStart);
	glLine(xOffset, -5, xOffset + 5, -10, rhsStart);

	xOffset += 10;

	// Letter: "E" xRange = (50, 55) yRange = (0,-10)
	BresenhamLineAlgorithm(xOffset, 0, xOffset, -10, lhsStart);
	BresenhamLineAlgorithm(xOffset, 0, xOffset + 5, 0, lhsStart);
	BresenhamLineAlgorithm(xOffset, -5, xOffset + 2, -5, lhsStart);
	BresenhamLineAlgorithm(xOffset, -10, xOffset + 5, -10, lhsStart);

	glLine(xOffset, 0, xOffset, -10, rhsStart);
	glLine(xOffset, 0, xOffset + 5, 0, rhsStart);
	glLine(xOffset, -5, xOffset + 2, -5, rhsStart);
	glLine(xOffset, -10, xOffset + 5, -10, rhsStart);
}

void mouseFunc(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			previousControlPoint = make_pair<float,float>(x,y);
			controlPoints.push_back(previousControlPoint);	// Add a vertex to control points list
			drawDynamicLine = true;
			pressedLeftButton = true;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON) {
		if (state == GLUT_DOWN) {
			// Check if we have pressed left mouse button down at least once
			if (pressedLeftButton) {
				controlPoints.push_back(make_pair<float,float>(x,y)); // Add final vertex for this line-segment to vector
				controlPoints.push_back(dummyVertex);	// Add dummyVertex (-1,-1) to indicate end of line segment in our vector

				// Reset some global variable values
				previousControlPoint = dummyVertex;
				drawDynamicLine = false;
				pressedLeftButton = false;
			}
		}
	}
}

void passiveMotionFunc(int x, int y) {
	if (drawDynamicLine) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    	glClear(GL_COLOR_BUFFER_BIT);

		DrawWAKE();	// Redraw WAKE on lhs using BresenhamLineAlgorithm and on rhs using GL_LINES

		glPushMatrix();
		glLoadIdentity();

		glMatrixMode(GL_PROJECTION);
		gluOrtho2D(0.0, glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), 0.0);	// set coordinate system to match window size

		// For every 2 vertexes/elements in controlPoints, draw a line
		for (unsigned int i = 0; i < controlPoints.size()-1; i++) {
			// If the current vertex or the next vertex in controlPoints has an x-coordinate = -1, skip it
			// In other words, this if-statement indicates the end of a line in our 'controlPoints' vector
			if (controlPoints.at(i).first == -1 || controlPoints.at(i+1).first == -1) {
				continue;
			}
			glBegin(GL_LINES);
				glVertex2f(controlPoints.at(i).first, controlPoints.at(i).second);
				glVertex2f(controlPoints.at(i+1).first, controlPoints.at(i+1).second);
			glEnd();
		}
		// Now draw the dynamic line with mouse cursor position as the end vertex
		glBegin(GL_LINES);
			glVertex2f(previousControlPoint.first, previousControlPoint.second);
			glVertex2f(x, y);
		glEnd();

		glPopMatrix();
		glLoadIdentity();

		glFlush();
	}
}

void LButtonDown() {
	;
}

void RButtonDown() {
	;
}

void display() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


	DrawWAKE();	// Draw WAKE on lhs using BresenhamLineAlgorithm and on rhs using GL_LINES
	glutMouseFunc(mouseFunc);
	glutPassiveMotionFunc(passiveMotionFunc);

	glFlush();	// Render now
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutCreateWindow("Hello CS460/560");
    glutInitWindowSize(500, 500);
	glutReshapeWindow(500, 500);
    glutInitWindowPosition(200,200);
    glutDisplayFunc(display);
	glutMainLoop();	// Enter event processing loop
	return 0;
}
