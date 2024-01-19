#include <SPI.h>  // include the SPI library
#include <MC_MCP41010.h>
//https://github.com/calfizzi/MC_MCP41010

#define SPI_COPI 13
#define SPI_CLK 14
#define SPI_CS 15
#define BUCKEN 16

MC_MCP41010 MCP41010(SPI_CS, SPI_CLK,SPI_COPI);


void setup() {
  // put your setup code here, to run once:
  pinMode(BUCKEN,OUTPUT);
  digitalWrite(BUCKEN,HIGH);
  MCP41010.Begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int level = 60; level <= MAX_LEVEL; level++)
  {
    MCP41010.Write((uint8_t)level);
    delay(10);
  }
  for (int level = 0; level <= MAX_LEVEL; level++)
  {
    MCP41010.Write((uint8_t)(MAX_LEVEL-level));
    delay(10);
  }
}
