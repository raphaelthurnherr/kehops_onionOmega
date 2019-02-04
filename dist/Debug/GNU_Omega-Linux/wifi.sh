#!/bin/sh

ScanWifi () {
        WIFILIST="$(ubus call iwinfo scan '{"device":"ra0"}')"
        echo $WIFILIST
        exit 0
}

AddWifi () {
        local index=$2
	local ssid=$3
        local pass=$4
        local encr=$5

        uci add wireless wifi-config > /dev/null
        uci set wireless.@wifi-config["$index"].ssid="$ssid"
        uci set wireless.@wifi-config["$index"].key="$pass"
        uci set wireless.@wifi-config["$index"].encryption="$encr"
        uci commit wireless
        uci set wireless.sta.disabled=0
        uci commit wireless
        uci set wireless.radio0.device_mode=apsta
        uci commit wireless
        wifi
        ##uci delete wireless.@wifi-config[0]
        
        exit 0
}

########################
##### Main Program #####

# read the arguments
if [ $# == 0 ]
then
        ## accept all info from user interactions
        echo "Please specify param"
else
        ## accept info from arguments
        while [ "$1" != "" ]
        do
                case "$1" in
                -h|-help|--help|help)
                        ;;
                -scan)
                                ScanWifi
                        ;;
                -add)
                                AddWifi $1 $2 $3 $4 $5
                        ;;
                    *)
                                echo "ERROR: Invalid Argument: $1"
                                exit
                        ;;
                esac
        done
fi

exit 0