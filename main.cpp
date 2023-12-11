#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>
#include "Solver.h"
using namespace std;


int main() {

    Schema* schema = new Schema();

    schema->add_element(Element(ElementType::E, 1, 0, 10, "E1", true));

    schema->add_element(Element(ElementType::R, 1, 2, 1000, "R1", false));
    schema->add_element(Element(ElementType::C, 1, 2, 1e-6, "C1", false));
    schema->add_element(Element(ElementType::L, 1, 2, 0.001, "L1", false));

    schema->add_element(Element(ElementType::R, 2, 3, 1000000, "Ru", false));
    schema->add_element(Element(ElementType::R, 3, 4, 20, "Rb", false));
    schema->add_element(Element(ElementType::C, 2, 3, 2e-12, "CB", false));
    schema->add_element(Element(ElementType::Id, 3, 2, 2, "Id1", false));

    schema->add_element(Element(ElementType::C, 4, 5, 1e-6, "C2", false));
    schema->add_element(Element(ElementType::R, 5, 0, 1000, "R1", false));
    
    schema->add_element(Element(ElementType::L, 5, 0, 0.001, "L1", false));

    Solver* solver = new Solver(schema);
    FILE * f1 = fopen("out.txt", "w");

    solver->point_method(f1);
    fclose(f1);
    return 0;
}