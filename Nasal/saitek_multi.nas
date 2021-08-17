######################################
#     FUNCTIONS  MULTI PANEL         #
######################################

#### flaps_control
##################
var flaps_control = func (stkprop, chanel) {
	var stkproprties ="/saitek_multi_panel/"~stkprop;

	var switch = getprop(stkproprties);
	var flaps_old_val = getprop(chanel);
		
	if (switch == "2") {
		if (flaps_old_val <= 0.1 ) 							{ setprop (chanel, "0.33") ; }
		if (flaps_old_val >= 0.3 and flaps_old_val <= 0.4 ) { setprop (chanel, "0.66") ; }
		if (flaps_old_val >= 0.6 ) 							{ setprop (chanel, "1"   ) ; }
	}
	
	if (switch == "1") {
		if (flaps_old_val >= 0.9 ) 							{ setprop (chanel, "0.66") ; }
		if (flaps_old_val >= 0.6 and flaps_old_val <=0.7 ) 	{ setprop (chanel, "0.33") ; }
		if (flaps_old_val <= 0.4 ) 							{ setprop (chanel, "0"   ); }
	}
	
	setprop (stkproprties, "0");
}


#### bot_sw_on_off
##################
var bot_sw_on_off = func (stkprop, chanel) {
	
	var stkproprties ="/saitek_multi_panel/"~stkprop;
	
	var switch = getprop(chanel);

	if (switch == "true") {
		setprop (chanel, "false");
	}
	
	if (switch == "false") {
		setprop (chanel, "true");
	}
	setprop (stkproprties, "0");
}


####  sw_button
###############
var sw_button_tf = func (stkprop, chanel) {
	
	var stkproprties ="/saitek_multi_panel/"~stkprop;
	
	var switch = getprop(stkproprties);

	if (switch == "1") {
		setprop (chanel, "true");
	}
	
	if (switch == "0") {
		setprop (chanel, "false");
	}
	
	setprop (stkproprties, "0");
}

####  inc_val
##############
var inc_val = func (val, min, max, inc, mult){
	
	mlt = int (mult);
	if (mlt == 0){
		mlt = 1;
	} 
	
	var int_val = int(val);

	int_val = int_val + (inc * mlt) ;
	
	if (int_val > max) { int_val = min; }
	if (int_val < min) { int_val = max; }

	return int_val;
}

#####  inc_val_chanel
######################
var inc_val_chanel = func (stkprop, chanel ,min, max, mul){
	var stkproprties ="saitek_multi_panel/"~stkprop;
	
	var switch = getprop(stkproprties);
	if (switch != "0") {
		var proprFreq = chanel;
		var val = getprop(proprFreq);
		
		if(switch == "1"){  
			val = inc_val(val,min,max,1, mul);
		}
		
		if(switch == "2"){  
			val = inc_val(val,min,max,-1,mul);
		}
			
		setprop (proprFreq, val);
	}
	setprop (stkproprties, "0");

}


######################################
#                ALT                 #
######################################
var fun_alt_inc = func {
	inc_val_chanel("bot_alt_inc","/autopilot/KAP140/settings/target-alt-ft",0,49999,100);
}

setprop ("/saitek_multi_panel/bot_alt_inc", "0");
setlistener ("/saitek_multi_panel/bot_alt_inc", fun_alt_inc);


######################################
#                VS                  #
######################################
var fun_vs_inc = func {
	inc_val_chanel("bot_vs_inc","/autopilot/KAP140/settings/target-pressure-rate-fpm",0,10000,10);
}

setprop ("/saitek_multi_panel/bot_vs_inc", "0");
setlistener ("/saitek_multi_panel/bot_vs_inc", fun_vs_inc);

######################################
#                IAS                 #
######################################
var fun_ias_inc = func {
	inc_val_chanel("bot_ias_inc","/autopilot/KAP140/settings/target-pressure-rate",0,10000,1);
}

setprop ("/saitek_multi_panel/bot_ias_inc", "0");
setlistener ("/saitek_multi_panel/bot_ias_inc", fun_ias_inc);


######################################
#                HDG                 #
######################################
var fun_hdg_inc = func {
	inc_val_chanel("bot_hdg_inc","/autopilot/settings/heading-bug-deg",0,359,1);
}
setprop ("/saitek_multi_panel/bot_hdg_inc", "0");
setlistener ("/saitek_multi_panel/bot_hdg_inc", fun_hdg_inc);

######################################
#                CRS                 #
######################################

