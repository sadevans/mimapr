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
    int n_max = 7;
    float epsilon = 0.001;

public:
    Solver(){};

    void Gauss() { 
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
    };





};