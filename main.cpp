//Hayden Collins, OEP
#include "Board.h"
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <string>
#include <iostream>
#include "pieces/pieceClasses.h"
#include <filesystem>
#include <sstream>
//#include "graphics.h"
#include <stdlib.h>
#include <sys/time.h>
#include <GLUT/glut.h>
#include "Button.h"

using namespace std;

//TODO print move disambiguating in printLegalMovesList
//TODO save moves of the game in a list (needed for en passant and 50 move rule)
//TODO add en passant
//TODO add three fold repetition, insufficient material, 50 move rule draws

// square encoding
enum squares {
    a8 = 0,
    b8,
    c8,
    d8,
    e8,
    f8,
    g8,
    h8,
    a7 = 16,
    b7,
    c7,
    d7,
    e7,
    f7,
    g7,
    h7,
    a6 = 32,
    b6,
    c6,
    d6,
    e6,
    f6,
    g6,
    h6,
    a5 = 48,
    b5,
    c5,
    d5,
    e5,
    f5,
    g5,
    h5,
    a4 = 64,
    b4,
    c4,
    d4,
    e4,
    f4,
    g4,
    h4,
    a3 = 80,
    b3,
    c3,
    d3,
    e3,
    f3,
    g3,
    h3,
    a2 = 96,
    b2,
    c2,
    d2,
    e2,
    f2,
    g2,
    h2,
    a1 = 112,
    b1,
    c1,
    d1,
    e1,
    f1,
    g1,
    h1,
    no_sq
};

string getMove(string FEN, int elo);

void passAndPlay(Board &board);

void stockFish(int elo, Board &board, bool side);

void regularPlay();

void tests();

int squareToInt(string square);

void makeCompMove(bool side, int elo, Board &board);

//int main () {
//    cout << "Welcome to Chess" << endl;
//    Board board(true);
////    regularPlay();
//}

//this method gets the move for the opponent from the stockfish python library
string getMove(string FEN, int elo) {
    //change based on computer type
    const string python = "python3";
    string command = python + " ../chess.py" + " " + FEN + " " + to_string(elo);
    //sends a command to the terminal
    system(command.c_str());
    string move;

    //gather move from file now
    ifstream stockMove;
    stockMove.open("../cmake-build-debug/stockfishMove.txt");
    //gets the move from a file written in python
    if (stockMove.is_open()) {
        stockMove >> move;
    }
    stockMove.close();

    return move;
    //pull from file when getting move from stockfish
}

//pass and play game mode method
void passAndPlay(Board &board) {
    vector<int> moves;
    bool side = true;
    //print board
    board.printBoard(true);
    //while loop to keep game running until somebody wins
    while (!board.game_end) {
        if (side) {
            cout << "White to move." << endl;
        } else {
            cout << "Black to move." << endl;
        }
        //gets user move
        moves = board.getUserMove(side, cout, cin);
        //makes the users move
        board.makeUserMove(moves);
        board.printBoard(true);
        board.checkGameEnd();
        side = !side;
    }
}

//side is player's side
void stockFish(int elo, Board &board, bool side) {
    //based on who is what color determines what order moves are made in
    if (!side) {
        makeCompMove(!side, elo, board);
    }

    while (!board.game_end) {
        //prints board
        board.printBoard(side);
        vector<int> moves = board.getUserMove(side, cout, cin);
        //makes the move for the user
        board.makeUserMove(moves);
        //prints board again
        board.printBoard(side);
        //checks if game is over
        board.checkGameEnd();
        if (!board.game_end) {
            //computer moves
            makeCompMove(!side, elo, board);
        }
        //checks if game is over
        board.checkGameEnd();
    }
}

//menu for user input and initial game setup
void regularPlay() {
    string line;
    stringstream ss;
    int elo;
    bool side;
    //sets up board
    Board board(true);
    cout << "Would you like to do pass and play or play a computer? (p/c) or (debug) to enter custom setups: " << endl;
    //gets user input
    getline(cin, line);
    //some input validation to choose what mode the user wants to play
    while (line != "p" && line != "c" && line != "debug") {
        cout << "please enter a valid option (p/c): " << endl;
        cin.clear();
        getline(cin, line);
    }
    if (line == "p") {
        passAndPlay(board);
    } else if (line == "debug") {
        tests();
    } else {
        cin.clear();
        cout << "Jack , elo 400" << endl;
        cout << "Evan, elo 1000" << endl;
        cout << "Hayden, elo 1700" << endl;
        cout << "Huong, elo 1900" << endl;
        //elo selector
        cout << "Who would you like to play against? (j,e,ha,hu) " << endl;
        getline(cin, line);
        while (line != "j" && line != "e" && line != "ha" && line != "hu") {
            cout << "please enter a valid option (j,e,ha,hu): " << endl;
            cin.clear();
            getline(cin, line);
        }
        if (line == "j") {
            elo = 400;
        } else if (line == "e") {
            elo = 1000;
        } else if (line == "ha") {
            elo = 1700;
        } else {
            elo = 2000;
        }
        //run stockfish option
        cin.clear();
        //which side of the board would you like to play
        cout << "Would you like to play as white or black?(w/b) " << endl;
        getline(cin, line);
        while (line != "w" && line != "b") {
            //validation
            cout << "please enter a valid option (w/b): " << endl;
            cin.clear();
            getline(cin, line);
        }
        if (line == "w") {
            side = true;
        } else {
            side = false;
        }
        stockFish(elo, board, side);
    }
}

