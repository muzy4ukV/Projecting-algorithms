#include "func.h"

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


void sort(string file_name) {
	int quantity_of_number = get_size(file_name);
	copy_file(file_name, quantity_of_number);

	for (long sequence_size = 1; sequence_size < quantity_of_number; sequence_size *=2) {
		split(COPY_FILE, sequence_size);

		//file_output(FIRST_FILE);
		//file_output(SECOND_FILE);

		merge(COPY_FILE, sequence_size, quantity_of_number);

		file_output(COPY_FILE);

	}
	//file_output(COPY_FILE);
}

int get_size(string name) {
	ifstream file(FOLDER_NAME + name, ios::binary);
	file.seekg(0, ios::end);
	int size = file.tellg();
	file.close();
	size /= 4;
	return size;
}

void copy_file(string name, int file_size) {
	ifstream file(FOLDER_NAME + name, ios::binary);
	ofstream copy(FOLDER_NAME + COPY_FILE, ios::binary);

	file.read((char*)&buff, file_size * 4);
	copy.write((char*)&buff, file_size * 4);

	file.close();
	copy.close();
}


void split(string name, int sequence_size) {
	ifstream file_out(FOLDER_NAME + name, ios::binary);
	ofstream A(FOLDER_NAME + FIRST_FILE, ios::binary);
	ofstream B(FOLDER_NAME + SECOND_FILE, ios::binary);
	
	int number;
	bool flag = true;
	int value = 0;

	while (file_out.read((char*)&number, sizeof(number))) {
		if (flag) {
			A.write((char*)&number, sizeof(number));
			value++;
			if (value >= sequence_size) {
				flag = false;
				value = 0;
			}
		}
		else {
			B.write((char*)&number, sizeof(number));
			value++;
			if (value >= sequence_size) {
				flag = true;
				value = 0;
			}
		}
	}
	A.close();
	B.close();
	file_out.close();
}


void merge(string file_name, int sequence_size, int size) {

	ofstream file_out(FOLDER_NAME + file_name, ios::binary);
	ifstream A(FOLDER_NAME + FIRST_FILE, ios::binary);
	ifstream B(FOLDER_NAME + SECOND_FILE, ios::binary);
	int first_number; int second_number;


	while (true) {
		B.read((char*)&second_number, sizeof(int));
		if (B.eof())
			break;
		A.read((char*)&first_number, sizeof(int));
		int valueA = 0, valueB = 0;

		while (valueA != sequence_size && valueB != sequence_size) {
			if (first_number < second_number) {
				file_out.write((char*)&first_number, sizeof(int));
				valueA++;
				if (valueA != sequence_size)
					A.read((char*)&first_number, sizeof(int));
			}
			else {
				file_out.write((char*)&second_number, sizeof(int));
				valueB++;
				if (valueB != sequence_size)
					B.read((char*)&second_number, sizeof(int));
			}
		}
		if (valueA > valueB) {
			file_out.write((char*)&second_number, sizeof(int));
			valueB++;
			while (valueB < sequence_size) {
				B.read((char*)&second_number, sizeof(int));
				if (B.eof())
					break;
				file_out.write((char*)&second_number, sizeof(int));
				valueB++;
			}

		}
		else if (valueA < valueB) {
			file_out.write((char*)&first_number, sizeof(int));
			valueA++;
			while (valueA < sequence_size) {
				A.read((char*)&first_number, sizeof(int));
				if (A.eof())
					break;
				file_out.write((char*)&first_number, sizeof(int));
				valueA++;
			}
		}
	}

	while (A.read((char*)&first_number, sizeof(int))) {
		file_out.write((char*)&first_number, sizeof(int));
	}
	while (B.read((char*)&second_number, sizeof(int))) {
		file_out.write((char*)&second_number, sizeof(int));
	}
	file_out.close();
	A.close();
	B.close();
}