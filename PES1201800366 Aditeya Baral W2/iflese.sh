#!/bin/sh
osch=0

echo "1. Unix (Sun OS)"
echo "2. Linux (Red Hat)"
echo -n "Select your os choice [1 or 2]? "
read osch

if [ $osch -eq 1 ]
then
    echo "You selected Unix (Sun OS)"

else
    if [ $osch -eq 2 ]
    then
        echo "You selected Linux (Red Hat)"
    else
        echo "You don't like Unix/Linux OS."
    fi
fi