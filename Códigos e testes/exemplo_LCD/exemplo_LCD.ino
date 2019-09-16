#include <LiquidCrystal_I2C.h>


#include <Wire.h> 


LiquidCrystal_I2C lcd(0x3F,16,2);

void setup()
{
  lcd.begin(16,2);
}
void loop()
{lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Te amo, Moninha!");
  delay(1500);

//Rolagem para a esquerda
  for (int posicao = 0; posicao < 4; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
  }

  //Rolagem para a direita
  for (int posicao = 0; posicao < 8; posicao++)
  {
    lcd.scrollDisplayRight();
    delay(300);
  }

  for (int posicao = 0; posicao < 4; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
   }


}
