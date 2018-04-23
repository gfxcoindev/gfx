#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/graphicscoin.ico

convert ../../src/qt/res/icons/graphicscoin-16.png ../../src/qt/res/icons/graphicscoin-32.png ../../src/qt/res/icons/graphicscoin-48.png ${ICON_DST}
