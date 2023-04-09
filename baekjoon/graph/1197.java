import java.io.*;
import java.util.*;
import java.util.stream.*;
public class Anything {

	static ArrayList<Edge> edge_lst = new ArrayList<>();
	static ArrayList<Integer> parents;
	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		int v = Integer.parseInt(st.nextToken());
		int e = Integer.parseInt(st.nextToken());
		parents = IntStream.range(0,v+1).mapToObj(i -> i).collect(Collectors.toCollection(ArrayList::new));
		for (int i = 0; i < e; i++) {
			st = new StringTokenizer(br.readLine(), " ");
			edge_lst.add(new Edge(Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken()), Integer.parseInt(st.nextToken())));
		}
		Collections.sort(edge_lst);

		long ret = 0;
		for(int i = 0; i < edge_lst.size(); i++) {
			Edge edge = edge_lst.get(i);
			int root_a = find_parent(edge.idx_a);
			int root_b = find_parent(edge.idx_b);
			if (root_a != root_b){
				if (root_a < root_b)
					parents.set(root_b, root_a);
				else
					parents.set(root_a, root_b);
				ret += edge.weight;
			}
		}
		System.out.println(ret);
	}

	static int find_parent(int x){
		if (parents.get(x) == x)
			return (x);
		int root = find_parent(parents.get(x));
		parents.set(x, root);
		return (root);
	}
}

class Edge implements Comparable<Edge> {
	int idx_a, idx_b, weight;

	public Edge(int idx_a, int idx_b, int weight){
		this.idx_a = idx_a;
		this.idx_b = idx_b;
		this.weight = weight;
	}

	@Override
	public int compareTo(Edge o) {
		if (o.weight > weight)
			return -1;
		else if (o.weight < weight)
			return 1;
		return 0;
	}
}
