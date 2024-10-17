import java.io.FileWriter;
import java.io.IOException;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    public static void main(String[] args) throws IOException {
        String string = GetStringFromFile.getStringFromFile("../adventures-of-huckleberry-finn.txt");
        StringBuilder toWrite = new StringBuilder("id;time(ns);memory(B)\n");
        //used for getting current RAM usage
        Runtime runtime = Runtime.getRuntime();

        Pattern pattern = Pattern.compile("Finn|Huckleberry", 0);

        //number of test repeats
        for (int i = 0; i < 1000; i++) {
            //garbage collector to avoid wierd data
            runtime.gc();
            long startMemory = runtime.totalMemory() - runtime.freeMemory();
            long startTime = System.nanoTime();

            Matcher matcher = pattern.matcher(string);
            while(matcher.find()) {
            }

            long endTime = System.nanoTime();
            long endMemory = runtime.totalMemory() - runtime.freeMemory();

            toWrite.append(i).append(";").append(endTime - startTime).append(";").append(endMemory - startMemory).append("\n");
        }

        FileWriter myWriter = new FileWriter("results.csv");
        myWriter.write(toWrite.toString());
        myWriter.close();
    }
}