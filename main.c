#include "lab9.h"

/*
 ***********************
 *  main
 ***********************
 */
int main (int argc,char *argv[])
{
       int option;
       pthread_t tid;
       if (argc == 1) 
       {
        printf("missing name of the file\n");
        return 1;
       }
       if (argc < 3) 
       {
        printf("missing arguments\n");
        return 1;   
       }
      read_file(argv[1]);
      pthread_mutex_init(&lock,NULL);
      pthread_create(&tid, NULL, autosave_thread, argv[2]);

	while (1)
	{
		if (scanf ("%d", &option) != 1)
		{
			printf ("option error\n");
			return 0;
		}

		switch (option)
		{
			case 1:
				insert ();
				break;

			case 2:
				delete ();
				break;

			case 3:
				show_backwards(Head);
				break;


			case 0:
				pthread_mutex_lock(&lock);
				save_file(argv[1]);
				delete_all(Head);
				Head = NULL;
				tail = NULL;
				pthread_mutex_unlock(&lock);

				pthread_cancel(tid);
				pthread_join(tid,NULL);
				pthread_mutex_destroy(&lock);
				printf ("exit\n");
				return 0;

			case 4:
				change();
				break;
			case 5:
				showbin(argv[2]);
				break;

			default:
				printf ("wrong option\n");
		}

	}

}
