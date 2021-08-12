######################################
#              FUNCTIONS             #
######################################

####  sw_button
###############
var sw_button_tf = func (stkprop, chanel) {
	
	var stkproprties ="/saitek_switch_panel/"~stkprop;
	
	var switch = getprop(stkproprties);

	if (switch == "1") {
		setprop (chanel, "true");
	}
	
	if (switch == "0") {
		setprop (chanel, "false");
	}
	
	setprop (stkproprties, "0");
}

######################################
#              MASTER BAT            #
######################################
var bot_master_bat_sw = func {
	sw_button_tf("master_bat","/controls/switches/master-bat");
}

setprop ("/saitek_switch_panel/master_bat", "0");
setlistener ("/saitek_switch_panel/master_bat", bot_master_bat_sw);


######################################
#              MASTER ALT            #
######################################
var bot_master_alt_sw = func {
	sw_button_tf("master_alt","/controls/switches/master-alt");
}

setprop ("/saitek_switch_panel/master_alt", "0");
setlistener ("/saitek_switch_panel/master_alt", bot_master_alt_sw);



######################################
#              MASTER AVIONIC        #
######################################
var bot_master_avionic_sw = func {
	sw_button_tf("master_avionic","/controls/switches/master-avionics");
}

setprop ("/saitek_switch_panel/master_avionic", "0");
setlistener ("/saitek_switch_panel/master_avionic", bot_master_avionic_sw);


######################################
#              FUEL PUMP             #
######################################
var bot_fuel_pump_sw = func {
	sw_button_tf("fuel_pump","/controls/engines/engine/fuel-pump");
}

setprop ("/saitek_switch_panel/fuel_pump", "0");
setlistener ("/saitek_switch_panel/fuel_pump", bot_fuel_pump_sw);



##### NOT WORKING, I don't know what is the action in GF
######################################
#              DE_ICE                #
######################################
var bot_de_ice_sw = func {
######	sw_button_tf("de_ice"," ????? ");
}

setprop ("/saitek_switch_panel/de_ice", "0");
setlistener ("/saitek_switch_panel/de_ice", bot_de_ice_sw);




######################################
#              PITOT HEAT            #
######################################
var bot_pitot_heat_sw = func {
 sw_button_tf("pitot_heat","/controls/anti-ice/pitot-heat");
}

setprop ("/saitek_switch_panel/pitot_heat", "0");
setlistener ("/saitek_switch_panel/pitot_heat", bot_pitot_heat_sw );



######################################
#              COWL                  #
######################################
var bot_cowl_sw = func {
	sw_button_tf("cowl","/controls/engines/engine/cowl-flaps-norm");
}

setprop ("/saitek_switch_panel/cowl", "0");
setlistener ("/saitek_switch_panel/cowl", bot_cowl_sw);



##### NOT WORKING, I don't know what is the action to perform in GF
######################################
#              LIGHT PANEL           #
######################################
var bot_light_panel_sw = func {
######	sw_button_tf("cowl"," ????? ");
}

setprop ("/saitek_switch_panel/light_panel", "0");
setlistener ("/saitek_switch_panel/light_panel", bot_light_panel_sw);


######################################
#           LIGHTING   BEACON        #
######################################
var bot_light_beacon_sw = func {
 sw_button_tf("light_beacon","/controls/mighting/beacon");
}

setprop ("/saitek_switch_panel/light_beacon", "0");
setlistener ("/saitek_switch_panel/light_beacon", bot_light_beacon_sw );


######################################
#              LIGHTING NAV          #
######################################
var bot_light_nav_sw = func {
 sw_button_tf("light_nav","/controls/lighting/nav-lights");
}

setprop ("/saitek_switch_panel/light_nav", "0");
setlistener ("/saitek_switch_panel/light_nav", bot_light_nav_sw );


######################################
#              LIGHTING STROB        #
######################################
var bot_light_strob_sw = func {
 sw_button_tf("light_strob","/controls/lighting/strob");
}

setprop ("/saitek_switch_panel/light_strob", "0");
setlistener ("/saitek_switch_panel/light_strob", bot_light_strob_sw );

######################################
#              LIGHTING TAXI         #
######################################
var bot_light_taxi_sw = func {
 sw_button_tf("light_taxi","/controls/lighting/taxi-light");
}

setprop ("/saitek_switch_panel/light_taxi", "0");
setlistener ("/saitek_switch_panel/light_taxi", bot_light_taxi_sw );


######################################
#              LIGHTING LANDING      #
######################################
var bot_light_landing_sw = func {
 sw_button_tf("light_landing","/controls/lighting/landings-lights");
}

setprop ("/saitek_switch_panel/light_landing", "0");
setlistener ("/saitek_switch_panel/light_landing", bot_light_landing_sw );


######################################
#              GEAR UP DOWN          #
######################################
var bot_gear_up_down_sw = func {
 sw_button_tf("gear_up_down","/controls/gear/gear-down");
}

setprop ("/saitek_switch_panel/gear_up_down", "0");
setlistener ("/saitek_switch_panel/gear_up_down", bot_gear_up_down_sw );




######################################
#				MAGNETO              # 
######################################
var bot_magneto_rot = func {
	
	var val = getprop("/saitek_switch_panel/magnetos");
	
	setprop ("/controls/switches/magnetos", val);

	setprop ("/saitek_switch_panel/magnetos", "0");
}

setprop ("/saitek_switch_panel/magnetos", "0");
setlistener ("/saitek_switch_panel/magnetos", bot_magneto_rot );























