/*
author: Wanderson Hermirio dos Santos
describe: programa para clonar codigo dos controle
version: 0.1
*/

#include <IRremote.h>
#include "nvs_flash.h"

#define CHAVE_NVS  "teste"

uint32_t dado_lido;
void grava_dado_nvs(uint32_t dado);
uint32_t le_dado_nvs(void);

int butao = 26;
int IRpin = 13;
int pinLed = 12;
IRrecv irrecv(IRpin);
decode_results results;
int statusLed = 0;

void grava_dado_nvs(uint32_t dado)
{
    nvs_handle handler_particao_nvs;
    esp_err_t err;
    
    err = nvs_flash_init_partition("nvs");
     
    if (err != ESP_OK)
    {
        Serial.println("[ERRO] Falha ao iniciar partição NVS.");           
        return;
    }
 
    err = nvs_open_from_partition("nvs", "ns_nvs", NVS_READWRITE, &handler_particao_nvs);
    if (err != ESP_OK)
    {
        Serial.println("[ERRO] Falha ao abrir NVS como escrita/leitura"); 
        return;
    }
 
    /* Atualiza valor do horimetro total */
    err = nvs_set_u32(handler_particao_nvs, CHAVE_NVS, dado);
 
    if (err != ESP_OK)
    {
        Serial.println("[ERRO] Erro ao gravar horimetro");                   
        nvs_close(handler_particao_nvs);
        return;
    }
    else
    {
        Serial.println("Dado gravado com sucesso!");     
        nvs_commit(handler_particao_nvs);    
        nvs_close(handler_particao_nvs);      
    }
}

uint32_t le_dado_nvs(void)
{
    nvs_handle handler_particao_nvs;
    esp_err_t err;
    uint32_t dado_lido;
     
    err = nvs_flash_init_partition("nvs");
     
    if (err != ESP_OK)
    {
        Serial.println("[ERRO] Falha ao iniciar partição NVS.");         
        return 0;
    }
 
    err = nvs_open_from_partition("nvs", "ns_nvs", NVS_READWRITE, &handler_particao_nvs);
    if (err != ESP_OK)
    {
        Serial.println("[ERRO] Falha ao abrir NVS como escrita/leitura");         
        return 0;
    }
 
    /* Faz a leitura do dado associado a chave definida em CHAVE_NVS */
    err = nvs_get_u32(handler_particao_nvs, CHAVE_NVS, &dado_lido);
     
    if (err != ESP_OK)
    {
        Serial.println("[ERRO] Falha ao fazer leitura do dado");         
        return 0;
    }
    else
    {
        Serial.println("Dado lido com sucesso!");  
        nvs_close(handler_particao_nvs);   
        return dado_lido;
    }
}

void setup() 
{ 
    Serial.begin(115200);
    Serial.println("Leitura do botão");
    irrecv.enableIRIn();
    pinMode(butao,INPUT);
    pinMode(pinLed,OUTPUT);
}

void loop() 
{
    if(digitalRead(butao)!=0)
    {
      while(irrecv.decode(&results)==0)
      {
        
        digitalWrite(pinLed,HIGH);
        delay(500);  
        digitalWrite(pinLed,LOW);
        delay(500); 
      }
      grava_dado_nvs(results.value);
    }
    if (irrecv.decode(&results)) 
    {
      Serial.println(results.value); // Print the Serial 'results.value'
      irrecv.resume();   // Receive the next value

      dado_lido = le_dado_nvs();
      if(results.value == dado_lido)
      {
        statusLed = 1-statusLed;
        digitalWrite(pinLed,statusLed);
      }
      
 }
}
