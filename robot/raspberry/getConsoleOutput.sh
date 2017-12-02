printf "\nVisualizando output do processo\n"

strace -ewrite -p `cat /var/www/html/robot/robot/robot.pid`