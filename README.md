# Raspberry Motion Controller

Pirmc provides to communicate ADS1256 and DAC8552 with spi interface and serv from grpc server. Contains adc and dac drivers. Developed with linux spi and gpio drivers.

## Prepare buildroot sdk

distversion : downloaded release version.

- download buildroot [link](https://buildroot.org/download.html)
- tar -xf buildroot-distversion.tar.gx
- cp ~/your_store_path/rpimotioncontroller/buildroot-config/.config buildroot-distversion/
- make sdk

## Requirements

- buildroot sdk
- cmake

## Build 

source buildroot-distversion/output/host/environment-setup
mkdir build
popd build
cmake ..
make all
scp pirmc root@raspberryip:~/path
./pirmc