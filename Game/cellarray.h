#ifndef CELLARRAY_H
#define CELLARRAY_H
#include "Enums.h"
#include <cstdlib>

struct Cell {
    int pos_i, pos_j;
    Direction back_direction;
    bool visited, free;
    Cell * back_cell;
};

class CellArray
{
private:
    Cell ** colision;
    int x, y;
    CellArray() { }

    CellArray(const CellArray &);
    CellArray &operator = (const CellArray &);
public:
    ~CellArray(){}
    Cell ** get() const { return colision; }
    void setCell(int x, int y, int ** mat) {
        this->x = x; this->y = y;
        colision = new Cell*[x];
        for (int i = 0; i < x; i++) {
            colision[i] = new Cell[y];
            for (int j = 0; j < y; j++) {
                colision[i][j].pos_i = i;
                colision[i][j].pos_j = j;
                colision[i][j].visited = false;
                colision[i][j].back_direction = SLEEP;
                colision[i][j].back_cell = NULL;
                if(mat[i][j])
                    colision[i][j].free = false;
                else
                    colision[i][j].free = true;
            }
        }
    }

    static CellArray *instance();
};

#endif // CELLARRAY_H
