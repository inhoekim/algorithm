import java.io.*;
import java.util.*;
import java.util.stream.*;


class Anything {
    static int ret = Integer.MIN_VALUE;
    static ArrayList<ArrayList<Integer>> block_map;
    static int n;
    public static void get_ret_recur(int depth){
        /* 종료조건 */
        if (depth == 5) {
            ret = Math.max(ret, get_current_ret());
            return;
        }
        /* 경우의 수를 전부 시도해보는 part */
        for (int rotate = 0; rotate < 4; rotate++){
            if (rotate != 0)
                rotate_map();
            /* 복사본 map 만들기 (깊은복사) */
            ArrayList<ArrayList<Integer>> temp_map = (ArrayList<ArrayList<Integer>>)block_map.clone();
            for (int i = 0; i < temp_map.size(); i++)
                temp_map.set(i, (ArrayList<Integer>)block_map.get(i).clone());
            move_block();
            get_ret_recur(depth + 1);
            block_map = temp_map;
        }
    }

    public static void move_block(){
        Queue<Integer> queue = new LinkedList<Integer>();
        int target_block, idx;
        for (int y = 0; y < n; y++){
            target_block = 0;
            for (int x = 0; x < n; x++){
                if (target_block == 0 && block_map.get(y).get(x) != 0)
                    target_block = block_map.get(y).get(x);
                else if (target_block != 0 && block_map.get(y).get(x) == target_block) {
                    queue.add(target_block * 2);
                    target_block = 0;
                }else if (target_block != 0 && block_map.get(y).get(x) != 0 && block_map.get(y).get(x) != target_block) {
                    queue.add(target_block);
                    target_block = block_map.get(y).get(x);
                }
            }
            if (target_block != 0)
                queue.add(target_block);
            idx = 0;
            while (idx < n) {
                if (!queue.isEmpty())
                    block_map.get(y).set(idx, queue.poll());
                else
                    block_map.get(y).set(idx, 0);
                idx++;
            }
        }
    }
    /* block_map을 회전시키는 방식으로 풀었음. 이렇게 하면 map 탐색할때 인덱스 계산 매우 편해짐. */
    public static void rotate_map()
    {
        ArrayList<ArrayList<Integer>> rotated_map = Stream.generate(()->
                                                    Stream.generate(() -> 0).limit(n).collect(Collectors.toCollection(ArrayList::new)))
                                                    .limit(n).collect(Collectors.toCollection(ArrayList::new));
        for (int y = 0; y < n; y++)
            for (int x = 0; x < n; x++)
                rotated_map.get(y).set(x, block_map.get(n - x - 1).get(y));
        block_map = rotated_map;
    }

    public static int get_current_ret(){
        int temp_ret = -1;
        for (int y = 0; y < block_map.size(); y++)
            for (int x = 0; x < block_map.size(); x++)
                temp_ret = Math.max(temp_ret, block_map.get(y).get(x));
        return temp_ret;
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        n = Integer.parseInt(br.readLine());
        block_map = Stream.generate(
                        ()-> Stream.generate(()-> 1).limit(n).collect(Collectors.toCollection(ArrayList::new)))
                .limit(n).collect(Collectors.toCollection(ArrayList::new));
        for (int i = 0; i < n; i++){
            st = new StringTokenizer(br.readLine()," ");
            for (int j = 0; j < n; j++)
                block_map.get(i).set(j, Integer.parseInt(st.nextToken()));
        }
        get_ret_recur(0);
        System.out.println(ret);
    }

}
