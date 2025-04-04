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

        double elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
        toWrite << elapsed / 1000000 << "\n";
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

    regex regexKMP("abacab");
    regex regexAC("ac|aca|cab|ab");
    regex regexSS("(a|b)(b|c)");
    regex regexWC("a..b..c..");


    benchmark(abc1, regexKMP, "KMP1");
    benchmark(abc2, regexKMP, "KMP2");
    benchmark(abc3, regexKMP, "KMP3");

    benchmark(abc1, regexAC, "AC1");
    benchmark(abc2, regexAC, "AC2");
    benchmark(abc3, regexAC, "AC3");
    
    benchmark(abc1, regexSS, "SS1");
    benchmark(abc2, regexSS, "SS2");
    benchmark(abc3, regexSS, "SS3");
    
    benchmark(abc1, regexWC, "WC1");
    benchmark(abc2, regexWC, "WC2");
    benchmark(abc3, regexWC, "WC3");


	ofstream f2("c++_results.csv");
	f2 << toWrite.str();
	f2.close();

	return 0;
}