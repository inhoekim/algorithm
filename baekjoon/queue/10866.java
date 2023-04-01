import java.io.*;
import java.util.*;
import java.util.stream.*;

public class Anything {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
		LinkedList<Integer> deque = new LinkedList<>();
		int n = Integer.parseInt(br.readLine());

		while (n-- != 0){
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			String oper = st.nextToken();

			if (oper.equals("push_front")){
				deque.addFirst(Integer.parseInt(st.nextToken()));
			}else if (oper.equals("push_back")){
				deque.addLast(Integer.parseInt(st.nextToken()));
			}else if (oper.equals("pop_front")){
				if (deque.size() == 0)
					bw.write("-1\n");
				else
					bw.write(Integer.toString(deque.pollFirst()) + "\n");
			}else if (oper.equals("pop_back")){
				if (deque.size() == 0)
					bw.write("-1\n");
				else
					bw.write(Integer.toString(deque.pollLast()) + "\n");
			}else if (oper.equals("size")){
				bw.write(Integer.toString(deque.size()) + "\n");
			}else if (oper.equals("empty")) {
				if (deque.isEmpty())
					bw.write("1\n");
				else
					bw.write("0\n");
			}else if (oper.equals("front")){
				if (deque.size() == 0)
					bw.write("-1\n");
				else
					bw.write(Integer.toString(deque.peek()) + "\n");
			}else if (oper.equals("back")){
				if (deque.size() == 0)
					bw.write("-1\n");
				else
					bw.write(Integer.toString(deque.peekLast()) + "\n");
			}
		}
		bw.flush();
	}
}
