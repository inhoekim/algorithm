import java.util.*;
import java.io.*;

class Anything{
    public static void main(String[] argv) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        int test_case = Integer.parseInt(br.readLine());

        for (int i = 0; i < test_case; i++) {
            Stack<Character> stack_left = new Stack<>();
            Stack<Character> stack_right = new Stack<>();
            String input_str = br.readLine();
            for (char ch : input_str.toCharArray()) {
                if (ch == '<') {
                    if (!stack_left.empty())
                        stack_right.add(stack_left.pop());
                } else if (ch == '>') {
                    if (!stack_right.isEmpty())
                        stack_left.add(stack_right.pop());
                } else if (ch == '-'){
                    if (!stack_left.empty())
                        stack_left.pop();
                } else {
                    stack_left.add(ch);
                }
            }
            StringBuilder sb = new StringBuilder();
            while (!stack_right.isEmpty())
                stack_left.add(stack_right.pop());
            while (!stack_left.empty())
                sb.append(stack_left.pop());
            sb.reverse();
            System.out.println(sb);
        }
    }
}
