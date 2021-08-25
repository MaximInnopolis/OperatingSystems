#include <stdio.h>
#include <string.h>

void reverse(char str[100]);

int main()
{
    char str[100];

    printf("Enter a string:\n");
    gets(str);
    reverse(str);
    printf("Your sentence in reverse:\n%s", str);
    return 0;
}

void reverse(char str[100]) {
    int length, c;
    char *begin, *end, tmp;

    length = strlen(str);
    begin = str;
    end = str;

    for (c = 0; c < length - 1; ++c)
        end++;

    for (c = 0; c < length/2; ++c)
    {
        tmp   = *end;
        *end   = *begin;
        *begin = tmp;

        begin++;
        end--;
    }
}