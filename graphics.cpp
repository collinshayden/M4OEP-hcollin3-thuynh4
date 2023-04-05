#include "graphics.h"
#include "Button.h"
#include <iostream>
#include <time.h>
#include <vector>
#include <random>

using namespace std;

GLdouble width, height;
int wd;
vector<Button> board;
Quad outline({1, 0, 0}, {0, 0}, 0, 0);
enum screens {
    start, game, finish
};
screens current_screen;
int num_clicks = 0;

void init() {
    width = 750;
    height = 750;
    srand(time(0));
    current_screen = start;
    for (int i = 1; i < 6; i++) {
        for (int j = 1; j < 6; j++) {
            Button button = Button({1, 1, 0}, {125 * j, 125 * i}, 75, 75, "");
            if (std::rand() % 2 == 0) {
                button.flipOnOff();
            }
            board.push_back(button);
        }
    }
//    board.at(0).flipOnOff();
//    board.at(1).flipOnOff();
//    board.at(5).flipOnOff();
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);

    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);

    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (current_screen == start) {
        string label = "Welcome to Lights Out!";
        glColor3f(0.5, 0.5, 0.5);
        glRasterPos2i(width / 2 - (5 * label.length()), (height / 2) - 40);
        for (const char &letter: label) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }

        label = "Clicking on a cell toggles that cell and each of its immediate neighbors. ";
        glRasterPos2i(width / 2 - (5 * label.length()) + 20, (height / 2) + 10);
        for (const char &letter: label) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }

        label = "The goal is to turn out all the lights,";
        glRasterPos2i((width / 2) - (4 * label.length()), (height / 2) + 40);
        for (const char &letter: label) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
        label = "ideally with the minimum number of clicks.";
        glRasterPos2i((width / 2) - (4 * label.length()) - 30, (height / 2) + 70);
        for (const char &letter: label) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
        label = "Press 's' to start.";
        glRasterPos2i((width / 2) - (4 * label.length()), (height / 2) + 100);
        for (const char &letter: label) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
    } else if (current_screen == game) {
        outline.draw();
        for (const Quad &square: board) {
            square.draw();
        }
        string label = to_string(num_clicks) + " clicks";
        glRasterPos2i(width - 100, (height) - 30);
        for (const char &letter: label) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
    } else if (current_screen == finish) {
        string label = "You Win!";
        glColor3f(1, 0, 1);
        glRasterPos2i(width / 2 - (5 * label.length()), height / 2);
        for (const char &letter: label) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
        label = "It took you " + to_string(num_clicks) + " clicks to finish";
        glRasterPos2i(width / 2 - (4 * label.length()), (height / 2) + 30);
        for (const char &letter: label) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
    }

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    if (key == 's') {
        if (current_screen == start) current_screen = game;

    }
    glutPostRedisplay();
}

void cursor(int x, int y) {
    outline.resize(0, 0);
    for (Button &square: board) {
        if (square.isOverlapping(x, y)) {
            //make it slightly bigger than square
            outline.resize(square.getWidth() + 10, square.getHeight() + 10);
            //move it to origin
            outline.move(-outline.getCenterX(), -outline.getCenterY());
            //move it to be centered on square
            outline.move(square.getCenterX(), square.getCenterY());
        }
    }
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    int total_off = 0;
    for (int index = 0; index < board.size(); index++) {
        Button square = board.at(index);
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && square.isOverlapping(x, y)) {
            vector<int> adj_indices = {index, index - 5, index + 5};
            num_clicks += 1;
            for (int adj: adj_indices) {
                if (adj >= 0 && adj < board.size()) {
                    board.at(adj).flipOnOff();
                }
            }
            //making sure it doesn't wrap around rows
            if (index % 5 != 0) board.at(index - 1).flipOnOff();
            if ((index - 4) % 5 != 0) board.at(index + 1).flipOnOff();
        }
        if (!square.state) total_off += 1;
    }
    if (total_off == board.size()) current_screen = finish;
    glutPostRedisplay();
}

void timer(int dummy) {

    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char **argv) {

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int) width, (int) height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */

    wd = glutCreateWindow("Lights Out!" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // handles timer
    glutTimerFunc(0, timer, 0);

    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
