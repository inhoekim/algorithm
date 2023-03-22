import java.util.*;

Class Main{
	public static void main(void){
		Stack<Integer> stack = new Stack<>();
		Queue<Integer> queue = new LinkedList<>();
		BufferedReader br = new BufferedReader(new InputStream(System.in));
		String init_str = br.readLine();
		int m = Interger.parseInt(br.readLine());
		
		for (char ch : init_str.toCharArray())
			stack.add(ch);
		for (int i = 0; i < m; i++){
			String oper = br.readLine();
			if (oper.charAt(0) == 'P')
				stack.add(oper.charAt(2));
			else if (oper.charAt(0) == 'L')
				if (!stack.empty())
					queue.add(stack.pop());
			else if (oper.charAt(0) == 'D')
				if (!queue.isEmpty())
					stack.add(queue.poll());
			else{
				if (!stack.empty)
					stack.pop();
			}
		}
		Stakc<Integer> print_stack = new Stack<>();
		while (!stack.empty())
			print_stack.add(stack.pop());
		while (!print_stack.empty())
			System.out.print(print_stack.pop());
		while (!queue.isEmpty())
			System.out.print(queue.poll());
	}
}
