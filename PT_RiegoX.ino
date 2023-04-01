#include <Keypad_I2C.h>
#include<LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h>

//Direccion de los esclavos
#define I2CADDR 0x21
#define LCDADDR 0x27

char tecla;
char tiempo[4];

byte i=0;
byte x=0;
byte modo=0;
unsigned int t=0;
unsigned int tw=0;
unsigned int tm=0;

//CONFIGURACION DEL TECLADO
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char teclas[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
// Pines PCF8574 I/O
byte rowPins[ROWS] = {4, 5, 6, 7};
byte colPins[COLS] = {0, 1, 2, 3};

TwoWire *jwire = &Wire;   //test passing pointer to keypad lib
Keypad_I2C teclado( makeKeymap(teclas), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574, jwire );
//Keypad_I2C kpd( makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR );

LiquidCrystal_I2C lcd (LCDADDR, 2, 1, 0, 4, 5, 6, 7); // DIR, E, RW, RS, D4, D5, D6, D7

void setup(){
  
//  Wire.begin( );
  jwire->begin( );
//  kpd.begin( makeKeymap(keys) );
  teclado.begin( );
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.begin(16,2);
  lcd.clear();
  hola();
  delay(5000);
  menu_modo();
  
  //menuprincipal();
  
}
void rst(){
lcd.clear();
tiempo[0]='0';tiempo[1]='\0';tiempo[2]='\0';
i=0;t=0;tm=0;x=0;
}

void menuprincipal(){
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Riego:");
lcd.setCursor(11,0);
lcd.print("[min]");
lcd.setCursor(0,1);
lcd.print("Clc[*]     Ok[#]");
}

void prueba()
{lcd.clear();
lcd.setCursor(0,0);
lcd.print("Prueba OK");}
void prueba1()
{lcd.clear();
lcd.setCursor(0,0);
lcd.print("Prueba 1 OK");}

void modowifi()
{lcd.clear();
lcd.setCursor(0,0);
lcd.print("En desarrollo");
lcd.setCursor(0,1);
lcd.print("Adios popo :)");
delay(2000);}

void hola(){
lcd.setCursor(0,0);
lcd.print("Xochitla Riego");
lcd.setCursor(0,1);
lcd.print("    By Pt <3 ...");}


void menu_modo(){
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Manual[A]WiFi[B]");
lcd.setCursor(0,1);
lcd.print("Estado WiFi  [C]");}


void menu_confirmar(){
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Tiempo: ");
lcd.setCursor(0,1);
lcd.print("<-- [*]");
lcd.setCursor(8,1);
lcd.print("Regar[#]");
lcd.setCursor(8,0);
lcd.print(tiempo);
lcd.print("min");
}

void confirmar(){
menu_confirmar();
x=0;
while (x==0){
    delay(100);
    tecla=teclado.getKey();
      if (tecla){
        if (tecla=='*'&&modo==1){
          rst();
          manual1();
        }
        }
   }

}

//control de tiempo 
void twifi(){}

void tmanual(){}

void tiempot(){}
//----------------

void manual1(){
  menuprincipal();
  while (x==0){
    delay(100);
    tecla=teclado.getKey();
      if (tecla){
        if (tecla == '#'){
          x=1;
          confirmar();}
        else if (i>2||tecla == '*'&&tecla!='#'){rst();menuprincipal();}
        else if(tecla!='A'&&tecla!='B'&&tecla!='C'&&tecla!='D'&&tecla!='#'){
        lcd.setCursor(i+8,0);
        lcd.print(tecla);
        tiempo[i]=tecla;
        i++;}
      
       }
    }
  }

void loop(){

tecla=teclado.getKey();

if (tecla){
  //modo manual
  if (tecla == 'A'){
    modo=1;    
    manual1();
  }
  //modo wifi
  else if(tecla == 'B'){
    modo=2;
    modowifi();
    confirmar();
  }
}



  
}
