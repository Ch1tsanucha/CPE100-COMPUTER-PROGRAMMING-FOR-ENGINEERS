# Group Member : 
#### 1. Jiraporn Wangkumharn 65070501008
#### 2. Chitsanucha Onrit 65070501016
#### 3. Jaatupoj Tuangsintaweekul 650070501070
---
โปรแกรมนี้เป็นโปรแกรมจำลองระบบจัดเก็บของห้องสมุด โดยต้องมีฟังก์ชั่นดังนี้
1. สามารถเพิ่ม-ลบหนังสือในห้องสมุดได้
2. สามารถแก้ไขรายละเอียดของหนังสือ (ชื่อหนังสือ, ชื่อผู้แต่ง, ปีที่พิมพ์) ได้
3. สามารถค้นหาหนังสือจากชื่อหนังสือและ/หรือชื่อผู้แต่งได้
4. มีระบบการยืม-คืนหนังสือ โดยไม่จํากัดจํานวนครั้งในการยืม-คืนของหนังสือแต่ละเล่ม
5. จัดเก็บข้อมูลลงไฟล์โดยอัตโนมัติโดยเมื่อเปิด-ปิดโปรแกรมใหม่รายละเอียดหนังสือและรายการยืมคืนทั้งหมด
จะต้องยังคงอยู่
---
# maic.c
ทำการจองพื้นที่สำหรับหนังสือที่มีอยู่ในคลัง (ที่เก็บไว้ในฐานข้อมูลครั้งก่อน) ก่อนจะถามผู้ใช้ว่าต้องการทำอะไร 
``` c
BOOK *Book = calloc(Shelf(), sizeof(BOOK));
Book->data = calloc(Bookcount() - (3 *  Shelf()), sizeof(BOOK));
```

---
# function.h
- กำหนด struct ชือ **USER** ให้เก็บค่า User Event หรือการเก็บประวัติการยืมคืนของผู้ใช้
- กำหนด struct ชื่อ **BOOK** ให้เก็บค่า ชื่อหนังสือ ชื่อผู้แต่ง สถานะหนังสือ ปีที่พิมพ์ จำนวนบรรทัดของการยืมคืน และจำนวนบรรทัดของทั้งหมด
- กำหนด struct ชื่อ **TEMP** ไว้สร้าง array 2 มิติสำหรับจองพื้นที่แบบ Dynamic
  และทำการประกาศชื่อฟังก์ชั่นต่างๆเพื่อจะนำไปใช้ต่อใน **main.c**
```c
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
```

---
# function.c
#### First function: getSelectMenu
 เป็นฟังก์ชั่นที่ทำการถามผู้ใช้งานว่าต้องการทำการทำสิ่งใด โดย 
- หมายเลข 1 เป็นการเพิ่มหนังสือเข้าไปในคลังหนังสือ
- หมายเลข 2 เป็นการลบหนังสือออกจากคลังหนังสือ
- หมายเลข 3 เป็นแการแก้ไขหนังสือที่มีอยู่ในคลัง
- หมายเลย 4 เป็นการโชว์หนังสือทั้งหมมดที่อยู่ในคลัง
- หมายเลข 6 เป็นระบบการยืมหนังสือ
- หมายเลข 7 เป็นระบบการคืนหนังสือทที่ได้ยืมไป
- หมายเลข 8 เป็นการออกจากโปรแกรมห้องสมุด

  ```c
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
  fgets(buffer,9,stdin);
    sscanf(buffer, "%d", &check);
   printf("\n");
  return check;
  } 

---
#### Second function: Bookcount
เป็นฟังก์ชั่นที่ทำการเข้าไปอ่านจำนวนบรรทัดที่อยู่ในคลัง
```c
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
```
---
#### Third function: Read
ฟังก์ชั่นนี้จะทำการอ่านข้อมูลในคลังทั้งหมด และตัดข้อมูลแบ่งเป็นเล่มๆ เป็นสองส่วนคือ 
- ชื่อหนังสือ ชื่อผู้แต่ง ปีที่พิมพ์
- สถานะของหนังสือ กับประวัติการยืมคืน
```c
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
```
---
#### Fourth function: Show
เป็นฟังก์ชั่นที่ทำการอ่านข้อมูลในคลังทั้งหมด และแสดงออกมา ได้แก่ชื่อหนังสือ ชื่อผู้แต่ง ปีที่พิมพ์
และประวัติการยืมคืนของหนังสือเล่มนั้น
```c
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
```
---
  
#### Fifth function: Write & ReWrite
- Write - เป็นฟังก์ชั่นที่ทำการเขียนข้อมูลลงไปในคลัง
  ```c
  void Write(char buffer[50]) {
  FILE *fp = fopen("namebook.txt","ap");
  fprintf(fp,"\n%s", buffer);
  fclose(fp);
  }


