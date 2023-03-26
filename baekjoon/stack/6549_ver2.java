import java.io.*;
import java.util.*;

public class Anything {
	public static void main(String[] args) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
		long num, ret;
		int left_idx, right_idx;

		while (true){
			StringTokenizer st = new StringTokenizer(br.readLine(), " ");
			num = Long.parseLong(st.nextToken());
			if (num == 0)
				break ;
			ArrayList<Long> arrayList = new ArrayList<>();
			for (int i = 0; i < num; i++)
				arrayList.add(Long.parseLong(st.nextToken()));

			left_idx = 0;
			right_idx = arrayList.size();
			ret = get_area(left_idx ,right_idx - 1, arrayList);
			System.out.println(ret);
		}
	}

	public static long get_area(int left_idx, int right_idx, ArrayList<Long> arr){
		long ret = 0;

		if (left_idx == right_idx)
			return (arr.get(left_idx));

		int middle = (left_idx + right_idx) / 2;
		//분할된 왼쪽 영역과, 오른쪽 영역에서 최대값이 존재하는 경우를 따져줌
		ret = Math.max(get_area(left_idx, middle, arr),
				get_area(middle + 1, right_idx, arr));
		
		//가운데 영역에 걸쳐서 최대값이 존재하는 경우를 따져줌
		long height = Math.min(arr.get(middle), arr.get(middle + 1));
		long width = 2;
		for (int i = middle - 1; i >= left_idx; i--){
			if (arr.get(i) < height)
				break ;
			width++;
		}
		for (int i = middle + 2; i <= right_idx; i++){
			if (arr.get(i) < height)
				break ;
			width++;
		}
		ret = Math.max(ret, height * width);
		return (ret);
	}
}
