using System.Diagnostics;
using System.Text;
using System.Text.RegularExpressions;


class Program {
	static StringBuilder toWrite = new StringBuilder("");

	static void Main(string[] args) {
		StreamReader sr = new StreamReader("../../../../abc1.txt");
		string abc1 = sr.ReadToEnd();
		sr = new StreamReader("../../../../abc2.txt");
		string abc2 = sr.ReadToEnd();
		sr = new StreamReader("../../../../abc3.txt");
		string abc3 = sr.ReadToEnd();
		sr.Close();

		Regex regexKMP = new Regex("(ab)+", RegexOptions.Compiled);
		Regex regexAC = new Regex("ac|aca|cab|ab", RegexOptions.Compiled);
		Regex regexSS = new Regex("(a|b)(b|c)", RegexOptions.Compiled);
		Regex regexWC = new Regex("a..b..c..", RegexOptions.Compiled);
		Regex regexNE = new Regex("d", RegexOptions.Compiled);


		Benchmark(abc1, regexKMP, "KMP1");
		Benchmark(abc2, regexKMP, "KMP2");
		Benchmark(abc3, regexKMP, "KMP3");

		Benchmark(abc1, regexAC, "AC1");
		Benchmark(abc2, regexAC, "AC2");
		Benchmark(abc3, regexAC, "AC3");
		
		Benchmark(abc1, regexSS, "SS1");
		Benchmark(abc2, regexSS, "SS2");
		Benchmark(abc3, regexSS, "SS3");
		
		Benchmark(abc1, regexWC, "WC1");
		Benchmark(abc2, regexWC, "WC2");
		Benchmark(abc3, regexWC, "WC3");
		
		Benchmark(abc1, regexNE, "NE1");
		Benchmark(abc2, regexNE, "NE2");
		Benchmark(abc3, regexNE, "NE3");


		StreamWriter sw = new StreamWriter("../../../c#_results.csv");
		sw.WriteLine(toWrite);
		sw.Close();
	}

	static void Benchmark(string text, Regex regex, string title) {
		toWrite.Append(title).Append("\n");

		for (int i = 0; i < 1000; i++) {
			Match match = regex.Match(text);

			Stopwatch sw = Stopwatch.StartNew();

			while (match.Success) {
				match = match.NextMatch();
			}

			sw.Stop();

			toWrite.Append((double)sw.ElapsedTicks / 10000).Append("\n");
		}
	}
}