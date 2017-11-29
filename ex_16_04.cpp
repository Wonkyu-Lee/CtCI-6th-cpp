//
// Created by blazeq on 2017. 11. 28..
//

#include "catch.hpp"
#include <vector>
#include <stack>
#include <list>
#include <cassert>
#include <iostream>

namespace ex_16_04 {

namespace tic_tac_toe {

using namespace std;

const int SLOT_COUNT = 9;
enum class SlotState
{
    INVALID = -1, EMPTY, X, O
};
enum class GameState
{
    PLAYING, X_WIN, O_WIN, DRAW
};

class Game
{
public:
    Game();

    SlotState getSlotState(int slot) const;

    GameState getGameState() const;

    bool mark(int slot);

    bool rollback();

    bool isXTurn() const;

    const vector<SlotState>& getSlotStates() const;

    vector<int> getEmptySlots() const;

    vector<int> getSlotsThatMustBeBlocked() const;

    void reset();

    bool willDraw(int limit) const;

    list<int> getSequence() const;

private:
    bool _xTurn;
    vector<SlotState> _slotStates{9, SlotState::EMPTY};
    stack<int> _slotStack;
};

void run(Game* debugGame = nullptr);

void play(bool userIsX);

} // namespace tic_tac_toe



namespace tic_tac_toe {

namespace {

bool _willDraw(Game& g, int depth) {
    switch (g.getGameState()) {
        case GameState::DRAW: {
            return true;
        }
        case GameState::PLAYING: {
            if (depth == 0) {
                return false;
            }
            auto emptySlots = g.getEmptySlots();
            for (auto slot : emptySlots) {
                g.mark(slot);
                if (!_willDraw(g, depth - 1)) {
                    return false;
                }
                g.rollback();
            }
            return true;
        }
        default : {
            return false;
        }
    }
};

} // namespace

Game::Game()
        : _xTurn(true)
{
}

SlotState Game::getSlotState(int slot) const {
    if (slot < 0 || SLOT_COUNT <= slot) {
        return SlotState::INVALID;
    }

    return _slotStates[slot];
}

bool Game::mark(int slot) {
    if (slot < 0 || SLOT_COUNT <= slot) {
        return false;
    }

    if (_slotStates[slot] != SlotState::EMPTY) {
        return false;
    }

    _slotStates[slot] = _xTurn ? SlotState::X : SlotState::O;
    _xTurn = !_xTurn;
    _slotStack.push(slot);
    return true;
}

bool Game::rollback() {
    if (_slotStates.empty()) {
        return false;
    }

    int lastMarked = _slotStack.top();
    _slotStack.pop();

    _slotStates[lastMarked] = SlotState::EMPTY;
    _xTurn = !_xTurn;
    return true;
}

bool Game::isXTurn() const {
    return _xTurn;
}

const vector<SlotState>& Game::getSlotStates() const {
    return _slotStates;
}

GameState Game::getGameState() const {
    auto isAll = [&](SlotState slotState, int s1, int s2, int s3) {
        return _slotStates[s1] == slotState && _slotStates[s2] == slotState && _slotStates[s3] == slotState;
    };

    auto hasLine = [&](SlotState slotState) {
        return  isAll(slotState, 0, 1, 2) ||
                isAll(slotState, 3, 4, 5) ||
                isAll(slotState, 6, 7, 8) ||
                isAll(slotState, 0, 3, 6) ||
                isAll(slotState, 1, 4, 7) ||
                isAll(slotState, 2, 5, 8) ||
                isAll(slotState, 0, 4, 8) ||
                isAll(slotState, 2, 4, 6);
    };

    auto isFull = [&]() {
        for (int i = 0; i < SLOT_COUNT; ++i) {
            if (_slotStates[i] == SlotState::EMPTY)
                return false;
        }
        return true;
    };

    if (hasLine(SlotState::X)) {
        return GameState::X_WIN;
    } else if (hasLine(SlotState::O)) {
        return GameState::O_WIN;
    } else if (isFull()) {
        return GameState::DRAW;
    } else {
        return GameState::PLAYING;
    }
}

vector<int> Game::getEmptySlots() const {
    vector<int> emptySlots;
    for (int i = 0; i < SLOT_COUNT; ++i) {
        if (_slotStates[i] == SlotState::EMPTY) {
            emptySlots.push_back(i);
        }
    }

    return emptySlots;
}

vector<int> Game::getSlotsThatMustBeBlocked() const {
    vector<int> result;
    Game game = *this;
    SlotState opposite  = game.isXTurn() ? SlotState::O : SlotState::X;
    GameState oppositeWin = game.isXTurn() ? GameState::O_WIN : GameState::X_WIN;

    for (int i = 0; i < SLOT_COUNT; ++i) {
        if (game.getSlotState(i) == SlotState::EMPTY) {
            game._slotStates[i] = opposite;
            if (game.getGameState() == oppositeWin) {
                result.push_back(i);
            }
            game._slotStates[i] = SlotState::EMPTY;
        }
    }

    return result;
}

void Game::reset() {
    _xTurn = true;
    for (auto& slot : _slotStates) {
        slot = SlotState::EMPTY;
    }
}

bool Game::willDraw(int limit) const {
    Game game = *this;
    return _willDraw(game, limit);
}

list<int> Game::getSequence() const {
    stack<int> stack(_slotStack);
    list<int> sequence;
    while (!stack.empty()) {
        int top = stack.top();
        stack.pop();
        sequence.push_front(top);
    }
    return sequence;
}

void showSlotIndexes() {
    cout << "-----" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int slot = i * 3 + j;
            cout << slot << " ";
        }
        cout << endl;
    }
    cout << "-----" << endl;
};

