#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Element.h"
using namespace std;

// check if works
int main() {
    vector<Element> elements;

    cout << "Enter elements one by one with their characteristics: start node, end node, value, name." << endl;
    cout << "Or 'exit' to finish input." << endl;

    while (true) {
        string input;
        ElementType elementType;
        int startNode, endNode;
        float value;
        string name;
        bool isSin;

        cout << "Enter element type (E, C, R, L, I): ";
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

        cout << "Enter start node: ";
        cin >> startNode;
        cin.ignore();

        cout << "Enter end node: ";
        cin >> endNode;
        cin.ignore();

        cout << "Enter value: ";
        cin >> value;
        cin.ignore();

        cout << "Enter element name: ";
        getline(cin, name);

        Element element(elementType, startNode, endNode, value, name, isSin);
        elements.push_back(element); // запись в вектор всех элементов
    }

    for (const auto& elem : elements) {
        cout << "\nElement Type: " << static_cast<int>(elem.getType()) << endl;
        cout << "Start Node: " << elem.getStartNode() << endl;
        cout << "End Node: " << elem.getEndNode() << endl;
        cout << "Value: " << elem.getValue() << endl;
        cout << "Name: " << elem.getName() << endl;
    }

    return 0;
}