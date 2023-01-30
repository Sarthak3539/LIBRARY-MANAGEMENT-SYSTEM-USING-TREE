
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>

struct book
{
  int bnum;
  char name[25];
  char author[25];
  struct book *l;
  struct book *r;
};

struct student
{
  char roll_num[25];
  int b[5];
  struct student *l;
  struct student *r;
};

struct book *newnode(char *tname, char *tauthor)
{
  struct book *p = (struct book *)malloc(sizeof(struct book));
  strcpy(p->name, tname);
  strcpy(p->author, tauthor);
  p->l = NULL;
  p->r = NULL;
  return p;
}

void display(struct book *p)
{
  if (p == NULL)
  {
    return;
  }
  display(p->l);
  printf(" %d. %10s  %15s\n", p->bnum, p->name, p->author);
  display(p->r); 
}

void display_avalible_books(struct book *p, bool *b)
{
  if (p == NULL)
  {
    return;
  }
  display_avalible_books(p->l, b);
  if (((b[p->bnum] != 1)))
  {
    printf("\n  %d. %s   %s\n", p->bnum, p->name, p->author);
  }
  display_avalible_books(p->r, b);
}

void search(struct book *b, char *c)
{
  while (b != NULL)
  {
    if (strcmp(b->name, c) > 0)
      b = b->l;
    else if (strcmp(b->name, c) < 0)
      b = b->r;
    else
    {
      printf("\n %10s%15s\n", "name", "author");
      printf(" %10s%15s\n\n", b->name, b->author);
      return;
    }
  }
  printf("\nNo record found...!!!\n\n");
}

void insert(struct book **p, int *booknum)
{
  struct book *ptr = (*p), *a1, *a2;
  char tname[25], tauthor[25];
  printf("\nEnter the book name: ");
  fflush(stdin);
  gets(tname);
  printf("Enter the author of the book: ");
  fflush(stdin);
  gets(tauthor);
  a1 = newnode(tname, tauthor);
  a1->bnum = *booknum;
  (*booknum)++;
  if ((*p) == NULL)
  {
    (*p) = a1;
    return;
  }
  else
  {
    while (ptr != NULL)
    {
      a2 = ptr;
      if (strcmp(a1->name, ptr->name) > 0)
      {
        ptr = ptr->r;
      }
      else if (strcmp(a1->name, ptr->name) < 0)
      {
        ptr = ptr->l;
      }
    }
  }

  if (strcmp(a1->name, a2->name) > 0)
  {
    a2->r = a1;
  }
  else
  {
    a2->l = a1;
  }
}

struct book *inordersucessor(struct book *node)
{
  struct book *current = node;
  while (current && current->l != NULL)
  {
    current = current->l;
  }
  return current;
}

struct book *delete_book(struct book *root, char *c)
{

  if (root == NULL)
  {
    return root;
  }
  if (strcmp(root->name, c) > 0)
  {
    root->l = delete_book(root->l, c);
  }
  else if (strcmp(c, root->name) > 0)
  {
    root->r = delete_book(root->r, c);
  }
  else
  {
    if (root->l == NULL)
    {
      struct book *tmp = root->r;
      return tmp;
    }
    else if (root->r == NULL)
    {
      struct book *tmp = root->l;
      return tmp;
    }
    struct book *tmp = inordersucessor(root->r);
    strcpy(root->name, tmp->name);
    root->r = delete_book(root->r, tmp->name);
  }
  return root;
}

struct student *newstudnet(char *p)
{
  struct student *tmp = (struct student *)malloc(sizeof(struct student));
  strcpy(tmp->roll_num, p);
  for (int i = 0; i < 5; i++)
  {
    tmp->b[i] = 0;
  }

  tmp->l = NULL;
  tmp->r = NULL;
  return tmp;
}

void registration(struct student **p)
{
  char roll[25];
  struct student *a = (*p), *a1, *tmp;
  printf("\nEnter the roll number of the student :  ");
  gets(roll);
  fflush(stdin);
  tmp = newstudnet(roll);
  if ((*p) == NULL)
  {
    (*p) = tmp;
    return;
  }
  else
  {
    while (a != NULL)
    {
      a1 = a;
      if (strcmp(tmp->roll_num, a->roll_num) > 0)
      {
        a = a->r;
      }
      else if (strcmp(tmp->roll_num, a->roll_num) < 0)
      {
        a = a->l;
      }
    }
  }
  if (strcmp(tmp->roll_num, a1->roll_num) > 0)
  {
    a1->r = tmp;
  }
  else
  {
    a1->l = tmp;
  }
}

void issus_book(struct book *root, struct student *p, bool *avalible)
{
  struct student *ptr = p;
  struct book *bptr = root;
  char rnum[25];
  int idx = 0;
  fflush(stdin);
  printf("\n\nEnter your roll number : ");
  gets(rnum);
  fflush(stdin);
  printf("\nlist of avalible books\n");
  display_avalible_books(root, avalible);
  printf("\nEnter the index of the book\n");
  scanf("%d", &idx);
  while (strcmp(rnum, ptr->roll_num) != 0)
  {
    if (strcmp(rnum, ptr->roll_num) > 0)
    {
      ptr = ptr->r;
    }
    else
    {
      ptr = ptr->l;
    }
  }
  for (int i = 0; i < 5; i++)
  {
    if (ptr->b[i] == 0)
    {
      ptr->b[i] = idx;
      *(avalible + (idx)) = true;
      break;
    }
    if (i == 4)
    {
      printf("You can't issue new book");
    }
  }
}

