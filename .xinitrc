export PATH="$HOME/.local/bin:$PATH"
xrandr --output HDMI-A-0 --mode 1920x1080 --rate 100
xrandr --output DisplayPort-0 --off #--mode 1440x900 --rate 74.98 --left-of HDMI-A-0
xrdb -merge ~/.Xresources
xset r rate 300 50
setxkbmap -layout "us,ru" -option "grp:caps_toggle" & #grp:caps_toggle,grp_led:caps
slstatus &
xsetroot -solid "#282828"
#redshift -l 50.454009:30.619396 &
firefox &
#Telegram &
exec dwm

#############UNUSED

#feh --bg-scale /home/terson/Pictures/desk.png
#clipmenud &
