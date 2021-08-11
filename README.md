
Driver Saitek Radio Panel for flightgear under Linux

### 
copy saitek_input.xml and saitek_output.xml to $FG_ROOT/Protocole
copy saitek_nas.nas  to ~/.fgfs/Nasal/

##
 run flightgear whith options : 

```
/usr/games/fgfs \
	...
	--generic=socket,out,30,127.0.0.1,49001,udp,saitek_output \
	--generic=socket,in,30,,49002,udp,saitek_input  \
	...
```

## run driver 

```
	sudo ./saitek_fg /dev/hidraw3
```
---
	
# new driver 

```
fgfs --generic=socket,in,30,,49006,udp,saitek_switch_input
```


Pour tester, envoyer en UDPune chaine 

```
printf "0,0\n" | nc -4u -w1 127.0.0.1 49006

```