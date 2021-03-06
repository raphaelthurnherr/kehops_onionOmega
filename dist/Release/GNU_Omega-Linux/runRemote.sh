#bin/bash
# Indique au système que l'argument qui suit est le programme utilisé pour exécuter ce fichier
# En règle générale, les "#" servent à mettre en commentaire le texte qui suit comme ici


#CREATION D UN NOUVEAU BUILDNUMBER DANS LE FICHIER HEADER
number=$(cut buildNumber.h -c 20-)
newHeader='#define BUILD_CODE '$((number+1))
echo $newHeader > buildNumber.h
echo Build code: \# $((number))       

md5sum /home/raph/ownCloud/dev/Projets/kehops_onionOmega/dist/Release/GNU_Omega-Linux/kehops | cut -c -32 > dist/Release/GNU_Omega-Linux/kehops.md5
#md5sum /home/raph-pnp/ownCloud/dev/Projets/kehops_onionOmega/dist/Release/GNU_Omega-Linux/kehops | cut -c -32 > dist/Release/GNU_Omega-Linux/kehops.md5
echo "Fichier MD5 cr�e: "`cat /home/raph-pnp/ownCloud/dev/Projets/kehops_onionOmega/dist/Release/GNU_Omega-Linux/kehops.md5`

#echo "Compression des fichiers binaires \"kehops.tar\""
tar -cvf dist/Release/kehops.tar -C dist/Release/GNU_Omega-Linux/ deviceMap.cfg devices.cfg kehops.cfg wifi.sh kehops kehops.md5

echo "Transfere des fichiers binaire..."
rsync -a /home/raph/ownCloud/dev/Projets/kehops_onionOmega/dist/Release/GNU_Omega-Linux/kehops root@192.168.3.1:~/kehops
#rsync -a /home/raph-pnp/ownCloud/dev/Projets/kehops_onionOmega/dist/Release/GNU_Omega-Linux/kehops root@192.168.3.1:~/kehops

echo "Transfere du fichier MD5 du binaire..."
#rsync -a /home/raph-pnp/Documents/dev/embedded_soft/kehops_onionOmega/dist/Release/GNU_Omega-Linux/kehops.md5  root@192.168.3.1:~/kehops
#echo "Transfere du script de mise à jour"
#rsync -a /home/raph-pnp/Documents/dev/embedded_soft/kehops_onionOmega/dist/Release/GNU_Omega-Linux/kehopsManager.sh  root@192.168.3.1:~       
#echo "Lancement de l'application via SSH...\n"
#sshpass -p onioneer ssh root@192.168.3.1 "~/kehops/./kehops"
        
echo "Fermeture du tunnel SSH"

exit