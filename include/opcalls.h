/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opcalls.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 17:14:27 by myaremen          #+#    #+#             */
/*   Updated: 2019/05/02 01:46:40 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPCALLS_H
# define OPCALLS_H

# include <stdint.h>
# include <stdbool.h>
#include "abstract_cpu.h"

typedef enum e_opcode
{
	no_op = -1,
	oplowborder = 0,
	oplive = 0,
	opld,
	opst,
	opadd,
	opsub,
	opand,
	opor,
	opxor,
	opzjmp,
	opldi,
	opsti,
	opfork,
	oplld,
	oplldi,
	oplfork,
	opaff,
	ophighborder
} t_opcode;

typedef struct	s_op
{
	char	*name;
	uint32_t		args;
	uint8_t		targs[3];
	uint8_t		opcode;
	uint32_t		cycle;
	char	*descr;
	bool	codoctal;
	bool		tdir_size;
}				t_op;

typedef struct s_decoded_op
{
	uint32_t ip;
	uint8_t tparams;
	t_opcode opcode;
	t_memory args[3];
	bool valid;
} t_decoded_op;

typedef struct s_thread
{
    void *player;       //указатель на игрока, который породил каретку
	uint32_t ip;		//код операции, на которой стоит каретка
	bool cf;			//Флаг, который могут изменять некоторые операции
	uint32_t id;		//номер каретки
	uint32_t reg[16];	//регистры, количество которых задано в константе
	uint8_t  *vm_memory;//указатель на оперативную память
	uint32_t lives;		//сколько раз поток сообщил о том, что жив
	bool alive;			//определяет, жив ли поток
	uint16_t wait;		//сколько еще ждать до выполнения операции
	t_decoded_op op;	//содержит информацию об операции, которая ожидает выполнения
	bool processing;	//
} t_thread;

typedef struct s_opcall
{
	uint8_t opcode;
	void (*opfunc)(t_thread*, t_memory*, t_memory*, t_memory*);
} t_opcall;

t_opcall opcalls[ophighborder];

void f_live(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);

void f_ld(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);

void f_st(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);

void f_add(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);

void f_sub(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);

void f_and(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);

void f_or(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);

void f_xor(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);

void f_zjmp(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);

void f_ldi(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);

void f_sti(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);

void f_fork(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);

void f_lld(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);

void f_lldi(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);

void f_lfork(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);

void f_aff(t_thread *sp, t_memory *p1, t_memory *p2, t_memory *p3);

#endif
