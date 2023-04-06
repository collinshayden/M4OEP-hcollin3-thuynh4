#include "Button.h"
#include <GLUT/glut.h>

using namespace std;

Button::Button(color fill, point center, unsigned int width, unsigned int height, std::string label) : Quad(fill, center, width, height) {
    this->label = label;
    originalFill = fill;
    hoverFill = {1,0,0};
    pressFill = { 0.5, 0.5, 0.5};
}

void Button::draw() const {
    Quad::draw();
    glColor3f(0, 0, 0);
    glRasterPos2i(getCenterX(), getCenterY());
    for (const char &letter: label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}

/* Returns true if the coordinate is inside the box */
bool Button::isOverlapping(int x, int y) const {
    return (getLeftX() < x && getRightX() > x && getTopY() < y && getBottomY() > y);
}

/* Change color of the box when the user is hovering over it */
void Button::hover() {
    setColor(hoverFill);
    draw();
    glutPostRedisplay();
}

/* Change color of the box when the user is clicking on it */
void Button::pressDown() {
    setColor(pressFill);
    draw();
    glutPostRedisplay();
}

/* Change the color back when the user is not clicking/hovering */
void Button::release() {
    setColor(originalFill);
}

