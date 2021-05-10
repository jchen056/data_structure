#include <iostream>
//using std::cin;
//using std::cout;
//using std::endl;
using namespace std;
#include <getopt.h> // to parse long arguments.
#include <string>
using std::string;

/* doubly linked list node: */
struct node {
string data;
node* prev;
node* next;
node(string s="", node* p=NULL, node* n=NULL) : data(s),prev(p),next(n) {}
/*last line allows us to declare nodes and initialize them all in one step
--example: node* n=new node("hi");*/
};

// function to create and return a new node of a doubly linked list
/*node* getNode(string data){
    node* newNode =new node;
newNode->data=data;
    return newNode;}*/
//--------------------------------
/*there are many possibilities where we can insert a given string, the beginning, the end, and the middle */
//insert at the beginning of the list
void insert_front(node*& head,string line){
//if the list is empty
if(head==NULL){
head=new node(line);}
//node *newNode=new node(line);
//newNode->next=head;//next node after newnNode is head
//newNode->prev=NULL;//since newNode is in the beginning, newNode->prev is null
head->prev=new node(line,NULL,head);
head=head->prev;//head_prev is new node
}

void insert_between(node*&before,node* after,string line){
node* current=new node(line,before,after);
after->prev=current;
before->next=current;
/*while(current->next!=NULL&&current->next->data<=newNode->data){
current=current->next;}
newNode->next=current->next;
current->next=newNode;
newNode->prev=current;
if(newNode->next!=NULL){
newNode->next->prev=newNode;}*/ }
void insert_end(node *&tail,string line){

//node *last=head;
//newNode is the last node
tail->next=new node(line,tail);
tail=tail->next;
//node *newNode=new node(line);
//newNode->next=NULL;
}
//-----------------------
void insert_sort(node*& head,string line){
//create a new node and put the data in
//node *newNode=new node;
//newNode->data=line;
//node *newNode=new node(line);

node *current;

//starts with empty linklist
if(head==NULL){
//newNode->prev=NULL;
//newNode->next=NULL;
head=new node(line);
}

//insert at the front
if(head->data>=line){
head->prev=new node(line,NULL,head);
head=head->prev;}
//newNode->next=head;//next node after newnNode is head
//head->prev=newNode;
//newNode->prev=NULL;
//since newNode is in the beginning, newNode->prev is null
//head=newNode;
else{
current=head;

//find the location to insert the node
while(current!=NULL){
//insert in between
if(line<=current->data){
node *temp=new node(line,current->prev,current);
current->prev->next=temp;
//newNode->prev=current->prev;
current->prev=temp;
break;}
//newNode->next=current;}
//insert at the end
else if(current->next==NULL){
current->next=new node(line,current);
break;
}
current=current->next;}


}
}

//-----------------------------------
// function to print the doubly linked list
void printList1(node* head)
{
    /*while (head != NULL) {
        cout << head->data << " ";
        head = head->next;*/
node *i;
for(i=head;i!=NULL;i=i->next){
cout<<i->data<<endl;}
    }
void print_reverse(node* head){
if(head==NULL)
return;
node* tail=head;
while(tail->next!=NULL){
tail=tail->next;}
while(tail!=NULL){
cout<<tail->data<<endl;
tail=tail->prev;}
/*for(node *i=tail;i!=NULL;i=i->prev){
cout<<i->data<<endl;}*/
}

void print_list(node*head,int reverse){
if(reverse){
print_reverse(head);}
else
{
printList1(head);}}

/*void reverse_node(node* &head){
node *temp=NULL;
node *current=head;
while(current!=NULL){
temp=current->prev;
current->prev=current->next;
current->next=temp;
current=current->prev;}
if(temp!=NULL){
head=temp->prev;}
}*/
/*-----------------------*/
void remove(node *& head, node* del){
if(head==NULL||del==NULL){
return;}//nothing to be removed

//if the node to be removed is the very first node
if(del==head){
head=del->next;
}
//while the node deleted is not the last one
if(del->next!=NULL){
del->next->prev=del->prev;
del->prev->next=del->next;
}
/*if(del->prev!=NULL){
del->prev->next=del->next;}*/
delete del;//free the space
}

void rem_duplicate(node* &head){
if(head==NULL){
return;}
node* current=head;
while(current->next!=NULL){
if(current->data==current->next->data){
remove(head,current);}
else{
current=current->next;}}
}


bool Uni(string line,node* &head){
for(node*i=head;i!=NULL;i=i->next){
if(line==i->data)
return false;}
return true;}
//-----------------------------
//argc: the count of things entered;
//argv: an array holding the things you enter
int main(int argc, char *argv[]) {
/* define long options */
static int unique=0, reverse=0;
//int unique=0, reverse=0;
static struct option long_opts[] = {
{"unique",   no_argument,       &unique,   'u'},
{"reverse",  no_argument,       &reverse,  'r'},
{0,0,0,0} // this denotes the end of our options.
};
/* process options */
char c; /* holds an option */
int opt_index = 0;
while ((c = getopt_long(argc, argv, "ur", long_opts, &opt_index)) != -1) {
switch (c) {
case 'u':
unique = 1;
break;
case 'r':
reverse = 1;
break;
case '?': /* this will catch unknown options. */
return 1;
}
}
node* head = NULL;
//node *tail=NULL;
string a;

//initialize double linked list so that it is not null
if(getline(cin,a)){
head=new node(a);
//tail=head;}
while(getline(cin,a)){

if(unique==1){
bool cont=Uni(a,head);
if(cont){
insert_sort(head,a);}
}
//no need to worry about duplicates
else{
insert_sort(head,a);
}}}

//case1:insert at the end
/*if(a>tail->data){
insert_end(tail,a);}
//case2: insert in the front
else if(a<head->data){
insert_front(head,a);}
else{
node* temp;
for(temp=head;a>=temp->data;temp=temp->next){
if(temp->next==NULL)
break;
}
if(temp==head){
insert_front(head,a);}
else
insert_between(temp->prev,temp,a);
}}
if(unique)
rem_duplicate(head);*/
//printf("unique=%d,reverse=%d,optind=%d\n",unique,reverse,optind);

print_list(head,reverse);



/* NOTE: at this point, variables 'reverse' and 'unique' have been set
* according to the command line.  */
//node *L=NULL;//starts with an empty linked list
//string line;
/*------------while(getline(cin,line)){
if(L==NULL){
node*x=new node;
x->data=line;
L=x;
x->next=NULL;}
else if(L->next==NULL){
node*y=new node;
y->data=line;
y->next=NULL;
L->next=y;
y->prev=L;}----*/
/*create a node called "left" to keep track of where to place new string*/
/*-----------else{
node *left=L;
if(line<L->data){
insert_front(&L,line);}

node*last=L;
while(last!=NULL){
last=last->next;}
if(line>last->data){
insert_end(&L,line);
}
while(left!=NULL){
if(line>(left->prev->data)&&line<(left->data)){
insert_between(left,line);}
left=left->next;
}}}

while(L!= NULL){
cout<<L->data<<" ";
L=L->next;}-----*/

/* TODO: finish writing this.  Maybe use while(getline(cin,line)) or
* similar to read all the lines from stdin. */
return 0;}