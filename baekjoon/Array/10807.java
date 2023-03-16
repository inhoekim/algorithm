import java.io.*;
import java.util.*;
public class Anything {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        StringTokenizer st = new StringTokenizer(br.readLine(), " ");
        int target_n = Integer.parseInt(br.readLine());
        int[] nums = new int[201];
        Arrays.fill(nums, 0);
        while (st.hasMoreTokens())
            nums[Integer.parseInt(st.nextToken()) + 100] ++;
        System.out.println(nums[target_n + 100]);
    }
}
