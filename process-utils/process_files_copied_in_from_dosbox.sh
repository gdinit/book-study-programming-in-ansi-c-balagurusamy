#!/bin/bash
# convert all files to all-chars-in-lowercase format
rename -f 'y/A-Z/a-z/' *
# delete unnecessary stuff (*.obj *.dsk etc.)
../process-utils/make_clean.sh
#EOF
