
## POR HACER
- [ ] Revisar export a="algo=k", Se divide en 2
  COMPROBAR COMILLAS, SIMPLES O DOBLES, CERRADAS!
a=
algo=k
cuando debería ser a=algo=k

- [X] ls / /home
- [X] cd ~/.cd42/ Con ruta relativa
- [ ] ARREGLAR Ctr +D
- [ ] EJECUTAR MINISHELL DENTRO DE MINISHELL Y ACTUALIZAR SHLVL=1
- [ ] Revisar el ft_strconcat y ft_strdup (Problemas con el prompt)
- [ ] ls -la >> apen3.txt >> apen4.txt



remove ft_isallalpha.c ??? --> usar en export ex: export a=">>"

## ERRORES
- [X] valgrind en echo heredoc (revisar ft_strjoin)
- [ ] Después de hacer un echo y presionar (flecha abajo) en el historial, se queda estatico echo
- [X] valgrind export algo=a""sd

## COSAS QUE NO ES NECESARIO HACER
- [-] cd - se interpreta como cd sin nada NO ES NECESARIO?, solo rutas

## PROBAR
- [ ] BUSCAR LA GUIA DE CORRECCIÓN Y PROBAR
- [ ] COMPROBAR QUE NO SE USAN FUNCIONES PROHIBIDAS
- [ ] Quitar posibles comentarios y debug code antes de entrega, NORMA



cat | cat | ls
ls | wc

<< eof | cat, cat | cat | ls
echo -nnnnnnnnn -n -nnnnnm
|
ls | | wc

ls |;
ls |&
$_
echo $TEST > $TEST
unset PWD
cd ... x 8
ls /*/
export a="ls -la"
$a
l's'
export a =asd
export a="algo=k"
ls > a | echo >> a > b | wc a | wc b
unset HOME && cd ~
export a='algo"algo'
echo "$a"
avoid awk
export a=">>"
ls $a algo
exit 4 y fuera de las shell echo $?
exit a1
exit 1a
<< ola | grep 42 | cat
export a="ls -la"
"$a"
ls | exit | wc
qué output se espera en minishell de ls |;  y de ls |& ?
<<< ,  <<<< , |||
<<<, <<<<, >>, >>>>, > $Expansion y no existe la variable en si, 1234>1, < >,

echo $P$P$P$PWD
echo $HOME$HOME$HOME$HOME
echo "$"HOME
echo "$HO"ME
echo $HOME"$HOME"$HOME
echo $$
echo $""HOME
echo "''$PWD'''qwere"qwqwer$P$P$PWD"'$PWD'"

## COSAS
norminette -R CheckForbiddenSourceHeader **/*.c **/*.h 2>/dev/null
valgrind --leak-check=full ./minishell -c 'ecfreho hola'

-pedantic -fsanitize=undefined -gdwarf-4 -g3 -O0 debug: OFLAGS += -g -O0

ps -a
lsof -p <pid>
valgrind  --track-fds=yes

printf("Process: %s, in_fd: %d, out_fd: %d\n", \
exec_cmd->executable, exec_cmd->in_fd, exec_cmd->out_fd);


https://platzi.com/blog/agregar-cuentas-git-y-github-computadora/

$ vim ~/.ssh/config

# You can also manually open the file and copy/paste the section below
# Add section below to it
Host github.com
  Hostname ssh.github.com
  Port 443

1.ssh-keygen -t ed25519 -C "your_email@example.com"
2.eval $(ssh-agent -s)
3.ssh-add ~/.ssh/id_rsa
4.clip < ~/.ssh/id_rsa.pub(it copies the ssh key that has got generated)
5.then go to your remote repository on github and goto settings-> SSH and GPG keys ->new SSH key ->enter any title and paste the copied SSH key and save it
6. now give git push origin master

git@github.com:mahshakti/minish3ll.git


## INFO
Al cambiar buildin a procesos hijos, ya no funciona cd & otros. Obvio.. se ejecutan en otro proceso que no es el padre.

