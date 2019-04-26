/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 15:57:21 by myaremen          #+#    #+#             */
/*   Updated: 2019/04/26 07:54:57 by oivanyts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	players_sort_by_id(t_player *players, uint32_t nplayers)
{
	(void)players;
	(void)nplayers;
}

uint32_t player_threads_alive(t_player *player)
{
	size_t thread;
	uint32_t alive;

	alive = 0;
	thread = 0;
	while (thread < threads_size(&player->threads))
	{
		if (threads_pat(&player->threads, thread)->alive)
		{
			++alive;
		}
		++thread;
	}
	return (alive);
}

uint32_t threads_alive(t_player *players, uint32_t nplayers)
{
	uint32_t player;
	uint32_t alive;

	player = 0;
	alive = 0;
	while (player < nplayers)
	{
		alive += player_threads_alive(&players[player]);
		++player;
	}
	return (alive);
}

void	vm_cycle(t_player *players, uint32_t nplayers)
{
	uint32_t player;
	uint32_t player_thread;
	uint32_t cycles;
	uint32_t checks;
	uint32_t alive;

	cycles = CYCLE_TO_DIE;
	player = 0;
	checks = 0;
	while ((alive = threads_alive(players, nplayers) && (cycles > 0)))
	{
		if (checks == MAX_CHECKS || alive > 21)
		{
			cycles -= CYCLE_DELTA;
			checks = 0;
		}
		++checks;
		while (player < nplayers)
		{
			player_thread = 0;
			while (player_thread < threads_size(&players[player].threads))
			{
				op_exec(threads_pat(&players[player].threads, player_thread));
				++player_thread;
			}
			++player;
		}
		if (player == nplayers)
		{
			player = 0;
		}
	}
}

t_opcode decode_opcode(struct s_thread *pc)
{
	t_opcode opcode;

	opcode = as_byte(vm_memory)[pc->ip % MEM_SIZE];
	if (opcode <= oplowborder || opcode >= ophighborder)
	{
		pc->alive = 0;
		return (opcode);
	}
	pc->ip += 1;
	return (opcode);
}

void	check_op_params(t_opcode opcode, uint8_t tparams)
{
	if ((t_ops[opcode].targs[0] & (tparams & T_FIRST_PARAM)) == 0)
	{
		//error
	}
	else if ((t_ops[opcode].targs[1] & (tparams & T_SECOND_PARAM)) == 0)
	{
		//error
	}
	else if ((t_ops[opcode].targs[0] & (tparams & T_FIRST_PARAM)) == 0)
	{
		//error
	}
}

uint8_t	decode_tparams(struct s_thread *pc, t_opcode opcode)
{
	uint8_t tparams;

	tparams = as_byte(vm_memory)[pc->ip % MEM_SIZE];
	check_op_params(opcode, tparams);
	pc->ip += 1;
	return (tparams);
}

void	*decode_param(t_opcode opcode, uint8_t tparams, t_thread *pc, uint8_t param_number)
{
	void *param;
	uint8_t  tparam;
	uint8_t reg_number;
	uint32_t addr;

	param = 0;
	if (param_number <= t_ops[opcode].nargs)
	{
		if (param_number == 1)
		{
			tparam = tparams & T_FIRST_PARAM;
		}
		else if (param_number == 2)
		{
			tparam = tparams & T_SECOND_PARAM;
		}
		else
		{
			tparam = tparams & T_THIRD_PARAM;
		}
		if (tparam == T_REG)
		{
			reg_number = as_byte(vm_memory)[pc->ip];
			if (reg_number == 0 || reg_number > REG_NUMBER)
			{
				//error
			}
			param = &pc->reg[reg_number - 1];
		}
		else if (tparam == T_DIR)
		{
//			param = (as_byte(vm_memory)[pc->ip]);

		}
		else if (tparam == T_IND)
		{
			addr = pc->ip + as_byte(vm_memory)[pc->ip];
			addr = pc->ip % MEM_SIZE;
			param = (uint32_t*)&as_byte(vm_memory)[addr];
			pc->ip += 2;
		}
		else
		{
			//error
		}
	}
	return (param);
}

t_decoded_op	op_decode(struct s_thread *pc)
{
	t_decoded_op op;
	uint8_t tparams;

	op.opcode = decode_opcode(pc);
	if (pc->alive == 0)
	{
		return (op);
	}
	tparams = decode_tparams(pc, op.opcode);
	op.args[0] = decode_param(op.opcode, tparams, pc, 1);
	op.args[1] = decode_param(op.opcode, tparams, pc, 2);
	op.args[2] = decode_param(op.opcode, tparams, pc, 3);
	return (op);
}

void	op_exec(struct s_thread *pc)
{
	t_decoded_op op;

	if (pc->wait)
	{
		return ;
	}
	op = op_decode(pc);
	opcalls[op.opcode].opfunc(pc, op.args[0], op.args[1], op.args[2]);
}

uint8_t	*as_byte(void *ptr)
{
	return (ptr);
}