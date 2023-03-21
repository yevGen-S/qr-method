#include "qr.h"
#include "pch.h"


/// <summary>
/// Функция для печати матрицы в stdout
/// </summary>
/// <param name="A"> Матрица, которую передаем </param>
/// <param name="N"> Количество столбцов матрицы </param>
/// <param name="M"> Количество строк матрицы </param>
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
/// Функция для копирования матрицы в другую
/// </summary>
/// <param name="matrix1"> Матрица 1 - куда кпируем </param>
/// <param name="matrix2"> Матрица 2 - что копируем </param>
void copyMatrix( double*** matrix1, double** matrix2 ){
    for(int i=0;i<DIMENSION;i ++){
        for(int j =0;j<DIMENSION;j++){
            (*matrix1)[i][j] = matrix2[i][j];
        }
    }
}

/// <summary>
///  Функция для создания матрицы.
/// </summary>
/// <param name="n"> Желаемый размер матрциы </param>
/// <returns> Созданную матрицу </returns>
double** createMatrix(int n) {
    double** A = (double**)malloc(n * sizeof(double*)); //Выделяем память на массив указателей размера n, 
                                                        //каждый из которых указывает на строку
    for (int i = 0; i < n; i++) {
        A[i] = (double*)malloc(n * sizeof(double)); // Выделяем память на строки
    }
    return A;
}

/// <summary>
/// Функция создания вектора
/// </summary>
/// <param name="c">Размер вектора</param>
/// <returns> Вектор </returns>
double* createVector(int c) {
    return (double*)malloc(c * sizeof(double)); //Возвращает указатель на выделенную память.
}


/// <summary>
/// Функция для чтения матрицы из файла.
/// </summary>
/// <param name="file"> Указатель на файл </param>
/// <param name="rang"> Ранг матрицы </param>
/// <returns> Возвращает прочтенную с файла матрицу </returns>
double** readMatrix(FILE* file, int rang) {
    double** matrix = createMatrix(rang);// создание матрицы размера rang
    for (int i = 0; i < rang; i++) {
        for (int j = 0; j < rang; j++) {
            fscanf(file, "%lf; ", &matrix[i][j]);// выполняем форматированное чтение из файла в матрицу.
        }
    }
    return matrix;
}

/// <summary>
/// Освобожение памяти, выделенной на матрицу.
/// </summary>
/// <param name="A"> Матрица </param>
/// <param name="n"> Ранг матрицы </param>
void freeMatrix(double** A, int n) { // there's n for sure
    for (int i = 0; i < n; i++) {
        free(A[i]); //освобождение памяти, выделенной на элементы матрцицы
    }
    free(A);// освобожение указателей на строки
}


