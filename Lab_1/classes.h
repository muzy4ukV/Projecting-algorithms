#pragma once
#include "config.h"

class Sort {
protected:
	string file_name;
	long long file_size;
	long long sequence_size;
public:
	Sort(string name);
	long long get_size();
	void test();
};

class BasicSort : public Sort {
public:
	BasicSort(string name);
	void copy_file();
	void basic_sort();
	void split();
	void merge();
};

class ModifiedSort : public Sort {
	int num_of_chunks;
public:
	ModifiedSort(string name);
	void modified_sort();
	void pre_sort();
	void mod_split();
	void merge();
	void flush(int& index);
};


class Timer
{
private:
	using clock_t = chrono::high_resolution_clock;
	using second_t = chrono::duration<double, ratio<1> >;

	chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};