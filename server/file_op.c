/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_op.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asarandi <asarandi@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 19:05:13 by asarandi          #+#    #+#             */
/*   Updated: 2018/05/23 19:05:26 by asarandi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

ssize_t file_get_size(char *filename) {
    int fd;
    ssize_t size;

    if ((fd = open(filename, O_RDONLY)) == -1)
        return (-1);
    size = lseek(fd, 0, SEEK_END);
    close(fd);
    return (size);
}
