/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npiatiko <npiatiko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 12:19:23 by npiatiko          #+#    #+#             */
/*   Updated: 2019/04/26 16:10:38 by npiatiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "libft.h"
# include "op.h"
# include <errno.h>

typedef enum	e_identifier
{
	COMMENT, NAME, LABEL, INSTRUCTION,
	REGISTER, INDIRECT, DIRECT, DIRECT_LABEL,
	INDIRECT_LABEL, SEPARATOR, STRING
}				t_identifier;

typedef struct  s_asm
{
	int 				row;
	int 				col;
	struct s_fsm		*fsm;
    struct s_op_list	*op_list;
    struct s_token_list	*token_list;
    int 				(*lex_condition[13])(char *c);
	int 				(*id_state[13])(struct s_asm *a);
}               t_asm;

typedef struct	s_fsm
{
	int 				st_col;
	int 				st_row;
	char 				*start;
	char 				*curr;
	int 				state;
	int 				**table;
	int					tab_row;
	int					tab_col;
	char 				*code;
}				t_fsm;

typedef struct	s_op_list					//Структура для зберігання списку операцій (одна строка - одна операція)
{
	struct s_token_list	*token_list;		//Для зберігання списку з токенами
	struct s_op_list	*next;				//Перехід на наступний токен
}				t_op_list;

typedef struct	s_token_list
{
	enum e_identifier	ident;			//ідентифікатор токену (один зі списку нижче)
	void				*data;				//Для зберігання самої строки, що відповідає даному токену
	int					col;				//Номер колонки (де знаходиться перший символ токену)
	int					row;				//Номер рядка
	struct s_token_list	*next;
}				t_token_list;
 
typedef struct  s_label_list
{
    char                *name;
    struct s_op_list    *op;
    struct s_label_list *next;
}               t_label_list;

// COMMENT - NULL
// NAME	- NULL
// LABEL - name of label (char*)
// INSTRUCTION - name of instruction (char*)
// REGISTER - number (int)
// INDIRECT - number (int)
// DIRECT - number (int)
// DIRECT_LABEL - name of label (char*)
// INDIRECT_LABEL - name of label (char*)
// SEPARATOR - NULL
// STRING - (char*)

typedef struct	s_op
{
	char	*name;
	int		args;
	int		targs[3];
	int		opcode;
	int		cycle;
	char	*descr;
	int		codoctal;
	int		dirsize;
}				t_op;

static char 	*g_ident_str[] =
{
	"COMMENT", "NAME", "LABEL", "INSTRUCTION",
	"REGISTER", "INDIRECT", "DIRECT", "DIRECT_LABEL",
	"INDIRECT_LABEL", "SEPARATOR", "STRING"
};
static t_op		g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, DIR_SIZE},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, DIR_SIZE},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, DIR_SIZE},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, DIR_SIZE},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, DIR_SIZE},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, DIR_SIZE},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, DIR_SIZE},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, DIR_SIZE},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, IND_SIZE},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		10, 25, "load index", 1, IND_SIZE},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		11, 25, "store index", 1, IND_SIZE},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, IND_SIZE},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, DIR_SIZE},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		14, 50, "long load index", 1, IND_SIZE},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, IND_SIZE},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, DIR_SIZE},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};
void ft_validation(t_op_list *oplist, t_header *header);
void	ft_exit(char *stre, int e);
#endif
