savedcmd_/home/user/work_t/hello2/hello.mod := printf '%s\n'   start.o stop.o | awk '!x[$$0]++ { print("/home/user/work_t/hello2/"$$0) }' > /home/user/work_t/hello2/hello.mod
