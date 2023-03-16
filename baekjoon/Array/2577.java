import java.io.*;
import java.util.*;
public class Anything {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        long num = 1;
        int[] nums = new int[10];
        Arrays.fill(nums, 0);
        for (int i = 0; i < 3; i++)
            num *= Integer.parseInt(br.readLine());
        while (num != 0) {
            nums[(int)num % 10]++;
            num /= 10;
        }
        for(int i = 0; i < 10; i++)
            System.out.println(nums[i]);
    }
}
