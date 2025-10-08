# ControleDe_Umidade_Temperatura

**Monitoramento de Clima Web com ESP32**

<p>Este projeto apresenta um sistema completo de monitoramento de temperatura e umidade em tempo real. Utilizamos o microcontrolador ESP32 para hospedar um servidor web assíncrono que coleta dados de um sensor DHT22 e os exibe em um gráfico interativo diretamente no navegador, eliminando a necessidade de serviços de cloud externos.</p>



 **Funcionalidades**

* Servidor Web Assíncrono: Implementado com ESPAsyncWebServer, garantindo que o servidor seja rápido, responsivo e capaz de lidar com requisições simultâneas de forma eficiente.

* Visualização Gráfica: O front-end (servido via LittleFS) utiliza JavaScript para buscar periodicamente os dados do sensor e atualizá-los em um gráfico dinâmico.

* API de Dados: O firmware expõe endpoints simples para o front-end buscar os valores atuais:


**Materias** 

* Microcontrolador	ESP32 Dev Module
* DHT22 (Sensor de Temperatura e Umidade)
* Pull-up de 4.7 kΩ (Necessário para a linha de dados do DHT)
* Cabos Jumper, Protoboard e Cabo Micro USB para alimentação

**Referências**

* ESP32/ESP8266 Plot Sensor Readings in Real Time Charts – Web Server - https://randomnerdtutorials.com/esp32-esp8266-plot-chart-web-server/

* Arduino IDE 2: Install ESP32 LittleFS Uploader (Upload Files to the Filesystem) - https://randomnerdtutorials.com/arduino-ide-2-install-esp32-littlefs/
