#include "function.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char getSelectMenu() {
  printf("Menu\n");
  printf("1 - Add book\n");
  printf("2 - Remove book\n");
  printf("3 - Edit book\n");
  printf("4 - Show all book\n");
  printf("5 - Search book\n");
  printf("6 - Borrow book\n");
  printf("7 - Return book\n");
  printf("8 - Exit\n");
  char buffer[50];
  int check;
  printf("> ");
  fgets(buffer, 9, stdin);
  sscanf(buffer, "%d", &check);
  printf("\n");
  return check;
}

//--------------------------------------------------------------------------

int Bookcount() {
  char temp[50];
  int i = 0;
  FILE *fp = fopen("namebook.txt", "r");

  while (!feof(fp)) {
    fgets(temp, 50, fp);
    i++;
  }

  fclose(fp);
  return i;
}

//--------------------------------------------------------------------------

void Read(BOOK *info) {

  TEMP *temp = calloc(1, sizeof(TEMP));
  temp->data = calloc(Bookcount(), sizeof(char *));
  for (int j = 0; j < Bookcount(); j++) {
    temp->data[j] = calloc(50, sizeof(char));
  }

  int rob = 0;

  FILE *fp = fopen("namebook.txt", "r");
  while (!feof(fp)) {
    fgets(temp->data[rob], 50, fp);
    rob++;
  }

  // for(int k=0;k<21;k++){
  // printf("%s",temp->data[k]);
  //   }
  for (int m = 0; m < Bookcount(); m++) {
    if (temp->data[m][strlen(temp->data[m]) - 1] == '\n') {
      temp->data[m][strlen(temp->data[m]) - 1] = '\0';
    }
  }

  int check = 0;
  int subloop1 = 0;
  int subloop2 = 0;
  int subloop3 = 0;
  int loopcheck = 0;
  int count = 0;
  int event = 0;
  int sumevent = 0;

  while (loopcheck < Shelf()) {
    if (check == 0) {
      strcpy(info[subloop1].bookname, temp->data[subloop3]);
      strcpy(info[subloop1].name, temp->data[subloop3 + 1]);
      strcpy(info[subloop1].printdate, temp->data[subloop3 + 2]);
      subloop3 = subloop3 + 3;
      subloop1++;
      check = 1;
    } else {
      if (strcmp(temp->data[subloop3], "---") == 0) {
        strcpy(info->data[subloop2].UE, temp->data[subloop3]);
        subloop3 = subloop3 + 1;
        check = 0;
        subloop2++;
        loopcheck++;
      } else {
        strcpy(info->data[subloop2].UE, temp->data[subloop3]);
        subloop3 = subloop3 + 1;
        subloop2++;
      }
    }
  }
  for (int h = 0; h < Shelf(); h++) {
    while (strcmp(info->data[count].UE, "---") != 0) {
      event++;
      count++;
    }
    info[h].Event = event + sumevent + 1;
    info[h].rob = event + 4;
    // printf("%d",info[h].Event);
    sumevent = info[h].Event;
    if ((event) % 2 == 0)
      strcpy(info[h].status, "Available");

    else
      strcpy(info[h].status, "Borrowed");
    event = 0;
    count++;
  }

  fclose(fp);
}

//--------------------------------------------------------------------------

void Show(BOOK *info) {
  Read(info);
  int check = 0;
  int subloop1 = 0;
  int subloop2 = 0;
  int subloop3 = 0;
  int countB = 0;
  while (countB < Shelf()) {
    if (check == 0) {
      printf("Title: %s\n", info[subloop1].bookname);
      printf("Author Name: %s\n", info[subloop1].name);
      printf("Publish Year: %s\n", info[subloop1].printdate);
      printf("Status: %s\n", info[subloop1].status);
      subloop3 = subloop3 + 3;
      subloop1++;
      check = 1;
    } else {
      if (strcmp(info->data[subloop2].UE, "---") == 0) {
        printf("\n");
        subloop3 = subloop3 + 1;
        check = 0;
        subloop2++;
        countB++;
      } else {
        printf("%s\n", info->data[subloop2].UE);
        subloop3 = subloop3 + 1;
        subloop2++;
      }
    }
  }
}

//--------------------------------------------------------------------------

void Write(char buffer[50]) {
  FILE *fp = fopen("namebook.txt", "ap");
  fprintf(fp, "\n%s", buffer);
  fclose(fp);
}

void ReWrite(BOOK *info, TEMP *in, int loop) {
  Read(info);
  FILE *fp = fopen("namebook.txt", "w");

  for (int i = 0; i < loop; i++) {
    if (i != loop - 1)
      fprintf(fp, "%s\n", in->data[i]);
    else
      fprintf(fp, "%s", in->data[i]);
  }
  fclose(fp);
}

