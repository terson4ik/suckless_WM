#!/bin/bash
cat readme.md
echo 'PLEASE, DEFINE LAPTOP IF YOU NEED THEM!!!'
sleep 1.5
for dir in */; do
    cd "$dir" || { echo 'PIZDEC';exit 100; }
    sudo make install clean || { echo 'PIZDEC NAHUY'; exit 111; }
    cd ..
done;
    mv .xinitrc ~/.xinitrc
    mv .Xresources ~/.Xresources
echo 'ready.'
echo 'mkdir -p ~/Pictures/Screenshots'
mkdir -p ~/Pictures/Screenshots
echo "mkdir ~/.local/bin/"
mkdir ~/.local/bin/
mv extra_scripts/* ~/.local/bin/
echo 'if you need, please, compile the "bell.c" and add prog in you PATH.'
echo 'run:'
echo 'gcc bell.c -o bell'
echo 'mv bell ~/.local/bin/'
