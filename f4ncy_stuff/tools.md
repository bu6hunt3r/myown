# Tools
## Vboxmanage bash autocompletion

1. Set up bash completion
```
    autoload -U +X compinit && compinit
    autoload -U +X bashcompinit && bashcompinit
```
2. Grab script
 [Vboxmanage](https://raw.githubusercontent.com/gryf/vboxmanage-bash-completion/master/VBoxManage
 )
2. Script to folder of choice and source in ~/.zshrc
```
source /home/cr0c0/.completions/VBoxManage
```