//--------------------------------------------------------------------------

void BookAdd(BOOK *info) {

  char temp[50];

  printf("Enter title: ");
  fgets(temp, 50, stdin);
  while (strlen(temp) == 1) {
    printf("Invalid title\n");
    printf("Enter title: ");
    fgets(temp, 50, stdin);
  }
  if (temp[strlen(temp) - 1] == '\n') {
    temp[strlen(temp) - 1] = '\0';
  }
  Write(temp);

  printf("Enter author name: ");
  fgets(temp, 50, stdin);
  while (strlen(temp) == 1) {
    printf("Invalid author name\n");
    printf("Enter author name: ");
    fgets(temp, 50, stdin);
  }
  if (temp[strlen(temp) - 1] == '\n') {
    temp[strlen(temp) - 1] = '\0';
  }
  Write(temp);

  printf("Enter publish year: ");
  fgets(temp, 50, stdin);

  int ck = 1;
  while (ck == 1) {
    if (temp[strlen(temp) - 1] == '\n') {
      temp[strlen(temp) - 1] = '\0';
    }

    if (strlen(temp) > 0) {
      for (int j = 0; j < strlen(temp); j++) {
        if (isdigit(temp[j]) == 0) {
          ck = 1;
          break;
        } else {
          ck = 0;
        }
      }
    } else
      ck = 1;
    if (ck == 0)
      break;
    printf("Invalid publish year\n");
    printf("Enter publish year:");
    fgets(temp, 50, stdin);
  }
  Write(temp);
  Write("---");
  Read(info);
}

void searchengine(BOOK *info) {
  Read(info);
  char find[99];
  char wfind[99];
  char ret[99];
  char wret[99];
  int bookcount = Shelf();
  int next = 2;
  printf("Title (leave blank to include all titles): ");
  fgets(find, 99, stdin);
  if (find[strlen(find) - 1] == '\n') {
    find[strlen(find) - 1] = '\0';
  }
  for (int i = 0; i < bookcount; i++) {
    ret[i] = strstr(info[i].bookname, find);
    // printf("%s\n",ret[i]);
  }
  printf("Author Name (leave blank to include all author names): ");
  fgets(wfind, 99, stdin);
  if (wfind[strlen(wfind) - 1] == '\n') {
    wfind[strlen(wfind) - 1] = '\0';
  }
  for (int i = 0; i < bookcount; i++) {
    wret[i] = strstr(info[i].name, wfind);
    // printf("%s\n",wret[1]);
  }
  for (int i = 0; i < bookcount; i++) {
    // printf("%d\n", i);
    if (wfind[0] == '\0' && find[0] == '\0') {
      printf("Not found!");
      break;
      ;
    }
    if (ret[i] == NULL || wret[i] == NULL) {
      printf("Not found!");
      break;
    } else if (ret[i] != NULL && wret[i] != NULL) {
      printf("\nTitle: %s\n", info[i].bookname);
      printf("Author Name: %s\n", info[i].name);
      printf("Publish Year: %s\n", info[i].printdate);
      printf("Status: %s\n", info[i].status);
      if (i != 0) {
        for (int m = info[i - 1].Event; m < info[i].Event - 1; m++) {
          printf("%s\n", info->data[m].UE);
          next++;
        }
      } else {
        for (int m = 0; m < info[i].Event - 1; m++) {
          printf("%s\n", info->data[m].UE);
        }
      }

    } else if (ret[i] == ' ' && wret[i] != NULL) {
      printf("\nTitle: %s\n", info[i].bookname);
      printf("Author Name: %s\n", info[i].name);
      printf("Publish Year: %s\n", info[i].printdate);
      printf("Status: %s\n", info[i].status);
      if (i != 0) {
        for (int m = info[i - 1].Event + next; m < info[i].Event; m++) {
          printf("%s\n", info->data[m].UE);
          next++;
        }
      } else {
        for (int m = 0; m < info[i].Event; m++) {
          printf("%s\n", info->data[m].UE);
        }
      }
    } else if (ret[i] != NULL && wret[i] == ' ') {
      printf("\nTitle: %s\n", info[i].bookname);
      printf("Author Name: %s\n", info[i].name);
      printf("Publish Year: %s\n", info[i].printdate);
      printf("Status: %s\n", info[i].status);
      if (i != 0) {
        for (int m = info[i - 1].Event + next; m < info[i].Event; m++) {
          printf("%s\n", info->data[m].UE);
          next++;
        }
      } else {
        for (int m = 0; m < info[i].Event; m++) {
          printf("%s\n", info->data[m].UE);
        }
      }
    }
  }
}

