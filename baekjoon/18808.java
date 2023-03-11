import java.io.*;
import java.util.*;
import java.util.stream.*;

public class Algorithm {
    public final static int EMPTY = 0;
    public static int n, m, k;
    public static BufferedReader br;
    public static StringTokenizer st;
    public static ArrayList<ArrayList<Integer>> macbook_arr;
    public static ArrayList<Sticker> stickers;
    public static int ret;
    
    public static void main(String[] args) throws IOException {
        br = new BufferedReader(new InputStreamReader(System.in));
        st = new StringTokenizer(br.readLine());
        n = Integer.parseInt(st.nextToken());
        m = Integer.parseInt(st.nextToken());
        k = Integer.parseInt(st.nextToken());

        macbook_arr = Stream.generate(() ->
                Stream.generate(() -> 0).limit(m).collect(Collectors.toCollection(ArrayList::new)))
                .limit(n).collect(Collectors.toCollection(ArrayList::new));
        stickers = dispose_stickers();

        ret = 0;
        init_paste();
        System.out.println(ret);
    }
    public static ArrayList<Sticker> dispose_stickers() throws IOException{
        int col, row;
        ArrayList<Sticker> stickers = new ArrayList<>();
        for (int i = 0; i < k; i++) {
            st = new StringTokenizer(br.readLine());
            col = Integer.parseInt(st.nextToken());
            row = Integer.parseInt(st.nextToken());
            Sticker sticker = new Sticker(col, row);
            for (int y = 0; y < col; y++) {
                st = new StringTokenizer(br.readLine());
                for (int x = 0; x < row; x++)
                    sticker.fill_arr(y, x, Integer.parseInt(st.nextToken()));
            }
            stickers.add(sticker);
        }
        return stickers;
    }

    public static void init_paste(){
        for(Sticker sticker : stickers) {
            for(int ver = 0; ver < 4; ver++) {
                sticker.rotate_arr(ver);
                // 스티커가 노트북보다 크면 그냥 건너뜀
                if (sticker.col > n || sticker.row > m)
                    continue;
                //모든 노트북 맵을 순회하면서 현재 스티커를 붙일 수 있을지를 check하고 paste하는 작업을 실시.
                if (check_and_paste(sticker, ver))
                    break;
            }
        }
    }

    public static boolean check_and_paste(Sticker sticker, int ver) {
        ArrayList<ArrayList<Integer>> sticker_arr = sticker.get_sticker_arr(ver);
        //모든 노트북 맵을 순회하면서 스티커를 위치시킬 첫번째 자리를 탐색
        for (int y = 0; y < n; y++) {
            for (int x = 0; x < m; x++) {
                //스티커가 노트북 맵을 초과하는 상황이면 더이상 검사하지 않고 다음 좌표에서 재검사
                if (sticker.col + y > n || sticker.row + x > m)
                    continue;
                //실제로 스티커를 노트북 맵에 올려보면서 잘 들어갈 수 있는지 검사하는 part. 실패하면 다음 좌표에서 재검사
                int s_y = 0;
                int s_x = 0;
                boolean check_is_fail = false;
                while (s_y < sticker.col && !check_is_fail){
                    s_x = 0;
                    while (s_x < sticker.row) {
                        if (sticker_arr.get(s_y).get(s_x) != EMPTY) {
                            if (macbook_arr.get(y + s_y).get(x + s_x) != EMPTY) {
                                check_is_fail = true;
                                break;
                            }
                        }
                        s_x++;
                    }
                    s_y++;
                }
                //while문이 다 돌때까지 fail이 뜨지 않았다는 것은 스티커를 온전히 노트북에 붙일 수 있는 자리를 찾았다는 것이기에 복사 시작
                if (!check_is_fail){
                    proceed_paste(sticker_arr, y, x);
                    return true;
                }
            }
        }
        return false;
    }

    public static void proceed_paste(ArrayList<ArrayList<Integer>> sticker_arr, int map_col, int map_row){
        for (int y = 0; y < sticker_arr.size(); y++) {
            for (int x = 0; x < sticker_arr.get(0).size(); x++) {
                if (sticker_arr.get(y).get(x) != EMPTY) {
                    macbook_arr.get(map_col + y).set(map_row + x, 1);
                    ret++;
                }
            }
        }
    }
}

class Sticker {
    ArrayList<ArrayList<Integer>> arr;
    ArrayList<ArrayList<Integer>> rotated_arr;
    ArrayList<ArrayList<ArrayList<Integer>>> version = new ArrayList<>();
    int col, row;

    public Sticker(int col, int row) {
        this.col = col;
        this.row = row;

        arr = Stream.generate(() ->
                Stream.generate(() -> 0).limit(row).collect(Collectors.toCollection(ArrayList::new))
        ).limit(col).collect(Collectors.toCollection(ArrayList::new));

        rotated_arr = Stream.generate(() ->
                        Stream.generate(() -> 0).limit(col).collect(Collectors.toCollection(ArrayList::new)))
                .limit(row).collect(Collectors.toCollection(ArrayList::new));

        version.add(arr);
        version.add(rotated_arr);
    }

    public void fill_arr(int y, int x, int area) {
        this.arr.get(y).set(x, area);
    }

    public void rotate_arr(int ver) {
        if (ver == 0)
            return ;
        int temp = this.col;
        this.col = this.row;
        this.row = temp;

        ver %= 2;
        ArrayList<ArrayList<Integer>> after_arr = this.version.get(ver);
        ArrayList<ArrayList<Integer>> before_arr = this.version.get((ver + 1) % 2);
        
        for (int y = 0; y < col; y++) {
            for (int x = 0; x < row; x++) {
                int target = before_arr.get(this.row - 1 - x).get(y);
                after_arr.get(y).set(x, target);
            }
        }
    }

    public ArrayList<ArrayList<Integer>> get_sticker_arr(int ver) {return this.version.get(ver % 2);}
}
