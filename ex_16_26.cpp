//
// Created by blazeq on 2017. 12. 6..
//

#include <iostream>
#include <cassert>
#include <stack>
#include "catch.hpp"

namespace ex_16_26 {

using namespace std;

enum TokenType { OPERATOR, OPERAND };
enum OperatorType { ADD, SUB, MUL, DIV };

class Token {
public:
    virtual ~Token() {}
    virtual TokenType type() const = 0;
    virtual ostream& write(ostream& o) const = 0;
    friend ostream& operator<<(ostream& o, const Token& token) {
        return token.write(o);
    }
};

class Operator : public Token {
    OperatorType _opType;
    int _priority{0};
public:
    TokenType type() const override {
        return OPERATOR;
    }

    Operator(OperatorType opType):_opType(opType) {
        switch (_opType) {
            case ADD:
            case SUB:
                _priority = 1;
                break;
            case MUL:
            case DIV:
                _priority = 2;
                break;
            default: assert(false);
        }
    }

    OperatorType operatorType() const { return _opType; }

    ostream& write(ostream& o) const override {
        switch (_opType) {
            case ADD: return o << '+';
            case SUB: return o << '-';
            case MUL: return o << '*';
            case DIV: return o << '/';
            default: assert(false);
        }
    }

    int priority() const { return _priority; }

    double operator()(double a, double b) const {
        switch (_opType) {
            case ADD: return a + b;
            case SUB: return a - b;
            case MUL: return a * b;
            case DIV: {
                if (b == 0) {
                    throw string("Divide by zero!");
                }
                return a / b;
            }
            default: assert(false);
        }
    }
};

class Operand : public Token {
    int _value{0};
public:
    TokenType type() const override {
        return OPERAND;
    }

    Operand(int value):_value(value) {}
    int value() const { return _value; }

    ostream& write(ostream& o) const override {
        return o << _value;
    }
};

class Tokenizer {
    vector<Token*> _tokens;
    bool _valid{true};
    string _errorMessage;

public:
    class Iterator {
        vector<Token*>::const_iterator _it;
        vector<Token*>::const_iterator _itEnd;

    public:
        Iterator(const vector<Token*>& tokens) {
            _it = tokens.begin();
            _itEnd = tokens.end();
        }

        bool valid() const {
            return _it != _itEnd;
        }

        const Token& value() const {
            if (!valid())
                throw "Invalid access!";
            return *(*_it);
        }

        void next() {
            _it++;
        }
    };

    Tokenizer(const string& expr) {
        _valid = tokenize(expr);
    }

    ~Tokenizer() {
        for (auto each : _tokens) {
            delete each;
        }
    }

    bool valid() const { return _valid; }

    const string& errorMessage() const { return _errorMessage; }

    Iterator iterator() const {
        return Iterator(_tokens);
    }

private:
    bool tokenize(const string& expr) {
        _tokens.clear();

        size_t i = 0;
        while (i < expr.size()) {
            char ch = expr[i];

            if (isSpace(ch)) {
                ++i;
            } else if (isOperator(ch)) {
                Operator* token = readOperator(expr, i);
                _tokens.push_back(token);
            } else if (isDigit(ch)) {
                Operand* token = readOperand(expr, i);
                _tokens.push_back(token);
            } else {
                ostringstream out;
                out << "Invalid character: " << ch;
                _errorMessage = out.str();
                return false;
            }
        }

        return true;
    }

    Operator* readOperator(const string& expr, size_t& i) {
        Operator* token;
        char ch =  expr[i];
        switch (ch) {
            case '+': token = new Operator(ADD); break;
            case '-': token = new Operator(SUB); break;
            case '*': token = new Operator(MUL); break;
            case '/': token = new Operator(DIV); break;
            default: assert(false);
        }

        ++i;
        return token;
    }

    Operand* readOperand(const string& expr, size_t& i) {
        int start = i;
        int value = 0;
        while (i < expr.size()) {
            char ch = expr[i];
            if (isDigit(ch)) {
                value = 10 * value + ch - '0';
                ++i;
            } else {
                break;
            }
        }

        if (i == start) {
            return nullptr;
        }

        return new Operand(value);
    }

    static bool isDigit(char ch) {
        return '0' <= ch && ch <= '9';
    }

    static bool isOperator(char ch) {
        return (ch == '+') || (ch == '-') || (ch == '*') || (ch == '/');
    }

