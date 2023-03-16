import java.io.*;
import java.util.*;
public class Anything {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] inputs = br.readLine().split("");
        int[] ascii = new int[255];
        Arrays.fill(ascii, 0);
        for (String ch : inputs)
            ascii[ch.charAt(0) - '0']++;

        for (int i = 'a'; i <= 'z'; i++){
            System.out.print(ascii[i - '0']);
            if (i != 'z')
                System.out.print(" ");
        }
        System.out.println("");
    }
}
