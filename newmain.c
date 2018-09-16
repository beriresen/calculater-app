
#define _XTAL_FREQ 4000000            //osilatör hızını belirledim.

#include <xc.h>
#include "lcd.h";                    //Lcd kullanabilmek icin lcd.h kutuphanemi yukledim.
#include <stdio.h>                   //sprint fonskiyonumu kullanabilmek icin stdio.h kutuphanemi yukledim.

#pragma config FOSC = XT            //4Mhz=XT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config CP = OFF


#define t1 PORTAbits.RA4        // Button pinlerimi tanimliyorum.
#define t2 PORTAbits.RA3
#define t3 PORTAbits.RA2
#define t4 PORTAbits.RA1
#define t5 PORTAbits.RA0

int main()
{
  TRISB = 0x00;                  //cikisi belirledim.B lcd ye bagli data gonderdiğim icin cikis
  TRISB2 = 1;                    //push button input olduğu icin 1dir.
  TRISA = 0xFF;                  //Butonlarımızın bagli olduğu register.Butonlari input yaptik.

  Lcd_Init();                   // Lcd mi initialize ediyorum.(haberlesme protokolü)
  Lcd_Clear();                 // lcd mi temizliyorum

  int x1;                       //girecegğim 5 bitlik 1. sayi
  int x2;                       //girececim 5 bitlik 2. sayi
  char str[10];                 //bilgileri koyabilecegim array(buffer).

    while(1)
    {
        if(PORTBbits.RB2){                              //pushbutton a basildiginda
            x1 = t1<<4 | t2<<3 | t3<<2 | t4<<1 | t5;    // sayimi uretiyorum

            sprintf(str,"1. = %d",x1);                 // sayimi formatliyorum bufferimdan ekrana aktariyorum.
            Lcd_Set_Cursor(1,1);                       // Lcd mdeki lokasyon.
            Lcd_Write_String(str);                     //buferima attigim değeri yazdiriyorum Lcdme.

            __delay_ms(1600);

            while(!PORTBbits.RB2);
            x2 = t1<<4 | t2<<3 | t3<<2 | t4<<1 | t5;


            sprintf(str,"2. = %d",x2);
            Lcd_Set_Cursor(1,8);
            Lcd_Write_String(str);


            Lcd_Set_Cursor(2,1);

                                                            // toplama
            sprintf(str,"%d",x1+x2);
            Lcd_Write_String(str);

                                                           // cikarma
            sprintf(str," : %d",x1-x2);
            Lcd_Write_String(str);

                                                          // carpma
            sprintf(str," : %d",x1*x2);
            Lcd_Write_String(str);

            __delay_ms(9000);                           //ekranda sonucun gorulme süresi

            Lcd_Clear();

        }
    }

  return 0;
}
