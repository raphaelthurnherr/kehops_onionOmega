#!/bin/sh

ScanWifi () {
        WIFILIST="$(ubus call iwinfo scan '{"device":"ra0"}')"
        echo $WIFILIST
        exit 0
}

wanCheck () {
        WIFILIST="$(ubus call iwinfo scan '{"device":"ra0"}')"
        echo $WIFILIST
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
                    *)
                                echo "ERROR: Invalid Argument: $1"
                                exit
                        ;;
                esac
        done
fi

exit 0