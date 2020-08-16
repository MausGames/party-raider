#!/bin/bash
cd bin/linux/x64

# set library path
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH

# start game
if type gamemoderun &> /dev/null; then
    gamemoderun ./PartyRaider.elf "$@"
else
    ./PartyRaider.elf "$@"
fi