#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>
#include "Element.h"
using namespace std;


class Schema {
private:
    // vectors
    vector<Element> elements;
    vector<Element> el_cond;
    vector<Element> el_katush;
    vector<Element> el_resist;
    vector<Element> el_eds;
    vector<Element> el_i;
    vector<Element> el_id;


    // current values
    vector<float> dU;
    vector<float> U;
    vector<float> dIl;
    vector<float> Il;
    vector<float> Ie;
    vector<float> phi;

    // previous values
    vector<float> phi_prev;
    vector<float> Ie_prev;
    vector<float> Il_prev;
    vector<float> dIl_prev;
    vector<float> U_prev;
    vector<float> dU_prev;

    // counts
    int c_count; // impact on dimension
    int l_count; // impact on dimension
    int n_count; // impact on dimension
    int e_count; // impact on dimension
    int r_count;
    int i_count;
    int id_count;
    int all_count;

    // offsets
    int offset_du;
    int offset_di;
    int offset_u;
    int offset_i;
    int offset_n;
    int offset_e;

    // dimension of the Jacobian matrix and vectors
    int dimension;

    float delta_t = 0.0001;

    // diode parameters
    float It = 2;
    float m = 2;
    float phi_t = 1;

    vector<float> I;
    vector<vector<float>> J;
    
public:
    Schema(){};

    void add_element(Element elem){
        elements.push_back(elem);

        if (elem.getType() == ElementType::C) {el_cond.push_back(elem); c_count += 1; dU.push_back(0); dU_prev.push_back(0);
                                                    U.push_back(0); U_prev.push_back(0);}
        if (elem.getType() == ElementType::L) {el_katush.push_back(elem); l_count += 1; dIl.push_back(0); dIl_prev.push_back(0);
                                                    Il.push_back(0); Il_prev.push_back(0);}
        if (elem.getType() == ElementType::R) {el_resist.push_back(elem); r_count += 1;}
        if (elem.getType() == ElementType::E) {el_eds.push_back(elem); e_count += 1; Ie.push_back(0); Ie_prev.push_back(0);}
        if (elem.getType() == ElementType::I) {el_i.push_back(elem); i_count += 1;}
        if (elem.getType() == ElementType::Id) {el_id.push_back(elem); id_count += 1;}


        
        if (n_count == 0) {phi.push_back(0); phi_prev.push_back(0);}
        if (elem.getStartNode() > n_count){
            n_count = elem.getStartNode();
            phi.push_back(0);
            phi_prev.push_back(0);

        }
        if (elem.getEndNode() > n_count){
            n_count = elem.getEndNode();
            phi.push_back(0);
            phi_prev.push_back(0);
        }

        all_count += 1;

        dimension = 2*c_count + 2*l_count + n_count + e_count;

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
    };

    void getCounts() const {
        cout << "Count C: " << c_count << endl;
        cout << "Count L: " << l_count << endl;
        cout << "Count R: " << r_count << endl;
        cout << "Count E: " << e_count << endl;
        cout << "Count I: " << i_count << endl;
        cout << "Count Id: " << id_count << endl;

    };


    int get_dimension() const {
        return 2*c_count + 2*l_count + n_count + e_count;
    };


    void init_matrix_vector(){
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

        for (int i=0; i<c_count; i++) {insert_condensator_matrix(el_cond[i], i); insert_condensator_vector(el_cond[i], i);}
        for (int i=0; i<l_count; i++) {insert_katushka_matrix(el_katush[i], i); insert_katushka_vector(el_katush[i], i);}
        for (int i=0; i<r_count; i++) {insert_resistor_matrix(el_resist[i], i); insert_resistor_vector(el_resist[i], i);}
        for (int i=0; i<e_count; i++) {insert_eds_matrix(el_eds[i], i); insert_eds_vector(el_eds[i], i);}
        for (int i=0; i<i_count; i++) {insert_i_vector(el_i[i], i);}
        for (int i=0; i<id_count; i++) {insert_id_matrix(el_id[i], i); insert_id_vector(el_id[i], i);}

    };

    void get_matrix(){
        for (int i=0; i<dimension; i++){
            for (int j=0; j<dimension; j++){
                cout << J[i][j] << " ";
            }
            cout << endl;
        }
    };

    void get_vector(){
        for (int i=0; i<dimension; i++)
            cout << I[i] << " ";
        cout << endl;
    };

    void get_phi(){
        for (int i=0; i<phi.size(); i++)
            cout << phi[i] << " ";
        cout << endl;
    };

    void insert_condensator_matrix(Element condensator, int i){
        J[i][i] += 1;
        J[i][offset_u + i] -= 1/delta_t;
        J[offset_u + i][offset_u + i] += 1;
        int start = condensator.getStartNode();
        int end = condensator.getEndNode();
        float c = condensator.getValue();
        if (start != 0){
            J[offset_u + i][offset_n + start - 1] -= 1;
            J[offset_n + start - 1][i] += c;
        }
        if (end != 0){
            J[offset_u + i][offset_n + end - 1] += 1;
            J[offset_n + end - 1][i] -= c;
        }            
    };

