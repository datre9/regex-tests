import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class GetStringFromFile {
    public static String getStringFromFile(String filePath) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader(filePath));
        StringBuilder sb = new StringBuilder();

        while (in.readLine() != null) {
            sb.append(in.readLine()).append("\n");
        }

        in.close();

        return sb.toString();
    }
}