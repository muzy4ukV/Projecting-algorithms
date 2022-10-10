#include "classes.h"

int buff[BUFF_SIZE];

string generate_file() {
	cout << "Ви хочете згенерувати файл чи відсортувати наявний?\nВідсортувати наявний - 1\nСтворити новий - 2\n";
	string flag, file_name;
	while (true) {
		getline(cin, flag);
		if (!flag.compare("1")) {
			cout << "Введіть ім'я файлу: ";
			getline(cin, file_name);
			ifstream file(FOLDER_NAME + file_name, ios::binary);
			if (!file) {
				cout << "Неможливо відкрити файл з ім'ям " << file_name << "\n";
				exit(1);
			}
			file.close();
			break;
		}
		else if (!flag.compare("2"))
		{
			cout << "Введіть ім'я файлу: ";
			getline(cin, file_name);
			cout << "Введіть розмір файлу (у Мб): ";
			int size; cin >> size;
			cin.ignore(32767, '\n');
			cout << "Генеруємо файл...\n";

			ofstream file(FOLDER_NAME + file_name, ios::binary);
			unsigned long long number_of_ints = (size * pow(1024, 2));
			number_of_ints /= 4;

			random_device rd;
			mt19937 mersenne(rd());
			if (number_of_ints <= BUFF_SIZE) {
				for (unsigned int i = 0; i < number_of_ints; i++) {
					buff[i] = mersenne();
				}
				file.write((char*)&buff, number_of_ints * 4);
				file.close();
			}
			else {
				int count = number_of_ints / BUFF_SIZE;
				int remainder = number_of_ints % BUFF_SIZE;
				for (int i = 0; i < count; i++)
				{
					for (unsigned int j = 0; j < BUFF_SIZE; j++) {
						buff[j] = mersenne();
					}
					file.write((char*)&buff, sizeof(buff));
				}
				for (unsigned int i = 0; i < remainder; i++) {
					buff[i] = mersenne();
				}

				file.write((char*)&buff, remainder * 4);
				file.close();
			}
			break;
		}
		else {
			cout << "Неправильно введені дані :( Спробуйте ще раз\n";
		}
	}
	return file_name;
}


void file_output(string name) {
	ifstream file(FOLDER_NAME + name, ios::binary);

	cout << "\n===========////===========\n\n" << name << "\n\n";
	int number; 
	int flag = 1;
	cout << "\nFirst " << NUMBER_OF_READ << " numbers\n\n";
	for (int i = 0; i < NUMBER_OF_READ; i++) {
		file.read((char*)&number, sizeof(number));
		cout << number << "   ";
		if (flag == 8) {
			flag = 0;
			cout << endl;
		}
		flag++;
	}

	file.seekg(-(NUMBER_OF_READ * 4), ios::end);
	cout << "\nLast " << NUMBER_OF_READ << " numbers\n\n";

	flag = 1;
	for (int i = 0; i < NUMBER_OF_READ; i++) {
		file.read((char*)&number, sizeof(number));
		cout << number << "   ";
		if (flag == 8) {
			flag = 0;
			cout << endl;
		}
		flag++;
	}

	cout << "\n===========////===========\n\n";
	file.close();
}