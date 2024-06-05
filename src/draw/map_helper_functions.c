#include "../../include/cub3d.h" 

void	print2d_array(t_parsing *data)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (data->map_flood[j])
	{
		i = 0;
		while (data->map_flood[j][i])
		{
			i++;
		}
		j++;
	}
}

int	set_value(char value, t_parsing *data, int y, int x)
{
	if (value == '1')
		return (1);
	else if (value == '0')
		return (0);
	else if (value == '\n')
		return (2);
	else if (value == 'N' || value == 'E' || value == 'S' || value == 'W')
	{
		data->player_direction = value;
		data->player_position[0] = y;
		data->player_position[1] = x;
		if (data->map_flood[y][x - 1] == 1 || data->map_flood[y - 1][x
			- 1] == 1)
		{
			data->player_position[1] = x + 1;
			data->player_position[0] = y + 1;
		}
		return (0);
	}
	else
		return (2);
}