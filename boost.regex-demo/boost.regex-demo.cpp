#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <boost/regex.hpp>
#include <chrono>

using namespace std;

int main()
{
    ifstream f("../adventures-of-huckleberry-finn.txt");
    string s;
    ostringstream ss;
    ss << f.rdbuf();
    s = ss.str();
    f.close();
    boost::regex pattern("Finn|Huckleberry");

    stringstream toWrite;
    toWrite << "id;time(ns);memory(B)\n";

    for (int i = 0; i < 1000; i++) {
        auto start = chrono::high_resolution_clock::now();

        boost::sregex_iterator iter(s.begin(), s.end(), pattern);
        boost::sregex_iterator end;
        for (; iter != end; ++iter) { }

        auto finish = chrono::high_resolution_clock::now();

        auto elapsed = chrono::duration_cast<chrono::nanoseconds>(finish - start).count();
        toWrite << i << ";" << elapsed << ";" << 0 << "\n";
    }

    ofstream f2("results.csv");
    f2 << toWrite.str();
    f2.close();

    return 0;
}