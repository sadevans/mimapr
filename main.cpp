#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Schema.h"


int main(int argc, char* argv[]){
    Schema* _schema = new Schema(0.001);
    Element* c1 = new Element(ElementType::C, 0, 1, 100, "C1");
    Element* c2 = new Element(ElementType::C, 0, 1, 100, "C2");
    Element* c3 = new Element(ElementType::C, 0, 1, 100, "C3");

    _schema->add_element(*c1);
    _schema->add_element(*c2);
    _schema->add_element(*c3);
    //_schema->get_elements();
    _schema->init_matrix_and_vector();
    _schema->print_matrix();
    return 0;

}