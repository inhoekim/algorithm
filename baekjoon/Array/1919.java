import java.io.*;
import java.util.*;
public class Anything {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String a = br.readLine();
        String b = br.readLine();
        int[] ascii_a = new int[256];
        int[] ascii_b = new int[256];

        for (char ch : a.toCharArray())
            ascii_a[ch]++;
        for (char ch : b.toCharArray())
            ascii_b[ch]++;

        int ret = 0;
        for (int i = 0; i < 256; i++)
            ret+= Math.abs(ascii_a[i] - ascii_b[i]);

        System.out.println(ret);
    }
}
