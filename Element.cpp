#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

enum class ElementType { E, C, R, L, I };

class Element {
private:
    ElementType type;
    int startNode;
    int endNode;
    double value;
    std::string name;

public:
    Element(ElementType elementType, int start, int end, double val, const std::string& elemName)
        : type(elementType), startNode(start), endNode(end), value(val), name(elemName) {}

    ElementType getType() const {
        return type;
    }


    int getStartNode() const {
        return startNode;
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

int main() {
    vector<Element> elements;

    std::cout << "Enter elements one by one with their characteristics: start node, end node, value, name." << std::endl;
    std::cout << "Or 'exit' to finish input." << std::endl;

    while (true) {
        string input;
        ElementType elementType;
        int startNode, endNode;
        double value;
        string name;

        std::cout << "Enter element type (E, C, R, L, I): ";
        getline(cin, input);
        if (input == "exit") break;
        if (input == "E") elementType = ElementType::E;
        else if (input == "C") elementType = ElementType::C;
        else if (input == "R") elementType = ElementType::R;
        else if (input == "L") elementType = ElementType::L;
        else if (input == "I") elementType = ElementType::I;
        else {
            cout << "Invalid Element type!" << endl;
            continue;
        }

        std::cout << "Enter start node: ";
        cin >> startNode;
        cin.ignore();

        std::cout << "Enter end node: ";
        cin >> endNode;
        cin.ignore();

        std::cout << "Enter value: ";
        cin >> value;
        cin.ignore();

        std::cout << "Enter element name: ";
        getline(cin, name);

        Element element(elementType, startNode, endNode, value, name);
        elements.push_back(element); // запись в вектор всех элементов
    }

    for (const auto& elem : elements) {
        std::cout << "\nElement Type: " << static_cast<int>(elem.getType()) << std::endl;
        std::cout << "Start Node: " << elem.getStartNode() << std::endl;
        std::cout << "End Node: " << elem.getEndNode() << std::endl;
        std::cout << "Value: " << elem.getValue() << std::endl;
        std::cout << "Name: " << elem.getName() << std::endl;
    }

    return 0;
}