/// <summary>
///  Функция транспонирования матрицы.
/// </summary>
/// <param name="a"> Матрица </param>
/// <param name="n"> Ранг матрицы </param>
/// <returns> Возвращает транспонированную матрицу </returns>
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
///  Функция создания единичной матрицы ранга n
/// </summary>
/// <param name="n"> Ранг матрицы </param>
/// <returns> Единичная матрица </returns>
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
/// Функция произведения матриц. По правилам произведения матриц.
/// </summary>
/// <param name="n"> Ранг матрицы </param>
/// <param name="H"> Первая матрица </param>
/// <param name="A"> Вторая матрица </param>
/// <returns> Результат произведения матриц - новая матрциа </returns>
double** multiplyMatrix(int n, double** H, double** A) {
    double** A1 = createMatrix(n); // Создаем матрицу ранга n;
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
///  Преобразование Хаусхолдера(отражения)
///  Функция для приведения исходной матрицы к матрице Хессенберга 
/// - правой почти треугольной матрице (почти, потому что элементы = 0, под второй диагональю )
///  
/// </summary>
/// <param name="A"> Матрица </param>
/// <param name="n"> Ранг матрицы </param>
/// <returns> Матрица Хессенберга </returns>
double** hessenberg(double** A, int n) {
    double** B = A; // Записываем в B указатель на матрицу A.
    double summa; 
    int sign; // коэффициент, определяющий знак (1 или -1)
    double s; // s и m коэффициенты для вычисления векторов w
    double m; //
    for (int i = 0; i < n - 2; i++) {
        summa = 0;

        for (int j = i + 1;j < n; j++) {
            summa += B[j][i] * B[j][i];
        }
        sign = (-B[i+1][i]>0) ? 1 : -1;

        s = sign * sqrt(summa);
        m = 1 / sqrt(2 * s * (s - B[i + 1][i]));

        double* w = createVector(n);// Создание вектора размера n
        for (int j = 0; j < n; j++) {
            if (j <= i) {
                w[j] = 0;
            }
        }

        w[i+1] = m * (B[i+1][i] - s);

        for (int p = i + 2; p < n; p++) {
            w[p] = m * B[p][i];
        }

        double** P = create_E(n); // Создание единичной матрицы размера n
        for (int v = 0; v < n; v++) {
            for (int k = 0; k < n; k++) {
                P[v][k] -= 2 * w[v] * w[k]; // Из единичной матрицы вычитаем произведение векторов вида w на w транспонированное.
            }
        }

        B = multiplyMatrix(n, P, B); // Произведение матрицы P на B
        B = multiplyMatrix(n, B, P); // Произведение матрицы B на P
    }
    return B; // Матрица Хессенберга
}





/// <summary>
///  Преобразование плоских вращений Гивенса.
/// </summary>
/// <param name="B"> Матрица, к оторой применяем разложение </param>
/// <param name="Q"> Произведение транспонированных матриц G - матриц вращений(Гивенса) </param>
/// <param name="R"> Матрица, которую мы получаем в результате разложения - правая трегоульная</param>
/// <param name="n"> Ранг матриц </param>
void givens(double** B, double*** Q, double*** R, int n) {
    double t;
    double cos; // косинус и синус -- кэффициенты матрицы вращений G.
    double sin; //
    for (int j = 0; j < n - 1; j++) {
        t = B[j][j] / B[j + 1][j];
        cos = 1 / sqrt(1 + t * t); // вычисление синуса и косинуса производится таким образом, исходя из условий,
        sin = t * cos;             // чтобы произведения G на B зануляли поддиагональные элементы.
        double** G = create_E(n); // Создание единичной матрицы ранга n
        G[j][j] = sin;
        G[j + 1][j] = -cos;
        G[j + 1][j + 1] = sin;
        G[j][j + 1] = cos;
        B = multiplyMatrix(n, G, B);
        if (j == 0) {
            (*Q) = T(G,n); // на первом шаге записываем в Q транспонированную G
        }
        else {
            double** G_t = T(G, n); // в G_t помещаем текущую транспонированную матрицу G
            double** Q1 = multiplyMatrix(n, (*Q), G_t); // выполняем произведение Q на G_t 
            freeMatrix((*Q), n);
            freeMatrix(G_t, n);
            freeMatrix(G, n);
            (*Q) = Q1;
        }
    }
    (*R) = B; // в R записваем результат разложения.
}

/// <summary>
///  Функция для поиска максимального поддиагонального элемента.
/// </summary>
/// <param name="matrix"> Матрица, в которой выполняем поиск </param>
/// <param name="n"> Ранг матрицы </param>
/// <returns> Максимальный поддигаональный элемент </returns>
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
///  В качестве критерия остановки было взято:
///  Если максимальный поддиагональный элемент меньше заданного eps,
///  то достигнута требуемая точность.
/// </summary>
/// <param name="matrix"> Матрица</param>
/// <param name="n"> Ранг матрицы </param>
/// <param name="eps"> Желаемая точность</param>
/// <returns> Если критерий выполнен вовзращаем 1(True), иначе - 0(False)</returns>
char stop_criteria(double** matrix,int n, double eps) {
    if (find_max_underdiagonal_element(matrix,n) < eps)
        return 1;
    return 0;
}


/// <summary>
/// QR метод с модификацией привидения к матрице Хессенберга на первом шаге
/// и завершением с помощью метода Гивенса.
/// </summary>
/// <param name="A"> Исходная матрциа </param>
/// <param name="n"> Ранг матрицы </param>
/// <param name="eps"> Желаемая точность результата </param>
/// <returns> Вектор собственных значений </returns>
double* qr_hes(double** A, int n, double eps) {
    double** Q = createMatrix(n);//   Создаем матрицы ранга n
    double** R = createMatrix(n);//
    double** A1;
    double** B = hessenberg(A, n); //Приводим исходную матрицу к матрице Хессенберга.
    do {
        givens(B, &Q, &R, n); // Выполняем разложение Гивенса, пока не выполнится критерий остановки.
        A1 = multiplyMatrix(n, R, Q);
        B = A1;
    } while (!stop_criteria(B, n, eps));

    double* solution = (double*)malloc(n * sizeof(double)); // Выделяем память на вектор решений.
    for (int i = 0; i < n; i++) {
        solution[i] = B[i][i]; // Результат -- дигональные элементы матрицы, которую мы получили.
    }

    return solution;
}


/// <summary>
/// Фунция для вычитания диагональных элементов матриц.
/// </summary>
/// <param name="matrix1"> Матрица - уменьшаемое</param>
/// <param name="matrix2"> Матрица - вычитаемое</param>
/// <param name="n"> Ранг матриц</param>
void matrix_defference(double*** matrix1, double** matrix2, int n) {
    for (int i = 0; i < n; i++) {
        (*matrix1)[i][i] -= matrix2[i][i];
    }
}

/// <summary>
/// Фунция для сложение диагональных элементов матриц.
/// </summary>
/// <param name="matrix1"> Матрица1</param>
/// <param name="matrix2"> Матрица2 слагаемое</param>
/// <param name="n"> Ранг матриц</param>
void matrix_sum(double*** matrix1, double** matrix2, int n) {
    for (int i = 0; i < n; i++) {
        (*matrix1)[i][i] += matrix2[i][i];
    }
}





/// <summary>
///  Функция для чтения матрицы с файла.
/// </summary>
/// <param name="A"> Матрица, в которую записываем прочтенные данные с файла</param>
/// <param name="file"> Указатель на файловых поток </param>
/// <param name="n"> Ранг матрицы </param>
/// <returns> код ошибки 0, если чтение прошло успешно </returns>
int fileToMatrix(double*** A, FILE* file, int n) {
    char* token; //токен - отдельный элемент прочтенной строки
    double number;// форматированное прочтенное значение 
    char row[300];
    char* check;
    for(int i =0 ; i < n; i++) {
        fgets(row,sizeof(row),file); // читаем строку из файла
        token = strtok(row,";");// делим на токены (было ";")
        for(int j = 0; j < n; j++) {

            number = strtod(token, &check); // форматируем токены к значениям

            if (token == check) { // Проверка, что введены символы
                printf("Error matrix input");
                return ERROR_MATRIX_INPUT;  
            }
            else if (check[strspn(check, " \t\r\n")] != '\0') { // Проверка на некорректные символы
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
/// Функция для проверки размера матрицы по количеству элементов первой строки
/// </summary>
/// <param name="file"></param>
/// <returns> ранг матрицы </returns>
int findMatrixDimension(FILE* file) {
    char* token; //токен - отдельный элемент прочтенной строки
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
/// Функция проверки, что матрица квадратная.
/// </summary>
/// <param name="file"></param>
/// <param name="matrixDimension"></param>
/// <returns> Количество элементов матрицы или ошибку</returns>
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
/// Функция проверки, что матрица симметричная.
/// </summary>
/// <param name="Matrix"> Матрица, которую хотим проверить на симметричность</param>
/// <param name="matrixDimension"> Размер матрицы </param>
/// <returns> true если симметричная/false - не симметричная</returns>
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
/// QR метод с модификацией привидения к матрице Хессенберга на первом шаге
/// и завершением с помощью метода Гивенса с явными сдвигами.
/// </summary>
/// <param name="A"> Исходная матрица </param>
/// <param name="n"> Ранг матрицы </param>
/// <param name="eps"> Желаемая точность результата </param>
/// <returns> Вектор собственных значений </returns>
double* qr_explicit_shift(double** A, int n, double eps) {
    double** Q = createMatrix(n); // Создание матриц ранга n
    double** R = createMatrix(n); //
    double** A1; 
    double** B = hessenberg(A, n);// Приведение исходной матрицы к матрице Хессенберга.
    do {
        double** E = create_E(n); // Создание единичной матрицы ранга n
        for(int i = 0; i < n; i++) {
            E[i][i] = B[n-1][n-1]; // записываем b-n(ый) в диагональные элементы E
        }
        matrix_defference(&B, E, n); // вычитаем из диагональных элементов B, элементы E
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
/// Фунrция с методом QR со сдвигами для построения 
/// графика зависимости итеаций от заданной точности
/// </summary>
/// <param name="A"> Матрица исходная </param>
/// <param name="n"> Ранг матрицы </param>
/// <param name="eps"> Точность </param>
/// <returns> Количество итераций для достижения задаваемой точности</returns>
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
/// Функция для получения зависимости количества итераций от задаваемой точности для QR со сдвигом
/// </summary>
/// <param name="A"> Исходная матрица</param>
/// <param name="n"> Ранг матрицы </param>
/// <param name="eps"> Задаваемая точность</param>
/// <returns> Вектор значений попарно: задаваемая точность, количество итераций</returns>
vector<double> qr_explicit_shift_iter_of_eps(double** A, int n, double eps) {
    vector<double> result;
    double current_eps = 0.1;
    for (current_eps; current_eps >= eps; current_eps /= 10) {// Вызываем метод qr, возвращающий количество итераций для eps от 0.1 до задаваемого с шагом в 10
        result.push_back(current_eps);
        result.push_back(double(qr_explicit_shift_iter(A, n, current_eps)));
    }
    return result;
}


/// <summary>
///  Функция для получения синуса и косинуса для матрицы вращений Гивенса
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns>массив из 2-ух элементов: синус и косинус </returns>
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
///  Функция неявного симметричного QR-шага со сдвигом Уилкинсона.
/// </summary>
/// <param name="B"> Матрица Хессенберга</param>
/// <param name="A"> Матрица для сохранения значения для следующего шага </param>
/// <param name="n"> размер матрицы </param>
/// <returns> Матрицу для следующего шага </returns>
double** QR_francis_implicity_step(double** B, int n) {
    double d = (B[n - 2][n - 2] - B[n - 1][n - 1]) / 2; //параметры для сдвига Уилкинсона
    double sign = (d > 0) ? 1 : -1;
    double m = B[n - 1][n - 1] - pow(B[n - 1][n - 2], 2) / (d + sign * sqrt(d * d + B[n - 1][n - 2])); //сдвиг Уилкинсона
    double x = B[0][0] - m;
    double z = B[1][0];

    double* c_s = givens_cos_sin(x, z); // косинус и синус для построения матрицы вращений 

    double** G = create_E(n);
    G[0][0] = c_s[0];
    G[1][0] = -c_s[1];
    G[0][1] = c_s[1];
    G[1][1] = c_s[0];

    double** G_t = T(G, n); // транспонирование матрицы G -Гивенса

    B = multiplyMatrix(n, G_t, B); // произведение матрицы G_t на B
    B = multiplyMatrix(n, B, G); // произведение матрицы B на G

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
///  Функция QR алгоритма с неявными сдвигами Уилкинсона для трехдиагональной симметричной матрицы.
/// </summary>
/// <param name="A"> Матрица, для которой ищем собственные значения</param>
/// <param name="n"> размерность матрицы</param>
/// <param name="eps"> заданная точноть</param>
/// <returns> массив собственных значений  </returns>
double* qr_implicit_shift(double** A, int n, double eps) {
    double** B = hessenberg(A, n);// получение трехдиагональной матрицы, т.к. изначально A - симметричная

    do {
        B = QR_francis_implicity_step(B, n); //выполнение шага неявного QR алгоритма
        
    } while (!stop_criteria(B, n, eps));

    double* solution = (double*)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        solution[i] = B[i][i];
    }

    return solution;
}


/// <summary>
/// Фукнция с методом QR с неявными сдвигами для построения 
/// графика зависимости итеаций от заданной точности
/// </summary>
/// <param name="A"> Матрица исходная </param>
/// <param name="n"> Ранг матрицы </param>
/// <param name="eps"> Точность </param>
/// <returns> Количество итераций для достижения задаваемой точности</returns>
int qr_implicit_shift_iter(double** A, int n, double eps) {
    double** B = hessenberg(A, n);// получение трехдиагональной матрицы, т.к. изначально A - симметричная
    int iter = 0;
    do {
        B = QR_francis_implicity_step(B, n); //выполнение шага неявного QR алгоритма
        iter++;
    } while (!stop_criteria(B, n, eps));

    return iter;
}



/// <summary>
/// Функция для получения зависимости количества итераций от задаваемой точности для QR с неявными сдвигами
/// </summary>
/// <param name="A"> Исходная матрица</param>
/// <param name="n"> Ранг матрицы </param>
/// <param name="eps"> Задаваемая точность</param>
/// <returns> Вектор значений попарно: задаваемая точность, количество итераций</returns>
vector<double> qr_implicit_shift_iter_of_eps(double** A, int n, double eps) {
    vector<double> result;
    double current_eps = 0.1;
    for (current_eps; current_eps >= eps; current_eps /= 10) {// Вызываем метод qr, возвращающий количество итераций для eps от 0.1 до задаваемого с шагом в 10
        result.push_back(current_eps);
        result.push_back(double(qr_implicit_shift_iter(A, n, current_eps)));
    }
    return result;
}



/// <summary>
/// Фукнция с методом QR без сдвигов
/// </summary>
/// <param name="A"> Матрица исходная </param>
/// <param name="n"> Ранг матрицы </param>
/// <param name="eps"> Точность </param>
/// <returns> Количество итераций для достижения задаваемой точности</returns>
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
/// Функция для получения зависимости количества итераций от задаваемой точности для QR без сдвига
/// </summary>
/// <param name="A"> Исходная матрица</param>
/// <param name="n"> Ранг матрицы </param>
/// <param name="eps"> Задаваемая точность</param>
/// <returns> Вектор значений попарно: задаваемая точность, количество итераций</returns>
vector<double> qr_hes_iter_of_eps(double** A, int n, double eps) {
    vector<double> result;
    double current_eps = 0.1;
    for (current_eps; current_eps >= eps; current_eps /= 10) {
        result.push_back(current_eps);
        result.push_back(double(qr_hes_iter(A, n, current_eps)));
    }
    return result;
}