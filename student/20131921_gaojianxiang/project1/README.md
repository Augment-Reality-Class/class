
sudo apt-get install build-essential 
sudo apt-get install libgl1-mesa-dev
sudo apt-get install libglu1-mesa-dev 
sudo apt-get install freeglut3-dev


gcc test.c -o test -lGL -lGLU -lglut



sudo apt-get install libgstreamer0.10-dev gstreamer-tools gstreamer0.10-tools gstreamer0.10-doc 
如果之前报错的话使用下面一句
sudo apt-get install gstreamer0.10-plugins-base gstreamer0.10-plugins-good gstreamer0.10-plugins-ugly gstreamer0.10-plugins-bad gstreamer0.10-plugins-bad gstreamer0.10-plugins-bad
