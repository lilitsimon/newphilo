/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisimony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:09:21 by lisimony          #+#    #+#             */
/*   Updated: 2024/10/15 16:09:25 by lisimony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	data_init(t_data *data, t_philo *philos, pthread_mutex_t *forks,
		char **argv)
{
	data->philos = philos;
	data->dead_flag = 0;
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->write_lock);
		return (0);
	}
	if (pthread_mutex_init(&data->meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&data->write_lock);
		pthread_mutex_destroy(&data->dead_lock);
		return (0);
	}
	if (!fork_init(forks, ft_atol(argv[1])))
		return (0);
	return (philo_init(philos, data, forks, argv));
}

int	fork_init(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&forks[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	philo_init(t_philo *philos, t_data *data, pthread_mutex_t *forks,
		char **argv)
{
	int	i;
	int	num_philos;

	num_philos = ft_atol(argv[1]);
	i = 0;
	while (i < num_philos)
	{
		philos[i].id = i + 1;
		if (!input_init(&philos[i], argv))
			return (0);
		philos[i].last_meal = get_time();
		philos[i].start_time = get_time();
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		philos[i].write_lock = &data->write_lock;
		philos[i].dead_lock = &data->dead_lock;
		philos[i].meal_lock = &data->meal_lock;
		philos[i].dead = &data->dead_flag;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % num_philos];
		i++;
	}
	return (1);
}

int	input_init(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_atol(argv[2]);
	philo->time_to_eat = ft_atol(argv[3]);
	philo->time_to_sleep = ft_atol(argv[4]);
	philo->num_philos = ft_atol(argv[1]);
	if (argv[5])
		philo->must_eat_count = ft_atol(argv[5]);
	else
		philo->must_eat_count = -1;
	return (1);
}