    void insert_condensator_vector(Element condensator, int i){
        int start = condensator.getStartNode();
        int end = condensator.getEndNode();
        float C = condensator.getValue();
        I[i] += dU[i] - (U[i] - U_prev[i])/delta_t;
        
        if (start != 0 && end != 0){
            I[offset_u + i] += U[i] - (phi[start - 1] - phi[end - 1]);
        }
        if (start != 0 && end == 0){
            I[offset_u + i] += U[i] - (phi[start - 1]);
        }
        if (start == 0 && end != 0){
            I[offset_u + i] += U[i] - (-phi[end - 1]);
        }

        if (start != 0) {I[offset_n + start - 1] += C*dU[i];}
        if (end != 0) {I[offset_n + end - 1] -= C*dU[i];}
        
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


    void insert_katushka_vector(Element katushka, int i){
        int start = katushka.getStartNode();
        int end = katushka.getEndNode();
        float L = katushka.getValue();

        I[offset_di + i] += dIl[i] - (Il[i] - Il_prev[i])/delta_t;

        if (start != 0 && end != 0){I[offset_i + i] += L*dIl[i] - (phi[start -1] - phi[end - 1]);}
        if (start != 0 && end == 0){I[offset_i + i] += L*dIl[i] - (phi[start -1]);}
        if (start == 0 && end != 0){I[offset_i + i] += L*dIl[i] - (-phi[end - 1]);}

        if (start != 0) {I[offset_n + start - 1] += dIl[i];}
        if (end != 0) {I[offset_n + end - 1] -= dIl[i];}
    };


    void insert_resistor_matrix(Element resistor, int i){
        int start = resistor.getStartNode();
        int end = resistor.getEndNode();  
        float r = resistor.getValue();
        if (start != 0) J[offset_n + start - 1][offset_n + start - 1] += 1/r;
        if (end != 0) J[offset_n + end - 1][offset_n + end - 1] += 1/r;
        if (start != 0 && end != 0){
            J[offset_n + end - 1][offset_n + start - 1] -= 1/r;
            J[offset_n + start - 1][offset_n + end - 1] -= 1/r;
        }  

    };

    void insert_resistor_vector(Element resistor, int i){
        int start = resistor.getStartNode();
        int end = resistor.getEndNode();
        float R = resistor.getValue();
        
        
        if (start != 0 && end != 0){
            I[offset_n + start - 1] += (phi[start - 1] - phi[end - 1])/R;
            I[offset_n + end - 1] -= (phi[start - 1] - phi[end - 1])/R;
            }
        if (start != 0 && end == 0){
            I[offset_n + start - 1] += (phi[start - 1])/R;
            // I[offset_n + end - 1] -= (phi[start - 1])/R;
            }
        if (start == 0 && end != 0){
            // I[offset_n + start - 1] -= (phi[end - 1])/R;
            I[offset_n + end - 1] += (phi[end - 1])/R;
            }
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

    void insert_eds_vector(Element eds, int i){
        int start = eds.getStartNode();
        int end = eds.getEndNode();
        float E = eds.getValue();

        if (start != 0) {
            I[offset_n + start - 1] += Ie[i];
        }
        if (end != 0) {
            I[offset_n + end - 1] -= Ie[i];
        }

        if (start != 0 && end != 0){I[offset_e] += (phi[start - 1] - phi[end - 1]) - E;}
        if (start != 0 && end == 0){I[offset_e] += phi[start - 1] - E;}
        if (start == 0 && end != 0){I[offset_e] += (-phi[end - 1]) - E;}
    };


    void insert_id_matrix(Element el_id, int i){
        int start = el_id.getStartNode();
        int end = el_id.getEndNode();

        if (start != 0) {J[offset_n + start - 1][offset_n + start - 1] += (It*exp(phi[start-1] - phi[end -1]))/(m*phi_t);}
        if (end != 0) {J[offset_n + end - 1][offset_n + end - 1] += (It*exp(phi[start-1] - phi[end -1]))/(m*phi_t);}
        if (start != 0 && end != 0){
            J[offset_n + end - 1][offset_n + start - 1] -= (It*exp(phi[start-1] - phi[end -1]))/(m*phi_t);
            J[offset_n + start - 1][offset_n + end - 1] -= (It*exp(phi[start-1] - phi[end -1]))/(m*phi_t);
        } 
    };

    void insert_id_vector(Element el_id, int i){
        int start = el_id.getStartNode();
        int end = el_id.getEndNode();
        // float E = eds.getValue();
        if (start != 0 && end != 0){
            I[offset_n + start - 1] += (It*(exp((phi[start-1] - phi[end -1])/(m*phi_t)) - 1));
            I[offset_n + end - 1] -= (It*(exp((phi[start-1] - phi[end -1])/(m*phi_t)) - 1));

            }
        if (start != 0 && end == 0){I[offset_n + start - 1] += (It*(exp((phi[start-1])/(m*phi_t)) - 1));}
        if (start == 0 && end != 0){I[offset_n + end - 1] -= (It*(exp((phi[start-1] - phi[end -1])/(m*phi_t)) - 1));}
    };

    void insert_i_vector(Element el_i, int i){
        int start = el_i.getStartNode();
        int end = el_i.getEndNode();
        float val = el_i.getValue();

        if (start != 0) {I[offset_n + start - 1] += val;}
        if (end != 0) {I[offset_n + end - 1] -= val;}
    };

};
