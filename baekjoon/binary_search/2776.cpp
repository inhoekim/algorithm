#include <set>
#include <sstream>

using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int N;
        scanf("%d", &N);
        set<int> note_one;
        stringstream ss;
        for (int i = 0; i < N; i++) {
            int num;
            scanf("%d", &num);
            note_one.insert(num);
        }
        scanf("%d", &N);
        for (int i = 0; i < N; i++) {
            int target_num;
            scanf("%d", &target_num);
            if (note_one.find(target_num) != note_one.end())
               ss << "1\n";
            else
                ss << "0\n";
        }
        printf("%s", ss.str().c_str());
    }
    return 0;
}
