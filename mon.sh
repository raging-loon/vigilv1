ip link set $wifi_nic down
iw $wifi_nic set monitor control
ip link set $wifi_nic up
 