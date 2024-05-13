/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pepi <pepi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:13:25 by pepi              #+#    #+#             */
/*   Updated: 2024/05/13 10:40:26 by pepi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_if_num(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

static int	check_args(char **argv)
{
	if (ft_atoi(argv[1]) > PHILO_MAX || ft_atoi(argv[1]) <= 0
		|| check_if_num(argv[1]) == 1)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ft_atoi(argv[2]) <= 0 || check_if_num(argv[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(argv[3]) <= 0 || check_if_num(argv[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(argv[4]) <= 0 || check_if_num(argv[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_if_num(argv[5]) == 1))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
	return (0);
}


int main(int argc, char **argv)
{
    t_data  data;
	
   if (argc != 5 && argc != 6)
		return (write(2, "ERROR : invalid number of arguments", 36), 1);
	if (check_args(argv) == 1)
	{
		write(1, "fuck this shit", 15);
		return (1);
	}
    if (ft_init_all(&data, argv))
		return (1);
	if (create_threads(&data))
			return (1);
    return (0);
}
