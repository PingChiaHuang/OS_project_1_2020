apt-get update
apt-get install -y gcc vim ssh wget libncurses5-dev libssl-dev libelf-dev
cd ${HOME}
wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.14.25.tar.xz
tar Jxvf linux-4.14.25.tar.xz
cd linux-4.14.25
make -j4 menuconfig
make -j4 bzImage
make -j4 modules
make -j4 modules_install
mkinitramfs -o /boot/initrd.img-4.14.25
