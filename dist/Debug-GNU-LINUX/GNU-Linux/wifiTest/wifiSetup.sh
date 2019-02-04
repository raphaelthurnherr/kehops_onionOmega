SCAN WIFI HP:
ubus call iwinfo scan '{"device":"ra0"}'

VOIR L'ETAT DES CONNEXIONS:
ubus call network.wireless status

NOM DU ACCESS POINT (IF0)
uci set wireless.@wifi-iface[0].ssid="kehops-929C"

MODIFIE L'INTERFACE (CLIENT)
uci set wireless.@wifi-iface[1].ssid="Samsung"
uci set wireless.@wifi-iface[1].encryption="psk"

// PASSWORD PSK2 PSK
uci set wireless.@wifi-iface[1].key="sam123456"

// PASSWORD WEP
uci set wireless.@wifi-iface[$intfId].key=1
uci set wireless.@wifi-iface[$intfId].key1="$password"
			
// RECUPERE LA CLEF ENREGISTREE
key=$(uci -q get wireless.\@wifi-iface[1].key)

// DELETE LA CLEF (RESEAU OUVERT)
uci delete wireless.@wifi-iface[1].key


VALIDER LES CHANGEMENTS:
uci commit wireless

REDEMARRER L'INTERFACE:
wifi

LISTER LES CONFIG WIFI!
wifisetup -list



uci add wireless wifi-iface > /dev/null
uci set wireless.@wifi-iface[1].device="radio0" 

//uci set wireless.@wifi-iface[1]="wifi-iface"
uci set wireless.@wifi-iface[1].mode="sta"
(uci set wireless.radio0.device_mode="sta"
uci set wireless.@wifi-iface[1].network="wwan"
uci set wireless.@wifi-iface[1].ssid="RaphTest"
uci set wireless.@wifi-iface[1].encryption="psk2"
//uci set wireless.@wifi-iface[1].ifname="apcli0"

//uci set wireless.@wifi-iface[1].section="sta"

PSK|| PSK2
uci set wireless.@wifi-iface[1].key="1234abcd"

wep)
	uci set wireless.@wifi-iface[$intfId].key=1
	uci set wireless.@wifi-iface[$intfId].key1="$password"
			
none)
	# set no keys for open networks, delete any existing ones
	local key=$(uci -q get wireless.\@wifi-iface[$intfId].key)

	if [ "$key" != "" ]; then
		uci delete wireless.@wifi-iface[$intfId].key




uci set wireless.@wifi-iface[1].disabled=0

uci commit wireless

/etc/init.d/network restart




##
DELETE
uci delete wireless.@wifi-iface[2]

# check if network has to be committed (for AP addr change)
if 	[ "$networkType" = "ap" ] &&
	[ "$apIpAddr" != "" ]; then
	uci commit network
fi
		

//////////////

		"interfaces": [
			{
				"section": "ap",
				"ifname": "ra0",
				"config": {
					"mode": "ap",
					"ifname": "ra0",
					"encryption": "psk2",
					"key": "12345678",
					"ssid": "kehops-929C",
					"mode": "ap",
					"network": [
						"wlan"
					],
					"disabled": false
				}
			},
			{
				"section": "sta",
				"ifname": "apcli0",
				"config": {
					"mode": "sta",
					"ifname": "apcli0",
					"encryption": "psk2",
					"key": "2xok-1f62-wply-kpur",
					"ssid": "cac-39837",
					"mode": "sta",
					"network": [
						"wwan"
					],
					"disabled": false
				}
		
		}
		]
