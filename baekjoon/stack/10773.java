import java.util.*;
import java.io.*;

class Anything{
    public static void main(String[] argv) throws IOException {
       BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
       int k = Integer.parseInt(br.readLine());
       Stack<Integer> stack = new Stack<>();
       int num;

       for(int i = 0; i < k; i++){
           num = Integer.parseInt(br.readLine());
           if (num == 0 && !stack.isEmpty()) {
               stack.pop();
               continue;
           }
           stack.add(num);
       }
       int ret = 0;
       while (!stack.isEmpty())
           ret += stack.pop();
       System.out.println(ret);
    }
}
