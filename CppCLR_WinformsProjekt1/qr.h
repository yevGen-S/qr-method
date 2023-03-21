#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#include "iostream"
#include "vector"
#include "fstream"

#define eps1 1e-10
#define DIMENSION 10

#define ERROR_MATRIX_INPUT -100
#define ERROR_MATRIX_NOT_SQUARED -101

using namespace std;



void printMatrix(double** A, int N, int M);
void copyMatrix( double*** matrix1, double** matrix2 );
double** createMatrix(int n);
double* createVector(int c);
double** readMatrix(FILE* file, int rang);
void freeMatrix(double** A, int n);
double** T(double** a, int n);
double** create_E(int n);
double vectorNorm_2(double* A, int n);
double** multiplyMatrix(int n, double** H, double** A);
double** hessenberg(double** A, int n);
void givens(double** B, double*** Q, double*** R, int n);
double find_max_underdiagonal_element(double** matrix, int n );
char stop_criteria(double** matrix,int n, double eps);
double* qr_hes(double** A, int n, double eps);
void matrix_defference(double*** matrix1, double** matrix2,int n );
void matrix_sum (double*** matrix1, double** matrix2, int n);
int fileToMatrix(double*** A, FILE* file, int n);

double* qr_explicit_shift(double** A, int n, double eps);
double* qr_implicit_shift(double** A, int n, double eps);

int findMatrixDimension(FILE* file);
int checkIsMatrixSquared(FILE* file, int matrixDimension);
int checkIsMatrixSymmetric(double** Matrix, int matrixDimension);

int qr_explicit_shift_iter(double** A, int n, double eps);
vector<double> qr_explicit_shift_iter_of_eps(double** A, int n, double eps);

int qr_hes_iter(double** A, int n, double eps);
vector<double> qr_hes_iter_of_eps(double** A, int n, double eps);

double* givens_cos_sin(double a, double b);
double** QR_francis_implicity_step(double** B, int n);

int qr_implicit_shift_iter(double** A, int n, double eps);
vector<double> qr_implicit_shift_iter_of_eps(double** A, int n, double eps);

