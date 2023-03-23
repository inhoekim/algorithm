import java.util.*;
import java.io.*;

class Anything{
    public static void main(String[] argv) throws IOException {
        Stack<Character> stack_left = new Stack<>();
        Stack<Character> stack_right = new Stack<>();
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String init_str = br.readLine();
        int m = Integer.parseInt(br.readLine());

        for (char ch : init_str.toCharArray())
            stack_left.add(ch);
        for (int i = 0; i < m; i++) {
            String oper = br.readLine();
            if (oper.charAt(0) == 'P')
                stack_left.add(oper.charAt(2));
            else if (oper.charAt(0) == 'L') {
                if (!stack_left.empty())
                    stack_right.add(stack_left.pop());
            } else if (oper.charAt(0) == 'D') {
                if (!stack_right.isEmpty())
                    stack_left.add(stack_right.pop());
            } else {
                if (!stack_left.empty())
                    stack_left.pop();
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
