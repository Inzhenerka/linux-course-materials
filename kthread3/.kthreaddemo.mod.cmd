savedcmd_/home/user/work/kthread3/kthreaddemo.mod := printf '%s\n'   kthreaddemo.o | awk '!x[$$0]++ { print("/home/user/work/kthread3/"$$0) }' > /home/user/work/kthread3/kthreaddemo.mod
