import java.io.*;
import java.util.*;


public class Anything {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(br.readLine());
		while (t-- != 0){
			String opers = br.readLine();
			int n = Integer.parseInt(br.readLine());
			LinkedList<Integer> input_lst = str_to_lst(br.readLine());

			boolean is_error = false;
			int is_reverse = -1;
			for (int i = 0 ; i < opers.length(); i++) {
				if (opers.charAt(i) == 'R')
					is_reverse *= -1;
				else if (opers.charAt(i) == 'D'){
					if (input_lst.isEmpty()) { //예외 case
						is_error = true;
						System.out.println("error");
						break ;
					}
					if (is_reverse > 0) { //오른쪽에서 pop()
						input_lst.pollLast();
					}
					else if (is_reverse < 0) { //왼쪽에서 pop()
						input_lst.pollFirst();
					}
				}
			}
			if (!is_error && !input_lst.isEmpty()) {
				StringBuilder sb = new StringBuilder();
				sb.append("[");
				while (!input_lst.isEmpty()) {
					if (is_reverse > 0) {
						sb.append(input_lst.pollLast());
						sb.append(",");
					}
					else if (is_reverse < 0) {
						sb.append(input_lst.pollFirst());
						sb.append(",");
					}
				}
				sb.setLength(sb.length() - 1);
				sb.append("]");
				System.out.println(sb);
			}
			else if (!is_error && input_lst.isEmpty())
				System.out.println("[]");
		}
	}

	static LinkedList<Integer> str_to_lst(String str){
		LinkedList<Integer> lst = new LinkedList<>();

		int idx = 0;
		while (idx < str.length()) {
			StringBuilder sb = new StringBuilder();
			while (idx < str.length() && !('0' <= str.charAt(idx) && str.charAt(idx) <= '9'))
				idx++;
			while (idx < str.length() && ('0' <= str.charAt(idx) && str.charAt(idx) <= '9')) {
				sb.append(str.charAt(idx));
				idx++;
			}
			if (sb.length() != 0)
				lst.add(Integer.valueOf(sb.toString()));
		}
		return (lst);
	}
}
