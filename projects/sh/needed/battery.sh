#!/bin/bash
# battery.sh - A simple status script for dwm

# Battery status
battery=$(acpi -b | grep -oP '\d+%')
charging_status=$(acpi -b | grep -oP '(Charging|Discharging)')

echo " $charging_status > $battery % "
