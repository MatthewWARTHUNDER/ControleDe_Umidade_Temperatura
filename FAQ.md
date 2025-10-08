# ❓ Perguntas Frequentes (FAQ)

## 📡 Conexão e Rede

### Posso usar rede WiFi 5GHz?
**Não.** O ESP32 só suporta redes WiFi de 2.4GHz. Certifique-se de que seu roteador tem uma rede 2.4GHz ativa.

### Como descobrir o endereço IP do ESP32?
Abra o Monitor Serial no Arduino IDE (115200 baud) após o upload. O endereço IP será exibido quando o ESP32 se conectar ao WiFi.

### O ESP32 não conecta ao WiFi, o que fazer?
1. Verifique se o SSID e senha estão corretos (case-sensitive)
2. Certifique-se de usar rede 2.4GHz
3. Aproxime o ESP32 do roteador
4. Desabilite o filtro MAC temporariamente
5. Tente usar um hotspot do celular para testar

### Posso acessar de fora da minha rede local?
Por padrão, não. O sistema é projetado para uso em rede local. Para acesso externo, você precisaria:
- Configurar port forwarding no roteador
- Implementar segurança adicional (HTTPS, autenticação)
- Considerar usar um serviço de VPN

### É possível usar IP fixo?
Sim! Adicione estas linhas após `WiFi.begin()`:
```cpp
IPAddress local_IP(192, 168, 1, 100);  // IP desejado
IPAddress gateway(192, 168, 1, 1);     // Gateway do roteador
IPAddress subnet(255, 255, 255, 0);
WiFi.config(local_IP, gateway, subnet);
```

## 🔌 Hardware e Sensores

### Qual a diferença entre DHT11 e DHT22?
- **DHT22**: Mais preciso (±0.5°C), faixa maior (-40 a 80°C), mais caro
- **DHT11**: Menos preciso (±2°C), faixa menor (0 a 50°C), mais barato

Para usar DHT11, altere no código:
```cpp
#define DHTTYPE DHT11
```

### Preciso do resistor pull-up?
Sim, é recomendado. Alguns módulos DHT22 já vêm com o resistor integrado. Se seu sensor tiver 4 pinos, você precisa adicionar o resistor externo.

### Posso usar outro pino GPIO?
Sim! Qualquer pino GPIO digital serve. Altere no código:
```cpp
#define DHTPIN 5  // ou outro pino de sua escolha
```

Evite usar GPIO0, GPIO2 e GPIO12 (usados no processo de boot).

### As leituras mostram NaN ou valores estranhos
1. Verifique todas as conexões
2. Confirme se o resistor pull-up está instalado
3. Aguarde 2-3 segundos após ligar
4. Teste o sensor com um sketch exemplo básico DHT
5. O sensor pode estar defeituoso

### Posso usar múltiplos sensores?
Sim! Você precisará:
1. Conectar cada sensor a um pino GPIO diferente
2. Criar instâncias separadas do DHT no código
3. Modificar a interface para exibir múltiplos sensores

### Qual a vida útil do DHT22?
Tipicamente 5+ anos com uso normal. Evite ambientes com químicos corrosivos.

## 💻 Software e Código

### É compatível com Arduino Uno/Nano?
Não diretamente. Este código usa bibliotecas específicas do ESP32. Para usar com Arduino Uno/Nano, você precisaria de um módulo WiFi adicional e reescrever parte do código.

### Posso usar PlatformIO em vez do Arduino IDE?
Sim! Um arquivo `platformio.ini` está incluído no projeto. Basta abrir a pasta no VSCode com a extensão PlatformIO.

### Como mudar o intervalo de atualização?
No arquivo .ino, altere:
```cpp
const unsigned long intervaloLeitura = 2000;  // milissegundos
```

E no JavaScript (dentro do HTML):
```javascript
setInterval(atualizarDados, 2000);  // milissegundos
```

### Como adicionar mais pontos no gráfico?
No JavaScript, modifique:
```javascript
const maxDataPoints = 50;  // em vez de 20
```

### Posso salvar os dados históricos?
Esta versão não salva dados. Para implementar:
1. Use SPIFFS para armazenar em arquivo
2. Use um servidor externo
3. Use um cartão SD
4. Implemente banco de dados (SQLite)

### Como adicionar autenticação?
Você pode adicionar autenticação básica HTTP. Exemplo:
```cpp
server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    if(!request->authenticate("admin", "senha")) {
        return request->requestAuthentication();
    }
    request->send_P(200, "text/html", index_html);
});
```

