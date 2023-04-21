import java.util.*;
import java.io.*;

public class Anything {

	public static void main(String[] argvs) throws IOException {
		//입력 part
		int directions[][] = {{-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1}};
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		while (true) {
			String input = br.readLine();
			if (input.equals("0 0 0"))
				break ;
			StringTokenizer st = new StringTokenizer(input, " ");
			int l = Integer.parseInt(st.nextToken());
			int r = Integer.parseInt(st.nextToken());
			int c = Integer.parseInt(st.nextToken());
			int building[][][] = new int[l][r][c];
			Queue<Coord> queue = new LinkedList<>();
			Coord goal = new Coord(-1, -1, -1, -1);
			for (int k = 0; k < l; k++) {
				for (int y = 0; y < r; y++) {
					input = br.readLine();
					for (int x = 0; x < c; x++) {
						char ch = input.charAt(x);
						if (ch == 'S')
							queue.add(new Coord(y, x, k, 0));
						else if (ch == 'E')
							goal = new Coord(y, x, k, -1);
						if (ch == '.' || ch == 'E')
							building[k][y][x] = -1;
						else
							building[k][y][x] = 987654321;
					}
				}
				br.readLine();
			}
			//bfs 시작
			while (!queue.isEmpty()) {
				Coord curr = queue.poll();
				if (curr.y == goal.y && curr.x == goal.x && curr.h == goal.h) {
					goal.dist = curr.dist;
					System.out.println("Escaped in " + curr.dist + " minute(s).");
					break ;
				}
				for (int i = 0; i < 6; i++) {
					int next_h = curr.h + directions[i][0];
					int next_y = curr.y + directions[i][1];
					int next_x = curr.x + directions[i][2];
					if (next_x < 0 || next_x == c || next_y < 0 || next_y == r || next_h < 0 || next_h == l
							|| building[next_h][next_y][next_x] != -1)
						continue ;
					building[next_h][next_y][next_x] = curr.dist + 1;
					queue.add(new Coord(next_y, next_x, next_h, curr.dist + 1));
				}
			}
			if (goal.dist == -1)
				System.out.println("Trapped!");
		}
	}
}

class Coord {
	int y, x, h, dist;

	public Coord(int y, int x, int h, int dist) {
		this.y = y;
		this.x = x;
		this.h = h;
		this.dist = dist;
	}
}
