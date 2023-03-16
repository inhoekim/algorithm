import java.io.*;
import java.util.*;
public class Anything {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        int[] ascii = new int[256];
        int n = Integer.parseInt(br.readLine());
        boolean is_possible;
        for (int i = 0; i < n; i++){
            is_possible = true;
            Arrays.fill(ascii,0);
            st = new StringTokenizer(br.readLine(), " ");
            for (char ch : st.nextToken().toCharArray())
                ascii[ch]++;
            for (char ch : st.nextToken().toCharArray())
                ascii[ch]--;
            //possible인지 판단하는 part
            for (int j = 0; j < 256; j++){
                if (ascii[j] != 0){
                    System.out.println("Impossible");
                    is_possible = false;
                    break;
                }
            }
            if (is_possible)
                System.out.println("Possible");
        }
    }
}
