import java.util.*;
import java.io.*;

class Anything{
    public static void main(String[] argv) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine(), " ");
        StringBuilder sb = new StringBuilder();
        int k, n ,cnt, element;
        k = Integer.parseInt(st.nextToken());
        n = Integer.parseInt(st.nextToken());
        sb.append("<");
        LinkedList<Integer> lst = new LinkedList<>();
        for (int i = 1; i <= k; i++)
            lst.add(i);
        cnt = 0;
        while (!lst.isEmpty()) {
            Iterator<Integer> lst_iter = lst.iterator();
            while (lst_iter.hasNext()){
                element = lst_iter.next();
                cnt++;
                if (cnt == n) {
                    sb.append(Integer.toString(element));
                    lst_iter.remove();
                    if (!lst.isEmpty())
                        sb.append(", ");
                    cnt = 0;
                }
            }
        }
        sb.append(">");
        System.out.println(sb);
    }
}
