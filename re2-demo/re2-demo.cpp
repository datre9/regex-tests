#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <re2/re2.h>

using namespace std;

int main() {
    ifstream f("../adventures-of-huckleberry-finn.txt");
    string s;
    ostringstream ss;
    ss << f.rdbuf();
    s = ss.str();
    f.close();
    string pattern = R"((Finn|Huckleberry))";

    stringstream toWrite;
    toWrite << "id;time(ns);memory(B)\n";

    RE2 re(pattern);
    re2::StringPiece input(s);

    for (int i = 0; i < 1000; i++) {
        re2::StringPiece input(s);

        auto start = chrono::high_resolution_clock::now();

        while (RE2::FindAndConsume(&input, re)) {
        }

        auto finish = chrono::high_resolution_clock::now();

        auto elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
        toWrite << i << ";" << elapsed << ";" << 0 << "\n";
    }

    ofstream f2("results.csv");
    f2 << toWrite.str();
    f2.close();

    return 0;
}