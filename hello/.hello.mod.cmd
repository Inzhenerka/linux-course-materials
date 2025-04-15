savedcmd_/home/user/work_t/hello/hello.mod := printf '%s\n'   hello.o | awk '!x[$$0]++ { print("/home/user/work_t/hello/"$$0) }' > /home/user/work_t/hello/hello.mod
