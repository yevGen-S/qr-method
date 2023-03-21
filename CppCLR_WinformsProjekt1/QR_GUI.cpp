#include "pch.h"
#include "QR_GUI.h"

#include <string>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
static int matrixDimension;

/// <summary>
/// ������� ��� ������� ���� � ��������
/// </summary>
System::Void CppCLRWinformsProjekt::QR_GUI::clearGraphicToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->chart1->Series["qr_explicit_shift_iter_of_eps"]->Points->Clear();
	this->chart1->Series["qr_hes_iter_of_eps"]->Points->Clear();
	return System::Void();
}


/// <summary>
/// ������� ��� �������� ���� � ��������
/// </summary>
System::Void CppCLRWinformsProjekt::QR_GUI::createGraphicErrorOfIter_Click(System::Object^ sender, System::EventArgs^ e){

	//const string path = fs::current_path().string() + "\\matrix.txt"; // ���� �� ����� � ��������
	FILE* file= fopen("matrix.txt", "r"); // ��������� ����

	if (file == NULL) {
		MessageBox::Show("����������� ����� ����", "ERROR");
		return;
	}

	matrixDimension = findMatrixDimension(file); // ����� ����� �������
	fseek(file, 0, SEEK_SET);


	// ��������, ��� ������� ����������.
	if (checkIsMatrixSquared(file, matrixDimension) == ERROR_MATRIX_NOT_SQUARED) {
		this->chart1->Series["qr_implicit_shift_iter_of_eps"]->Points->Clear();
		this->chart1->Series["qr_explicit_shift_iter_of_eps"]->Points->Clear();
		this->chart1->Series["qr_hes_iter_of_eps"]->Points->Clear();
		this->qr_hessenberg->Text = Convert::ToString("");
		this->qr_explicit_solution->Text = Convert::ToString("");
		this->qr_implicit_solution->Text = Convert::ToString("");
	
		MessageBox::Show("������� �������� �������!!!\n ���������, ��� ������� ���������� � �������������!", "ERROR");
		return;
	}
	else {
		fseek(file, 0, SEEK_SET);
	}

	double** m = createMatrix(matrixDimension); //������� ������� ����������� matrixDimension


	if (fileToMatrix(&m, file, matrixDimension) == ERROR_MATRIX_INPUT) {//������ ������� �� ����� � m
		this->chart1->Series["qr_implicit_shift_iter_of_eps"]->Points->Clear();
		this->chart1->Series["qr_explicit_shift_iter_of_eps"]->Points->Clear();
		this->chart1->Series["qr_hes_iter_of_eps"]->Points->Clear();
		this->qr_hessenberg->Text = Convert::ToString("");
		this->qr_explicit_solution->Text = Convert::ToString("");
		this->qr_implicit_solution->Text = Convert::ToString("");

		MessageBox::Show("������� �������� �������� � �������!!!\n ���������, ��� ��� �������� ������� ����� � ��������� ������!", "ERROR");
		return;
	}; 


	double** m2 = m;
	double** m3 = m;


	// ��������, ��� ������� ������������.
	if (!checkIsMatrixSymmetric(m, matrixDimension)) {
		this->chart1->Series["qr_implicit_shift_iter_of_eps"]->Points->Clear();
		this->chart1->Series["qr_explicit_shift_iter_of_eps"]->Points->Clear();
		this->chart1->Series["qr_hes_iter_of_eps"]->Points->Clear();
		this->qr_hessenberg->Text = Convert::ToString("");
		this->qr_explicit_solution->Text = Convert::ToString("");
		this->qr_implicit_solution->Text = Convert::ToString("");

		MessageBox::Show("������� �������� �������� � �������!!!\n ���������, ��� ������� ����������� � ��������� ������", "ERROR");
		return;
	}

	//this->textBox1->Text = L"button 1 clicked1";
	this->chart1->Series["qr_implicit_shift_iter_of_eps"]->Points->Clear();
	this->chart1->Series["qr_explicit_shift_iter_of_eps"]->Points->Clear();
	this->chart1->Series["qr_hes_iter_of_eps"]->Points->Clear();
	this->qr_hessenberg->Text = Convert::ToString("");
	this->qr_explicit_solution->Text = Convert::ToString("");
	this->qr_implicit_solution->Text = Convert::ToString("");

	double default_eps = 1e-10; // ����������� ��������, ���� eps �� ������ � ���� �����
	double input_eps;
	//�������� ������������ ����� ������.

		if (this->textBox1->Text == "") {
			MessageBox::Show("����������� ���� �� ���������!\n ���� ����������� ����������� �������� eps = 1e-10", "ERROR");

			vector<double> result1 = qr_explicit_shift_iter_of_eps(m, matrixDimension, default_eps); // �������� ������ �������� ��������
			vector<double> result2 = qr_hes_iter_of_eps(m, matrixDimension, default_eps); // ����������
			vector<double> result3 = qr_implicit_shift_iter_of_eps(m, matrixDimension, default_eps); // ����������

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
				this->chart1->Series["qr_explicit_shift_iter_of_eps"]->Points->AddXY(result1[i + 1], result1[i]); //������ ������ ��� ����������� � qr ������� �� ��������

			}
			for (int i = 0; i < result2.size(); i += 2) {
				this->chart1->Series["qr_hes_iter_of_eps"]->Points->AddXY(result2[i + 1], result2[i]); //������ ������ ��� ����������� � qr ������� ��� �������
			}

			for (int i = 0; i < result3.size(); i += 2) {
				this->chart1->Series["qr_implicit_shift_iter_of_eps"]->Points->AddXY(result3[i + 1], result3[i]); //������ ������ ��� ����������� � qr ������� c �������� ��������
			}
		}
		else {
			try {
				try{
					input_eps = Convert::ToDouble(this->textBox1->Text);
				
					if (input_eps <= 0 ) {
						MessageBox::Show("���������� �������� �� ����� ���� ������ ��� ����� 0\n������� �������� ������ � ������� 1e-n", "ERROR");
						return;
					}
					if (input_eps >= 0.1) {
						MessageBox::Show("���������� �������� �� ����� ���� ������ ��� ����� 0.1\n1e-2 - ����������� �������� �������� ��� ��������� ���������� \n������� �������� ������ � ������� 1e-n", "ERROR");
						return;
					}
					if (input_eps <= 1e-16) {
						MessageBox::Show("���������� �������� �� ����� ���� ������ ��� ����� 1^(-16)\n�������� eps ��� double ������� 1^(-16) \n������� �������� ������.", "ERROR");
						return;
					}
					
				}
				catch (OverflowException^) {
					MessageBox::Show("������� ������� ������� ��������", "ERROR");
				}
				
				vector<double> result1 = qr_explicit_shift_iter_of_eps(m, matrixDimension, input_eps);// �������� ������ �������� ��������
				vector<double> result2 = qr_hes_iter_of_eps(m, matrixDimension, input_eps);// ����������
				vector<double> result3 = qr_implicit_shift_iter_of_eps(m, matrixDimension, input_eps); // ����������

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
					this->chart1->Series["qr_implicit_shift_iter_of_eps"]->Points->AddXY(result3[i + 1], result3[i]); //������ ������ ��� ����������� � qr ������� c �������� ��������
				}
			}
			catch (FormatException^) {
				MessageBox::Show("�� ����� ������������ ��������!\n������� �������� � ������� 1e-n", "ERROR");
			}
		}
	

		fclose(file);

	return System::Void();
}


System::Void CppCLRWinformsProjekt::QR_GUI::QR_GUI_Load(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}


