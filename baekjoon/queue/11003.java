import java.io.*;
import java.util.*;

public class Anything {
	public static void main(String[] args) throws IOException{
		//입출력 part
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(br.readLine(), " ");
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		LinkedList<Nbr> lst = new LinkedList<>();
		st = new StringTokenizer(br.readLine(), " ");
		StringBuilder sb = new StringBuilder();
		//본로직 part
		int	new_num;
		int lst_size = 0;
		for (int i = 0; i < n; i++)
		{
			int inside_cnt = 1;
			new_num = Integer.parseInt(st.nextToken());
			//주어진 L 범위가 다 차있는 상태
			if (lst_size == m) {
				// 새로운 new_num을 추가하기위해 가장 앞에 있는 숫자를 L 범위에서 제외
				Nbr front_nbr = lst.pollFirst();
				if (front_nbr.inside_cnt > 1) { //이때 만약 제거할려는 숫자가 압축되어진 숫자였다면 inside_cnt를 1개 없애고 다시 집어넣는다
					front_nbr.inside_cnt--;
					lst.addFirst(front_nbr);
				}
				//앞 숫자를 제거하여 공간을 1칸 비우고 new_num을 뒤에다 삽입
				//삽입과정에서 숫자 압축이 필요한경우 압축을 해준다
				if (lst.isEmpty() || new_num > lst.peekLast().value)
					lst.add(new Nbr(new_num, 1));
				else { //숫자압축 과정
					while (!lst.isEmpty() && new_num <= lst.peekLast().value)
						inside_cnt += lst.pollLast().inside_cnt;
					lst.add(new Nbr(new_num, inside_cnt));
				}
				sb.append(lst.peekFirst().value + " ");
			}
			//아직 L 범위를 다 채우지 못해 공간이 남는 상황 (앞숫자를 비우지않고 new_num을 추가함)
			if (lst_size < m) {
				if (lst.isEmpty() || new_num > lst.peekLast().value)
					lst.add(new Nbr(new_num, 1));
				else {
					while (!lst.isEmpty() && new_num <= lst.peekLast().value)
						inside_cnt += lst.pollLast().inside_cnt;
					lst.addLast(new Nbr(new_num, inside_cnt));
				}
				lst_size++;
				sb.append(lst.peekFirst().value + " ");
			}
		}
		sb.setLength(sb.length() - 1);
		System.out.println(sb);
	}
}

class Nbr {
	int value, inside_cnt;

	public Nbr(int value, int inside_cnt){
		this.value = value;
		this.inside_cnt = inside_cnt;
	}

}
