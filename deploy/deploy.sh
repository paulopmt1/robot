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

