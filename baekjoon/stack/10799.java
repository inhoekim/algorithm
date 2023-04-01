import java.io.*;
import java.util.*;


public class Anything {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		String input = br.readLine();
		Stack<Left_bracket> stack = new Stack<>();
		int ret = 0;
		for (char c : input.toCharArray())
		{
			if (c == '(') {
				stack.push(new Left_bracket(0));
			}
			else if (c == ')') {
				int pop_cnt = stack.peek().pop_cnt;
				stack.pop();
				if (!stack.isEmpty()) {
					Left_bracket lb = stack.pop();
					if (pop_cnt == 0)
						lb.setPop_cnt(lb.pop_cnt + 1);
					else
						lb.setPop_cnt(lb.pop_cnt + pop_cnt);
					stack.push(lb);
				}
				if (pop_cnt != 0)
					ret += pop_cnt + 1;
			}
		}
		System.out.println(ret);
	}
}

class Left_bracket{
	int pop_cnt;

	public Left_bracket(int pop_cnt){
		this.pop_cnt = pop_cnt;
	}

	public void setPop_cnt(int pop_cnt) {
		this.pop_cnt = pop_cnt;
	}
}
