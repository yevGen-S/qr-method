#include "qr.h"
#include "pch.h"


/// <summary>
/// ������� ��� ������ ������� � stdout
/// </summary>
/// <param name="A"> �������, ������� �������� </param>
/// <param name="N"> ���������� �������� ������� </param>
/// <param name="M"> ���������� ����� ������� </param>
void printMatrix(double** A, int N, int M) {
    printf("\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("%*.5lf ", 6, A[i][j]);
        }
        printf("\n");
    }
}

/// <summary>
/// ������� ��� ����������� ������� � ������
/// </summary>
/// <param name="matrix1"> ������� 1 - ���� ������� </param>
/// <param name="matrix2"> ������� 2 - ��� �������� </param>
void copyMatrix( double*** matrix1, double** matrix2 ){
    for(int i=0;i<DIMENSION;i ++){
        for(int j =0;j<DIMENSION;j++){
            (*matrix1)[i][j] = matrix2[i][j];
        }
    }
}

/// <summary>
///  ������� ��� �������� �������.
/// </summary>
/// <param name="n"> �������� ������ ������� </param>
/// <returns> ��������� ������� </returns>
double** createMatrix(int n) {
    double** A = (double**)malloc(n * sizeof(double*)); //�������� ������ �� ������ ���������� ������� n, 
                                                        //������ �� ������� ��������� �� ������
    for (int i = 0; i < n; i++) {
        A[i] = (double*)malloc(n * sizeof(double)); // �������� ������ �� ������
    }
    return A;
}

/// <summary>
/// ������� �������� �������
/// </summary>
/// <param name="c">������ �������</param>
/// <returns> ������ </returns>
double* createVector(int c) {
    return (double*)malloc(c * sizeof(double)); //���������� ��������� �� ���������� ������.
}


/// <summary>
/// ������� ��� ������ ������� �� �����.
/// </summary>
/// <param name="file"> ��������� �� ���� </param>
/// <param name="rang"> ���� ������� </param>
/// <returns> ���������� ���������� � ����� ������� </returns>
double** readMatrix(FILE* file, int rang) {
    double** matrix = createMatrix(rang);// �������� ������� ������� rang
    for (int i = 0; i < rang; i++) {
        for (int j = 0; j < rang; j++) {
            fscanf(file, "%lf; ", &matrix[i][j]);// ��������� ��������������� ������ �� ����� � �������.
        }
    }
    return matrix;
}

/// <summary>
/// ����������� ������, ���������� �� �������.
/// </summary>
/// <param name="A"> ������� </param>
/// <param name="n"> ���� ������� </param>
void freeMatrix(double** A, int n) { // there's n for sure
    for (int i = 0; i < n; i++) {
        free(A[i]); //������������ ������, ���������� �� �������� ��������
    }
    free(A);// ����������� ���������� �� ������
}


/// <summary>
///  ������� ���������������� �������.
/// </summary>
/// <param name="a"> ������� </param>
/// <param name="n"> ���� ������� </param>
/// <returns> ���������� ����������������� ������� </returns>
double** T(double** a, int n) { // transpose matrix
    double** a_t = createMatrix(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a_t[j][i] = a[i][j];
        }
    }
    return a_t;
}


/// <summary>
///  ������� �������� ��������� ������� ����� n
/// </summary>
/// <param name="n"> ���� ������� </param>
/// <returns> ��������� ������� </returns>
double** create_E(int n) {
    double** A = (double**)malloc(sizeof(double*)* n);
    for(int i =0; i < n; i++) {
        A[i] = (double*)calloc(n,sizeof(double));
        A[i][i] =1 ;
    }
    return A;
}


double vectorNorm_2(double* A, int n) {
    double norm = 0;
    for (int i = 0; i < n; i++) {
        norm += A[i] * A[i];
    }
    return sqrt(norm);
}



