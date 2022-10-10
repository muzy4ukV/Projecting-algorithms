#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <random>
#include <Windows.h>
#include <algorithm>
#include <chrono>


using namespace std;

const string FOLDER_NAME = "files/";
const string FIRST_FILE = "B.bin";
const string SECOND_FILE = "C.bin";
const string COPY_FILE = "out.bin";
const int BUFF_SIZE = 67108864/4;
const int NUMBER_OF_READ = 1000;

string generate_file();
void file_output(string name);
void file_sort(string file_name);
long long get_size(string name);
void copy_file(string name, int file_size);
void merge(string file_name, long long sequence_size, long long size);
void split(string name, long long sequence_size);