- ReWrite - เป็นฟังก์ชั่นที่ทำการลบบข้อมูลทั้งหมดออกก่อนที่จะทำการเขียนข้อมูลลงไปใหม่

  ```c
  void ReWrite(BOOK *info,TEMP *in,int loop){
  Read(info);
  FILE *fp = fopen("namebook.txt", "w");
  
   for (int i = 0; i < loop; i++){
   if(i!=loop-1)
        fprintf(fp, "%s\n",in->data[i]);
   else
     fprintf(fp, "%s",in->data[i]);
   }
   fclose(fp); 
  }


---
#### Sixth function: BookAdd
เป็นฟังก์ชั่นที่ทำการรับข้อมูลจากผู้ใช้เพื่อมาเก็บในคลังห้องสมุด ได้แก่ชื่อหนังสือ ชื่อผู้แต่ง ปีที่พิมพ์(เป็นตัวเลขเท่านั้น) โดยหากไม่ได้ทำการใส่ข้อมูลลงไปจะขึ้น "Invalid" และทำการขอค่าใหม่ หลังจากที่ได้ข้อมูลครบแล้วโปรแกรมจะทำการนำเข้าสู่ฟังก์ชั่น  **Write** เพื่อเพิ่มข้อมูลไปในคลัง
```c
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
```

---
#### Seventh function: searchengine
เป็นฟังก์ชั่นที่ทำการรับ **ชือหนังสือและชื่อผู้แต่ง** จากผู้ใช้เพื่อค้นหาหนังสือในคลังว่ามี เล่มไหนบ้างที่มีคำตรงกับที่ผู้ใช้ใส่เข้ามา และแสดงผลหนังสือทั้งหมดที่มีคำตรงกับผู้ใช้ใส่ และสถานะของหนังสือเล่มนั้น ประวัติการยืมคินของหนังสือเล่มนั้น
```c
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
  }
  printf("Author Name (leave blank to include all author names): ");
  fgets(wfind, 99, stdin);
  if (wfind[strlen(wfind) - 1] == '\n') {
    wfind[strlen(wfind) - 1] = '\0';
  }
  for (int i = 0; i < bookcount; i++) {
    wret[i] = strstr(info[i].name, wfind);
  }
  for (int i = 0; i < bookcount; i++) {
    if (wfind[0] == '\0' && find[0] == '\0') {
      printf("Not found!");
      break;;
    } if (ret[i] == NULL || wret[i] == NULL) {
      printf("Not found!");
      break;      
    } 
    else if (ret[i] != NULL && wret[i] != NULL) {
      printf("\nTitle: %s\n", info[i].bookname);
      printf("Author Name: %s\n", info[i].name);
      printf("Publish Year: %s\n", info[i].printdate);
       printf("Status: %s\n",info[i].status);
      if(i!=0){
    for(int m=info[i-1].Event;m<info[i].Event-1;m++)
      {
        printf("%s\n",info->data[m].UE);
        next++;
      }
        }
      else{
        for(int m=0;m<info[i].Event-1;m++)
      {
        printf("%s\n",info->data[m].UE);
      }
      }
    } else if (ret[i] == ' ' && wret[i] != NULL) {
      printf("\nTitle: %s\n", info[i].bookname);
      printf("Author Name: %s\n", info[i].name);
      printf("Publish Year: %s\n", info[i].printdate);
      printf("Status: %s\n",info[i].status);
        if(i!=0){
    for(int m=info[i-1].Event+next;m<info[i].Event;m++)
      {
        printf("%s\n",info->data[m].UE);
        next++;
      }
        }
      else{
        for(int m=0;m<info[i].Event;m++)
      {
        printf("%s\n",info->data[m].UE);
      }
      }
    } else if (ret[i] != NULL && wret[i] == ' ') {
      printf("\nTitle: %s\n", info[i].bookname);
      printf("Author Name: %s\n", info[i].name);
      printf("Publish Year: %s\n", info[i].printdate);
      printf("Status: %s\n",info[i].status);
        if(i!=0){
    for(int m=info[i-1].Event+next;m<info[i].Event;m++)
      {
        printf("%s\n",info->data[m].UE);
        next++;
      }
        }
      else{
        for(int m=0;m<info[i].Event;m++)
      {
        printf("%s\n",info->data[m].UE);
      }
      }
    }
  }
}
```
---
#### Eigth: EditBook
เป็นฟังก์ชั่นที่ทำการรับชื่อหนังสือจากผู้ใช้ และนำมาแก้ไขชื่อหนังสือ ชื่อผู้ใช้ ปีที่พิมพ์โดยหากไม่ได้ใส่ข้อมูลแก้ในช่องไหนก็จะเท่ากับไม่แก้ไขข้อมูลในช่องนั้น
```c
void EditBook(BOOK *info) {
  Read(info);
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
    if (check == 1){
    strcpy(info[temp].printdate, tempyear);
  } else
    (strcpy(info[temp].printdate, newyear));
ReadV(info);
}
```

---
#### Ninth function: Shelf
เป็นฟังก์ชั่นที่ทำการนำค่าบรรทัดทั้งหมดจาก **BookCount** มาทำการจองพื้นที่ในการเก็บหนังสือแต่ละเล่มโดยที่นับด้วยว่าในคลังหนังสือมีหนังสือทั้งหมดกี่เล่ม
```c
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
```

---
#### Tenth function: ReadV
เป็นฟังก์ชั่นที่ทำการอ่านค่าจากตัวแปรที่สร้างไว้เก็บข้อมูลชั่วคราว ก่อนนำไปเขียนใหม่ด้วย **ReWrite**
```c
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
```
---
#### Eleventh function: BookRemove
เป็นฟังก์ชั่นที่ให้ผู้ใช้กรอกชื่อหนังสือ และโปรแกรมจะทำการลบหนังสือที่ตรงกับที่ผู้ใช้กรอก หากกรอกชื่อผิดก็จะไม่ทำการลบหนังสือออก
```c
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
  for (int i = 0; i < Shelf(); i++) 
    if (i != (line - 1)) {
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
```

---
#### Twelfth function: Borrow
เป็นฟังก์ชั่นที่ให้ผู้ใช้กรอกชื่อหนังสือให้ตรงกับหนังสือ และหากหนังสือมีสถานะ **Avaliable** ก็จะให้ผู้ใช้ทำการกรอกชื่อผู้ใช้ เพื่อเก็บไว้ในข้อมูลว่าใครเป็นคนยืมหนังสือ และทำการเพิ่มข้อมูลการยืมก่อนจะทำการ **ReWrite** ข้อมูลใหม่ลงไปในคลัง
```c
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
  int callthis = strlen(text) - 12;
  char *name = calloc(callthis, sizeof(char));
  int subloop = 0;
  for (int s = 12; s < strlen(text); s++) {
    name[subloop] = text[s];
    subloop++;
  }
  char *concatenate = calloc(callthis + 12, sizeof(char));
  strcpy(concatenate, "- Return by ");
  strcat(concatenate, name);
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
```

---
#### Thirteenth function: Return
เป็นฟังก์ชั่นที่ให้ผู้ใช้กรอกชื่อหนังสือเรื่องที่ต้องการจะคืน โดนโปรแกรมก็จะทำการเพิ่มข้อมูลการคืนของผู้ใช้ด้วยชื่อคนยืม และทำการ **ReWrite** ข้อมูลใหม่ลงไปในคลัง
```c
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
  char *concatenate = calloc(strlen(Uname) + 12, sizeof(char));
  strcpy(concatenate, "- Borrow by ");
  strcat(concatenate, Uname);
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
  ReWrite(info, buffer, Bookcount() + 1);
  Read(info);
}
```