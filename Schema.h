#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Element.h"
using namespace std;


class Schema {
private:
    vector<Element> elements;
    vector<Element> el_cond;
    vector<Element> el_katush;
    vector<Element> el_resist;
    vector<Element> el_eds;
    vector<Element> el_i;



    int c_count; // for dim
    int l_count; // for dim
    int n_count; // for dim
    int e_count; // for dim
    int r_count;
    int i_count;

    int offset_du;
    int offset_di;
    int offset_u;
    int offset_i;
    int offset_n;
    int offset_e;

    int l_count; // for dim
    int n_count; // for dim
    int e_count; // for dim
    int r_count;
    int i_count;

    int dimension;

    int all_count;

    vector<float> I;
    vector<vector<float>> J;
    vector<float> phi;
    vector<float> phi_prev;
    
public:
    Schema(){};

    void add_element(Element elem){
        elements.push_back(elem);

        if (elem.getType() == ElementType::C) {el_cond.push_back(elem); c_count += 1;}
        if (elem.getType() == ElementType::L) {el_katush.push_back(elem); l_count += 1;}
        if (elem.getType() == ElementType::R) {el_resist.push_back(elem); r_count += 1;}
        if (elem.getType() == ElementType::E) {el_eds.push_back(elem); e_count += 1;}
        if (elem.getType() == ElementType::I) {el_i.push_back(elem); i_count += 1;}


        // if (elem.getType() == ElementType::C) c_count += 1;
        // if (elem.getType() == ElementType::L) l_count += 1;
        // if (elem.getType() == ElementType::R) r_count += 1;
        // if (elem.getType() == ElementType::E) e_count += 1;
        // if (elem.getType() == ElementType::I) i_count += 1;

        if (elem.getStartNode() > n_count)
            n_count = elem.getStartNode();
        if (elem.getEndNode() > n_count)
            n_count = elem.getEndNode();
        all_count += 1;

    };


    void get_elements(){
        for (const auto& elem : elements) {
        cout << "\nElement Type: " << static_cast<int>(elem.getType()) << endl;
        cout << "Start Node: " << elem.getStartNode() << endl;
        cout << "End Node: " << elem.getEndNode() << endl;
        cout << "Value: " << elem.getValue() << endl;
        cout << "Name: " << elem.getName() << endl;
        }
    };

    int getNCount() const {
        return n_count;
    }

    int get_dimencion() const {
        return 2*c_count + 2*l_count + n_count + e_count;
    }

    void init_matrix_vector(){
        dimension = 2*c_count + 2*l_count + n_count + e_count;

        for (int i=0; i<dimension; i++){
            vector<float> temp;
            for (int j=0; j<dimension; j++)
                temp.push_back(0);
            J.push_back(temp);
            I.push_back(0);
        }

        offset_du = 0;
        offset_di = c_count;
        offset_u = c_count + l_count;
        offset_i= 2*c_count + l_count;
        offset_n = 2*(c_count + l_count);
        offset_e = 2*(c_count + l_count) + n_count;
    };

    void get_matrix(){
        for (int i=0; i<dimension; i++){
            for (int j=0; j<dimension; j++){
                cout << J[i][j] << " ";
            }
            cout << endl;
        }
    };

    void insert_condens(Element condensator){
        
    };

    void insert_katushka(Element katushka){};

    void insert_resistor(Element resistor){};

    void insert_eds(Element eds){};

    void inster_i(Element i){};



};
