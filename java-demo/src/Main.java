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


        benchmark(abc1, regexKMP, "KMP1");
        benchmark(abc2, regexKMP, "KMP2");
        benchmark(abc3, regexKMP, "KMP3");


        FileWriter myWriter = new FileWriter("results.csv");
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

            toWrite.append(endTime - startTime).append("\n");
        }
    }
}