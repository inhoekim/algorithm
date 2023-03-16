import java.io.*;
import java.util.*;
public class Anything {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine(), " ");
        int n = Integer.parseInt(st.nextToken());
        int k = Integer.parseInt(st.nextToken());
        int[][] students = new int[2][7]; // students[gender][grade]
        int gender, grade;
        for (int i = 0; i < n; i++) {
            st = new StringTokenizer(br.readLine(), " ");
            gender = Integer.parseInt(st.nextToken());
            grade = Integer.parseInt(st.nextToken());
            students[gender][grade]++;
        }
        int ret = 0;
        for (int i = 0; i < 2; i++)
            for (int j = 1; j < 7; j++) {
                ret += (students[i][j] / k);
                if (students[i][j] % k != 0)
                    ret += 1;
            }
        System.out.println(ret);
    }
}
