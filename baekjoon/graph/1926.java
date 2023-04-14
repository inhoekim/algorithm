import java.util.*;
import java.util.stream.*;
import java.io.*;

public class Anything {

	static ArrayList<ArrayList<Integer>> map;
	static int directions[][] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
	static boolean visited[];
	static int n,m;
	public static void  main(String args[]) throws IOException {
		//입출력 part
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		map = Stream.generate(() -> Stream.generate(() -> 0).limit(m).collect(Collectors.toCollection(ArrayList::new)))
				.limit(n).collect(Collectors.toCollection(ArrayList::new));
		visited = new boolean[n * m];
		Arrays.fill(visited, false);
		for (int y = 0; y < n; y++) {
			st = new StringTokenizer(br.readLine(), " ");
			for (int x = 0; x < m; x++) {
				map.get(y).set(x, Integer.parseInt(st.nextToken()));
			}
		}
		int max_area = 0;
		int paint_cnt = 0;
		//dfs
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < m; x++)
				if (!visited[y * m + x] && map.get(y).get(x) == 1) {
					paint_cnt++;
					max_area = Integer.max(max_area, dfs(y, x));
				}
		}
		//출력 part
		System.out.println(paint_cnt);
		System.out.println(max_area);
	}

	static int dfs(int y, int x) {
		int area = 1;
		visited[y * m + x] = true;
		for (int i = 0; i < 4; i++) {
			int next_y = y + directions[i][0];
			int next_x = x + directions[i][1];
			if (next_x < 0 || next_x == m || next_y < 0 || next_y == n
					|| map.get(next_y).get(next_x) == 0 || visited[next_y * m + next_x])
				continue;
			area += dfs(next_y, next_x);
		}
		return (area);
	}
}
