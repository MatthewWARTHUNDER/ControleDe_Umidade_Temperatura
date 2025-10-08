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
