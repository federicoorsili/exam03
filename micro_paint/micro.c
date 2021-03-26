#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>

typedef struct	s_info
{
	int			width;
	int			height;
	char		background;
}				t_info;

typedef	struct	s_data
{
	char		type;
	float		x;
	float		y;
	float		width;
	float		height;
	char		carattere;

}				t_data;



int		ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int		take_info(t_info *info, FILE *fd, char matrix[305][305])
{
	int i = 0;
	int k = 0;
	int ret;

	ret = fscanf(fd, "%d %d %c\n", &info->width, &info->height, &info->background);
	if (ret == 3)
	{
		if (info->width > 300 || info->width < 0 || info->height >300 || info->height < 0)
			return (1);
		while (i < info->height)
		{
			k = 0;
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

void	draw(char matrix[305][305], t_data *data, t_info *info)
{
	float y = 0;
	float x = 0;

	while (y < info->height)
	{
		x = 0;
		while (x < info->width)
		{
			if ((y < data->y || y > data->height + data->y) || (x < data->x || x > data->width + data->x))
			{
				x += 1;
				continue;
			}
			if (((y - data->y) < 1.00000000 || ((data->y + data->height) - y) < 1.00000000))
				matrix[(int)y][(int)x] = data->carattere;
			if (((x - data->x) < 1.00000000 || ((data->x + data->width) - x) < 1.00000000))
				matrix[(int)y][(int)x] = data->carattere;
			if (data->type == 'R')
				matrix[(int)y][(int)x] = data->carattere;
			x += 1;
		}
		y += 1;	
	}
}

void	print_matrix(char matrix[305][305], t_info *info)
{
	float i = 0;
	float k = 0;

	while (i < info->height)
	{
		k = 0;
		while (k < info->width)
		{
			write(1, &matrix[(int)i][(int)k], 1);
			k++;
		}
		write(1, "\n", 1);
		i++;
	}
	
}

int		start(char **argv, char matrix[305][305], t_info *info, t_data *data)
{
	int res;
	FILE	*fd;


	res = 0;
	fd = fopen(argv[1], "r");
	if (!fd)
		return (1);
	res = (take_info(info, fd, matrix));
	if (res)
		return (1);
	res =fscanf(fd,"%c %f %f %f %f %c\n", &data->type, &data->x, &data->y,
	&data->width, &data->height, &data->carattere);
	while (res == 6)
	{
		if ((data->type != 'r' && data->type != 'R') || data->width < 0.00000000 || data->height < 0.00000000)
			return (1);
		draw(matrix, data, info);
		res =fscanf(fd,"%c %f %f %f %f %c\n", &data->type, &data->x, &data->y,
		&data->width, &data->height, &data->carattere);
	}
	if (res == -1)
	{
		print_matrix(matrix, info);
		return (0);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	char 	matrix[305][305];
	t_info info;
	t_data data;

	if (argc != 2)
	{
		write(0, "Error: argument\n", ft_strlen("Error: argument\n"));
		return (1);
	}
	//printf("ueua\n");
	if (start(argv, matrix, &info, &data))
	{
		write(0, "Error: Operation file corrupted\n", ft_strlen("Error: Operation file corrupted\n"));
		return (1);	
	}
	return (0);
}