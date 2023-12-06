#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>
#include "Schema.h"
using namespace std;


class Solver {
private:
    Schema* schema;
    int n_max;
    float epsilon;
    float start_t;
    float min_t;
    float max_t;
    float t;
public:
    Solver(Schema* _schema, int _n_max = 7, float _epsilon = 1e-7, 
        float _start_t = 1e-7, float _min_t = 1e-15, 
        float _max_t = 1e-6, float _t = 1e-3):
    schema(_schema), n_max(_n_max), epsilon(_epsilon), start_t(_start_t), min_t(_min_t), max_t(_max_t), t(_t){};

    
    vector<float> gauss() { 
        long int i, j, k;
        int N = schema->get_dimension();
        double diagonalElement;
        vector<vector<float>> matrix = schema->get_matrix();
        vector<float> I = schema->get_vector();

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
        
        for (i = N - 2; i >= 0; i--) //Обратный ход
            for (j = i + 1; j < N; j++)
                I[i] -= matrix[i][j] * I[j];

        for (int i = 0; i<schema->get_dimension();i++){
            cout << I[i] << " ";
        }
        cout << endl;

        return I;
    };


    void point_method() {
        float time = 0;
        schema->init_dx();
        while (time < t){
            int newton_iteration = 0;
            bool newton_convergence = true;
            while (newton_convergence){
                schema->init_matrix_vector();
                schema->print_matrix();
                schema->print_vector();
                // return;
                vector<float> new_dx = gauss();
                schema->change_vectors(new_dx);
                return;

            }
        }

    }





};