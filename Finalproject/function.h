#ifndef BOOK_H
#define BOOK_H

typedef struct {
  char UE[50];
} USER;

typedef struct {
  char bookname[50];
  char name[50];
  char status[15];
  char printdate[10];
  int Event;
  int rob;
  USER *data;
} BOOK;

typedef struct {
  char **data;
} TEMP;

int Shelf();

int Bookcount();

void BookAdd(BOOK *info);

void Read(BOOK *info);

void Show(BOOK *info);

void Write(char buffer[50]);

void searchengine(BOOK *info);

void EditBook(BOOK *info);

void ReWrite(BOOK *info, TEMP *in, int loop);

void ReadV(BOOK *info);

void BookRemove(BOOK *info);

void Borrow(BOOK *info);

 void Return(BOOK *info);
// int getSelectMenu();

#endif