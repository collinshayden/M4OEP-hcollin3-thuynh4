#include "Button.h"
#include "graphics.h"
using namespace std;

Button::Button(color fill, point center, unsigned int width, unsigned int height, std::string label) : Quad(fill, center, width, height) {
    this->label = label;
    originalFill = fill;
    hoverFill = {fill.red + 0.5, fill.green + 0.5, fill.blue + 0.5};
    pressFill = { 0.5, 0.5, 0.5};
}

void Button::draw() const {
    Quad::draw();
}

/* Returns true if the coordinate is inside the box */
bool Button::isOverlapping(int x, int y) const {
    return (getLeftX() < x && getRightX() > x && getTopY() < y && getBottomY() > y);
}

/* Change color of the box when the user is hovering over it */
void Button::hover() {
//    setColor(hoverFill);
    draw();
    glutPostRedisplay();
}

/* Change color of the box when the user is clicking on it */
void Button::pressDown() {
    setColor(pressFill);
}

/* Change the color back when the user is not clicking/hovering */
void Button::release() {
//    setColor(originalFill);
}

void Button::flipOnOff() {
    state = !state;
    state ? setColor(originalFill) : setColor(pressFill);
}

