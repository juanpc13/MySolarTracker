# MySolarTracker
Proyecto de un seguidor de la luz con 4 fotoceldas para maximizar la eficiencia del panel solar, tambien se agregaron 6 diodos led que encenderan cuando la iluminación este en el minimo de porcentaje luz supere de las 4 fotoresistencias usando un mosfet-N channel

Editar variables del codigo segun las necesidades
```c++
#define max_servo1 175          //Servo Max 180° -5°
#define min_servo1 5            //Servo Min 0° +5°
#define max_servo2 110          //Servo Max 180° -70°
#define min_servo2 55           //Servo Min 0° +55°
#define luces 7                 //Pin de las luces
int delta = 25;                 //Error de Fotoceldas
float minimo = 60.0;            //50% para activar luces
int sensor[4] = {0, 0, 0, 0};   //Arreglo de los sesores
```

# 1-Diagrama

![PROFIT!](/diagrama.png)

# 2-Diagrama y Conexiones

![PROFIT!](/posiciones.png)
![PROFIT!](/conexiones.png)

