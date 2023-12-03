#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Element.h"
using namespace std;


class Schema {
private:
    vector<Element> elements;
    int c_count; // for dim
    int l_count; // for dim
    int n_count; // for dim
    int e_count; // for dim
    int r_count;
    int i_count;

    int dimension;

    int all_count;

    vector<float> b;
    vector<vector<float>> A;
    vector<float> phi;
    vector<float> phi_prev;
    
public:
    Schema(){};

    void add_element(Element elem){
        elements.push_back(elem);
        if (elem.getType() == ElementType::C) c_count += 1;
        if (elem.getType() == ElementType::L) l_count += 1;
        if (elem.getType() == ElementType::R) r_count += 1;
        if (elem.getType() == ElementType::E) e_count += 1;
        if (elem.getType() == ElementType::I) i_count += 1;

        if (elem.getStartNode() > n_count)
            n_count = elem.getStartNode();
        if (elem.getEndNode() > n_count)
            n_count = elem.getEndNode();
        all_count += 1;

    };


    void get_elements(){
        for (const auto& elem : elements) {
        std::cout << "\nElement Type: " << static_cast<int>(elem.getType()) << std::endl;
        std::cout << "Start Node: " << elem.getStartNode() << std::endl;
        std::cout << "End Node: " << elem.getEndNode() << std::endl;
        std::cout << "Value: " << elem.getValue() << std::endl;
        std::cout << "Name: " << elem.getName() << std::endl;
        }
    };

    int getNCount() const {
        return n_count;
    }

    void init_matrix_vector(){


    };

    void init_phi(){

    };

    void reset_phi(){

    };

    void reset_vector(){

    };

    void init_vector(){
        return;
    };

};
