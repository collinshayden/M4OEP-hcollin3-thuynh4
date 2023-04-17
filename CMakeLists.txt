cmake_minimum_required(VERSION 3.23)
project(M4OEP_hcollin3-thuynh4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wno-deprecated")

find_package (OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR}  ${GLUT_INCLUDE_DIRS})

file(GLOB SOURCE_FILES
        *.cpp
        *.h
        )




add_executable(M3OEP_hcollin3-thuynh4 ${SOURCE_FILES}
        main.cpp Board.cpp Board.h Piece.cpp Piece.h pieces/Rook.cpp pieces/Rook.h pieces/Bishop.cpp pieces/Bishop.h pieces/Pawn.cpp pieces/Pawn.h pieces/Queen.cpp pieces/Queen.h pieces/King.cpp pieces/King.h pieces/Knight.cpp pieces/Knight.h pieces/pieceClasses.h pieces/Empty.cpp pieces/Empty.h)

target_link_libraries (M3OEP_hcollin3-thuynh4 ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})