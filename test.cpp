#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
#define TK 1e-3    // Время расчета
#define TST 1e-7   // Начальный шаг
#define TMX 1e-6   // Масимальный шаг
#define TMN 1e-15  // Минимальный шаг
#define ACR 1e-7   // Точность
using namespace std;

double* matrix;    // Матрица Якоби
double* vector;    // Вектор невязок
const int dim = 18;   // Размерность

// Параметры системы 
const double It = 1e-12;
const double E2 = 5.0, E3 = 5.0; 
const double C1 = 1e-6;
const double C2 = 2e-12, C3 = 2e-12;
const double L = 0.1;
const double R1 = 1000.0, R3 = 1000.0;
const double R2 = 10000.0;
const double R4 = 20.0, R7 = 20.0;
const double R5 = 1000000.0, R6 = 1000000.0;
const double Mft = 0.026;
 

//Метод Гаусса для решения СЛАУ
void Gauss() { 
    long int i, j, k;
    int N = dim;
    double diagonalElement;
    for (k = 0; k < N; k++) {   // Прямой ход
        diagonalElement = matrix[N * k + k];
        for (j = k; j < N; j++)
            matrix[N * k + j] /= diagonalElement;
        vector[k] /= diagonalElement;
        for (i = k + 1; i < N; i++) {
            diagonalElement = matrix[N * i + k];
            for (j = k; j < N; j++)
                matrix[N * i + j] -= matrix[N * k + j] * diagonalElement;
            vector[i] -= vector[k] * diagonalElement;
        }
    }
    for (i = N - 2; i >= 0; i--) //Обратный ход
        for (j = i + 1; j < N; j++)
            vector[i] -= matrix[N * i + j] * vector[j];
}

//Функция синусоидального источника
double E_sin(double t) { 
    double A = 10.0;   // Амплитуда
    double freq = 2 * M_PI / 0.0001;  // Частота (2pi/T)
    return A * sin(freq * t);
}

//Нахождение максимального элемента для расчета точности
double max_elem(double * vector, int N) { 
    int i;
    double result = 0;
    for (i = 0; i < N; i++)
        if (result < fabs(vector[i]))
            result = fabs(vector[i]);
    return result;
}

// Функция обнуления перед новым шагом
void Reset() 
{
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            matrix[dim * i + j] = 0;
        }
        vector[i] = 0;
    }
}

void minus_vector() 
{
    for (int i = 0; i < dim; i++) {
        vector[i] = -vector[i];
    }
}

// Заполнение матрицы Якоби
void init_matrix(double dt, double phi_2, double phi_3, double phi_6,  double phi_7) {
    double b = - It/Mft* exp((phi_7-phi_2)/Mft)-1.0/R6;
    double a = 1.0/R1+1.0/R2+1.0/R4-b;
    double d = It/Mft* exp((phi_6-phi_3)/Mft)+1.0/R5;

    // Строки производных переменных состояния
    matrix[dim * 0 + 0] = 1.0;
    matrix[dim * 0 + 4] = -1.0/dt;
    matrix[dim * 1 + 1] = 1.0;
    matrix[dim * 1 + 5] = -1.0/dt;
    matrix[dim * 2 + 2] = 1.0;
    matrix[dim * 2 + 6] = -1.0/dt;
    matrix[dim * 3 + 3] = 1.0;
    matrix[dim * 3 + 7] = -1.0/dt;

    // Строки переменных состояния
    matrix[dim * 4 + 4] = 1.0;
    matrix[dim * 4 + 12] = -1.0;
    matrix[dim * 5 + 5] = 1.0;
    matrix[dim * 5 + 10] = 1.0;
    matrix[dim * 5 + 13] = -1.0;
    matrix[dim * 6 + 6] = 1.0;
    matrix[dim * 6 + 9] = 1.0;
    matrix[dim * 6 + 14] = -1.0;
    matrix[dim * 7 + 3] = L;
    matrix[dim * 7 + 9] = -1.0;
    matrix[dim * 7 + 12] = 1.0;
    
    //phi_1
    matrix[dim * 8 + 8] = 1.0/R1;
    matrix[dim * 8 + 9] = -1.0/R1;
    matrix[dim * 8 + 15] = 1.0;

    //phi_2
    matrix[dim * 9 + 2] = -C3;
    matrix[dim * 9 + 7] = 1.0;
    matrix[dim * 9 + 8] = -1.0/R1;
    matrix[dim * 9 + 9] = a;
    matrix[dim * 9 + 12] = -1.0/R2;
    matrix[dim * 9 + 13] = -1.0/R4;
    matrix[dim * 9 + 14] = b;

    //phi_3
    matrix[dim * 10 + 1] = -C2;
    matrix[dim * 10 + 10] = d;
    matrix[dim * 10 + 13] = -d;
    matrix[dim * 10 + 16] = 1.0;

    //phi_4
    matrix[dim * 11 + 11] = 1.0/R7;
    matrix[dim * 11 + 14] = -1.0/R7;
    matrix[dim * 11 + 17] = -1.0;

    //phi_5
    matrix[dim * 12 + 0] = C1;
    matrix[dim * 12 + 7] = -1.0;
    matrix[dim * 12 + 9] = -1.0/R2;
    matrix[dim * 12 + 12] = 1.0/R3+1.0/R2;

    //phi_6
    matrix[dim * 13 + 1] = C2;
    matrix[dim * 13 + 9] = -1.0/R4;
    matrix[dim * 13 + 10] = -d;
    matrix[dim * 13 + 13] = d+1.0/R4;

    //phi_7
    matrix[dim * 14 + 2] = C3;
    matrix[dim * 14 + 9] = b;
    matrix[dim * 14 + 11] = -1.0/R7;
    matrix[dim * 14 + 14] = 1.0/R7-b;

    // Строки источников
    matrix[dim * 15 + 8] = 1.0;
    matrix[dim * 16 + 10] = 1.0;
    matrix[dim * 17 + 11] = -1.0;

}

