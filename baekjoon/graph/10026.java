import java.util.*;
import java.io.*;
import java.util.stream.*;

public class Anything{
	static boolean visited_arr[][][];
	static boolean visited[][];
	static boolean visited_odd[][];
	static ArrayList<ArrayList<Character>> paint;
	static int n;
	static int directions[][] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	public static void main (String[] argvs) throws IOException{
		//입력 part
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		n = Integer.parseInt(br.readLine());
		paint = Stream.generate(() -> Stream.generate(()-> '\0').limit(n).collect(Collectors.toCollection(ArrayList::new)))
				.limit(n).collect(Collectors.toCollection(ArrayList::new));
		for (int y = 0; y < n; y++) {
			String input = br.readLine();
			int x = 0;
			for (char ch : input.toCharArray()) {
				paint.get(y).set(x, ch);
				x++;
			}
		}
		visited = new boolean [n][n];
		visited_odd = new boolean [n][n];
		for (int i = 0; i < n; i++) {
			Arrays.fill(visited[i], false);
			Arrays.fill(visited_odd[i], false);
		}
		visited_arr = new boolean[][][]{visited, visited_odd};
		int normal = 0;
		int odd = 0;
		//dfs 호출
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				if (!visited[y][x])
					normal += dfs(y, x, 0);
				if (!visited_odd[y][x])
					odd += dfs(y, x, 1);
			}
		}
		//출력 part
		System.out.println(normal + " " + odd);
	}

	public static int dfs(int y, int x, int is_odd) {
		visited_arr[is_odd][y][x] = true;
		char color = paint.get(y).get(x);
		for (int i = 0; i < 4; i++) {
			int next_y = y + directions[i][0];
			int next_x = x + directions[i][1];
			if (next_x < 0 || next_x == n || next_y < 0 || next_y == n || visited_arr[is_odd][next_y][next_x])
				continue;
			//다음칸이 현재칸과 색깔이 경우만 방문(단 적록색약인 경우는 제외)
			if (paint.get(next_y).get(next_x) != color && !(is_odd == 1 && (color == 'R' || color == 'G') && paint.get(next_y).get(next_x) != 'B') )
				continue;
			dfs(next_y, next_x, is_odd);
		}
		return (1);
	}
}
