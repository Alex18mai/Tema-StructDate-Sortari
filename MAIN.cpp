/*
	Nume: Alexandru Enache
	Grupa: 152
	Tema: Algoritmi de sortare
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

ifstream fin("input.txt"); ofstream fout("output.txt");




bool test_sort(vector < int >& v) {

	for (int i = 1; i < v.size(); i++)
		if (v[i] < v[i - 1])
			return false;
	return true;
}


void BubbleSort(int n, int MAX, vector < int > v) {

	auto start = chrono::steady_clock::now();

	if (n > 1e4) {
		fout << "N = " << n << " is too big for BubbleSort.\n";
		return;
	}

	int ok = 1;
	while (ok) {
		ok = 0;
		for (int i = 1; i < n; i++) {
			if (v[i - 1] > v[i]) {
				swap(v[i - 1], v[i]);
				ok = 1;
			}
		}
	}
	if (!test_sort(v)) {
		fout << "BubbleSort FAILED!\n";
		exit(0);
	}

	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
	fout << "BubbleSort duration: " << duration << " ms." << '\n';

	return;
}


void CountSort(int n, int MAX, vector < int > v) {

	auto start = chrono::steady_clock::now();

	if (MAX > 1e6) {
		fout << "MAX = " << MAX << " is too big for CountSort.\n";
		return;
	}
	vector < int > fv(MAX + 5, 0);

	for (int i = 0; i < n; i++) {
		fv[v[i]]++;
	}
	int idx = 0;
	for (int i = 0; i <= MAX; i++) {
		while (fv[i]) {
			v[idx] = i;
			idx++;
			fv[i]--;
		}
	}
	if (idx != n || !test_sort(v)) {
		fout << "CountSort FAILED!\n";
		exit(0);
	}

	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
	fout << "CountSort duration: " << duration << " ms." << '\n';

	return;
}


void RadixSort(int n, int MAX, vector < int > v) {

	auto start = chrono::steady_clock::now();

	if (MAX > 1e9) {
		fout << "MAX = " << MAX << " is too big for my implementation of RountSort.\n";
		return;
	}

	vector < int > fv(256, 0);
	vector < int > aux(n + 5, 0);

	for (long long bit = 0; bit < 31; bit += 8) {

		for (int i = 0; i < n; i++) {
			int nr = v[i] >> bit;
			nr &= 255;
			fv[nr]++;
		}

		for (int i = 1; i <= 255; i++) {
			fv[i] += fv[i - 1];
		}

		for (int i = n - 1; i >= 0; i--) {
			int nr = v[i] >> bit;
			nr &= 255;
			aux[fv[nr] - 1] = v[i];
			fv[nr]--;
		}

		for (int i = 0; i < n; i++) {
			v[i] = aux[i];
		}

		for (int i = 0; i <= 255; i++) {
			fv[i] = 0;
		}

	}
	if (!test_sort(v)) {
		fout << "RadixSort FAILED!\n";
		exit(0);
	}

	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
	fout << "RadixSort duration: " << duration << " ms." << '\n';

	return;
}

void recursive_merge_sort(int st, int dr, vector < int >& v) {
	if (st == dr) {
		return;
	}

	int mij = (st + dr) / 2;

	recursive_merge_sort(st, mij, v);
	recursive_merge_sort(mij + 1, dr, v);

	int ST = st, DR = mij + 1;
	vector < int > aux;

	while (ST <= mij && DR <= dr) {
		if (v[ST] < v[DR]) {
			aux.push_back(v[ST]); ST++;
		}
		else {
			aux.push_back(v[DR]); DR++;
		}
	}

	while (ST <= mij) {
		aux.push_back(v[ST]); ST++;
	}

	while (DR <= dr) {
		aux.push_back(v[DR]); DR++;
	}

	for (int i = st; i <= dr; i++) {
		v[i] = aux[i - st];
	}
}

void MergeSort(int n, int MAX, vector < int > v) {

	auto start = chrono::steady_clock::now();

	recursive_merge_sort(0, n - 1, v);
	if (!test_sort(v)) {
		fout << "MergeSort FAILED!\n";
		exit(0);
	}

	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
	fout << "MergeSort duration: " << duration << " ms." << '\n';

	return;
}


void recursive_quick_sort(vector < int >& v) {
	if (v.size() <= 1) {
		return;
	}
	int pivot = v[v.size() - 1];
	vector < int > ST, DR, MID;
	for (auto& x : v) {
		if (x < pivot)
			ST.push_back(x);
		else if (x > pivot)
			DR.push_back(x);
		else
			MID.push_back(x);
	}

	recursive_quick_sort(ST);
	recursive_quick_sort(DR);

	v.clear();
	for (auto& x : ST)
		v.push_back(x);
	for (auto& x : MID)
		v.push_back(x);
	for (auto& x : DR)
		v.push_back(x);
}

void QuickSort(int n, int MAX, vector < int > v) {

	auto start = chrono::steady_clock::now();

	recursive_quick_sort(v);
	if (!test_sort(v)) {
		fout << "QuickSort FAILED!\n";
		exit(0);
	}

	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
	fout << "QuickSort duration: " << duration << " ms." << '\n';

	return;
}


void StlSort(int n, int MAX, vector < int > v) {

	auto start = chrono::steady_clock::now();

	sort(v.begin(), v.end());

	auto end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
	fout << "StlSort duration: " << duration << " ms." << '\n';

	return;
}



int main() {

	int n, MAX;

	while (fin >> n >> MAX) {

		cout << n << " " << MAX << '\n';

		vector < int > v(n);
		for (int i = 0; i < n; i++) {
			fin >> v[i];
		}

		fout << "N = " << n << "& MAX = " << MAX << '\n';

		BubbleSort(n, MAX, v);
		CountSort(n, MAX, v);
		RadixSort(n, MAX, v);
		MergeSort(n, MAX, v);
		QuickSort(n, MAX, v);
		StlSort(n, MAX, v);
		fout << '\n';

	}

	return 0;
}