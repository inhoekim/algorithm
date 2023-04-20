import java.util.*;
import java.io.*;

public class Anything{

	public static void main (String[] argvs) throws IOException {
		//입력 part
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		int f = Integer.parseInt(st.nextToken());
		int s = Integer.parseInt(st.nextToken());
		int g = Integer.parseInt(st.nextToken());
		int u = Integer.parseInt(st.nextToken());
		int d = Integer.parseInt(st.nextToken());
		boolean visited[] = new boolean[f + 1];
		Arrays.fill(visited, false);
		//bfs 시작
		Queue<Floor> queue = new LinkedList<>();
		queue.add(new Floor(s, 0));
    visited[s] = true;
		while (!queue.isEmpty()) {
			Floor curr = queue.poll();
			//목표층에 도달했을 때
			if (curr.floor == g) {
				System.out.println(curr.dist);
				break;
			}
			//위층으로 올라갈 수 있는지 검사
			if (curr.floor + u <= f && !visited[curr.floor + u]) {
				visited[curr.floor + u] = true;
				queue.add(new Floor(curr.floor + u, curr.dist + 1));
			}
			//아래층으로 내려갈 수 있는지 검사
			if (curr.floor - d > 0 && !visited[curr.floor - d]) {
				visited[curr.floor - d] = true;
				queue.add(new Floor(curr.floor - d, curr.dist + 1));
			}
		}
		if (!visited[g])
			System.out.println("use the stairs");
	}
}
class Floor{
	int floor, dist;
	public Floor(int floor, int dist) {
		this.floor = floor;
		this.dist = dist;
	}
}
