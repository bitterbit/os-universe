#!/bin/bash

/mnt/sda/content_shell --no-sandbox $1 2>&1 | tee log.txt 