void showBoard(const Game& game) {
    cout << "-----" << endl;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            int slot = i * 3 + j;
            SlotState state = game.getSlotState(slot);
            char glyph;
            switch (state) {
                case SlotState::O: glyph = 'O'; break;
                case SlotState::X: glyph = 'X'; break;
                default: glyph = ' ';
            }
            cout << glyph << " ";
        }
        cout << endl;
    }
    cout << "-----" << endl;
};

bool askQuit() {
    cout << "Quit(y/n)? ";
    char answer;
    cin >> answer;
    bool quit = (answer == 'y');
    if (quit) {
        cout << "Bye~" << endl;
        return true;
    } else {
        cout << "Game start!" << endl;
        showSlotIndexes();
        return false;
    }
}

void run(Game* debugGame) {
    Game game;

    if (debugGame == nullptr) {
        cout << "Game start!" << endl;
        showSlotIndexes();
    } else {
        game = *debugGame;
        showBoard(game);
    }

    while (true) {
        GameState gameState = game.getGameState();
        bool gameOver = false;

        if (gameState != GameState::PLAYING) {
            switch (gameState) {
                case GameState::O_WIN:
                    cout << "O win!" << endl;
                    break;
                case GameState::X_WIN:
                    cout << "X win!" << endl;
                    break;
                case GameState::DRAW:
                    cout << "Draw!" << endl;
                    break;
                default:
                    assert (false);
            }

            gameOver = true;
        } else {
            if (game.willDraw(3)) {
                cout << "Eventually will draw!" << endl;
                gameOver = true;
            }
        }

        if (gameOver) {
            cout << "Sequence: ";
            auto sequence = game.getSequence();
            for (auto each : sequence) {
                cout << each << " ";
            }
            cout << endl;

            if (askQuit()) {
                break;
            } else {
                game.reset();
            }
        }

        while (true) {
            cout << (game.isXTurn() ? "X" : "O") << "'s turn -> ";
            int slot = -1;
            cin >> slot;
            if (game.mark(slot)) {
                break;
            } else {
                cout << "Error! Wrong slot!" << endl;
                continue;
            }
        }

        showBoard(game);
    }
}

void play(bool userIsX) {
    std::srand((unsigned int)time(nullptr));
    Game game;

    cout << "Game start!" << endl;
    showSlotIndexes();

    while (true) {
        bool gameOver = false;
        bool userTurn = (game.isXTurn() && userIsX) || (!game.isXTurn() && !userIsX);

        GameState gameState = game.getGameState();
        if (gameState != GameState::PLAYING) {
            switch (gameState) {
                case GameState::O_WIN:
                    cout << "O win!" << endl;
                    break;
                case GameState::X_WIN:
                    cout << "X win!" << endl;
                    break;
                case GameState::DRAW:
                    cout << "Draw!" << endl;
                    break;
                default:
                    assert (false);
            }
            gameOver = true;

        } else {
            if (game.willDraw(3)) {
                cout << "Eventually will draw!" << endl;
                gameOver = true;
            }
            if (userTurn) {
                auto mustSLots = game.getSlotsThatMustBeBlocked();
                if (1 < mustSLots.size()) {
                    char who = (game.isXTurn() ? 'X' : 'O');
                    cout << "Eventually " << who <<" will lose!" << endl;
                    gameOver = true;
                }
            }
        }

        if (gameOver) {
            if (askQuit()) {
                break;
            } else {
                game.reset();
            }
        }

        cout << (game.isXTurn() ? "X" : "O") << "'s turn -> ";
        if (userTurn) {
            while (true) {
                int slot = -1;
                cin >> slot;
                if (game.mark(slot)) {
                    break;
                } else {
                    cout << "Error! Wrong slot!" << endl;
                    cout << (game.isXTurn() ? "X" : "O") << "'s turn -> ";
                    continue;
                }
            }
        } else {
            auto mustSlots = game.getSlotsThatMustBeBlocked();
            int nextSlot;
            if (mustSlots.empty()) {
                auto emptySlots = game.getEmptySlots();
                size_t slot = std::rand() % emptySlots.size();
                nextSlot = emptySlots[slot];
            } else {
                nextSlot = mustSlots.front();
            }

            cout << nextSlot << endl;
            bool success = game.mark(nextSlot);
            assert (success);
        }

        showBoard(game);
    }
}

} // namespace tic_tac_toe

TEST_CASE("16-04", "[16-04]") {
    tic_tac_toe::Game game;
    int sequence[] = {0, 4, 2, 1, 7, 5, 3, 6, 8};
    for (auto each : sequence) {
        game.mark(each);
    }
    REQUIRE(game.getGameState() == tic_tac_toe::GameState::DRAW);
}

} // namespace ex_16_04