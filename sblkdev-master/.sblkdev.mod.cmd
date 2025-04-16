savedcmd_/home/user/work/sblkdev-master/sblkdev.mod := printf '%s\n'   main.o device.o | awk '!x[$$0]++ { print("/home/user/work/sblkdev-master/"$$0) }' > /home/user/work/sblkdev-master/sblkdev.mod
