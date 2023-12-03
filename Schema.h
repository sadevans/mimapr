#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "Element.h"
#define de
using namespace std;

class Schema {
    private:
        vector<Element>e_elements;
        vector<Element>c_elements;
        vector<Element>r_elements;
        vector<Element>l_elements;
        vector<Element>i_elements;

        int e_count;
        int c_count;
        int r_count;
        int l_count;
        int i_count;
        int n_count;

        int offset_du;
        int offset_di;
        int offset_u;
        int offset_i;
        int offset_n;
        int offset_e;

        float delta_t;

        int all_count;
        int matrix_len;

        vector<float> b;
        vector<vector<float>> A;
        vector<float> dx;
        vector<float> dx_prev;

    public:
        Schema(float t){delta_t = t;};

        void change_delta(){delta_t /= 2;};
        void add_element(Element elem){
            if (elem.getType() == ElementType::E){ e_count+=1; e_elements.push_back(elem);}
            if (elem.getType() == ElementType::C){ c_count+=1; c_elements.push_back(elem);}
            if (elem.getType() == ElementType::R){ r_count+=1; r_elements.push_back(elem);}
            if (elem.getType() == ElementType::L){ l_count+=1; l_elements.push_back(elem);}
            if (elem.getType() == ElementType::I){ i_count+=1; i_elements.push_back(elem);}

            if (elem.getStartNode()>n_count)
                n_count = elem.getStartNode();

            if (elem.getEndNode()>n_count)
                n_count = elem.getEndNode();

            all_count+=1;
        };


        void get_elements(){
            for (const auto& elem : e_elements) {
                std::cout << "\nElement Type: " << static_cast<int>(elem.getType()) << std::endl;
                std::cout << "Start Node: " << elem.getStartNode() << std::endl;
                std::cout << "End Node: " << elem.getEndNode() << std::endl;
                std::cout << "Value: " << elem.getValue() << std::endl;
                std::cout << "Name: " << elem.getName() << std::endl;
            }
            for (const auto& elem : c_elements) {
                std::cout << "\nElement Type: " << static_cast<int>(elem.getType()) << std::endl;
                std::cout << "Start Node: " << elem.getStartNode() << std::endl;
                std::cout << "End Node: " << elem.getEndNode() << std::endl;
                std::cout << "Value: " << elem.getValue() << std::endl;
                std::cout << "Name: " << elem.getName() << std::endl;
            }
            for (const auto& elem : r_elements) {
                std::cout << "\nElement Type: " << static_cast<int>(elem.getType()) << std::endl;
                std::cout << "Start Node: " << elem.getStartNode() << std::endl;
                std::cout << "End Node: " << elem.getEndNode() << std::endl;
                std::cout << "Value: " << elem.getValue() << std::endl;
                std::cout << "Name: " << elem.getName() << std::endl;
            }
            for (const auto& elem : l_elements) {
                std::cout << "\nElement Type: " << static_cast<int>(elem.getType()) << std::endl;
                std::cout << "Start Node: " << elem.getStartNode() << std::endl;
                std::cout << "End Node: " << elem.getEndNode() << std::endl;
                std::cout << "Value: " << elem.getValue() << std::endl;
                std::cout << "Name: " << elem.getName() << std::endl;
            }
            for (const auto& elem : i_elements) {
                std::cout << "\nElement Type: " << static_cast<int>(elem.getType()) << std::endl;
                std::cout << "Start Node: " << elem.getStartNode() << std::endl;
                std::cout << "End Node: " << elem.getEndNode() << std::endl;
                std::cout << "Value: " << elem.getValue() << std::endl;
                std::cout << "Name: " << elem.getName() << std::endl;
            }
            cout << "E count: " << e_count << endl;
            cout << "C count: " << c_count << endl;
            cout << "R count: " << r_count << endl;
            cout << "L count: " << l_count << endl;
            cout << "I count: " << i_count << endl;
        };

        void init_matrix_and_vector(){
            matrix_len = 2 * c_count + 2 * l_count + n_count + e_count;
            for (int i = 0; i < matrix_len; i++){
                vector<float> temp;
                for (int j = 0; j < matrix_len; j++)
                    temp.push_back(0);
                A.push_back(temp);
                b.push_back(0);
                dx.push_back(0);
                dx_prev.push_back(0);
            }
            
            offset_du = 0;
            offset_di = c_count;
            offset_u = c_count + l_count;
            offset_i = 2 * c_count + l_count;
            offset_n = 2 * (c_count + l_count);
            offset_e = 2 * (c_count + l_count) + n_count;

            for (int i = 0; i < c_count; i++)
                insert_condencator_matrix(c_elements[i], i);

            for (int i = 0; i < l_count; i++)
                insert_katushka_matrix(c_elements[i], i); 

            for (int i = 0; i < r_count; i++)
                insert_resistor_matrix(c_elements[i], i);

            for (int i = 0; i < e_count; i++)
                insert_eds_matrix(c_elements[i], i);                             
        };


        void insert_condencator_matrix(Element condencator, int i){
            A[i][i] += 1;
            A[i][offset_u + i] -= 1/delta_t;
            A[offset_u + i][offset_u + i] += 1;
            int start = condencator.getStartNode();
            int finish = condencator.getEndNode();
            if (start != 0){
                A[offset_u + i][offset_n + start - 1] -= 1;
                A[offset_n + start - 1][i] += condencator.getValue();
            }
            if (finish != 0){
                A[offset_u + i][offset_n + finish - 1] += 1;
                A[offset_n + finish - 1][i] -= condencator.getValue();
            }            
        }


        void insert_katushka_matrix(Element katushka, int i){
            A[offset_di + i][offset_di + i] += 1;
            A[offset_di + i][offset_i + i] += (-1/delta_t);
            A[offset_i + i][offset_di + i] += katushka.getValue();
            int start = katushka.getStartNode();
            int finish = katushka.getEndNode();
            if (start != 0) {
                A[offset_i + i][offset_n + start - 1] -= 1;
                A[offset_n + start - 1][offset_i + i] += 1;
            }
            if (finish != 0) {
                A[offset_i + i][offset_n + finish - 1] += 1;
                A[offset_n + finish - 1][offset_i + i] -= 1;
            }
        };

        void insert_resistor_matrix(Element resistor, int i){
            int start = resistor.getStartNode();
            int finish = resistor.getEndNode();  
            float r = resistor.getValue();
            if (start != 0) A[offset_n + start - 1][offset_n + start - 1] += 1/r;
            if (finish != 0) A[offset_n + finish - 1][offset_n + finish - 1] += 1/r;
            if (start != 0 && finish != 0){
                A[offset_n + finish - 1][offset_n + start - 1] -= 1/r;
                A[offset_n + start - 1][offset_n + finish - 1] -= 1/r;
            }  
        }


        void insert_eds_matrix(Element eds, int i){
            int start = eds.getStartNode();
            int end = eds.getEndNode();
            if (start != 0) {
                A[offset_n + start - 1][offset_e] += 1;
                A[offset_e][offset_n + start - 1] += 1;
            }
            if (end != 0) {
                A[offset_n + end - 1][offset_e] -= 1;
                A[offset_e][offset_n + end - 1] -= 1;
            }
        };


        void insert_i(Element i){

        }
        void print_matrix(){
            for (int i = 0; i < matrix_len; i++){
                for (int j = 0; j < matrix_len; j++)
                    cout << A[i][j]<< " ";
                cout << endl;
            };
        }

        void init_dx(){

        };

        void reset_vector(){};
        //void reset_phi(){};
};