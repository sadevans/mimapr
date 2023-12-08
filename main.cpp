#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>
#include "Solver.h"
using namespace std;



int main() {

    Schema* schema = new Schema();
    // Element* c1 = new Element(ElementType::E, 0, 1, 10, "E1");
    // Element* c2 = new Element(ElementType::E, 0, 2, 10, "E2");
    // Element* c3 = new Element(ElementType::E, 0, 1, 10, "E3");
    // Element* c1 = new Element(ElementType::C, 1, 2, 1e-6, "c1", false);
    Element* e1 = new Element(ElementType::E, 1, 0, 1, "E1", true);
    // Element* r1 = new Element(ElementType::R, 1, 2, 1000, "R1", false);
    // Element* c1 = new Element(ElementType::C, 1, 2, 1e-6, "C1", false);
    // Element* e1 = new Element(ElementType::E, 1, 0, 1, "E1", true);
    Element* r1 = new Element(ElementType::R, 1, 2, 1000, "R1", false);
    Element* l1 = new Element(ElementType::L, 2, 0, 0.001, "L1", false);

    //Element* cb = new Element(ElementType::C, 2, 3, 2e-12, "Cb", false);
    //Element* ru = new Element(ElementType::R, 2, 3, 1000000, "Ru", false);
    //Element* id = new Element(ElementType::Id, 2, 3, 0, "Id", false); 
    
    // Element* rb = new Element(ElementType::R, 2, 3, 20, "Rb", false);

    // Element* c2 = new Element(ElementType::C, 3, 4, 1, "C2", false);
    // Element* r2 = new Element(ElementType::R, 4, 0, 1000, "R2", false);
    // Element* l2 = new Element(ElementType::L, 4, 0, 0.001, "L2", false);    
    


    schema->add_element(*e1);
    schema->add_element(*l1);
    // schema->add_element(*r1);
    schema->add_element(*r1);

    //schema->add_element(*cb);
    //schema->add_element(*ru);
    //schema->add_element(*id);

    // schema->add_element(*rb);

    // schema->add_element(*c2);
    // schema->add_element(*r2);
    // schema->add_element(*l2);
    // Element* e1 = new Element(ElementType::E, 1, 0, 10, "E1", true);
    // Element* c1 = new Element(ElementType::C, 1, 3, 5, "C1", false);
    // Element* r1 = new Element(ElementType::R, 0, 2, 2, "R1", false);
    // Element* r2 = new Element(ElementType::R, 2, 3, 2, "R2", false);
    // Element* c2 = new Element(ElementType::C, 2, 3, 5, "C2", false);
    // Element* i1 = new Element(ElementType::Id, 2, 3, 12, "I1", false);

    // Element* r3 = new Element(ElementType::R, 3, 4, 2, "R3", false);
    // Element* r4 = new Element(ElementType::R, 4, 5, 2, "R4", false);
    // Element* c3 = new Element(ElementType::C, 4, 5, 5, "C3", false);
    // Element* i2 = new Element(ElementType::Id, 4, 5, 12, "I2", false);

    // Element* c4 = new Element(ElementType::C, 0, 5, 5, "C4", false);
    // Element* r5 = new Element(ElementType::R, 0, 5, 2, "R5", false);
    // Element* l1 = new Element(ElementType::L, 0, 5, 0.2, "L1", false);

    // // my schema
    // schema->add_element(*e1);
    // schema->add_element(*c1);
    // schema->add_element(*r1);
    // schema->add_element(*r2);
    // schema->add_element(*c2);
    // schema->add_element(*i1);
    // schema->add_element(*r3);
    // schema->add_element(*r4);
    // schema->add_element(*c3);
    // schema->add_element(*i2);
    // schema->add_element(*c4);
    // schema->add_element(*r5);
    // schema->add_element(*l1);

    // konovs
    // Element* e1 = new Element(ElementType::E, 1, 0, 10, "E1", true);
    // Element* r1 = new Element(ElementType::R, 1, 2, 1000, "R1", false);
    // Element* e2 = new Element(ElementType::E, 3, 0, 5, "E2", false);
    // Element* c1 = new Element(ElementType::C, 5, 0, 1, "C1", false);
    // Element* l1 = new Element(ElementType::L, 2, 5, 0.1, "L1", false);
    // Element* r2 = new Element(ElementType::R, 2, 5, 10000, "R2", false);
    // Element* r3 = new Element(ElementType::R, 5, 0, 1000, "R3", false);
    // Element* r4 = new Element(ElementType::R, 2, 6, 20, "R4", false);
    // Element* r5 = new Element(ElementType::R, 6, 3, 1000000, "R5", false);

    // Element* c2 = new Element(ElementType::C, 6, 3, 2, "C2", false);
    // Element* id1 = new Element(ElementType::Id, 6, 3, 2, "Id1", false);
    // Element* e3 = new Element(ElementType::E, 0, 4, 5, "E3", false);
    
    // Element* c3 = new Element(ElementType::C, 7, 2, 2, "C3", false);
    // Element* r6 = new Element(ElementType::R, 7, 2, 1000000, "R6", false);
    // Element* id2 = new Element(ElementType::Id, 7, 2, 2, "Id2", false);

    // Element* r7 = new Element(ElementType::R, 4, 7, 20, "R7", false);

    // schema->add_element(*e1);
    // schema->add_element(*r1);
    // schema->add_element(*e2);
    // schema->add_element(*c1);
    // schema->add_element(*l1);
    // schema->add_element(*r2);
    // schema->add_element(*r3);
    // schema->add_element(*r4);
    // schema->add_element(*r5);
    // schema->add_element(*c2);
    // schema->add_element(*id1);
    // schema->add_element(*e3);
    // schema->add_element(*c3);
    // schema->add_element(*r6);
    // schema->add_element(*id2);
    // schema->add_element(*r7);

    // schema->init_dx();

    // schema->init_matrix_vector(0);
    // cout << 'hi'<<endl;
    // schema->print_matrix();
    // cout << schema->get_dimension() << endl;
    // return 0;
    




















    // schema->get_elements();

    // cout << schema->getNCount() << endl;
    // schema->getCounts();

    // schema->init_matrix_vector();
    // cout << schema->get_dimension() << endl;
    // schema->print_matrix();
    // cout << endl;
    // schema->print_vector();
    
    Solver* solver = new Solver(schema);
    FILE * f1 = fopen("out.txt", "w");
    solver->point_method(f1);
    fclose(f1);
    return 0;
}