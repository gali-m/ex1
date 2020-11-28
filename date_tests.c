#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "date.h"


int main(int argc, char *argv[]) 
{
    Date date1 = dateCreate(30,12,2020);

    int *day = (int*)malloc(sizeof(int));
    int *month = (int*)malloc(sizeof(int));
    int *year = (int*)malloc(sizeof(int));
    if (day == NULL || month == NULL || year == NULL)
    {
        return 0;
    }

    if (dateGet(date1,day,month,year))
    {
        printf("The 1st date is: %d/%d/%d\n", *day,*month,*year);
    }

    Date date2 = dateCopy(date1);
    if (dateGet(date2,day,month,year))
    {
        printf("The 2nd date is: %d/%d/%d\n", *day,*month,*year);
    }
    printf("Comparison: %d\n\n",dateCompare(date1,date2));

    dateTick(date2);
    if (dateGet(date1,day,month,year))
    {
        printf("The 1st date is: %d/%d/%d\n", *day,*month,*year);
    }
    if (dateGet(date2,day,month,year))
    {
        printf("The 2nd date is: %d/%d/%d\n", *day,*month,*year);
    }
    printf("Comparison: %d\n\n",dateCompare(date1,date2));

    dateTick(date2);
    if (dateGet(date2,day,month,year))
    {
        printf("The 2nd date is: %d/%d/%d\n", *day,*month,*year);
    }

    dateDestroy(date1);
    dateDestroy(date2);
    printf("ok\n");

    free(day);
    free(month);
    free(year);
    return 0;
}
