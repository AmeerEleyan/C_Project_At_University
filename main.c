#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100 // the max numbers of books  which can added on the book store
#define NAMESIZE 50 // max size of a book name
/**********************************************
*    Author: Amir Mohammad Eleyan             *
*    ID: 1191076.                             *
*    Section: (4) Dr.Sobhi                    *
*    Date: 13/5/2020.                         *
***********************************************/
void displayMainMenu();
void addBook(char [][NAMESIZE],int [],double [],int []);
void uploadDataFile(char [][NAMESIZE],int [],double [],int []);
void removeBook(char [][NAMESIZE],int [],double [],int []);
void searchForBook(char [][NAMESIZE],int [],double [],int []);
void printBookList(char [][NAMESIZE],int [],double [],int []);
void updataDataFile(char [][NAMESIZE],int [],double [],int []);
void sorting(char [][NAMESIZE],int [],double [],int []);
void stop_or_continue(int *temp);
int size=0; /// number of books
int main()
{
    int choice;
    int bins[MAXSIZE];
    int status[MAXSIZE];
    double prices[MAXSIZE];
    char name[MAXSIZE][NAMESIZE];
    uploadDataFile(name,bins, prices,status);///to gets data from file book.txt
    printf("\nThe Data You Have Read from file books.txt: \n");
    displayMainMenu(); /// view Operations for the user
    scanf("%d",&choice);/// to get Operation
    while (choice != 5)
    {
        switch (choice)
        {
        case 1: printBookList(name,bins, prices, status); break; /// to Display data of books for the user
        case 2: addBook(name,bins, prices,status); break;/// to add a new book
        case 3: searchForBook(name,bins, prices,status); break;/// to search a  book
        case 4: removeBook(name,bins, prices,status);break;/// to remove a  book
        default: printf(" No such Operation! Please try again.\n");
        }
        displayMainMenu();
        scanf("%d",&choice);
    }
    updataDataFile(name,bins, prices,status); /// Add the new data in file books.txt
    printf("\nThank you for using My BookStore Management System. GoodBye\n");

    return 0;
}
void displayMainMenu()/// view Operations for the user
{
    printf("\nPlease Select an Operation (1-5):\n");
    printf("1- Print Book list\n");
    printf("2- Add a book\n");
    printf("3- Search a Book\n");
    printf("4- Remove a Book\n");
    printf("5- Exit System\n");
}
void uploadDataFile(char name[][NAMESIZE],int bins[],double prices[],int status[]) ///to gets data from file book.txt
{
    FILE *readData;
    readData=fopen("books.txt","r"); /// open the file books.txt ...to obtain the data of books
    if(readData==NULL) /// if Can not open file books.txt
    {
        printf("\nThe File does NOT exist(Cannot open file)...GoodBye\n") ;
        exit(0); /// exist the program
    }
    printf("\nWelcome to My BookStore Management System: ");
    printf("\n\nUploading Data File ...\n");
    while(fscanf(readData," %s%d%lf",name[size],&bins[size],&prices[size])!=EOF ) ///to gets data from file book.txt
    {
        status[size]=1; /// set the status of book number (size) equal one
        size++; /// increment number of books by one
        if(size==MAXSIZE)
            break; /// if the number of books is equal the maxsize
    }
    fclose(readData); /// close file read data
    printf("Data File uploaded\n ");
}
void addBook(char name[][NAMESIZE],int bins[],double prices[], int status[])/// to add a new book
{
    int temp;
    do
    {
        if(size<MAXSIZE) /// add new book if the book store is not full
        {
            int bin,flag=1;
            printf(" Enter bin number for book:  ");
            scanf("%d",&bin); // get the bin number of book
            for(int i=0; i<size; i++) /// check if the new book added is in the book store or not
            {

                if(bin==bins[i]) // the new bin number of book is in the book store
                {
                    if(status[i]==1) // the status of old book is one
                    {
                        while(bin==bins[i]&&status[i]==1) /// the new book added is exist in library
                        {
                            printf(" This bin %d already Exist,please enter any bin number book OR enter zero if you\n do NOT want to add the Book: :  ",bin);
                            scanf("%d",&bin);
                            i=0;
                            if(bin==0)
                                return; // if the user wants not to add a new book and out of this function
                        }
                    }
                    else if(status[i]!=1)  // if the bin number of new book is exist but the status equal zero
                    {
                        status[i]=1;/// set the status of new book one
                        flag=0;
                        printf(" Enter the name of the book: ");
                        scanf(" %s",name[i]);// get the name of the new book
                        printf(" Enter the price of book:  ");
                        scanf("%lf",&prices[i]); // get the price of the new book
                    }
                }
            }

            if(flag) /// if the new bin number of book is not in the library
            {
                printf(" Enter the name of the book: ");
                scanf(" %s",name[size]);// get the name of the new book
                printf(" Enter the price of book:  ");
                scanf("%lf",&prices[size]); // get the price of the new book
                bins[size]=bin; /// storage the new bin number of book in the matrix bins
                status[size]=1; /// set the status of new book one
                size++; /// increment the number of book in book store by one
                printf(" Book with bin number %d has been added\n",bin);
            }
            else /// if the new bin number of book is exist in the library and the his status equal one
                printf(" Book with bin number %d has been added\n",bin);
        }
        else /// if the book store is free of books (numbers of books zero)
            printf(" Sorry.The book store is FULL.\n");

        stop_or_continue(&temp); /// if the user want add another book to library or not
    }
    while(temp==1); /// if the user want add another book to library
}
void removeBook(char name[][NAMESIZE],int bins[],double prices[],int status[]) /// to remove a book
{
    int temp;
    do
    {
        if(size == 0 )/// if the book store is free of books (numbers of books zero)
        {
            printf(" The book store is free of books\n");
            return;
        }
        else
        {
            int bin,flag=1;
            printf(" Please Enter the bin number for book  to remove:  ");
            scanf("%d",&bin);/// get the bin of the book the user wants to remove it
            for(int i=0; i<size; i++)///to check if the book the user wants to remove it,is already exist on book store
            {
                if(bin==bins[i] && status[i]==1)
                {
                    status[i]=0; /// set status of the book which was removed equal zero
                    flag=0;
                    printf(" Book with bin number %d has been Removed\n",bin);
                    break;
                }
            }

            if(flag)/// the book the user wants to remove it does not exist on book store
                printf(" Book with bin number %d does NOT exist\n",bin);
        }
        stop_or_continue(&temp); /// if the user want remove another book to library or not
    }
    while(temp==1); /// if the user want add remove another book to library
}
void searchForBook(char name[][NAMESIZE],int bins[],double prices[],int status[]) /// to search a book
{
    int temp;
    do
    {
        if(size == 0 )/// if the book store is free of books (numbers of books zero)
        {
            printf(" The book store is free of books\n");
            return;
        }
        else
        {
            int bin,flag=1;
            printf(" Please Enter bin number of the book to search for:  ");
            scanf("%d",&bin);/// get the bin of the book the user was searching for
            for(int i=0; i<size; i++)///to check if the book added the user was searching for already exist on book store
            {
                if(bin==bins[i] && status[i]==1)
                {
                    printf("\n Name: %s\tbin number = %d\tPrice = %.2f\n",name[i],bins[i],prices[i]); /// view the data for the book the user was searching for
                    flag=0;
                    break;
                }
            }
            if(flag) /// if the book does not exist in book store
                printf(" Book with bin number %d does NOT exist in book store...\n",bin);
        }
        stop_or_continue(&temp);/// if the user want search another book to library or not
    }
    while(temp==1); /// if the user want search another book to library
}
void sorting(char name[][NAMESIZE],int bins[],double prices[],int status[]) // to sort books in ascending order by bins
{
    int temp_bins_status;
    double temp_prices;
    char str[NAMESIZE];
    for(int index=0; index<size-1; index++)
    {
        for(int j=index+1; j<size; j++)
        {
            if(bins[index]>bins[j])
            {
                temp_bins_status=bins[j];  /* sort the bins of books in ascending order */
                bins[j]=bins[index];
                bins[index]=temp_bins_status;

                temp_bins_status=status[j];/* sort the status of books in ascending order */
                status[j]=status[index];
                status[index]=temp_bins_status;

                temp_prices=prices[j];/* sort the prices of books in ascending order */
                prices[j]=prices[index];
                prices[index]=temp_prices;

                strcpy(str,name[j]);/* sort the name of books in ascending order */
                strcpy(name[j],name[index]);
                strcpy(name[index],str);
            }
        }
    }
}
void printBookList(char name[][NAMESIZE],int bins[],double prices[],int status[])/// to Display data of books for the user
{
    if(size==0)/// if the book store is free of books (numbers of books zero)
    {
        printf(" The book store is Free of books\n");
        return;
    }
    else
    {
        sorting(name,bins, prices,status) ;// to sort books in ascending order by bins
        for(int i=0; i<size; i++) /// to Display data of books for the user which his status equal one(is already exist )
        {
            if(status[i]==1)
                printf(" Name: %s\t bin number = %d\tPrice = %.2f \n",name[i],bins[i],prices[i]);
        }
    }
}
void updataDataFile(char name[][NAMESIZE],int bins[],double prices[],int status[])/// Add the new data in file books.txt
{
    FILE *writeData;
    writeData=fopen("books.txt","w"); /* open file books .txt to add the new data */
    printf("\nUpdating Data File ...\n");
    sorting( name,bins, prices,status) ; // to sort books in ascending order by bins
    for(int j=0; j<size; j++) /// to add all new data of books which his status equal one(is already exist )
    {
        if(status[j]==1)
            fprintf(writeData,"%s\t%d\t\t%.2f\n",name[j],bins[j],prices[j]); /// print new data in file books. txt
    }
    fclose(writeData); /// close file writedata
    printf("Data File update\n");
}
void stop_or_continue(int *temp) /*if the user want complete the process or not */
{
    (*temp)=0;
    int choice;
    printf("\n If you want to complete your process,Enter 1, if Not Enter 0: ");
    scanf("%d",&choice);
    while(choice!=0)
    {
        if(choice==1)
        {
            (*temp)=1;
            break;
        }
        else
            printf(" Please try again! Please enter one if you want to complete your process or zero if not :  ");

        scanf("%d",&choice);
    }
}