// Заполнение вектора невязок
void init_vector(double dt, double time, double dUC1, double dUC2, 
double dUC3, double dIL, double UC1, double UC2, double UC3, double IL,
double phi_1, double phi_2, double phi_3, double phi_4, double phi_5, 
double phi_6,  double phi_7, double IE1, double IE2, double IE3, 
double UC1_prev, double UC2_prev, double UC3_prev, double IL_prev) {
    // Производные переменных состояния
    vector[0] = dUC1 - (UC1-UC1_prev)/dt;
    vector[1] = dUC2 - (UC2-UC2_prev)/dt;
    vector[2] = dUC3 - (UC3-UC3_prev)/dt;
    vector[3] = dIL - (IL-IL_prev)/dt;
    
    // Переменные состояния
    vector[4] = UC1-phi_5;
    vector[5] = UC2-(phi_6-phi_3);
    vector[6] = UC3-(phi_7-phi_2);
    vector[7] = L*dIL-(phi_2-phi_5);
    
    // phi_1
    vector[8] = IE1 +(phi_1-phi_2)/R1;

    // phi_2
    vector[9] = IL -(phi_1-phi_2)/R1 - C3*dUC3 + (phi_2-phi_6)/R4 - It * (exp((phi_7 - phi_2) / Mft) - 1) 
    - (phi_7-phi_2)/R6 +(phi_2-phi_5)/R2; 

    // phi_3
    vector[10] = IE2 - (phi_6-phi_3)/R5 
    - It * (exp((phi_6 - phi_3) / Mft) - 1) - C2*dUC2;

    // phi_4
    vector[11] = (phi_4-phi_7)/R7 - IE3;

    //phi_5
    vector[12] = -IL + C1*dUC1 + phi_5/R3 - (phi_2-phi_5)/R2;

    // phi_6
    vector[13] = (phi_6-phi_3)/R5 + It * (exp((phi_6 - phi_3) / Mft) - 1)
    - (phi_2-phi_6)/R4 + C2*dUC2;

    // phi_7
    vector[14] = (phi_7-phi_2)/R6 + It * (exp((phi_7 - phi_2) / Mft) - 1)
    - (phi_4-phi_7)/R7 + C3*dUC3;
    
    // Источники 
    vector[15] = phi_1 - E_sin(time);
    vector[16] = phi_3 - E2;
    vector[17] = -phi_4 - E3;
}

