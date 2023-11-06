#!/bin/bash

# Path to the original folder AKA the folder of your 42 work
path_42="/path/to/42/git"

# Get the current date
current_date=$(date +"%d/%m/%Y %H:%M")

# Path to backup folder AKA your personal git
path_personal="/path/to/personal/git"

# Custom message for the commit
custom_message="Cron Automatic Backup - $current_date"

# Copy everything from path_42 to path_personal
/usr/bin/rsync -av --exclude='.*' $path_42 $path_personal

# Go to path_personal, add everything, commit with a custom message & push
cd $path_personal && git add . && git commit -m "$custom_message" && git push
