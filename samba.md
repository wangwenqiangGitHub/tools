# samba基本使用
```shell
sudo apt-get install samba
sudo touch /etc/samba/smbpasswd
sudo smbpasswd -a <用户>
vi /etc/samba/smb.conf

[ubuntu]
	comment = ubuntu
	path = /home/kingwq
	writable = yes
	valid user = xugaoxiang
	available = yes
	create mask = 0777
	directory mask = 0777
	public = yes

sudo /etc/init.d/smbd restart
```
