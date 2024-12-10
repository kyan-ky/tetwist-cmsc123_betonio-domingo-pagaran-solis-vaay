#include "color.h"

using namespace std;

const Color black = {14, 17, 17, 255};
const Color indigo = {10, 10, 255, 255};
const Color orange = {255, 151, 28, 255};
const Color cyan = {10, 255, 255, 255};
const Color red = {255, 50, 19, 255};
const Color green = {114, 203, 59, 255};
const Color yellow = {254, 213, 1, 255};
const Color purple = {191, 40, 212, 255};
const Color lightgray = {11, 9, 10, 11};
const Color white = {234, 231, 230, 255};
const Color pink = {255, 182, 193, 255};


vector<Color> getCellColor() {
    return {black, indigo, orange, cyan, red, green, yellow, purple, lightgray, white, pink};
}

