# Practicas-SO


Practicas del curso de sistemas operativos 2022-1.

Integrantes:
- Juan Jose Figueroa - jufigueroap@unal.edu.co
- Eduards Mendez - emendezc@unal.edu.co
- David Felipe Mora - dmorara@unal.edu.co

## **Practica 1 - P1**

El programa gestiona información de viajes de Uber-Movement, especificamente, le permite al usuario consultar el tiempo medio de un viaje 
con base a ciertos criterios basicos del mismo.

Antes de ejecutar el programa, es necesario descargar e indexar el archivo de viajes:

1. Descomprimir el archivo `rides.zip` que se encuentra en la carpeta data.
2. Compilar el programa de preprocesamiento, para lo cual debe ir a la capeta preprocess. Este se realiza al ejecutar el comando `make`.
3. Ejecutar `preprocess_data` para generar el archivo binario de estructuras.
4. Remover los archivos innecesarios mediante el comando `make clean`

**Ejecución del programa:**

1. En la carpeta P1, compilar los archivos del programa ejecutando el comando `make`.
2. Lanzas el proceso `menu` en una terminal y el proceso `search` en otra terminal.


## **Inter Process Communication**

En la caperta `IPC` se encuentran unos programas que prueban distintas tecnicas de comunicación entre procesos, especificamente:
- Memoria compartida
- Archivos
- Tuberias(Nombradas y No nombradas)
- Paso de mensajes(Sockets)

Para realizar las pruebas se debe ejecutar el script de bash mediante el comando:

`bash run.sh`