import java.util.*;
import java.io.*;

public class Anything{
	public static void main(String[] argv) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		Stack<Integer> inputs = new Stack<>();
		for (int i = 0; i < n; i++)
			inputs.add(Integer.parseInt(br.readLine()));

		Stack<Building> stack = new Stack<>();
		stack.add(new Building(Integer.MAX_VALUE, 0));
		long ret = 0;
		int inside_cnt;
		while (!inputs.isEmpty()){
			int curr_height = inputs.pop();
			if (stack.peek().height >= curr_height){
				stack.add(new Building(curr_height, 1));
				continue;
			}
			inside_cnt = 1;
			while (stack.peek().height < curr_height){
				ret += stack.peek().inside_cnt;
				inside_cnt += stack.peek().inside_cnt;
				stack.pop();
			}
			stack.add(new Building(curr_height, inside_cnt));
		}
		System.out.println(ret);
	}
}

class Building{
	int height, inside_cnt;

	Building(int height, int inside_cnt){
		this.height = height;
		this.inside_cnt = inside_cnt;
	}
}
