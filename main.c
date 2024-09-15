#include <stdio.h>//file names that are used:-   input file: "InputFile.txt"  , output file: "OutputFile.txt"
#include <stdlib.h>// Taleen Abuzulof 1211061 lecture section: 1

struct node
{
    int Data;// the integer digit
    int Sign ;//when the sign is positive then this would be 1, if negative it will be -1
    struct node* next;// next node in linked list
    struct node* prev;//previous node in linked list
};

struct node* InsertToEmpty(int, struct node*);//to insert a node in an empty list
struct node* InsertAtBeginning(int, struct node*);// to insert a node at the beginning of a list and if the list is empty it creates one
void InsertAtEnd(int, struct node*);// to insert a node at the end of the list
struct node* CreateList(char[]);// takes a string and creates a linked list
void PrintAllLists(struct node*[],int);// prints all the lists available
void PrintList(struct node*);// prints the list needed
void Menu();// the menu of operations
void start();// a start screen
struct node* Add(struct node*,struct node*);// a function that adds two linked lists an d returns the result in a liked list
struct node* Subtract(struct node*,struct node*);// a function that subtracts two linked lists and returns the result in a linked list
struct node* Multiply(struct node*,struct node*);// a function that multiplies two linked lists and returns the result in a linked list
struct node* divide(struct node*,struct node*);// a function that divides two linked lists and returns the result in a linked list
struct node* Selection(struct node* [],int);// takes an array of pointers and  the size of it and returns the selected number for the operation
int NodeCount(struct node*);// takes a linked list and returns the size of it
struct node* larger(struct node*,struct node*);// takes tow linked list and returns the list that is larger between them
struct node* Clone(struct node*);// a function that takes a linked lists and clones it and returns the clone
int Compare(struct node*,struct node*);// a function that compares the big integers in the linked lists
struct node* reverseList(struct node*);// a function to reverse a linked list
void emptyList(struct node*);// a function that empties a linked list
struct node* RemoveLeftZeros(struct node*);// a function that remove the left sided zero from a linked lists
void SaveToFile(struct node*);// a function that prints the result in the output file
void CleanFile();// a function that cleans the output file of old data to write new data after the program is closed


/*note that the linked lists implemented store the big integers from the least significant digit to the most significant digit
for example: 12345 would be stored with a head pointer as    Head-> [5]<->[4]<->[3]<->[2]<->[1]
*/


