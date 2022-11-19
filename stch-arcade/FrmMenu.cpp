#include "FrmMenu.h"
#include "FrmBackground.h"

using namespace stcharcade;

int main() {
	//Application::Run(gcnew FrmBackground());
	srand(time(NULL));

	Application::Run(gcnew FrmMenu());
	return 0;
}