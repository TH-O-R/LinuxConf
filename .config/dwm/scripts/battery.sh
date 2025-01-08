#!/bin/bash
# battery.sh - A simple status script for dwm

# Battery status
battery=$(cat /sys/class/power_supply/BAT0/capacity)
charging_status=$(cat /sys/class/power_supply/BAT0/status)

echo " [$charging_status $battery%]"
