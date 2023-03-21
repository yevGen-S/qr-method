#include "pch.h"
#include "QR_GUI.h"

#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
static int matrixDimension;

/// <summary>
/// Фукнция для очистки поля с графиком
/// </summary>
System::Void CppCLRWinformsProjekt::QR_GUI::clearGraphicToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->chart1->Series["qr_explicit_shift_iter_of_eps"]->Points->Clear();
	this->chart1->Series["qr_hes_iter_of_eps"]->Points->Clear();
	return System::Void();
}


/// <summary>
/// Фукнция для создания поля с графиком
/// </summary>
System::Void CppCLRWinformsProjekt::QR_GUI::createGraphicErrorOfIter_Click(System::Object^ sender, System::EventArgs^ e){

	//const string path = fs::current_path().string() + "\\matrix.txt"; // Путь до файла с матрицей
	FILE* file= fopen("matrix.txt", "r"); // Открываем файл

	if (file == NULL) {
		MessageBox::Show("Неправильно задан файл", "ERROR");
		return;
	}

	matrixDimension = findMatrixDimension(file); // поиск ранга матрицы
	fseek(file, 0, SEEK_SET);


	// Проверка, что матрица квадратная.
	if (checkIsMatrixSquared(file, matrixDimension) == ERROR_MATRIX_NOT_SQUARED) {
		this->chart1->Series["qr_implicit_shift_iter_of_eps"]->Points->Clear();
		this->chart1->Series["qr_explicit_shift_iter_of_eps"]->Points->Clear();
		this->chart1->Series["qr_hes_iter_of_eps"]->Points->Clear();
		this->qr_hessenberg->Text = Convert::ToString("");
		this->qr_explicit_solution->Text = Convert::ToString("");
		this->qr_implicit_solution->Text = Convert::ToString("");
	
		MessageBox::Show("Неверно заданная матрица!!!\n Проверьте, что матрица квадратная и перезапустите!", "ERROR");
		return;
	}
	else {
		fseek(file, 0, SEEK_SET);
	}

	double** m = createMatrix(matrixDimension); //Создаем матрицу размерности matrixDimension


	if (fileToMatrix(&m, file, matrixDimension) == ERROR_MATRIX_INPUT) {//Читаем матрицу из файла в m
		this->chart1->Series["qr_implicit_shift_iter_of_eps"]->Points->Clear();
		this->chart1->Series["qr_explicit_shift_iter_of_eps"]->Points->Clear();
		this->chart1->Series["qr_hes_iter_of_eps"]->Points->Clear();
		this->qr_hessenberg->Text = Convert::ToString("");
		this->qr_explicit_solution->Text = Convert::ToString("");
		this->qr_implicit_solution->Text = Convert::ToString("");

		MessageBox::Show("Неверно заданное значение в матрице!!!\n Проверьте, что все значения матрицы числа и запустите заново!", "ERROR");
		return;
	}; 


	double** m2 = m;
	double** m3 = m;


	// Проверка, что матрица симметричная.
	if (!checkIsMatrixSymmetric(m, matrixDimension)) {
		this->chart1->Series["qr_implicit_shift_iter_of_eps"]->Points->Clear();
		this->chart1->Series["qr_explicit_shift_iter_of_eps"]->Points->Clear();
		this->chart1->Series["qr_hes_iter_of_eps"]->Points->Clear();
		this->qr_hessenberg->Text = Convert::ToString("");
		this->qr_explicit_solution->Text = Convert::ToString("");
		this->qr_implicit_solution->Text = Convert::ToString("");

		MessageBox::Show("Неверно заданное значение в матрице!!!\n Проверьте, что матрица симетричная и запустите заново", "ERROR");
		return;
	}

	//this->textBox1->Text = L"button 1 clicked1";
	this->chart1->Series["qr_implicit_shift_iter_of_eps"]->Points->Clear();
	this->chart1->Series["qr_explicit_shift_iter_of_eps"]->Points->Clear();
	this->chart1->Series["qr_hes_iter_of_eps"]->Points->Clear();
	this->qr_hessenberg->Text = Convert::ToString("");
	this->qr_explicit_solution->Text = Convert::ToString("");
	this->qr_implicit_solution->Text = Convert::ToString("");

	double default_eps = 1e-10; // Стандартное значение, если eps не задано в поле ввода
	double input_eps;
	//Проверка корректности ввода данных.

		if (this->textBox1->Text == "") {
			MessageBox::Show("Необходимое поле не заполнено!\n Было подставлено стандартное значение eps = 1e-10", "ERROR");

			vector<double> result1 = qr_explicit_shift_iter_of_eps(m, matrixDimension, default_eps); // получаем вектор попарных значений
			vector<double> result2 = qr_hes_iter_of_eps(m, matrixDimension, default_eps); // аналогично
			vector<double> result3 = qr_implicit_shift_iter_of_eps(m, matrixDimension, default_eps); // аналогично

			double* qr_hes_solution = qr_hes(m, matrixDimension, default_eps);
			double* qr_explicit_solution = qr_explicit_shift(m2, matrixDimension, default_eps);
			double* qr_implicit_solution = qr_implicit_shift(m3, matrixDimension, default_eps);

			for (int i = 0; i < matrixDimension; i++) {
				this->qr_hessenberg->Text += Convert::ToString(qr_hes_solution[i]);
				this->qr_hessenberg->Text += Convert::ToString("  ");

			}
			for (int i = 0; i < matrixDimension; i++) {
				this->qr_explicit_solution->Text += Convert::ToString(qr_explicit_solution[i]);
				this->qr_explicit_solution->Text += Convert::ToString("  ");

			}
			for (int i = 0; i < matrixDimension; i++) {
				this->qr_implicit_solution->Text += Convert::ToString(qr_implicit_solution[i]);
				this->qr_implicit_solution->Text += Convert::ToString("  ");

			}


			for (int i = 0; i < result1.size(); i += 2) {
				this->chart1->Series["qr_explicit_shift_iter_of_eps"]->Points->AddXY(result1[i + 1], result1[i]); //строим график для зависимости с qr методом со сдвигами

			}
			for (int i = 0; i < result2.size(); i += 2) {
				this->chart1->Series["qr_hes_iter_of_eps"]->Points->AddXY(result2[i + 1], result2[i]); //строим график для зависимости с qr методом без сдвигов
			}

			for (int i = 0; i < result3.size(); i += 2) {
				this->chart1->Series["qr_implicit_shift_iter_of_eps"]->Points->AddXY(result3[i + 1], result3[i]); //строим график для зависимости с qr методом c неявными сдвигами
			}
		}
		else {
			try {
				try{
					input_eps = Convert::ToDouble(this->textBox1->Text);
				
					if (input_eps <= 0 ) {
						MessageBox::Show("Задаваемая точность не может быть меньше или равна 0\nВведите значение заново в формате 1e-n", "ERROR");
						return;
					}
					if (input_eps >= 0.1) {
						MessageBox::Show("Задаваемая точность не может быть больше или равна 0.1\n1e-2 - минимальная заданная точность для получения результата \nВведите значение заново в формате 1e-n", "ERROR");
						return;
					}
					if (input_eps <= 1e-16) {
						MessageBox::Show("Задаваемая точность не может быть меньше или равна 1^(-16)\nМашинное eps для double порядка 1^(-16) \nВведите значение заново.", "ERROR");
						return;
					}
					
				}
				catch (OverflowException^) {
					MessageBox::Show("Введено слишком большое значение", "ERROR");
				}
				
				vector<double> result1 = qr_explicit_shift_iter_of_eps(m, matrixDimension, input_eps);// получаем вектор попарных значений
				vector<double> result2 = qr_hes_iter_of_eps(m, matrixDimension, input_eps);// аналогично
				vector<double> result3 = qr_implicit_shift_iter_of_eps(m, matrixDimension, input_eps); // аналогично

				double* qr_hes_solution = qr_hes(m, matrixDimension, input_eps);
				double* qr_explicit_solution = qr_explicit_shift(m2, matrixDimension, input_eps);
				double* qr_implicit_solution = qr_implicit_shift(m3, matrixDimension, input_eps);


				for (int i = 0; i < matrixDimension; i++) {
					this->qr_hessenberg->Text += Convert::ToString(qr_hes_solution[i]);
					this->qr_hessenberg->Text += Convert::ToString("   ");

				}
				for (int i = 0; i < matrixDimension; i++) {
					this->qr_explicit_solution->Text += Convert::ToString(qr_explicit_solution[i]);
					this->qr_explicit_solution->Text += Convert::ToString("   ");

				}
				for (int i = 0; i < matrixDimension; i++) {
					this->qr_implicit_solution->Text += Convert::ToString(qr_implicit_solution[i]);
					this->qr_implicit_solution->Text += Convert::ToString("   ");

				}


				for (int i = 0; i < result1.size(); i += 2) {
					this->chart1->Series["qr_explicit_shift_iter_of_eps"]->Points->AddXY(result1[i + 1], result1[i]);

				}
				for (int i = 0; i < result2.size(); i += 2) {
					this->chart1->Series["qr_hes_iter_of_eps"]->Points->AddXY(result2[i + 1], result2[i]);
				}
				for (int i = 0; i < result3.size(); i += 2) {
					this->chart1->Series["qr_implicit_shift_iter_of_eps"]->Points->AddXY(result3[i + 1], result3[i]); //строим график для зависимости с qr методом c неявными сдвигами
				}
			}
			catch (FormatException^) {
				MessageBox::Show("Вы ввели некорректное значение!\nВведите значение в формате 1e-n", "ERROR");
			}
		}
	

		fclose(file);

	return System::Void();
}


System::Void CppCLRWinformsProjekt::QR_GUI::QR_GUI_Load(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}


