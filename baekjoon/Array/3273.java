import java.io.*;
import java.util.*;
public class Anything {

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(br.readLine());
        StringTokenizer st = new StringTokenizer(br.readLine(), " ");
        int target_num = Integer.parseInt(br.readLine());
        int num, ret;
        HashMap<Integer, Boolean> map = new HashMap<>();
        ret = 0;
        while (st.hasMoreElements()) {
            num = Integer.parseInt(st.nextToken());
            if (map.containsKey(num)) {
                ret++;
            } else
                map.put(target_num - num, true);
        }
        System.out.println(ret);
    }
}
