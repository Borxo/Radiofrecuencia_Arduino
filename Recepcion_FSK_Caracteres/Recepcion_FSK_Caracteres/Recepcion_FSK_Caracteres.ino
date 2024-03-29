/*
 Name:		Recepcion_FSK_Caracteres.ino
 Created:	09/05/2019 
 Author:	Borxo Garc�a
*/

#define data 9

float pulso = 0.00;
float Tiempo = 0;
int estado = 0;
unsigned char fin = 0b00000000;
unsigned char resultado = 0b11111111;
unsigned char ResultadoFinal = 0b11111111;
unsigned char R = 0;
int z = 0;

void setup()
{
	Serial.begin(9600);
	pinMode(data, INPUT);
	Serial.println("Receptor");
}

void loop()
{
	R = 0;
	z = 0;
	RecibirByte(); //lee si se mandan datos 

	if (pulso > 0)
	{
		while (z < 7) //Agrupa los caracteres en una variable de 8 bit 
		{
			RecibirByte();
			R = resultado;
			z++;
		}
	}

	if ((R >= 'A'&& R <= 'Z') || (R >= 'a' && R <= 'z'))  // Analiza si es un caracter valido, es decir, una letra. 
	{
		if (pulso > 0)
		{
			Serial.print((char)R); // imprime la letra 
		}
	}
	else if (R == '\r')
	{
		Serial.println("");  //Si es un intro lo omite 
	}
	if (R == ' ')
	{
		Serial.print(" ");   // Si es un espacio le pone . 
	}
}

void RecibirByte()   //Funcion de recibir el codigo. 
{
	fin = RecibirDato();
	resultado = resultado >> 1;
	resultado = (fin * 128) + resultado;
}


int RecibirDato()
{
	int dato;
	pulso = pulseIn(data, HIGH);
	Tiempo = pulso / 1000;
	// Serial.print("pulso: ");
	 //Serial.print(pulso);
	 //Serial.print("    ");
	if (Tiempo <= 1.50)
	{
		dato = 1;
	}
	else if (Tiempo >= 0.00)
	{
		dato = 0;
	}
	return dato;
}