#include "func.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string file_name = generate_file();
	file_output(file_name);
	sort(file_name);

	return 0;
}