import java.util.*;
import java.util.stream.*;
import java.io.*;

public class Anything {

	static ArrayList<ArrayList<Integer>> maze;
	static int n, m;
	static boolean visited[][];
	static int directions[][] = {{-1,0}, {1,0}, {0, -1}, {0, 1}};

	public static void  main(String args[]) throws IOException {
		//입력 part
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		maze = Stream.generate(() -> Stream.generate(() -> 0).limit(m).collect(Collectors.toCollection(ArrayList::new)))
				.limit(n).collect(Collectors.toCollection(ArrayList::new));
		for (int y = 0; y < n; y++) {
			String str = br.readLine();;
			for (int x = 0; x < m; x++)
				maze.get(y).set(x, str.charAt(x) - '0');
		}
		visited = new boolean[n][m];
		for (int i = 0; i < n; i++)
			Arrays.fill(visited[i], false);
		//bfs
		int ret = bfs();
		//출력
		System.out.println(ret);
	}

	public static int bfs()
	{
		Queue<Pair> queue = new LinkedList<>();
		queue.add(new Pair(0, 0, 1));
		while (!queue.isEmpty()) {
			Pair curr = queue.poll();
			if (curr.y == n - 1 && curr.x == m - 1)
				return (curr.dist);
			for (int i = 0; i < 4; i++) {
				int next_y = curr.y + directions[i][0];
				int next_x = curr.x + directions[i][1];
				if (next_x < 0 || next_x == m || next_y < 0 || next_y == n
						|| visited[next_y][next_x] || maze.get(next_y).get(next_x) == 0)
					continue;
				queue.add(new Pair(next_y, next_x, curr.dist + 1));
				visited[next_y][next_x] = true;
			}
		}
		return (-1);
	}
}

class Pair{
	int x, y, dist;
	public Pair(int y, int x, int dist) {
		this.x = x;
		this.y = y;
		this.dist = dist;
	}
}
