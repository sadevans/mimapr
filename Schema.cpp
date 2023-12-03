#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Schema.h"
using namespace std;


int main() {

    Schema* schema = new Schema();
    Element* c1 = new Element(ElementType::E, 0, 1, 10, "E1");
    Element* c2 = new Element(ElementType::E, 0, 2, 10, "E2");
    Element* c3 = new Element(ElementType::E, 0, 1, 10, "E3");


    schema->add_element(*c1);
    schema->add_element(*c2);
    schema->add_element(*c3);

    schema->get_elements();

    cout << schema->getNCount() << endl;

    return 0;
}
