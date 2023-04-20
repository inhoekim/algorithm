import java.util.*;
import java.io.*;

public class Anything{

	static int m, n, k;
	static boolean visited[][];
	static ArrayList<Integer> ret = new ArrayList<>();
	static int directions[][] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	public static void main (String[] argvs) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		m = Integer.parseInt(st.nextToken());
		n = Integer.parseInt(st.nextToken());
		k = Integer.parseInt(st.nextToken());
		visited = new boolean[m][n];
		//직사각형 입력처리
		for (int i = 0; i < k; i++) {
			st = new StringTokenizer(br.readLine(), " ");
			int l_bottom_x = Integer.parseInt(st.nextToken());
			int l_bottom_y = Integer.parseInt(st.nextToken());
			int r_top_x = Integer.parseInt(st.nextToken());
			int r_top_y = Integer.parseInt(st.nextToken());
			for (int y = l_bottom_y; y < r_top_y; y++)
				for (int x = l_bottom_x; x < r_top_x; x++)
					visited[y][x] = true;
		}
		//dfs시작
		for (int y = 0; y < m; y++) {
			for (int x = 0; x < n; x++) {
				if (!visited[y][x])
					ret.add(dfs(y, x));
			}
		}
		//출력 part
		ret.sort(Comparator.naturalOrder());
		System.out.println(ret.size());
		for (int i = 0; i < ret.size(); i++) {
			if (i == ret.size() - 1)
				System.out.print(ret.get(i));
			else
				System.out.print(ret.get(i) + " ");
		}
	}

	static int dfs(int y, int x) {
		int cnt = 1;
		visited[y][x] = true;
		for (int i = 0; i < 4; i++) {
			int next_y = y + directions[i][0];
			int next_x = x + directions[i][1];
			if (next_x < 0 || next_x == n || next_y < 0 || next_y == m || visited[next_y][next_x])
				continue;
			cnt += dfs(next_y, next_x);
		}
		return (cnt);
	}
}
