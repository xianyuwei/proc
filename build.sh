sudo rmmod test_proc
make
sudo insmod test_proc.ko
#cat /proc/ethercat/gfar_log
