import java.io.*;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;


public class Anything {
	public static int n, m;
	public static LinkedList<Coord> chicks = new LinkedList<>();
	public static LinkedList<Coord> houses = new LinkedList<>();
	public static Stack<Coord> stack = new Stack<>();
	public static int ret = Integer.MAX_VALUE;

	public static void main(String[] args) throws IOException {
		//입출력 part
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		for (int y = 0; y < n; y++) {
			st = new StringTokenizer(br.readLine(), " ");
			int num;
			for (int x = 0; x < n; x++) {
				num = Integer.parseInt(st.nextToken());
				if (num == 1)
					houses.add(new Coord(y, x));
				else if (num == 2)
					chicks.add(new Coord(y, x));
			}
		}
		//본로직 part
		get_comb(0, 0); //폐업시킬 치킨점뽑기 (== 폐업 안시킬 치킨점뽑기)
		System.out.println(ret);
	}

	public static void get_comb(int idx, int depth){
		//open시킬 치킨집을 m개만큼 전부 선택했을때
		if (depth == m){
			int temp_ret = 0;
			//구해놓은 house들의 좌표들과 오픈된 치킨집 좌표들의 dist값을 계산
			for(Coord coord : houses)
				temp_ret += get_near_chick_dist(coord);
			ret = Math.min(ret, temp_ret);
			return ;
		}
		//재귀적으로 반복을 돌면서 open시킬 치킨집을 수집
		for (int i = idx; i < chicks.size(); i++) {
			stack.add(chicks.get(i));
			get_comb(i + 1, depth + 1);
			stack.pop();
		}
	}

	public static int get_near_chick_dist(Coord coord){
		int dist = Integer.MAX_VALUE;
		for (int i = 0; i < stack.size(); i++){
			int temp_dist = Math.abs((stack.get(i).y - coord.y)) + Math.abs((stack.get(i).x - coord.x));
			dist = Math.min(dist, temp_dist);
		}
		return (dist);
	}
}
class Coord{
	int y, x;

	public Coord(int y, int x){
		this.y = y;
		this.x = x;
	}
}
