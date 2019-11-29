#!/bin/sh
init()
{
//	modprobe irda
//	modprobe irtty
//	modprobe ircomm
//	modprobe s3c2410_ir
	echo 38400 > /proc/sys/net/irda/max_baud_rate
	irattach /dev/tts/2 -s 1
}

case "$1" in
  send)
  	irxfer $2
  	;;
  resv)
  	irxfer
  	;;
  *)
  	echo "init irda"
  	init
  	//irdadump
  	exit 1
esac
exit 0 
