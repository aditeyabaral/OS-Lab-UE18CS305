#!/bin/sh
# Script to print user information who currently login, current date & time
# Enter the following commands in a file
echo "Hello $USER"
echo "Today is ";date
echo "Number of user login : " ; who | wc -l
echo "Calendar"
cal
exit 0
