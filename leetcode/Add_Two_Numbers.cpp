class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        bool digit = false;
        bool l1_flag = false, l2_flag = false, flag = false;
        ListNode* first = new ListNode(0);
        ListNode* list = first;
        while(!(l1_flag && l2_flag && !digit)) {
            int a = 0, b = 0;
            if(l1_flag) a = 0;
            else a = l1->val;
            if(l2_flag) b = 0;
            else b = l2->val;
            int addTwo = a + b;
            if(digit) {
                addTwo++;
                digit = false;
            }
            if (addTwo >= 10) {
                addTwo %= 10;
                digit = true;
            }
            list->val = addTwo;

            if(l1->next == nullptr) l1_flag = true;
            if(l2->next == nullptr)  l2_flag = true;

            if(!l1_flag) l1 = l1->next;
            if(!l2_flag) l2 = l2->next;
            if (!(l1_flag && l2_flag && !digit) ) {
                ListNode * temp = new ListNode();
                list->next = temp;
                list = list->next;
            }
        }
        return first ;
    }
};
