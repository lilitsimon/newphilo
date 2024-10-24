/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lisimony <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:10:27 by lisimony          #+#    #+#             */
/*   Updated: 2024/10/15 15:10:28 by lisimony         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (((*str == ' ') || (*str >= 9 && *str <= 13)))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_usleep(long long milliseconds)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	one_philo(t_data *data)
{
	t_philo	*philo;

	philo = &data->philos[0];
	print_status("has taken a fork", philo, philo->id);
	ft_usleep(philo->time_to_die);
	print_status("died", philo, philo->id);
	pthread_mutex_lock(philo->dead_lock);
	*philo->dead = 1;
	pthread_mutex_unlock(philo->dead_lock);
}
