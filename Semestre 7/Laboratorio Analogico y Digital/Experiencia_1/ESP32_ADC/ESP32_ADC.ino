// Creamos un objeto UART usando el puerto hardware 2 del ESP32
HardwareSerial UART(2);


// ----------------------------------------------------
// Función que convierte un número decimal a BCD
// Formato: 2 dígitos enteros + 2 decimales
// Ejemplo: 1.23 → 0000 0001 0010 0011
// ----------------------------------------------------
uint16_t convertirBCD(float valor){

  int x = valor * 100;   // convertimos a entero con 2 decimales

  // extraemos cada dígito
  int d1 = (x / 1000) % 10;   // decena entera
  int d2 = (x / 100) % 10;    // unidad entera
  int d3 = (x / 10) % 10;     // primera decimal
  int d4 = x % 10;            // segunda decimal

  // empaquetamos en 16 bits BCD
  uint16_t BCD = (d1<<12) | (d2<<8) | (d3<<4) | d4;

  return BCD;
}



void setup(){

  // Inicializa puerto serial USB para debug
  Serial.begin(115200);

  // Inicializa UART2
  // formato: baudrate, formato de bits, RX pin, TX pin
  UART.begin(9600, SERIAL_8N1, 16, 17);

  // GPIO17 = TX hacia FPGA
  // GPIO16 = RX (no usado)
}



void loop(){

  // ---------------------------------
  // 1) Leer señal analógica
  // ---------------------------------
  int adc = analogRead(35);  // ADC del pin 35

  // Convertimos a voltaje
  float voltaje = adc * 3.3 / 4095.0;



  // ---------------------------------
  // 2) Calcular valores que queremos enviar
  // ---------------------------------

  float V = 3.0 - voltaje;      // señal invertida

  float V2 = V / 0.471 + 3;     // transformación pedida



  // ---------------------------------
  // 3) Convertir ambos valores a BCD
  // ---------------------------------

  uint16_t BCD1 = convertirBCD(V);
  uint16_t BCD2 = convertirBCD(V2);



  // ---------------------------------
  // 4) Separar los 16 bits en bytes
  // ---------------------------------

  uint8_t datos[4];

  datos[0] = BCD1 >> 8;   // byte alto del primer número
  datos[1] = BCD1 & 0xFF; // byte bajo del primer número

  datos[2] = BCD2 >> 8;   // byte alto del segundo número
  datos[3] = BCD2 & 0xFF; // byte bajo del segundo número



  // ---------------------------------
  // 5) Enviar los 4 bytes por UART
  // ---------------------------------

  UART.write(datos,4);

  // UART enviará automáticamente:
  // START + 8 bits + STOP para cada byte



  // ---------------------------------
  // 6) Mostrar valor en Serial Monitor
  // ---------------------------------
  //Serial.println(V,3);

  // Para ver SOLO V2 en el Serial Plotter
  //Serial.println(V2,3);


  // pequeño delay para no saturar la transmisión
  //delay(1);
}
