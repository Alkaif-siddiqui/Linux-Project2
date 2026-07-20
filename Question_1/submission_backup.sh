#!/bin/bash

# Directories
Source_Dir="submissions"
Backu_Dir="backup"

# Files
Report_File="report.txt"
Error_Log="errors.log"

# Count
processed=0
duplicates=0
backedup=0

# Create backup directory
mkdir -p "$Backup_Dir" 2>>"$Error_Log"

# Process files
for file in "$Source_Dir"/*; do
    if [ -f "$file" ]; then
        processed=$((processed + 1))

        filename=$(basename "$file")

        if [ -f "$Backup_Dir/$filename" ] && cmp -s "$file" "$Backup_Dir/$filename"; then
            duplicates=$((duplicates + 1))
        else
            cp "$file" "$Backup_Dir/" 2>>"$Error_Log"
            backedup=$((backedup + 1))
        fi
    fi
done

# Write the report
echo "===== Report =====" > "$Report_File"
echo "Files Processed : $processed" >> "$Report_File"
echo "Duplicate Files : $duplicates" >> "$Report_File"
echo "Files Backed Up : $backedup" >> "$Report_File"
echo "Task Completed."

