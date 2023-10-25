#include <iostream>

class ListNode {
public:
    int data;
    ListNode* next;

    ListNode(int value) : data(value), next(nullptr) {}
};

class Stack {
public:
   ListNode* top;

   Stack() : top(nullptr) {}

   bool is_empty() {
      return top == nullptr;
   }

   void push(int data) {
       ListNode* new_node = new ListNode(data);
       new_node->next = top;
       top = new_node;
   }

   int pop() {
       if (!is_empty()) {
           int popped = top->data;

           ListNode* temp = top;
           top = top->next;
           delete temp;
           return popped;
       }else {
          return -1; // Return some sentinel value for an empty stack
       }
   }
};

int main() {
    Stack my_stack;
    

    while (!my_stack.is_empty()) {
        cout << my_stack.pop() << endl;
    }

    return 0;
}