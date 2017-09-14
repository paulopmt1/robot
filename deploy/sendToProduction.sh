printf "\nEnviando para produçao...\n"
cd /var/www/html/robot

rsync -avz /var/www/html/robot/ servidorpessoal:/var/www/html/robot/

printf "\n\n\nEnviado com sucesso!\n\n"