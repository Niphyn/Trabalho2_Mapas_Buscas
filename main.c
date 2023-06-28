#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

int main()
{
    int n, i, val;
    Queue *s = queue_construct();

    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        scanf("%d", &val);
        queue_push(s, val);
    }

    while (!queue_empty(s))
        printf("%d\n", queue_pop(s));

    queue_destroy(s);
    return 0;
}