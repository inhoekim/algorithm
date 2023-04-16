import java.util.*;
import java.io.*;

public class Anything {
	public static void  main(String args[]) throws IOException {
		int directions[][] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
		//입력 part
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		int r = Integer.parseInt(st.nextToken());
		int c = Integer.parseInt(st.nextToken());
		char map[][] = new char[r][c];
		Queue<Maze_obj> queue = new LinkedList<>();
		Queue<Maze_obj> temp_queue = new LinkedList<>();
		for (int y = 0; y < r; y++) {
			String str = br.readLine();
			for (int x = 0; x < c; x++) {
				char ch = str.charAt(x);
				map[y][x] = ch;
				if (ch == 'J')
					queue.add(new Maze_obj(true, y, x, 0));
				else if (ch == 'F')
					temp_queue.add(new Maze_obj(false,  y, x, -1));
			}
		}
		while (!temp_queue.isEmpty())
			queue.add(temp_queue.poll());
		// bfs()
		while (!queue.isEmpty()) {
			Maze_obj obj = queue.poll();
			//대근이 현재자리에 이미 불이 번져 타죽는 경우
			if (obj.is_jh && map[obj.y][obj.x] == 'F')
				continue ;
			//대근의 탈출 조건
			if (obj.is_jh && (obj.y == 0 || obj.y == r - 1 || obj.x == 0 || obj.x == c - 1)){
				System.out.println(obj.time + 1);
				return ;
			}
			for (int i = 0; i < 4; i++) {
				int next_y = obj.y + directions[i][0];
				int next_x = obj.x + directions[i][1];
				//해당 경우 다음 방문 장소로 큐에 등록하지 않는다
				if (next_x < 0 || next_x == c || next_y < 0 || next_y == r || map[next_y][next_x] == '#'
						|| map[next_y][next_x] == 'F' || obj.is_jh && map[next_y][next_x] == 'J')
					continue ;
				if (!obj.is_jh)
					map[next_y][next_x] = 'F';
				if (obj.is_jh)
					map[next_y][next_x] = 'J';
				/* 대근이가 불타죽는 과정 출력문
				System.out.println("====================");
				for(int y = 0; y < r; y++) {
					for (int x = 0; x < c; x++) {
						System.out.print(map[y][x]);
					}
					System.out.println();
				}
				 */
				queue.add(new Maze_obj(obj.is_jh, next_y, next_x, obj.time + 1));
			}
		}
		System.out.println("IMPOSSIBLE");
	}
}

class Maze_obj {
	boolean is_jh;
	int y, x, time;

	public Maze_obj(boolean is_jh, int y, int x, int time) {
		this.is_jh = is_jh;
		this.y = y;
		this.x = x;
		this.time = time;
	}
}
