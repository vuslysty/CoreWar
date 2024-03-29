/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_list_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:24:05 by vuslysty          #+#    #+#             */
/*   Updated: 2019/05/22 13:05:23 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	add_to_op_list(t_op_list **op_list, t_token_list *token_list)
{
	t_op_list	*tmp;

	tmp = (t_op_list*)ft_memalloc(sizeof(t_op_list));
	tmp->token_list = token_list;
	if (*op_list == NULL)
		*op_list = tmp;
	else
	{
		tmp->next = *op_list;
		*op_list = tmp;
	}
}

void	reverse_op_list(t_op_list **op_list)
{
	t_op_list	*prev;
	t_op_list	*next;

	if (*op_list == NULL)
		return ;
	prev = NULL;
	next = (*op_list)->next;
	while (next != NULL)
	{
		(*op_list)->next = prev;
		prev = *op_list;
		*op_list = next;
		next = (*op_list)->next;
	}
	(*op_list)->next = prev;
}
