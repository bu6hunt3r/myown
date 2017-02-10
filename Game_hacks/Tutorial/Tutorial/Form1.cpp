#include "Form1.h"

using namespace Tutorial;

void Main(void)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew Form1);
	Application::Exit();
}