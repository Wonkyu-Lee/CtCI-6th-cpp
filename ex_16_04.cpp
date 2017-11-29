//
// Created by blazeq on 2017. 11. 28..
//

#include "catch.hpp"
#include <iostream>

namespace ex_16_04 {

using namespace std;

enum GameState {
    PLAYING,
    O_WIN,
    X_WIN,
    DRAW,
};

enum CellPos {
    P1, P2, P3,
    P4, P5, P6,
    P7, P8, P9,
};

enum CellValue {
    EMPTY, O, X
};

class TicTacToe {
    CellValue _board[9];
    bool _turnOfO{true};

public:
    TicTacToe() {
        for (int i = 0; i < 9; ++i) {
            _board[i] = EMPTY;
        }
    }

    CellValue getCellValue(CellPos cellPos) const {
        return _board[cellPos];
    }

    bool empty(CellPos cellPos) const {
        return _board[cellPos] == EMPTY;
    }

    bool putOn(CellPos cellPos) {
        if (!empty(cellPos))
            return false;

        if (_turnOfO) {
            _board[cellPos] = O;
        } else {
            _board[cellPos] = X;
        }

        _turnOfO = !_turnOfO;
        return true;
    }

    bool isTurnOfO() const {
        return _turnOfO;
    }

    bool isFull() const {
        for (int i = 0; i < 9; ++i) {
            if (_board[i] == EMPTY) {
                return false;
            }
        }

        return true;
    }

    GameState getGameState() const {
        if (doesWon(O)) {
            return O_WIN;
        } else if (doesWon(X)) {
            return X_WIN;
        } else if (isFull()) {
            return DRAW;
        } else {
            return PLAYING;
        }
    }

    GameState predictGameState() const {
        TicTacToe* thiz = const_cast<TicTacToe*>(this);
        if (_turnOfO) {
            if (thiz->willWin(X)) {
                return X_WIN;
            }
        } else {
            if (thiz->willWin(O)) {
                return O_WIN;
            }
        }

        int count = 0;
        for (int i = 0; i < 9; ++i) {
            if (_board[i] != EMPTY) {
                ++count;
            }
        }
        if (count == 8) {
            return DRAW;
        }

        return PLAYING;
    }

private:
    bool filled(CellValue v, CellPos p1, CellPos p2, CellPos p3) const {
        return (_board[p1] == v) && (_board[p2] == v) && (_board[p3] == v);
    }

    bool doesWon(CellValue v) const {
        if (v == EMPTY)
            return false;

        if (filled(v, P1, P2, P3))
            return true;

        if (filled(v, P4, P5, P6))
            return true;

        if (filled(v, P7, P8, P9))
            return true;

        if (filled(v, P1, P4, P7))
            return true;

        if (filled(v, P2, P5, P8))
            return true;

        if (filled(v, P3, P6, P9))
            return true;

        if (filled(v, P1, P5, P9))
            return true;

        if (filled(v, P3, P5, P7))
            return true;

        return false;
    }

    bool willWin(CellValue v) {
        if (v == EMPTY)
            return false;

        GameState win;
        if (v == O) {
            win = O_WIN;
        } else {
            win = X_WIN;
        }

        int count = 0;
        for (int i = 0; i < 9; ++i) {
            if (_board[i] == EMPTY) {
                _board[i] = v;
                if (getGameState() == win) {
                    ++count;
                    if (1 < count) {
                        _board[i] = EMPTY;
                        return true;
                    }
                }
                _board[i] = EMPTY;
            }
        }

        return false;
    }
};

void playTicTacToe() {
    TicTacToe game;

    auto showBord = [&game]() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                char ch;
                switch (game.getCellValue((CellPos)(i * 3 + j))) {
                    case O: ch = 'O'; break;
                    case X: ch = 'X'; break;
                    default: ch = ' ';
                }
                cout << ch << " ";
            }
            cout << endl;
        }
        cout << endl;
    };

    while (true) {
        switch (game.predictGameState()) {
            case O_WIN:
                cout << "O Win!" << endl;
                return;
            case X_WIN:
                cout << "X Win!" << endl;
                return;
            case DRAW:
                cout << "Draw!" << endl;
                return;
            default:
                ; // do nothing
        }

        showBord();

        cout << "Turn of " << (game.isTurnOfO() ? 'O' : 'X') <<" : ";

        int i = -1;
        cin >> i;
        --i;
        if (i < 0 || 9 <= i) {
            continue;
        }
        if (!game.empty((CellPos)i)) {
            continue;
        }

        game.putOn((CellPos)i);
    }
}

TEST_CASE("16-04", "[16-04]") {
    TicTacToe game;
    game.putOn(P5);
    REQUIRE(game.predictGameState() == PLAYING);
    game.putOn(P4);
    REQUIRE(game.predictGameState() == PLAYING);
    game.putOn(P1);
    REQUIRE(game.predictGameState() == PLAYING);
    game.putOn(P9);
    REQUIRE(game.predictGameState() == PLAYING);
    game.putOn(P3);
    REQUIRE(game.predictGameState() == O_WIN);
}

} // namespace ex_16_04