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

class Queue {
private:
   LinkedList linkedList;

public:
   Queue() {
   }
   
   void Enqueue(int newData) {
      // Create a new node
      Node* newNode = new Node(newData);
       
      // Insert as list tail (end of queue)
      linkedList.Append(newNode);
   }
   
   int Dequeue() {
      // Copy list head's data
      int dequeuedItem = linkedList.headData();
      
      // Remove list head
      linkedList.RemoveAfter(nullptr);
      
      // Return dequeued item
      return dequeuedItem;
   }
   
   void Print(std::ostream& printStream) {
      linkedList.PrintList(printStream);
   }
};

int main()
{
   int numbers[] = { 83, 4, 57, 6, 92, 49, 64, 5 };
      
   // Initialize a new Queue and add numbers
   Queue numQueue;
   for (int number : numbers) {
      numQueue.Enqueue(number);
   }

   // Output queue
   cout << "Queue after initial enqueues: ";
   numQueue.Print(cout);
      
   // Dequeue 83 and print
   numQueue.Dequeue();
   cout << "Queue after first dequeue:    ";
   numQueue.Print(cout);
      
   // Enqueue 99 and print
   numQueue.Enqueue(99);
   cout << "Queue after enqueueing 99:    ";
   numQueue.Print(cout);
      
   // Dequeue 4 and print
   numQueue.Dequeue();
   cout << "Queue after second dequeue:   ";
   numQueue.Print(cout);
    return 0;
}
