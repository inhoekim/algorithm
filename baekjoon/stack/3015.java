import java.util.*;
import java.io.*;

public class Main{
	public static void main(String[] argv) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		Stack<Pair> stack = new Stack<>();

		stack.add(new Pair(Integer.parseInt(br.readLine()), 1));
		long ret = 0;
		int height, inside_cnt;
		for (int i = 1; i < n; i++){
			height = Integer.parseInt(br.readLine());
			inside_cnt = 1;
			// 만약 앞사람이 자신보다 키가 크다면 순서쌍 1개를 추가
			if (stack.peek().height > height) {
				ret++;
				stack.add(new Pair(height,1));
				continue;
			}
			// 만약 앞사람이 자신보다 키가 작다면 그 앞사람은 더 이상 순서쌍을 만들 수 없음
			while (!stack.isEmpty() && stack.peek().height <= height){
				// 앞사람이 자신과 키가 같다면 그 사람은 자신과 합쳐짐(inside_cnt++)
				if (stack.peek().height == height)
					inside_cnt += stack.peek().inside_cnt;
				ret += stack.peek().inside_cnt;
				stack.pop();
			}
			// 자신의 앞에 키큰 사람이 존재한다면 순서쌍 1개를 추가
			if (!stack.isEmpty())
				ret++;
			stack.add(new Pair(height, inside_cnt));
		}
		System.out.println(ret);
	}
}

class Pair{
	long height;
	int inside_cnt;

	Pair(long height, int inside_cnt){
		this.height = height;
		this.inside_cnt = inside_cnt;
	}
}
