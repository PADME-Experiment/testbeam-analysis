source ~/padme-fw/Configure/padme_init.sh
source ~/padme-fw/Configure/padme_init_cvmfs_centos7_root6.sh
export LD_LIBRARY_PATH=$(find /home/monitor/padme-fw/ -type d -name lib|paste -sd:):$LD_LIBRARY_PATH
export CPATH=$(find /home/monitor/padme-fw/ -type d -name include|paste -sd:):$CPATH
export LIBRARY_PATH=$(find /home/monitor/padme-fw/ -type d -name lib|paste -sd:):$LIBRARY_PATH
