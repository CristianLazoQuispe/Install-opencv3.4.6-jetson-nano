# Install-opencv3.4.6-jetson-nano
Install opencv 3.4.6 jetson nano


Since memory (4GB) on the Jetson Nano is rather limited, I’d create and mount a swap file on the system. 


		$ sudo fallocate -l 8G /mnt/8GB.swap
		$ sudo mkswap /mnt/8GB.swap
		$ sudo swapon /mnt/8GB.swap

Once the above is working, add the following line into /etc/fstab and reboot the system. Make sure the swap space gets mounted automatically after reboot.

		/mnt/8GB.swap  none  swap  sw 0  0
Example fstab:

<img src="scripts/fstab.png?raw=true" width="600" height = "200"/>

reboot

		$ sudo reboot now

After the reboot, clone the repository:

		$ git clone https://github.com/CristianLazoQuispe/Install-opencv3.4.6-jetson-nano.git
		$ cd Install-opencv3.4.6-jetson-nano/
		$ cd scripts/

To set Jetson Nano to 10W performance mode

		$ sudo nvpmodel -m 0
		$ sudo jetson_clocks

Install basic libraries

		$ ./install_basics.sh

Install protobuf

		$ ./install_protobuf-3.6.1.sh

Install protobuf

		$ ./install_opencv-3.4.6.sh
