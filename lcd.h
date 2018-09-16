
void Lcd_Port(char a)
{
	if(a & 1)
		RB4 = 1;
	else
		RB4 = 0;

	if(a & 2)
		RB5 = 1;
	else
		RB5 = 0;

	if(a & 4)
		RB6 = 1;
	else
		RB6 = 0;

	if(a & 8)
		RB7 = 1;
	else
		RB7 = 0;
}


void Lcd_Cmd(char a)
{
	RB0 = 0;             // => RB0 = 0
	Lcd_Port(a);
	RB1  = 1;             // => E = 1
        __delay_ms(4);
        RB1  = 0;             // => E = 0
}

void Lcd_Clear()
{
	Lcd_Cmd(0);
	Lcd_Cmd(1);
}

void Lcd_Set_Cursor(char a, char b)
{
	char temp,z,y;
	if(a == 1)
	{
	  temp = 0x80 + b - 1;
		z = temp>>4;
		y = temp & 0x0F;
		Lcd_Cmd(z);
		Lcd_Cmd(y);
	}
	else if(a == 2)
	{
		temp = 0xC0 + b - 1;
		z = temp>>4;
		y = temp & 0x0F;
		Lcd_Cmd(z);
		Lcd_Cmd(y);
	}
}

void Lcd_Init()
{
  Lcd_Port(0x00);
   __delay_ms(20);
  Lcd_Cmd(0x03);
	__delay_ms(5);
  Lcd_Cmd(0x03);
	__delay_ms(11);
  Lcd_Cmd(0x03);
  /////////////////////////////////////////////////////
  Lcd_Cmd(0x02);
  Lcd_Cmd(0x02);
  Lcd_Cmd(0x08);
  Lcd_Cmd(0x00);
  Lcd_Cmd(0x0C);
  Lcd_Cmd(0x00);
  Lcd_Cmd(0x06);


}

void Lcd_Write_Char(char a)
{
   char temp,y;
   temp = a&0x0F;
   y = a&0xF0;
   RB0 = 1;             // => RB0 = 1
   Lcd_Port(y>>4);             //Data transfer
   RB1 = 1;
   __delay_us(40);
   RB1 = 0;
   Lcd_Port(temp);
   RB1 = 1;
   __delay_us(40);
   RB1 = 0;
}

void Lcd_Write_String(char *a)          //Arraimizdeki charı \n görene kadar ekrana yaz
{
	int i;
	for(i=0;a[i]!='\0';i++)
	   Lcd_Write_Char(a[i]);
}
