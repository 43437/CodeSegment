#modify sshd default port
#!/bin/bash

sed -i 's/.*Port[[:space:]]*[0-9]*$/Port 4022/' /etc/ssh/sshd_config
firewall-cmd --zone=public --add-port=4022/tcp --permanent
firewall-cmd --remove-port=22/tcp --permanent
firewall-cmd --reload

systemctl restart sshd.service
