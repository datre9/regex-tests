#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <re2/re2.h>

using namespace std;

stringstream toWrite;

static void benchmark(const string& text, const RE2& regex, const string& title) {
    toWrite << title << "\n";

    for (int i = 0; i < 1000; i++) {
        re2::StringPiece input(text);

        auto start = chrono::high_resolution_clock::now();

        while (RE2::FindAndConsume(&input, regex)) {
        }

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

int main() {
    string abc1 = readFile("../abc1.txt");
    string abc2 = readFile("../abc2.txt");
    string abc3 = readFile("../abc3.txt");

    RE2 regexKMP("Finn|Huckleberry");


    benchmark(abc1, regexKMP, "KMP1");
    benchmark(abc2, regexKMP, "KMP2");
    benchmark(abc3, regexKMP, "KMP3");


    ofstream f2("results.csv");
    f2 << toWrite.str();
    f2.close();

    return 0;
}