//--------------------------------------------------------------------------

void EditBook(BOOK *info) {
  Read(info);
  // char book[3][50] = {"Harry Potter and the Philosopher's",
  //                     "Harry Potter and the Chamber of Secrets", "Mickiee"};
  // char writer[3][50] = {"J. K. Rowling", "J. K. Rowling", "lol"};
  // char year[3][50] = {"1999", "1998", "1997"};
  char edit[50];
  int count = 0;
  int temp = -1;
  char newword[50];
  char neww[50];
  char newyear[10];
  char wordtemp[50];
  char newwtemp[50];
  char tempyear[10];
  int bookcount = Bookcount(info) / 3;
  int check = 0;
  printf("Enter title to edit : ");
  fgets(edit, 50, stdin);
  if (edit[strlen(edit) - 1] == '\n') {
    edit[strlen(edit) - 1] = '\0';
  }

  for (int i = 0; i < bookcount; i++) {
    count = strcmp(edit, info[i].bookname);
    if (count == 0) {
      // printf("Title : %s\n", info[i].bookname);
      // printf("Writer : %s\n", info[i].name);
      // printf("Writer : %s\n", info[i].printdate);
      temp = i;
      strcpy(wordtemp, info[i].bookname);
      strcpy(newwtemp, info[i].name);
      strcpy(tempyear, info[i].printdate);
    }
  }

  printf("New title (leave blank to retain old value) : ");
  fgets(newword, 50, stdin);
  if (newword[strlen(newword) - 1] == '\n') {
    newword[strlen(newword) - 1] = '\0';
  }
  strcpy(info[temp].bookname, newword);
  if (strlen(info[temp].bookname) == NULL) {
    strcpy(info[temp].bookname, wordtemp);
  } else
    (strcpy(info[temp].bookname, newword));

  printf("New author name (leave blank to retain old value) :");
  fgets(neww, 50, stdin);
  if (neww[strlen(neww) - 1] == '\n') {
    neww[strlen(neww) - 1] = '\0';
  }
  strcpy(info[temp].name, neww);
  if (strlen(info[temp].name) == NULL) {
    strcpy(info[temp].name, newwtemp);
  } else
    (strcpy(info[temp].name, neww));

  printf("New publish year (leave blank to retain old value) : ");
  fgets(newyear, 50, stdin);
  if (newyear[strlen(newyear) - 1] == '\n') {
    newyear[strlen(newyear) - 1] = '\0';
  }
  strcpy(info[temp].printdate, newyear);
  if (strlen(newyear) > 0) {
    for (int j = 0; j < strlen(newyear); j++) {
      if (isdigit(newyear[j]) == 0) {
        check = 1;
        break;
      } else {
        check = 0;
      }
    }
  } else
    check = 1;

  if (strlen(info[temp].printdate) == NULL) {
    check = 1;
  }
  if (check == 1) {
    strcpy(info[temp].printdate, tempyear);
  } else
    (strcpy(info[temp].printdate, newyear));
  ReadV(info);
}

int Shelf() {

  int i = Bookcount();

  TEMP *buffer = calloc(1, sizeof(TEMP));
  buffer->data = calloc(i, sizeof(char *));
  for (int j = 0; j < i; j++) {
    buffer->data[j] = calloc(50, sizeof(char));
  }

  int loop = 0;
  FILE *fp = fopen("namebook.txt", "r");
  while (!feof(fp)) {
    fgets(buffer->data[loop], 50, fp);
    loop++;
  }

  for (int m = 0; m < i; m++) {
    if (buffer->data[m][strlen(buffer->data[m]) - 1] == '\n') {
      buffer->data[m][strlen(buffer->data[m]) - 1] = '\0';
    }
  }

  int book = 0;

  for (int loop = 0; loop < i; loop++) {
    if (strcmp(buffer->data[loop], "---") == 0)
      book++;
  }

  return book;
}

void ReadV(BOOK *info) {

  int count1 = 0;
  int count2 = 0;
  int count3 = 0;
  int check_three = 0;
  TEMP *temp = calloc(1, sizeof(TEMP));
  temp->data = calloc(Bookcount(), sizeof(char *));
  for (int j = 0; j < Bookcount(); j++) {
    temp->data[j] = calloc(50, sizeof(char));
  }

  for (int l = 0; l < Bookcount() - (Shelf() * 2); l++) {
    if (check_three == 0) {
      strcpy(temp->data[count3], info[count1].bookname);
      strcpy(temp->data[count3 + 1], info[count1].name);
      strcpy(temp->data[count3 + 2], info[count1].printdate);
      count3 += 3;
      count1 += 1;
      check_three = 1;
    } else {
      if ((strcmp(info->data[count2].UE, "---") == 0)) {
        strcpy(temp->data[count3], info->data[count2].UE);
        count2++;
        count3++;
        check_three = 0;
      } else {
        strcpy(temp->data[count3], info->data[count2].UE);
        count2++;
        count3++;
      }
    }
  }

  Read(info);
  ReWrite(info, temp, Bookcount());
}

