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
#include <sys/stat.h>
 
int main(int argc, const char *argv[]) {
    char byte[1];
    off_t offset=0L;

    if (argc==4) {
	struct stat st;
	stat(argv[1], &st);
	int fd=0;
	fd=open(argv[1], O_RDWR);
	if (fd<=0) {
	    fprintf(stderr,"Can't read \"%s\"!\n",argv[1]);
	    exit(1);
	}
	offset=atol(argv[2]);
	if (offset>=st.st_size) {
	    fprintf(stderr,"Can't seek to position %lld in file \"%s\"!\n",offset,argv[1]);
	    exit(1);
	}
	if (lseek(fd,offset,SEEK_SET)!=offset) {
	    fprintf(stderr,"Can't seek to position %lld in file \"%s\"!\n",offset,argv[1]);
	    exit(1);
	}
	byte[0]=atoi(argv[3]);
	write(fd, byte, 1);
	close(fd);
    } else {
        fprintf(stderr,"Incorrect command line.\nUsage: changbyte file offset bytevalue\n");
        fprintf(stderr,"\n       This utility changes a single byte in a file.\n");
        fprintf(stderr,"       Please note the first character is position zero, not one.\n");
	exit(1);
    }
    exit(0);
}