    static bool isSpace(char ch) {
        return (ch == ' ') || (ch == '\t') || (ch == '\n');
    }
};

class Lexer {
    bool _valid{true};
    string _errorMessage;

public:
    Lexer(Tokenizer::Iterator it) {
        if (!it.valid())
            return;

        if (it.value().type() == OPERAND) {
            it.next();
        } else {
            _valid = false;
            ostringstream out;
            out << "Invalid token: " << it.value();
            _errorMessage = out.str();
            return;
        }

        while (it.valid()) {
            if (it.value().type() == OPERATOR) {
                it.next();
            } else {
                _valid = false;
                ostringstream out;
                out << "Invalid token: " << it.value();
                _errorMessage = out.str();
                return;
            }

            if (!it.valid()) {
                _valid = false;
                ostringstream out;
                out << "Must end with operand!";
                _errorMessage = out.str();
                return;
            }

            if (it.value().type() == OPERAND) {
                it.next();
            } else {
                _valid = false;
                ostringstream out;
                out << "Invalid token: " << it.value();
                _errorMessage = out.str();
                return;
            }
        }
    }

    bool valid() const { return _valid; }

    const string& errorMessage() const { return _errorMessage; }
};

class Calculator {
    bool _valid{true};
    string _errorMessage;
    double _result{0};

public:
    Calculator(const string& expr) {
        Tokenizer tokenizer(expr);
        if (!tokenizer.valid()) {
            _valid = false;
            _errorMessage = tokenizer.errorMessage();
            return;
        }

        Lexer lexer(tokenizer.iterator());
        if (!lexer.valid()) {
            _valid = false;
            _errorMessage = lexer.errorMessage();
            return;
        }

        stack<double> operands;
        stack<Operator> operators;

        auto it = tokenizer.iterator();
        while (it.valid()) {
            auto& token = it.value();
            if (token.type() == OPERAND) {
                auto t = static_cast<const Operand&>(token);
                operands.push((double)t.value());
                it.next();
                continue;
            }

            auto t = static_cast<const Operator&>(token);
            if (operators.empty()) {
                operators.push(t);
                it.next();
                continue;
            }

            if (operators.top().priority() <= t.priority()) {
                operators.push(t);
                it.next();
                continue;
            }


            while (operators.top().priority() > t.priority()) {
                Operator op = operators.top();
                operators.pop();

                double b = operands.top(); operands.pop();
                double a = operands.top(); operands.pop();

                try {
                    operands.push(op(a, b));
                } catch (const string& e) {
                    _errorMessage = e;
                    _valid = false;
                    return;
                }
            }

            operators.push(t);
            it.next();
        }

        while (!operators.empty()) {
            Operator op = operators.top();
            operators.pop();
            double b = operands.top(); operands.pop();
            double a = operands.top(); operands.pop();
            operands.push(op(a, b));
        }

        _result = operands.top();
        operands.pop();
        assert (operands.empty());
    }

    bool valid() const { return _valid; }

    const string& errorMessage() const { return _errorMessage; }

    double result() const { return _result; }
};

TEST_CASE("16-26", "[16-26]") {
    SECTION("Tokenizer success") {
        Tokenizer tokenizer("21 + 3 * 15 - 23");
        REQUIRE(tokenizer.valid());
        for (auto it = tokenizer.iterator(); it.valid(); it.next()) {
            cout << it.value() << " ";
        }
        cout << endl;
    }

    SECTION("Tokenizer failure") {
        Tokenizer tokenizer("21 + 3 #* 15 - 23");
        REQUIRE(tokenizer.valid() == false);
        cout << tokenizer.errorMessage() << endl;
    }

    SECTION("Lexer success") {
        Tokenizer tokenizer("21 + 3 * 15 - 23");
        REQUIRE(tokenizer.valid());

        Lexer lexer(tokenizer.iterator());
        REQUIRE(lexer.valid());
    }

    SECTION("Lexer failure") {
        Tokenizer tokenizer("21 + 3 /* 15 - 23");
        REQUIRE(tokenizer.valid());

        Lexer lexer(tokenizer.iterator());
        REQUIRE(lexer.valid() == false);
        cout << lexer.errorMessage() << endl;
    }

    SECTION("Calculator") {
        Calculator calculator("21 + 3 * 15 - 23");
        if (!calculator.valid()) {
            cout << calculator.errorMessage();
        } else {
            cout << "result = " <<  calculator.result() << endl;
        }
    }

    SECTION("Calculator") {
        Calculator calculator("21 + 3 * 15 / 0 - 23");
        if (!calculator.valid()) {
            cout << calculator.errorMessage();
        } else {
            cout << "result = " <<  calculator.result() << endl;
        }
    }
}

} // namespace ex_16_26