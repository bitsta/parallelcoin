#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/pocketchange.png
ICON_DST=../../src/qt/res/icons/pocketchange.ico
convert ${ICON_SRC} -resize 16x16 pocketchange-16.png
convert ${ICON_SRC} -resize 32x32 pocketchange-32.png
convert ${ICON_SRC} -resize 48x48 pocketchange-48.png
convert pocketchange-16.png pocketchange-32.png pocketchange-48.png ${ICON_DST}

