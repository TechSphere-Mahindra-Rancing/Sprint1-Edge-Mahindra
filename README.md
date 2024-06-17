# Controle de Temperatura e Velocidade para Pneus de Veículo

![Captura de tela 2024-06-17 113324](https://github.com/TechSphere-Mahindra-Rancing/Sprint1-Edge-Mahindra/assets/91989307/9266fcce-3d68-4f61-9fb4-79ce110c8b6e)

## Descrição
Este projeto utiliza sensores DHT22 para monitorar a temperatura de cada pneu de um veículo e exibe as informações em um display LCD. Além disso, ele simula a velocidade do veículo com base em um potenciômetro e ajusta as temperaturas monitoradas de acordo com essa velocidade. O sistema também inclui feedback visual através de LEDs (verde, amarelo e vermelho) e sonoro através de uma buzina para alertar sobre condições de temperatura crítica.

## Componentes Utilizados
- Arduino Uno (ou similar)
- Sensores DHT22 (4 unidades)
- Display LCD I2C 16x2
- LEDs (verde, amarelo, vermelho)
- Buzina
- Potenciômetro
- Resistores e jumpers

## Bibliotecas Necessárias
- Wire.h
- LiquidCrystal_I2C.h
- DHT.h

## Configuração
- Conectar os sensores DHT22 aos pinos definidos no código (`DHTPIN1`, `DHTPIN2`, `DHTPIN3`, `DHTPIN4`). É recomendável calibrar os sensores para manter uma temperatura média ao redor de 50°C para melhor aproveitamento do sistema de velocidade.
- Conectar o display LCD I2C no endereço 0x27.
- Conectar os LEDs e a buzina aos pinos especificados (`GREEN_LED`, `YELLOW_LED`, `RED_LED`, `BUZZER`).

## Funcionamento
1. **Inicialização:**
   - O Arduino inicializa os sensores DHT22, o display LCD e a comunicação serial.
   
2. **Loop Principal:**
   - **Leitura de Temperatura:** Os sensores DHT22 são lidos para obter as temperaturas dos pneus.
   - **Ajuste de Temperatura:** As temperaturas lidas são ajustadas com base na velocidade simulada pelo potenciômetro.
   - **Exibição no LCD:** As temperaturas médias ajustadas e a velocidade são exibidas no display LCD.
   - **Feedback Visual e Sonoro:** LEDs indicam o estado da temperatura (verde: ideal, amarelo: aquecimento, vermelho: crítico) e a buzina emite um tom de alerta conforme a temperatura.

3. **Serial Monitor:**
   - Os valores de velocidade e temperatura são impressos no Serial Monitor para debug e monitoramento.

4. **Delay:**
   - O loop principal espera 10 segundos entre cada iteração para uma taxa de atualização adequada.

## Como Usar
1. Configure o circuito conforme a descrição em **Configuração**.
2. Carregue o código para o Arduino utilizando a IDE Arduino.
3. Abra o Serial Monitor para monitorar as temperaturas e a velocidade em tempo real.
4. Observe os LEDs e a buzina para feedback visual e sonoro sobre as condições de temperatura dos pneus.

## Links

#### [Repositório no GitHub](https://github.com/TechSphere-Mahindra-Rancing/Sprint1-Edge-Mahindra)
#### [Simulação no Wokwi](https://wokwi.com/projects/400411515672606721)
#### [Vídeo Explicativo](https://youtu.be/cUFec4MsSQc?si=RtlBDDmwxqeOTVAF)
