#!/bin/sh

# test to see how to use pacman without password

sync()
{
  echo "updating"
  pacman -Sy
}

hello="$1"

echo hello
sync
