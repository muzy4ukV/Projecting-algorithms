#include "classes.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string file_name = generate_file();
	file_output(file_name);

	cout << "Який алгоритм обираєте: базовий чи модифікований?\n";
	cout << "Базовий - 1\nМодифікований - 2\n";
	

	string flag;
	while (true) {
		getline(cin, flag);
		if (!flag.compare("1")) {
			BasicSort file(file_name);
			file.basic_sort();
			break;
		}
		else if (!flag.compare("2")) {
			ModifiedSort file(file_name);
			file.modified_sort();
			break;
		}
		else {
			cout << "Неправильно введені дані :( Спробуйте ще раз\n";
		}
	}
	file_output(COPY_FILE);
	return 0;
}