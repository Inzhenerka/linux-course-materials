savedcmd_/home/user/work/timer/timer.mod := printf '%s\n'   timer.o | awk '!x[$$0]++ { print("/home/user/work/timer/"$$0) }' > /home/user/work/timer/timer.mod
