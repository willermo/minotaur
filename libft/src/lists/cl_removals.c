/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_removals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doriani <doriani@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 12:54:15 by doriani           #+#    #+#             */
/*   Updated: 2024/02/08 11:37:59 by doriani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_cl_list *
cl_remove_node(t_cl_list *node) {
    if (node == NULL || node->next == node)
        return (NULL);
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->prev = NULL;
    node->next = NULL;
    return (node);
}

t_cl_list *
cl_remove_begin(t_cl_list *head) {
    if (head == NULL || head->next == head)
        return (NULL);
    return (cl_remove_node(head->next));
}

t_cl_list *
cl_remove_end(t_cl_list *head) {
    if (head == NULL || head->next == head)
        return (NULL);
    return (cl_remove_node(head->prev));
}

t_cl_list *
cl_remove_node_by_position(t_cl_list *head, int pos) {
    register t_cl_list *temp;
    register int i;

    if (head == NULL || cl_is_empty(head) || pos < 1 || pos > cl_size(head))
        return (NULL);
    i = 1;
    temp = head->next;
    while (i++ < pos)
        temp = temp->next;
    return (cl_remove_node(temp));
}

t_cl_list *
cl_remove_node_by_data(t_cl_list *head, void *data,
                       int(cmp_data)(void *, void *)) {
    register t_cl_list *temp;

    if (head == NULL || cl_is_empty(head))
        return (NULL);
    temp = head->next;
    while (temp != head) {
        if (cmp_data(temp->data, data) == 0)
            return (cl_remove_node(temp));
        temp = temp->next;
    }
    return (NULL);
}

void
cl_dismiss_list(t_cl_list *head) {
    while (cl_size(head))
        free(cl_remove_begin(head));
}
