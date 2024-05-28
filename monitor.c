/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:56:14 by rpepi             #+#    #+#             */
/*   Updated: 2024/05/28 14:14:30 by rpepi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long long	find_time(t_philo *philo, int i)
{
	return (time_diff(philo[i].last_meal, get_current_time()));
}

void	dead_check(t_data *data, t_philo *philo)
{
	int	i;

	while (!(data->all_have_eat))
	{
		i = -1;
		while (++i < data->nb_philos && !(data->one_is_dead))
		{
			pthread_mutex_lock(&(data->meals_mutex));
			if (find_time(philo, i) > data->time_to_die)
			{
				message("died", philo);
				data->one_is_dead = 1;
			}
			pthread_mutex_unlock(&(data->meals_mutex));
			ft_sleep(1, data);
		}
		if (data->one_is_dead)
			break ;
		i = 0;
		while (data->nb_meals != -1 && i < data->nb_philos
			&& philo[i].nb_meals_eated >= data->nb_meals)
			i++;
		if (i == data->nb_philos)
			data->all_have_eat = 1;
	}
}

void	exit_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->nb_philos)
		pthread_join(philos[i].thread, NULL);
	i = -1;
	while (++i < data->nb_philos)
		pthread_mutex_destroy(&(data->fork_mutex[i]));
	pthread_mutex_destroy(&(data->writing));
}
