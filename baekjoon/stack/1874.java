import java.util.*;
import java.io.*;

class Anything{
	public static void main(String[] argv) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder sb = new StringBuilder();

		int n = Integer.parseInt(br.readLine());
		Stack<Integer> stack = new Stack<>();
		boolean is_possible = true;
		int input_num, top_num;
		top_num = 0;
		for (int i = 0; i < n; i++){
			input_num = Integer.parseInt(br.readLine());
			if (top_num > input_num) {
				if (stack.peek() > input_num) {
					is_possible = false;
					break;
				} else if (stack.peek() == input_num) {
					stack.pop();
					sb.append("-");
				}
			}
			else {
				while (top_num < input_num) {
					top_num++;
					stack.add(top_num);
					sb.append("+");
				}
				stack.pop();
				sb.append("-");
			}
		}

		if (is_possible){
		   for (int i = 0; i < sb.length(); i++)
			   System.out.println(sb.charAt(i));
		}
		else
		   System.out.println("NO");
		}
}
