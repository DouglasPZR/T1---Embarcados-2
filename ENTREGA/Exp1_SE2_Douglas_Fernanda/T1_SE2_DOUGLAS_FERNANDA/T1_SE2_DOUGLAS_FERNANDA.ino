


//------------------------------------------------------------------------------------------ BIBLIOTECAS
#include <LiquidCrystal.h>
#include <DHT.h>
//#include <SHT1x.h>


//------------------------------------------------------------------------------------------ PINOS e INICIALIZAÇÕES
//--------------------------------------------------------  DEFS DISPLAY
#define rs 12
#define en 11
#define d4 5
#define d5 4
#define d6 3
#define d7 2
//--------------------------------------------------------  DEFS LEDS
#define LED1 6
#define LED2 7
#define LED3 8
#define LED4 9
//--------------------------------------------------------  DEFS CHAVES
#define CH1 A0
#define CH2 A1
#define CH3 A2
#define CH4 A3
//--------------------------------------------------------  DEFS DHT11
#define DHTTYPE DHT11   // DHT 11
#define DHTPIN 10     


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
DHT dht(DHTPIN, DHTTYPE);



//------------------------------------------------------------------------------------------ UNION 32 bits em 4 dados de 8 bits
typedef union{                    // union serve para separar um dado de 32bits em 4 dados de 8 bits, ajuda na transmissao de float
  struct{
    unsigned char high;
    unsigned char low;
    unsigned char high1;
    unsigned char low1;
  }parcial;
float total;
}INTEIRO;
INTEIRO dado16, TEMP16, UMI16;   // dado16 é variavel union com os dados, dado16.total é o float inteiro, dado16.parcial é as partes


//--------------------------------------------------- LEITURA DHT11
void LEITURA_DHT11(void){
  TEMP16.total = dht.readTemperature();
  UMI16.total = dht.readHumidity();
  Serial.print("Temp:  ");
  Serial.print((int)TEMP16.total);
  Serial.println("oC");
  Serial.print("UMI:  ");
  Serial.print((int)UMI16.total);
  Serial.println("%");
}


//------------------------------------------------------------------------------------------ CALCULO CRC
//--------------------------------------------------------  TABELAS CRC
static unsigned char auchCRCHi[] = {        /* Table of CRC values for high–order byte */
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
0x40
} ;

static char auchCRCLo[] = {                                 /* Table of CRC values for low–order byte */
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
0x40
};

//--------------------------------------------------------  FUNÇÃO QUE CALCULA CRC
unsigned short CRC16 (unsigned char *puchMsg, unsigned short usDataLen){        /* The function returns the CRC as a unsigned short type */
  unsigned char uchCRCHi = 0xFF ;                     /* high byte of CRC initialized */
  unsigned char uchCRCLo = 0xFF ;                     /* low byte of CRC initialized */
  unsigned uIndex ;                                   /* will index into CRC lookup table */
  while (usDataLen--){                                /* pass through message buffer */
    uIndex = uchCRCLo ^ *puchMsg++;                   /* calculate the CRC */
    uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex];
    uchCRCHi = auchCRCLo[uIndex] ;
   }
   
  return (uchCRCLo << 8 | uchCRCHi);
}

//------------------------------------------------------------------------------------------ FUNÇÃO ACIONA LEDS
void ACIONA_LEDS (uint8_t comando_LEDS){
  if (comando_LEDS & (1<<0)) digitalWrite(LED1, HIGH);
  else digitalWrite(LED1, LOW);
  if (comando_LEDS & (1<<1)) digitalWrite(LED2, HIGH);
  else digitalWrite(LED2, LOW);
  if (comando_LEDS & (1<<2)) digitalWrite(LED3, HIGH);
  else digitalWrite(LED3, LOW);
  if (comando_LEDS & (1<<3)) digitalWrite(LED4, HIGH);
  else digitalWrite(LED4, LOW);
}

