#include <bits/stdc++.h>
using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int v=0): val(v), next(nullptr) {}
};

struct LinkedList {
    Node* head; // dummy head for easier operations
    int len;

    LinkedList(): head(new Node()), len(0) {}

    void initialize() {
        int n;
        if (scanf("%d", &n) != 1) return;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
        Node* cur = head;
        for (int i = 0; i < n; ++i) {
            Node* t = new Node(a[i]);
            cur->next = t;
            cur = t;
            ++len;
        }
    }

    // insert value x after i-th element (1-indexed). If i==0, insert at beginning.
    void insert(int i, int x) {
        if (i < 0 || i > len) return; // invalid index
        Node* prev = head;
        for (int k = 0; k < i; ++k) prev = prev->next; // move to i-th node
        Node* node = new Node(x);
        node->next = prev->next;
        prev->next = node;
        ++len;
    }

    // delete i-th element (1-indexed)
    void erase(int i) {
        if (i < 1 || i > len) return;
        Node* prev = head;
        for (int k = 1; k < i; ++k) prev = prev->next;
        Node* victim = prev->next;
        prev->next = victim->next;
        delete victim;
        --len;
    }

    // swap odd/even positions: (1,2), (3,4), ... using O(1) extra space
    void swap_pairs() {
        Node* prev = head;
        while (prev->next && prev->next->next) {
            Node* a = prev->next;
            Node* b = a->next;
            a->next = b->next;
            b->next = a;
            prev->next = b;
            prev = a;
        }
    }

    // move first i elements back by x positions: resulting order:
    // A (first i) moves to position i+x, between B (next x) and C (rest)
    // Example in statement matches this behavior.
    void moveback(int i, int x) {
        if (i <= 0 || x <= 0 || i > len || i + x > len) return; // guaranteed not exceed
        // find boundaries: A: [1..i], B: [i+1 .. i+x], C: [i+x+1 .. len]
        Node* prevA = head; // before first element
        Node* tailA = head; // i-th element
        for (int k = 0; k < i; ++k) tailA = tailA->next;

        Node* headB = tailA->next; // may be nullptr if x==0 (but x>0 here)
        Node* tailB = headB;
        for (int k = 1; k < x; ++k) tailB = tailB->next;

        // Now rewire: head -> B -> A -> C
        tailA->next = tailB->next; // A tail points to C
        tailB->next = prevA->next; // B tail points to A head
        prevA->next = headB;       // head points to B head
    }

    int query(int i) {
        if (i < 1 || i > len) return 0; // undefined; but constraints likely valid
        Node* cur = head->next;
        for (int k = 1; k < i; ++k) cur = cur->next;
        return cur->val;
    }

    void printAll() {
        Node* cur = head->next;
        bool first = true;
        while (cur) {
            if (!first) putchar(' ');
            first = false;
            printf("%d", cur->val);
            cur = cur->next;
        }
        putchar('\n');
    }

    void ClearMemory() {
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = nullptr;
        len = 0;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    LinkedList List;
    List.initialize();

    int m; 
    if (scanf("%d", &m) != 1) {
        List.ClearMemory();
        return 0;
    }
    int op, i, x;
    while (m--) {
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &i, &x);
            List.insert(i, x);
        } else if (op == 2) {
            scanf("%d", &i);
            List.erase(i);
        } else if (op == 3) {
            List.swap_pairs();
        } else if (op == 4) {
            scanf("%d%d", &i, &x);
            List.moveback(i, x);
        } else if (op == 5) {
            scanf("%d", &i);
            printf("%d\n", List.query(i));
        } else if (op == 6) {
            List.printAll();
        }
    }
    List.ClearMemory();
    return 0;
}

