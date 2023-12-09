#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>
#include <cmath>
#include <bits/stdc++.h>
#include "Schema.h"
#include <unistd.h>
using namespace std;


class Solver {
private:
    Schema* schema;
    int n_max;
    double epsilon;
    double start_t;
    double min_t;
    double max_t;
    double t;
public:
    Solver(Schema* _schema, int _n_max = 7, double _epsilon = 1e-2, 
        double _start_t = 1e-4, double _min_t = 1e-9, 
        double _max_t = 1e-2, double _t = 5):
    schema(_schema), n_max(_n_max), epsilon(_epsilon), start_t(_start_t), min_t(_min_t), max_t(_max_t), t(_t){};

    double max_elem(vector<double> vect, int dim) {
        double result = 0;
        int temp = 0;
        for (int i = 0; i < dim; i++)
            if (result < abs(vect[i])) {result = abs(vect[i]); temp = i;};
        return result;
    };
    


    vector<double> gauss(int counter) { 
        long int i, j, k;
        int N = schema->get_dimension();
        double diagonalElement;
        vector<vector<double>> matrix = schema->get_matrix();
        vector<double> I = schema->get_vector();

        for (k = 0; k < N; k++) {   // Прямой ход
            diagonalElement = matrix[k][k];
            for (j = k; j < N; j++)
                matrix[k][j] /= diagonalElement;
            I[k] /= diagonalElement;
            for (i = k + 1; i < N; i++) {
                diagonalElement = matrix[i][k];
                for (j = k; j < N; j++)
                    matrix[i][j] -= matrix[k][j] * diagonalElement;
                I[i] -= I[k] * diagonalElement;
            }
        }

        for (i = N - 2; i >= 0; i--)
            for (j = i + 1; j < N; j++)
                I[i] -= matrix[i][j] * I[j];
        return I;
    };


    void point_method(FILE * file) {
        double time = 0;
        int counter = 0;
        schema->init_dx();
        while (time < t){
            int newton_iteration = 0;
            bool newton_convergence = true;
            while (newton_convergence){
                schema->init_matrix_vector(time, start_t);            
                vector<double> new_dx = gauss(counter);          
                schema->change_dx_vector(new_dx);
                newton_iteration += 1;
                double max_elem1 = max_elem(new_dx, schema->get_dimension());
                if (max_elem1 < epsilon){
                    newton_convergence = false;
                }   
                else{
                    
                    if (newton_iteration > n_max){    
                        newton_iteration = 0;
                        schema->decrease_delta_t();
                        if (schema->get_delta_t() < min_t){
                            cout << "delta t is to small, not possible to solve. Program exit." << endl;
                            exit(0);
                        }
                        schema->revert_dx();
                    }
                }
                counter ++;
            }

            vector<double> deviations = schema->get_deviation();
            //if (*max_element(deviations.begin(), deviations.end()) < min_t){
            if(deviations[0] < min_t){

                    time += schema->get_delta_t();
                    schema->increase_delta_t();
                    schema->change_dx_prev_vector();
                    fprintf(file, "%9.9f ", time);
                    for (int k = schema->get_n_offset(); k < schema->get_n_offset() + schema->getNCount(); k++)
                        fprintf(file, "%.12f ", schema->get_dx_elem(k));
                    fprintf(file, "\n");
            }
            else
                //if(*max_element(deviations.begin(), deviations.end()) < max_t && *min_element(deviations.begin(), deviations.end()) > min_t){
                if(deviations[0] < max_t && deviations[0] > min_t){
                    time += schema->get_delta_t();
                    schema->change_dx_prev_vector();
                    fprintf(file, "%9.12f ", time);
                    for (int k = schema->get_n_offset(); k < schema->get_n_offset() + schema->getNCount(); k++)
                        fprintf(file, "%.12f ", schema->get_dx_elem(k));
                    fprintf(file, "\n");
                }
                else{
                    schema->decrease_delta_t();
                    if (schema->get_delta_t() < min_t){
                        cout << "delta t is to small, not possible to solve. Program exit." << endl;
                        exit(0);
                    }
                    schema->revert_dx();
                }
        }
    }
};