int main() {
    FILE * f1 = fopen("out.txt", "w");

    double step_t = TST;      // Шаг по времени
    double step_t_prev = step_t;    // Предыдущий шаг по времени
    double dev_max = ACR;    // Максимальное отклонение
    double dev_min = 1e-15;    // Минимальное отклонение

    int i, j;
    int counter = 0;    // Счетчик шагов по времени
    double time = 0;    // Текущее время

    // Текущие значения
    double dUC1 = 0, dUC2 = 0, dUC3 = 0, dIL = 0, UC1 = 0, UC2 = 0, UC3 = 0, IL = 0, phi_1 = 0, 
    phi_2 = 0, phi_3 = 0, phi_4 = 0, phi_5 = 0, phi_6 = 0, phi_7 = 0, IE1 = 0, IE2 = 0, IE3 = 0; 
    // Значения на предыдущем шаге
    double phi_1_prev = 0, phi_1_extra = 0, phi_2_prev = 0, phi_3_prev = 0,
            phi_4_prev = 0, phi_5_prev = 0, phi_6_prev = 0, phi_7_prev = 0;
    double dUC1_prev = 0, dUC2_prev = 0, dUC3_prev = 0, dIL_prev = 0, UC1_prev = 0, UC2_prev = 0, UC3_prev = 0, IL_prev = 0, 
    IE1_prev = 0, IE2_prev = 0, IE3_prev = 0; 

    matrix = (double * ) malloc(sizeof(double) * dim * dim);
    vector = (double * ) malloc(sizeof(double) * dim);

    while (time < TK) { //Общий цикл расчета
        int iteration = 0;  // Счетчик итераций метода Ньютона
        int flag = 1;   // Индикатор сходимости метода Ньютона

        while (flag) {  // Выполнение итераций метода Ньютона
            Reset(); //Обнуление
            init_matrix(step_t, phi_2, phi_3,phi_6, phi_7); 
            init_vector(step_t, time, dUC1, dUC2, dUC3, dIL, UC1, UC2, UC3, IL, phi_1, phi_2, phi_3, phi_4, phi_5, phi_6, phi_7, IE1, IE2, IE3,
             UC1_prev, UC2_prev, UC3_prev, IL_prev);
            minus_vector();

            Gauss();

            dUC1 += vector[0];
            dUC2 += vector[1];
            dUC3 += vector[2];
            dIL += vector[3];
            UC1 += vector[4];
            UC2 += vector[5];
            UC3 += vector[6];
            IL += vector[7];
            phi_1 += vector[8];
            phi_2 += vector[9];
            phi_3 += vector[10];
            phi_4 += vector[11];
            phi_5 += vector[12];
            phi_6 += vector[13];
            phi_7 += vector[14];
            IE1 += vector[15];
            IE2 += vector[16];
            IE3 += vector[17];

            iteration++;

            if (max_elem(vector, dim) <= ACR) // Проверка точности
                flag = 0;

            if (iteration > 7 && flag == 1) { // Метод не сошелся, уменьшение шага и отбрасывание текущих результатов
                if (step_t < TMN){  // Шаг слишком мал, решение не сходится
                    printf("Error: dt < dt_min");
                    exit(1);
                }
                
                iteration = 0;
                step_t /= 2.0;
                cout << "i am here deviating" << endl;
                dUC1 = dUC1_prev;
                dUC2 = dUC2_prev;
                dUC3 = dUC3_prev;
                dIL = dIL_prev;
                UC1 = UC1_prev;
                UC2 = UC2_prev;
                UC3 = UC3_prev;
                IL = IL_prev;
                phi_1 = phi_1_prev;
                phi_2 = phi_2_prev;
                phi_3 = phi_3_prev;
                phi_4 = phi_4_prev;
                phi_5 = phi_5_prev;
                phi_6 = phi_6_prev;
                phi_7 = phi_7_prev;
                IE1 = IE1_prev;
                IE2 = IE2_prev;
                IE3 = IE3_prev;
            }
        }

        // Расчет текущего приращения
        double dev_cur = fabs(0.5 * step_t * step_t * ((phi_1 - phi_1_prev)/step_t - (phi_1_prev - phi_1_extra)/step_t_prev));
        if (dev_cur > dev_max) { //Недостаточная точность, уменьшение шага и отбрасывание текущих результатов
            if (step_t < TMN){  // Шаг слишком мал, решение не сходится
                printf("Error: dt < dt_min");
                exit(1);
            }
            step_t /= 2.0;
            cout << "i am here deviating" << endl;
            dUC1 = dUC1_prev;
            dUC2 = dUC2_prev;
            dUC3 = dUC3_prev;
            dIL = dIL_prev;
            UC1 = UC1_prev;
            UC2 = UC2_prev;
            UC3 = UC3_prev;
            IL = IL_prev;
            phi_1 = phi_1_prev;
            phi_2 = phi_2_prev;
            phi_3 = phi_3_prev;
            phi_4 = phi_4_prev;
            phi_5 = phi_5_prev;
            phi_6 = phi_6_prev;
            phi_7 = phi_7_prev;
            IE1 = IE1_prev;
            IE2 = IE2_prev;
            IE3 = IE3_prev;
        } else { //Точность достигнута
            dUC1_prev = dUC1;
            dUC2_prev = dUC2;
            dUC3_prev = dUC3;
            dIL_prev = dIL;
            UC1_prev = UC1;
            UC2_prev = UC2;
            UC3_prev = UC3;
            IL_prev = IL;
            phi_1_extra = phi_1_prev;
            phi_1_prev = phi_1;
            phi_2_prev = phi_2;
            phi_3_prev = phi_3;
            phi_4_prev = phi_4;
            phi_5_prev = phi_5;
            phi_6_prev = phi_6;
            IE1_prev = IE1;
            IE2_prev = IE2;
            IE3_prev = IE3;

            step_t_prev = step_t;

            fprintf(f1, "%9.6f %.6f %.6f %.6f %.15f\n", time, IL, phi_2, phi_5, step_t);

            time += step_t;
            counter++;

            if (dev_cur < dev_min){ // Точность выше требуемой, увеличение шага
                step_t *= 2.0;
                cout << "i am here" << endl;
            }
        //if (counter < 1000)
        //printf("%d %d %15.10f\n", counter, iteration, step_t);
        }

    }

    // Вывод графика
    FILE * gp = popen("gnuplot -persist", "w");
    fprintf(gp, "set terminal wxt size 900,600\n");
    fprintf(gp, "set grid\n");
    // fprintf(gp, "plot 'out.txt' using 1:2 with line title 'IL'\n");
    // fprintf(gp, "plot 'out.txt' using 1:3 with line title 'phi2'\n");
    fprintf(gp, "plot 'out.txt' using 1:4 with line title 'phi5'\n");
    pclose(gp);

    fclose(f1);
    return 0;
}