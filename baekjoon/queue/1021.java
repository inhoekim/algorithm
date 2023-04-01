import java.io.*;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class Anything {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		LinkedList<Integer> left_move_lst = IntStream.range(1, n + 1).mapToObj(i -> i).collect(Collectors.toCollection(LinkedList::new));
		LinkedList<Integer> right_move_lst = (LinkedList<Integer>)left_move_lst.clone();
		st = new StringTokenizer(br.readLine(), " ");

		long ret = 0;
		while (m-- != 0){
			int target = Integer.parseInt(st.nextToken());
			ret += Math.min(find_target(left_move_lst, target, true), find_target(right_move_lst, target, false));
		}
		System.out.println(ret);;
	}

	static long find_target(LinkedList<Integer> lst, int target, boolean is_left_find){
		long cnt = 0;
		while (lst.peek() != target) {
			if (is_left_find)
				lst.addLast(lst.pollFirst());
			else
				lst.addFirst(lst.pollLast());
			cnt++;
		}
		lst.poll();
		return (cnt);
	}
}
