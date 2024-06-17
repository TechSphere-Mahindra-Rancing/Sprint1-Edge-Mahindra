#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN1 2       // Pino do sensor DHT22 do pneu 1
#define DHTPIN2 3       // Pino do sensor DHT22 do pneu 2
#define DHTPIN3 4       // Pino do sensor DHT22 do pneu 3
#define DHTPIN4 5       // Pino do sensor DHT22 do pneu 4

#define DHTTYPE DHT22   // Tipo do sensor DHT
#define GREEN_LED 6     // Pino do LED verde
#define YELLOW_LED 7    // Pino do LED amarelo
#define RED_LED 8       // Pino do LED vermelho
#define BUZZER 9        // Pino da Buzina
#define POT_PIN A0      // Pino do potenciômetro

DHT dht1(DHTPIN1, DHTTYPE);  // Inicialização do sensor DHT no pino 2
DHT dht2(DHTPIN2, DHTTYPE);  // Inicialização do sensor DHT no pino 3
DHT dht3(DHTPIN3, DHTTYPE);  // Inicialização do sensor DHT no pino 4
DHT dht4(DHTPIN4, DHTTYPE);  // Inicialização do sensor DHT no pino 5

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Inicialização do LCD I2C no endereço 0x27, 16 colunas por 2 linhas

void setup() {
  pinMode(GREEN_LED, OUTPUT);    // Configura o pino do LED verde como saída
  pinMode(YELLOW_LED, OUTPUT);   // Configura o pino do LED amarelo como saída
  pinMode(RED_LED, OUTPUT);      // Configura o pino do LED vermelho como saída
  pinMode(BUZZER, OUTPUT);       // Configura o pino da buzina como saída
  
  lcd.init();                    // Inicializa o LCD
  lcd.backlight();               // Liga o backlight do LCD
  
  dht1.begin();                  // Inicia o sensor DHT1
  dht2.begin();                  // Inicia o sensor DHT2
  dht3.begin();                  // Inicia o sensor DHT3
  dht4.begin();                  // Inicia o sensor DHT4
  
  Serial.begin(9600);            // Inicializa a comunicação serial com baud rate de 9600
}

void loop() {
  // Ler a temperatura dos sensores DHT22
  float temp1 = dht1.readTemperature();   // Lê a temperatura do sensor DHT1
  float temp2 = dht2.readTemperature();   // Lê a temperatura do sensor DHT2
  float temp3 = dht3.readTemperature();   // Lê a temperatura do sensor DHT3
  float temp4 = dht4.readTemperature();   // Lê a temperatura do sensor DHT4
  
  // Verificar se as leituras são válidas
  if (isnan(temp1) || isnan(temp2) || isnan(temp3) || isnan(temp4)) {
    Serial.println("Falha ao ler do sensor DHT!");  // Se alguma leitura não for válida, exibe mensagem de erro no Serial Monitor
    return;  // Retorna e termina o loop
  }

  // Mapeamento das temperaturas para um intervalo de 0 a 120 graus Celsius
  float temp1_mapped = map(temp1, -40.0, 80.0, 0.0, 120.0);  // Mapeia a temperatura do sensor DHT1
  float temp2_mapped = map(temp2, -40.0, 80.0, 0.0, 120.0);  // Mapeia a temperatura do sensor DHT2
  float temp3_mapped = map(temp3, -40.0, 80.0, 0.0, 120.0);  // Mapeia a temperatura do sensor DHT3
  float temp4_mapped = map(temp4, -40.0, 80.0, 0.0, 120.0);  // Mapeia a temperatura do sensor DHT4

  // Ler o valor do potenciômetro para simular a velocidade
  int potValue = analogRead(POT_PIN);  // Lê o valor do potenciômetro
  float speed = map(potValue, 0, 1023, 0, 300);  // Mapeia o valor do potenciômetro para uma faixa de 0 a 300 km/h

  // Ajustar as temperaturas simuladas com base na velocidade
  float temp1_adjusted = temp1_mapped + (speed / 10);  // Ajusta a temperatura mapeada do sensor DHT1 com base na velocidade
  float temp2_adjusted = temp2_mapped + (speed / 10);  // Ajusta a temperatura mapeada do sensor DHT2 com base na velocidade
  float temp3_adjusted = temp3_mapped + (speed / 10);  // Ajusta a temperatura mapeada do sensor DHT3 com base na velocidade
  float temp4_adjusted = temp4_mapped + (speed / 10);  // Ajusta a temperatura mapeada do sensor DHT4 com base na velocidade

  // Calcular a média das temperaturas ajustadas
  float avgTemp = (temp1_adjusted + temp2_adjusted + temp3_adjusted + temp4_adjusted) / 4.0;  // Calcula a temperatura média ajustada

  // Atualizar o display LCD
  lcd.setCursor(0, 0);            // Configura o cursor do LCD para a primeira linha, primeira coluna
  lcd.print("Speed:");       // Exibe "Velocidade:"
  lcd.setCursor(7, 0);           // Configura o cursor do LCD para a primeira linha, coluna 12
  lcd.print(speed, 0);            // Exibe a velocidade sem casas decimais
  lcd.print("km/h");             // Exibe a unidade "km/h"

  lcd.setCursor(0, 1);            // Configura o cursor do LCD para a segunda linha, primeira coluna
  lcd.print("Temp:");       // Exibe "Temp Media:"
  lcd.setCursor(7, 1);           // Configura o cursor do LCD para a segunda linha, coluna 12
  lcd.print(avgTemp, 1);          // Exibe a temperatura média com uma casa decimal
  lcd.print((char)223);          // Exibe o simbolo de Graus Celsius (°) 
  lcd.print("C");                // Exibe a unidade "C"

  // Imprimir os valores no Serial Monitor
  Serial.print("Velocidade: ");   // Exibe "Velocidade: " no Serial Monitor
  Serial.print(speed);            // Exibe a velocidade no Serial Monitor
  Serial.println(" km/h");        // Exibe a unidade "km/h" no Serial Monitor
  Serial.print("Temperatura Media dos Pneus: ");  // Exibe "Temperatura Media: " no Serial Monitor
  Serial.print(avgTemp);          // Exibe a temperatura média no Serial Monitor
  Serial.println(" °C");          // Exibe a unidade "°C" no Serial Monitor
  Serial.println("--------------------------------------------------");  // Linha separadora no Serial Monitor

  // Controle dos LEDs e buzina com base na temperatura média ajustada
  if (avgTemp < 100) {
    // Temperatura ideal
    digitalWrite(GREEN_LED, HIGH);   // Liga o LED verde
    digitalWrite(YELLOW_LED, LOW);   // Desliga o LED amarelo
    digitalWrite(RED_LED, LOW);      // Desliga o LED vermelho
    noTone(BUZZER);                  // Para a buzina
  } else if (avgTemp < 120) {
    // Superaquecimento
    digitalWrite(GREEN_LED, LOW);    // Desliga o LED verde
    digitalWrite(YELLOW_LED, HIGH);  // Liga o LED amarelo
    digitalWrite(RED_LED, LOW);      // Desliga o LED vermelho
    tone(BUZZER, 1000);              // Toca a buzina com um tom suave
  } else {
    // Temperatura crítica
    digitalWrite(GREEN_LED, LOW);    // Desliga o LED verde
    digitalWrite(YELLOW_LED, LOW);   // Desliga o LED amarelo
    digitalWrite(RED_LED, HIGH);     // Liga o LED vermelho
    tone(BUZZER, 2000);              // Toca a buzina com um tom alto
  }

  delay(10000); // Aguardar dez segundos entre as leituras
}
