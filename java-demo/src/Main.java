import java.io.FileWriter;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    static StringBuilder toWrite = new StringBuilder();

    public static void main(String[] args) throws IOException {
        String abc1 = GetStringFromFile.getStringFromFile("../abc1.txt");
        String abc2 = GetStringFromFile.getStringFromFile("../abc2.txt");
        String abc3 = GetStringFromFile.getStringFromFile("../abc3.txt");

        Pattern regexKMP = Pattern.compile("(ab)+", 0);
        Pattern regexAC = Pattern.compile("ac|aca|cab|ab", 0);
        Pattern regexSS = Pattern.compile("(a|b)(b|c)", 0);
        Pattern regexWC = Pattern.compile("a..b..c..", 0);
        Pattern regexNE = Pattern.compile("d", 0);


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


        FileWriter myWriter = new FileWriter("java_results.csv");
        myWriter.write(toWrite.toString());
        myWriter.close();
    }

    static void benchmark(String text, Pattern pattern, String title) {
        toWrite.append(title).append("\n");

        for (int i = 0; i < 1000; i++) {
            long startTime = System.nanoTime();

            Matcher matcher = pattern.matcher(text);
            while(matcher.find()) {
            }

            long endTime = System.nanoTime();

            toWrite.append((double)(endTime - startTime) / 1000000).append("\n");
        }
    }
}