void tests() {
    string setup;
    vector<string> setups = {"pin", "legality", "checkmate", "promotion", "castles", "stalemate", "disambiguate"};
    cout << "Choose a setup: 'pin', 'legality' ,'checkmate', 'promotion', 'castles', 'stalemate', 'disambiguate'"
         << endl;
    getline(cin, setup);
    while (find(setups.begin(), setups.end(), setup) == setups.end()) {
        cout << setup
             << " is invalid. Choose from: 'pin', 'legality', 'checkmate', 'promotion', 'castles', 'stalemate', 'disambiguate'"
             << endl;
        getline(cin, setup);
    }
    Board board(setup);
    board.printBoard(true);
    if (setup == "checkmate") {
        cout << "Enter Rh8 to demonstrate checkmate." << endl;
    } else if (setup == "stalemate") {
        cout << "Enter Qb6 to demonstrate stalemate." << endl;
    } else if (setup == "promotion") {
        cout << "Enter 'a8=Q', 'a8=R', 'a8=N', or 'a8=B' to demonstrate promotion." << endl;
    } else if (setup == "disambiguate") {
        cout << "Enter 'Rbd5' or 'Rgd5' to demonstrate disambiguation." << endl;
    } else if (setup == "castles") {
        cout << "Enter '0-0' or '0-0-0' to demonstrate castling." << endl;
    } else if (setup == "legality") {
        cout << "The Black rook on f8 prevents White from moving into check on f1 or f2. ";
        board.printLegalMovesList(board.side_to_move);
    } else if (setup == "pin") {
        cout << "The Black rook on e8 prevents White from moving the knight, it is pinned to the king. ";
        board.printLegalMovesList(board.side_to_move);
    } else {
        cout << "Invalid setup type" << endl;
    }
    while (!board.game_end) {
        vector<int> moves = board.getUserMove(board.side_to_move, cout, cin);
        board.makeUserMove(moves);
        board.printBoard(true);
        board.checkGameEnd();
    }
}

//method to convert a user inputted move into the new index in tbe board
int squareToInt(string square) {
    int file = square[0] - 97;
    int rank = square[1] - 48;
    //calculation to get new index in the 0x88 board
    return (8 - rank) * 16 + file;
}

//makes the computer move
void makeCompMove(bool side, int elo, Board &board) {
    string opp_move;
    int init;
    int target;
    //gets move from stockfish
    opp_move = getMove(board.getFEN(side), elo);
    //gets initial pos of piece
    init = squareToInt(opp_move.substr(0, 2));
    //gets target position for piece
    target = squareToInt(opp_move.substr(2, 2));
    //moves piece for bot
    board.move(init, target);
}


// GRAPHICS

GLdouble width, height;
int wd;
vector<Button> board(128, Button({1,1,1},{0, 0}, 0, 0,""));
enum screens {
    start, game, finish
};
screens current_screen;

void init() {
    width = 760;
    height = 760;
    srand(time(0));
    current_screen = game;
    int rank, file;
    for (int i = 0; i < board.size(); i++) {
        if (!(i & 0x88)) {
            Button &square = board.at(i);
            rank = int(i)/16;
            file = i % 16;

            square.move(85 + file * 85, 85 + rank * 85);
            square.resize(86,86);

            //alternating colors
            if (rank % 2 == 0 && file % 2 == 1 || rank % 2 == 1 && file % 2 == 0) {
                //TODO this is a bit jank, might want to fix later
                square.setOriginalFill({0.5,0.5,0.5});
            }
            square.setLabel(to_string(i));
        }
    }
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
        string label = "Welcome to Chess!";
        glColor3f(0.5, 0.5, 0.5);
        glRasterPos2i(width / 2 - (5 * label.length()), (height / 2) - 40);
        for (const char &letter: label) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
        label = "Press 's' to start.";
        glRasterPos2i((width / 2) - (4 * label.length()), (height / 2) + 100);
        for (const char &letter: label) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
    } else if (current_screen == game) {
        for (const Quad &square: board) {
            square.draw();
        }

    } else if (current_screen == finish) {
        string label = "You Win!";
        glColor3f(1, 0, 1);
        glRasterPos2i(width / 2 - (5 * label.length()), height / 2);
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
    for (Button &square: board) {
        if (square.isOverlapping(x, y)) {
            square.hover();
        }
        else square.release();
    }
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    int total_off = 0;
    for (int index = 0; index < board.size(); index++) {
        Button &square = board.at(index);
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && square.isOverlapping(x, y)) {

        }
    }
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

    wd = glutCreateWindow("Chess" /* title */ );

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
