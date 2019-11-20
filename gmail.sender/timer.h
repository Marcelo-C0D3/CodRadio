extern "C"{
#include "user_interface.h"
}

os_timer_t mTimer1;
os_timer_t mTimer2;
os_timer_t mTimer3;

bool       _timeout1 = false;
bool       _timeout2 = false;
bool       _timeout3 = false;

int X = 25000;
int chargingT = 10000;
int valor_AD = 0;
int soma = 0;
int soma1 = 0;
int i = 0;
int x = 0;
double media = 0;
double media1 = 0;
String subject = " ";
String assunto = " ";
String e_mail = " ";
int state = 0;

void tCallback1(void *tCall){
    _timeout1 = true;
}

void tCallback2(void *tCall){
    _timeout2 = true;
}

void tCallback3(void *tCall){
    _timeout3 = true;
}


void usrInit(void){
    os_timer_setfn(&mTimer1, tCallback1, NULL);
    os_timer_setfn(&mTimer2, tCallback2, NULL);
    os_timer_setfn(&mTimer3, tCallback3, NULL);
    os_timer_arm(&mTimer1, X , true);
    os_timer_arm(&mTimer2, X , true);
    os_timer_arm(&mTimer3, chargingT , true);
}

void reset_timer1 (void) {
  os_timer_arm(&mTimer1, X , true);
}
void reset_timer2 (void) {
  os_timer_arm(&mTimer2, X , true);
}

void config_setup (){
  pinMode(D5, OUTPUT);
  pinMode(A0, INPUT);
  Serial.println();
  //iniciar a interrupcao
  usrInit();

}
