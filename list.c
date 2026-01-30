#include "lab9.h"


Node *Head = NULL;
Node *tail = NULL;

int daysInMonth[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
int valid_date(int m, int d)
{
	if(m <= 0 || m > 12 )
	{
		return 0;
	}
	if(d <= 0 || d > daysInMonth[m-1])
	{
		return 0;
	}
	return 1;
}

char	task[SIZE][LEN];
int	date[SIZE][2];
int	counter = 0;


void insert(void)
{
    Node *NN = (Node *)malloc(sizeof(Node));
    char ch1, ch2;
    if (scanf("%c%[^\n]%c", &ch1, NN -> name, &ch2) != 3)
    {
        printf("task scanf error\n");
        return;
    }

    if (scanf("%d%d", &NN -> month, &NN -> day) != 2)
    {
        printf("date scanf error\n");
        return;
    }
    if(!valid_date(NN -> month, NN -> day))
    {
	    printf("invalid date\n");
	    return;
    }
    pthread_mutex_lock(&lock);
    Node *p = Head;
    while(p != NULL)
    {
       if(strcmp(p -> name, NN -> name) ==0)
       {
	  printf("duplicate task\n");
	  return;
       }
       p = p->next;
    }

    NN -> next = NULL;
    NN -> prev = NULL;

    if(Head == NULL)
    {
	Head = NN;
	pthread_mutex_unlock(&lock);
	return;
    }
    Node *CUR = Head;
    while(CUR !=NULL && (CUR->month < NN->month || (CUR->month == NN->month && CUR -> day <= NN ->day)))
    {
	    CUR = CUR->next;
    }

    if(CUR == Head)
    {
	NN->next = Head;
	Head -> prev = NN;
	Head = NN;
    }
    else if(CUR==NULL)
    {
        Node *tail= Head;
	while(tail->next != NULL)
	{
           tail= tail->next;
	}
	tail->next = NN;
	NN->prev = tail;
    }
    else
    {
	NN->next = CUR;
	NN->prev = CUR->prev;
	CUR ->prev->next = NN;
	CUR->prev = NN;
    }
    pthread_mutex_unlock(&lock);
}

void delete (void)
{
    char ch1, ch2;
    char str[200];

    if (scanf ("%c%[^\n]%c", &ch1, str, &ch2) != 3)
    {
    	printf ("task scanf error\n");
	return;
    }
    pthread_mutex_lock(&lock);
   Node *p = Head;
   while(p != NULL && strcmp(p->name,str)!=0)
    {
      p = p->next;
    }
   if(p == NULL)
   {
     printf("not found\n");
     return;
   }
   
   if(p->prev != NULL)
   {
      p->prev->next = p->next;
   }
   else
   {
      Head = p->next;
   }
   if(p->next == NULL)
   {
     p->prev->next = NULL;
   }
   else
   {
	   tail = p->prev;
   }
   free(p);
  pthread_mutex_unlock(&lock);
}


/*void showall(void)
{ 
    pthread_mutex_lock(&lock);
    Node *p = Head;
    while(p != NULL)
    {
        printf("%d/%d/%s\n", p->month,p->day,p->name);
	p = p->next;
    }
    pthread_mutex_unlock(&lock);
}*/


void change (void)
{
   pthread_mutex_lock(&lock);	
   char ch1, ch2;
   char key[LEN];
   int newMonth, newDay;

   if (scanf("%c%[^\n]%c", &ch1, key, &ch2) != 3)
   {
       printf("task scanf error\n");
       return; 
   }
    if (scanf("%d%d", &newMonth, &newDay) != 2)
    {
        printf("date scanf error\n");
        return;
    }

    if (!valid_date(newMonth, newDay))
    {
        printf("invalid\n");
        return;
    }

    Node *p = Head;

    while (p != NULL)
    {	
	if (strcmp(key, p->name) != 0) {
        	p = p->next;
	}
	else {
		break;
	}
    }
    
    if (p == NULL) 
    {
       printf("not found\n");
       return;
    }

    deletee(p);
    p->month = newMonth;
    p->day = newDay;
    p->prev = NULL;
    p->next =NULL;
    strcpy(p->name,key);
    insertt(p);

    pthread_mutex_unlock(&lock);
}

void deletee(Node *p)
{
    if(p->prev != NULL)
   {
      p->prev->next = p->next;
   }
   else
   {
      Head = p->next;
   }
   if(p->next == NULL)
   {
     p->prev->next = p->prev;
   }
   free(p);
}

void insertt(Node *p)
{
    Node *CUR;
    if (Head == NULL) 
    {
        p->next = NULL;
        p->prev = NULL;
        Head = p;
        tail = p;
        return;
    }

    CUR = Head;

    while(CUR !=NULL && (CUR->month < p->month || (CUR->month == p->month && CUR -> day <= p ->day)))
    {
            CUR = CUR->next;
    }

    if(CUR == Head)
    {
        p->next = Head;
	p->prev = NULL;
        Head -> prev = p;
        Head = p;
    }
    else if(CUR==NULL)
    {
        Node *tail= Head;
        while(tail->next != NULL)
        {
           tail= tail->next;
        }
        tail->next = p;
        p->prev = tail;
	p->next = NULL;
    }
    else
    {
        p->next = CUR;
        p->prev = CUR->prev;
        CUR ->prev->next = p;
        CUR->prev = p;
    }
}

void show_backwards(Node *p)
{
    if (p == NULL)
    {return;}

    show_backwards(p->next);
    printf("%d/%d/%s\n", p->month, p->day, p->name);
}

void delete_all(Node *p)
{  
    if (p == NULL)
        return;

    delete_all(p->next);
    free(p);
}