void return_book(struct book *root, struct student *p, bool *avalible)
{
  int idx;
  char rnum[25];
  struct student *ptr = p;
  printf("\nEnter your roll number: ");
  fflush(stdin);
  gets(rnum);
  fflush(stdin);
  printf("\nEnter the index number of the book: ");
  scanf("%d", &idx);
  while (strcmp(rnum, ptr->roll_num) != 0)
  {
    if (strcmp(rnum, ptr->roll_num) > 0)
    {
      ptr = ptr->r;
    }
    else
    {
      ptr = ptr->l;
    }
  }
  for (int i = 0; i < 5; i++)
  {
    if (ptr->b[i] == idx)
    {
     
      *(avalible + idx) = false;

      ptr->b[i] = 0;
      break;
    }
    if (i == 4)
    {
      printf("\nbook not found in your record\n");
    }
  }
}
void student_record(struct student *p)
{
  if (p == NULL)
    return;
  student_record(p->l);
  fflush(stdin);
  printf("\nroll number:   ");
  puts(p->roll_num);
  printf("\nlist of issues books index\n");
  for (int i = 0; i < 5; i++)
  {
    if (p->b[i] != 0)
    {
      printf("%d  ", p->b[i]);
    }
  }
  printf("\n");
  student_record(p->r);
}

int main()
{
  int booknum = 1;
  struct book *root = NULL;
  struct student *first = NULL;
  char a[30];
  bool avalible[50];
  for (int i = 0; i < 50; i++)
    avalible[i] = false;
  int k;

  do
  {

    printf("\n                                 **************************************************************************\n");
    printf("                                                     WELCOME TO LIBRARY MANAGEMENT SYSTEM\n");
    printf("                                 **************************************************************************\n\n\n");
    printf("\t\t-----------------------");
    printf("\n\t\t 1. Admin Section      \n\t\t                   \n\t\t 2.Student Section     \n\n\t\t 3.Exit                \n");
    printf("\t\t-----------------------\n");
    printf("\n  Press: ");
    scanf("%d", &k);
    switch (k)
    {

    case 1:
      char pass[30] = "JitaliMam OP";
      char epass[30];
      printf("\n\n Enter the password:   ");
      fflush(stdin);
      gets(epass);
      fflush(stdin);
      if (strcmp(pass, epass) == 0)
      {

        int e;
        do
        {
          printf("\n\t\t\t\t\t   ----------------------------------------------\n");
          printf("\t\t\t\t\t\t\t    ADMIN SECTION\n");
          printf("\t\t\t\t\t   ----------------------------------------------\n\n");
          printf("\t\t-----------------------\n");
          printf("\t\t1.Insert New Book\n\n\t\t2.delete Book\n\n\t\t3.Display\n\n\t\t4.Back to Menu\n");
          printf("\t\t-----------------------\n");
          printf("\n  Press: ");
          fflush(stdin);
          scanf("%d", &e);
          fflush(stdin);
          switch (e)
          {
          case 1:
            printf("\nHow many books you want to enter:  ");
            int n;
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
              insert(&root, &booknum);
            break;
          case 2:
            char str[25];
            printf("\nEnter the book name\n");
            fflush(stdin);
            gets(str);
            fflush(stdin);
            root =

                delete_book(root, str);
            break;
          case 3:
            printf("\nidx   Book_Name        Author_Name  \n");
            display(root);
            break;
          case 4:
            break;
          default:
            printf("Enter appropriate choice");
            break;
          }

        } while (e != 4);
        break;
      }
      else
      {
        printf("\n\t\tWrong Password :( \n");
        break;
      }
    case 2:
      int r;
      do
      {
        printf("\t\t-----------------------------\n");
        printf("\t\t1.Search any book\n\n\t\t2.New Student Regestration\n\n\t\t3.Student Record\n\n\t\t4.Issue Book\n\n\t\t5.Display\n\n\t\t6.return book\n\n\t\t7. Back to Menu \n");
        printf("\t\t-----------------------------\n");
        printf("Press: ");

        fflush(stdin);
        scanf("%d", &r);
        fflush(stdin);
        switch (r)
        {
        case 1:
          printf("\nEnter a name to search: ");
          fflush(stdin);
          gets(a);
          search(root, a);
          break;

        case 2:
          printf("\nEnter the number of student want to regestration   : ");
          int tmp;
          scanf("%d", &tmp);
          fflush(stdin);
          for (int i = 0; i < tmp; i++)
          {
            registration(&first);
          }
          printf("\n\nRegestartion sucessful  !\n\n");
          break;

        case 3:
          student_record(first);
          break;

        case 4:
          issus_book(root, first, avalible);
          break;
        case 5:
          printf("\nidx   Book_Name        Author_Name  \n");
          display(root);
          break;

        case 6:
          return_book(root, first, avalible);
          break;
        case 7:
          break;
        default:
          printf("Enter appropriate choices");
          break;
        }
      } while (r != 7);
    }
  } while (k != 3);

  printf("\n\nThank you for visiting the library !!!!\n\n\n");
 
  return 0;

}
