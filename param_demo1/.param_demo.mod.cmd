savedcmd_/home/user/work_t/param_demo1/param_demo.mod := printf '%s\n'   param_demo.o | awk '!x[$$0]++ { print("/home/user/work_t/param_demo1/"$$0) }' > /home/user/work_t/param_demo1/param_demo.mod
