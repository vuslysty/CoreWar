//
// Created by actionfenix on 30.04.19.
//

#include "abstract_cpu.h"
#include "utils.h"
#include "libft.h"

void    memory_init(t_memory *mem, void *ptr, size_t size)
{
	mem->memory = ptr;
	mem->memory_size = size;
}

void    memory_init_number(t_memory *mem, void *ptr, size_t size, uint64_t num)
{
	memory_init(mem, ptr, size);
	ft_memcpy(mem->memory, &num, ft_ullmin(mem->memory_size, sizeof(num)));
}

void    memory_memmove(t_memory *dst, t_memory *src)
{
	ft_memcpy(dst, src, dst->memory_size);
}

void    memory_and(t_memory *dst, t_memory *param1, t_memory *param2)
{
	size_t i;
	size_t size;

	size = ft_ullmin(param1->memory_size, param2->memory_size);
	size = ft_ullmin(size, dst->memory_size);
	i = 0;
	while (i < size)
	{
		as_byte(dst->memory)[i] = as_byte(param1->memory)[i] & as_byte(param2->memory)[i];
		++i;
	}
}

void    memory_or(t_memory *dst, t_memory *param1, t_memory *param2)
{
	size_t i;
	size_t size;

	size = ft_ullmin(param1->memory_size, param2->memory_size);
	size = ft_ullmin(size, dst->memory_size);
	i = 0;
	while (i < size)
	{
		as_byte(dst->memory)[i] = as_byte(param1->memory)[i] | as_byte(param2->memory)[i];
		++i;
	}
}

void    memory_xor(t_memory *dst, t_memory *param1, t_memory *param2)
{
	size_t i;
	size_t size;

	size = ft_ullmin(param1->memory_size, param2->memory_size);
	size = ft_ullmin(size, dst->memory_size);
	i = 0;
	while (i < size)
	{
		as_byte(dst->memory)[i] = as_byte(param1->memory)[i] ^ as_byte(param2->memory)[i];
		++i;
	}
}

void    memory_add(t_memory *dst, t_memory *param1, t_memory *param2)
{
	//смакотелик
}

void    memory_subtract(t_memory *dst, t_memory *param1, t_memory *param2)
{
	//смакотелик
}

void    memory_xprintf(t_memory *mem)
{
	size_t i;

	i = 0;
	while (i < mem->memory_size)
	{
		ft_printf("%x", as_byte(mem->memory)[i]);
		++i;
	}
}
