# Valida se esta dentro da pasta do projeto
insideWorkTree="$(git rev-parse --is-inside-work-tree)"
if [ ! "$insideWorkTree" ]; then
        printf "\nNao estamos dentro da arvore de trabalho! Saindo...\n"
        exit 1
fi

# Baixa as novidades do github fofoqueiro que fica cuidando a vida dos outros...
/usr/bin/git -c core.askpass=true fetch --tags --progress git@github.com:paulopmt1/robot.git +refs/heads/*:refs/remotes/origin/*

# Faz checkout para a ultima versao
commit="$(/usr/bin/git rev-parse refs/remotes/origin/master^{commit})"
printf "\nEfetuando checkout para o commit mais recente em master: $commit\n"
/usr/bin/git checkout -f "$commit"

#/usr/bin/git checkout -f master
#/usr/bin/git pull

cd /var/www/html/robot
cp robot.ino /home/pi/arduino-testes/Arduino-Makefile/examples/Blink/
cd /home/pi/arduino-testes/Arduino-Makefile/examples/Blink/
make && avrdude -p m2560 -c wiring -P /dev/ttyACM0 -b 115200 -F -U flash:w:build-mega2560/Blink.hex
