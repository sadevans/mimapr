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
    float delta_t = 0.0001;

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


        for (int i=0; i<c_count; i++) insert_condensator_matrix(el_cond[i], i);
        for (int i=0; i<l_count; i++) insert_katushka_matrix(el_katush[i], i);
        for (int i=0; i<r_count; i++) insert_resistor_matrix(el_resist[i], i);
        for (int i=0; i<e_count; i++) insert_eds_matrix(el_eds[i], i);
        for (int i=0; i<i_count; i++) insert_i_matrix(el_i[i], i);
    };

    void get_matrix(){
        for (int i=0; i<dimension; i++){
            for (int j=0; j<dimension; j++){
                cout << J[i][j] << " ";
            }
            cout << endl;
        }
    };


    void insert_condensator_matrix(Element condensator, int i){
        J[i][i] += 1;
        J[i][offset_u + i] -= 1/delta_t;
        J[offset_u + i][offset_u + i] += 1;
        int start = condensator.getStartNode();
        int finish = condensator.getEndNode();
        if (start != 0){
            J[offset_u + i][offset_n + start - 1] -= 1;
            J[offset_n + start - 1][i] += condensator.getValue();
        }
        if (finish != 0){
            J[offset_u + i][offset_n + finish - 1] += 1;
            J[offset_n + finish - 1][i] -= condensator.getValue();
        }            
    };


    void insert_katushka_matrix(Element katushka, int i){
        int start = katushka.getStartNode();
        int end = katushka.getEndNode();


        J[offset_di + i][offset_di + i] += 1;
        J[offset_di + i][offset_i + i] += (-1/delta_t);
        J[offset_i + i][offset_di + i] += katushka.getValue();

        if (start != 0) {
            J[offset_i + i][offset_n + start - 1] -= 1;
            J[offset_n + start - 1][offset_i + i] += 1;
        }
        if (end != 0) {
            J[offset_i + i][offset_n + end - 1] += 1;
            J[offset_n + end - 1][offset_i + i] -= 1;
        }
    };


    void insert_resistor_matrix(Element resistor, int i){
        
    };


    void insert_eds_matrix(Element eds, int i){
        int start = eds.getStartNode();
        int end = eds.getEndNode();
        if (start != 0) {
            J[offset_n + start - 1][offset_e] += 1;
            J[offset_e][offset_n + start - 1] += 1;
        }
        if (end != 0) {
            J[offset_n + end - 1][offset_e] -= 1;
            J[offset_e][offset_n + end - 1] -= 1;
        }
    };


    void insert_i_vector(Element el_i, int i){

    };



};
