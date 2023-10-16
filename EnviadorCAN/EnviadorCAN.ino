#include "mcp_can.h"
#include <SPI.h>

#define tdelay 50  // Delay não necessario no código, mas que ajuda a visualizar a interrupção

MCP_CAN CAN(10);  // Set CS to pin 10

//Define se vai enviar um unico buffer de dados da CAN (word 0, 1, 2, e 3), ou varios
bool MODE_singleBuffer = true;

//Formato de buffer para o modo de unico buffer
uint8_t data_buffer_single[4] = { 200, 1, 3, 143 };  // word_0, word_1, word_2, word_3

/*
Formato de buffer para o modo de varios buffers, o tamanho da variavel é igual ao produto
do tamanho do tipo de variável (2, "uint16_t"), vezes a quantidade de buffers (x), vezes a quantidade
de posições por buffer (4). Ou seja, size = 2 * [x]*[4]
*/
uint16_t data_buffer[][4] = { { 200, 1, 3, 143 },      //  ID: 76 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 77 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 78 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 79 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 80 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 81 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 85 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 86 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 87 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 88 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 95 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 96 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 97 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 98 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 99 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 100 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 151 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 152 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 153 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 154 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 155 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 156 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 157 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 158 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 159 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 160 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 161 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 162 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 163 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 164 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 165 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 166 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 167 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 168 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 169 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 200 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 226 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 227 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 230 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 231 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 232 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 250 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 291 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 292 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 301 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 302 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 303 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 304 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 305 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 306 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 307 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 308 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 309 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 310 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 311 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 312 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 313 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 314 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 315 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 316 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 317 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 318 || word_0, word_1, word_2, word_3
                             { 45, 12, 100, 143 },     //  ID: 319 || word_0, word_1, word_2, word_3
                             { { 200, 1, 3, 143 },     //  ID: 320 || word_0, word_1, word_2, word_3
                             
/*
Vetor de armazenamento de ID's, o tamanho é 2*x, onde 2 é o tamanho do tipo de variável (uint16_t), e "x",
a quantidade de posições no vetor
*/
uint16_t id[] = { 76, 77, 78, 79, 80
                  81, 85, 86, 87, 88,
                  95, 96, 97. 98, 99, 
                  100, 151, 152, 153,
                  154, 155, 156, 157,
                  158, 159, 160, 161,
                  162, 163, 164, 165,
                  166, 167, 168, 169,
                  200, 226, 227, 230,
                  231, 232, 250, 291,
                  292, 301, 302, 303,
                  304, 305, 306, 307,
                  308, 309, 310, 311,
                  312, 313, 314, 315,
                  316, 317, 318, 319,
                  320};  // ID: 76, ID: 77, ID: 78, ID: 79, ...

void setup() {
  Serial.begin(115200);
  CAN_Init(&CAN);
}

void loop() {
  if (MODE_singleBuffer == true)
    CAN_SendMessage(&CAN, id, sizeof(id) / 2, data_buffer_single);  // A id é dividida por 2, para pegar a quantidade de posições
  //ou "CAN_SendMessage(&CAN, 'ID', data_buffer_single);" for single ID
  else
    CAN_SendMessage_multBuf(&CAN, id, sizeof(id) / 2, data_buffer, sizeof(data_buffer) / 2*4);
  // O data_buffer é dividida por 2*4, para pegar a quantidade de buffers independentes

  // CAN_MessageReceive_IT(&CAN, can_vector);    
    delay(tdelay);
}
