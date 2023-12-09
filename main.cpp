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

    Element* c1 = new Element(ElementType::C, 1, 3, 1e-6, "C1");
    Element* rb1 = new Element(ElementType::R, 0, 2, 20, "Rb1");
    Element* ru1 = new Element(ElementType::R, 2, 3, 1e6, "Ru1");
    Element* cb1 = new Element(ElementType::C, 2, 3, 2e-12, "Cb1");
    Element* id1 = new Element(ElementType::Id, 2, 3, 1, "Id1");

    Element* rb2 = new Element(ElementType::R, 3, 4, 20, "Rb2");
    Element* ru2 = new Element(ElementType::R, 4, 5, 1e6, "Ru2");
    Element* cb2 = new Element(ElementType::C, 4, 5, 2e-12, "Cb2");
    Element* id2 = new Element(ElementType::Id, 4, 5, 1, "Id2");

    Element* c2 = new Element(ElementType::C, 0, 5, 1e-6, "C2");
    Element* r2 = new Element(ElementType::R, 0, 5, 1e3, "R2");
    Element* l1 = new Element(ElementType::L, 0, 5, 2.53e-4, "L1");

    schema->add_element(*e1);

    schema->add_element(*c1);
    schema->add_element(*rb1);
    schema->add_element(*ru1);
    schema->add_element(*cb1);
    schema->add_element(*id1);
    schema->add_element(*rb2);
    schema->add_element(*ru2);
    schema->add_element(*cb2);
    schema->add_element(*id2);
    schema->add_element(*c2);
    schema->add_element(*r2);
    schema->add_element(*l1);

    Solver* solver = new Solver(schema);
    FILE * f1 = fopen("out.txt", "w");
    solver->point_method(f1);
    fclose(f1);
    system("python plotter.py");
    return 0;
}