void BookRemove(BOOK *info) {
  Read(info);
  int line = 0;
  int count1 = 0;
  int count2 = 0;
  int count3 = 0;
  int check_three = 0;
  char edit[50];
  int check = 0;

  printf("Enter title to be removed: ");
  fgets(edit, 50, stdin);
  if (edit[strlen(edit) - 1] == '\n') {
    edit[strlen(edit) - 1] = '\0';
  }

  for (int i = 0; i < Shelf(); i++) {
    if (strcmp(edit, info[i].bookname) == 0) {
      line++;
      check = 1;
      break;
    }
    line++;
  }

  if (check == 0) {
    printf("Invalid title\n");
  }

  TEMP *tempu = calloc(1, sizeof(TEMP));
  tempu->data = calloc(Bookcount(), sizeof(char *));
  for (int j = 0; j < Bookcount(); j++) {
    tempu->data[j] = calloc(50, sizeof(char));
  }

  for (int l = 0; l < Bookcount() - (Shelf() * 2); l++) {
    if (check_three == 0) {
      strcpy(tempu->data[count3], info[count1].bookname);
      strcpy(tempu->data[count3 + 1], info[count1].name);
      strcpy(tempu->data[count3 + 2], info[count1].printdate);
      count3 += 3;
      count1 += 1;
      check_three = 1;
    } else {
      if ((strcmp(info->data[count2].UE, "---") == 0)) {
        strcpy(tempu->data[count3], info->data[count2].UE);
        count2++;
        count3++;
        check_three = 0;
      } else {
        strcpy(tempu->data[count3], info->data[count2].UE);
        count2++;
        count3++;
      }
    }
  }
  TEMP *buffer = calloc(1, sizeof(TEMP));
  buffer->data = calloc(Bookcount() - info[line - 1].rob, sizeof(char *));
  for (int j = 0; j < Bookcount() - info[line - 1].rob; j++) {
    buffer->data[j] = calloc(50, sizeof(char));
  }

  int now = 0;
  int start = 0;
  int count = 1;
  int subloop = 0;

  for (int i = 0; i < Shelf(); i++) {
    // printf("%d hello\n",i);
    if (i != (line - 1)) {
      // printf("%d\n",i);
      for (int j = start; j < info[i].Event + (3 * count); j++) {
        strcpy(buffer->data[subloop], tempu->data[j]);
        subloop++;
        start = info[i].Event + (3 * count);
      }
      count++;
    } else {
      start = info[i].Event + (3 * count);
      count++;
    }
  }

  ReWrite(info, buffer, Bookcount() - info[line - 1].rob);
  Read(info);
}

