/*
 * bmptobin converts a bmp file to a pmode4 bin file for a CoCo
 * Copyright (C) 2021  Barry Nelson <barry.nelson@amobiledevice.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#define part1size 17413
#define part2size 9211
 
int main(int argc, const char *argv[]) {
    char part1[part1size];
    char part2[part2size];
    char image[6144];

    if (argc==3) {
	int fdrom=0;
	int fdimg=0;
	fdrom=open(argv[1], O_RDONLY);
	if (fdrom<=0) {
	    fprintf(stderr,"Can't read \"%s\"!\n",argv[1]);
	    exit(1);
	}
	fdimg=open(argv[2], O_RDONLY);
	if (fdimg<=0) {
	    fprintf(stderr,"Can't read \"%s\"!\n",argv[2]);
	    exit(1);
	}
	if (read(fdrom, part1, part1size)!=part1size) {
	    fprintf(stderr,"Can't read part1 of ROM image from \"%s\"!\n",argv[1]);
	    exit(1);
	}
	if (read(fdrom, image, 6144)!=6144) {
	    fprintf(stderr,"Can't read old image from ROM image \"%s\"!\n",argv[1]);
	    exit(1);
	}
	if (read(fdrom, part2, part2size)!=part2size) {
	    fprintf(stderr,"Can't read part2 of ROM image from \"%s\"!\n",argv[1]);
	    exit(1);
	}
	if (read(fdimg, image, 6144)!=6144) {
	    fprintf(stderr,"Can't read new image from \"%s\"!\n",argv[1]);
	    exit(1);
	}
	close(fdrom);
	close(fdimg);
	write(1, part1, part1size);
	write(1, image, 6144);
	write(1, part2, part2size);
    } else {
        fprintf(stderr,"Incorrect command line.\nUsage: replacepic rom_file raw_image_file >output.rom\n");
        fprintf(stderr,"\n       This utility outputs a new CoCo 3 ROM, replacing the CTRL-ALT image.\n");
	exit(1);
    }
    exit(0);
}
