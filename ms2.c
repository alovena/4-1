

#define out(pin,val) digitalWrite(pin,val)


void setup()
{
	pinMode(13, OUTPUT);
	pinMode(12, OUTPUT);
}

void loop()
{
	out(13, HIGH);
	out(12, HIGH);
	delay(300); // Wait for 1000 millisecond(s)
	out(13, LOW);
	out(12, LOW);
	delay(200); // Wait for 1000 millisecond(s)
}