//
// Created by Hayden Collins on 2/21/23.
//

#ifndef M1OEP_HCOLLIN3_KNIGHT_H
#define M1OEP_HCOLLIN3_KNIGHT_H

#include "../Piece.h"

class Knight : public Piece{
public:
    Knight(bool side);
    vector<int> getAttackedSquares(int initial_pos);

};


#endif //M1OEP_HCOLLIN3_KNIGHT_H
