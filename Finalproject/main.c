#include "function.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    
  printf("Welcome to CPE Library Management System");

 BOOK *Book = calloc(Shelf(), sizeof(BOOK));
  Book->data = calloc(Bookcount() - (3 *  Shelf()), sizeof(BOOK));

  // Show(info);
  // BookAdd(Book);
  
  Read(Book);
  // printf("%d",Book[1].rob);
 //  printf("%d",Shelf());
   
// ReadV(Book);
  //  searchengine(Book);

  // free(Book);
  // free( Book->data);

  //printf("%s",info[0].bookname);
  // info->data = calloc(5,sizeof(USER));
  // printf("%d",Bookcount(info));
  // Show(info);
  // Show(info);
  // BookAdd(info);
  //Show(info);


  int menu;
    while (menu != 8) {
        if (menu == 1) {
            BookAdd(Book);
         } else if (menu == 2) {
             BookRemove(Book);
        } else if (menu == 3) {
            EditBook(Book);
        } else if (menu == 4) {
            Show(Book);
        } else if (menu == 5) {
            searchengine(Book);
        } else if (menu == 6) {
            Borrow(Book);
         } else if (menu == 7) {
             Return(Book);
          }
          printf("\n");
        
        menu = getSelectMenu();
    }
  printf("Thank you");
  return 0;
}
