# Servidor 


Practica del curso de sistemas operativos 2022-1.

Integrantes:
- Juan Jose Figueroa - jufigueroap@unal.edu.co
- Eduards Mendez - emendezc@unal.edu.co
- David Felipe Mora - dmorara@unal.edu.co

## **Manual de uso**

El programa gestiona información de viajes de Uber-Movement, especificamente, le permite al usuario consultar el tiempo medio de un viaje 
con base a ciertos criterios basicos del mismo.

Antes de ejecutar el programa, es necesario descargar e indexar el archivo de viajes:

1. Descomprimir el archivo `rides.zip` que se encuentra en la carpeta data.
2. Compilar el programa de preprocesamiento, para lo cual debe ir a la capeta `Server`. Este se realiza al ejecutar el comando `make preprocess`.
3. Ejecutar `preprocess_data` para generar el archivo binario de estructuras.
4. Remover los archivos innecesarios mediante el comando `make clean`

Tambien es necesario asegurarse de tener instalada la libreria ncurses. Se adjunta guia de como hacerlo en caso contrario. (https://www.cyberciti.biz/faq/linux-install-ncurses-library-headers-on-debian-ubuntu-centos-fedora/)

**Ejecución del programa:**

1. En la carpeta `Server`, compilar los archivos del programa ejecutando el comando `make`.
2. Lanzar el proceso `menu` en una terminal y el proceso `server` en otra terminal.

## **Informe de elaboración**

- `p2-server.c`
    El servidor se encarga de cargar los datos, recibir las peticiones de los clientes y devolver la información pertinente a los mismo.
    - `int main()`
    El flujo del programa es el siguiente:
        - Abrir los archivos indexados de los datos de busqueda: `rides.bin`, `source_id_table.bin` que se encuentran en la carpeta `data`. También se abre el archivo log `x.log`.
        - Declarar las variables de busqueda y sockets.
        - Crear el socket con `socket()`.
        - Configurar el socket con `setsockopt()` y `bind()`.
        - Poner el socket como servidor con `listen()`.
        - Recibir peticiones de los clientes mediante `accept()`.
        - Una vez se ha establecido la conexión con un cliente, se leeran los datos de busqueda con `read()`.
        - Realizar la busqueda indexada en los archivos binarios.
        - Almacenar el tiempo de viaje medio en `avg_travel_time` o -1 si no se encontró ningun viaje.
        - Enviar el tiempo de viaje con `send()`.

- `p2-client.c`
