/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myaremen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 17:34:47 by myaremen          #+#    #+#             */
/*   Updated: 2019/06/05 17:34:49 by myaremen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "vm.h"

void		print_usage(char *argv)
{
	char	*prog_name;

	prog_name = ft_strrchr(argv, '/');
	if (!prog_name)
		prog_name = argv;
	ft_strrchr(argv, '/');
	ft_printf("Usage: .%s\t[-%c N -%c N -%c N "
		"| -%c -%c ] <champion1.cor> <...>\n",
		prog_name, OPTIONS[0], OPTIONS[2], OPTIONS[4], OPTIONS[6], OPTIONS[7]);
	ft_printf("\t-a\t\t\t: Prints output from \"aff\" (Default is to hide it)\n"
		"\t-s\t\t\t: Ncurses output mode\n"
	"\t-n N\t\t: \n"
	"#### TEXT OUTPUT MODE #################################################\n"
	"\t-d N\t\t: Dumps memory after N cycles then exits\n"
	"\t-v N\t\t: Verbosity levels, can be added together to enable several\n"
	"\t\t\t\t\t- 0 : Show only essentials\n"
	"\t\t\t\t\t- 1 : Show lives\n"
	"\t\t\t\t\t- 2 : Show cycles\n"
	"\t\t\t\t\t- 4 : Show operations (Params are NOT litteral ...)\n"
	"\t\t\t\t\t- 8 : Show deaths\n"
	"\t\t\t\t\t- 16 : Show PC movements (Except for jumps)\n");
	exit(1);
}

void		parce_option(int argc, char *argv[], uint8_t *arg_num, char *option)
{
	int		param;

	(argc >= *arg_num && ft_string_to_number(argv[*arg_num], &param))
	? (*arg_num)++ : print_usage(argv[0]);
	if (ft_strnequ(option, "dump", 4))
	{
		if (param < 0)
			handle_error(error_option);
		get_vm(0)->options.o_dump = true;
		get_vm(0)->options.o_dump_point = param;
	}
	else if (ft_strnequ(option, "v", 1))
	{
		get_vm(0)->options.o_a = true;
		get_vm(0)->options.o_v_param = param;
	}
	else if (ft_strnequ(option, "n", 1))
	{
		if (param > 4 || param < 1)
			handle_error(error_option);
		get_vm(0)->options.o_next_player = param;
	}
	else
		print_usage(argv[0]);
}

bool		is_option(char **argv, int argc, uint8_t *arg_num, char *string1)
{
	char	*option;

	if (argv[*arg_num][0] != '-')
		return (false);
	if ((option = ft_strstr(string1, &argv[*arg_num][1])))
	{
		get_vm(0)->options.o_next_player = 0;
		if (*(option + 1) == ':' || ft_strequ(argv[*arg_num], "-dump"))
		{
			(*arg_num)++;
			parce_option(argc, argv, arg_num, option);
		}
		else
		{
			if (argv[*arg_num][1] == 's')
			{
				get_vm(0)->options.visual_ncurses = true;
				get_vm(0)->options.o_dump = false;
			}
			else if (argv[*arg_num][1] == 'a')
				get_vm(0)->options.o_a = true;
			(*arg_num)++;
		}
	}
	return (true);
}

int			place_process(uint8_t *files, uint8_t o_numb, uint8_t i)
{
	int8_t	drag;

	if (o_numb)
	{
		if (files[o_numb - 1])
		{
			drag = 3;
			while (drag > (o_numb - 1))
			{
				files[drag] = files[drag - 1];
				drag--;
			}
		}
		files[o_numb - 1] = i;
	}
	else
	{
		drag = 0;
		while (files[drag] && drag < 3)
			drag++;
		files[drag] = i;
	}
	return (0);
}

void		handle_options(char **arguments, int argc, t_vm *vm, uint8_t *files)
{
	uint8_t		i;

	i = 1;
	while (i <= argc)
	{
		if (is_option(arguments, argc, &i, OPTIONS))
		{
			continue ;
		}
		place_process(&files[0], vm->options.o_next_player, i);
		vm->options.o_next_player = 0;
		vm->nplayers++;
		i++;
	}
}
