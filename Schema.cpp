#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Schema.h"
using namespace std;


int main() {

    Schema* schema = new Schema();
    // Element* c1 = new Element(ElementType::E, 0, 1, 10, "E1");
    // Element* c2 = new Element(ElementType::E, 0, 2, 10, "E2");
    // Element* c3 = new Element(ElementType::E, 0, 1, 10, "E3");

    Element* e1 = new Element(ElementType::E, 1, 0, 10, "E1", true);
    Element* c1 = new Element(ElementType::C, 1, 3, 5, "C1", false);
    Element* r1 = new Element(ElementType::R, 0, 2, 2, "R1", false);
    Element* r2 = new Element(ElementType::R, 2, 3, 2, "R2", false);
    Element* c2 = new Element(ElementType::C, 2, 3, 5, "C2", false);
    Element* i1 = new Element(ElementType::Id, 2, 3, 12, "I1", false);

    Element* r3 = new Element(ElementType::R, 3, 4, 2, "R3", false);
    Element* r4 = new Element(ElementType::R, 4, 5, 2, "R4", false);
    Element* c3 = new Element(ElementType::C, 4, 5, 5, "C3", false);
    Element* i2 = new Element(ElementType::Id, 4, 5, 12, "I2", false);

    Element* c4 = new Element(ElementType::C, 0, 5, 5, "C4", false);
    Element* r5 = new Element(ElementType::R, 0, 5, 2, "R5", false);
    Element* l1 = new Element(ElementType::L, 0, 5, 0.2, "L1", false);

    // my schema
    schema->add_element(*e1);
    schema->add_element(*c1);
    schema->add_element(*r1);
    schema->add_element(*r2);
    schema->add_element(*c2);
    schema->add_element(*i1);
    schema->add_element(*r3);
    schema->add_element(*r4);
    schema->add_element(*c3);
    schema->add_element(*i2);
    schema->add_element(*c4);
    schema->add_element(*r5);
    schema->add_element(*l1);

    schema->get_elements();

    cout << schema->getNCount() << endl;
    schema->getCounts();

    schema->init_dx();
    schema->init_matrix_vector(0);
    cout << schema->get_dimension() << endl;
    schema->print_matrix();
    cout << endl;
    schema->print_vector();

    return 0;
}
