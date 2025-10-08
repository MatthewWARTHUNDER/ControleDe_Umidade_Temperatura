# 🤝 Guia de Contribuição

Obrigado por considerar contribuir com o projeto de Monitoramento de Temperatura e Umidade! 

## 📋 Índice

- [Como Posso Contribuir?](#como-posso-contribuir)
- [Reportando Bugs](#reportando-bugs)
- [Sugerindo Melhorias](#sugerindo-melhorias)
- [Processo de Pull Request](#processo-de-pull-request)
- [Guia de Estilo](#guia-de-estilo)
- [Configuração do Ambiente de Desenvolvimento](#configuração-do-ambiente-de-desenvolvimento)

## 🎯 Como Posso Contribuir?

### Reportando Bugs

Antes de criar um relatório de bug, por favor:
1. Verifique se o bug já não foi reportado
2. Colete informações sobre o problema:
   - Versão do Arduino IDE
   - Modelo do ESP32
   - Versão das bibliotecas
   - Mensagens de erro completas
   - Passos para reproduzir

Ao criar um issue de bug, inclua:
- **Título claro e descritivo**
- **Descrição detalhada** do problema
- **Passos para reproduzir** o comportamento
- **Comportamento esperado** vs **comportamento atual**
- **Screenshots** se aplicável
- **Logs** do Monitor Serial
- **Informações do ambiente**:
  - Sistema operacional
  - Versão do Arduino IDE
  - Modelo do ESP32
  - Versões das bibliotecas

### Sugerindo Melhorias

Sugestões de melhorias são sempre bem-vindas! Ao sugerir uma melhoria:

1. **Use um título claro e descritivo**
2. **Descreva detalhadamente** a melhoria proposta
3. **Explique por que** essa melhoria seria útil
4. **Liste exemplos** de como funcionaria
5. **Inclua mockups** se for uma mudança visual

### Adicionando Novas Funcionalidades

Quer adicionar uma nova funcionalidade? Ótimo!

1. **Abra um issue primeiro** para discutir a ideia
2. Aguarde feedback antes de começar a implementação
3. Siga o guia de estilo do projeto
4. Adicione documentação adequada
5. Adicione exemplos de uso se aplicável

## 🔧 Processo de Pull Request

1. **Fork** o repositório
2. **Clone** seu fork localmente:
   ```bash
   git clone https://github.com/seu-usuario/ControleDe_Umidade_Temperatura.git
   ```
3. **Crie um branch** para sua feature:
   ```bash
   git checkout -b feature/minha-feature
   ```
4. **Faça suas mudanças** seguindo o guia de estilo
5. **Teste** suas mudanças completamente
6. **Commit** suas mudanças:
   ```bash
   git commit -m "feat: adiciona funcionalidade X"
   ```
7. **Push** para seu fork:
   ```bash
   git push origin feature/minha-feature
   ```
8. **Abra um Pull Request** no repositório original

### Checklist do Pull Request

Antes de submeter, certifique-se de que:

- [ ] O código compila sem erros
- [ ] O código foi testado em hardware real
- [ ] A documentação foi atualizada
- [ ] Comentários foram adicionados para código complexo
- [ ] O código segue o guia de estilo
- [ ] Commits seguem o padrão Conventional Commits
- [ ] Sem código comentado desnecessário
- [ ] Sem arquivos temporários ou de build

## 📝 Guia de Estilo

### Código C/C++ (Arduino)

```cpp
// Use comentários descritivos em português
// Função para ler temperatura do sensor
float lerTemperatura() {
    float temp = dht.readTemperature();
    
    // Verificar se a leitura é válida
    if (isnan(temp)) {
        Serial.println("Erro ao ler temperatura");
        return -999.0;
    }
    
    return temp;
}

// Constantes em MAIÚSCULAS
#define TEMPO_ATUALIZACAO 2000

// Variáveis descritivas em camelCase
int tempoUltimaLeitura = 0;
float temperaturaAtual = 0.0;

// Nomes de funções descritivos em camelCase
void atualizarDisplay() {
    // código
}
```

### HTML/CSS/JavaScript

```javascript
// Comentários descritivos em português
// Atualizar dados do servidor
function atualizarDados() {
    fetch('/dados')
        .then(response => response.json())
        .then(data => {
            // Atualizar interface
            atualizarInterface(data);
        })
        .catch(error => {
            console.error('Erro:', error);
        });
}

// Use nomes descritivos
const tempMaxima = 30;
const umidadeMinima = 40;

// Indentação consistente (4 espaços)
if (temperatura > tempMaxima) {
    mostrarAlerta('Temperatura alta!');
}
```

### Comentários

- Use comentários em **português**
- Explique o **porquê**, não o **o quê**
- Mantenha comentários atualizados
- Evite comentários óbvios
- Use comentários de documentação para funções públicas

### Commits

Siga o padrão [Conventional Commits](https://www.conventionalcommits.org/):

```
tipo(escopo): descrição curta

Descrição mais detalhada se necessário.
```

**Tipos permitidos:**
- `feat`: Nova funcionalidade
- `fix`: Correção de bug
- `docs`: Mudanças na documentação
- `style`: Formatação, sem mudança de lógica
- `refactor`: Refatoração de código
- `perf`: Melhoria de performance
- `test`: Adição ou correção de testes
- `chore`: Tarefas de manutenção

**Exemplos:**
```
feat(sensor): adiciona suporte para DHT11
fix(wifi): corrige timeout de conexão
docs(readme): atualiza instruções de instalação
style(web): melhora responsividade do layout
```

## 🛠️ Configuração do Ambiente de Desenvolvimento

### Requisitos

- Arduino IDE 1.8.x ou 2.x
- ESP32 Board Support
- Bibliotecas necessárias (veja README.md)

### Setup Local

1. Clone o repositório:
   ```bash
   git clone https://github.com/MatthewWARTHUNDER/ControleDe_Umidade_Temperatura.git
   ```

2. Instale as dependências (veja GUIA_INSTALACAO.md)

3. Conecte o hardware conforme CIRCUIT_DIAGRAM.txt

4. Configure WiFi no arquivo .ino

5. Compile e teste

### Testando Mudanças

Sempre teste suas mudanças:

1. **Compile** o código
2. **Upload** para o ESP32
3. **Verifique** o Monitor Serial
4. **Teste** a interface web
5. **Teste** em diferentes navegadores
6. **Teste** em mobile se houver mudanças na UI

## 🎨 Contribuindo com Design

Se quiser melhorar o design da interface:

1. Mantenha a **responsividade**
2. Preserve a **acessibilidade**
3. Use **cores consistentes** com o tema atual
4. Teste em **múltiplos dispositivos**
5. Inclua **screenshots** no PR

## 📚 Contribuindo com Documentação

A documentação é tão importante quanto o código!

- Mantenha a linguagem clara e acessível
- Use exemplos práticos
- Inclua screenshots quando útil
- Mantenha a formatação consistente
- Revise ortografia e gramática

## ❓ Perguntas?

Se tiver dúvidas sobre como contribuir:

1. Verifique se já não foi respondida nos issues
2. Abra uma issue com a tag `pergunta`
3. Seja claro e específico na sua pergunta

## 🏆 Reconhecimento

Todos os contribuidores serão reconhecidos no README.md e CHANGELOG.md.

## 📜 Código de Conduta

Este projeto adota um ambiente acolhedor e inclusivo:

- Seja respeitoso com outros contribuidores
- Aceite críticas construtivas graciosamente
- Foque no que é melhor para a comunidade
- Mostre empatia com outros membros

---

Obrigado por contribuir! Suas contribuições tornam este projeto melhor para todos. 🎉
