savedcmd_/home/user/work/kthread1/kthreaddemo.mod := printf '%s\n'   kthreaddemo.o | awk '!x[$$0]++ { print("/home/user/work/kthread1/"$$0) }' > /home/user/work/kthread1/kthreaddemo.mod
