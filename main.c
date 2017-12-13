#include <msp430.h>
#include <msp430f5529.h>
#include <stdio.h>
#include "lcd16.h"

//Declaração de variaveis globais
unsigned int entrada; // valor que o profissional vai entrar
volatile int estado; // define os estados dos 
//Corrigir variaveis globais 

// Connections LCD
//P1.0 - D4 Pin11
//P1.1 - D5 Pin12
//P1.2 - D6 Pin13
//P1.3 - D7 Pin14
//P1.4 - RS Pin4
//P1.5 - R/W Pin5
//P1.6 - E Pin6

//Função para comunicação serial
void UCA0init(void)
{
  UCA0CTL1 = 0x81;	// Usa SMCLK; UART desativada
  UCA0CTL0 = 0;		// Configura 8n1
  P3SEL = 0x30;		// Bita 4 e 5 da P3:  USCI_A0 TXD/RXD
  UCA0BR1 = 0;
  UCA0BR0 = 104;		// Valores para 9600 Baud
  UCA0MCTL = 0x31;
  UCA0CTL1 = 0x80;	// Reativa UART
}

// Nao sei porque eu peguei essa função, tenho que lembrar
unsigned int converte(unsigned int valor)
{
  int aux, tensao;
  aux = valor;
  aux = aux*3300;
  aux = aux/65535; // 2 elevado 16
  tensao = (unsigned int) aux;
  return tensao;
    
}
//função que tira a media de 10 amostras da entrada analogica
float media(float valor)
{
  int cont = 10;
  float media;
  float soma = 0;
  
  while(cont--)
  {
    soma = soma + valor;
  }
  cont = 10;
  
  media = (soma/cont);
  
  return media;
}

int definicao_de_estados(float aux)
{
  int estado;
  if (aux < 1)
  {
    // habilita a interrupção
    //sistema errado
    estado = 0;
  }
  else if(aux < (1+(0.0796*1)))
  {
    estado = 1;
  }
  else if(aux < (1+(0.0796*2)))
  {
    estado = 2;
  }
  else if(aux < (1+(0.0796*3)))
  {
    estado = 3;
  }
  else if(aux < (1+(0.0796*4)))
  {
    estado = 4;
  }
  else if(aux < (1+(0.0796*5)))
  {
    estado = 5;
  }
    else if(aux < (1+(0.0796*6)))
  {
    estado = 6;
  }
    else if(aux < (1+(0.0796*7)))
  {
    estado = 7;
  }
    else if(aux < (1+(0.0796*8)))
  {
    estado = 8;
  }
    else if(aux < (1+(0.0796*9)))
  {
    estado = 9;
  }
    else if(aux < (1+(0.0796*10)))
  {
    estado = 10;
  }
    else if(aux < (1+(0.0796*11)))
  {
    estado = 11;
  }
    else if(aux < (1+(0.0796*12)))
  {
    estado = 12;
  }
    else if(aux < (1+(0.0796*13)))
  {
    estado = 13; //é o estado fixo na saida do paciente
  }
    else if(aux < (1+(0.0796*14)))
  {
    estado = 14;
  }
    else if(aux < (1+(0.0796*15)))
  {
    estado = 15;
  }
    else if(aux < (1+(0.0796*16)))
  {
    estado = 16;
  }
    else if(aux < (1+(0.0796*17)))
  {
    estado = 17;
  }
    else if(aux < (1+(0.0796*18)))
  {
    estado = 18;
  }
    else if(aux < (1+(0.0796*19)))
  {
    estado = 19;
  }
    else if(aux < (1+(0.0796*20)))
  {
    estado = 20;
  }
    else if(aux < (1+(0.0796*21)))
  {
    estado = 21;
  }
    else if(aux < (1+(0.0796*22)))
  {
    estado = 22;
  }  
    else if(aux < (1+(0.0796*23)))
  {
    estado = 23;
  }
    else if(aux < (1+(0.0796*24)))
  {
    estado = 24;
  }
    else if(aux < (1+(0.0796*25)))
  {
    estado = 25;
  }
    else if(aux >= (1+(0.0796*5)))
  {
    estado = 26; //habilita interrupção
  }
  return estado;
}
int atualiza_valvula( int limite, int estado)
{
  if(estado < limite)
  {
    estado++;
  }
  if (estado == limite)
  {
    estado = limite;
  }
  if (estado > limite)
  {
    estado--;
  }
  return estado;
}

