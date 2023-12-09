#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>
#include "Solver.h"
using namespace std;



int main() {

    Schema* schema = new Schema();

    Element* e1 = new Element(ElementType::E, 1, 0, 1, "E1", true);

    Element* r1 = new Element(ElementType::R, 1, 2, 1000, "R1", false);
    Element* c1 = new Element(ElementType::C, 1, 2, 1e-6, "C1", false);
    Element* l1 = new Element(ElementType::L, 1, 2, 0.001, "L1", false);

    Element* cb = new Element(ElementType::C, 2, 3, 2e-12, "CB", false);
    Element* ru = new Element(ElementType::R, 2, 3, 1000000, "Ru", false);
    Element* id = new Element(ElementType::Id, 3, 2, 2, "Id1", false);

    Element* rb = new Element(ElementType::R, 3, 4, 20, "Rb", false);

    Element* c2 = new Element(ElementType::C, 4, 5, 1e-6, "C2", false); 

    Element* r2 = new Element(ElementType::R, 5, 0, 1000, "R1", false);
    Element* l2 = new Element(ElementType::L, 5, 0, 0.001, "L1", false);


    schema->add_element(*e1);

    schema->add_element(*r1);
    schema->add_element(*c1);
    schema->add_element(*l1);

    schema->add_element(*ru);
    schema->add_element(*rb);
    schema->add_element(*cb);
    schema->add_element(*id);

    schema->add_element(*c2);
    schema->add_element(*r2);
    
    schema->add_element(*l2);

    
    Solver* solver = new Solver(schema);
    FILE * f1 = fopen("out.txt", "w");
    solver->point_method(f1);
    fclose(f1);
    return 0;
}