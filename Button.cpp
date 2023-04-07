#include "Button.h"
#include <GLUT/glut.h>

using namespace std;

Button::Button(color fill, point center, unsigned int width, unsigned int height, int index) : Quad(fill, center, width, height) {
    this->index = index;
    this->originalFill = fill;
    hoverFill = {1,0,0};
    pressFill = { 0, 1, 0};
}

void Button::draw() const {
    Quad::draw();
    string label = to_string(index);
    glColor3f(0, 0, 0);
    glRasterPos2i(getCenterX()-(4*label.size()), getCenterY());
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
}

/* Change color of the box when the user is clicking on it */
void Button::pressDown() {
    setColor(pressFill);
}

/* Change the color back when the user is not clicking/hovering */
void Button::release() {
    setColor(originalFill);
}


void Button::setOriginalFill(color fill) {
    setColor(fill);
    originalFill = fill;
}

void Button::setIndex(int i) {
    index = i;
}

int Button::getIndex() {
    return index;
}

