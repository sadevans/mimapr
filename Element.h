#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

enum class ElementType { E, C, R, L, I, Id };

class Element {
private:
    ElementType type;
    int startNode;
    int endNode;
    float value;
    std::string name;
    bool isSin;

public:
    Element(ElementType elementType, int start, int end, double val, const std::string& elemName, bool isSinelem)
        : type(elementType), startNode(start), endNode(end), value(val), name(elemName), isSin(isSinelem) {}

    ElementType getType() const {
        return type;
    }


    int getStartNode() const {
        return startNode;
    }

    bool getIsSin() const {
        return isSin;
    }


    int getEndNode() const {
        return endNode;
    }


    double getValue() const {
        return value;
    }


    std::string getName() const {
        return name;
    }

};