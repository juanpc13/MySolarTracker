#include <Servo.h>

Servo servo1;
Servo servo2;
#define max_servo1 175          //Servo Max 180° -5°
#define min_servo1 5            //Servo Min 0° +5°
#define max_servo2 110          //Servo Max 180° -70°
#define min_servo2 55           //Servo Min 0° +55°
#define luces 7                 //Pin de las luces
int delta = 25;                 //Error de Fotoceldas
float minimo = 60.0;            //50% para activar luces
int sensor[4] = {0, 0, 0, 0};   //Arreglo de los sesores

void setup() {
  Serial.begin(115200);
  pinMode(luces, OUTPUT);
  servo1.attach(5);Serial.println("Servo1 a 90°");delay(1000);
  servo2.attach(6);Serial.println("Servo2 a 90°");delay(1000);  
}

void loop() {
  leerDatos();
  
  if (minimoLuz()) {              //Si algun sensor tiene el minimo de luz mover el panel
    digitalWrite(luces, LOW);
    moverPanel();
  } else {                        //Encender luces en vez de mover el panel
    digitalWrite(luces, HIGH);
  }

  Serial.println();
  delay(25);
}

void leerDatos() {
  for (int i = 0; i < (sizeof(sensor) / sizeof(sensor[0])) ; i++) {
    sensor[0 + i] = analogRead(A0 + i);
  }
}

boolean minimoLuz() {
  for (int i = 0; i < (sizeof(sensor) / sizeof(sensor[0])) ; i++) {
    if ((sensor[0 + i] / 1023.0) * (100) > minimo) {
      return true;
    }
  }
  return false;
}

void moverPanel() {
  moverHorizontal();
  moverVertical();
}

void moverHorizontal() {
  // 1 - 2 Y 3 - 4
  if ((sensor[0] - sensor[1]) >= delta || (sensor[3] - sensor[2]) >= delta) {
    izquierda();
  }
  // 2 - 1 Y 4 - 3
  if ((sensor[1] - sensor[0]) >= delta || (sensor[2] - sensor[3]) >= delta) {
    derecha();
  }
}

void moverVertical() {  
  // 1 - 4 Y 2 - 3
  if ((sensor[0] - sensor[3]) >= delta || (sensor[1] - sensor[2]) >= delta) {    
    arriba();
  }
  // 4 - 1 Y 3 - 2
  if ((sensor[3] - sensor[0]) >= delta || (sensor[2] - sensor[1]) >= delta) {
    abajo();
  }
}

void derecha() {
  if (servo1.read() <= max_servo1) {
    servo1.write(servo1.read() + 1);
    Serial.print("Derecha");
  }  
}

void izquierda() {
  if (servo1.read() >= min_servo1) {
    servo1.write(servo1.read() - 1);
    Serial.print("Izquierda");
  }
}

void arriba() {
  if (servo2.read() >= min_servo2) {
    servo2.write(servo2.read() - 1);    
    Serial.print("Arriba");
  }
}

void abajo() {
  if (servo2.read() <= max_servo2) {
    servo2.write(servo2.read() + 1);
    Serial.print("Abajo");
  }
}
