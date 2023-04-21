import java.util.*;
import java.io.*;

public class Anything {

	static int n, m;
	static int arctic[][];
	static boolean visited[][];
	static int directions[][] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	public static void main(String[] argvs) throws IOException {
		//입력 part
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		arctic = new int[n][m];
		int max_height = -1;
		for (int y = 0; y < n; y++) {
			st = new StringTokenizer(br.readLine(), " ");
			for (int x = 0; x < m; x++) {
				int height = Integer.parseInt(st.nextToken());
				arctic[y][x] = height;
				max_height = Integer.max(max_height, height);
			}
		}
		int ret = 0;
		//빙산이 모두 녹을때까지 계속 녹인다
		while (!is_all_melted()) {
			//dfs시작
			visited = new boolean[n][m];
			for (int j = 0; j < n; j++)
				Arrays.fill(visited[j], false);
			int split_area = 0;
			for (int y = 0; y < n; y++) {
				for (int x = 0; x < m; x++) {
					if (arctic[y][x] > 0 && !visited[y][x])
						split_area += dfs(y, x);
				}
			}
			//만약 빙산이 두 덩어리 이상으로 분리되었으면 현재까지 걸린 시간(ret)을 출력 후 종료
			if (split_area > 1) {
				System.out.println(ret);
				return ;
			}
			//아직 빙산이 분리되어 있지 않은경우(dfs로 확인) 빙산을 녹일 수있는 만큼 최대로 녹인다
			ret += melt_arctic();
		}
		System.out.println(0);
	}

	static int dfs(int y, int x) {
		visited[y][x] = true;
		for (int i = 0; i < 4; i++) {
			//현재 위치에서 상하좌우 4방향을 탐색하고 바다와 접촉하는 면이 몇개 있는지 카운트
			int next_y = y + directions[i][0];
			int next_x = x + directions[i][1];
			if (next_y < 0 || next_y == n || next_x < 0 || next_x == m
					|| arctic[next_y][next_x] <= 0 || visited[next_y][next_x])
				continue;
			dfs(next_y, next_x);
		}
		return (1);
	}
	static int melt_arctic() {
		ArrayList<Coord> lst = new ArrayList<>();
		int year_taken = 987654321;
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < m; x++) {
				//현재 자리가 빙산이 아니라 바다인 경우 continue
				if (arctic[y][x] <= 0)
					continue ;
				int water_cnt = 0;
				for (int i = 0; i < 4; i++) {
					//현재 위치에서 상하좌우 4방향을 탐색하고 바다와 접촉하는 면이 몇개 있는지 카운트
					int next_y = y + directions[i][0];
					int next_x = x + directions[i][1];
					if (next_y < 0 || next_y == n || next_x < 0 || next_x == m)
						continue;
					if (arctic[next_y][next_x] <= 0)
						water_cnt++;
				}
				//현재 빙산이 바다에 접하지 않아 녹을 수 없는 상황이면 continue
				if (water_cnt == 0)
					continue;
				lst.add(new Coord(y, x, water_cnt));
				//현재 lst에 등록된 빙산들(melt의 대상이 되는 빙산)중 최초로 높이가 0이 되는 빙산이 생기는 시간이 언제인지 구한다
				int temp_year_taken = arctic[y][x] / water_cnt;
				if (arctic[y][x] % water_cnt > 0)
					temp_year_taken++;
				year_taken = Integer.min(year_taken, temp_year_taken);
			}
		}
		//lst에 등록한 빙산들을 year_taken 만큼 녹인다 (최초로 하나의 빙산이 모두 녹는 시간 == year_taken)
		for (Coord iceberg : lst) 
			arctic[iceberg.y][iceberg.x] -= iceberg.water_cnt * year_taken;
		return (year_taken);
	}

	static boolean is_all_melted() {
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < m; x++)
				if (arctic[y][x] > 0)
					return (false);
		}
		return (true);
	}
}

class Coord {
	int y, x, water_cnt;

	public Coord(int y, int x, int water_cnt) {
		this.y = y;
		this.x = x;
		this.water_cnt = water_cnt;
	}
}
