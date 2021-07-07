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

Install opencv

		$ ./install_opencv-3.4.6.sh

### Note 
If you get an error with cuda_gl_interop.h:
		```
		/usr/local/cuda-8.0/include/cuda_gl_interop.h:64:2: error: #error Please include the appropriate gl headers before including cuda_gl_interop.h
		#error Please include the appropriate gl headers before including cuda_gl_interop.h
		```

You should do some modifications in ```/usr/local/cuda/include/cuda_gl_interop.h``` to fix the symbolic link of libGL.so.
		$ sudo vim /usr/local/cuda/include/cuda_gl_interop.h

The lines #62~#68 of ```cuda_gl_interop.h```. They look like after the modification:
	
	//#if defined(__arm__) || defined(__aarch64__)
	//#ifndef GL_VERSION
	//#error Please include the appropriate gl headers before including cuda_gl_interop.h
	//#endif
	//#else
	#include <GL/gl.h>
	//#endif


Then:
		$ cd /usr/lib/aarch64-linux-gnu/
		$ sudo ln -sf tegra/libGL.so libGL.so


Finally, you should download and install opencv-3.4.0 again
		$ ./install_opencv-3.4.6.sh



If you get an error with libGL.so:
		```
		Built target pch_Generate_opencv_stitching
		Scanning dependencies of target opencv_cudev
		make[2]: *** No rule to make target '/usr/lib/aarch64-linux-gnu/libGL.so', needed by 'lib/libopencv_cudev.so.3.4.6'. Stop.
		make[2]: *** Waiting for unfinished jobs....
		```
	
The error message says that make is not able to find the file ```/usr/lib/aarch64-linux-gnu/libGL.so```. Check if there is a ```/usr/lib/aarch64-linux-gnu/libGL.so.1.0.0``` on your Jetson Nano. If yes, you should be able to fix the problem by creating a symbolic link:

		$ sudo ln -sf libGL.so.1.0.0 /usr/lib/aarch64-linux-gnu/libGL.so
	
If you don't find any libGL.so.* at all, then there's probably something wrong with your Jetson Nano rootfs. In that case, I'd suggest you to re-flash your Jetson Nano system with the latest image from NVIDIA.


Test installation:

		$ cd ../test/

	Test opencv on c++ :

		$ g++ read_image.cpp -o app `pkg-config --cflags --libs opencv`
		$ ./app 
	
<img src="results/test_cplusplus.png?raw=true" width="600" height = "200"/>

		$ g++ read_video.cpp -o app `pkg-config --cflags --libs opencv`
		$ ./app
	
<img src="results/result_video_cplus_clpus.png?raw=true" width="600" height = "200"/>

	Test opencv on python3:

		$ python3 read_image.py 

<img src="results/test_python3.png?raw=true" width="600" height = "200"/>

		$ python3 read_video.py 

<img src="results/result_video_python.png?raw=true" width="600" height = "200"/>

	
