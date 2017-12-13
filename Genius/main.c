#include "msp430g2553.h"
#include "ad.h"
#include "lcd.h"
#include "timerPWM.h"
#include <stdlib.h>

#define amarelo_on P1OUT = P1OUT | BIT4;
#define amarelo_off P1OUT = P1OUT & (~ BIT4); 

#define vermelho_on P1OUT = P1OUT | BIT5; 
#define vermelho_off P1OUT = P1OUT & (~ BIT5); 

#define seg 2000000

#define A0 INCH_0
#define A1 INCH_1

unsigned long int aux; 
unsigned int tensao;
unsigned int p1,p2;
unsigned char pontuacao = 0, sair;
unsigned int nivel, aleatorio,verCores[10], i, j,cor,periodo,ton;	

unsigned int converte(unsigned int valor)
{   
    
    aux = valor;
    aux = aux*3300;
    aux = aux/1023;
    tensao = (unsigned int) aux;
    
    return tensao;
    
}

void lerPoten()
{
  
  p1 = LeAD(A0);
  p1 = converte(p1);
  
  p2 = LeAD(A1);
  p2 = converte(p2);
  
}

void piscaAmarelo(){
  
  amarelo_on;
  
  __delay_cycles(seg);
  
  amarelo_off;
 
  __delay_cycles(seg);
  
 }

void piscaVermelho(){
    
  vermelho_on;
  
  __delay_cycles(seg);
  
  vermelho_off;
 
  __delay_cycles(seg);
    
} 

void acertou(){
  
   periodo = 10000; 
   ton = 10000; 
   ConfigPWM(periodo);      

     AtualizaTonPWM(ton);
    __delay_cycles(100000);
     AtualizaTonPWM(0);
    __delay_cycles(100000);
    AtualizaTonPWM(ton);
    __delay_cycles(100000);
    AtualizaTonPWM(0);
    __delay_cycles(100000);

}

void errou(){
  
    periodo = 20000; 
    ton = 10000; 
    ConfigPWM(periodo);      

    AtualizaTonPWM(ton);
     __delay_cycles(1000000);
    AtualizaTonPWM(0);
    __delay_cycles(100000);
  
}
     
int main(){
	
    WDTCTL=WDTHOLD+WDTPW;
    
    P2SEL=0;
    P2SEL2=0;

    P2REN |= BIT6; 
    
    P2IES |= BIT6; 
    
    P2IFG &= ~BIT6;
    
    P2IE |= BIT6; 
  
    P1DIR=BIT4+BIT5;
    
    P1REN=BIT0+BIT1; 
    P1OUT=BIT0+BIT1;
    
    P1OUT &=~(BIT4+BIT5);
    
    InitLCD(); 
    
    ConfigAD(BIT0);
    ConfigAD(BIT1);   
    
    LCDPrintXYStr(1,1,"                "); 
    LCDPrintXYStr(1,2,"                "); 

    _BIS_SR(GIE);
    
    for(;;){
      
      LCDPrintXYStr(1,1,"Bem-vindo!");
      LCDPrintXYStr(1,2,"Genius");
      
      __delay_cycles(seg);
      
      LCDPrintXYStr(1,1,"                "); 
      LCDPrintXYStr(1,2,"                "); 
      
      for(i=0;i<2;i++)
      {
          verCores[i]=10;
      }
      
      pontuacao = 0;
      
      nivel = 0;
      
      do{
          
        cor = 10;
                     
        aleatorio = rand() % 2;  

        verCores[nivel] = aleatorio;
                    

          for(i=0; i<nivel+1; i++){
              
              __delay_cycles(seg);
                              
              if(verCores[i]==0)
                  piscaAmarelo();
              else if(verCores[i]==1)
                  piscaVermelho();  
                                                   
           }

                            
            for(j=0;j<nivel+1;j++)
            {
              
                LCDPrintXYStr(1,1,"Entre com a");
                LCDPrintXYStr(1,2,"Cor nº: ");
                LCDPrintVal(j+1);
                
                __delay_cycles(7000000);
                lerPoten();
                                        
                if(p1 <= 500)
                {
                  cor = 0;
                  
                }
                else if(p2 <= 2800)
                {
                  
                  cor = 1;
                  
                }
                else
                {
                  cor = 10;
                  
                }
                
                
                LCDPrintXYStr(1,1,"                "); 
                LCDPrintXYStr(1,2,"                ");
                              
                if(verCores[j]==cor){                      
                                    
                  pontuacao = pontuacao + 10;           
                  
                   acertou();
                   
                   LCDPrintXYStr(1,1,"Acertou!!");
                   LCDPrintXYStr(1,2,"Pontos: ");
                   LCDPrintVal(pontuacao);

                   __delay_cycles(seg);
                   
                   LCDPrintXYStr(1,1,"                "); 
                   LCDPrintXYStr(1,2,"                "); 
                   
                }else{
                    
                   errou();
                   
                   LCDPrintXYStr(1,1,"Errou a cor!!");
                   LCDPrintXYStr(1,2,"Pontos: ");
                   LCDPrintVal(pontuacao);

                  sair = 1;
                  j = nivel;
                  
                  __delay_cycles(seg);
                            
                   LCDPrintXYStr(1,1,"                "); 
                   LCDPrintXYStr(1,2,"                "); 
                            
                 }
                
            }
          
             nivel++;
          
            __delay_cycles(100000);
            
            if(sair != 1 && nivel < 10){
                                    
              LCDPrintXYStr(1,1,"Nivel: ");
              LCDPrintVal(nivel);
              LCDPrintXYStr(1,2,"                "); 
              
                   
              __delay_cycles(seg);
              
              LCDPrintXYStr(1,1,"                "); 
                                            
            }
               
            __delay_cycles(100000);
            
      }while(sair != 1 && nivel<10);
               
       LCDPrintXYStr(1,1,"Fim de jogo!!");
       LCDPrintXYStr(1,2,"Pontos: ");
       LCDPrintVal(pontuacao);
    
       __delay_cycles(5000000);
      
                  
       LCDPrintXYStr(1,1,"                "); 
       LCDPrintXYStr(1,2,"                "); 
   }
}
      
#pragma vector=PORT2_VECTOR
__interrupt void funcao_pause (void)
{
  _BIC_SR(GIE);               
  
  LCDPrintXYStr(1,1,"Pause           ");
  LCDPrintXYStr(1,2,"                ");
  
  while((P2IN&BIT6)==0x00) { }  
  __delay_cycles(100000); 
  
  while((P2IN&BIT6)==BIT6) { } 
  __delay_cycles(100000); 
  
   P2IFG&=~BIT6;
   _BIS_SR(GIE); 
   
   LCDPrintXYStr(1,1,"                ");
   LCDPrintXYStr(1,2,"                "); 
   
}
 
