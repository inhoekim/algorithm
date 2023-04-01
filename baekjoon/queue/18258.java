import java.io.*;
import java.util.*;

public class Anything {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		LinkedList<Integer> queue = new LinkedList<>();
		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

		for (int i = 0; i < n; i++){
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			String oper = st.nextToken();
			if (oper.equals("push")){
				int num = Integer.parseInt(st.nextToken());
				queue.add(num);
			}else if (oper.equals("pop")){
				if (queue.isEmpty())
					bw.write("-1\n");
				else
					bw.write(queue.poll().toString() + "\n");
			}else if (oper.equals("size")){
				bw.write(Integer.toString(queue.size()) + "\n");
			}else if (oper.equals("empty")){
				if (queue.isEmpty())
					bw.write("1\n");
				else
					bw.write("0\n");
			}else if (oper.equals("front")){
				if (queue.isEmpty())
					bw.write("-1\n");
				else
					bw.write(queue.peek().toString() + "\n");
			}else {
				if (queue.isEmpty())
					bw.write("-1\n");
				else
					bw.write(queue.peekLast().toString() + "\n");
			}
		}
		bw.flush();
	}
}
