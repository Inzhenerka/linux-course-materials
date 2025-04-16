savedcmd_/home/user/work_t/my_alert/my_alert.mod := printf '%s\n'   my_alert.o | awk '!x[$$0]++ { print("/home/user/work_t/my_alert/"$$0) }' > /home/user/work_t/my_alert/my_alert.mod
