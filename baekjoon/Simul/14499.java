import java.util.*;
import java.io.*;

public class Anything {
	static int n, m, k;
	static int map[][];
	static StringBuilder sb;

	public static void main(String args[]) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		Dice dice = new Dice(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()));
		k = Integer.parseInt(st.nextToken());
		map = new int[n][m];
		for (int y = 0; y < n; y++) {
			st = new StringTokenizer(br.readLine(), " ");
			for (int x= 0; x < m; x++)
				map[y][x] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(br.readLine(), " ");
		sb = new StringBuilder();
		for (int i = 0; i < k; i++)
			dice.roll(Integer.parseInt(st.nextToken()));
		sb.setLength(sb.length() - 1);
		System.out.println(sb);
	}

	static class Dice {
		int y, x;
		LinkedList<Integer> updown_state =  new LinkedList<>();
		LinkedList<Integer> lr_state =  new LinkedList<>();
		int directions[][] = {{0, 0}, {0, 1}, {0, -1}, {-1, 0}, {1, 0}};

		public Dice(int y, int x) {
			this.y = y;
			this.x = x;
			for (int i = 0; i < 4; i++) {
				this.updown_state.add(0);
				this.lr_state.add(0);
			}
		}

		public void roll(int idx) {
			int next_y = this.y + directions[idx][0];
			int next_x = this.x + directions[idx][1];
			if (next_y < 0 || next_y == n || next_x < 0 || next_x == m)
				return ;
			if (idx == 1)
				roll_right();
			else if (idx == 2)
				roll_left();
			else if (idx == 3)
				roll_up();
			else
				roll_down();
			if (map[next_y][next_x] == 0) {
				map[next_y][next_x] = updown_state.get(0);
			}else {
				updown_state.set(0, map[next_y][next_x]);
				lr_state.set(0, map[next_y][next_x]);
				map[next_y][next_x] = 0;
			}
			this.y = next_y;
			this.x = next_x;
			sb.append(updown_state.get(2) + "\n");
		}
		public void roll_up(){
			updown_state.addFirst(updown_state.pollLast());
			lr_state.set(0, updown_state.get(0));
			lr_state.set(2, updown_state.get(2));
		}

		public void roll_down(){
			updown_state.addLast(updown_state.pollFirst());
			lr_state.set(0, updown_state.get(0));
			lr_state.set(2, updown_state.get(2));
		}

		public void roll_left() {
			lr_state.addLast(lr_state.pollFirst());
			updown_state.set(0, lr_state.get(0));
			updown_state.set(2, lr_state.get(2));
		}

		public void roll_right(){
			lr_state.addFirst(lr_state.pollLast());
			updown_state.set(0, lr_state.get(0));
			updown_state.set(2, lr_state.get(2));
		}
	}
}

