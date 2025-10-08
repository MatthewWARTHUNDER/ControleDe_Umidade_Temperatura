# 🌡️ Sistema de Monitoramento de Temperatura e Umidade com ESP32

Este projeto implementa um sistema de monitoramento de temperatura e umidade em tempo real, utilizando um microcontrolador ESP32 para hospedar um servidor web assíncrono. Os dados coletados pelo sensor DHT22 são exibidos em um gráfico interativo diretamente no navegador, sem a necessidade de serviços de cloud externos.

![ESP32 + DHT22](https://img.shields.io/badge/ESP32-DHT22-blue)
![Arduino](https://img.shields.io/badge/Arduino-IDE-green)
![License](https://img.shields.io/badge/license-MIT-orange)

## 📋 Características

- ✅ **Monitoramento em Tempo Real**: Atualizações automáticas a cada 2 segundos
- ✅ **Interface Web Responsiva**: Visualização em desktop, tablet e smartphone
- ✅ **Gráficos Interativos**: Histórico visual de temperatura e umidade usando Chart.js
- ✅ **Servidor Assíncrono**: Alta performance com ESPAsyncWebServer
- ✅ **Sem Cloud**: Funciona completamente offline após configuração inicial
- ✅ **Design Moderno**: Interface limpa e intuitiva com animações suaves

## 🔧 Componentes Necessários

| Componente | Quantidade | Observações |
|------------|------------|-------------|
| ESP32 Development Board | 1 | Qualquer placa ESP32 compatível |
| Sensor DHT22 (AM2302) | 1 | Sensor de temperatura e umidade |
| Resistor 10kΩ | 1 | Pull-up para o DHT22 (alguns sensores já incluem) |
| Cabos Jumper | 3 | Macho-Fêmea ou Macho-Macho |
| Protoboard | 1 | Opcional, para montagem de protótipo |

## 📐 Diagrama de Conexões

```
ESP32                    DHT22
                        ┌─────┐
GPIO 4  ─────────────── │ DATA│
                        │     │
3.3V    ─────────────── │ VCC │
                        │     │
GND     ─────────────── │ GND │
                        └─────┘

Nota: Adicione um resistor de 10kΩ entre VCC e DATA
```

### Conexões Detalhadas:
- **DHT22 VCC** → **ESP32 3.3V** (alimentação do sensor)
- **DHT22 DATA** → **ESP32 GPIO4** (pino de dados)
- **DHT22 GND** → **ESP32 GND** (terra)
- **Resistor 10kΩ** entre VCC e DATA (pull-up)

## 📚 Bibliotecas Necessárias

Instale as seguintes bibliotecas através do Gerenciador de Bibliotecas do Arduino IDE:

1. **ESPAsyncWebServer** (por me-no-dev)
   - Biblioteca para servidor web assíncrono
   - [Link do GitHub](https://github.com/me-no-dev/ESPAsyncWebServer)

2. **AsyncTCP** (por me-no-dev)
   - Dependência do ESPAsyncWebServer
   - [Link do GitHub](https://github.com/me-no-dev/AsyncTCP)

3. **DHT sensor library** (por Adafruit)
   - Biblioteca para sensores DHT
   - Instale também a dependência: **Adafruit Unified Sensor**

### Instalação Manual das Bibliotecas

Se preferir instalação manual:

```bash
# Clone os repositórios na pasta de bibliotecas do Arduino
cd ~/Arduino/libraries/

# ESPAsyncWebServer
git clone https://github.com/me-no-dev/ESPAsyncWebServer.git

# AsyncTCP
git clone https://github.com/me-no-dev/AsyncTCP.git

# DHT sensor library (via Arduino Library Manager é mais fácil)
```

## 🚀 Configuração e Instalação

### 1. Preparar o Ambiente

1. Instale o [Arduino IDE](https://www.arduino.cc/en/software) (versão 1.8.x ou 2.x)
2. Adicione suporte para ESP32:
   - Vá em **Arquivo** → **Preferências**
   - Em "URLs Adicionais para Gerenciadores de Placas", adicione:
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```
   - Vá em **Ferramentas** → **Placa** → **Gerenciador de Placas**
   - Procure por "esp32" e instale "esp32 by Espressif Systems"

### 2. Configurar o Código

1. Abra o arquivo `ControleDe_Umidade_Temperatura.ino`
2. Modifique as credenciais WiFi:
   ```cpp
   const char* ssid = "SEU_SSID";          // Nome da sua rede WiFi
   const char* password = "SUA_SENHA";      // Senha da sua rede WiFi
   ```
3. (Opcional) Modifique o pino do DHT22 se necessário:
   ```cpp
   #define DHTPIN 4  // Pino GPIO conectado ao DHT22
   ```

### 3. Upload do Código

1. Conecte o ESP32 ao computador via USB
2. Selecione a placa em **Ferramentas** → **Placa** → **ESP32 Dev Module**
3. Selecione a porta correta em **Ferramentas** → **Porta**
4. Clique em **Upload** (→)
5. Aguarde a compilação e upload

### 4. Monitorar e Acessar

1. Abra o Monitor Serial em **Ferramentas** → **Monitor Serial** (115200 baud)
2. Pressione o botão RESET no ESP32
3. Anote o endereço IP exibido no monitor serial (ex: `192.168.1.100`)
4. Abra um navegador e acesse: `http://192.168.1.100`

## 💻 Como Usar

1. **Após o upload bem-sucedido**, o ESP32 se conectará automaticamente à rede WiFi
2. **Abra o Monitor Serial** para ver o endereço IP atribuído
3. **Acesse o endereço IP** em qualquer navegador da mesma rede
4. **Visualize os dados** em tempo real:
   - Temperatura atual em °C
   - Umidade relativa em %
   - Gráficos históricos interativos

### Interface Web

A interface mostra:
- **Cards de leitura**: Valores atuais grandes e legíveis
- **Gráfico de Temperatura**: Histórico dos últimos 20 pontos
- **Gráfico de Umidade**: Histórico dos últimos 20 pontos
- **Indicador de status**: Mostra que as atualizações estão ativas

## 🔍 Resolução de Problemas

### ESP32 não conecta ao WiFi
- Verifique se o SSID e senha estão corretos
- Certifique-se de que o ESP32 está no alcance do roteador
- Confirme que a rede é 2.4GHz (ESP32 não suporta 5GHz)

### Leituras inválidas (NaN ou --)
- Verifique as conexões do DHT22
- Confirme se o resistor pull-up está instalado
- Aguarde alguns segundos após ligar (sensor precisa estabilizar)

### Erro ao compilar
- Instale todas as bibliotecas necessárias
- Verifique se a placa ESP32 está selecionada corretamente
- Atualize as bibliotecas para as versões mais recentes

### Página não carrega
- Confirme que está na mesma rede WiFi do ESP32
- Verifique o endereço IP no Monitor Serial
- Tente acessar via `http://` e não `https://`

## 🎨 Personalização

### Alterar Intervalo de Atualização

No arquivo `.ino`, modifique:
```cpp
const unsigned long intervaloLeitura = 2000;  // em milissegundos
```

No JavaScript (dentro do HTML), modifique:
```javascript
setInterval(atualizarDados, 2000);  // em milissegundos
```

### Alterar Quantidade de Pontos no Gráfico

No JavaScript, modifique:
```javascript
const maxDataPoints = 20;  // quantidade de pontos exibidos
```

### Alterar Cores

Modifique os valores RGB/HEX no CSS dentro do HTML:
```css
.temperature { color: #ff6b6b; }  /* Cor da temperatura */
.humidity { color: #4ecdc4; }     /* Cor da umidade */
```

## 📊 API de Dados

O sistema expõe um endpoint REST para obter dados em JSON:

### GET `/dados`

**Resposta:**
```json
{
  "temperatura": 25.4,
  "umidade": 60.2
}
```

**Exemplo de uso:**
```javascript
fetch('http://192.168.1.100/dados')
  .then(response => response.json())
  .then(data => console.log(data));
```

## 🔐 Segurança

⚠️ **Importante**: Este projeto é destinado para uso em redes locais privadas.

Para uso em produção, considere:
- Implementar autenticação
- Usar HTTPS
- Configurar firewall no ESP32
- Restringir acesso por IP

## 🤝 Contribuindo

Contribuições são bem-vindas! Sinta-se à vontade para:
- Reportar bugs
- Sugerir novas funcionalidades
- Enviar pull requests
- Melhorar a documentação

## 📄 Licença

Este projeto é open-source e está disponível sob a licença MIT.

## 👨‍💻 Autor

MatthewWARTHUNDER

## 🙏 Agradecimentos

- Adafruit pela biblioteca DHT
- me-no-dev pelas bibliotecas ESPAsyncWebServer e AsyncTCP
- Chart.js pela biblioteca de gráficos
- Comunidade Arduino e ESP32

## 📞 Suporte

Se encontrar problemas ou tiver dúvidas:
1. Verifique a seção de Resolução de Problemas
2. Consulte a documentação das bibliotecas
3. Abra uma issue no GitHub

---

⭐ Se este projeto foi útil, considere dar uma estrela no GitHub!