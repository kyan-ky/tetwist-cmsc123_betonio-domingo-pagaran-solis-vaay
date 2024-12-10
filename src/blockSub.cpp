#include "blockMain.h"
#include "pos.h"

class blockJ : public blockMain {
    public:
        blockJ() {
            cellId = 1;
            cell[0] = {Pos(0, 0), Pos(1, 0), Pos(1, 1), Pos(1, 2)};
            cell[1] = {Pos(0, 1), Pos(0, 2), Pos(1, 1), Pos(2, 1)};
            cell[2] = {Pos(1, 0), Pos(1, 1), Pos(1, 2), Pos(2, 2)};
            cell[3] = {Pos(0, 1), Pos(1, 1), Pos(2, 0), Pos(2, 1)};
            Move(0, 3);
        }
};

class blockL : public blockMain {
    public:
        blockL() {
            cellId = 2;
            cell[0] = {Pos(0, 2), Pos(1, 0), Pos(1, 1), Pos(1, 2)};
            cell[1] = {Pos(0, 1), Pos(1, 1), Pos(2, 1), Pos(2, 2)};
            cell[2] = {Pos(1, 0), Pos(1, 1), Pos(1, 2), Pos(2, 0)};
            cell[3] = {Pos(0, 0), Pos(0, 1), Pos(1, 1), Pos(2, 1)};
            Move(0, 3);
        }
};

class blockI : public blockMain {
    public:
        blockI() {
            cellId = 3;
            cell[0] = {Pos(1, 0), Pos(1, 1), Pos(1, 2), Pos(1, 3)};
            cell[1] = {Pos(0, 2), Pos(1, 2), Pos(2, 2), Pos(3, 2)};
            cell[2] = {Pos(2, 0), Pos(2, 1), Pos(2, 2), Pos(2, 3)};
            cell[3] = {Pos(0, 1), Pos(1, 1), Pos(2, 1), Pos(3, 1)};
            Move(-1, 3);       
        }
};

class blockS : public blockMain {
    public:
        blockS() {
            cellId = 4;
            cell[0] = {Pos(0, 1), Pos(0, 2), Pos(1, 0), Pos(1, 1)};
            cell[1] = {Pos(0, 1), Pos(1, 1), Pos(1, 2), Pos(2, 2)};
            cell[2] = {Pos(1, 1), Pos(1, 2), Pos(2, 0), Pos(2, 1)};
            cell[3] = {Pos(0, 0), Pos(1, 0), Pos(1, 1), Pos(2, 1)};
            Move(0, 3);
        }
};

class blockZ : public blockMain {
    public:
        blockZ() {
            cellId = 5;
            cell[0] = {Pos(0, 0), Pos(0, 1), Pos(1, 1), Pos(1, 2)};
            cell[1] = {Pos(0, 2), Pos(1, 1), Pos(1, 2), Pos(2, 1)};
            cell[2] = {Pos(1, 0), Pos(1, 1), Pos(2, 1), Pos(2, 2)};
            cell[3] = {Pos(0, 1), Pos(1, 0), Pos(1, 1), Pos(2, 0)};
            Move(0, 3);
        }
};

class blockO : public blockMain {
    public:
        blockO() {
            cellId = 6;
            cell[0] = {Pos(0, 0), Pos(0, 1), Pos(1, 0), Pos(1, 1)};
            cell[1] = {Pos(0, 0), Pos(0, 1), Pos(1, 0), Pos(1, 1)};
            cell[2] = {Pos(0, 0), Pos(0, 1), Pos(1, 0), Pos(1, 1)};
            cell[3] = {Pos(0, 0), Pos(0, 1), Pos(1, 0), Pos(1, 1)};
            Move(0, 4);
        }
};

class blockT : public blockMain {
    public:
        blockT() {
            cellId = 7;
            cell[0] = {Pos(0, 1), Pos(1, 0), Pos(1, 1), Pos(1, 2)};
            cell[1] = {Pos(0, 1), Pos(1, 1), Pos(1, 2), Pos(2, 1)};
            cell[2] = {Pos(1, 0), Pos(1, 1), Pos(1, 2), Pos(2, 1)};
            cell[3] = {Pos(0, 1), Pos(1, 0), Pos(1, 1), Pos(2, 1)};
            Move(0, 3);
        }
};
class blockBomb : public blockMain {
    private:
        Texture2D bombTexture; 

    public:
        blockBomb() {
            cellId = 8; 
            cell[0] = {Pos(0, 0)}; 
            cell[1] = {Pos(0, 0)};
            cell[2] = {Pos(0, 0)};
            cell[3] = {Pos(0, 0)};
            Move(0, 3);

        }

};