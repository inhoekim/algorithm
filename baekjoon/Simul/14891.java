import java.io.*;
import java.util.StringTokenizer;

public class Anything {
	public static int gears[] = new int[4];
	public static boolean visited[] = new boolean[4];
	public static int max_bit = Integer.parseInt("100000000", 2);
	public static void main(String[] args) throws IOException{
		//입력 part
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		gears[0] = Integer.parseInt(br.readLine(), 2);
		gears[1] = Integer.parseInt(br.readLine(), 2);
		gears[2] = Integer.parseInt(br.readLine(), 2);
		gears[3] = Integer.parseInt(br.readLine(), 2);
		int k = Integer.parseInt(br.readLine());
		//본로직 part
		for (int i = 0; i < k; i++) {
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			int gear_idx = Integer.parseInt(st.nextToken());
			int direction = Integer.parseInt(st.nextToken());
			//visited 배열 초기화
			for(int j = 0; j < 4; j++)
				visited[j] = false;
			init_rotate(gear_idx - 1, direction);
		}
		//출력 part
		int ret = 0;
		int point = 1;
		for (int i = 0; i < 4; i++) {
			StringBuilder gear_str = new StringBuilder(Integer.toString(gears[i], 2));
			while (gear_str.length() != 8)
				gear_str.insert(0, '0');
			if(gear_str.charAt(0) == '1')
				ret += point;
			point *= 2;
		}
		System.out.println(ret);
	}

	public static void init_rotate(int gear_idx, int direction){
		visited[gear_idx] = true;
		int left_gear_idx = gear_idx - 1;
		int right_gear_idx = gear_idx + 1;
		//양 옆의 톱니바퀴들의 회전여부 검사 및 회전시키기
		if (left_gear_idx >= 0 && !visited[left_gear_idx])
			if (((gears[left_gear_idx] + max_bit >> 5) & 1)
					!= ((gears[gear_idx] + max_bit >> 1) & 1))
				init_rotate(left_gear_idx, direction * -1);
		if (right_gear_idx <= 3 && !visited[right_gear_idx])
			if (((gears[right_gear_idx] + max_bit >> 1) & 1)
					!= ((gears[gear_idx] + max_bit >> 5) & 1))
				init_rotate(right_gear_idx, direction * -1);
		//자신의 톱니들을 direction에 맞게 회전시킴
		int gear = gears[gear_idx];
		if (direction < 0){
			gear = gear << 1;
			if (gear >= max_bit)
				gears[gear_idx] = gear - max_bit + 1;
			else
				gears[gear_idx] = gear;
		}else{
			if ((gear & 1) == 1)
				gear += max_bit;
			gears[gear_idx] = gear >> 1;
		}
	}
}

