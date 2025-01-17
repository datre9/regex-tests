import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class GetStringFromFile {
    public static String getStringFromFile(String filePath) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader(filePath));
        StringBuilder sb = new StringBuilder();
        String line;

        while ((line = in.readLine()) != null) {
            sb.append(line).append("\n");
        }

        in.close();
        return sb.toString();
    }
}