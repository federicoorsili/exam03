#include <stdio.h>
#include <math.h>
#include <unistd.h>

typedef struct s_data
{
	char		type;
	float		x;
	float		y;
	float		raggio;
	char		carattere;
}				t_data;

typedef struct s_info
{
	int			width;
	int			height;
	char		background;
}				t_info;

int		take_info(t_info *info, char matrix[305][305], FILE *fd)
{
	int i = 0;
	int k = 0;

	if (fscanf(fd, "%d %d %c\n", &info->width, &info->height, &info->background) == 3)
	{
		if (info->width < 0 || info->width > 300 || info->height < 0 || info->height >300)
			return (1);
		i = 0;
		while (i < info->height)
		{
			k =0;
			while (k < info->width)
			{
				matrix[i][k] = info->background;
				k++;
			}
			i++;
		}
		return (0);
	}
	return (1);
}

void	print_matrix(t_info *info, char matrix[305][305])
{
	int i = 0;
	int k = 0;
	while (i < info->height)
	{
		k = 0;
		while (k < info->width)
		{
			write(1, &matrix[i][k], 1);
			k++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	draw_matrix(t_info *info, t_data *data, char matrix[305][305])
{
	int y = 0;
	int x = 0;
	float	dist = 0;

	while (y < info->height)
	{
		x  = 0;
		while (x < info->width)
		{
			dist = sqrtf((x - data->x) * (x - data->x) + (y - data->y) * (y - data->y)) - data->raggio;
			if (dist <= 0.00000000 && dist > -1.0000000)
				matrix[y][x] = data->carattere;
			if (data->type == 'C' && dist <= -1.00000000)
			{
				if ((sqrtf((x - data->x) * (x - data->x) + (y - data->y) * (y - data->y))) <= data->raggio)
				matrix[y][x] = data->carattere;
			}
			x++;
		}
		y++;
	}
	
}

int		exec(char **argv, char matrix[305][305], t_data *data, t_info *info)
{
	FILE *fd;
	int  res;

	fd = fopen(argv[1], "r");
	if (!fd)
		return (1);
	if (take_info(info, matrix, fd))
	{
		return (1);
	}
	res = fscanf(fd, "%c %f %f %f %c\n", &data->type, &data->x, &data->y,
		&data->raggio, &data->carattere);
	while (res == 5)
	{
		if ((data->type != 'c' && data->type != 'C') || data->raggio < 0.0000000)
		{
			return (1);
		}
		draw_matrix(info, data, matrix);
		res = fscanf(fd, "%c %f %f %f %c\n", &data->type, &data->x, &data->y,
		&data->raggio, &data->carattere);
	}
	printf("%d\n", res);
	if (res == -1)
	{
		print_matrix(info, matrix);
		return (0);
	}
	return (1);
}

int main(int argc, char **argv)
{
	char matrix[305][305];
	t_data data;
	t_info info;

	if (argc != 2)
	{
		write(1, "Error: argument\n", 18);
		return (1);
	}
	if (exec(argv, matrix, &data, &info))
	{
		write(1, "Error: Operation file corrupted\n", 38);
		return (1);
	}
	return (0);
}