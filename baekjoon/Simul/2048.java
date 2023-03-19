package mypack;

import java.io.*;
import java.util.*;
import java.util.stream.*;


class Monitoring {
    static int[][] directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; //상하좌우순
    static int ret = Integer.MIN_VALUE;
    static ArrayList<ArrayList<Integer>> block_map;

    public static void get_ret_recur(int depth){
        /* 종료조건 */
        if (depth == 5)
            return ;
        /* 복사본 map 만들기 (깊은복사) */
        ArrayList<ArrayList<Integer>> temp_map = (ArrayList<ArrayList<Integer>>)block_map.clone();
        for (int i = 0; i < temp_map.size(); i++)
            temp_map.set(i, (ArrayList<Integer>)block_map.get(i).clone());
        /* 경우의 수를 전부 시도해보는 part */
        for(int direct = 0; direct < 4; direct++){

            get_ret_recur(depth + 1);
            block_map = temp_map;
        }
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        int n = Integer.parseInt(br.readLine());
        block_map = Stream.generate(
                ()-> Stream.generate(()-> 1).limit(n).collect(Collectors.toCollection(ArrayList::new)))
                .limit(n).collect(Collectors.toCollection(ArrayList::new));
        for (int i = 0; i < n; i++){
            st = new StringTokenizer(br.readLine()," ");
            for (int j = 0; j < n; j++)
                block_map.get(i).set(j, Integer.parseInt(st.nextToken()));
        }

        get_ret(0);
        System.out.println(ret);
    }

}

