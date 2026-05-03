#!/bin/bash
for dir in */; do
    cd "$dir" || { echo 'PIZDEC';exit 100; }
    sudo make install clean || { echo 'PIZDEC NAHUY'; exit 111; }
    cd ..
done;
    mv .xinitrc ~/.xinitrc
    mv .Xresources ~/.Xresources
echo 'ready.'
