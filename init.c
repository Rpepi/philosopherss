/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:56:06 by rpepi             #+#    #+#             */
/*   Updated: 2024/05/28 11:56:08 by rpepi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_init_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal = 0;
		data->philos[i].data = data;
		data->philos[i].nb_meals_eated = 0;
		data->philos[i].l_fork_id = i;
		data->philos[i].r_fork_id = (i + 1) % data->nb_philos;
		i++;
	}
	return (0);
}

static int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i >= data->nb_philos)
	{
		if (pthread_mutex_init(&(data->fork_mutex[i]), NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&(data->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(data->meals_mutex), NULL))
		return (1);
	return (0);
}

int	ft_init_all(t_data *data, char **argv)
{
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		data->nb_meals = ft_atoi(argv[5]);
		if (data->nb_meals <= 0)
			return (1);
	}
	else
		data->nb_meals = -1;
	data->one_is_dead = 0;
	if (init_mutex(data) == 1)
		return (1);
	if (ft_init_philos(data) == 1)
		return (1);
	return (0);
}
