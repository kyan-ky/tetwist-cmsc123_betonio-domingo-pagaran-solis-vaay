#include "blockMain.h"
#include "pos.h"
#include "C:\raylib\raylib\src\raylib.h"

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
        Texture2D bombTexture; // Texture for the bomb
    
    public:
        blockBomb() {
            cellId = 8; // Unique ID for the bomb
            cell[0] = {Pos(0, 0)}; // Bomb is a single-cell block
            cell[1] = {Pos(0, 0)};
            cell[2] = {Pos(0, 0)};
            cell[3] = {Pos(0, 0)};
            Move(0, 3);
            
            // Load the bomb texture
            // bombTexture = LoadTexture("C:\\Users\\vaay\\tetwist-cmsc123\\src\\bomb.jpg");
        }
        
        ~blockBomb() {
            UnloadTexture(bombTexture); // Clean up the texture when done
        }



        // void OnLand(Grid &grid) override {
        //     // Define explosion radius
        //     int explosionRadius = 1; // 3x3 grid around the bomb
        //     Pos position = GetCurrentPosition();

        //     // Clear blocks within the explosion radius
        //     for (int i = -explosionRadius; i <= explosionRadius; i++) {
        //         for (int j = -explosionRadius; j <= explosionRadius; j++) {
        //             Pos affectedPos = Pos(position.x + i, position.y + j);
        //             if (grid.IsValid(affectedPos)) {
        //                 grid.ClearBlock(affectedPos);
        //             }
        //         }
        //     }
        // }
};
