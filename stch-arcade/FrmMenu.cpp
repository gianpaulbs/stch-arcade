#include "FrmMenu.h"
#include "FrmBackground.h"

using namespace stcharcade;

int main() {
	srand(time(NULL));
	//Application::Run(gcnew FrmBackground());
	Application::Run(gcnew FrmMenu());
	return 0;
}