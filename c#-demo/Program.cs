using System.Text;
using System.Text.RegularExpressions;


StreamReader sr = new StreamReader("../../../../adventures-of-huckleberry-finn.txt");
string s = sr.ReadToEnd();
sr.Close();

StringBuilder toWrite = new StringBuilder("id;time(ns);memory(B)\n");

Regex regex = new Regex("finn|huckleberry", RegexOptions.IgnoreCase);

for (int i = 0; i < 1000; i++) {
	long startMemory = GC.GetTotalMemory(true);
	long startTime = DateTime.Now.Ticks;

	//.Matches possibly has some cache that greatly reduces the compute time by orders of magnitude
	//the first value of memory seems to be correct, the others are always incorrect
	//regex.Matches(s);
	regex.Count(s);

	long endTime = DateTime.Now.Ticks;
	long endMemory = GC.GetTotalMemory(true);

	toWrite.Append(0).Append(";").Append((endTime - startTime) * 100).Append(";").Append(endMemory - startMemory).Append("\n");
}

StreamWriter sw = new StreamWriter("../../../results.csv");
sw.WriteLine(toWrite);
sw.Close();