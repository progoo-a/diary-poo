#include <iostream>
using namespace std;

enum class Birds : short {
    SPARROW,
    ROBIN,
    BLUEJAY,
    BLACKBIRD
};

void foo(Birds b) {
    cout << static_cast<short>(b) << endl;
}

int main () {
    Birds b = Birds::BLUEJAY;
    foo(b);
    foo((Birds)3);
    foo(Birds::BLACKBIRD);
}

enum class CellState : char {
    UNREVEALED = '.',
    ZERO_ADJACENT = ' ',
    FLAGGED = '?',
    BOMB = 'x',
    ONE_ADJACENT = '1',
    TWO_ADJACENT,
    THREE_ADJACENT,
    FOUR_ADJACENT,
    FIVE_ADJACENT,
    SIX_ADJACENT,
    SEVEN_ADJACENT,
    EIGHT_ADJACENT,
};

class Cell {
    bool is_bomb, is_flagged;
    int adjacent_bombs;
    auto to_char() {
        if (is_bomb) return CellState::BOMB;
        if (adjacent_bombs > 0) return static_cast<CellState>(adjacent_bombs);
        if (is_flagged) return CellState::FLAGGED;
        return '.';
    }
}