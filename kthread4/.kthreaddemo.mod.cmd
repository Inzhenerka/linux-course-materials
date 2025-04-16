savedcmd_/home/user/work/kthread4/kthreaddemo.mod := printf '%s\n'   kthreaddemo.o | awk '!x[$$0]++ { print("/home/user/work/kthread4/"$$0) }' > /home/user/work/kthread4/kthreaddemo.mod
