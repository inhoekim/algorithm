import java.util.*;
import java.io.*;

public class Anything{
	public static void main(String[] argv) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();
		int n = Integer.parseInt(br.readLine());
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		Stack<Pair> stack = new Stack<>();
		int curr_num;
		//가장 왼쪽끝에는 최대높이의 통신탑이 있다고 가정 (0번 인덱스의 통신탑의 높이는 INT_MAX값)
		stack.add(new Pair(Integer.MAX_VALUE, 0));
		for (int i = 1; i <= n; i++){
			curr_num = Integer.parseInt(st.nextToken());
			if (stack.peek().num > curr_num){
				sb.append(stack.peek().idx + " ");
				stack.add(new Pair(curr_num, i));
				continue ;
			}
			while (stack.peek().num < curr_num)
				stack.pop();
			sb.append(stack.peek().idx + " ");
			stack.add(new Pair(curr_num ,i));
		}
		sb.deleteCharAt(sb.length() - 1);
		System.out.println(sb);
	}
}

class Pair{
	int	num, idx;

	Pair(int num, int idx){
		this.num = num;
		this.idx = idx;
	}
}
