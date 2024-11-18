#include <vector>
#include <iostream>
#include <utility>
#include <functional>

using namespace std;

class Cell
{
public:
    int row, col;
    bool isBomb = false;
    int vinicityBombs = 0;
    bool flagged = false;
    bool revealed = false;

public:
    char getSymbol(bool debug = false)
    {
        if (debug || revealed)
        {
            if (isBomb)
                return '*';
            if (vinicityBombs > 0)
            {
                return '0' + vinicityBombs;
            }
            return '.';
        }
        return '~';
    }
};

class Board
{
    using size_type = long unsigned int;

    vector<Cell> cells;
    vector<int> bombIndices;

    size_type rows, cols;
    size_type bombs;
    size_type bombsLeft;
    int cellsToReveal;

public:
    Board(size_type rows, size_type cols, size_type bombs) : cells{rows * cols}, rows{rows}, cols{cols}, bombs{bombs}
    {
        for (int row = 0; row < rows; ++row)
        {
            for (int col = 0; col < cols; ++col)
            {
                getCell(row, col).row = row;
                getCell(row, col).col = col;
            }
        }
    }

    Cell &getCell(int row, int col)
    {
        return cells[row * cols + col];
    }

    void display(bool debug = false)
    {
        for (int row = 0; row < rows; ++row)
        {
            for (int col = 0; col < cols; ++col)
            {
                cout << getCell(row, col).getSymbol(debug) << ' ';
            }
            cout << endl;
        }
    }

    // private:
    void placeBombs()
    {
        bombIndices.clear();
        int left = bombs;
        while (left)
        {
            size_t index = rand() % (rows * cols);
            auto &cell = cells[index];
            if (!cell.isBomb)
            {
                cell.isBomb = true;
                bombIndices.push_back(index);
                left--;
            }
        }
    }

    static constexpr pair<int, int> deltas[] = {
        pair<int, int>{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    void placeNumbers()
    {
        for (auto index : bombIndices)
        {
            auto &cell = cells[index];
            neighbours(cell, [](Cell &neighbour)
                       {
                if (!neighbour.isBomb) neighbour.vinicityBombs++; });
        }
    }

    bool isValidCell(int row, int col)
    {
        return !(row < 0 || col < 0 || row > rows - 1 || col > cols - 1);
    }

    bool reveal(int row, int col)
    {
        if (!isValidCell(row, col))
            return true;
        return expand(getCell(row, col));
    }

    bool expand(Cell &cell)
    {
        if (cell.revealed) return true;
        if (cell.vinicityBombs > 0) {
            cell.revealed = true;
            return true;
        }
        if (cell.isBomb) {
            cell.revealed = true;
            return false;
        }
        cell.revealed = true;
        neighbours(cell, [this](Cell&cell){ expand(cell);} );
        return true;
    }

    void neighbours(Cell &cell, function<void(Cell &)> cb)
    {
        for (auto delta : deltas) {
            const int row = cell.row + delta.first;
            const int col = cell.col + delta.second;
            if (!isValidCell(row, col))
                continue;
            cb(getCell(row, col));
        }
    }
};

int main()
{
    Board board{5, 5, 3};
    board.placeBombs();
    board.placeNumbers();
    board.reveal(4, 4);
    board.display(false);
    cout << "\n";
    board.display(true);
}