#!/bin/bash

/mnt/sda/content_shell --single-process --ozone-platform=gbm --no-sandbox $1 2>&1 | tee log.txt 