//------------------------------------------------------------------------------------------ FUNÇÃO MODBUS
void modbus(uint8_t dado){
  static int estado = 0;
  static char msg_recebida [16];
  uint8_t crc_baixo, crc_alto, vetor_resposta_modbus [30];
  uint16_t  crc16_calculado;
  
  switch (estado){
//---------- verifica endereços   
    case 0:                               
      if (dado == 0x01) estado = 1;       // endereço do arduino no proteus
      else estado = 0;
     break;
//---------- verifica função   
    case 1:                         
      if (dado == 0x10) estado = 2;        // numero da função modbus; 2~12 = função ler flaot
      else if (dado == 0x0F) estado = 13;   // numero da função LEDS 13~20
      else if (dado == 0x02) estado = 21;   // numero da função CHAVES 21~26
      else if (dado == 0x03) estado = 40;   // numero da função DHT11 40~
      else estado =0;
    break;


//------------------------------------------------------- FUNÇÃO FLOAT + DISPLAY

//----------------- ESTRUTURA DADOS MODBUS FUNÇÃO 0x10 MASTER -> SLAVE
//
//  ENDEREÇO |  FUNÇAO |                                   DADOS                  |         CRC
//           |         |  END INICIAL |   Nº ESTADOS   | Nº Bytes | BYTE1 | BYTE2 | CRC ALTO  | CRC BAIXO
//   0x11    |  0x10   |      0x01    |  0x00  |  0x2D |   0x02   | 0x00  | 0x0A  | BYTE ALTO | BYTE BAIXO

//---------- verifica endereço inicial alto
    case 2:                         
      if (dado == 0x00) estado = 3;        // parte alta do endereço é sempre zero
      else estado =0;
    break;
//---------- verifica endereço inicial baixo
    case 3:                         
      if (dado == 0x06) estado = 4;        // endereço do periférico ponto flutuante segundo o trabalho 1 - end 0x06
      else if (dado == 0x00) estado = 27;  // numero função escreve caracteres no display 27~ 39
      else estado =0;
    break;
//---------- verifica numero de estados alto
    case 4:                                // estados parte alta é zero
      if (dado == 0x00) estado = 5;        // para transmitir um numero em ponto flutuante são necessarios 4 bytes, entao sao necessarios 2 estados, 2 bytes por estado
      else estado =0;
    break;
//---------- verifica numero de estados baixa
    case 5:                         
      if (dado == 0x02) estado = 6;        // 2 estados para transmitir 4 bytes
      else estado =0;
    break;
//---------- numero de bytes
    case 6:                         
      if (dado == 0x04) estado = 7;        // numero de bytes a ser recebido - neste caso 4 bytes
      else estado =0;
    break;
//---------- recebe primeiro byte de dados
    case 7:                         
      dado16.parcial.low = dado;          // recebe primeiro dado 4 bytes e salva no parcial low
      estado = 8;
    break;
//---------- recebe segundo byte de dados
    case 8:                         
      dado16.parcial.high = dado;          // recebe segundo dado 4 bytes e salva no parcial low
      estado = 9;
    break;
//---------- recebe terceiro byte de dados
    case 9:                         
      dado16.parcial.low1 = dado;          // recebe terceiro dado 4 bytes e salva no parcial low
      estado = 10;
    break;
//---------- recebe primeiro byte de dados
    case 10:                         
      dado16.parcial.high1 = dado;          // recebe quarto dado 4 bytes e salva no parcial low

      lcd.setCursor(0,2);
      lcd.print("N= ");
      lcd.print(dado16.total);
      
      estado = 11;
    break;
//---------- recebe CRC ALTO
    case 11:                         
      crc_alto = dado;          // recebe crc alto
      estado = 12;
    break;
//---------- recebe CRC BAIXO
    case 12:                         
      crc_baixo = dado;          // recebe crc baixo
      estado = 0;                // reset da maquina de estados
//resposta modbus p/ slave
      vetor_resposta_modbus [0] = 0x01;   // endereço
      vetor_resposta_modbus [1] = 0x10;   // função modbus
      vetor_resposta_modbus [2] = 0x00;   // endereço alto
      vetor_resposta_modbus [3] = 0x06;   // endereço baixo
      vetor_resposta_modbus [4] = 0x00;   // numero de estados alto
      vetor_resposta_modbus [5] = 0x02;   // numero de estados baixo
      crc16_calculado = CRC16(vetor_resposta_modbus, 6);          // calcula crc do conteudo da resposta com 6 bytes
      vetor_resposta_modbus [6] = (crc16_calculado >>8 )& 0xff;   // crc alto
      vetor_resposta_modbus [7] = (crc16_calculado)& 0xff;        // crc baixo

      Serial.write(vetor_resposta_modbus,8);                      // envia a resposta
    break;



//------------------------------------------------------- FUNÇÃO ACIONA LEDS

//----------------- ESTRUTURA DADOS MODBUS FUNÇÃO 0x0F MASTER -> SLAVE
//
//  ENDEREÇO |  FUNÇAO |                                   DADOS                  |         CRC
//           |         |  END INICIAL |   Nº ESTADOS   | Nº Bytes | BYTE1 | BYTE2 | CRC ALTO  | CRC BAIXO
//   0x11    |  0x0F   |      0x00    |  0x00  |  0x2D |   0x02   | 0x00  | 0x0A  | BYTE ALTO | BYTE BAIXO
//---------- verifica endereço inicial alto
    case 13:                         
      if (dado == 0x00) estado = 14;        // parte alta do endereço é sempre zero
      else estado =0;
    break;
//---------- verifica endereço inicial baixo
    case 14:                         
      if (dado == 0x01) estado = 15;        // parte alta do endereço é sempre zero
      else estado =0;
    break;
//---------- verifica numero de estados alto
    case 15:                                // estados parte alta é zero
      if (dado == 0x00) estado = 16;        // para transmitir um numero em ponto flutuante são necessarios 4 bytes, entao sao necessarios 2 estados, 2 bytes por estado
      else estado =0;
    break;
//---------- verifica numero de estados baixa
    case 16:                         
      if (dado == 0x04) estado = 17;        // 1 estados para transmitir 4 bytes
      else estado =0;
    break;
//---------- numero de bytes
    case 17:                         
      if (dado == 0x01) estado = 18;        // numero de bytes a ser recebido - neste caso 1 bytes
      else estado =0;
    break;
//---------- recebe primeiro byte de dados
    case 18:                         
      ACIONA_LEDS(dado);
      estado = 19;
    break;
//---------- recebe CRC ALTO
    case 19:                         
      crc_alto = dado;          // recebe crc alto
      estado = 20;
    break;
//---------- recebe CRC BAIXO
    case 20:                         
      crc_baixo = dado;          // recebe crc baixo
      estado = 0;                // reset da maquina de estados
//resposta modbus p/ slave
      vetor_resposta_modbus [0] = 0x01;   // endereço
      vetor_resposta_modbus [1] = 0x0F;   // função modbus
      vetor_resposta_modbus [2] = 0x00;   // endereço alto
      vetor_resposta_modbus [3] = 0x01;   // endereço baixo
      vetor_resposta_modbus [4] = 0x00;   // numero de estados alto
      vetor_resposta_modbus [5] = 0x04;   // numero de estados baixo
      crc16_calculado = CRC16(vetor_resposta_modbus, 6);          // calcula crc do conteudo da resposta com 6 bytes
      vetor_resposta_modbus [6] = (crc16_calculado >>8 )& 0xff;   // crc alto
      vetor_resposta_modbus [7] = (crc16_calculado)& 0xff;        // crc baixo

      Serial.write(vetor_resposta_modbus,8);                      // envia a resposta
    break;


//------------------------------------------------------- FUNÇÃO LEITURA DAS CHAVES

//----------------- ESTRUTURA DADOS MODBUS FUNÇÃO 0x02 MASTER -> SLAVE
//
//  ENDEREÇO |  FUNÇAO |                DADOS          |          CRC
//           |         |  END INICIAL |   Nº ESTADOS   | CRC ALTO  | CRC BAIXO
//   0x11    |  0x02   |      0x00    |  0x00  |  0x0D | BYTE ALTO | BYTE BAIXO
//---------- verifica endereço inicial alto
    case 21:                         
      if (dado == 0x00) estado = 22;        // parte alta do endereço é sempre zero
      else estado =0;
    break;
//---------- verifica endereço inicial baixo
    case 22:                         
      if (dado == 0x02) estado = 23;        // parte alta do endereço é sempre zero
      else estado =0;
    break;
//---------- verifica numero de estados alto
    case 23:                                // estados parte alta é zero
      if (dado == 0x00) estado = 24;        // para transmitir um numero em ponto flutuante são necessarios 4 bytes, entao sao necessarios 2 estados, 2 bytes por estado
      else estado =0;
    break;
//---------- verifica numero de estados baixa
    case 24:                         
      if (dado == 0x04) estado = 25;        // 1 estados para transmitir 4 bytes
      else estado =0;
    break;
//---------- recebe CRC ALTO
    case 25:                         
      crc_alto = dado;          // recebe crc alto
      estado = 26;
    break;
//---------- recebe CRC BAIXO
    case 26:                         
      crc_baixo = dado;          // recebe crc baixo
      estado = 0;                // reset da maquina de estados
//resposta modbus p/ slave
      vetor_resposta_modbus [0] = 0x01;   // endereço
      vetor_resposta_modbus [1] = 0x02;   // função modbus
      vetor_resposta_modbus [2] = 0x01;   // endereço alto
      vetor_resposta_modbus [3] = ((digitalRead(CH4) << 3) |(digitalRead(CH3) << 2) | (digitalRead(CH2) << 1) | (digitalRead(CH1) << 0));
      crc16_calculado = CRC16(vetor_resposta_modbus, 4);          // calcula crc do conteudo da resposta com 6 bytes
      vetor_resposta_modbus [4] = (crc16_calculado >>8 )& 0xff;   // crc alto
      vetor_resposta_modbus [5] = (crc16_calculado)& 0xff;        // crc baixo

      Serial.write(vetor_resposta_modbus,6);                      // envia a resposta
    break;


//------------------------------------------------------- FUNÇÃO ESCREVE NO DISPLAY
//---------- verifica numero de estados alto
    case 27:                                // estados parte alta é zero
      if (dado == 0x00) estado = 28;        // para transmitir um numero em ponto flutuante são necessarios 4 bytes, entao sao necessarios 2 estados, 2 bytes por estado
      else estado =0;
    break;
//---------- verifica numero de estados baixa
    case 28:                         
      if (dado == 0x10) estado = 29;        // 2 estados para transmitir 4 bytes
      else estado =0;
    break;
//---------- numero de bytes
    case 29:                         
      if (dado == 0x20) estado = 30;        // numero de bytes a ser recebido - neste caso 4 bytes
      else estado =0;
    break;
//---------- recebe segundo byte de dados
    case 30:                         
      msg_recebida[0] = (dado);          // recebe segundo dado 4 bytes e salva no parcial low
      estado = 31;
    break;
//---------- recebe terceiro byte de dados
    case 31:                         
      msg_recebida[1] = dado;              // recebe terceiro dado 4 bytes e salva no parcial low
      estado = 32;
    break;
//---------- recebe terceiro byte de dados
    case 32:                         
      msg_recebida[2] =( dado);              // recebe terceiro dado 4 bytes e salva no parcial low
      estado = 33;
    break;
//---------- recebe terceiro byte de dados
    case 33:                         
      msg_recebida[3] =( dado);              // recebe terceiro dado 4 bytes e salva no parcial low
      estado = 34;
    break;
//---------- recebe terceiro byte de dados
    case 34:                         
      msg_recebida[4] =  (dado);              // recebe terceiro dado 4 bytes e salva no parcial low
      estado = 35;
    break;
//---------- recebe terceiro byte de dados
    case 35:                         
      msg_recebida[5] =( dado);              // recebe terceiro dado 4 bytes e salva no parcial low
      estado = 36;
    break;
//---------- recebe terceiro byte de dados
    case 36:                         
      msg_recebida[6] = (dado);              // recebe terceiro dado 4 bytes e salva no parcial low
      estado = 50;
    break;
    
//---------- recebe segundo byte de dados
    case 50:                         
      msg_recebida[7] = (dado);          // recebe segundo dado 4 bytes e salva no parcial low
      estado = 51;
    break;
//---------- recebe terceiro byte de dados
    case 51:                         
      msg_recebida[8] = dado;              // recebe terceiro dado 4 bytes e salva no parcial low
      estado = 52;
    break;
//---------- recebe terceiro byte de dados
    case 52:                         
      msg_recebida[9] =( dado);              // recebe terceiro dado 4 bytes e salva no parcial low
      estado = 53;
    break;
//---------- recebe terceiro byte de dados
    case 53:                         
      msg_recebida[10] =( dado);              // recebe terceiro dado 4 bytes e salva no parcial low
      estado = 54;
    break;
//---------- recebe terceiro byte de dados
    case 54:                         
      msg_recebida[11] =  (dado);              // recebe terceiro dado 4 bytes e salva no parcial low
      estado = 55;
    break;
//---------- recebe terceiro byte de dados
    case 55:                         
      msg_recebida[12] =( dado);              // recebe terceiro dado 4 bytes e salva no parcial low
      estado = 56;
    break;
//---------- recebe terceiro byte de dados
    case 56:                         
      msg_recebida[13] = (dado);              // recebe terceiro dado 4 bytes e salva no parcial low
      estado = 57;
    break;
    
//---------- recebe terceiro byte de dados
    case 57:                         
      msg_recebida[14] = (dado);              // recebe terceiro dado 4 bytes e salva no parcial low
      estado = 37;
    break;
//---------- recebe terceiro byte de dados
    case 37:                         
      msg_recebida[15] = dado;              // recebe terceiro dado 4 bytes e salva no parcial low
      lcd.setCursor(0,0);
      lcd.print(msg_recebida);
//      lcd.print(msg_recebida[1]);
//      lcd.print(msg_recebida[2]);
//      lcd.print(msg_recebida[3]);
//      lcd.print(msg_recebida[4]);
//      lcd.print(msg_recebida[5]);
//      lcd.print(msg_recebida[6]);
//      lcd.print(msg_recebida[7]);
      estado = 38;
    break;
//---------- recebe CRC ALTO
    case 38:                         
      crc_alto = dado;          // recebe crc alto
      estado = 39;
    break;
//---------- recebe CRC BAIXO
    case 39:                         
      crc_baixo = dado;          // recebe crc baixo
      estado = 0;                // reset da maquina de estados
//resposta modbus p/ slave
      vetor_resposta_modbus [0] = 0x01;   // endereço
      vetor_resposta_modbus [1] = 0x10;   // função modbus
      vetor_resposta_modbus [2] = 0x00;   // endereço alto
      vetor_resposta_modbus [3] = 0x00;   // endereço baixo
      vetor_resposta_modbus [4] = 0x00;   // numero de estados alto
      vetor_resposta_modbus [5] = 0x10;   // numero de estados baixo
      crc16_calculado = CRC16(vetor_resposta_modbus, 6);          // calcula crc do conteudo da resposta com 6 bytes
      vetor_resposta_modbus [6] = (crc16_calculado >>8 )& 0xff;   // crc alto
      vetor_resposta_modbus [7] = (crc16_calculado)& 0xff;        // crc baixo

      Serial.write(vetor_resposta_modbus,8);                      // envia a resposta
    break;

//------------------------------------------------------- FUNÇÃO DHT11
//---------- verifica endereço inicial alto
    case 40:                         
      if (dado == 0x00) estado = 41;        // parte alta do endereço é sempre zero
      else estado =0;
    break;
//---------- verifica endereço inicial baixo
    case 41:                         
      if (dado == 0x04) estado = 42;        // leitura temperatura
      else if (dado == 0x05) estado = 46;   // leitura umidade
      else estado =0;
    break;
//---------- verifica numero de estados alto
    case 42:                                // estados parte alta é zero
      if (dado == 0x00) estado = 43;        // para transmitir um numero em ponto flutuante são necessarios 4 bytes, entao sao necessarios 2 estados, 2 bytes por estado
      else estado =0;
    break;
//---------- verifica numero de estados baixa
    case 43:                         
      if (dado == 0x03) estado = 44;        // 1 estados para transmitir 4 bytes
      else estado =0;
    break;
//---------- recebe CRC ALTO
    case 44:                         
      crc_alto = dado;          // recebe crc alto
      estado = 45;
    break;
//---------- recebe CRC BAIXO
    case 45:                         
      crc_baixo = dado;          // recebe crc baixo
      estado = 0;                // reset da maquina de estados
      TEMP16.total = 2*(dht.readTemperature());
      //resposta modbus p/ slave
      vetor_resposta_modbus [0] = 0x01;   // endereço
      vetor_resposta_modbus [1] = 0x03;   // função modbus
      vetor_resposta_modbus [2] = 0x06;   // endereço alto
      vetor_resposta_modbus [3] = 0x00;
      vetor_resposta_modbus [4] = 0x01;
      vetor_resposta_modbus [5] = TEMP16.parcial.low;
      vetor_resposta_modbus [6] = TEMP16.parcial.high;
      vetor_resposta_modbus [7] = TEMP16.parcial.low1;
      vetor_resposta_modbus [8] = TEMP16.parcial.high1;
      crc16_calculado = CRC16(vetor_resposta_modbus, 9);          // calcula crc do conteudo da resposta com 6 bytes
      vetor_resposta_modbus [9] = (crc16_calculado >>8 )& 0xff;   // crc alto
      vetor_resposta_modbus [10] = (crc16_calculado)& 0xff;        // crc baixo

      Serial.write(vetor_resposta_modbus,11);                      // envia a resposta
    break;


//---------- verifica numero de estados alto
    case 46:                                // estados parte alta é zero
      if (dado == 0x00) estado = 47;        // para transmitir um numero em ponto flutuante são necessarios 4 bytes, entao sao necessarios 2 estados, 2 bytes por estado
      else estado =0;
    break;
//---------- verifica numero de estados baixa
    case 47:                         
      if (dado == 0x03) estado = 48;        // 1 estados para transmitir 4 bytes
      else estado =0;
    break;
//---------- recebe CRC ALTO
    case 48:                         
      crc_alto = dado;          // recebe crc alto
      estado = 49;
    break;
//---------- recebe CRC BAIXO
    case 49:                         
      crc_baixo = dado;          // recebe crc baixo
      estado = 0;                // reset da maquina de estados
      UMI16.total = 2*(dht.readHumidity());
      //resposta modbus p/ slave
      vetor_resposta_modbus [0] = 0x01;   // endereço
      vetor_resposta_modbus [1] = 0x03;   // função modbus
      vetor_resposta_modbus [2] = 0x06;   // endereço alto
      vetor_resposta_modbus [3] = 0x00;
      vetor_resposta_modbus [4] = 0x02;
      vetor_resposta_modbus [5] = UMI16.parcial.low;
      vetor_resposta_modbus [6] = UMI16.parcial.high;
      vetor_resposta_modbus [7] = UMI16.parcial.low1;
      vetor_resposta_modbus [8] = UMI16.parcial.high1;
      crc16_calculado = CRC16(vetor_resposta_modbus, 9);          // calcula crc do conteudo da resposta com 6 bytes
      vetor_resposta_modbus [9] = (crc16_calculado >>8 )& 0xff;   // crc alto
      vetor_resposta_modbus [10] = (crc16_calculado)& 0xff;        // crc baixo

      Serial.write(vetor_resposta_modbus,11);                      // envia a resposta
    break;

    
  } 
}

//------------------------------------------------------------------------------------------ SETUP
void setup() {
//--------------------------------------------------------  LCD INIT
  lcd.begin(16, 2);
  //lcd.print("teste");
//--------------------------------------------------------  SERIAL INIT
  Serial.begin(9600);
//--------------------------------------------------------  I/O's INIT
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  pinMode (LED3, OUTPUT);
  pinMode (LED4, OUTPUT);
  pinMode (CH1, INPUT);
  pinMode (CH2, INPUT);
  pinMode (CH3, INPUT);
  pinMode (CH4, INPUT);
//--------------------------------------------------------  INIT temp+umi com valor
//  TEMP16.total = 25.27;
//  UMI16.total = 67.37;

}


//------------------------------------------------------------------------------------------ LOOP
void loop() {
  uint8_t dadoRX;
  int res_chaves = 0;
  char msg_ch [20];

//  LEITURA_DHT11();
//  delay(250);


  if (Serial.available() > 0) {
    dadoRX = Serial.read();
    modbus(dadoRX);
  }
}
