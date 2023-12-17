#include <iostream>
#include <iomanip>
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

    double delta_t = 0.0000001;
    double prev_delta_t = 0.0000001;
    // diode parameters
    double It = 1e-12;
    double m_phit = 0.026;

    vector<double> I;
    vector<vector<double>> J;
    vector<double> dx;
    vector<double> dx_prev;
    vector<double> extra_phi;
    
public:
    Schema(){};

    void add_element(Element elem){
        elements.push_back(elem);

        if (elem.getType() == ElementType::C) {el_cond.push_back(elem); c_count += 1;}
        if (elem.getType() == ElementType::L) {el_katush.push_back(elem); l_count += 1;}
        if (elem.getType() == ElementType::R) {el_resist.push_back(elem); r_count += 1;}
        if (elem.getType() == ElementType::E) {el_eds.push_back(elem); e_count += 1;}
        if (elem.getType() == ElementType::I) {el_i.push_back(elem); i_count += 1;}
        if (elem.getType() == ElementType::Id) {el_id.push_back(elem); id_count += 1;}


        
        if (elem.getStartNode() > n_count){
            n_count = elem.getStartNode();
        }

        if (elem.getEndNode() > n_count){
            n_count = elem.getEndNode();
        }

        all_count += 1;

        dimension = 2*c_count + 2*l_count + n_count + e_count;

    };


    void init_dx(){
        for (int i = 0; i < dimension; i++){
            dx.push_back(0);
            dx_prev.push_back(0);
        }
        for (int i = 0; i < n_count; i++)
            extra_phi.push_back(0);
    }


    double E_sin(double A, double t) { 
        double freq = 2 * M_PI / (1e-4);
        return A * sin(freq * t);
    }

    void get_elements(){
        for (const auto& elem : elements) {
            cout << "\nElement Type: " << static_cast<int>(elem.getType()) << endl;
            cout << "Start Node: " << elem.getStartNode() << endl;
            cout << "End Node: " << elem.getEndNode() << endl;
            cout << "Value: " << elem.getValue() << endl;
            cout << "Name: " << elem.getName() << endl;
        }
        cout << endl;
    };

    int get_n_offset() {
        return offset_n;
    }
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
        cout << endl;
    };


    int get_dimension() const {
        return 2*c_count + 2*l_count + n_count + e_count;
    };


    void reset_matrix_vector(){
        for (int i = 0; i < dimension; i++){
            for (int j = 0; j < dimension; j++){
                J[i][j] = 0;
            }
            I[i] = 0;
        }
    };

    void init_matrix_vector(double time){
        if (J.size() == 0 && I.size() == 0){
            for (int i = 0; i < dimension; i++){
                vector<double> temp;
                for (int j = 0; j < dimension; j++)
                    temp.push_back(0);
                J.push_back(temp);
                I.push_back(0);
            }
        }
        else reset_matrix_vector();


        offset_du = 0;
        offset_di = c_count;
        offset_u = c_count + l_count;
        offset_i= 2*c_count + l_count;
        offset_n = 2*(c_count + l_count);
        offset_e = 2*(c_count + l_count) + n_count;

        for (int i=0; i<c_count;  i++) {insert_condensator_matrix(el_cond[i], i); insert_condensator_vector(el_cond[i], i);}
        for (int i=0; i<l_count;  i++) {insert_katushka_matrix(el_katush[i], i); insert_katushka_vector(el_katush[i], i);}
        for (int i=0; i<r_count;  i++) {insert_resistor_matrix(el_resist[i], i); insert_resistor_vector(el_resist[i], i);}
        for (int i=0; i<e_count;  i++) {insert_eds_matrix(el_eds[i], i); insert_eds_vector(el_eds[i], i, time);}
        for (int i=0; i<i_count;  i++) {insert_i_vector(el_i[i], i);} // ordinary I
        for (int i=0; i<id_count; i++) {insert_id_matrix(el_id[i], i); insert_id_vector(el_id[i], i);} // diode I

        minus_vector();
    };

    void minus_vector() {
        for (int i = 0; i < dimension; i++) {
            I[i] *= -1;
        }
    };

    void print_matrix(){
        cout << "Jacobian matrix:" << endl;
        for (int i=0; i<dimension; i++){
            for (int j=0; j<dimension; j++){
                cout << setprecision(12)<<setw(6) << J[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    };

    void print_vector(){
        cout << "vector ";
        for (int i=0; i<dimension; i++)
            cout <<setw(6)<< I[i] << " ";
        cout << endl;
        cout << endl;

    };

    void print_dx(){
        for (int i=0; i<dimension; i++)
            cout << dx[i] << " ";
        cout << endl;
    };


    vector<vector<double>> get_matrix(){
        return J;
    };


    vector<double> get_vector(){
        return I;
    };


    void change_dx_vector(vector <double> new_dx){
        for (int i=0; i<dimension;i++){
            dx[i] += new_dx[i];
        }
    };


    void change_dx_prev_vector(){
        for (int i = 0; i < n_count; i++)
            extra_phi[i] = dx_prev[offset_n + i];
        for (int i = 0; i < dimension; i++)
            dx_prev[i] = dx[i];
    };

    double get_dx_elem(int i){
        return dx[i];
    }

    void increase_delta_t(){
        delta_t *= 2;
    };


    void decrease_delta_t(){
        delta_t /= 2;
    };


    void revert_dx(){
        for (int i = 0; i < dimension; i++)
            dx[i] = dx_prev[i];
    };


    double get_delta_t(){
        return delta_t;
    };


    vector<double> get_deviation(){
        vector<double> res;
        for (int node = 0; node < n_count; node++){
            double temp = 0.5 * delta_t * delta_t * abs((dx[offset_n + node] - dx_prev[offset_n + node])/delta_t - 
                                            (dx_prev[offset_n + node] - extra_phi[node])/prev_delta_t);
            //double temp = abs((dx[offset_n + node] - dx_prev[offset_n + node]))/delta_t; 
            //                 
            res.push_back(temp);
        }
        return res;
    }


    void insert_condensator_matrix(Element condensator, int i){
        J[i][i] += 1;
        J[i][offset_u + i] -= 1/delta_t;
        J[offset_u + i][offset_u + i] += 1;
        int start = condensator.getStartNode();
        int end = condensator.getEndNode();
        double c = condensator.getValue();
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
        double C = condensator.getValue();
        I[i] += dx[offset_du + i] - (dx[offset_u + i] - dx_prev[offset_u + i])/delta_t;

        if (start != 0 && end != 0){
            I[offset_u + i] += dx[offset_u + i] - (dx[offset_n + start - 1] - dx[offset_n + end - 1]);
        }
        if (start != 0 && end == 0){
            I[offset_u + i] += dx[offset_u + i] - (dx[offset_n + start - 1]);
        }
        if (start == 0 && end != 0){
            I[offset_u + i] += dx[offset_u + i] - (-dx[offset_n + end - 1]);
        }

        if (start != 0) {I[offset_n + start - 1] += C*dx[offset_du + i];}
        if (end != 0) {I[offset_n + end - 1] -= C*dx[offset_du + i];}
        
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
        double L = katushka.getValue();

        I[offset_di + i] += dx[offset_di + i] - (dx[offset_i + i] - dx_prev[offset_i + i])/delta_t;

        if (start != 0 && end != 0){I[offset_i + i] += L*dx[offset_di + i] - (dx[offset_n + start -1] - dx[offset_n + end - 1]);}
        if (start != 0 && end == 0){I[offset_i + i] += L*dx[offset_di + i] - (dx[offset_n + start -1]);}
        if (start == 0 && end != 0){I[offset_i + i] += L*dx[offset_di + i] - (-dx[offset_n + end - 1]);}

        if (start != 0) {I[offset_n + start - 1] += dx[offset_i + i];}
        if (end != 0) {I[offset_n + end - 1] -= dx[offset_i + i];}
    };


    void insert_resistor_matrix(Element resistor, int i){
        int start = resistor.getStartNode();
        int end = resistor.getEndNode();  
        double r = resistor.getValue();
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
        double R = resistor.getValue();
        
        
        if (start != 0 && end != 0){
            I[offset_n + start - 1] += (dx[offset_n + start - 1] - dx[offset_n + end - 1])/R;
            I[offset_n + end - 1] -= (dx[offset_n + start - 1] - dx[offset_n + end - 1])/R;
            }
        if (start != 0 && end == 0){
            I[offset_n + start - 1] += (dx[offset_n + start - 1])/R;
            // I[offset_n + end - 1] -= (phi[start - 1])/R;
            }
        if (start == 0 && end != 0){
            // I[offset_n + start - 1] -= (phi[end - 1])/R;
            I[offset_n + end - 1] += (dx[offset_n + end - 1])/R;
            }
    };


    void insert_eds_matrix(Element eds, int i){
        int start = eds.getStartNode();
        int end = eds.getEndNode();
        if (start != 0) {
            J[offset_n + start - 1][offset_e + i] += 1;
            J[offset_e + i][offset_n + start - 1] += 1;
        }
        if (end != 0) {
            J[offset_n + end - 1][offset_e + i] -= 1;
            J[offset_e + i][offset_n + end - 1] -= 1;
        }
    };

    void insert_eds_vector(Element eds, int i, double time){
        int start = eds.getStartNode();
        int end = eds.getEndNode();
        double E = eds.getValue();

        if (start != 0) {
            I[offset_n + start - 1] += dx[offset_e + i];
        }
        if (end != 0) {
            I[offset_n + end - 1] -= dx[offset_e + i];
        }

        if (eds.getIsSin()){
            if (start != 0 && end != 0){I[offset_e + i] += (dx[offset_n + start - 1] - dx[offset_n + end - 1]) - E_sin(E, time);}
            if (start != 0 && end == 0){I[offset_e + i] += dx[offset_n + start - 1] - E_sin(E, time);}
            if (start == 0 && end != 0){I[offset_e + i] += (-dx[offset_n + end - 1]) - E_sin(E, time);}
        }

        else{
            if (start != 0 && end != 0){I[offset_e + i] += (dx[offset_n + start - 1] - dx[offset_n + end - 1]) - E;}
            if (start != 0 && end == 0){I[offset_e + i] += dx[offset_n + start - 1] - E;}
            if (start == 0 && end != 0){I[offset_e + i] += (-dx[offset_n + end - 1]) - E;}

        }
    };


    void insert_id_matrix(Element el_id, int i){
        int start = el_id.getStartNode();
        int end = el_id.getEndNode();

        if (start != 0) {J[offset_n + start - 1][offset_n + start - 1] += (It * exp((dx[offset_n + start-1] - dx[offset_n + end -1])/(m_phit)))/(m_phit);}
        if (end != 0) {J[offset_n + end - 1][offset_n + end - 1] += (It * exp((dx[offset_n + start-1] - dx[offset_n + end -1])/(m_phit)))/(m_phit);}
        if (start != 0 && end != 0){
            J[offset_n + end - 1][offset_n + start - 1] -= (It * exp((dx[offset_n + start-1] - dx[offset_n + end -1])/(m_phit)))/(m_phit);
            J[offset_n + start - 1][offset_n + end - 1] -= (It * exp((dx[offset_n + start-1] - dx[offset_n + end -1])/(m_phit)))/(m_phit);
        } 
    };

    void insert_id_vector(Element el_id, int i){
        int start = el_id.getStartNode();
        int end = el_id.getEndNode();
        // double E = eds.getValue();
        if (start != 0 && end != 0){
            I[offset_n + start - 1] += (It*(exp((dx[offset_n + start - 1] - dx[offset_n + end - 1])/(m_phit)) - 1));
            I[offset_n + end - 1] -= (It*(exp((dx[offset_n + start - 1] - dx[offset_n + end - 1])/(m_phit)) - 1));

            }
        if (start != 0 && end == 0){I[offset_n + start - 1] += (It*(exp((dx[offset_n + start-1])/(m_phit)) - 1));}
        if (start == 0 && end != 0){I[offset_n + end - 1] -= (It*(exp((dx[offset_n + start-1] - dx[offset_n + end -1])/(m_phit)) - 1));}
    };

    void insert_i_vector(Element el_i, int i){
        int start = el_i.getStartNode();
        int end = el_i.getEndNode();
        double val = el_i.getValue();

        if (start != 0) {I[offset_n + start - 1] += val;}
        if (end != 0) {I[offset_n + end - 1] -= val;}
    };

};
