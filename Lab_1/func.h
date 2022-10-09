#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <random>
#include <Windows.h>


using namespace std;

const string FOLDER_NAME = "files/";
const string FIRST_FILE = "B.bin";
const string SECOND_FILE = "C.bin";
const string COPY_FILE = "out.bin";
const int BUFF_SIZE = 26214400;
const int NUMBER_OF_READ = 1000;

string generate_file();
void file_output(string name);
void sort(string file_name);
int get_size(string name);
void copy_file(string name, int file_size);
void merge(string file_name, int sequence_size, int size);
void split(string name, int sequence_size);
