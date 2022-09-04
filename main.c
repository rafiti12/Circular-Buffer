#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"

int main()
{
    int n, b, err_code;
    printf("Podaj rozmiar bufora: ");
    if (!scanf("%d", &n))
    {
        printf("Incorrect input");
        return 1;
    }
    if (n <= 0)
    {
        printf("Incorrect input data");
        return 2;
    }
    struct circular_buffer_t* a;
    if (circular_buffer_create_struct(&a, n) == 2)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    while (1)
    {
        printf("Co chcesz zrobic? ");
        if (!scanf("%d", &n))
        {
            circular_buffer_destroy_struct(&a);
            printf("Incorrect input");
            return 1;
        }
        if (n == 0) break;
        switch (n)
        {
        case 1:
            printf("Podaj liczbe ");
            if (!scanf("%d", &b))
            {
                circular_buffer_destroy_struct(&a);
                printf("Incorrect input");
                return 1;
            }
            circular_buffer_push_back(a, b);
            break;
        case 2:
            if (circular_buffer_empty(a) == 1)
                printf("Buffer is empty\n");
            else
                printf("%d\n",circular_buffer_pop_back(a, &err_code));
            break;
        case 3:
            if (circular_buffer_empty(a) == 1)
                printf("Buffer is empty\n");
            else
                printf("%d\n", circular_buffer_pop_front(a, &err_code));
            break;
        case 4:
            if (circular_buffer_empty(a) == 1)
                printf("Buffer is empty\n");
            else
            {
                circular_buffer_display(a);
                printf("\n");
            }
            break;
        case 5:
            printf("%d\n", circular_buffer_empty(a));
            break;
        case 6:
            printf("%d\n", circular_buffer_full(a));
            break;
        default:
            printf("Incorrect input data\n");
            break;
        }
    }
    circular_buffer_destroy_struct(&a);

    return 0;
}
