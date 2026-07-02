#include <stdio.h>

int	calculate_removals(char *str)
{
	int	open_count;
	int	close_count;
	int	i;

	open_count = 0;
	close_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '(')
			open_count++;
		else if (str[i] == ')')
		{
			if (open_count > 0)
				open_count--;
			else
				close_count++;
		}
		i++;
	}
	return (open_count + close_count);
}

void	solve(char *str, int min_removals, int current_removals, int position)
{
	int	i;
	int	saved_char;

	if (min_removals == current_removals && !calculate_removals(str))
	{
		puts(str);
		return ;
	}
	i = position;
	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')')
		{
			saved_char = str[i];
			str[i] = ' ';
			solve(str, min_removals, current_removals + 1, i);
			str[i] = saved_char;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	int	min_removals;

	if (ac == 2)
	{
		min_removals = calculate_removals(av[1]);
		solve(av[1], min_removals, 0, 0);
	}
	return (0);
}

