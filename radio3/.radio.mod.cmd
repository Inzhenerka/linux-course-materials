savedcmd_/home/user/work/radio3/radio.mod := printf '%s\n'   radio.o | awk '!x[$$0]++ { print("/home/user/work/radio3/"$$0) }' > /home/user/work/radio3/radio.mod