/// <summary>
/// ������� ������������ ������. �� �������� ������������ ������.
/// </summary>
/// <param name="n"> ���� ������� </param>
/// <param name="H"> ������ ������� </param>
/// <param name="A"> ������ ������� </param>
/// <returns> ��������� ������������ ������ - ����� ������� </returns>
double** multiplyMatrix(int n, double** H, double** A) {
    double** A1 = createMatrix(n); // ������� ������� ����� n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A1[i][j] = 0;
            for (int k = 0; k <n; k++) {
                A1[i][j] += H[i][k] * A[k][j];
            }
        }
    }
    return A1;
}


/// <summary>
///  �������������� �����������(���������)
///  ������� ��� ���������� �������� ������� � ������� ����������� 
/// - ������ ����� ����������� ������� (�����, ������ ��� �������� = 0, ��� ������ ���������� )
///  
/// </summary>
/// <param name="A"> ������� </param>
/// <param name="n"> ���� ������� </param>
/// <returns> ������� ����������� </returns>
double** hessenberg(double** A, int n) {
    double** B = A; // ���������� � B ��������� �� ������� A.
    double summa; 
    int sign; // �����������, ������������ ���� (1 ��� -1)
    double s; // s � m ������������ ��� ���������� �������� w
    double m; //
    for (int i = 0; i < n - 2; i++) {
        summa = 0;

        for (int j = i + 1;j < n; j++) {
            summa += B[j][i] * B[j][i];
        }
        sign = (-B[i+1][i]>0) ? 1 : -1;

        s = sign * sqrt(summa);
        m = 1 / sqrt(2 * s * (s - B[i + 1][i]));

        double* w = createVector(n);// �������� ������� ������� n
        for (int j = 0; j < n; j++) {
            if (j <= i) {
                w[j] = 0;
            }
        }

        w[i+1] = m * (B[i+1][i] - s);

        for (int p = i + 2; p < n; p++) {
            w[p] = m * B[p][i];
        }

        double** P = create_E(n); // �������� ��������� ������� ������� n
        for (int v = 0; v < n; v++) {
            for (int k = 0; k < n; k++) {
                P[v][k] -= 2 * w[v] * w[k]; // �� ��������� ������� �������� ������������ �������� ���� w �� w �����������������.
            }
        }

        B = multiplyMatrix(n, P, B); // ������������ ������� P �� B
        B = multiplyMatrix(n, B, P); // ������������ ������� B �� P
    }
    return B; // ������� �����������
}





/// <summary>
///  �������������� ������� �������� �������.
/// </summary>
/// <param name="B"> �������, � ������ ��������� ���������� </param>
/// <param name="Q"> ������������ ����������������� ������ G - ������ ��������(�������) </param>
/// <param name="R"> �������, ������� �� �������� � ���������� ���������� - ������ �����������</param>
/// <param name="n"> ���� ������ </param>
void givens(double** B, double*** Q, double*** R, int n) {
    double t;
    double cos; // ������� � ����� -- ����������� ������� �������� G.
    double sin; //
    for (int j = 0; j < n - 1; j++) {
        t = B[j][j] / B[j + 1][j];
        cos = 1 / sqrt(1 + t * t); // ���������� ������ � �������� ������������ ����� �������, ������ �� �������,
        sin = t * cos;             // ����� ������������ G �� B �������� ��������������� ��������.
        double** G = create_E(n); // �������� ��������� ������� ����� n
        G[j][j] = sin;
        G[j + 1][j] = -cos;
        G[j + 1][j + 1] = sin;
        G[j][j + 1] = cos;
        B = multiplyMatrix(n, G, B);
        if (j == 0) {
            (*Q) = T(G,n); // �� ������ ���� ���������� � Q ����������������� G
        }
        else {
            double** G_t = T(G, n); // � G_t �������� ������� ����������������� ������� G
            double** Q1 = multiplyMatrix(n, (*Q), G_t); // ��������� ������������ Q �� G_t 
            freeMatrix((*Q), n);
            freeMatrix(G_t, n);
            freeMatrix(G, n);
            (*Q) = Q1;
        }
    }
    (*R) = B; // � R ��������� ��������� ����������.
}

