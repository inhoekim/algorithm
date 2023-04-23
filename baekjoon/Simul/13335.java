import java.util.*;
import java.io.*;

public class Anything {

	public static void main(String[] argvs) throws IOException {
		//입력 part
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		int n = Integer.parseInt(st.nextToken());
		int w = Integer.parseInt(st.nextToken());
		int l = Integer.parseInt(st.nextToken());
		LinkedList<Truck> bridge = new LinkedList<>();
		st = new StringTokenizer(br.readLine(), " ");
		int total_weight = 0;
		int total_time = 0;
		for (int i = 0; i < n; i++) {
			boolean time_passed = false;
			int truck_weight = Integer.parseInt(st.nextToken());
			while (total_weight + truck_weight > l) {
				Truck front_truck = bridge.pollFirst();
				total_weight -= front_truck.weight;
				total_time += w - front_truck.dist;
				add_val_to_lst(w - front_truck.dist, bridge, w);
				time_passed = true;
			}
			Truck truck = new Truck(truck_weight, 0);
			if (!time_passed) {
				total_time++;
				total_weight -= add_val_to_lst(1, bridge, w);
			}
			total_weight += truck_weight;
			bridge.addLast(truck);
		}
		while (!bridge.isEmpty()) {
			Truck front_truck = bridge.pollFirst();
			total_time += w - front_truck.dist;
			add_val_to_lst(w - front_truck.dist, bridge, w);
		}
		System.out.println(total_time);
	}

	static int add_val_to_lst(int val, LinkedList<Truck> lst, int w) {
		int minus_weight = 0;
		for(int i = 0; i < lst.size(); i++) {
			int truck_dist = lst.get(i).dist;
			if (truck_dist + val >= w) {
				minus_weight += lst.get(i).weight;
				lst.pollFirst();
				i--;
			}
			else
				lst.get(i).dist = truck_dist + val;
		}
		return (minus_weight);
	}
}

class Truck {
	int dist, weight;
	public Truck(int weight, int dist) {
		this.dist = dist;
		this.weight = weight;
	}
}
