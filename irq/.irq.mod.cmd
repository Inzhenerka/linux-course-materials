savedcmd_/home/user/work/irq/irq.mod := printf '%s\n'   irq.o | awk '!x[$$0]++ { print("/home/user/work/irq/"$$0) }' > /home/user/work/irq/irq.mod
