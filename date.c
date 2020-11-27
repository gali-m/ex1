#include <stdlib.h>
#include <stdbool.h>
#include "date.h"

enum months{JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC,NUM_OF_MONTHS};
struct Date_t 
{
    int day;
    enum months month;
    int year;
};

static bool isValid(int day, int month, int year)
{
    return (day >=1 && day <= 30 && month >= JAN && month <= DEC);
}

Date dateCreate(int day, int month, int year)
{
    if (!isValid(day,month,year))
    {
        return NULL;
    }

    Date date = (Date)malloc(sizeof(Date));
    if (date == NULL)
    {
        return NULL;
    }
    
    date->day = day;
    date->month = month;
    date->year = year;

    return date;
}