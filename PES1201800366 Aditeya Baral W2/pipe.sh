#!/bin/sh
ls | more
who | sort
who | sort > user_list.txt
who | wc -l 
ls -l | wc -l  
who | grep aditeya