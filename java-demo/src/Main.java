import java.io.FileWriter;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    public static void main(String[] args) throws IOException {
        String string = GetStringFromFile.getStringFromFile("../adventures-of-huckleberry-finn.txt");
        Runtime runtime = Runtime.getRuntime();
        StringBuilder toWrite = new StringBuilder("id;time;memory\n");

        //number of test repeats
        for (int i = 0; i < 1000; i++) {
            long startMemory = runtime.totalMemory() - runtime.freeMemory();
            long startTime = System.nanoTime();

            Pattern pattern = Pattern.compile("finn|huckleberry", Pattern.CASE_INSENSITIVE);
            //does not measure difference in memory for smaller numbers
            for (int j = 0; j < 10000; j++) {
                Matcher matcher = pattern.matcher(string);
            }

            long endTime = System.nanoTime();
            long endMemory = runtime.totalMemory() - runtime.freeMemory();
            //sometimes throws a negative number or a zero for memory
            if (endMemory - startMemory > 0) toWrite.append(i).append(";").append(endTime - startTime).append(";").append(endMemory - startMemory).append("\n");
        }

        FileWriter myWriter = new FileWriter("results.csv");
        myWriter.write(toWrite.toString());
        myWriter.close();
    }
}