## Instalación

Se siguieron los pasos de la documentación para instalar con docker
```bash
sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
docker pull contiker/contiki-ng
git clone https://github.com/contiki-ng/contiki-ng.git
cd contiki-ng
git submodule update --init --recursive
```

## Configuración

Y se agregó el CNG_PATH export y el contiker alias a mi config.
```C
export CNG_PATH=$HOME/Documentos/contiki-ng
alias contiker="xhost +'local:docker@' && docker run --privileged --sysctl net.ipv6.conf.all.disable_ipv6=0 --mount type=bind,source=$CNG_PATH,destination=/home/user/contiki-ng -e DISPLAY=$DISPLAY -e LOCAL_UID=$(id -u $USER) -e LOCAL_GID=$(id -g $USER) -v /tmp/.X11-unix:/tmp/.X11-unix -v /dev/bus/usb:/dev/bus/usb -ti contiker/contiki-ng"
```


Luego cerré sesión, inicié sesión, y pude ejecutar el comando contiker.

Para iniciar cooja, ejecutar el comando `contiker cooja`