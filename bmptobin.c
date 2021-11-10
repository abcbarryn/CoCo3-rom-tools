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
 
int main(int argc, const char *argv[]) {
    char line[192][32];
    char head[63];
    char bytes[5];
    int ln=0;

    if (argc > 1 && argc<4) {
	int fd=0;
	int loadaddress=0xe00;
	if (argc==3)
	    loadaddress=atoi(argv[2]);
	if (loadaddress==0 && strcmp(argv[2],"raw")!=0) {
	    fprintf(stderr,"Warning, %s is not a valid load address. Defaulting to 3584.\n",argv[2]);
	    loadaddress=0xe00;
	}
	fd=open(argv[1], O_RDONLY);
	if (fd<=0) {
	    fprintf(stderr,"Can't read \"%s\"!\n",argv[1]);
	    exit(1);
	}
	if (read(fd, head, 62)!=62) {
	    fprintf(stderr,"Can't read bmp header from \"%s\"!\n",argv[1]);
	    exit(1);
	}
	if (head[0]!='B' || head[1]!='M' ) {
	    fprintf(stderr,"\"%s\" is not a BMP image!\n",argv[1]);
	    exit(1);
	}
	if (head[19]!=(char) 1 || head[20]!=(char) 0 || head[21]!=(char) 0 || head[22]!=(char) 192) {
	    fprintf(stderr,"\"%s\" is not a 256x192 BMP image!\n",argv[1]);
	    exit(1);
	}
	for (ln=191 ; ln>-1 ; ln--) {
	    if (read(fd, line[ln], 32)!=32) {
		fprintf(stderr,"Error reading bmp data from \"%s\"!\n",argv[1]);
		exit(1);
	    }
	}
	close(fd);
	if (loadaddress!=0) {
	    bytes[0]=0x00;
            bytes[1]=0x18;
	    bytes[2]=0x00;
	    bytes[3]=floor(loadaddress/256);
	    bytes[4]=loadaddress-256*bytes[3];
	    write(1, bytes, 5);
	}
	for (ln=0 ; ln<192 ; ln++) {
	    write(1, line[ln], 32);
	}
	if (loadaddress!=0) {
	    bytes[0]=0xff;
            bytes[1]=0x00;
	    bytes[2]=0x00;
	    bytes[3]=0x00;
	    bytes[4]=0x00;
	    write(1, bytes, 5);
	}
    } else {
        fprintf(stderr,"Incorrect command line.\nUsage: bmptobin bmp_file [CoCo_bin_file_load_address | raw] >output.bin\n");
        fprintf(stderr,"\n       This utility can only convert 256x192 2 color (B&W) BMP images.\n");
        fprintf(stderr,"       The second argument is an optional load address with a default of 3584.\n");
        fprintf(stderr,"       Specifying the word raw for the load address results in a raw binary\n");
        fprintf(stderr,"       file with no CoCo header or trailer.\n");
	exit(1);
    }
    exit(0);
}
