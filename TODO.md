
## POR HACER
- [ ] Revisar export a="algo=k", Se divide en 2
a=
algo=k
cuando debería ser a=algo=k
- [X] ls / /home
- [X] cd ~/.cd42/ Con ruta relativa
- [X] ARREGLAR Ctr +D
- [X] EJECUTAR MINISHELL DENTRO DE MINISHELL Y ACTUALIZAR SHLVL=1
	Nadie lo hace?, Ojo con unset SHLVL (Implementado en init_shell())
- [X] Revisar el ft_strconcat y ft_strdup (Problemas con el prompt)
	Se hizo un apaño imprimiendo con printf el prompt en vez de meterlo todo en el readline()
- [ ] COMPROBAR COMILLAS, SIMPLES O DOBLES, CERRADAS! en export, echo,..
- [ ] ls -la >> apen3.txt >> apen4.txt
- [ ] echo $? + $? Devuelve basura (�Fϓ�U + 1) y en bash (0 + 0)
- [ ] Meter en algún lado el mensaje de error al borrar PWD y hacer cd ..

remove ft_isallalpha.c ??? --> usar en export ex: export a=">>"

## ERRORES & LEAKS
- [X] valgrind export algo=a""sd, leak
- [X] valgrind en echo heredoc (revisar ft_strjoin), leak
- [ ] Después de hacer un echo y presionar (flecha abajo) en el historial, se queda estatico echo
- [ ] Entradas con pipe como env | grep SHLVL se queda experando, en bash no

## COSAS QUE NO ES NECESARIO HACER
- [-] cd - se interpreta como cd sin nada NO ES NECESARIO?, solo rutas
- [X] Eliminado adjust_prompt en utls.c, como primer intento de ajustar el prompt al tamaño de la consola
- [?] Still reachable de readline

## PROBAR
- [ ] COMPROBAR QUE CUALQUIER COMANDO QUE DEPENDA DE VARIABLES DE ENTORNO NO DE Segmentation fault AL BORRAR SU VARIABLE EX: $PWD/cd, pwd .., $HOME/cd ~/,
- [ ] BUSCAR LA GUIA DE CORRECCIÓN Y PROBAR
- [ ] COMPROBAR QUE NO SE USAN FUNCIONES PROHIBIDAS
- [ ] Quitar posibles comentarios y debug code (utils/dbg_print.c, y minishell.h) antes de entrega, NORMA


echo "cat lol.c | " cat > lol.c"
> "
user@darkc:/tmp$ echo 'cat lol.c | " cat > lol.c'
cat lol.c | " cat > lol.c

echo "  a   sd " | cat -e


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

## INFO
- Mirar las funciones rl_clear_history(), rl_deprep_terminal() y rl_cleanup_after_signal. Pueden servir para arreglar los still reachable.

- Si se ejecutan los comandos build-in en procesos hijos, ya no funciona comandos como cd, export, etc, Porque cada proceso hijo lleva una copia de las variables de entorno del padre y solo se cambian en el hijo que al hacer exit se borra.
Thrads (Hilos) si comparten memoria, Procesos (Fork) no por eso usan señales??? (Ver philosophers + bonus).

## DUDAS ??¿?¿?¿¿?
- ctrl-D in an empty prompt should quit minishell --> RELAUNCH!
- ctrl-D in a prompt after you wrote some stuff should not do anything.
- Try ctrl-D after running a blocking command like cat without arguments or grep “something“.
- Entonces, ¿ctrl-D Se sale de la shell definitivamente? (según subject) o sale y se relanza (Bye bye, pero vuelve a la shell) (según hoja de correcciones)?

## COMENTARIOS

---

- exit (999), echo $? debe mostrar 999 fuera de la minishell -> NO, según subject es exit sin argumentos

---

- Set the $PATH to a multiple directory value (directory1:directory2) and ensure that directories are checked in order from left to right.

En teoría es así. En child_utils.c -> get_path_exec() se llama a env_path_to_array() que es la función que trocea "PATH" y ft_split trocea en orden.

	tmp_str = get_env_value(shell->env_list, "PATH");
	if (!tmp_str)
		print_error(-1, shell, ERR_PATH);
	path_array = ft_split(tmp_str, ':');
- [X] Creado print_path en dbg_print.c por si acaso ... Ex: ls + echo $PATH

## COSAS
- norminette -R CheckForbiddenSourceHeader **/*.c **/*.h 2>/dev/null
- valgrind --leak-check=full ./minishell -c 'ecfreho hola'
- env -i ./minishell
- ps -a
- lsof -p <pid>
- valgrind  --track-fds=yes

printf("Process: %s, in_fd: %d, out_fd: %d\n", \
exec_cmd->executable, exec_cmd->in_fd, exec_cmd->out_fd);

---

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