/// <summary>
///  ������� ��� ������ ������������� ���������������� ��������.
/// </summary>
/// <param name="matrix"> �������, � ������� ��������� ����� </param>
/// <param name="n"> ���� ������� </param>
/// <returns> ������������ ��������������� ������� </returns>
double find_max_underdiagonal_element(double** matrix, int n ) {
    double max = 0;
    for (int j = 0; j < (n-1); j++) {
        for (int i = (j+1) ; i < n ; i++) {
            if (fabs(matrix[i][j] > max))
                max = fabs(matrix[i][j]);
        }
    }
    return max;
}


/// <summary>
///  � �������� �������� ��������� ���� �����:
///  ���� ������������ ��������������� ������� ������ ��������� eps,
///  �� ���������� ��������� ��������.
/// </summary>
/// <param name="matrix"> �������</param>
/// <param name="n"> ���� ������� </param>
/// <param name="eps"> �������� ��������</param>
/// <returns> ���� �������� �������� ���������� 1(True), ����� - 0(False)</returns>
char stop_criteria(double** matrix,int n, double eps) {
    if (find_max_underdiagonal_element(matrix,n) < eps)
        return 1;
    return 0;
}


/// <summary>
/// QR ����� � ������������ ���������� � ������� ����������� �� ������ ����
/// � ����������� � ������� ������ �������.
/// </summary>
/// <param name="A"> �������� ������� </param>
/// <param name="n"> ���� ������� </param>
/// <param name="eps"> �������� �������� ���������� </param>
/// <returns> ������ ����������� �������� </returns>
double* qr_hes(double** A, int n, double eps) {
    double** Q = createMatrix(n);//   ������� ������� ����� n
    double** R = createMatrix(n);//
    double** A1;
    double** B = hessenberg(A, n); //�������� �������� ������� � ������� �����������.
    do {
        givens(B, &Q, &R, n); // ��������� ���������� �������, ���� �� ���������� �������� ���������.
        A1 = multiplyMatrix(n, R, Q);
        B = A1;
    } while (!stop_criteria(B, n, eps));

    double* solution = (double*)malloc(n * sizeof(double)); // �������� ������ �� ������ �������.
    for (int i = 0; i < n; i++) {
        solution[i] = B[i][i]; // ��������� -- ����������� �������� �������, ������� �� ��������.
    }

    return solution;
}


/// <summary>
/// ������ ��� ��������� ������������ ��������� ������.
/// </summary>
/// <param name="matrix1"> ������� - �����������</param>
/// <param name="matrix2"> ������� - ����������</param>
/// <param name="n"> ���� ������</param>
void matrix_defference(double*** matrix1, double** matrix2, int n) {
    for (int i = 0; i < n; i++) {
        (*matrix1)[i][i] -= matrix2[i][i];
    }
}

/// <summary>
/// ������ ��� �������� ������������ ��������� ������.
/// </summary>
/// <param name="matrix1"> �������1</param>
/// <param name="matrix2"> �������2 ���������</param>
/// <param name="n"> ���� ������</param>
void matrix_sum(double*** matrix1, double** matrix2, int n) {
    for (int i = 0; i < n; i++) {
        (*matrix1)[i][i] += matrix2[i][i];
    }
}





/// <summary>
///  ������� ��� ������ ������� � �����.
/// </summary>
/// <param name="A"> �������, � ������� ���������� ���������� ������ � �����</param>
/// <param name="file"> ��������� �� �������� ����� </param>
/// <param name="n"> ���� ������� </param>
/// <returns> ��� ������ 0, ���� ������ ������ ������� </returns>
int fileToMatrix(double*** A, FILE* file, int n) {
    char* token; //����� - ��������� ������� ���������� ������
    double number;// ��������������� ���������� �������� 
    char row[300];
    char* check;
    for(int i =0 ; i < n; i++) {
        fgets(row,sizeof(row),file); // ������ ������ �� �����
        token = strtok(row,";");// ����� �� ������ (���� ";")
        for(int j = 0; j < n; j++) {

            number = strtod(token, &check); // ����������� ������ � ���������

            if (token == check) { // ��������, ��� ������� �������
                printf("Error matrix input");
                return ERROR_MATRIX_INPUT;  
            }
            else if (check[strspn(check, " \t\r\n")] != '\0') { // �������� �� ������������ �������
                printf("Error matrix input");
                return ERROR_MATRIX_INPUT;
            }

            (*A)[i][j] = number;
            token =  strtok(NULL,";");
        }
    }
    fgets(row,sizeof(row),file);
    printf("successful reading of matrix");
    return EXIT_SUCCESS;
}

