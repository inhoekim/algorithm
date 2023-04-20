import java.util.*;
import java.io.*;

public class Anything{

	static int n;
	static ArrayList<Integer> ret = new ArrayList<>();
	static int map[][];
	static int directions[][] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	public static void main (String[] argvs) throws IOException {
		//입력 part
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		n = Integer.parseInt(br.readLine());
		map = new int[n][n];
		for (int y = 0; y < n; y++) {
			String input = br.readLine();
			for (int x = 0; x < n; x++)
				map[y][x] = input.charAt(x) - '0';
		}
		//dfs시작
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				if (map[y][x] != 0)
					ret.add(dfs(y, x));
			}
		}
		//출력 part
		ret.sort(Comparator.naturalOrder());
		System.out.println(ret.size());
		for (int i = 0; i < ret.size(); i++)
			System.out.println(ret.get(i));
	}

	static int dfs(int y, int x) {
		int cnt = 1;
		map[y][x] = 0;
		for (int i = 0; i < 4; i++) {
			int next_y = y + directions[i][0];
			int next_x = x + directions[i][1];
			if (next_x < 0 || next_x == n || next_y < 0 || next_y == n || map[next_y][next_x] == 0)
				continue;
			cnt += dfs(next_y, next_x);
		}
		return (cnt);
	}
}
