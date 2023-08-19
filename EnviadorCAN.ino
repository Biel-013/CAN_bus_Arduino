//Descrição do código: É enviado por CAN os valores de dois potenciometros.
//Os valores simulam o sensor de direçao e de velocidade da roda traseira direita enviados pela ECU.
#include "mcp_can.h"
#include <stdio.h>
#include <SPI.h>

#define tdelay 100

const int buttonPin = 6;  
int buttonState = 50100;


/*Dadoos gerais d baterias*/
 
int airStatus;
float current[4] = {0.2};
int glvVoltage = 15;
int chargePercent = 60;
int totalVoltage;
int maxTemperature;
int minVoltage;

/*pack 0*/

int cell0[13] = {3.3};
int temp0[6] = {25};

/*pack 1*/

int cell1[13] = {3.3};
int temp1[6] = {25};

/*pack 2*/

int cell2[13] = {3.3};
int temp2[6] = {25};

/*pack 3*/

int cell3[13] = {3.3};
int temp3[6] = {25};

/*pack 4*/

int cell4[13] = {3.3};
int temp4[6] = {25};

/*pack 5*/

int cell5[13] = {3.3};
int temp5[6] = {25};


/*controle geral*/

int steeringWheel = 50; 
int pedalAcelerador = 10;
int pedalFreio = 10;
int selectedMode = 10;
int frenagemRegenerativa = 10;
int hodometroParcial = 10;
int hodometroTotal = 10;
int motorTorqueRight = 10;
int motorTorqueLeft = 10;
int torqueReferenceRight = 10;
int torqueReferenceLeft = 10;
int speedMotorRight = 10;
int speedMotorLeft = 10;
int ECU_control_Event_1 = 10;
int ECU_control_Event_2 = 10;
int speedFL = 10; 
int speedFR = 10;
int speedBL = 10;
int speedBR = 10;
int ganhoTorque = 10;
int motorCurrentRight = 10;
int motorCurrentLeft = 10;
int temperatureInversorR1 = 10;
int temperatureInversorR2 = 10;
int temperatureInversorL1 = 10;
int temperatureInversorL2 = 10;
int accelerometerX = 10;
int accelerometerY = 10;
int accelerometerZ = 10;
int Erro_1 = 10;
int gyroscopeX = 10;
int gyroscopeY = 10;
int gyroscopeZ = 10;
int Erro_2 = 10;
int modoCorrespondente = 10;
int flagCorrespondente1 = 10;
int flagCorrespondente2 = 10;
int tireTempFL = 10;
int tireTempFR = 10;
int tireTempBL;
int tireTempBR;
int potenciometroBalancin;
int termoparFreioD;
int extensometro1;
int extensometro2;
int interfaceFlag;
int selecaoBotao;
int extensometro22;
int extensometro13;
int extensometro23;
int portConnected;
int rssi;
int sensorPressaoDianteiro;
int simHodometer;
int simCharge;
int pressaoTraseiro;
int mediaCurrent;
int mediaTemperature;  

/***************************************************************************/
int cell[4] = {50, 70, 60, 80};
int temp = 25;
int id[] = {51,52, 102, 105, 106};
int teste = 0;



MCP_CAN CAN(10);     // Set CS to pin 10

void setup()

{
  // pinMode(A1, INPUT);
 pinMode(buttonPin, INPUT_PULLUP); // setup do botão
 pinMode(buttonPin, INPUT_PULLUP); // setup do botão
  Serial.begin(115200);
  // init can bus, baudrate: 500k
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if (CAN.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) Serial.println("MCP2515 Initialized Successfully!");
  else Serial.println("Error Initializing MCP2515...");

  CAN.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted

}
uint32_t num = 0;
void loop()

{  
  Serial.print("LOOP ");
  Serial.println(num);
  num++;
  // cell[1] = map(analogRead(A1), 0, 1023, 0, 100);
  //Create data packet for CAN message
  unsigned char canMsg1[8] = {cell[0], cell[0] >> 8, cell[1], cell[1] >> 8,  cell[2], cell[2] >> 8, cell[3], cell[3] >> 8};
  //unsigned char canMsg2[8] = {0, 0, 0x00, 0x00, refTorqueD, refTorqueD >> 8, refTorqueE, refTorqueE >> 8}; 
  //unsigned char canMsg3[8] = {velRodaDD, velRodaDD >> 8, velRodaDE, velRodaDE >> 8, velRodaTD, velRodaTD >> 8, velRodaTE, velRodaTE >> 8};
  //unsigned char canMsg4[8] = {modo,0,0,0,0,0,0,0};
  
  // send data:  id = 0x123, standrad flame, data len = 8, stmp: data buf

  delay(tdelay);
  // byte sndStat1 = CAN.sendMsgBuf(id, 0, 8, canMsg1); 
  // if (sndStat1 == CAN_OK) {
  //   Serial.print("Message 1 Sent Successfully! id = ");
  //   Serial.print(id);
  //   Serial.print("\n");
  // } else {
  //   Serial.print("Error Sending Message 1...");
  //   Serial.print("\n");
  // if(id >= 100){
  //   id=0;
  //   teste=0;
  // }
  // else{
  //   id++;
  //   teste++;
  // }

  // delay(tdelay);
  /*byte sndStat2 = CAN.sendMsgBuf(103, 0, 8, canMsg2);
  if (sndStat2 == CAN_OK) {
    Serial.println("Message 2 Sent Successfully!(Torque)");
  } else {
    Serial.println("Error Sending Message 2...(Torque)");
  }
  delay(tdelay);
  byte sndStat3 = CAN.sendMsgBuf(105, 0, 8, canMsg3);
  if (sndStat3 == CAN_OK) {
    Serial.println("Message 3 Sent Successfully!(Velocidade)");
  } else {
    Serial.println("Error Sending Message 3...(Velocidade)");
  }
  delay(tdelay);
  byte sndStat4 = CAN.sendMsgBuf(107, 0, 8, canMsg4);
  if (sndStat4 == CAN_OK) {
    Serial.println("Message 4 Sent Successfully!(Modo)");
  } else {
    Serial.println("Error Sending Message 4...(Modo)");
  }*/
  
  for(int i = 0; i < 5; i++){
    for(int j = 0; j < 5; j++){
     uint8_t sndStat1 = CAN.sendMsgBuf(id[i], 0, 8, canMsg1); 
    }
  }


}
