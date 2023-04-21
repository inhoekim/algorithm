import java.util.*;
import java.io.*;

public class Anything {

	public static void main(String[] argvs) throws IOException {
		//입력 part
		int directions[][] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int map[][] = new int[n][m];
		for (int y = 0; y < n; y++) {
			String input = br.readLine();
			for (int x = 0; x < m; x++)
				map[y][x] = input.charAt(x) - '0';
		}
		//bfs 시작
		boolean visited[][][] = new boolean[n][m][2];
		Queue<Coord> queue = new LinkedList<>();
		queue.add(new Coord(0, 0, 0, 0));
		visited[0][0][0] = true;
		int ret = 987654321;
		while (!queue.isEmpty()) {
			Coord curr = queue.poll();
			if (curr.y == n - 1 && curr.x == m - 1)
				ret = Integer.min(ret, curr.dist + 1);
			for (int i = 0; i < 4; i++) {
				int next_y = curr.y + directions[i][0];
				int next_x = curr.x + directions[i][1];
				//방문할 수 없는 정점(이미 방문했던 곳 + 맵 범위를 벗어나는 곳)
				if (next_x < 0 || next_x == m || next_y < 0 || next_y == n || visited[next_y][next_x][curr.is_crash])
					continue;
				//다음 정점이 벽이고 이미 벽을 부순 경우
				if (curr.is_crash == 1 && map[next_y][next_x] == 1)
					continue;
				//다음 정점이 벽이지만 아직 벽을 부술수 있는 경우
				int temp = curr.is_crash;
				if (curr.is_crash == 0 && map[next_y][next_x] == 1)
					temp = curr.is_crash + 1;
				queue.add(new Coord(next_y, next_x, curr.dist + 1, temp));
				visited[next_y][next_x][temp] = true;
			}
		}
		if (ret == 987654321)
			ret = -1;
		System.out.println(ret);
	}
}
class Coord {
	int y, x, dist, is_crash;

	public Coord(int y, int x, int dist, int is_crash) {
		this.y = y;
		this.x = x;
		this.dist = dist;
		this.is_crash = is_crash;
	}
}
