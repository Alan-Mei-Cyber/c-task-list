#include "lab9.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *autosave_thread(void *arg)
{
    char *biname = (char *)arg;

    while(1)
    {
       sleep(15);

       pthread_mutex_lock(&lock);
       FILE *fp = fopen(biname,"wb");
       if (fp != NULL) 
       {
            Node *p = Head;
            while (p != NULL) 
	    {
                fwrite(p, sizeof(Node), 1, fp);
                p = p->next;
            }
            fclose(fp);
        }

        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void showbin(char *filename)
{
    FILE *fp = fopen(filename,"rb");
    if(fp == NULL)
    {
       printf("cannot open it\n");
       return;
    }
    Node temp;

    pthread_mutex_lock(&lock);
    while(fread(&temp,sizeof(Node),1,fp)==1)
    {
        printf("%d/%d/%s\n", temp.month, temp.day, temp.name);
    }

    pthread_mutex_unlock(&lock);

    fclose(fp);
}

void read_file(char *filename)
{
    FILE *fp;
    char name[LEN];
    int m, d;
    Node *p;
    
    Head=NULL;
    tail=NULL;
    counter = 0;

    fp = fopen(filename, "r");
    if (fp == NULL) 
    {
        printf("empty list.\n");
        return;
    }
    while (fscanf(fp, "%s %d %d", name, &m, &d) == 3) 
    {
        if (!valid_date(m, d)) 
	{
            printf("Invalid date\n");
        }

        p = (Node *)malloc(sizeof(Node));
        strcpy(p->name, name);
        p->month = m;
        p->day   = d;
        p->next  = NULL;
        p->prev  = NULL;
        insertt(p);
    }

    fclose(fp);
}

void save_file(char *filename)
{
    FILE *fp;
    Node *p = Head;

    fp = fopen(filename, "w");
    if (fp == NULL) 
    {
        printf("Cannot open this file\n");
        return;
    }

    while (p != NULL) 
    {
        fprintf(fp, "%s %d %d\n", p->name, p->month, p->day);
        p = p->next;
    }

    fclose(fp);
}

