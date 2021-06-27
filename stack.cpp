//stack 

#include <iostream>
using namespace std;

//create node class and linkedlist class which has dummy variables for head and tail
class Node {
public:
   int data;
   Node* next;

   Node(int initialData) {
      data = initialData;
      next = nullptr;
   }
};
class LinkedList {
private:
   Node* head;
   Node* tail;
   
public:
   LinkedList() {
      head = nullptr;
      tail = nullptr;
   }
//linkedList operations
    int headData(){
       return head->data;
   }
   void InsertAfter(Node* currentNode, Node* newNode) {
   if (head == nullptr) {
      head = newNode;
      tail = newNode;
   }
  
   else if (currentNode == tail) {
      tail->next = newNode;
      tail = newNode;
   }
   else {
      newNode->next = currentNode->next;
      currentNode->next = newNode;
   }
}
    void Prepend(Node* newNode) {
      if (head == nullptr) {
         head = newNode;
         tail = newNode;
      }
      else {
         newNode->next = head;
         head = newNode;
      }
   }
   void Append(Node* newNode) {
      if (head == nullptr) {
         head = newNode;
         tail = newNode;
      }
      else {
         tail->next = newNode;
         tail = newNode;
      }
   }
    void RemoveAfter(Node* currentNode) {
      if (currentNode == nullptr && head) {
         // Special case: remove head
         Node* nodeBeingRemoved = head;
         head = head->next;
         delete nodeBeingRemoved;
         
         if (head == nullptr) {
             // Last item was removed
             tail = nullptr;
         }
      }
      else if (currentNode->next) {
         Node* nodeBeingRemoved = currentNode->next;
         Node* succeedingNode = currentNode->next->next;
         currentNode->next = succeedingNode;
         delete nodeBeingRemoved;
         if (succeedingNode == nullptr) {
            // Remove tail
            tail = currentNode;
         }
      }
   }
   void PrintList(std::ostream& printStream, const std::string& separator = ", ") {
      Node* node = head;
      if (node) {
          // Head node is not preceded by separator
          printStream << node->data;
          node = node->next;
      }
      while (node) {
         printStream << separator << node->data;
         node = node->next;
      }
      printStream << std::endl;
   }
};

class Stack {
private:
   LinkedList linkedList;

public:
   Stack() {
   }
   
   void Push(int newData) {
      // Create a new node and prepend
      Node* newNode = new Node(newData);
      linkedList.Prepend(newNode);
   }
   
   int Pop() {
      // Copy list head's data
      int poppedItem = linkedList.headData();
      
      // Remove list head
      linkedList.RemoveAfter(nullptr);
      
      // Return popped item
      return poppedItem;
   }
   
   void Print(std::ostream& printStream) {
      linkedList.PrintList(printStream);
   }
};


int main()
{
   int numbers[] = { 91, 66, 9, 46, 23, 65, 6, 77 };
      
   // Initialize a new Stack and add numbers
   Stack numStack;
   for (int number : numbers) {
       numStack.Push(number);
   }

   // Output stack
   cout << "Stack after push:       ";
   numStack.Print(cout);
      
   // Pop 77 and print
   numStack.Pop();
   cout << "Stack after first pop:  ";
   numStack.Print(cout);
      
   // Pop 6 and print
   numStack.Pop();
   cout << "Stack after second pop: ";
   numStack.Print(cout);
    return 0;
}