## 🎨 Interface e Personalização

### Como mudar as cores?
Edite o CSS dentro do HTML. Exemplo:
```css
.temperature { color: #ff6b6b; }  /* vermelho */
.humidity { color: #4ecdc4; }     /* azul */
```

### A interface não é responsiva no meu celular
A interface é responsiva, mas:
1. Limpe o cache do navegador
2. Desabilite modo de economia de dados
3. Teste em navegador diferente
4. Verifique se JavaScript está habilitado

### Como mudar o título da página?
Edite a tag `<title>` no HTML:
```html
<title>Meu Monitor Personalizado</title>
```

### Posso adicionar mais sensores (pressão, etc)?
Sim! O código é modular. Adicione novos sensores seguindo o padrão existente.

## 🔧 Problemas Técnicos

### Erro "Brownout detector was triggered"
Problema de alimentação. Soluções:
1. Use uma fonte USB de qualidade (mín. 500mA)
2. Use um cabo USB com fios de maior bitola
3. Adicione um capacitor de 100-470µF entre VCC e GND

### Erro "Port not found" ou porta não aparece
1. Instale drivers USB (CP2102 ou CH340)
2. Tente outro cabo USB (alguns são só para carga)
3. Tente outra porta USB do computador
4. Reinicie o computador

### ESP32 aquece muito
Normal durante WiFi, mas se aquecer excessivamente:
1. Reduza a potência de transmissão WiFi
2. Adicione pequeno dissipador
3. Melhore ventilação

### Memória insuficiente ao compilar
Otimizações possíveis:
1. Use `PROGMEM` para strings grandes
2. Reduza o tamanho do HTML
3. Use compressão gzip
4. Selecione esquema de partição maior

### Erro "A fatal error occurred: Failed to connect"
Durante upload:
1. Pressione e segure BOOT durante upload
2. Tente reduzir Upload Speed para 115200
3. Pressione RESET antes de clicar Upload
4. Use cabo USB de dados (não apenas carga)

## 📊 Dados e Precisão

### Qual a precisão do DHT22?
- Temperatura: ±0.5°C
- Umidade: ±2-5% RH

### Por que as leituras variam tanto?
Variações pequenas são normais. Se variar muito:
1. Verifique as conexões
2. Afaste de fontes de calor
3. Permita circulação de ar
4. Aguarde estabilização (2-3 minutos)

### Como calibrar o sensor?
O DHT22 vem calibrado de fábrica. Para calibração:
1. Compare com termômetro/higrômetro de referência
2. Adicione offset no código se necessário:
```cpp
temperatura = dht.readTemperature() + 0.5;  // +0.5°C offset
```

### Os dados ficam salvos após reiniciar?
Não, os dados são perdidos ao desligar. Para persistência, implemente armazenamento em SPIFFS, SD card ou servidor externo.

## ⚡ Consumo e Energia

### Quanto consome o ESP32 com WiFi?
Aproximadamente 160-260mA com WiFi ativo. Para bateria:
1. Use modo sleep entre leituras
2. Considere ESP32 deep sleep
3. Use bateria de maior capacidade

### Posso alimentar por bateria?
Sim! Use:
- Baterias Li-Ion 18650 (3.7V) com regulador 3.3V
- Power bank USB
- Bateria 9V com regulador (não recomendado, baixa duração)

### Como implementar economia de energia?
Exemplo básico de deep sleep:
```cpp
esp_sleep_enable_timer_wakeup(60 * 1000000);  // 60 segundos
esp_deep_sleep_start();
```

## 🌐 Outros

### Funciona offline?
Sim! Após a configuração inicial, funciona completamente offline na rede local. O único recurso externo é Chart.js via CDN, que pode ser baixado localmente se necessário.

### Posso vender projetos baseados neste código?
Sim, a licença MIT permite uso comercial. Mas mantenha os créditos e a licença.

### Como contribuir com o projeto?
Veja o arquivo CONTRIBUTING.md para detalhes sobre como contribuir.

### Onde reportar bugs?
Abra uma issue no GitHub com:
- Descrição detalhada
- Passos para reproduzir
- Logs do Monitor Serial
- Informações do ambiente

---

**Não encontrou sua pergunta?**
Abra uma issue no GitHub com a tag `pergunta` e teremos prazer em ajudar!