/// <summary>
/// ������� ��� �������� ������� ������� �� ���������� ��������� ������ ������
/// </summary>
/// <param name="file"></param>
/// <returns> ���� ������� </returns>
int findMatrixDimension(FILE* file) {
    char* token; //����� - ��������� ������� ���������� ������
    char row[300];
    int counter = 0;
    if (fgets(row, sizeof(row), file) == NULL) {
        return 0;
    };
    token = strtok(row, ";");
    while (token != NULL) {
        token = strtok(NULL, ";");
        counter++;
    }

    return counter;
}

/// <summary>
/// ������� ��������, ��� ������� ����������.
/// </summary>
/// <param name="file"></param>
/// <param name="matrixDimension"></param>
/// <returns> ���������� ��������� ������� ��� ������</returns>
int checkIsMatrixSquared(FILE* file, int matrixDimension) {
    int counter = 0;
    int numberOfElementsInRow = 0;

    while ((numberOfElementsInRow = findMatrixDimension(file)) != 0) {
        if (matrixDimension != numberOfElementsInRow) {
            return ERROR_MATRIX_NOT_SQUARED;
        }
        counter += numberOfElementsInRow;
        numberOfElementsInRow = 0;
    }

    if (counter != matrixDimension * matrixDimension) {
        return ERROR_MATRIX_NOT_SQUARED;
    }

    return counter;
}

/// <summary>
/// ������� ��������, ��� ������� ������������.
/// </summary>
/// <param name="Matrix"> �������, ������� ����� ��������� �� ��������������</param>
/// <param name="matrixDimension"> ������ ������� </param>
/// <returns> true ���� ������������/false - �� ������������</returns>
int checkIsMatrixSymmetric(double** Matrix, int matrixDimension) {
    for (int j = 0; j < matrixDimension - 1; j++) {
        for (int i = j + 1; i < matrixDimension; i++) {
            if (Matrix[i][j] != Matrix[j][i]) {
                return false;
            }
        }
    }
    return true;
}


/// <summary>
/// QR ����� � ������������ ���������� � ������� ����������� �� ������ ����
/// � ����������� � ������� ������ ������� � ������ ��������.
/// </summary>
/// <param name="A"> �������� ������� </param>
/// <param name="n"> ���� ������� </param>
/// <param name="eps"> �������� �������� ���������� </param>
/// <returns> ������ ����������� �������� </returns>
double* qr_explicit_shift(double** A, int n, double eps) {
    double** Q = createMatrix(n); // �������� ������ ����� n
    double** R = createMatrix(n); //
    double** A1; 
    double** B = hessenberg(A, n);// ���������� �������� ������� � ������� �����������.
    do {
        double** E = create_E(n); // �������� ��������� ������� ����� n
        for(int i = 0; i < n; i++) {
            E[i][i] = B[n-1][n-1]; // ���������� b-n(��) � ������������ �������� E
        }
        matrix_defference(&B, E, n); // �������� �� ������������ ��������� B, �������� E
        givens(B, &Q, &R, n); // 
        A1 = multiplyMatrix(n, R, Q);
        B = A1;
        matrix_sum(&B, E, n);
    } while (!stop_criteria(B, n, eps));

    double* solution = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        solution[i] = B[i][i];
    }

    return solution;
}



