using System.Text;
using System.Text.RegularExpressions;


StreamReader sr = new StreamReader("../../../../adventures-of-huckleberry-finn.txt");
string s = sr.ReadToEnd();
sr.Close();

StringBuilder toWrite = new StringBuilder("id;time(ns);memory(B)\n");

Regex.CacheSize = 0;
Regex regex = new Regex("finn|huckleberry", RegexOptions.IgnoreCase);

GC.Collect();
GC.WaitForPendingFinalizers();
long startMemory = GC.GetTotalMemory(true);
long startTime = DateTime.Now.Ticks;

regex.Matches(s);

long endTime = DateTime.Now.Ticks;
long endMemory = GC.GetTotalMemory(true);

toWrite.Append(0).Append(";").Append((endTime - startTime) * 100).Append(";").Append(endMemory - startMemory).Append("\n");

Console.WriteLine(toWrite);