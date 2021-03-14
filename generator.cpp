/*
	Nume: Alexandru Enache 
	Grupa: 152
	Tema: Algoritmi de sortare
	
	Generator de teste
*/

#include <iostream>
#include <fstream>
#include <random>
#include <assert.h>

using namespace std;

ofstream fout("input.txt");

long long RANDOM(long long st, long long dr) {
	assert(st <= dr);
	long long now = 1LL * rand() * RAND_MAX + rand();
	now %= dr - st + 1LL;
	return st + now;
}

void test(int n, int MAX) {
	cout << n << " " << MAX << '\n';
	fout << n << " " << MAX << '\n';

	for (int i = 0; i < n; i++) {
		fout << RANDOM(0, MAX) << " ";
	}
	fout << '\n' << '\n';
}


int main() {

	test(1e3, 1e3);
	test(1e3, 1e6);
	test(1e3, 1e9);

	test(1e4, 1e3);
	test(1e4, 1e6);
	test(1e4, 1e9);

	test(1e5, 1e3);
	test(1e5, 1e6);
	test(1e5, 1e9);

	test(1e6, 1e3);
	test(1e6, 1e6);
	test(1e6, 1e9);
	
	return 0;
}