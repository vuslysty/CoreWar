/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_state1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuslysty <vuslysty@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 19:20:01 by vuslysty          #+#    #+#             */
/*   Updated: 2019/05/22 13:05:23 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "lexer.h"

int		id_direct(t_asm *a)
{
	t_fsm	*fsm;
	char	*data;
	int		*i;
	size_t	len;

	fsm = a->fsm;
	len = fsm->curr - fsm->start - 1;
	data = (char*)ft_memalloc(len + 1);
	ft_strncpy(data, fsm->start + 1, len);
	i = (int*)malloc(sizeof(int));
	*i = ft_atoi(data);
	free(data);
	add_to_token_list(&a->token_list, DIRECT, i, a);
	return (0);
}

int		id_direct_label(t_asm *a)
{
	t_fsm	*fsm;
	char	*data;
	size_t	len;

	fsm = a->fsm;
	len = fsm->curr - fsm->start - 2;
	data = (char*)ft_memalloc(len + 1);
	ft_strncpy(data, fsm->start + 2, len);
	add_to_token_list(&a->token_list, DIRECT_LABEL, data, a);
	return (0);
}

int		id_indirect_label(t_asm *a)
{
	t_fsm	*fsm;
	char	*data;
	size_t	len;

	fsm = a->fsm;
	len = fsm->curr - fsm->start - 1;
	data = (char*)ft_memalloc(len + 1);
	ft_strncpy(data, fsm->start + 1, len);
	add_to_token_list(&a->token_list, INDIRECT_LABEL, data, a);
	return (0);
}

int		id_commentary(t_asm *a)
{
	if (a)
		;
	return (0);
}

int		id_separator(t_asm *a)
{
	add_to_token_list(&a->token_list, SEPARATOR, NULL, a);
	return (1);
}
