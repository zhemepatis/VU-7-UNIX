#!/bin/sh

echo "Most frequently used words:"

tr -d "[:punct:]" | tr -s "[:space:]" | tr "[:space:]" "\n" |
    sort | uniq -ci | sort -nr | head -n 5