int main()
{
    CleanFile();
    FILE* in=fopen("InputFile.txt","r");
    int i=0,x,exitFlag1=1,exitFlag2=1;// the exit flags a re important for the while loops, [i] is the size of the array, [x] is the operation selector
    char A[100] ;// a string
    struct node*num1=malloc(sizeof(struct node));
    struct node*num2=malloc(sizeof(struct node));
    struct node*result=malloc(sizeof(struct node));
    struct node* List[100];// the maximum number of large integers that can be read from the input file is 100, Array of pointers
    // each array cell is a pointer to a linked list
    printf("\n\n Application started\n\n");

    while(exitFlag1)
    {
        start();
        scanf("%d",&x);
        if(x==1)
        {
            while((fscanf(in,"%s\n",A))!=EOF)// taking the strings from a file
            {
                List[i]=CreateList(A);
                ++i;
            }
            printf("\n**the input file has been uploaded successfully**");
            printf("\n -> there are %d large integers in the input file\n",i);
            printf("\n choose any two integers numbered from 1 to %d\n",i);
            PrintAllLists(List,i);
            num1=Selection(List,i);/* puts the values selected in num1 and num2*/
            num2=Selection(List,i);
            while(num1==NULL||num2==NULL)// this loops checks if the user entered valid selection number
            {
                printf("\nNo such number/s!\n");
                printf("\n choose any two integers numbered from 1 to %d\n",i);
                PrintAllLists(List,i);
                num1=Selection(List,i);
                num2=Selection(List,i);
            }
            exitFlag1=0;// breaks from the loop
        }
        else if(x==2)// if the user wants to exit it breaks from this loop and future loops
        {
            exitFlag1=0;
            exitFlag2=0;
        }
        else printf("No such Operation\n");// checks that the user entered a valid operation
    }


    while(exitFlag2)
    {
        Menu();
        scanf("%d",&x);
        switch(x)
        {
        case 1:// Addition
        {
            printf("\n");
            if((num1->Sign)==1&&(num2->Sign)==1)// these if statement are used to check the sign and determine the needed operation
            {
                result=Add(num1,num2);
                PrintList(result);
                SaveToFile(result);
            }
            if((num1->Sign)!=(num2->Sign))// if the numbers sign are opposite
            {
                result=Subtract(num1,num2);
                if(Compare(num1,num2)==1)
                    result->Sign=num1->Sign;
                else if(Compare(num1,num2)==0)
                    result->Sign=num2->Sign;
                PrintList(result);
                SaveToFile(result);
            }

            if(num1->Sign==-1&&num2->Sign==-1)// if the numbers have the same negative sign
            {
                result=Add(num1,num2);
                result->Sign=-1;
                PrintList(result);
                SaveToFile(result);
            }

        }
        break;
        case 2:// subtraction
        {
            printf("\n");
            if((num1->Sign==1)&&num2->Sign==1)// if statements checks the sign of the two numbers
            {
                result=Subtract(num1,num2);
                if(Compare(num1,num2)==1)
                    result->Sign=1;
                else result->Sign=-1;
                PrintList(result);
                SaveToFile(result);
            }
            else if(num1->Sign==1&&num2->Sign==-1)
            {
                result=Add(num1,num2);
                PrintList(result);
                SaveToFile(result);
            }
            else if(num1->Sign==-1&&num2->Sign==1)
            {
                result=Add(num1,num2);
                result->Sign=-1;
                PrintList(result);
                SaveToFile(result);
            }
            else
            {
                result=Subtract(num1,num2);
                if(Compare(num1,num2))
                    result->Sign=-1;
                else result->Sign=1;
                PrintList(result);
                SaveToFile(result);
            }
        }
        break;
        case 3://Multiplication
        {
            printf("\n");
            if((num1->Sign)==(num2->Sign))
            {
                result=Multiply(num1,num2);
                PrintList(result);
                SaveToFile(result);
            }
            else
            {
                result=Multiply(num1,num2);
                result->Sign=-1;
                PrintList(result);
                SaveToFile(result);
            }
        }
        break;
        case 4://Division
        {
            printf("\n");
            if (num2 ->Data == 0){
                printf(" Infinity!\n");
                break;
            }
            if((num1->Sign)==(num2->Sign))
            {
                result=divide(num1,num2);
                PrintList(result);
                SaveToFile(result);
            }
            else
            {
                result=divide(num1,num2);
                result->Sign=-1;
                PrintList(result);
                SaveToFile(result);
            }
        }
        break;
        case 5://Print all numbers
        {
            PrintAllLists(List,i);
        }

        break;
        case 6://Exit
            exitFlag2=0;
            break;
        case 7:// choose any two numbers from the array
        {
            printf("\n choose any two integers numbered from 1 to %d\n",i);
            PrintAllLists(List,i);// list is the array and i is the size of it
            num1=Selection(List,i);
            num2=Selection(List,i);
            while(num1==NULL||num2==NULL)
            {
                printf("\nNo such number/s!\n");
                printf("\n choose any two integers numbered from 1 to %d\n",i);
                PrintAllLists(List,i);
                num1=Selection(List,i);
                num2=Selection(List,i);

            }

        }
        break;
        default:
            printf("No such Operation");
        }

    }
    fclose(in);
    return 0;
}

struct node* InsertToEmpty(int x,struct node* P) // P is a pointer to the beginning of the list
{
    struct node* temp=malloc(sizeof(struct node));
    temp->Data=x;
    temp->next=NULL;
    temp->prev=NULL;
    return(P=temp);
};

struct node* InsertAtBeginning(int x, struct node* P)
{
    struct node* temp=malloc(sizeof(struct node));
    if(P!=NULL)// inserts a node at the beginning of a list
    {
        temp->Data=x;
        temp->prev=NULL;
        temp->next=P;
        P->prev=temp;
        return(P=temp);
    }
    else
    {
        P=malloc(sizeof(struct node));// if the list does not exist it will create one
        P->Data=x;
        P->prev=NULL;
        P->next=NULL;
        return P;
    }

};

void InsertAtEnd(int x, struct node* P)
{
    struct node* tp=malloc(sizeof(struct node));
    struct node* temp=malloc(sizeof(struct node));
    temp->Data=x;
    tp=P;
    while(tp->next!=NULL)// a loop to find the end of the list
        tp=tp->next;
    tp->next=temp;
    temp->prev=tp;
    temp->next=NULL;


};


