// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "tilelist.h"

TileList::TileList() {
    TileNode *source = new TileNode(3, 4, 1, 2, "red", NULL, NULL);
    // TODO: write this constructor
}

TileList::~TileList() {
    // TODO: write this destructor
}

void TileList::debug() {
    // TODO: write this function (optional)
}

void TileList::addBack(int x, int y, int width, int height, string color) {
    // TODO: write this function
}

void TileList::addFront(int x, int y, int width, int height, string color) {
    // TODO: write this function
}

void TileList::clear() {
    // TODO: write this function
}

void TileList::drawAll(GWindow& window) {
    // TODO: write this function
}

void TileList::highlight(int x, int y) {
    // TODO: write this function
}

void TileList::lower(int x, int y) {
    // TODO: write this function
}

void TileList::raise(int x, int y) {
    // TODO: write this function
}

void TileList::remove(int x, int y) {
    // TODO: write this function
}

void TileList::removeAll(int x, int y) {
    // TODO: write this function
}
