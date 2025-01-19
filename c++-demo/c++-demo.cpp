#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include <chrono>

using namespace std;

stringstream toWrite;

static void benchmark(const string& text, const regex& regex, const string& title) {
    toWrite << title << "\n";

    for (int i = 0; i < 1000; i++) {
        auto start = chrono::high_resolution_clock::now();

        sregex_iterator begin(text.begin(), text.end(), regex);
        sregex_iterator end;
        for (auto it = begin; it != end; ++it) {}

        auto finish = chrono::high_resolution_clock::now();

        auto elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();

        toWrite << elapsed << "\n";
    }
}

string readFile(const std::string& path) {
    std::ifstream f(path);
    std::ostringstream ss;
    ss << f.rdbuf();
    return ss.str();
}

int main()
{
    string abc1 = readFile("../abc1.txt");
    string abc2 = readFile("../abc2.txt");
    string abc3 = readFile("../abc3.txt");

    regex regexKMP("(ab)+");


    benchmark(abc1, regexKMP, "KMP1");
    benchmark(abc2, regexKMP, "KMP2");
    benchmark(abc3, regexKMP, "KMP3");


	ofstream f2("results.csv");
	f2 << toWrite.str();
	f2.close();

	return 0;
}