struct node* CreateList(char A[100])// creates a linked list from a string
{
    int negativeflag=0;
    int digit,i=0;
    struct node* head=malloc(sizeof(struct node));
    head=NULL;
    if(A[0]=='-')// if statement to find if the number is negative
    {
        negativeflag=1;
        i++;
    }
    while(A[i]!='\0')// this loops addes the numbers backwards
    {
        digit=A[i]-'0';
        if(head==NULL)
            head=InsertToEmpty(digit,head);
        else InsertAtEnd(digit,head);
        i++;

    }
    head=reverseList(head);// to reverse the list
    if(negativeflag==1)
        head->Sign=-1;
    else head->Sign=1;
    return head;
};

void PrintList(struct node* P)
{
    if(P->Sign==-1)//Prints the sign
        printf("-");
    while(P->next!=NULL)// gets to the last node
        P=P->next;
    printf("%d",P->Data);
    while(P->prev!=NULL)//prints the list in the write order
    {
        P=P->prev;
        printf("%d",P->Data);

    }

    printf("\n");


};

void PrintAllLists(struct node* List[],int n)//Prints every number using the PrintList function
{
    for(int i=0; i<n; i++){
            printf("  %d)   ",i+1);
        PrintList(List[i]);
    }
    printf("\n");
};

void Menu()
{
    printf("\n Choose one of the following operations to perform on the two numbers:\n\n");
    printf(" 1-Addition\n");
    printf(" 2-Subtraction\n");
    printf(" 3-Multiplication\n");
    printf(" 4-Division\n");
    printf(" 5-Print all numbers\n");
    printf(" 6-Exit\n");
    printf(" 7-Choose another two numbers\n");
};

void start()
{

    printf("1-Read the input file\n");
    printf("2-Exit\n");
};

int NodeCount(struct node*P)//finds the size of a Linked list
{
    int count=0;
    while(P!=NULL)
    {
        count++;
        P=P->next;
    }
    return count;
};

struct node* larger(struct node* P,struct node* L)// returns the largest number between two numbers
{
    if((NodeCount(P))>(NodeCount(L)))//if the node count on number one is greater than number two then it returns num1
        return P;
    else if((NodeCount(L))>(NodeCount(P)))
        return L;
    struct node* temp1=P;
    struct node* temp2=L;
    while(temp1->next!=NULL)// if both numbers have the same digit size then it compares each digit to find the larger
    {
        temp1=temp1->next;
        temp2=temp2->next;
    }
    while(temp1!=NULL)
    {
        if((temp1->Data)>(temp2->Data))
            return P;
        else if((temp2->Data)>(temp1->Data))
            return L;
        temp1=temp1->prev;
        temp2=temp2->prev;
    }
    return NULL;// if the loops above end then the two numbers are equal, then the function returns NULL
};

int Compare(struct node* num1,struct node* num2)// it uses the larger function and returns 1,0, or -1
{
    struct node*P=malloc(sizeof(struct node));
    P=larger(num1,num2);
    if(P==num1)
        return 1;//num1 is bigger, it returns 1
    else if(P==num2)
        return 0;//num2 is bigger, it returns 0
    else return -1;//they are equal, it returns -1
};


struct node* Add(struct node* num1,struct node* num2)
{
    int carry=0;
    struct node* res=malloc(sizeof(struct node));
    if(Compare(num1,num2)==1)// if the first one is larger
    {
        int sum=0,resDigit;
        sum=carry+num1->Data+num2->Data;//first hand summation with carry
        carry=sum/10;// new carry
        resDigit=sum%10;// the actual result digit
        res=InsertToEmpty(resDigit,res);
        num1=num1->next;
        num2=num2->next;
        while(num2!=NULL)
        {
            sum=carry+num1->Data+num2->Data;
            carry=sum/10;
            resDigit=sum%10;
            InsertAtEnd(resDigit,res);
            num1=num1->next;
            num2=num2->next;
        }
        while(num1!=NULL)
        {
            sum=carry+num1->Data;
            carry=sum/10;
            resDigit=sum%10;
            InsertAtEnd(resDigit,res);
            num1=num1->next;
        }
        if(carry!=0)
            InsertAtEnd(carry,res);
        return RemoveLeftZeros(res);
    }

    else if(Compare(num1,num2)==0)// if the second one is larger it switches the numbers and compares them again using recursion
        return Add(num2,num1);

