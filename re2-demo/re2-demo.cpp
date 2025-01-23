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

int main() {
    string abc1 = readFile("../abc1.txt");
    string abc2 = readFile("../abc2.txt");
    string abc3 = readFile("../abc3.txt");

    RE2 regexKMP("(ab)+");
    RE2 regexAC("ac|aca|cab|ab");
    RE2 regexSS("(a|b)(b|c)");
    RE2 regexWC("a..b..c..");
    RE2 regexNE("d");


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

    benchmark(abc1, regexNE, "NE1");
    benchmark(abc2, regexNE, "NE2");
    benchmark(abc3, regexNE, "NE3");


    ofstream f2("re2_results.csv");
    f2 << toWrite.str();
    f2.close();

    return 0;
}