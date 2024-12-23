#!/bin/sh

# get the number of updates using checkupdates command
  
  outdated_count=$(checkupdates | wc -l)

# set a color based on how many updates there is

  if [ "$outdated_count" -lt 3 ]; then
    color="#00FF00" #green
    icon=" " #no-problemo
  elif [ "$outdated_count" -lt 10 ]; then
    color="#FFA500" #orange
    icon=" " #jme3 rask achrif
  else
    color="#FF0000" #$RED
    icon=" " #oh-oh
  fi

#output the result in a good format
echo "{$icon $outdated_count updates}"
