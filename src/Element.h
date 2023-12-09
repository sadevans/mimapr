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
    double value;
    std::string name;
    bool isSin;
    double It;
    double m_phit;

public:
    Element(ElementType elementType, int start, int end, double val, const std::string& elemName, bool isSinelem=false, 
    double It_ = 1e-12, double m_phit_ = 0.026)
        : type(elementType), startNode(start), endNode(end), value(val), name(elemName), isSin(isSinelem), It(It_), m_phit(m_phit_) {}

    
    ElementType getType() const {
        return type;
    };


    int getStartNode() const {
        return startNode;
    };

    bool getIsSin() const {
        return isSin;
    };


    int getEndNode() const {
        return endNode;
    };


    double getValue() const {
        return value;
    };


    std::string getName() const {
        return name;
    };

    double getIt() const {
        return It;
    };

    double getMphit() const {
        return m_phit;
    };

};