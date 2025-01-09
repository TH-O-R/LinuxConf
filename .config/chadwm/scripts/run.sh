#!/bin/sh

xrdb merge ~/.Xresources
feh --bg-fill /home/akuma/.config/hypr/bg/minimal.png &
picom -b --config ~/.config/chadwm/chadwm/picom.conf &

bash ~/.config/chadwm/scripts/bar.sh &
run "nm-applet"
run "pamac-tray"
run "xfce4-power-manager"
run "/usr/lib/xfce4/notifyd/xfce4-notifyd"

while type chadwm >/dev/null; do chadwm && continue || break; done
