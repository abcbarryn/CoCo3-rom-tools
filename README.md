# CoCo3-rom-tools
Tools for customizing a CoCo 3 ROM image

You will need a dump of the CoCo 3 rom to use most of these tools.
The script radioshack.sh will make an file named custom.rom that will display a
blue and red Radio Shack logo when you press CTRL-ALT-reset.

Usage: bmptobin bmp_file [CoCo_bin_file_load_address | raw] >output.bin

       This utility can only convert 256x192 2 color (B&W) BMP images.
       The second argument is an optional load address with a default of 3584.
       Specifying the word raw for the load address results in a raw binary
       file with no CoCo header or trailer.

Usage: replacepic rom_file raw_image_file >output.rom

       This utility outputs a new CoCo 3 ROM, replacing the CTRL-ALT image.

Usage: changbyte file offset bytevalue

       This utility changes a single byte in a file.
       Please note the first character is position zero, not one.

This is the position and default value of the bytes that set the foreground and
background color of the CTRL-ALT-reset screen.

C1FA,offset 16890 decimal 41FA hex=palette 10 value of $09, dark blue foreground

C1FF,offset 16895 decimal 41FF hex=palette 11 value of $3F, white background
