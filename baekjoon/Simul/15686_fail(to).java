import java.io.*;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;


public class Anything {
	public static int n, m;
	public static LinkedList<LinkedList<House>> city;
	public static LinkedList<Coord> chicks = new LinkedList<>();
	public static LinkedList<Coord> houses = new LinkedList<>();
	public static int ret = Integer.MAX_VALUE;
	public static int[][] directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

	public static void main(String[] args) throws IOException {
		//입출력 part
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		city = Stream.generate(()-> Stream.generate(
				() -> new House()).limit(n).collect(Collectors.toCollection(LinkedList::new)))
				.limit(n).collect(Collectors.toCollection(LinkedList::new));
		for (int y = 0; y < n; y++) {
			st = new StringTokenizer(br.readLine(), " ");
			int num;
			for (int x = 0; x < n; x++) {
				num = Integer.parseInt(st.nextToken());
				if (num == 1)
					houses.add(new Coord(y, x));
				else if (num == 2)
					chicks.add(new Coord(y, x));
				city.get(y).get(x).setType(num);
			}
		}
		//본로직 part
		get_comb(0, 0); //폐업시킬 치킨점뽑기 (== 폐업 안시킬 치킨점뽑기)
		System.out.println(ret);
	}

	public static void reset_visited(LinkedList<LinkedList<House>> city){
		for (int y = 0; y < n; y++)
			for (int x = 0; x < n; x++)
				city.get(y).get(x).setVisited(false);
	}
	public static void get_comb(int idx, int depth){
		//open시킬 치킨집을 m개만큼 전부 선택했을때
		if (depth == m){
			int temp_ret = 0;
			for(Coord coord : houses) { //미리 구해놓은 house들의 좌표를 시작점으로해서 각각 bfs탐색을 반복(탐색 종료점은 치킨집)
				reset_visited(city);
				//각 house들의 치킨거리를 bfs 탐색으로 구해서 temp_ret에 더함
				temp_ret += find_near_chick_bfs(coord);
			}
			ret = Math.min(ret, temp_ret);
			return ;
		}
		//재귀적으로 반복을 돌면서 open시킬 치킨집을 표시
		for (int i = idx; i < chicks.size(); i++) {
			Coord curr_chick = chicks.get(i);
			city.get(curr_chick.y).get(curr_chick.x).setClosed(false);
			get_comb(i + 1, depth + 1);
			city.get(curr_chick.y).get(curr_chick.x).setClosed(true);
		}
	}

	public static int find_near_chick_bfs(Coord coord){
		Queue<Coord> queue = new LinkedList<>();;
		coord.setDist(0);
		queue.add(coord);

		while (!queue.isEmpty()) {
			Coord curr = queue.poll();
			for (int i = 0; i < 4; i++) {
				int next_y = curr.y + directions[i][0];
				int next_x = curr.x + directions[i][1];
				if (next_y < 0 || next_y >= n || next_x < 0 || next_x >= n)
					continue;
				House next_house = city.get(next_y).get(next_x);
				//폐업되지 않은 치킨집을 발견했을 경우 dist를 리턴(bfs 탐색이므로 dist는 최단거리임)
				if (next_house.type == 2 && !next_house.closed)
					return (curr.dist + 1);
				//다음으로 방문할 좌표를 큐에 추가
				if (!next_house.visited) {
					next_house.setVisited(true);
					Coord next_Coord = new Coord(next_y, next_x);
					next_Coord.setDist(curr.dist + 1);
					queue.add(next_Coord);
				}
			}
		}
		return (-1);
	}
}

class House{

	int type;
	boolean closed, visited;

	public House(){
		this.type = -1;
		this.closed = true;
		this.visited = false;
	}

	public void setClosed(boolean closed) {
		this.closed = closed;
	}

	public void setVisited(boolean visited) {
		this.visited = visited;
	}

	public void setType(int type) {
		this.type = type;
	}
}

class Coord{
	int y, x, dist;

	public Coord(int y, int x){
		this.y = y;
		this.x = x;
	}

	public void setDist(int dist){
		this.dist = dist;
	}
}
