import java.util.*;
import java.io.*;

public class Anything {
	static int m, n, k;
	static int korea_kimchi_garden[][];
	static Coord start_point[];
	static int directions[][] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	public static void main(String args[]) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(br.readLine());
		while(t-- != 0) {
			//입력
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			m = Integer.parseInt(st.nextToken());
			n = Integer.parseInt(st.nextToken());
			k = Integer.parseInt(st.nextToken());
			korea_kimchi_garden = new int[n][m];
			start_point = new Coord[k];
			for (int i = 0; i < n; i++)
				Arrays.fill(korea_kimchi_garden[i], 0);
			for (int i = 0; i < k; i++) {
				st = new StringTokenizer(br.readLine(), " ");
				int x = Integer.parseInt(st.nextToken());
				int y = Integer.parseInt(st.nextToken());
				korea_kimchi_garden[y][x] = 1;
				start_point[i] = new Coord(y, x);
			}
			// dfs()
			int ret = 0;
			for (Coord start : start_point)
				if (korea_kimchi_garden[start.y][start.x] == 1)
					ret += dfs(start);
			// 출력
			System.out.println(ret);
		}

	}

	static int dfs(Coord curr) {
		korea_kimchi_garden[curr.y][curr.x] = 0;
		for (int i = 0; i < 4; i++) {
			int next_y = curr.y + directions[i][0];
			int next_x = curr.x + directions[i][1];
			if (next_x < 0 || next_x == m || next_y < 0 || next_y == n || korea_kimchi_garden[next_y][next_x] == 0)
				continue;
			dfs(new Coord(next_y, next_x));
		}
		return (1);
	}
}

class Coord {
	int y, x;
	public Coord(int y, int x) {
		this.y = y;
		this.x = x;
	}
}
