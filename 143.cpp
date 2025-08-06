/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverse_list(ListNode* head) {
        if (!head || !head->next) return head;
        ListNode* prev = nullptr;
        while (head->next) {
            ListNode* next_copy = head->next;
            head->next = prev;
            prev = head;
            head = next_copy;
        }
        head->next = prev;
        return head;
    }
    int list_size(ListNode* head) {
        if (!head) return 0;
        auto ptr = head;
        int sz = 1;
        while (ptr->next) {
            ptr = ptr->next;
            ++sz;
        }
        return sz;
    }
    void reorderList(ListNode* head) {
        if (!head || !head->next) return;
        int n = list_size(head);
        ListNode* ptr2 = head;
        for (int i = 0; i < (n / 2); ++i) {
            ptr2 = ptr2->next;
        }
        ListNode* head2 = ptr2->next;
        ptr2->next = nullptr;
        head2 = reverse_list(head2);
        while (head2) {
            ListNode* next_copy = head->next;
            ListNode* next_copy2 = head2->next;
            head->next = head2;
            head->next->next = next_copy;
            head2 = next_copy2;
            head = next_copy;
        }

    }
};
