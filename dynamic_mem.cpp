#include <iostream>
using std::cin;
using std::cout;
using namespace std;
/* NOTE: you have to explicitly give the size of the array,
 * since arrays don't know their own size (contrast with
 * vectors). */
/* This function accepts an array of n elements, and will
 * resize it to point to an array of m elements.  The first
 * min(n,m) elements will be preserved. */
/* TODO: make sure you understand the parameter list: the first
 * param (A) is a pointer *passed by reference*.  NOTE: in the
 * C language, you would just give A as type int** instead. */
void resize(int*& A, size_t n, size_t m)
{
int* B = new int[m]; /* step 1 */
size_t c = n; /* number of elements to copy */
if (m < n) c = m;
for (size_t i = 0; i < c; i++) {
B[i] = A[i]; /* step 2 */
}
delete [] A; /* step 3 */
A = B; /* step 4 */
// &A = B; // Doesn't quite make sense: LHS (&A) would have type int**
}

int main()
{
/* TODO: use the resize function to read all of stdin into array A.
* Double the size when you run out of space. */
int* A = new int[10];
// int A[10]; /* for static arrays, there is no A!! */
int a;
size_t i=0;
size_t m=10;//original size of the array
size_t n=0;//size of the array afterwards
while(cin>>a){
if (i==m){
n=2*m;
resize(A,m,n);
m=2*m;}
A[i]=a;
i++;}
/* TODO: try to understand why you can't resize a static array
* (e.g. if A was declared as the commented line above). */

resize(A,m,20);
for (size_t j=0;j<20;j++){
cout<<A[j]<<" ";}
cout<<"\n";
/* NOTE: you can do arithmetic with pointers.  In fact this
* is happening all the time when you use A[i]: This is just
* shorthand for *(A+i). */
//printf("A   == %p\n",A);
//printf("A+1 == %p\n",A+1);
/* NOTE: if A points to an int, A+x gives you the memory address
* x*sizeof(int) after the address in A (scaling happens automatically!)
* For a char* pointer (see below), C+x will just be x away from the
* address of C, since char takes a single byte.  */
//char* C = new char[10];
//printf("C   == %p\n",C);
//printf("C+1 == %p\n",C+1);
//delete [] A;
//delete [] C;
return 0;
}
