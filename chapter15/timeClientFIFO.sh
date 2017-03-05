#########################################################################
# File Name: timeClientFIFO.sh
# Author: ma6174
# mail: ma6174@163.com
# Created Time: Sun Mar  5 13:25:05 2017
#########################################################################
#!/bin/bash
while true; do
	cat /tmp/time_fifo
	sleep 1
done
