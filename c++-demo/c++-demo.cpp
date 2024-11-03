#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <chrono>
#include <windows.h>
#include <psapi.h>

using namespace std;

size_t getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize;
    }
    return 0;
}

int main()
{
    ifstream f("../adventures-of-huckleberry-finn.txt");
    string s;
    ostringstream ss;
    ss << f.rdbuf();
    s = ss.str();
    f.close();
    regex pattern("Finn|Huckleberry");

    stringstream toWrite;
    toWrite << "id;time(ns);memory(B)\n";

    for (int i = 0; i < 100; i++) {
        size_t memoryBefore = getMemoryUsage();
        auto start = chrono::high_resolution_clock::now();

        sregex_iterator begin(s.begin(), s.end(), pattern);
        sregex_iterator end;
        for (auto it = begin; it != end; ++it) {}

        auto finish = chrono::high_resolution_clock::now();
        size_t memoryAfter = getMemoryUsage();

        auto elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
        size_t memoryUsed = memoryAfter - memoryBefore;

        toWrite << i << ";" << elapsed << ";" << memoryUsed << "\n";
    }

	ofstream f2("results.csv");
	f2 << toWrite.str();
	f2.close();

	return 0;
}