//controle da valvula para a saida do gas no paciente
float controle_valvula(int estado)
{
  float saida;
  switch(estado)
  {
  case 0: saida = 0;
  // colocar o valor na saida da porta analogica 2, em tensão
  //fazer o circuito que irá converter tensao em corrente para valvula mdpro
    break;
  case 1: saida = ; //conversao do 
    break;
  case 2: saida = VALOR_ANALOGICO_DO_GRAFICO(0); 
    break;
  case 3: saida = VALOR_ANALOGICO_DO_GRAFICO(0); 
    break;
  case 4: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 5: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 6: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 7: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 8: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 9: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 10: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 11: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 12: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 13: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 14: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 15: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 16: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 17: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 18: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 19: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 20: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 21: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 22: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 23: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 24: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  case 25: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
  default: saida = VALOR_ANALOGICO_DO_GRAFICO(0);
    break;
}
  return saida; // retornar o valor da valvula
}

int main( void )
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer to prevent time out reset
    
    //Declaração de variaveis
    volatile unsigned int i; // nao sei porque eu coloquei essa variavel, tenho que lembrar
    float valor_atual_com_media; //pega os valores das medias da variação do fluxo
    int estado_atual;
    int sistema_ligado = 0;
    int porcentagem_oxig = 50;
    int porcentagem_nitro;
    int estado_atual_oxig;
    int estado_atual_nitro;
    float valor_nitro;
    float valor_atual_oxig;
    float valor_oxig;
    float valor_atual_nitro;
    unsigned int limite_oxig;
    unsigned int limite_nitro;
    float valor_valvula;
    static unsigned int valor = 0; //pega os valores do leitor analogico
    
    //Configurando o led que indica que ligou o sistema
    P1DIR=0x01; //Define o Port 1 bit 0 como saida
    
    //Configurando o led que indica que está fazendo leitura
    P4DIR=0x07; //Define o porta 4 como saida
    
    //Configurando o led que indica interrupção
    P1DIR = 0x00;
    
    //Configurando os botoes de porcentagem
    P2REN |= 0x05; //Ativa o resistor no P2.5
    P2OUT = 0x05; // Ajuste o resistor para puxar para cima
    P2REN |= 0x04; //Ativa o resistor no P2.4
    P2OUT = 0x04; //Ajuste o resistor para puxar para cima
    
    
    //Confirmar a porcentagem e iniciar o sistema
    P2REN |= 0x02; // Ativar resistor na P2.1
    P2OUT = 0x02; // Ajuste o resistor para puxar para cima 
    
    //Configurando a interrupção no pino P2.3 botao
    P2SEL = 0; 
    P2DIR = 0; 
    P2IES = 1; 
    P2IFG = 0; 
    P2IE = 1;
    __enable_interrupt ();
    
    //Condiguração da parte de leitura analogica
    ADC12CTL0 = ADC12SHT02 + ADC12ON;         // Sampling time, ADC12 on
    ADC12CTL1 = ADC12SHP;                     // Use sampling timer
    ADC12IE = 1;                           // Enable interrupt
    ADC12CTL0 |= ADC12ENC;
    P6SEL = 0x0F;                             // Enable A/D channel inputs
    ADC12CTL0 = ADC12ON+ADC12MSC+ADC12SHT0_8; // Turn on ADC12, extend sampling time
                                            // to avoid overflow of results
    ADC12CTL1 = ADC12SHP+ADC12CONSEQ_3;       // Use sampling timer, repeated sequence
    ADC12IE = 0x08;                           // Enable ADC12IFG.3
    ADC12CTL0 |= ADC12ENC;                    // Enable conversions
    ADC12CTL0 |= ADC12SC;                     // Start convn - software trigger
    
    //Configura o clock para usar o cristal externo para gerar MCLK
    
    //Configura a comunicação serial
    UCA0CTL1 = 0x81;	// Usa SMCLK; UART desativada
    UCA0CTL0 = 0;		// Configura 8n1
    
    
    //LCD tem que arrumar
    
    while(sistema_ligado!=1)
    {
      
      if (! (P2IN & 0x05))
      {
        porcentagem_oxig++;
        __delay_cycles(100);
      }
      if (!(P2IN & 0x04))
      {
        porcentagem_oxig--;
        __delay_cycles(100);
      }
    }
    
    //inicializacao
    if (! (P2IN & 0x02)) //Se o botão pressionar P2.2 for pressionado 
    {
      P4OUT=1; //aciona o Led
      sistema_ligado= 1;
      porcentagem_nitro = 100 - porcentagem_oxig;
      
      //converter a porcentagem em fluxo, de 0 a 25, tem que fazer testes 
      limite_oxig = ;
      limite_nitro = ;
    }
    
    while(sistema_ligado)
    {
      //Saida da mascara
      ADC12CTL0 |= ADC12SC;                   // Start sampling/conversion
      
      //Entrada analogica (sensor) P6.0
      valor = ADC12MEM0;           // Move A0 results, IFG is cleared
      valor_atual_com_media = media(valor);
      
      //LCD tem que arrumar
      
      // Começa a conversão
      estado_atual = definicao_de_estados(valor_atual_com_media); //sensor da saida final
      valor_valvula = controle_valvula(estado_atual);
      //Aciona o pino que vai para valvula
      //Na entrada do P6.1 mandar o valor analogico para acionar a valvula
      estado_atual = atualiza_valvula(13,estado_atual);
      valor_valvula = controle_valvula(estado_atual); //saida final do paciente 13 litros por minutos
      //Na entrada do P6.1 mandar o valor analogico (valor_analogico) para acionar a valvula
      
      //Saida do oxigenio
      //Definir o fluxo de acordo com a porcentagem
      //Entrada analogica (sensor) P6.2 
      valor_oxig = ADC12MEM2;           // leitura da entrada analogica P6.2
      valor_atual_oxig = media(valor_oxig);
      estado_atual_oxig = definicao_de_estados(valor_atual_oxig);
      valor_valvula = controle_valvula(estado_atual_oxig);
      //Aciona o pino que vai para valvula
      //Na entrada do P6.3 mandar o valor analogico para acionar a valvula
      estado_atual_oxig = atualiza_valvula(limite_oxig,estado_atual_oxig);
      valor_valvula = controle_valvula(estado_atual_oxig);
      //Na entrada do P6.3 mandar o valor analogico (valor_valvula) para acionar a valvula
      
      //Saida do oxido nitroso
      //Entrada analogica (sensor) P6.4
      //Definir o fluxo de acordo com a porcentagem
      valor_nitro = ADC12MEM4; //// leitura da entrada analogica P6.2
      valor_atual_nitro = media(valor_nitro);
      estado_atual_nitro = definicao_de_estados(valor_atual_nitro);
      valor_valvula = controle_valvula(estado_atual_nitro);
      //Aciona o pino que vai para valvula
      //Na entrada no P6.5 mandar o valor analogico (valor_valvula) para acionar a valvula
      estado_atual_nitro = atualiza_valvula(limite_nitro,estado_atual_nitro);
      valor_valvula = controle_valvula(estado_atual_nitro);
      //Na entrada no P6.5 mandar o valor analogico (valor_valvula) para acionar a valvula
    }
}
// Rotina de serviço de interrupção da porta 1 
#pragma vector = PORT1_VECTOR 
__interrupt void Port_1 (void) 
{ 
  //Desligar tudo (primeira coisa)  
  P1DIR = 0;
  P2DIR = 0;
  P3DIR = 0;
  P4DIR = 0;
  P5DIR = 0;
  P6DIR = 0;
  
  P1OUT |= 0x00; //aciona o Led e o buzzer
  
  //Verificar se a interrupção é do botao
  if(! (P2IN & 0x03))
  {
    //Mandar no lcd que a interrupção por causa do botao
  }
  
  //Verificar se a interrupção é da falta de gas ou problema nas mangueiras
  if(estado == 0 || estado > 25)
  {
    
  }
}