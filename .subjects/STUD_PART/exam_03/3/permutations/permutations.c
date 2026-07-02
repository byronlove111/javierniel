#include <unistd.h>
#include <stdlib.h>

static char	used[26];
static char	result[26];
static int	len;

static void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

static void	sort_string(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	while (i < len - 1)
	{
		j = i + 1;
		while (j < len)
		{
			if (str[i] > str[j])
			{
				tmp = str[i];
				str[i] = str[j];
				str[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	generate(int pos, char *str)
{
	int	i;

	if (pos == len)
	{
		result[pos] = '\0';
		ft_putstr(result);
		return ;
	}
	
	i = 0;
	while (i < len)
	{
		if (used[i] == 0)
		{
			used[i] = 1;
			result[pos] = str[i];
			generate(pos + 1, str);
			used[i] = 0;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (1);

	len = 0;
	while (av[1][len])
		len++;

	if (len == 0)
		return (1);

	sort_string(av[1]);
	generate(0, av[1]);
	
	return (0);
}