void Return(BOOK *info) {

  int line = 0;
  int count1 = 0;
  int count2 = 0;
  int count3 = 0;
  int check_three = 0;
  char edit[50];

  printf("Enter title to return: ");
  fgets(edit, 50, stdin);
  if (edit[strlen(edit) - 1] == '\n') {
    edit[strlen(edit) - 1] = '\0';
  }

  for (int i = 0; i < Shelf(); i++) {
    if (strcmp(edit, info[i].bookname) == 0) {
      line++;
      break;
    }
    line++;
  }

  TEMP *tempu = calloc(1, sizeof(TEMP));
  tempu->data = calloc(Bookcount(), sizeof(char *));
  for (int j = 0; j < Bookcount(); j++) {
    tempu->data[j] = calloc(50, sizeof(char));
  }

  for (int l = 0; l < Bookcount() - (Shelf() * 2); l++) {
    if (check_three == 0) {
      strcpy(tempu->data[count3], info[count1].bookname);
      strcpy(tempu->data[count3 + 1], info[count1].name);
      strcpy(tempu->data[count3 + 2], info[count1].printdate);
      count3 += 3;
      count1 += 1;
      check_three = 1;
    } else {
      if ((strcmp(info->data[count2].UE, "---") == 0)) {
        strcpy(tempu->data[count3], info->data[count2].UE);
        count2++;
        count3++;
        check_three = 0;
      } else {
        strcpy(tempu->data[count3], info->data[count2].UE);
        count2++;
        count3++;
      }
    }
  }

  TEMP *buffer = calloc(1, sizeof(TEMP));
  buffer->data = calloc(Bookcount() + 1, sizeof(char *));
  for (int j = 0; j < Bookcount() + 1; j++) {
    buffer->data[j] = calloc(50, sizeof(char));
  }
  int rowput = 0;

  for (int r = 0; r < line; r++) {
    rowput = rowput + info[r].rob;
  }

  rowput = rowput - 1;

  char text[50];

  strcpy(text, tempu->data[rowput - 1]);

  // printf("%c\n",text[12]);
  // printf("%d\n",strlen(text));

  int callthis = strlen(text) - 12;
  // printf("%d\n",callthis);

  char *name = calloc(callthis, sizeof(char));
  int subloop = 0;

  for (int s = 12; s < strlen(text); s++) {
    name[subloop] = text[s];
    subloop++;
  }

  char *concatenate = calloc(callthis + 12, sizeof(char));
  strcpy(concatenate, "- Return by ");
  // printf("%s\n",concatenate);
  strcat(concatenate, name);
  // printf("%s\n",concatenate);

  int jump = 0;
  int jumpb = 0;
  for (int h = 0; h < Bookcount() + 1; h++) {
    if (h != rowput)
      strcpy(buffer->data[h], tempu->data[h - jump]);
    else {
      strcpy(buffer->data[h], concatenate);
      jump = 1;
    }
  }

  ReWrite(info, buffer, Bookcount() + 1);
  Read(info);
}


void Borrow(BOOK *info) {
  int line = 0;
  int count1 = 0;
  int count2 = 0;
  int count3 = 0;
  int check_three = 0;
  char edit[50];
  char Uname[50];

  printf("Enter borrower name: ");
  fgets(Uname, 50, stdin);
  if (Uname[strlen(edit) - 1] == '\n') {
    Uname[strlen(edit) - 1] = '\0';
  }

  printf("Enter title to borrow: ");
  fgets(edit, 50, stdin);
  if (edit[strlen(edit) - 1] == '\n') {
    edit[strlen(edit) - 1] = '\0';
  }

  for (int i = 0; i < Shelf(); i++) {
    if (strcmp(edit, info[i].bookname) == 0) {
      line++;
      break;
    }
    line++;
  }

  TEMP *temp = calloc(1, sizeof(TEMP));
  temp->data = calloc(Bookcount(), sizeof(char *));
  for (int j = 0; j < Bookcount(); j++) {
    temp->data[j] = calloc(50, sizeof(char));
  }

  for (int l = 0; l < Bookcount() - (Shelf() * 2); l++) {
    if (check_three == 0) {
      strcpy(temp->data[count3], info[count1].bookname);
      strcpy(temp->data[count3 + 1], info[count1].name);
      strcpy(temp->data[count3 + 2], info[count1].printdate);
      count3 += 3;
      count1 += 1;
      check_three = 1;
    } else {
      if ((strcmp(info->data[count2].UE, "---") == 0)) {
        strcpy(temp->data[count3], info->data[count2].UE);
        count2++;
        count3++;
        check_three = 0;
      } else {
        strcpy(temp->data[count3], info->data[count2].UE);
        count2++;
        count3++;
      }
    }
  }

  TEMP *buffer = calloc(1, sizeof(TEMP));
  buffer->data = calloc(Bookcount() + 1, sizeof(char *));
  for (int j = 0; j < Bookcount() + 1; j++) {
    buffer->data[j] = calloc(50, sizeof(char));
  }
  int rowput = 0;

  for (int r = 0; r < line; r++) {
    rowput = rowput + info[r].rob;
  }

  rowput = rowput - 1;

  char text[50];

  // printf("%c\n",text[12]);
  // printf("%d\n",strlen(text));

  char *concatenate = calloc(strlen(Uname) + 12, sizeof(char));
  strcpy(concatenate, "- Borrow by ");
  // printf("%s\n",concatenate);
  strcat(concatenate, Uname);
  // printf("%s\n",concatenate);
  if (concatenate[strlen(concatenate) - 1] == '\n') {
    concatenate[strlen(concatenate) - 1] = '\0';
  }

  int jump = 0;
  for (int h = 0; h < Bookcount() + 1; h++) {
    if (h != rowput)
      strcpy(buffer->data[h], temp->data[h - jump]);
    else {
      strcpy(buffer->data[h], concatenate);
      jump = 1;
    }
  }

  //   for(int n=0;n<Bookcount()+1;n++)
  // printf("%s\n",buffer->data[n]);
  ReWrite(info, buffer, Bookcount() + 1);
  Read(info);
}
