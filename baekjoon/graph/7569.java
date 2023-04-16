import java.util.*;
import java.util.stream.*;
import java.io.*;

public class Anything {
	public static void  main(String args[]) throws IOException {
		//입력 part
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		int m = Integer.parseInt(st.nextToken());
		int n = Integer.parseInt(st.nextToken());
		int h = Integer.parseInt(st.nextToken());
		ArrayList<ArrayList<ArrayList<Integer>>> box = Stream.generate(() -> Stream.generate(()-> Stream.generate(() -> 0).limit(m).collect(Collectors.toCollection(ArrayList::new)))
				.limit(n).collect(Collectors.toCollection(ArrayList::new))).limit(h).collect(Collectors.toCollection(ArrayList::new));
		int directions[][] = {{-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1}}; // 위층,아래층, 상하좌우 순
		Queue<Tomato> queue = new LinkedList<>();
		for (int z = 0; z < h; z++) {
			for (int y = 0; y < n; y++) {
				st = new StringTokenizer(br.readLine(), " ");
				for (int x = 0; x < m; x++) {
					int tomato_state = Integer.parseInt(st.nextToken());
					if (tomato_state == 1)
						queue.add(new Tomato(z, y, x, 0));
					box.get(z).get(y).set(x, tomato_state);
				}
			}
		}
		int max_day = -1;
		//bfs()
		while (!queue.isEmpty()) {
			Tomato curr = queue.poll();
			for (int i = 0; i < 6; i++) {
				int next_z = curr.z + directions[i][0];
				int next_y = curr.y + directions[i][1];
				int next_x = curr.x + directions[i][2];
				if (next_z < 0 || next_z == h || next_y < 0 || next_y == n || next_x < 0 || next_x == m
				|| box.get(next_z).get(next_y).get(next_x) != 0)
					continue;
				box.get(next_z).get(next_y).set(next_x, 1);
				max_day = Integer.max(max_day, curr.day + 1);
				queue.add(new Tomato(next_z, next_y, next_x, curr.day + 1));
			}
		}
		//0이 존재하는지 검사
		boolean is_false = false;
		for (int z = 0; z < h; z++) {
			for (int y = 0; y < n; y++) {
				for (int x = 0; x < m; x++) {
					if (box.get(z).get(y).get(x) == 0)
						is_false = true;
				}
			}
		}
		if (is_false)
			max_day = -1;
		else if (!is_false && max_day == -1)
			max_day = 0;
		System.out.println(max_day);
	}
}

class Tomato {
	int z,y,x,day;

	public Tomato(int z, int y, int x, int day) {
		this.z = z;
		this.y = y;
		this.x = x;
		this.day = day;
	}
}
