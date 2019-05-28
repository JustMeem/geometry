#include "shape.h"
#include <stdio.h>

/*
struct stringlistnode;
typedef struct stringlistnode stringlistnode;
struct stringlistnode
{
        stringlistnode *next;
        char *string;
};*/
struct listnode;
typedef struct listnode listnode;
struct listnode {
    Shape* s;
    listnode* next;
    // stringlistnode *intersections;
};

int stringStream(char* string)
{
    char buffer;
    int i = 0;
    while ((buffer = getchar()) != '\n') {
        if ((buffer == '@') || (i > 254))
            return 0;
        string[i++] = buffer;
    }
    string[i] = '\0';
    return 1;
}

/*
void addIntersection(stringlistnode *node, const Shape *s, size_t n)
{
        if(node == NULL)
                return;
        while (node->next != NULL)
        {
                node = node->next;
        }
        if (!(node->next = malloc(sizeof(stringlistnode))))
        {
                printf("Memory access error\n");
                return;
        }
        if (!(node->next->string = malloc(sizeof(char)*260)))
        {
                printf("Memory access error\n");
                return;
        }
        node = node->next;
        node->next = NULL;
        switch (s->n)
        {
        case 1:
                sprintf(node->string, "%d. circle", n);
                return;
        case 4:
                sprintf(node->string, "%d. triangle", n);
                return;
        default:
                sprintf(node->string, "%d. polygon", n);
        }
}
*/
int main()
{
    char string[255];
    size_t counter = 0;
    listnode shapelist = (listnode){NULL, NULL};
    listnode* buffer = &shapelist;
    while (stringStream(string)) {
        if (string[0] == '\0')
            continue;
        counter++;
        if (!(buffer->next = malloc(sizeof(listnode)))) {
            printf("Memory access error\n");
            return 0;
        }
        switch (interpret(string, &(buffer->next->s))) {
        case 1:
            printf("Memory access error\n\n");
            return 0;
        case -1:
            printf("Unexpected figure type\n");
            break;
        case -2:
            printf("Invaild figure parameters\n");
            break;
        default:
            buffer = buffer->next;
            buffer->next = NULL;
            // buffer->intersections = NULL;
        }
    }
    listnode* s = &shapelist;
    char intersect[counter][counter];
    int j = 0;
    for (size_t i = 0; i < counter - 1; i++) {
        s = s->next;
        buffer = s->next;
        j = i + 1;
        while (buffer != NULL) {
            if (isIntersects(s->s, buffer->s)) {
                intersect[i][j] = 1;
                intersect[j][i] = 1;
            }
            buffer = buffer->next;
            j++;
        }
    }
    /*for (int i = 0; i < counter - 1; i++)
    {
            s = s->next;
            buffer = s->next;
            j = i + 1;
            while (buffer != NULL)
            {
                    if (isIntersects(s->s, buffer->s))
                    {
                            if (s->intersections == NULL)
                            {
                                    if (!(s->intersections =
    malloc(sizeof(stringlistnode))))
                                    {
                                            printf("Memory access error\n");
                                            return 0;
                                    }
                                    s->intersections->next = NULL;
                                    if (!(s->intersections->string =
    malloc(sizeof(char)*260)))
                                    {
                                            printf("Memory access error\n");
                                            return 0;
                                    }
                            }
                            addIntersection(s->intersections, buffer->s, j + 1);
                            if (buffer->intersections == NULL)
                            {
                                    if (!(buffer->intersections =
    malloc(sizeof(stringlistnode))))
                                    {
                                            printf("Memory access error\n");
                                            return 0;
                                    }
                                    s->intersections->next = NULL;
                                    if (!(buffer->intersections->string =
    malloc(sizeof(char)*260)))
                                    {
                                            printf("Memory access error\n");
                                            return 0;
                                    }
                            }
                            addIntersection(buffer->intersections, s->s, i + 1);
                    }
                    buffer = buffer->next;
                    j++;
            }
    }*/
    j = 0;
    buffer = shapelist.next;
    while (buffer != NULL) {
        printf("%d. %s\n\tprimeter = %f\n\tarea = %f\n\tintersects:\n",
               j + 1,
               toString(buffer->s),
               getPerimeter(buffer->s),
               getArea(buffer->s));
        for (size_t i = 0; i < counter; i++) {
            if (intersect[j][i] == 1) {
                switch (buffer->s->n) {
                case 1:
                    printf("\t  %d. circle\n", i + 1);
                    break;
                case 4:
                    printf("\t  %d. triangle\n", i + 1);
                    break;
                default:
                    printf("\t  %d. polygon\n", i + 1);
                }
            }
        }
        buffer = buffer->next;
        j++;
    }
    return 1;
}