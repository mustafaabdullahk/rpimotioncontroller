## Yocto Getting Started

```
$ sudo apt-get install gawk wget git-core diffstat unzip texinfo gcc-multilib build-essential chrpath socat libsdl1.2-dev xterm
```
Get source...
```
$ git clone git://git.yoctoproject.org/poky
$ cd poky
$ git clone git://git.yoctoproject.org/meta-raspberrypi -b kirkstone
$ git clone git://git.openembedded.org/meta-openembedded -b kirkstone
$ git clone https://github.com/meta-qt5/meta-qt5.git -b kirkstone
```
Prepare build env and add layers
```
$ source oe-init-build-env
$ bitbake-layers add-layer ./../meta-openembedded
$ bitbake-layers add-layer ./../meta-raspberrypi
$ bitbake-layers add-layer ./../meta-openembedded/meta-oe
$ bitbake-layers add-layer ./../meta-openembedded/meta-python
$ bitbake-layers add-layer ./../meta-openembedded/meta-networking
$ bitbake-layers add-layer ./../meta-qt5
```
and build...
```
bitbake core-image-full-cmdline
```

## Extract sdcard image

- [stackexchange entry](https://raspberrypi.stackexchange.com/questions/57155/how-do-i-use-yocto-to-build-an-sdcard-image-for-my-raspberry-pi-3-model-b)

## Extra infos

- [raspberry extra config](https://meta-raspberrypi.readthedocs.io/en/latest/extra-build-config.html)
- [yocto bsp guide](https://docs.yoctoproject.org/2.5/bsp-guide/bsp-guide.html)
- [raspberry wifi, bluetooth](https://raspberrypi.stackexchange.com/questions/49970/setting-up-in-built-bluetooth-from-raspberrypi3-using-image-created-with-yocto-j)

## Pay to attentions

- yocto main branch and all submodules should be match otherwise you get a parse error from bitbake.
- theese configurations for raspberrypi 4.