    else
    {
        struct node* clone=Clone(num1);// if both are equal then it inserts a zero on the left of the number
        InsertAtEnd(0,clone);// this way when the two numbers are evaluated again it will declare the first one bigger
        return Add(clone,num2);// uses recursion just like the last part
    }
};

struct node* Multiply(struct node* num1,struct node* num2)
{
    int mult,carry=0,resDigit,zeroConcat,i;// mult is the single digit multiplication, zero concat is the concatination of zeros needed in normal miltiplication
    struct node* L=malloc(sizeof(struct node));
    struct node* res1=malloc(sizeof(struct node));
    res1=NULL;
    struct node* res2=malloc(sizeof(struct node));
    res2=NULL;
    if(Compare(num1,num2))
    {
        zeroConcat=NodeCount(num2)-1;// the zero addition is always less that the least number digit size by one
        i=zeroConcat;
        while(num2!=NULL)// a while loop to multiply each digit of number two and then add
        {
            if(res1==NULL)// this is the first time the multiplication is performed
            {
                L=num1;
                mult=((num2->Data)*(L->Data))+carry;// first hand digit multiplication
                carry=mult/10;// carry to the second digit
                resDigit=mult%10;// the res1 result digit
                res1=InsertToEmpty(resDigit,res1);// creates res1
                L=L->next;
                while(L!=NULL)
                {
                    mult=(num2->Data)*(L->Data)+carry;
                    carry=mult/10;
                    resDigit=mult%10;
                    InsertAtEnd(resDigit,res1);
                    L=L->next;

                }
                if(carry!=0)
                    InsertAtEnd(carry,res1);// checks if the last carry in non-zero to add it
            }
            else// if this is not the first time the operation is performed it will calculate res2
            {
                L=num1;
                res2=InsertToEmpty(0,res2);
                for(int j=i; j<zeroConcat; j++)// this for loop is used to concat zeros to res2
                    InsertAtEnd(0,res2);
                i--;
                carry=0;
                while(L!=NULL)// a loop to multiply the rest of num2 digits with num1 and add the carry
                {
                    mult=(num2->Data)*(L->Data)+carry;
                    carry=mult/10;
                    resDigit=mult%10;
                    InsertAtEnd(resDigit,res2);
                    L=L->next;
                }
                if(carry!=0)
                    InsertAtEnd(carry,res2);// if the carry is not zero then it will add it to res2
                res1=Add(res1,res2);// this line adds res1 and res2 and puts the result in res1 so it can be used in the next iteration
            }
            num2=num2->next;

        }

        return res1;
    }
    else if(Compare(num1,num2)==0)//if the first number is smaller than the second one then it will switch the two numbers using recursion
        return Multiply(num2,num1);
    else
    {
        struct node* clone=Clone(num1);// if both numbers are equal then it will insert a zero on the left of number1
        InsertAtEnd(0,clone);
        return Multiply(clone,num2);// wen the two numbers are compared again the first number will be larger

    }
};

struct node* Subtract(struct node* num1,struct node* num2)// subtraction num1-num2
{
    int resDigit;
    struct node* P=malloc(sizeof(struct node));
    struct node* temp=malloc(sizeof(struct node));
    struct node* res=malloc(sizeof(struct node));
    P=larger(num1,num2);// P now points to the larger linked list
    if(P==num1)// if num1 is larger
    {
        if((num1->Data)>=(num2->Data))
            resDigit=(num1->Data)-(num2->Data);// if the digit from num11 is greater that the digit of num2 it subtracts with no problems
        else
        {
            P=Clone(num1);// it clones num1 so the changes done to it in this function would not effect it in the main
            temp=P;
            while(temp->next==0)// if the next digit is 0 then it becomes 9
            {
                temp->next->Data=9;
                temp=temp->next;
            }
            (temp->next->Data)=(temp->next->Data)-1;// borrow one from the next digit
            resDigit=(P->Data)+10-(num2->Data);//calculates the result digit
        }
        res=InsertToEmpty(resDigit,res);
        P=P->next;
        num2=num2->next;
        while(num2!=NULL)// continues the last line of code but in a loop
        {
            if(P->Data>=num2->Data)
                resDigit=(P->Data)-(num2->Data);
            else
            {
                temp=P;
                while(temp->next==0)
                {
                    temp->next->Data=9;
                    temp=temp->next;
                }
                --(temp->next->Data);
                resDigit=(P->Data)+10-(num2->Data);
            }
            InsertAtEnd(resDigit,res);
            P=P->next;
            num2=num2->next;
        }
        while(P!=NULL)// if there are some left digits in num1 then it puts them in the result
        {
            InsertAtEnd(P->Data,res);
            P=P->next;
        }

        return RemoveLeftZeros(res);
    }

