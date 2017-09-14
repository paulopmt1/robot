printf "\n\nConectando no robo...\n"
cd /var/www/html/robot

rsync -avz /var/www/html/robot/ robot:/var/www/html/robot/

printf "\n\n\nEnviado com sucesso!\n\n"