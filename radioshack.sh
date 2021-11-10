#!/bin/sh

./bmptobin radioshk.bmp raw >radioshk.raw
./replacepic coco3.rom radioshk.raw >custom.rom
./changebyte custom.rom 16890 38
./changebyte custom.rom 16895 9
