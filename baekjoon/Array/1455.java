import java.io.*;
import java.util.*;
public class Anything {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String input = br.readLine();
        int[] nums = new int[10];
        Arrays.fill(nums, 0);
        for (char ch : input.toCharArray())
            nums[ch - '0']++;

        int max_num = -1;
        for (int i = 0; i < nums.length; i++) {
            //6과 9에 대한 값 계산은 따로 처리
            if (i == 6 || i == 9)
                continue;
            if (nums[i] > max_num)
                max_num = nums[i];
        }
        // 6과 9에 대한 플라스틱 숫자 계산을 처리
        int remain_6_9 = Math.max(nums[6], nums[9]) - Math.min(nums[6], nums[9]);
        int temp_max = Math.min(nums[6], nums[9]) + remain_6_9 / 2 + remain_6_9 % 2;
        System.out.println(Math.max(max_num, temp_max));
    }
}
