/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpepi <rpepi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 11:55:51 by rpepi             #+#    #+#             */
/*   Updated: 2024/06/14 16:09:31 by rpepi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	message(char *str, t_data *data, int philo_id)
{
	pthread_mutex_lock(&(data->writing));
	if (!data->one_is_dead && !data->all_have_eat)
	{
		printf("%lli ", curr_time() - data->starting_time);
		printf("%i ", philo_id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(data->writing));
	return ;
}

void	sleeping(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	message("is sleeping", data, philo->id);
	ft_sleep(philo->data->time_to_sleep, data);
}

void	eating(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&(data->fork_mutex[philo->l_fork_id]));
	message("has taken a fork", data, philo->id);
	if (data->nb_philos == 1)
	{
		ft_sleep(200, data);
		message("has died", data, philo->id);
		data->one_is_dead = 1;
		return ;
	}
	pthread_mutex_lock(&(data->fork_mutex[philo->r_fork_id]));
	message("has taken a fork", data, philo->id);
	pthread_mutex_lock(&(data->meals_mutex));
	message("is eating", data, philo->id);
	philo->last_meal = curr_time();
	pthread_mutex_unlock(&(data->meals_mutex));
	ft_sleep(data->time_to_eat, data);
	philo->nb_meals_eated++;
	pthread_mutex_unlock(&(data->fork_mutex[philo->l_fork_id]));
	pthread_mutex_unlock(&(data->fork_mutex[philo->r_fork_id]));
}
