/*
Write a function which takes a pointer to the beginning of a linked list of integers (that is, a pointer to the first node) and an integer d > 0 and returns a pointer to a new list whose nodes have only integers from the original list which were divisible by d (meaning they would leave no remainder when divided by d). For example, if d = 2 and all list items are odd, then the returned list should be empty. If d = 1, then everything satisfies the condition and you should return a copy of the original list. Here is a prototype for the function:



node* divisibleby(node* L, int d);
*/

#include<iostream>
using namespace std;

struct node{
  int data;
  node* next;};

void divisibleby(node* L, int d,node* &result){
  //dummy node in the returned list
  node R;//dummy node that stores no data
  R.next=NULL;

  node *l=&R;//l will point to last node in returned linked list
  node* p=L;//p will be used to go through nodes in linked list L
  if (L==NULL){
    exit(-1);}//no elements in the linked list
  while(p!=NULL){
    if((p->data)%d==0){
      l->next=new node;
      l=l->next;
      l->data=p->data;
      }
    p=p->next;}
  l->next=NULL;
  result=R.next;
  }

int main(){
  node R;//dummy node with no data, not used
  R.next=NULL;
  node* e=&R;//points to the end node of returned linked list

  /*read inputs from the user and store all the info on a linked list*/
  int n;
  while(cin>>n){
    e->next=new node;
    e=e->next;
    e->data=n;}
  e->next=NULL;

  node *result;
  divisibleby(R.next,2,result);

  //print the results
    for(node* i=result;i!=NULL;i=i->next){
      cout<<i->data<<" ";}
    cout<<"\n";
  return 0;}
