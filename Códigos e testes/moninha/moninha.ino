#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);


 
void setup()
{
 lcd.begin (16,2);
}
 
void loop()
{
  
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.clear();
  lcd.print("Moninha!");
  delay(2000);
  lcd.setCursor(0,0);
  lcd.print("Ei, Moninhaaa!");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("**Moninha**");
  lcd.setCursor(0,1);
  lcd.print("Amo Voce!!!");
  delay(1000);

  for (int repete = 0; repete < 3; repete++)
  {
    //Rolagem para a direita
  for (int posicao = 0; posicao < 5; posicao++)
  {
    lcd.scrollDisplayRight();
    delay(200);
  }
 
  //Rolagem para a esquerda
  for (int posicao = 0; posicao < 5; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(200);
  }

  }

delay(1000);


  
}