var fun_crs_inc = func {
	inc_val_chanel("bot_crs_inc","/autopilot/settings/heading-bug-deg",0,359,1);
}
setprop ("/saitek_multi_panel/bot_crs_inc", "0");
setlistener ("/saitek_multi_panel/bot_crs_inc", fun_crs_inc);

######################################
#                Pitch Trim          #
######################################

var fun_trim = func {
	flaps("bot_trim","/controls/flight");
}
setprop ("/saitek_multi_panel/bot_trim", "0");
setlistener ("/saitek_multi_panel/bot_trim", fun_trim);


######################################
#                BTN AP              #
######################################
var bot_ap_sw = func {

	var stkproprties ="/saitek_multi_panel/bot_ap";
	
	setprop (stkproprties, 6);	
	var switch = getprop("/autopilot/KAP140/locks/pitch-mode");
	
	if (switch == "true") {
		setprop ("/autopilot/KAP140/locks/pitch-axis", "false");
		setprop ("/autopilot/KAP140/locks/roll-axis", "false");
		setprop ("/autopilot/KAP140/locks/pitch-mode", "0");
	}


	if (switch == "false" ) {
		setprop ("/autopilot/KAP140/locks/pitch-axis", "true");
		setprop ("/autopilot/KAP140/locks/roll-axis", "true");
		setprop ("/autopilot/KAP140/locks/pitch-mode", "1");
	}
	
	setprop (stkproprties, 2);
}

setprop ("/saitek_multi_panel/bot_ap", "0");
setlistener ("/saitek_multi_panel/bot_ap", bot_ap_sw);


######################################
#                BTN HDG             #
######################################
var bot_heg_sw = func {
	bot_sw_on_off("bot_heg","/autopilot/KAP140/locks/hdg-hold");
}

setprop ("/saitek_multi_panel/bot_heg", "0");
setlistener ("/saitek_multi_panel/bot_heg", bot_heg_sw);


######################################
#                BTN NAV             #
######################################
var bot_nav_sw = func {
	bot_sw_on_off("bot_nav","/autopilot/KAP140/locks/nav-hold");
}

setprop ("/saitek_multi_panel/bot_nav", "0");
setlistener ("/saitek_multi_panel/bot_nav", bot_nav_sw);


######################################
#                BTN IAS             #
######################################
var bot_ias_sw = func {
	#### bot_sw_on_off("bot_ias","/autopilot/KAP140/locks/");
}

setprop ("/saitek_multi_panel/bot_ias", "0");
setlistener ("/saitek_multi_panel/bot_ias", bot_ias_sw);


######################################
#                BTN ALT             #
######################################
var bot_alt_sw = func {
	bot_sw_on_off("bot_alt","/autopilot/KAP140/locks/alt-hold");
}

setprop ("/saitek_multi_panel/bot_alt", "0");
setlistener ("/saitek_multi_panel/bot_alt", bot_alt_sw);


######################################
#                BTN VS              #
######################################
var bot_vs_sw = func {
###	bot_sw_on_off("bot_vs","/autopilot/KAP140/locks/");
}

setprop ("/saitek_multi_panel/bot_vs", "0");
setlistener ("/saitek_multi_panel/bot_vs", bot_vs_sw);


######################################
#                BTN APR             #
######################################
var bot_apr_sw = func {
	bot_sw_on_off("bot_apr","/autopilot/KAP140/locks/apr-hold");
}

setprop ("/saitek_multi_panel/bot_apr", "0");
setlistener ("/saitek_multi_panel/bot_apr", bot_apr_sw);


######################################
#                BTN REV             #
######################################
var bot_rev_sw = func {
	bot_sw_on_off("bot_rev","/autopilot/KAP140/locks/rev-hold");
}

setprop ("/saitek_multi_panel/bot_rev", "0");
setlistener ("/saitek_multi_panel/bot_rev", bot_rev_sw);



######################################
#                Auto Trot           #
######################################
# not for cessna
var bot_auto_trottle_sw = func {
	sw_button_tf("bot_auto_trottle","/contols/autoflight/autothrottle-arm");
}

setprop ("/saitek_multi_panel/bot_auto_trottle", "0");
setlistener ("/saitek_multi_panel/bot_auto_trottle", bot_auto_trottle_sw);


######################################
#                Flaps               #
######################################
var fun_bot_flaps_inc = func {
	flaps_control("bot_flaps_inc","/controls/flight/flaps");
}
setprop ("/saitek_multi_panel/bot_flaps_inc", "0");
setlistener ("/saitek_multi_panel/bot_flaps_inc", fun_bot_flaps_inc);




