import java.util.*;
import java.util.stream.*;
import java.io.*;

public class Anything {

	static ArrayList<ArrayList<Integer>> dists;
	static ArrayList<ArrayList<Integer>> next;
	static final  int MAX = 987654321;
	public static void  main(String args[]) throws IOException{
		//입력 and 초기화 part
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine()) + 1;
		int m = Integer.parseInt(br.readLine());
		dists = Stream.generate(() ->
						Stream.generate(()-> MAX).limit(n).collect(Collectors.toCollection(ArrayList::new)))
				.limit(n + 1).collect(Collectors.toCollection(ArrayList::new));
		next = Stream.generate(() ->
						Stream.generate(()-> -1).limit(n).collect(Collectors.toCollection(ArrayList::new)))
				.limit(n + 1).collect(Collectors.toCollection(ArrayList::new));
		for (int i = 0; i < n; i++){
			for (int j = 0; j < n; j++) {
				if (i == j)
					dists.get(i).set(j, 0);
			}
		}
		for (int i = 0; i < m; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			int city_a = Integer.parseInt(st.nextToken());
			int city_b = Integer.parseInt(st.nextToken());
			int dist = Integer.parseInt(st.nextToken());
			if (dists.get(city_a).get(city_b) > dist) {
				dists.get(city_a).set(city_b, dist);
				next.get(city_a).set(city_b, city_b);
			}
		}
		//본로직 플루이드
		for (int k = 1; k < n; k++) {
			for (int i = 1; i < n; i++) {
				for (int j = 1; j < n; j++) {
					if (dists.get(i).get(j) > dists.get(i).get(k) + dists.get(k).get(j)) {
						dists.get(i).set(j, dists.get(i).get(k) + dists.get(k).get(j));
						next.get(i).set(j, next.get(i).get(k));
					}
				}
			}
		}
		//출력 part
		StringBuilder sb = new StringBuilder();
		for (int i = 1; i < n; i++) {
			for (int j = 1; j < n; j++){
				int dist = dists.get(i).get(j);
				if (dist == MAX)
					sb.append("0 ");
				else
					sb.append(dist + " ");
			}
			sb.setLength(sb.length() - 1);
			sb.append("\n");
		}
		for (int i = 1; i < n; i++) {
			for (int j = 1; j < n; j++) {
				if (next.get(i).get(j) == -1)
					sb.append("0\n");
				else{
					sb.append(i + " ");
					int cnt = 2;
					int next_city_idx = next.get(i).get(j);
					int append_len = Integer.toString(i).length() + 1;
					while (next_city_idx != j) {
						sb.append(next_city_idx + " ");
						append_len += Integer.toString(next_city_idx).length() + 1;
						next_city_idx = next.get(next_city_idx).get(j);
						cnt++;
					}
					sb.insert(sb.length() - append_len,cnt + " ");
					sb.append(next_city_idx + "\n");
				}

			}
		}
		sb.setLength(sb.length() - 1);
		System.out.print(sb);
	}
}
