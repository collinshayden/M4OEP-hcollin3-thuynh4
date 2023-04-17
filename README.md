**Open Ended Project Module 4 - Chess - Hayden Collins & Hoang Huynh**

**Summary**
We are continuing to make chess for the module 4 open ended project. This is a continuation of our M3OEP. 

*Backend*
We are using a board representation technique called 0x88. The general idea is to have 
a 1x128 vector, where you can imagine your normal 8x8 playing board and then another empty 8x8 grid next to it. Each 8 indices in the 
vector alternates between a normal rank (horizontal row on a chess board) and 8 empty squares. The primary advantage to this representation
is that we can do a one line check to see if a given square index is on or off the 8x8 playing space. This is done by doing a bitwise 
and of the index and the hex value 0x88 (hence the representation name) which will return 0 if it is on the board, and 1 if off. This
representation also makes finding attacked squares and thus legal moves far easier from a programming perspective than the intuitive 
2d array representation. 
Last module we fully implemented short algebraic move input validation, legal move validation, 
captures, promotion, castling, stalemate, checkmate, FEN board state representation, pass and play game functionality, debug options to test features, 
functions to get and set the board state from custom positions, and computer moves with Stockfish 15.
via Python,

**Module 4**
For the graphics module, we moved away from the unicode board display in the console and into OpenGL and GLUT graphics. Each square is a button that has a
default color and is clickable. When a square is clicked, it records the board coordinate and waits for another click. Then it checks to see if that is a legal move, and if so, that move is made. If the second (or subsequent) clicks are not legal, the selected square is updated. The pieces are being displayed from 45x45 pixel data saved in a .txt file. This is the most unfortunate aspect of the project, as textures proved to be far to difficult. As a result of this very suboptimal piece display, the program is quite slow. It took a lot of time to figure out how to load the pieces. And with 45x45, the resolution isn't amazing, however the time cost of doing a higher resolution image in this format would be too great. 

**Bugs**
The display being refreshed really doesn't look good. It isn't necessarily a bug, but somewhat unavoidable. The app is also very slow, likely due to pieces
being displayed by loading files. 

**Future Work**
I think we are going to make a chess engine for the final project, although that likely won't involve the graphics because they are too slow. 

**Grade**
60 points for complexity. I think this project is vastly more complex than the expectations of an OEP. 
20 points for other programming language (Python)
10 points for command line input/output interfacing with Python. We are sending info to the Stockfish Python module each move via command line, 
then the Python script writes the computer move to a file, then we read the file to receive input. 
Total: 90 points. 

**References**
https://en.wikipedia.org/wiki/Board_representation_(computer_chess)
https://peterellisjones.com/posts/generating-legal-chess-moves-efficiently/
https://www.youtube.com/watch?v=n5vV4u-nKtw
https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
https://stockfishchess.org/
https://pypi.org/project/stockfish/
