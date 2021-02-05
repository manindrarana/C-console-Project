#define MAX_NUMBER 50
#define MIN_NUMBER 20
#include<time.h>

#ifndef HEADER_H
#define HEADER_H

/** structure that represents a enterprises programmer  */
typedef struct
{
    int id; /** Contains the number of id on ascending order*/
    char title[MAX_NUMBER];///contains the name of the tasks in string so we had used the arrays on it i like to used (Macro) to look good .
    short priority;
    char status[MIN_NUMBER];
    char due_date[MIN_NUMBER];
    int regidate;
}tasks;

#endif

