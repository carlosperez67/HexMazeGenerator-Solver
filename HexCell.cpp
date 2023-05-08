#include "HexCell.h"

#include <cmath>

HexCell::HexCell(int Q, int R) {
    /**
     * @todo Your code here!
     */

    q = Q;                  // initializing field coord
    r = R;                  // init field coord
    for (int i=0; i<6; i++){
        links[i] = nullptr;
        neighbours[i]= nullptr;
    }
    path_dist_from_start = 0;   // init to 0
}

void HexCell::link(HexCell* cell) {
    /**
     * @todo Your code here!
     */

    if (cell && is_neighbour(cell)){                      // checking that the cell is and a neighbout
        int side = get_neighbour_side(cell);
        links[side] = cell; // linking both directions
        cell->links[(side + 3) % 6] = this;
    }
    // else do nothing
}



int HexCell::get_neighbour_side(const HexCell* cell) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */

    int tempQ =  cell->q - this->q;
    int tempR = cell->r - this->r;
    pair<int,int> diffPair = {tempQ, tempR};

    for (int i=0; i<6;i++) {
        if (diffPair == unitVectors[i]) {
            return i;
        }
    }
    return -1;          // if they are not neighbours
}

bool HexCell::is_linked(const HexCell* cell) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    if (!cell) {
        return false;
    }
    for (int i=0; i<6; i++){
        if (links[i] == cell)
            return true;
    }
    return false;
}

bool HexCell::is_neighbour(const HexCell* cell) const {
    return (distance(cell) == 1);
}

int HexCell::distance(const HexCell* cell) const {
    /**
     * @todo Your code here! You will need to replace the following line.
     */
    if (!cell)                  // cell being a nullpointer
        return -1;
    int qPrime = q - cell->q;
    int rPrime = r - cell->r;

    return ((abs(qPrime) + abs(qPrime + rPrime) + abs(rPrime))/2);

}

bool HexCell::is_edge() const {
    for (int i=0; i<6; i++)
        if (!neighbours[i])
            return true;

    return false;
}

// pair<int,int> HexCell::get_coord() const {
//     pair<int,int> result = make_pair(q,r);
//     return result;
// }




