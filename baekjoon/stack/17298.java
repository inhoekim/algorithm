import java.util.*;
import java.io.*;

public class Anything {
	public static void main(String[] argv) throws IOException {
		//입출력 Part
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		Stack<Integer> input = new Stack<>();
		//주어진 입력을 뒤집어서 한개씩 보면서 오큰수를 찾을 것임
		while (st.hasMoreTokens())
			input.add(Integer.parseInt(st.nextToken()));
		StringBuilder sb = new StringBuilder();

		//본 로직 Part
		Stack<Integer> stack = new Stack<>();
		int num;
		while (!input.isEmpty()){
			num = input.pop();
			//자신의 앞이 오큰수가 아닌경우 -> 이제부터 자신이 앞으로 나올 자신보다 작은 다른 숫자들의 오큰수가 될것이므로 앞에 있는 수는 pop 시켜버림
			while (!stack.isEmpty() && num >= stack.peek()){
				stack.pop();
			}
			//자신의 오른쪽에 오큰수가 없는 예외경우 처리
			if (stack.isEmpty()){
				sb.append("1- ");
				stack.add(num);
			}
			//오큰수를 찾았을 경우
			else if (num < stack.peek()){
				sb.append(new StringBuilder(stack.peek().toString()).reverse() + " ");
				stack.add(num);
			}
		}
		sb.setLength(sb.length() - 1);
		sb.reverse();
		System.out.println(sb);
	}
}
