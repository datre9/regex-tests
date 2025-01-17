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


		Benchmark(abc1, regexKMP, "KMP1");
		Benchmark(abc2, regexKMP, "KMP2");
		Benchmark(abc3, regexKMP, "KMP3");


		StreamWriter sw = new StreamWriter("../../../results.csv");
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

			toWrite.Append(sw.ElapsedTicks * 100).Append("\n");
		}
	}
}