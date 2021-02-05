#include <stdio.h> /** for input output functions like Printf and scanf*/
#include <stdlib.h>
#include <string.h>/** for the operations of the string  functions */
#include<time.h>




#include "header.h" /** included with the header file */

/** List of Macros to be used :::: */

#define MAX_NUMBER 50
#define MIN_NUMBER 20


/** list of the global variable and file paths */

    char path[]="title.bin";

/** The functions :::: */
    void id_topic(tasks *topic)
 {

     int id;

     char see_id[MAX_NUMBER];

     char ipath[]= "store_id.txt";

     FILE *fp, *fpp;

     fp = fopen(ipath,"r");

     fgets(see_id,MAX_NUMBER,fp);

     fclose(fp);

     id = atoi(see_id);

     fpp = fopen(ipath, "w");

     fprintf(fpp,"%d",id+1);

     fclose(fpp);

     topic->id=id+1;


 }

    int priority_topic(char *argv[], tasks *topic)
    {

        short given_priority = atoi(argv[4]);

         if(given_priority>=0 && given_priority<=10)
         {
             topic->priority = given_priority;

         }

         else
        {

        printf("!!please have a right priority (0-10) !!\n");

        return 0;

        }

    }

    int status_topic(char *argv[],tasks *topic)
    {
        char status[MAX_NUMBER];

        strcpy(status,argv[5]);

        if(strcmp(status,"ongoing")==0 || strcmp(status,"done")==0)
        {

            strcpy(topic->status,argv[5]);


        }

        else
        {
           printf("!!Please have a right argument!!");

            return 0;

        }


    }

    void title_topic(char *argv[],tasks *topic)
    {

    strcpy(topic->title, argv[3]);


    }

    void due_date_topic(char *argv[], tasks *topic)
    {

        strcpy(topic->due_date,argv[6]);

    }

    void reg_date_topic(tasks *topic)
    {

        topic->regidate = (int)time(NULL);

    }

    void rewind_topic(int argc, char *argv[])
    {

    tasks rewind;

    FILE *fprw;



    if (strcmp(argv[1], "task") == 0 && strcmp(argv[2], "rewind") == 0)
    {

        for (int i = 3; i < argc; i++)
        {

            fprw = fopen(path, "r+b");

            while (fread(&rewind, sizeof(tasks), 1, fprw) == 1)
            {

                if (rewind.id == atoi(argv[i]))
                {
                    strcpy(rewind.status, "ongoing");

                    fseek(fprw, -sizeof(tasks),
                          SEEK_CUR);/** it juts moves the co-ordinates from the current position to the steps back of size of tasks */

                    fwrite(&rewind, sizeof(tasks), 1, fprw);
                }

            }

            fclose(fprw);

        }
    }

}

    void conclude_topic(int argc, char *argv[])
{

    tasks complete;

    FILE *fptc;



    if (strcmp(argv[1], "task") == 0 && strcmp(argv[2], "complete") == 0)
    {
        for (int i = 0; i < argc; i++)
        {

            fptc = fopen(path, "r+b");

            while (fread(&complete, sizeof(tasks), 1, fptc) == 1)
            {

                if (complete.id == atoi(argv[i]))
                {
                    strcpy(complete.status, "done");

                    fseek(fptc, -sizeof(tasks), SEEK_CUR);

                    fwrite(&complete, sizeof(tasks), 1, fptc);
                }

            }

            fclose(fptc);

        }
    }

}

    void help_topic(char *argv[])
    {
        if (strcmp(argv[1], "--help") == 0)
        {

            printf("task create\t\t\t\t Creates a new task registration");

            printf("\ntask ls\t\t\t\t   List the created tasks");

            printf("\ntask complete\t\t\t\t Concludes the task");

            printf("\ntask rewind \t\t\t\t Rewinds the concluded tasks");

            printf("\ntask del\t\t\t\t Delete or Removes the task or multiples tasks");

            printf("\n*****How to use it *****");

            printf("\ngcc main.c && (a.exe) or (a.out) task create \"title\" priority(0-10) status(ongoing/done) \"duedate\"");


        }

    }

    void create_topic(char *argv[])
{
    tasks topic;


    if (strcmp(argv[1], "task") == 0 && strcmp(argv[2], "create") == 0)
    {

        id_topic(&topic);

        title_topic(argv,&topic);

        priority_topic(argv,&topic);

        status_topic(argv,&topic);

        due_date_topic(argv,&topic);

        reg_date_topic( &topic);

        FILE *ftpr;

        ftpr=fopen(path,"ab");

        fwrite(&topic, sizeof(tasks),1,ftpr);

        fclose(ftpr);


    }

}

    void listPriority_asc_topic(int argc, char *argv[])
    {
        if (argc== 6 && strcmp(argv[1], "task") == 0 && strcmp(argv[2], "ls") == 0 && strcmp(argv[3],"--order")==0 && strcmp(argv[4],"priority")==0 && strcmp(argv[5],"asc")==0)
        {
            tasks store;

            tasks array[MAX_NUMBER];

            FILE *frp;

            int total = 0;

            frp = fopen(path, "rb");

            while (fread(&store, sizeof(tasks), 1, frp) == 1)
            {
                array[total++] = store;
            }
            for (int i = 0; i < total - 1; i++)
            {
                for (int j = 0; j < total - i - 1; j++)
                {
                    if (array[j].priority > array[j + 1].priority)
                    {
                        store = array[j];
                        array[j] = array[j + 1];
                        array[j + 1] = store;
                    }
                }
            }
            time_t rawtime = store.regidate;

            struct tm ts;

            char registration_date[80];

            ts = *localtime(&rawtime);/// Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"

            strftime(registration_date, sizeof(registration_date), "%a %Y-%m-%d %H:%M:%S ", &ts);

            for (int i = 0; i < total; i++)

                printf("\n\tid: %d, \n\ttitle : %s, \n\tpriority: %d, \n\tstatus: %s ,\n\ttime: %s, \n\tdue date: %s\n\n",
                       array[i].id, array[i].title, array[i].priority, array[i].status, registration_date,
                       array[i].due_date);
        }
    }

    void listPriority_desc_topic(int argc, char *argv[])
    {
        if (argc== 6 && strcmp(argv[1], "task") == 0 && strcmp(argv[2], "ls") == 0 && strcmp(argv[3],"--order")==0 && strcmp(argv[4],"priority")==0 && strcmp(argv[5],"desc")==0)
        {
            tasks store;

            tasks array[MAX_NUMBER];

            FILE *frp;

            int total = 0;

            frp = fopen(path, "rb");

                while (fread(&store, sizeof(tasks), 1, frp) == 1)
                {
                 array[total++] = store;
                }
                for (int i = 0; i < total - 1; i++)
                {
                    for (int j = 0; j < total - i - 1; j++)
                    {
                         if (array[j].priority < array[j + 1].priority)
                        {
                            store = array[j];

                            array[j] = array[j + 1];

                            array[j + 1] = store;
                        }
                    }
                }
             time_t rawtime = store.regidate;

            struct tm ts;

            char registration_date[80];

            ts = *localtime(&rawtime);

            strftime(registration_date, sizeof(registration_date), "%a %Y-%m-%d %H:%M:%S ", &ts);

            for (int i = 0; i < total; i++)

            printf("\n\tid: %d, \n\ttitle : %s, \n\tpriority: %d, \n\tstatus: %s ,\n\ttime: %s, \n\tdue date: %s\n\n",
                   array[i].id, array[i].title, array[i].priority, array[i].status, registration_date,
                   array[i].due_date);
        }
    }

    void list_topic(int argc, char *argv[])
    {
        if (argc == 3 && strcmp(argv[1],"task") ==0 && strcmp(argv[2],"ls") ==0)
        {

            tasks store;

            FILE *lfp;

            lfp = fopen(path, "rb");

            while (fread(&store, sizeof(tasks), 1, lfp) == 1)
            {
                time_t rawtime = store.regidate;

                struct tm ts;

                char registration_date[80];


                ts = *localtime(&rawtime);/// Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"

                strftime(registration_date, sizeof(registration_date), "%a %Y-%m-%d %H:%M:%S ", &ts);

                printf("\n\tid: %d, \n\ttitle : %s, \n\tpriority: %d, \n\tstatus: %s ,\n\ttime: %s, \n\tdue date: %s\n\n",
                   store.id, store.title, store.priority, store.status, registration_date, store.due_date);
            }
            fclose(lfp);
        }

    }

    void del_topic(int argc, char *argv[])
    {
        if (strcmp(argv[1],"task") == 0  && strcmp(argv[2],"del")==0)
        {
            char iipath[]="tempor.bin";

            tasks store;

            FILE *rfp, *wfp;

            for (int i = 3; i< argc; i++)
            {

                rfp = fopen(path, "rb");

                wfp = fopen(iipath, "wb");

                while (fread(&store, sizeof(tasks), 1, rfp) == 1)
                {
                    if (store.id != atoi(argv[i]))

                        fwrite(&store, sizeof(tasks), 1, wfp);

                }
                fclose(rfp);

                fclose(wfp);

                remove(path);

                rename(iipath, path);

            }

        }

 }

    int quit_topic(int argc,char *argv[])
 {
     if (strcmp(argv[1], "quit") == 0)
     {

         printf("GoodBye!!");

         return 0;

     }


 }
/**
 main function started
*/

    int main(int argc, char *argv[])
    {

        quit_topic(argc,argv);

        help_topic(argv);

        create_topic(argv);

        listPriority_desc_topic(argc, argv);

        listPriority_asc_topic(argc, argv);

        list_topic(argc, argv);

        time_t currenttime;

        time(&currenttime);

        //struct tm *mytime = localtime(&currenttime);

        //printf("%d/%d/%d\n",mytime->tm_year+1900,mytime->tm_mon+1,mytime->tm_mday); /**it just prints the current date and time.*/

        del_topic(argc, argv);

        rewind_topic(argc, argv);

        conclude_topic(argc, argv);

    }