/// <summary>
/// ���r��� � ������� QR �� �������� ��� ���������� 
/// ������� ����������� ������� �� �������� ��������
/// </summary>
/// <param name="A"> ������� �������� </param>
/// <param name="n"> ���� ������� </param>
/// <param name="eps"> �������� </param>
/// <returns> ���������� �������� ��� ���������� ���������� ��������</returns>
int qr_explicit_shift_iter(double** A, int n, double eps) {
    double** Q = createMatrix(n);
    double** R = createMatrix(n);
    double** A1;
    int iter = 0;
    double** B = hessenberg(A, n);
    do {
        double** E = create_E(n);
        for (int i = 0; i < n; i++) {
            E[i][i] = B[n - 1][n - 1];
        }
        matrix_defference(&B, E, n);
        givens(B, &Q, &R, n);
        A1 = multiplyMatrix(n, R, Q);
        B = A1;
        matrix_sum(&B, E, n);
        iter++;
    } while (!stop_criteria(B, n, eps));
    
    return iter;
}

/// <summary>
/// ������� ��� ��������� ����������� ���������� �������� �� ���������� �������� ��� QR �� �������
/// </summary>
/// <param name="A"> �������� �������</param>
/// <param name="n"> ���� ������� </param>
/// <param name="eps"> ���������� ��������</param>
/// <returns> ������ �������� �������: ���������� ��������, ���������� ��������</returns>
vector<double> qr_explicit_shift_iter_of_eps(double** A, int n, double eps) {
    vector<double> result;
    double current_eps = 0.1;
    for (current_eps; current_eps >= eps; current_eps /= 10) {// �������� ����� qr, ������������ ���������� �������� ��� eps �� 0.1 �� ����������� � ����� � 10
        result.push_back(current_eps);
        result.push_back(double(qr_explicit_shift_iter(A, n, current_eps)));
    }
    return result;
}


/// <summary>
///  ������� ��� ��������� ������ � �������� ��� ������� �������� �������
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns>������ �� 2-�� ���������: ����� � ������� </returns>
double* givens_cos_sin(double a, double b) {
    double* res = (double*)malloc(sizeof(double) * 2);
    double c;
    double s;
    double t;

    if (b == 0) {
        c = 1;
        s = 0;
    }
    else {
        if (fabs(b) > fabs(a)) {
            t = -a / b; s = 1 / sqrt(1 + t * t); c = s * t;
        }
        else {
            t = -b / a; c = 1 / sqrt(1 + t * t);  s = c * t;
        }
    }

    res[0] = c;
    res[1] = s;

    return res;
}



/// <summary>
///  ������� �������� ������������� QR-���� �� ������� ����������.
/// </summary>
/// <param name="B"> ������� �����������</param>
/// <param name="A"> ������� ��� ���������� �������� ��� ���������� ���� </param>
/// <param name="n"> ������ ������� </param>
/// <returns> ������� ��� ���������� ���� </returns>
double** QR_francis_implicity_step(double** B, int n) {
    double d = (B[n - 2][n - 2] - B[n - 1][n - 1]) / 2; //��������� ��� ������ ����������
    double sign = (d > 0) ? 1 : -1;
    double m = B[n - 1][n - 1] - pow(B[n - 1][n - 2], 2) / (d + sign * sqrt(d * d + B[n - 1][n - 2])); //����� ����������
    double x = B[0][0] - m;
    double z = B[1][0];

    double* c_s = givens_cos_sin(x, z); // ������� � ����� ��� ���������� ������� �������� 

    double** G = create_E(n);
    G[0][0] = c_s[0];
    G[1][0] = -c_s[1];
    G[0][1] = c_s[1];
    G[1][1] = c_s[0];

    double** G_t = T(G, n); // ���������������� ������� G -�������

    B = multiplyMatrix(n, G_t, B); // ������������ ������� G_t �� B
    B = multiplyMatrix(n, B, G); // ������������ ������� B �� G

    for (int j = 0; j < n - 2; j++) {
        c_s = givens_cos_sin(B[j + 1][j], B[j + 2][j]);

        G = create_E(n);
        G[j + 1][j + 1] = c_s[0];
        G[j + 2][j + 1] = -c_s[1];
        G[j + 1][j + 2] = c_s[1];
        G[j + 2][j + 2] = c_s[0];

        G_t = T(G, n);

        B = multiplyMatrix(n, G_t, B);
        B = multiplyMatrix(n, B, G);
    }
    
    return B;

}

