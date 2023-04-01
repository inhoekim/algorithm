import java.io.*;
import java.util.*;
import java.util.stream.*;

public class Anything {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int input = Integer.parseInt(br.readLine());
		LinkedList<Integer> queue = IntStream.range(1,input + 1).mapToObj(i -> i).collect(Collectors.toCollection(LinkedList::new));
		while (queue.size() != 1){
			queue.poll();
			queue.add(queue.poll());
		}
		System.out.println(queue.get(0));
	}
}
