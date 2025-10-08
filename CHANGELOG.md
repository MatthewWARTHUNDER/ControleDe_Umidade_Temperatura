# Changelog

Todas as mudanças notáveis neste projeto serão documentadas neste arquivo.

O formato é baseado em [Keep a Changelog](https://keepachangelog.com/pt-BR/1.0.0/),
e este projeto adere ao [Semantic Versioning](https://semver.org/lang/pt-BR/).

## [1.0.0] - 2024-01-08

### Adicionado
- Implementação inicial do sistema de monitoramento
- Suporte para sensor DHT22 (AM2302)
- Servidor web assíncrono com ESPAsyncWebServer
- Interface web responsiva com design moderno
- Gráficos interativos em tempo real usando Chart.js
- Sistema de atualização automática a cada 2 segundos
- Cards visuais para temperatura e umidade
- Histórico visual dos últimos 20 pontos de dados
- API REST endpoint `/dados` para acesso aos dados em JSON
- Documentação completa em português
- Guia de instalação passo a passo
- Diagrama de circuito detalhado
- Arquivo de configuração de exemplo
- Suporte para PlatformIO
- Arquivo .gitignore configurado
- Licença MIT

### Características
- Interface totalmente responsiva (mobile-friendly)
- Funcionamento 100% offline após configuração
- Sem necessidade de serviços cloud externos
- Animações suaves e indicador de status visual
- Suporte para múltiplos navegadores
- Design gradiente moderno
- Código bem comentado em português

### Documentação
- README.md completo com instruções detalhadas
- GUIA_INSTALACAO.md com passo a passo ilustrado
- CIRCUIT_DIAGRAM.txt com esquema ASCII art
- Comentários em português no código
- Exemplos de uso e personalização

## [Próximas Versões]

### Planejado para v1.1.0
- [ ] Suporte para múltiplos sensores DHT22
- [ ] Exportação de dados em CSV
- [ ] Alertas configuráveis por temperatura/umidade
- [ ] Modo AP (Access Point) como fallback
- [ ] Armazenamento de dados em SPIFFS
- [ ] Gráficos com período configurável

### Planejado para v1.2.0
- [ ] Suporte para outros sensores (BME280, SHT31)
- [ ] Autenticação básica para acesso web
- [ ] Configuração WiFi via interface web
- [ ] OTA (Over-The-Air) updates
- [ ] Integração com MQTT
- [ ] API RESTful expandida

### Ideias Futuras
- [ ] App mobile nativo (Flutter/React Native)
- [ ] Integração com Home Assistant
- [ ] Notificações push
- [ ] Modo de economia de energia
- [ ] Registro histórico em banco de dados
- [ ] Dashboard com múltiplos dispositivos

---

## Formato das Entradas

### Tipos de mudanças
- `Adicionado` para novas funcionalidades
- `Modificado` para mudanças em funcionalidades existentes
- `Descontinuado` para funcionalidades que serão removidas
- `Removido` para funcionalidades removidas
- `Corrigido` para correções de bugs
- `Segurança` para vulnerabilidades corrigidas

### Exemplo de entrada
```markdown
## [X.Y.Z] - AAAA-MM-DD

### Adicionado
- Nova funcionalidade ABC (#123)
- Suporte para XYZ

### Corrigido
- Correção do bug em DEF (#456)
```