/// <summary>
///  ������� QR ��������� � �������� �������� ���������� ��� ���������������� ������������ �������.
/// </summary>
/// <param name="A"> �������, ��� ������� ���� ����������� ��������</param>
/// <param name="n"> ����������� �������</param>
/// <param name="eps"> �������� �������</param>
/// <returns> ������ ����������� ��������  </returns>
double* qr_implicit_shift(double** A, int n, double eps) {
    double** B = hessenberg(A, n);// ��������� ���������������� �������, �.�. ���������� A - ������������

    do {
        B = QR_francis_implicity_step(B, n); //���������� ���� �������� QR ���������
        
    } while (!stop_criteria(B, n, eps));

    double* solution = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        solution[i] = B[i][i];
    }

    return solution;
}


/// <summary>
/// ������� � ������� QR � �������� �������� ��� ���������� 
/// ������� ����������� ������� �� �������� ��������
/// </summary>
/// <param name="A"> ������� �������� </param>
/// <param name="n"> ���� ������� </param>
/// <param name="eps"> �������� </param>
/// <returns> ���������� �������� ��� ���������� ���������� ��������</returns>
int qr_implicit_shift_iter(double** A, int n, double eps) {
    double** B = hessenberg(A, n);// ��������� ���������������� �������, �.�. ���������� A - ������������
    int iter = 0;
    do {
        B = QR_francis_implicity_step(B, n); //���������� ���� �������� QR ���������
        iter++;
    } while (!stop_criteria(B, n, eps));

    return iter;
}



/// <summary>
/// ������� ��� ��������� ����������� ���������� �������� �� ���������� �������� ��� QR � �������� ��������
/// </summary>
/// <param name="A"> �������� �������</param>
/// <param name="n"> ���� ������� </param>
/// <param name="eps"> ���������� ��������</param>
/// <returns> ������ �������� �������: ���������� ��������, ���������� ��������</returns>
vector<double> qr_implicit_shift_iter_of_eps(double** A, int n, double eps) {
    vector<double> result;
    double current_eps = 0.1;
    for (current_eps; current_eps >= eps; current_eps /= 10) {// �������� ����� qr, ������������ ���������� �������� ��� eps �� 0.1 �� ����������� � ����� � 10
        result.push_back(current_eps);
        result.push_back(double(qr_implicit_shift_iter(A, n, current_eps)));
    }
    return result;
}



/// <summary>
/// ������� � ������� QR ��� �������
/// </summary>
/// <param name="A"> ������� �������� </param>
/// <param name="n"> ���� ������� </param>
/// <param name="eps"> �������� </param>
/// <returns> ���������� �������� ��� ���������� ���������� ��������</returns>
int qr_hes_iter(double** A, int n, double eps) {
    double** Q = createMatrix(n);
    double** R = createMatrix(n);
    double** A1;
    int iter = 0;
    double** B = hessenberg(A, n);
    do {
        givens(B, &Q, &R, n);
        A1 = multiplyMatrix(n, R, Q);
        B = A1;
        iter++;
    } while (!stop_criteria(B, n, eps));
    return iter;
}

/// <summary>
/// ������� ��� ��������� ����������� ���������� �������� �� ���������� �������� ��� QR ��� ������
/// </summary>
/// <param name="A"> �������� �������</param>
/// <param name="n"> ���� ������� </param>
/// <param name="eps"> ���������� ��������</param>
/// <returns> ������ �������� �������: ���������� ��������, ���������� ��������</returns>
vector<double> qr_hes_iter_of_eps(double** A, int n, double eps) {
    vector<double> result;
    double current_eps = 0.1;
    for (current_eps; current_eps >= eps; current_eps /= 10) {
        result.push_back(current_eps);
        result.push_back(double(qr_hes_iter(A, n, current_eps)));
    }
    return result;
}