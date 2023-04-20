import java.util.*;
import java.io.*;

public class Anything{


	public static void main (String[] argvs) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(br.readLine());
		while (t-- != 0) {
			//입력 part
			int l = Integer.parseInt(br.readLine());
			boolean visited[][] = new boolean[l][l];
			for (int i = 0; i < l; i++)
				Arrays.fill(visited[i], false);
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			Queue<Coord> queue = new LinkedList<>();
			queue.add(new Coord(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()), 0));
			st = new StringTokenizer(br.readLine(), " ");
			Coord goal = new Coord(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()), -1);
			int directions[][] = {{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}};
			//bfs 시작
			while (!queue.isEmpty()) {
				Coord curr = queue.poll();
				if (curr.y == goal.y && curr.x == goal.x) {
					System.out.println(curr.dist);
					break;
				}
				for(int i = 0; i < directions.length; i++) {
					int next_y = curr.y + directions[i][0];
					int next_x = curr.x + directions[i][1];
					if (next_x < 0 || next_x >= l || next_y < 0 || next_y >= l || visited[next_y][next_x])
						continue;
					visited[next_y][next_x] = true;
					queue.add(new Coord(next_y, next_x, curr.dist + 1));
				}
			}
		}
	}
}

class Coord{
	int y, x;
	long dist;

	public Coord(int y, int x, long dist) {
		this.y = y;
		this.x = x;
		this.dist = dist;
	}
}
