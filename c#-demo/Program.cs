using System.Text;
using System.Text.RegularExpressions;


StreamReader sr = new StreamReader("../../../../adventures-of-huckleberry-finn.txt");
string s = sr.ReadToEnd();
sr.Close();

StringBuilder toWrite = new StringBuilder("id;time(ns);memory(B)\n");

Regex regex = new Regex("Finn|Huckleberry", 0);

for (int i = 0; i < 1000; i++) {
	Match match = regex.Match(s);

	long startMemory = GC.GetTotalMemory(true);
	long startTime = DateTime.Now.Ticks;

	while (match.Success) {
		match = match.NextMatch();
	}

	long endTime = DateTime.Now.Ticks;
	long endMemory = GC.GetTotalMemory(true);

	toWrite.Append(i).Append(";").Append((endTime - startTime) * 100).Append(";").Append(endMemory - startMemory).Append("\n");
}

StreamWriter sw = new StreamWriter("../../../results.csv");
sw.WriteLine(toWrite);
sw.Close();