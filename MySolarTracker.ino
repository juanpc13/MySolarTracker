#include <Servo.h>

Servo servo1;
Servo servo2;
#define max_servo 175           //Servo Max 180° -5°
#define min_servo 5             //Servo Min 0° +5°
#define luces 7                 //Pin de las luces
int delta = 20;                 //Error de Fotoceldas
float minimo = 50.0;            //50% para activar luces
int sensor[4] = {0, 0, 0, 0};   //Arreglo de los sesores

void setup() {
  Serial.begin(115200);
  pinMode(luces, OUTPUT);
  servo1.attach(5);Serial.println("Servo1 a 90°");delay(2500);
  servo2.attach(6);Serial.println("Servo2 a 90°");delay(2500);  
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
  delay(100);
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
  if (servo1.read() >= min_servo && servo1.read() <= max_servo) {
    moverHorizontal();
  }
  if (servo2.read() >= min_servo && servo2.read() <= max_servo) {
    moverVertical();
  }  
}

void moverHorizontal() {
  // 1 - 2 Y 3 - 4
  if ((sensor[0] - sensor[1]) > delta || (sensor[3] - sensor[2]) > delta) {
    derecha();
  }
  // 2 - 1 Y 4 - 3
  if ((sensor[1] - sensor[0]) > delta || (sensor[2] - sensor[3]) > delta) {
    izquierda();
  }
}

void moverVertical() {
  // 1 - 4 Y 2 - 3
  if ((sensor[0] - sensor[3]) > delta || (sensor[1] - sensor[2]) > delta) {
    arriba();
  }
  // 4 - 1 Y 3 - 2
  if ((sensor[3] - sensor[0]) > delta || (sensor[2] - sensor[1]) > delta) {
    abajo();
  }
}

void derecha() {  
  servo1.write(servo1.read() + 1);
  Serial.print("Derecha");
}

void izquierda() {
  servo1.write(servo1.read() - 1);
  Serial.print("Izquierda");
}

void arriba() {
  servo2.write(servo2.read() + 1);
  Serial.print("Arriba");
}

void abajo() {
  servo2.write(servo2.read() - 1);
  Serial.print("Abajo");
}
