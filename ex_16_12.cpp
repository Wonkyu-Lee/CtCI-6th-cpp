//
// Created by blazeq on 2017. 11. 30..
//

#include <iostream>
#include <list>
#include <unordered_map>
#include "catch.hpp"

namespace ex_16_12 {

using namespace std;

enum { END = 0 };

unordered_map<string, int> WORD_MAP = {
        {"family", 1},
        {"person", 2},
        {"firstName", 3},
        {"lastName", 4},
        {"state", 5},
};

struct Attribute;
struct Element;
using AttributePtr = shared_ptr<Attribute>;
using ElementPtr = shared_ptr<Element>;

struct Attribute {
    string tag;
    string value;
    Attribute() = default;
    Attribute(const string& tag, const string& value): tag(tag), value(value) {}

    friend ostream& operator<<(ostream& out, const Attribute& attr) {
        out << WORD_MAP[attr.tag] << " " << attr.value;
        return out;
    }
};

struct Element {
    string tag;
    string value;
    list<ElementPtr> children;
    list<AttributePtr> attributes;
    Element() = default;
    Element(const string& tag): tag(tag) {}

    void setAttribute(const string& tag, const string& value) {
        attributes.push_back(make_shared<Attribute>(tag, value));
    }

    void setValue(const string& value) {
        this->value = value;
    }

    void addChild(ElementPtr element) {
        children.push_back(element);
    }

    friend ostream& operator<<(ostream& out, const Element& element) {
        out << WORD_MAP[element.tag] << " ";
        for (auto each : element.attributes) {
            out << *each << " ";
        }
        out << END << " ";
        for (auto each : element.children) {
            out << *each << " ";
        }

        if (!element.value.empty())
            out << element.value << " ";

        out << END << " ";
        return out;
    }
};

string encodingXml(const Element& element) {
    ostringstream out;
    out << element;
    return out.str();
}

TEST_CASE("16-12", "[16-12]") {
    ElementPtr family = make_shared<Element>("family");
    family->setAttribute("lastName", "McDowell");
    family->setAttribute("state", "CA");

    ElementPtr person = make_shared<Element>("person");
    person->setAttribute("firstName", "Gale");
    person->setValue("Some Message");
    family->addChild(person);

    string encoded = encodingXml(*family);
    cout << encoded << endl;
}

} // namespace ex_16_12