######################################
#              FUNCTIONS             #
######################################


####  sw_button
###############
var sw_button_tf = func (stkprop, chanel) {
	
	var stkproprties ="saitek_switch_panel/"~stkprop;
	var switch = getprop(stkproprties);

	if (switch == "1") {
		setprop (chanel, true);
	}
	
	if (switch == "0") {
		setprop (chanel, false);
	}
	
	setprop (stkproprties, "0");
}

######################################
#              MASTER BAT            #
######################################
var bot_master_bat_sw = func {
	sw_button("master_bat","/controls/switches/master-bat");
}

setprop ("saitek_switch_panel/master_bat", "0");
setlistener ("saitek_switch_panel/master_bat", bot_master_bat_sw);


######################################
#              MASTER ALT            #
######################################
var bot_master_alt_sw = func {
	sw_button("master_alt","/controls/switches/master-alt");
}

setprop ("saitek_switch_panel/master_alt", "0");
setlistener ("saitek_switch_panel/master_alt", bot_master_alt_sw);






















