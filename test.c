#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

char * duplicateString(char *string_to_duplicate, int times)
{
    assert(string_to_duplicate);
    assert(times > 0);

    int len = strlen(string_to_duplicate);

    char *out = malloc((len * times) + 1);
    if (out == NULL)
    {
        return NULL;
    }

    for (int i = 0; i < times; i++)
    {
        strcpy(out + (i*len), string_to_duplicate);
    }

    return out;
}

int main(){
    char * string_out;
    string_out = duplicateString("asdf", 3);
    printf(string_out);
    return 0;
}
