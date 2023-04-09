import java.io.*;
import java.util.*;
import java.util.stream.*;
public class Anything {

	static ArrayList<Edge> edge_lst = new ArrayList<>();
	static ArrayList<Integer> parents;
	public static void main(String[] args) throws IOException{
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		parents = IntStream.range(0,n+1).mapToObj(i -> i).collect(Collectors.toCollection(ArrayList::new));
		for (int i = 0; i < n; i++)
			edge_lst.add(new Edge(0, i + 1,  Integer.parseInt(br.readLine())));
		for (int y = 0; y < n; y++){
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			for (int x = 0; x < n; x++) {
				int weight = Integer.parseInt(st.nextToken());
				if (weight == 0)
					continue ;
				edge_lst.add(new Edge(y + 1, x + 1, weight));
			}
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
