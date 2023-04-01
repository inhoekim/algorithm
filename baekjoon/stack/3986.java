import java.io.*;
import java.util.*;


public class Anything {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(br.readLine());
		int ret = 0;
		while (n-- != 0){
			Stack<Character> st = new Stack<>();
			String word = br.readLine();
			for (int i = 0; i < word.length(); i++){
				char curr_alpha = word.charAt(i);
				if (!st.isEmpty() && st.peek() == curr_alpha)
					st.pop();
				else
					st.push(curr_alpha);
			}
			if (st.isEmpty())
				ret++;
		}
		System.out.println(ret);
	}
}
