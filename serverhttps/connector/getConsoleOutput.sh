printf "\nVisualizando output do processo\n"

strace -ewrite -p `cat /var/www/html/robot/serverhttps/connector/connector.pid`
~                                                                                                    
