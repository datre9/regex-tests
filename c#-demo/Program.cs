using System.Diagnostics;
using System.Text;
using System.Text.RegularExpressions;


StreamReader sr = new StreamReader("../../../../adventures-of-huckleberry-finn.txt");
string s = sr.ReadToEnd();
sr.Close();

StringBuilder toWrite = new StringBuilder("id;time(ns);memory(B)\n");

//Process process = Process.GetCurrentProcess();

Regex.CacheSize = 0;
Regex regex = new Regex("finn|huckleberry", RegexOptions.IgnoreCase);

for (int i = 0; i < 100; i++) {
	GC.Collect();
	GC.WaitForPendingFinalizers();
	long startMemory = GC.GetTotalMemory(true);
	long startTime = DateTime.Now.Ticks;

	regex.Matches(s);

	long endTime = DateTime.Now.Ticks;
	long endMemory = GC.GetTotalMemory(true);

	toWrite.Append(i).Append(";").Append((endTime - startTime) * 100).Append(";").Append(endMemory - startMemory).Append("\n");
}

Console.WriteLine(toWrite);