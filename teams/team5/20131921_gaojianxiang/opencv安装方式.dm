下载最新版本的opencv源码 
https://github.com/opencv/opencv/archive/3.4.0.zip

编译源代码 
解压下载的源码文件到~/opencv目录下，执行以下命令：

cd ~/opencv
mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..

下载 ippicv_2017u3_lnx_intel64_general_20170822.tgz 
由于网络的问题，通常在执行cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local .. 的时候会报错，显示ippicv_2017u3_lnx_intel64_general_20170822.tgz这个文件下载不成功，那么可以预先下载好这个文件放到特定的目录下，下载地址为 https://pan.baidu.com/s/1o8ywdZW，下载完毕后，将文件重命名为4e0352ce96473837b1d671ce87f17359-ippicv_2017u3_lnx_intel64_general_20170822.tgz，即文件名前面加上md5，放到~/opencv/.cache/ippicv下，再重新运行cmake -D CMAKE_BUILD_TYPE=Release -D CMAKE_INSTALL_PREFIX=/usr/local ..

编译、安装

make
sudo make install
