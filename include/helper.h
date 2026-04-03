#ifndef HELPER_H
# define HELPER_H

# include <stdio.h>
# include <stdlib.h>

// Linked list of integers.
typedef struct list
{
    int val;
    struct list *next;
} s_list;

// Prepends val to list and returns the new head.
s_list *add_to_list(int val, s_list *list);

// Frees all nodes of the list.
void destroy_list(s_list *list);

// Frees a NULL-terminated array of strings.
void destroy_matrix(char **mat);

#endif /* !HELPER_H */
