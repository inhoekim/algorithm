import java.util.*;
import java.io.*;

public class Anything {

	static int n;
	static int edge[];
	static boolean completed[];
	static int visited[];

	public static void main(String[] argvs) throws IOException {
		//입력 part
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(br.readLine());
		while (t-- != 0) {
			n = Integer.parseInt(br.readLine());
			edge = new int[n];
			completed = new boolean[n];
			visited = new int[n];
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			for (int i = 0; i < n; i++) {
				edge[i] = Integer.parseInt(st.nextToken()) - 1;
				completed[i] = false;
				visited[i] = -1;
			}
			int team_member_cnt = 0;
			for (int i = 0; i < n; i++) {
				//한번 dfs에서 탐색된 정점은 이미 사이클 여부 판단이 끝났으므로 더이상 dfs 탐색을 하지 않아도 된다. 해당 내용을 completed 배열에 저장.
				if (!completed[i]) {
					//visited 배열을 이용해서 사이클을 판별. 만약 dfs도중 visited이 true인 정점을 다시 방문해야하는 상황이 온다면 사이클. visted는 dfs를 돌면서 정점이 방문된 순서를 저장.
					visited[i] = 1;
					team_member_cnt += dfs(i);
				}
			}
			System.out.println(n - team_member_cnt);
		}
	}

	static int dfs(int node) {
		int cycle_member_cnt = 0;
		if (completed[edge[node]]) {
			completed[node] = true;
			return (cycle_member_cnt);
		}
		if (visited[edge[node]] == -1) {
			visited[edge[node]] = visited[node] + 1;
			cycle_member_cnt = dfs(edge[node]);
		}
		else {
			completed[node] = true;
			return (visited[node] - visited[edge[node]] + 1);
		}
		completed[node] = true;
		return (cycle_member_cnt);
	}
}
