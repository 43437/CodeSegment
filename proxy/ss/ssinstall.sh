#!/bin/bash

# install epel repos
echo "install epel-release"
yum -y install epel-release
if [ 0 -ne $? ]
then
  echo "install epel-release failed" > install.log
  exit 1
fi

# install pip
echo "install pip"
yum -y install python-pip
if [ 0 -ne $? ]
then
  echo "install pip failed" > install.log
  exit 1
fi

# upgrade pip
echo "upgrade pip"
pip install --upgrade pip
if [ 0 -ne $? ]
then
  echo "upgrade pip failed" > install.log
  exit 1
fi

# install shadowsocks
echo "install shadowsocks"
pip install shadowsocks
if [ 0 -ne $? ]
then
  echo "install shadowsocks failed" > install.log
  exit 1
fi

# install mkpasswd
echo "install mkpasswd"
yum -y install expect
if [ 0 -ne $? ]
then
  echo "install mkpasswd failed" > install.log
  exit 1
fi

# open port for service
firewall-cmd --permanent --add-port=8080/tcp
firewall-cmd --reload

# generate config file
pw=$(mkpasswd -l 15 -s 4)

echo "config shadowsocks"
echo "{
  \"server\":\"0.0.0.0\",
  \"server_port\":8080,
  \"password\":\"$pw\",
  \"method\":\"aes-256-cfb\"
}
" > /etc/shadowsocks.json

# generate service file
echo "[Unit]
Description=Shadowsocks

[Service]
TimeoutStartSec=0
ExecStart=/usr/bin/ssserver -c /etc/shadowsocks.json

[Install]
WantedBy=multi-user.target" > /etc/systemd/system/shadowsocks.service

# enable and start service
chmod a+x /etc/systemd/system/shadowsocks.service

systemctl enable shadowsocks
systemctl start shadowsocks
