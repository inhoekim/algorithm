import java.util.*;
import java.io.*;

public class Anything{

	static int n;
	static int map[][];
	static boolean visited[][];
	static int directions[][] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	public static void main (String[] argvs) throws IOException {
		//입력 part
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		n = Integer.parseInt(br.readLine());
		map = new int[n][n];
		int max_height = -1;
		for (int y = 0; y < n; y++) {
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			for (int x = 0; x < n; x++) {
				map[y][x] = Integer.parseInt(st.nextToken());
				max_height = Integer.max(max_height, map[y][x]);
			}
		}
		//dfs 시작
		int ret = 1;
		for (int i = 1; i < max_height; i++) {
			//매 반복마다 map에 1만큼 비가 차오르게함
			for (int y = 0; y < n; y++) {
				for (int x = 0; x < n; x++)
					map[y][x]--;
			}
			int temp_ret = 0;
			//dfs를 돌려서 안전영역 개수를 구함
			visited = new boolean[n][n];
			for (int j = 0; j < n; j++)
				Arrays.fill(visited[j], false);
			for (int y = 0; y < n; y++) {
				for (int x = 0; x < n; x++)
					if (map[y][x] > 0 && !visited[y][x])
						temp_ret += dfs(y, x);
			}
			//현재 물의 높이에서 만들어지는 안전영역이 최대라면 ret을 갱신
			ret = Integer.max(ret, temp_ret);
		}
		System.out.println(ret);
	}

	static int dfs(int y, int x) {
		visited[y][x] = true;
		for (int i = 0; i < 4; i++) {
			int next_y = y + directions[i][0];
			int next_x = x + directions[i][1];
			if (next_x < 0 || next_x == n || next_y < 0 || next_y == n
					|| visited[next_y][next_x] || map[next_y][next_x] <= 0)
				continue;
			dfs(next_y, next_x);
		}
		return (1);
	}
}
