SCAN WIFI HP:
ubus call iwinfo scan '{"device":"ra0"}'

NOM DU ACCESS POINT (IF0)
uci set wireless.@wifi-iface[$intfId].ssid="kehops-929C"

VOIR L'ETAT DES CONNEXIONS:
ubus call network.wireless status

MODIFIE L'INTERFACE (CLIENT)
uci set wireless.@wifi-iface[$intfId].ssid="$ssid"
uci set wireless.@wifi-iface[$intfId].encryption="$auth"

// PASSWORD PSK2 PSK
uci set wireless.@wifi-iface[$intfId].key="$password"

// PASSWORD WEP
uci set wireless.@wifi-iface[$intfId].key=1
uci set wireless.@wifi-iface[$intfId].key1="$password"
			
// RECUPERE LA CLEF ENREGISTREE
key=$(uci -q get wireless.\@wifi-iface[$intfId].key)

// DELETE LA CLEF (RESEAU OUVERT)
uci delete wireless.@wifi-iface[$intfId].key


VALIDER LES CHANGEMENTS:
uci commit wireless

REDEMARRER L'INTERFACE:
wifi