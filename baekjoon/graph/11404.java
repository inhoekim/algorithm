import java.io.*;
import java.util.*;
import java.util.stream.*;
public class Anything {

	static ArrayList<ArrayList<Long>> dists;
	public static void main(String[] args) throws IOException {
		//입력 part
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		dists = Stream.generate(()->
						Stream.generate(() -> Integer.MAX_VALUE).limit(n).mapToLong(i -> i).mapToObj(i -> i).collect(Collectors.toCollection(ArrayList::new)))
						.limit(n).collect(Collectors.toCollection(ArrayList::new));
		int m = Integer.parseInt(br.readLine());
		for(int i = 0; i < m; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			int a = Integer.parseInt(st.nextToken()) - 1;
			int b = Integer.parseInt(st.nextToken()) - 1;
			long dist = Integer.parseInt(st.nextToken());
			if (dists.get(a).get(b) > dist)
				dists.get(a).set(b, dist);
		}
		for (int a = 0; a < n; a++)
			dists.get(a).set(a, (long) 0);

		//플루이드 워샬
		for (int k = 0; k < n; k++) {
			for (int a = 0; a < n; a++) {
				for (int b = 0; b < n; b++) {
					long waypoint_dist = dists.get(a).get(k) + dists.get(k).get(b);
					if (waypoint_dist > Integer.MAX_VALUE)
						waypoint_dist = Integer.MAX_VALUE;
					if (dists.get(a).get(b) > waypoint_dist)
						dists.get(a).set(b, waypoint_dist);
				}
			}
		}
		//출력 part
		StringBuilder sb = new StringBuilder();
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				long dist = dists.get(y).get(x);
				if (dist == Integer.MAX_VALUE)
					sb.append("0 ");
				else
					sb.append(dist + " ");
			}
			sb.setLength(sb.length() - 1);
			sb.append("\n");
		}
		System.out.print(sb);
	}

}
