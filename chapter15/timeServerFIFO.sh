#########################################################################
# File Name: timeServerFIFO.sh
# Author: ma6174
# mail: ma6174@163.com
# Created Time: Sun Mar  5 13:23:20 2017
#########################################################################
#!/bin/bash
while true; do
	if [ ! -f "/tmp/time_fifo" ]; then
		rm -f /tmp/time_fifo
fi
	mkfifo /tmp/time_fifo
	date > /tmp/time_fifo
done

