import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    public static void main(String[] args) throws IOException {
        String string = GetStringFromFile.getStringFromFile("../adventures-of-huckleberry-finn.txt");

        Runtime runtime = Runtime.getRuntime();

        long startMemory = runtime.totalMemory() - runtime.freeMemory();
        long startTime = System.nanoTime();

        Pattern pattern = Pattern.compile("finn|huckleberry", Pattern.CASE_INSENSITIVE);
        for (int i = 0; i < 10000; i++) {
            Matcher matcher = pattern.matcher(string);
        }

        long endTime = System.nanoTime();
        long endMemory = runtime.totalMemory() - runtime.freeMemory();

        System.out.println(endTime - startTime + " ns");
        System.out.println(endMemory - startMemory + " B");
    }
}