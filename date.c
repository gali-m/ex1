#include <stdlib.h>
#include <stdbool.h>
#include "date.h"

#define MIN_DAY 1
#define MAX_DAY 30
enum months{JAN,FEB,MAR,APR,MAY,JUN,JUL,AUG,SEP,OCT,NOV,DEC,NUM_OF_MONTHS};


struct Date_t 
{
    int day;
    enum months month;
    int year;
};

// Function for checking that the date's values are valid
static bool isValid(int day, int month, int year)
{
    return (day >= MIN_DAY && day <= MAX_DAY && month >= JAN && month <= DEC);
}

Date dateCreate(int day, int month, int year)
{
    if (!isValid(day,month-1,year))
    {
        return NULL;
    }

    // Create new date
    Date date = (Date)malloc(sizeof(struct Date_t));
    if (date == NULL)
    {
        return NULL;
    }
    
    // Assign values
    date->day = day;
    date->month = month-1;
    date->year = year;

    return date;
}

void dateDestroy(Date date)
{
    if (date != NULL)
    {
        free(date);
    }
}

Date dateCopy(Date date)
{
    if (date == NULL)
    {
        return NULL;
    }
    
    // Create a new date with the same values
    return dateCreate(date->day,date->month+1,date->year);
}

bool dateGet(Date date, int* day, int* month, int* year)
{
    if (date == NULL || day == NULL || month == NULL || year == NULL)
    {
        return false;
    }

    // Assign date's values to the given pointers
    *day = date->day;
    *month = date->month + 1;
    *year = date->year;
    
    return true;
}

int dateCompare(Date date1, Date date2)
{
    if (date1 == NULL || date2 == NULL || (date1->year == date2->year && date1->month == date2->month && date1->day == date2->day))
    { // input is null or dates are equal
        return 0;
    }
    
    if (date1->year > date2->year || (date1->year == date2->year && date1->month > date2->month) 
            || (date1->year == date2->year && date1->month == date2->month && date1->day > date2->day))
    {// date1 is later than date2
        return 1;
    }
    
    // date1 is earlier than date2
    return -1;
}

void dateTick(Date date)
{
    if (date == NULL)
    {
        return;
    }
    
    if (date->day == MAX_DAY)
    { // End of the month
        date->day = MIN_DAY;

        if (date->month == DEC)
        { // End of the year
            date->month = JAN;
            date->year++;
        }
        else
        {
            date->month++;
        }
    }
    else
    { // Regular 'tick'
        date->day++;
    }
}