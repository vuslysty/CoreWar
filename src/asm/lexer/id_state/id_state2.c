#include "asm.h"
#include "lexer.h"

int		id_string(t_asm *a)
{
	t_fsm	*fsm;
	char	*data;
	size_t 	len;

	fsm = a->fsm;
	len = fsm->curr - fsm->start - 1;
	data = (char*)ft_memalloc(len + 1);
	ft_strncpy(data, fsm->start + 1, len);
	add_to_token_list(&a->token_list, STRING, data, a);
	return (1);
}

int		id_name(t_asm *a)
{
	add_to_token_list(&a->token_list, NAME, NULL, a);
	return ((int)ft_strlen(NAME_CMD_STRING));
}

int		id_comment(t_asm *a)
{
	add_to_token_list(&a->token_list, COMMENT, NULL, a);
	return ((int)ft_strlen(COMMENT_CMD_STRING));
}