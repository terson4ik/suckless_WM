#!/bin/bash
cat readme.md
echo 'PLEASE, DEFINE LAPTOP IF YOU NEED THEM!!!'
sleep 1
for dir in dwm* dmen* slstat*; do
    cd "$dir" || { echo 'PIZDEC';exit 100; }
    sudo make install clean || { echo 'PIZDEC NAHUY'; exit 111; }
    cd ..
done;
echo 'ready.'
echo 'mkdir -p ~/Pictures/Screenshots'
mkdir -p ~/Pictures/Screenshots
echo "mkdir ~/.local/bin/"
mkdir ~/.local/bin/
mv extra_scripts/* ~/.local/bin/
echo "we added some scripts in ~/.local/bin/"
echo "well, setting your PATH please"
echo 'if you need, please, compile the "bell.c" and add prog in you PATH.'
echo 'run:'
echo 'gcc bell.c -o bell'
echo 'mv bell ~/.local/bin/'
