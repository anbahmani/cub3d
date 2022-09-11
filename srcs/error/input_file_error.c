/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_file_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahmani <abahmani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 17:58:53 by abahmani          #+#    #+#             */
/*   Updated: 2022/09/11 17:59:13 by abahmani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_input_file_name(char const *file_name)
{
	unsigned int	len;

	len = (int)ft_strlen(file_name);
	if (len < 5)
		return (0);
	if (file_name[len - 1] != 'b'
		|| file_name[len - 2] != 'u'
		|| file_name[len - 3] != 'c'
		|| file_name[len - 4] != '.'
		|| file_name[len - 5] == '/')
		return (0);
	return (1);
}

static int	check_input_file_existing(char const *file_name)
{
	int	fd;

	fd = open((char *)file_name, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

static int	check_input_not_directory(char const *file_name)
{
	int	fd;

	fd = open((char *)file_name, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (0);
	}
	return (1);
}

static int	check_input_not_symbolic_link(char const *file_name)
{
	int	fd;

	fd = open((char *)file_name, O_NOFOLLOW);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
}

int	check_input_file_error(char const *file_name)
{
	if (!check_input_file_name(file_name))
	{
		print_error("Le nom du fichier est incorrecte.");
		return (0);
	}
	if (!check_input_file_existing(file_name))
	{
		print_error("Le fichier entré est inexistant.\n");
		return (0);
	}
	if (!check_input_not_directory(file_name))
	{
		print_error("Le fichier entré est un dossier.");
		return (0);
	}
	if (!check_input_not_symbolic_link(file_name))
	{
		print_error("Le fichier entré est un lien symbolique.");
		return (0);
	}
	return (1);
}
