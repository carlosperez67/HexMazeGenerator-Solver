#include "HexBoard.h"

#include <iostream>

#include "queue.h"
#include "stack.h"

HexBoard::HexBoard(int radius) {
    this->radius = radius;
    start_coord = make_pair(0,0);
    longest_path_dist = 0;
    // end_coord = NULL;
    // solution = NULL;
    // cells = NULL;
    create_board();
    configure_cells();
    
}

void HexBoard::create_board() {

    for (int i= -(start_coord.first + radius - 1); i <= (start_coord.first + radius - 1); i++) {
        int numCells = abs(abs(i) - radius + 1) + radius;
        if (i<0) {
            for (int j = -(i + radius - 1); j < numCells - (i + radius - 1); j++) {
                HexCell* cell2Add = new HexCell(i, j);
                cells.insert({make_pair(i,j), cell2Add});
            }
        }
        else {
            for (int j = -(radius - 1); j < numCells - (radius - 1); j++) {
                HexCell* cell2Add = new HexCell(i, j);
                cells.insert({make_pair(i,j), cell2Add});
            }
        }
    
    }
}

void HexBoard::configure_cells() {

    for (auto kv : cells) {
        pair<int,int> coord = kv.first;
        HexCell* cell = kv.second;
        for (auto keyVal: cells) {
            HexCell* secondCell = keyVal.second;
            if (cell->is_neighbour(secondCell)) {
                int side = cell->get_neighbour_side(secondCell);
                cell->neighbours[side] = secondCell;
            }
        }
    }
}


pair<int,int> HexBoard::cell_coord(HexCell* cell) {
    return make_pair(cell->q, cell->r);
}




void HexBoard::generate_maze(pair<int, int> start_coord, double branch_prob) {               // length of longest path to an edge in the maze
    this->start_coord = start_coord;
    Stack<pair<int,int>> stack;
    map<pair<int,int>, bool> visited;

    stack.push(start_coord);                 // added start_coord to stack
    visited.insert({start_coord, true});    // mark start_coord as visited
    int length = 0;

    while (!stack.isEmpty()) {
        HexCell* curr_cell = cells.find(stack.peek())->second; // the cell in cells map
        HexCell* neigh_cell = chooseNeighbour(curr_cell, visited, branch_prob);
        if (neigh_cell) {           // not NULL
            curr_cell->link(neigh_cell);
            visited.insert({cell_coord(neigh_cell), true});
            neigh_cell->path_dist_from_start = curr_cell->path_dist_from_start + 1;

            if (neigh_cell->path_dist_from_start > longest_path_dist) { // update longest path length if necessary
                longest_path_dist = neigh_cell->path_dist_from_start;  
            }

            if (neigh_cell->is_edge() && (neigh_cell->path_dist_from_start > length)) {
                end_coord = cell_coord(neigh_cell);
                length = neigh_cell->path_dist_from_start;
            }

            stack.push(cell_coord(neigh_cell));
        } else {
            stack.pop();
        }
    }
    
}

void HexBoard::solve_maze() {
    Stack<pair<pair<int,int>,vector<pair<int,int>>>> stack;
    map<pair<int,int>, bool> visited;
    vector<pair<int,int>> path;
    

    /** A Stack of pairs
     *      each pair contains:
     *          1) The current coordinate of the cell
     *          2) A vector of coordinates corresponding to the path taken
    */

    path.push_back(start_coord);
    stack.push(make_pair(start_coord,path));
    visited.insert({start_coord, true});
    int shortestSolution = INT_MAX;

    while(!stack.isEmpty()) {
        pair<pair<int,int>,vector<pair<int,int>>> currElem = stack.pop();
        HexCell* currCell = cells.find(currElem.first)->second;  // first cell in the stack

        if ((cell_coord(currCell) == end_coord) && ((int) currElem.second.size() < shortestSolution)) {
            solution = currElem.second;
            shortestSolution = currElem.second.size();
        } else {
            for (auto kv: currCell->links) {
                if (kv && (visited.find(cell_coord(kv)) == visited.end())) {    // if there is a link and it hasn't already been visited
                    pair<int,int> currCoord = cell_coord(kv);
                    vector<pair<int,int>> currPath = currElem.second;   // the path of coords to this cell
                    currPath.push_back(currCoord);
                    auto nextElem = make_pair(currCoord, currPath);
                    stack.push(nextElem);
                    visited.insert({currCoord, true});
                }
            }
        }
    }

    //stub todo

}



