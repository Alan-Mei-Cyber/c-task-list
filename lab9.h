#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#define LEN  200
#define SIZE 10

typedef struct node
{
    char name[LEN];
    int  day;
    int  month;
    struct node *next;
    struct node *prev;
} Node;

extern Node *Head;
extern Node *tail;
extern pthread_mutex_t lock;

extern char task[SIZE][LEN];
extern int  date[SIZE][2];
extern int  counter;

extern int  daysInMonth[12];
int  valid_date(int m, int d);

void insert  (void);
void delete  (void);
void showall (void);
void change  (void);

void deletee (Node *p);
void insertt (Node *p);

void read_file(char *filename);
void save_file(char *filename);
void show_backwards(Node *p);
void delete_all(Node *p);

void *autosave_thread(void *arg);
void showbin(char *filename);

