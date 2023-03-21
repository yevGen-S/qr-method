#pragma once

namespace CppCLRWinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;

	/// <summary>
	///
	/// </summary>
	public ref class QR_GUI : public System::Windows::Forms::Form
	{
	public:
		QR_GUI()
		{
			InitializeComponent();
			//
			//Конструктор для графического интерфейса
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы
		/// </summary>
		~QR_GUI()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::GroupBox^ groupBox5;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::GroupBox^ groupBox4;
	private: System::Windows::Forms::TextBox^ tap2output;
	private: System::Windows::Forms::TabPage^ tabPage3;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::Button^ create_graphic;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TabControl^ tabControl2;
	private: System::Windows::Forms::ToolStripMenuItem^ menuToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^ clearGraphicToolStripMenuItem; 

	private: System::Windows::Forms::Label^ label5;


	private: System::Windows::Forms::Label^ label6;

	private: System::Windows::Forms::Label^ qr_implicit_solution;
	private: System::Windows::Forms::Label^ qr_hessenberg;

	private: System::Windows::Forms::Label^ qr_explicit_solution;

	private: System::Windows::Forms::Label^ label3;

	private:

		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Метод для инициализации графических компонентов
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^ title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->menuToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->clearGraphicToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->tap2output = (gcnew System::Windows::Forms::TextBox());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->qr_implicit_solution = (gcnew System::Windows::Forms::Label());
			this->qr_explicit_solution = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->qr_hessenberg = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->create_graphic = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->tabControl2 = (gcnew System::Windows::Forms::TabControl());
			this->menuStrip1->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->tabControl2->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->menuToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1208, 24);
			this->menuStrip1->TabIndex = 4;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// menuToolStripMenuItem
			// 
			this->menuToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->clearGraphicToolStripMenuItem });
			this->menuToolStripMenuItem->Name = L"menuToolStripMenuItem";
			this->menuToolStripMenuItem->Size = System::Drawing::Size(50, 20);
			this->menuToolStripMenuItem->Text = L"Menu";
			// 
			// clearGraphicToolStripMenuItem
			// 
			this->clearGraphicToolStripMenuItem->Name = L"clearGraphicToolStripMenuItem";
			this->clearGraphicToolStripMenuItem->Size = System::Drawing::Size(144, 22);
			this->clearGraphicToolStripMenuItem->Text = L"Clear graphic";
			this->clearGraphicToolStripMenuItem->Click += gcnew System::EventHandler(this, &QR_GUI::clearGraphicToolStripMenuItem_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->tap2output);
			this->groupBox4->Location = System::Drawing::Point(3, 6);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(899, 466);
			this->groupBox4->TabIndex = 4;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Graphic";
			// 
			// tap2output
			// 
			this->tap2output->Location = System::Drawing::Point(65, 53);
			this->tap2output->Multiline = true;
			this->tap2output->Name = L"tap2output";
			this->tap2output->Size = System::Drawing::Size(637, 321);
			this->tap2output->TabIndex = 0;
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->button1);
			this->groupBox5->Location = System::Drawing::Point(908, 324);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(277, 147);
			this->groupBox5->TabIndex = 7;
			this->groupBox5->TabStop = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(0, 0);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->qr_implicit_solution);
			this->tabPage3->Controls->Add(this->qr_explicit_solution);
			this->tabPage3->Controls->Add(this->label3);
			this->tabPage3->Controls->Add(this->label6);
			this->tabPage3->Controls->Add(this->label5);
			this->tabPage3->Controls->Add(this->qr_hessenberg);
			this->tabPage3->Controls->Add(this->groupBox1);
			this->tabPage3->Controls->Add(this->groupBox3);
			this->tabPage3->Controls->Add(this->groupBox2);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(1200, 477);
			this->tabPage3->TabIndex = 0;
			this->tabPage3->Text = L"Error of iteration";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// qr_implicit_solution
			// 
			this->qr_implicit_solution->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->qr_implicit_solution->Location = System::Drawing::Point(838, 360);
			this->qr_implicit_solution->Name = L"qr_implicit_solution";
			this->qr_implicit_solution->Size = System::Drawing::Size(362, 52);
			this->qr_implicit_solution->TabIndex = 14;
			// 
			// qr_explicit_solution
			// 
			this->qr_explicit_solution->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->qr_explicit_solution->Location = System::Drawing::Point(841, 257);
			this->qr_explicit_solution->Name = L"qr_explicit_solution";
			this->qr_explicit_solution->Size = System::Drawing::Size(347, 51);
			this->qr_explicit_solution->TabIndex = 13;
			// 
			// label3
			// 
			this->label3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label3->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->label3->Location = System::Drawing::Point(841, 318);
			this->label3->Margin = System::Windows::Forms::Padding(10);
			this->label3->Name = L"label3";
			this->label3->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
			this->label3->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label3->Size = System::Drawing::Size(116, 32);
			this->label3->TabIndex = 12;
			this->label3->Text = L"QR_implicit_shift";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label6
			// 
			this->label6->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label6->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->label6->Location = System::Drawing::Point(841, 215);
			this->label6->Margin = System::Windows::Forms::Padding(10);
			this->label6->Name = L"label6";
			this->label6->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
			this->label6->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->label6->Size = System::Drawing::Size(116, 32);
			this->label6->TabIndex = 11;
			this->label6->Text = L"QR_explicit_shift";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label6->Click += gcnew System::EventHandler(this, &QR_GUI::label6_Click);
			// 
			// label5
			// 
			this->label5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label5->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->label5->Location = System::Drawing::Point(841, 110);
			this->label5->Margin = System::Windows::Forms::Padding(10);
			this->label5->Name = L"label5";
			this->label5->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
			this->label5->Size = System::Drawing::Size(116, 35);
			this->label5->TabIndex = 10;
			this->label5->Text = L"QR_hessenberg";
			this->label5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// qr_hessenberg
			// 
			this->qr_hessenberg->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 6.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->qr_hessenberg->ForeColor = System::Drawing::SystemColors::ControlText;
			this->qr_hessenberg->Location = System::Drawing::Point(848, 155);
			this->qr_hessenberg->Name = L"qr_hessenberg";
			this->qr_hessenberg->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->qr_hessenberg->Size = System::Drawing::Size(346, 50);
			this->qr_hessenberg->TabIndex = 7;
			this->qr_hessenberg->Click += gcnew System::EventHandler(this, &QR_GUI::label2_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->chart1);
			this->groupBox1->Location = System::Drawing::Point(3, 6);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(832, 466);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Graphic";
			// 
			// chart1
			// 
			this->chart1->BorderlineColor = System::Drawing::Color::Black;
			chartArea1->AxisX->Title = L"number of iterations";
			chartArea1->AxisY->IsLogarithmic = true;
			chartArea1->AxisY->Title = L"Error(eps)";
			chartArea1->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->chart1->Legends->Add(legend1);
			this->chart1->Location = System::Drawing::Point(62, 19);
			this->chart1->Name = L"chart1";
			this->chart1->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::Bright;
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series1->IsValueShownAsLabel = true;
			series1->Legend = L"Legend1";
			series1->Name = L"qr_explicit_shift_iter_of_eps";
			series2->ChartArea = L"ChartArea1";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series2->IsValueShownAsLabel = true;
			series2->Legend = L"Legend1";
			series2->Name = L"qr_hes_iter_of_eps";
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Line;
			series3->IsValueShownAsLabel = true;
			series3->Legend = L"Legend1";
			series3->Name = L"qr_implicit_shift_iter_of_eps";
			this->chart1->Series->Add(series1);
			this->chart1->Series->Add(series2);
			this->chart1->Series->Add(series3);
			this->chart1->Size = System::Drawing::Size(781, 441);
			this->chart1->TabIndex = 2;
			this->chart1->Text = L"chart1";
			title1->Name = L"Title_error_of_iteration";
			title1->Text = L"Зависимость ошибки(достигаемой точности) от количества итераций ";
			this->chart1->Titles->Add(title1);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->create_graphic);
			this->groupBox3->Location = System::Drawing::Point(841, 415);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(347, 57);
			this->groupBox3->TabIndex = 6;
			this->groupBox3->TabStop = false;
			// 
			// create_graphic
			// 
			this->create_graphic->Location = System::Drawing::Point(86, 19);
			this->create_graphic->Name = L"create_graphic";
			this->create_graphic->Size = System::Drawing::Size(104, 23);
			this->create_graphic->TabIndex = 0;
			this->create_graphic->Text = L"create_graphic";
			this->create_graphic->UseVisualStyleBackColor = true;
			this->create_graphic->Click += gcnew System::EventHandler(this, &QR_GUI::createGraphicErrorOfIter_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->textBox1);
			this->groupBox2->Controls->Add(this->label1);
			this->groupBox2->Location = System::Drawing::Point(841, 6);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(347, 100);
			this->groupBox2->TabIndex = 5;
			this->groupBox2->TabStop = false;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(100, 35);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(132, 20);
			this->textBox1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->label1->Location = System::Drawing::Point(13, 35);
			this->label1->Margin = System::Windows::Forms::Padding(10);
			this->label1->Name = L"label1";
			this->label1->Padding = System::Windows::Forms::Padding(20, 0, 0, 0);
			this->label1->Size = System::Drawing::Size(74, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Eps";
			// 
			// tabControl2
			// 
			this->tabControl2->Controls->Add(this->tabPage3);
			this->tabControl2->Location = System::Drawing::Point(0, 27);
			this->tabControl2->Name = L"tabControl2";
			this->tabControl2->SelectedIndex = 0;
			this->tabControl2->Size = System::Drawing::Size(1208, 503);
			this->tabControl2->TabIndex = 8;
			// 
			// QR_GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1208, 529);
			this->Controls->Add(this->tabControl2);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"QR_GUI";
			this->Text = L"QR_GUI";
			this->Load += gcnew System::EventHandler(this, &QR_GUI::QR_GUI_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->groupBox1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			this->groupBox3->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->tabControl2->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void QR_GUI_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void clearGraphicToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void createGraphicErrorOfIter_Click(System::Object^ sender, System::EventArgs^ e);

private: System::Void label6_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
