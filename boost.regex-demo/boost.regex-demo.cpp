#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <boost/regex.hpp>
#include <chrono>

using namespace std;

stringstream toWrite;

static void benchmark(const string& text, const boost::regex& regex, const string& title) {
    toWrite << title << "\n";

    for (int i = 0; i < 1000; i++) {
        auto start = chrono::high_resolution_clock::now();

        boost::sregex_iterator iter(text.begin(), text.end(), regex);
        boost::sregex_iterator end;
        for (; iter != end; ++iter) { }

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

    boost::regex regexKMP("(ab)+");
    boost::regex regexAC("ac|aca|cab|ab");
    boost::regex regexSS("(a|b)(b|c)");
    boost::regex regexWC("a..b..c..");
    boost::regex regexNE("d");


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


    ofstream f2("boost_results.csv");
    f2 << toWrite.str();
    f2.close();

    return 0;
}