    else if(P==num2)// if num2 is larger then it switches the numbers
        return Subtract(num2,num1);

    else// if both numbers are equal then the answere is zero
    {
        return CreateList("0");
    }
};

struct node* Selection(struct node*List[],int n)// takes an array and it's size and prompts the user to select a number which then is returned as a linked list
{
    struct node* temp=malloc(sizeof(struct node));
    int x=0,i=0;
    scanf("%d",&x);
    --x;
    while(i<n)// searches for the number
    {
        if(i==x)
        {
            temp=List[i];
            return temp;
        }
        i++;
    }
    return NULL;
};

struct node* Clone(struct node* List)// it clones a linked list
{
    int x=List->Data;
    struct node* clone=malloc(sizeof(struct node));
    clone->Sign=List->Sign;// copies the sign
    clone=InsertToEmpty(x,clone);// creates the clone
    List=List->next;
    while(List!=NULL)// copies each data
    {
        x=List->Data;
        InsertAtEnd(x,clone);
        List=List->next;
    }
    return clone;
};
struct node* divide(struct node* dividend,struct node* divisor)//division
{
    struct node* remainder=malloc(sizeof(struct node));//remainder of the division operation
    struct node* subDividend=malloc(sizeof(struct node));// a small part of the dividend
    struct node* result=malloc(sizeof(struct node));
    struct node* nextDigit=Clone(dividend);// the next digit of the dividend to insert
    nextDigit=reverseList(nextDigit);
    subDividend=NULL;
    struct node* P=malloc(sizeof(struct node*));
    P=larger(dividend,divisor);
    if(P==dividend)// if the first number is larger proceed
    {
        while(nextDigit!=NULL)
        {
            int digit=0;
            subDividend=InsertAtBeginning(nextDigit->Data,subDividend);
            while(Compare(subDividend,divisor)==1||Compare(subDividend,divisor)==-1)
            {
                remainder=Subtract(subDividend,divisor);
                subDividend=remainder;
                while(subDividend->prev!=NULL)
                    subDividend=subDividend->prev;
                digit++;
            }
            result=InsertAtBeginning(digit,result);
            nextDigit=nextDigit->next;
        }

        return RemoveLeftZeros(result);
    }
    else if(P==divisor)// if the second number is larger then the answer is simply zero since it's an integer division
        return result=CreateList("0");
    else
        return result=CreateList("1");// if the two numbers are equal then the answer is 1

};

struct node* reverseList(struct node* head)// reverses a linked list
{
    struct node* temp = NULL;
    struct node* current= head;

    while (current!=NULL)
    {
        temp=current->prev;// stores the previous address in temp
        current->prev=current->next;// modifies the previous to the next
        current->next=temp;//modifies the next to the previous using temp
        current=current->prev;// since the previous has been modified to the old next
    }
    if (temp!=NULL)// in case the list has only one node
        head=temp->prev;

    return head;
}

void emptyList(struct node* head)// it takes a list and empties it of nodes
{
    struct node* current =head;
    struct node* next;

    while (current!= NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    head = NULL;
};

struct node* RemoveLeftZeros(struct node* head)// remove the left zeros of a number
{

    struct node* temp=malloc(sizeof(struct node*));
    while(head->next!=NULL)
        head=head->next;// traverses the linked list
    while(head->Data==0)// a loop in case there are more than one left zero
    {
        temp=head->prev;
        head->prev=NULL;
        temp->next=NULL;
        free(head);
        head=temp;
    }
    return head;


};

void SaveToFile(struct node* P)// takes a linked list and saves it to the output file
{
    char digit;
    FILE* out=fopen("OutputFile.txt","a");
    if(P->Sign==-1)
        fprintf(out,"-");
    while(P->next!=NULL)
    {
        P=P->next;
    }
    while(P!=NULL)
    {
        digit=(P->Data)+'0';
        fprintf(out,"%c",digit);
        P=P->prev;

    }
    fprintf(out,"\n");

    fclose(out);

};

void CleanFile()// cleans the file every time the program runs
{
    FILE* k=fopen("OutputFile.txt","w");// opens the file for writing which by default clears any data stored previously
    fclose(k);

};



