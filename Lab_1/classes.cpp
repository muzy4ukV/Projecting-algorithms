#include "classes.h"

extern int buff[BUFF_SIZE];

Sort::Sort(string name) : file_name(name), sequence_size(1) {
	get_size();
}

long long Sort::get_size() {
	ifstream file(FOLDER_NAME + file_name, ios::binary);
	file.seekg(0, ios::end);
	file_size = file.tellg();
	file.close();
	file_size /= 4;
	return file_size;
}

void Sort::test() {
	bool flag = true;
	ifstream file(FOLDER_NAME + COPY_FILE, ios::binary);
	int previous_num, next_num;
	if (file_size <= BUFF_SIZE) {
		file.read((char*)&buff, sizeof(int) * file_size);
		for (int i = 0; i < file_size - 1; i++) {
			previous_num = buff[i];
			next_num = buff[i+1];
			if (previous_num > next_num)
				flag = false;
		}
	}
	else {
		int count = file_size / BUFF_SIZE;
		int remainder = file_size % BUFF_SIZE;
		for (int i = 0; i < count; i++) {
			file.read((char*)&buff, sizeof(int) * BUFF_SIZE);
			for (int j = 0; j < BUFF_SIZE - 1; j++) {
				previous_num = buff[j];
				next_num = buff[j + 1];
				if (previous_num > next_num)
					flag = false;
			}
		}
		file.read((char*)&buff, 4 * remainder);
		for (int i = 0; i < remainder - 1; i++) {
			previous_num = buff[i];
			next_num = buff[i + 1];
			if (previous_num > next_num)
				flag = false;
		}
	}

	if (flag)
		cout << "Тест пройдено успішно, файл відсортований" << endl;
	else
		cout << "Тест не пройдено :(" << endl;
}

BasicSort::BasicSort(string name) : Sort(name) {}

void BasicSort::copy_file() {
	ifstream file(FOLDER_NAME + file_name, ios::binary);
	ofstream copy(FOLDER_NAME + COPY_FILE, ios::binary);

	file.read((char*)&buff, file_size * 4);
	copy.write((char*)&buff, file_size * 4);

	file.close();
	copy.close();
}

void BasicSort::split() {
	ifstream file_out(FOLDER_NAME + COPY_FILE, ios::binary);
	ofstream A(FOLDER_NAME + FIRST_FILE, ios::binary);
	ofstream B(FOLDER_NAME + SECOND_FILE, ios::binary);

	int number;
	bool flag = true;
	long long value = 0;

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

void BasicSort::basic_sort() {
	copy_file();
	for (; sequence_size < file_size; sequence_size *= 2) {
		split();
		merge();
	}
	test();
}

void BasicSort::merge() {
	ofstream file_out(FOLDER_NAME + COPY_FILE, ios::binary);
	ifstream A(FOLDER_NAME + FIRST_FILE, ios::binary);
	ifstream B(FOLDER_NAME + SECOND_FILE, ios::binary);
	int first_number; int second_number;

	while (true) {
		B.read((char*)&second_number, sizeof(int));
		if (B.eof())
			break;
		A.read((char*)&first_number, sizeof(int));
		long long valueA = 0, valueB = 0;

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

	file_out.close();
	A.close();
	B.close();
}

ModifiedSort::ModifiedSort(string name) : Sort(name), num_of_chunks(0) {
	this->sequence_size = BUFF_SIZE;
}

void ModifiedSort::modified_sort() {
	pre_sort();

	Timer tim;

	for (; sequence_size < file_size; sequence_size *= 2) {
		mod_split();
		merge();
	}

	cout << "Зовнішнє сортування заняло " << tim.elapsed() << endl;
	test();
}

void ModifiedSort::pre_sort() {
	ifstream file(FOLDER_NAME + file_name, ios::binary);
	ofstream copy(FOLDER_NAME + COPY_FILE, ios::binary);

	num_of_chunks = file_size / BUFF_SIZE;

	Timer t;

	for (int i = 0; i < num_of_chunks; i++) {
		file.read((char*)&buff, BUFF_SIZE * 4);
		sort(buff, buff + BUFF_SIZE);
		copy.write((char*)&buff, BUFF_SIZE * 4);
	}

	cout << "Внутрішнє сортування заняло " << t.elapsed() << endl;

	file.close();
	copy.close();
}

void ModifiedSort::mod_split() {
	ifstream file_out(FOLDER_NAME + COPY_FILE, ios::binary);
	ofstream B(FOLDER_NAME + FIRST_FILE, ios::binary);
	ofstream C(FOLDER_NAME + SECOND_FILE, ios::binary);

	bool flag = true;
	long long value = 0;

	for (int i = 0; i < num_of_chunks; i++) {
		if (flag) {
			file_out.read((char*)&buff, sizeof(buff));
			B.write((char*)&buff, sizeof(buff));
			value += BUFF_SIZE;
			if (value >= sequence_size) {
				flag = false;
				value = 0;
			}
		}
		else {
			file_out.read((char*)&buff, sizeof(buff));
			C.write((char*)&buff, sizeof(buff));
			value += BUFF_SIZE;
			if (value >= sequence_size) {
				flag = true;
				value = 0;
			}
		}
	}
	B.close();
	C.close();
	file_out.close();
}

void ModifiedSort::merge() {
	ofstream clear(FOLDER_NAME + COPY_FILE, ios::binary);
	clear.close();
	ifstream A(FOLDER_NAME + FIRST_FILE, ios::binary);
	ifstream B(FOLDER_NAME + SECOND_FILE, ios::binary);
	int first_number; int second_number;

	while (true) {
		B.read((char*)&second_number, sizeof(int));
		if (B.eof())
			break;
		A.read((char*)&first_number, sizeof(int));
		long long valueA = 0, valueB = 0;
		int index = 0;
		
		while (valueA != sequence_size && valueB != sequence_size) {
			if (first_number < second_number) {
				flush(index);
				buff[index] = first_number;
				valueA++; index++;
				if (valueA != sequence_size)
					A.read((char*)&first_number, sizeof(int));
			}
			else {
				flush(index);
				buff[index] = second_number;
				valueB++; index++;
				if (valueB != sequence_size)
					B.read((char*)&second_number, sizeof(int));
			}
		}
		if (valueA > valueB) {
			flush(index);
			buff[index] = second_number;
			valueB++; index++;
			flush(index);
			while (valueB < sequence_size) {
				B.read((char*)&second_number, sizeof(int));
				if (B.eof())
					break;
				flush(index);
				buff[index] = second_number;
				valueB++; index++;
			}

		}
		else if (valueA < valueB) {
			flush(index);
			buff[index] = first_number;
			valueA++; index++;
			flush(index);
			while (valueA < sequence_size) {
				A.read((char*)&first_number, sizeof(int));
				if (A.eof())
					break;
				flush(index);
				buff[index] = first_number;
				valueA++; index++;
			}
		}
	}

	A.close();
	B.close();
}

void ModifiedSort::flush(int& index) {
	if (index + 1 > sequence_size) {
		ofstream file_out(FOLDER_NAME + COPY_FILE, ios::binary | ios::app);
		file_out.seekp(0, ios::end);
		file_out.write((char*)&buff, sizeof(int) * BUFF_SIZE);
		file_out.close();
		index = 0;
	}
}