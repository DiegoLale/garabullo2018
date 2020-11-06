// la función limpia_eeprom() busca en las posiciones reservadas a los records
// valores de 255 que son los que están al principio en estas posiciones si no se han usado
// De la posición 10 hasta la 29
// si hay un valor diferente no lo cambia
// la variable pasada como argumento "forzado" si es 1 es porque desde el menú de ajustes se fuerza a borrar
void limpia_eeprom(boolean forzado)
{
  for (int i = 10; i < 30; i++)
  if (EEPROM.read(i) == 255 || forzado) 
  {
    EEPROM.write(i, 0);
  }
  if (EEPROM.read(0) == 255) // posición de sonido activado, si es la primera vez que se usa se activa, si no se deja como está
  {
    EEPROM.write(0, 1);
  }
  if (EEPROM.read(1) == 255) // posicion de pasos recto
  {
    EEPROM.write(1, 78);// por defecto arranca en 77
  }
  if (EEPROM.read(2) == 255) // posicion de pasos giro
  {
    EEPROM.write(2, 54);// por defecto arranca en 53
  }
  
  pasos_recto = EEPROM.read(1);
  pasos_giro = EEPROM.read(2);
}
void cuenta_atras(int segundillos_y_eso)
{
  apaga_leds(1);
  pantalla.fillScreen(CYAN);
  pantalla.fillRoundRect(10,10,108,108,5, AMARILLO);
  pantalla.setTextSize(8);
  pantalla.setTextColor(NEGRO);
  while(segundillos_y_eso)
  {
  pantalla.setCursor(45, 40);
  pantalla.print(segundillos_y_eso);
  delay(600);
  pantalla.fillRoundRect(10,10,108,108,5, AMARILLO);
  segundillos_y_eso -= 1;
  }
  pantalla.fillScreen(NEGRO);
}


// Posiciones de eeprom
/*
 * EEPROM 0 SONIDO ACTIVADO
 * EEPROM 1 PASOS_RECTO
 * eePROM 2 PASOS_GIRO
 * EEPROM 11 MAGIC TILES 1
 * EEPROM 12 MAGIC TILES 2
 * EEPROM 13 SUMA VERDADERO FALSO
 * EEPROM 14 SIMON
 * EEPROM 15 PRODUCTO
 * 
 * 
 * 
 * 
 */

 void final(int puntuacion, int colores)
{
  //ole();
  apaga_leds(0);
  led.setPixelColor(8, led.Color(brillo, 0, 0));
  led.show();
  pantalla.fillScreen(ST7735_BLACK);
  pantalla.setCursor(0, 0);
  pantalla.setTextSize(3);
  pantalla.setTextColor(ST7735_WHITE, ST7735_BLUE);
  pantalla.print(" PUNTOS");
  pantalla.setTextColor(ST7735_WHITE);
  pantalla.print("    ");
  pantalla.print(puntuacion);
  if (puntuacion >= EEPROM.read(colores + 10 - 1)) // testea si hay record nuevo
  {
    pantalla.setCursor(0, 60);
    pantalla.setTextSize(3);
    pantalla.setTextColor(ST7735_WHITE, ST7735_GREEN);
    pantalla.print("!RECORD NUEVO!");
    EEPROM.write(colores + 10 - 1 , puntuacion);
  }
  pantalla.setCursor(80, 110);
  pantalla.setTextSize(1);
  pantalla.setTextColor(ROJO);
  pantalla.print("SALIR");
  boolean salida = 0;
  while (!salida)
  {
    test_alive();
    byte boton = boton_pulsado();
    switch (boton)
    {
      case 8:
        salida = 1;
        break;
    }
  }
}
