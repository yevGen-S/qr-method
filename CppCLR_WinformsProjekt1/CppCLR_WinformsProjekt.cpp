#include "pch.h"

#include "QR_GUI.h"
using namespace System;


using namespace System::Windows::Forms;

[STAThread]
int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew CppCLRWinformsProjekt::QR_GUI());
	return 0;
}