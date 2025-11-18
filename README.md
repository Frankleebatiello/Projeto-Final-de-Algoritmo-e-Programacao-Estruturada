# Dev Game Quest

**Um Jogo Educativo de Quiz Sobre Programação**

---

## Índice

- [Visão Geral](#visão-geral)
- [Características Principais](#características-principais)
- [Pré-requisitos](#pré-requisitos)
- [Como Executar](#como-executar)
- [Configuração do Arquivo JSON](#configuração-do-arquivo-json)
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Guia do Jogador](#guia-do-jogador)
- [Desenvolvedores](#desenvolvedores)

---

## Visão Geral

**Dev Game Quest** é um jogo educativo interativo desenvolvido em **C puro** (sem dependências externas) que permite ao jogador testar seus conhecimentos em programação através de um sistema de quiz dinâmico e progressivo.

O jogo foi concebido como ferramenta pedagógica para consolidar aprendizado em conceitos de computação, oferecendo uma experiência gamificada com sistema de recompensas, múltiplas dificuldades e recursos especiais.

### Filosofia do Projeto
- **Educação Interativa**: Perguntas organizadas por nível de dificuldade
- **Sem Dependências Externas**: Utiliza apenas bibliotecas padrão do C
- **Portabilidade**: Compila facilmente em sistemas Windows
- **Escalabilidade**: Banco de perguntas dinâmico via arquivo JSON

---

## Características Principais

| Recurso | Descrição |
|---------|-----------|
| **Sistema de Níveis** | 5 níveis progressivos com dificuldades crescentes |
| **Vidas e Pontos** | Comece com 1 vida e ganhe moedas por acertos |
| **Dicas Inteligentes** | Use até 3 dicas para orientação nas respostas |
| **Pulos Estratégicos** | Pule perguntas difíceis sem penalizar sua vida |
| **Trocas de Perguntas** | Troque a pergunta atual por outra do mesmo nível |
| **Sistema de Loja** | Compre vidas, dicas, pulos e trocas com moedas ganhas |
| **Banco de Perguntas Dinâmico** | Carregue perguntas de arquivo JSON personalizado |
| **Interface Responsiva** | Interface adaptável à largura do terminal |

---

## Pré-requisitos

### Ambiente Windows
- **Compilador GCC**: MinGW ou equivalente
- **Terminal**: CMD, PowerShell ou Git Bash
- **Editor de Texto** (opcional): Visual Studio Code, Notepad++, ou similar

### Verificar a Instalação do GCC

Abra o terminal/PowerShell e execute:

```bash
gcc --version
```

Se receber uma mensagem indicando a versão, está pronto. Caso contrário, [instale o MinGW](https://www.mingw-w64.org/).

---

## Instruções de Compilação

### Estrutura de Diretórios

Todos os arquivos devem estar no **mesmo diretório**:

```
projeto/
├── main.c
├── interface.c
├── interface.h
├── jogo.c
├── jogo.h
├── json.c
├── json.h
├── pergunta.c
├── pergunta.h
├── perguntas.json
├── README.md
├── utils.c
└── utils.h
```

### Compilação Manual (Recomendado)

Navegue até a pasta do projeto no terminal e execute:

#### **Opção 1: Comando Simples** (Recomendado)

```bash
gcc -o game main.c pergunta.c jogo.c json.c interface.c utils.c
```

**Explicação do comando:**
- `gcc`: Compilador GNU C
- `-o game`: Define o nome do executável como `game.exe`
- Arquivos `.c`: Arquivos-fonte a compilar

#### **Opção 2: Com Avisos Adicionais** (Para Debug)

```bash
gcc -Wall -Wextra -o game main.c pergunta.c jogo.c json.c interface.c utils.c
```

**Flags utilizadas:**
- `-Wall`: Exibe todos os avisos padrão
- `-Wextra`: Exibe avisos adicionais e úteis

#### **Opção 3: Com Otimização** (Para Produção)

```bash
gcc -O2 -o game main.c pergunta.c jogo.c json.c interface.c utils.c
```

**Flags utilizadas:**
- `-O2`: Otimização de nível 2 para melhor desempenho

### Resultado da Compilação

Após executar o comando, um arquivo **`game.exe`** será gerado na pasta. Este é seu executável final.

---

##  Como Executar

### No Terminal (Recomendado)

Navegue até o diretório do projeto e execute:

```bash
game.exe
```

Ou simplesmente:

Clique duas vezes no arquivo **`game.exe`** para iniciar o jogo.

### Verificar Execução

Se o jogo iniciou corretamente, você verá:
- O título "DEV GAME QUEST"
- O menu principal com opções
- Mensagens de carregamento do banco de perguntas

---

## Configuração do Arquivo JSON

### Formato do Arquivo de Perguntas

O arquivo **`perguntas.json`** deve estar na **mesma pasta** que o executável e seguir este formato:

```json
{
  "Perguntas": [
    {
      "enunciado": "O que é uma variável em programação?",
      "alternativas": [
        {
          "alternativa": "A",
          "texto": "Um espaço na memória para armazenar dados",
          "correta": true
        },
        {
          "alternativa": "B",
          "texto": "Um tipo de função",
          "correta": false
        },
        {
          "alternativa": "C",
          "texto": "Um comando do compilador",
          "correta": false
        },
        {
          "alternativa": "D",
          "texto": "Um arquivo de código",
          "correta": false
        }
      ]
      "dica": "É um espaço na memória que armazena dados",
      "dificuldade": 1,
    }
  ]
}
```

### Campos Obrigatórios

| Campo | Tipo | Descrição | Exemplo |
|-------|------|-----------|---------|
| **enunciado** | string | Texto da pergunta | `"O que é uma variável?"` |
| **alternativas** | array | Lista de opções de resposta | Ver exemplo acima |
| **alternativa** | string | Letra da opção (A, B, C, D) | `"A"`, `"B"`, `"C"` ou `"D"` |
| **texto** | string | Texto da alternativa | `"Um espaço na memória..."` |
| **correta** | boolean | Marca a resposta correta | `true` ou `false` |
| **dica** | string | Sugestão para responder | `"É um espaço na memória..."` |
| **dificuldade** | inteiro | Nível 1-5 | `1`, `2`, `3`, `4` ou `5` |

### Criando seu Próprio Arquivo JSON

#### **Passo 1: Abrir um Editor**
Abra um editor de texto (Notepad, VS Code, Sublime Text, etc.)

#### **Passo 2: Copiar o Template Abaixo**

```json
{
  "Perguntas": [
    {
      "enunciado": "Sua pergunta aqui",
      "alternativas": [
        {
          "alternativa": "A",
          "texto": "Primeira opção",
          "correta": true
        },
        {
          "alternativa": "B",
          "texto": "Segunda opção",
          "correta": false
        },
        {
          "alternativa": "C",
          "texto": "Terceira opção",
          "correta": false
        },
        {
          "alternativa": "D",
          "texto": "Quarta opção",
          "correta": false
        }
      ]
      "dica": "Uma dica útil",
      "dificuldade": 1,
    }
  ]
}
```

#### **Passo 3: Adicionar Mais Perguntas**

Adicione mais objetos de pergunta dentro do array `"Perguntas"`. Exemplo com 2 perguntas:

```json
{
  "Perguntas": [
    {
      "enunciado": "Pergunta 1",
      "alternativas": [...]
      "dica": "Dica 1",
      "dificuldade": 1,
    },
    {
      "enunciado": "Pergunta 2",
      "alternativas": [...]
      "dica": "Dica 2",
      "dificuldade": 2,
    }
  ]
}
```

#### **Passo 4: Salvar como JSON**

- Salve o arquivo como **`perguntas.json`**
- Escolha codificação **UTF-8**
- Coloque na **mesma pasta** do executável

### Validar o JSON

Para verificar se seu JSON está correto, use:
- Ferramenta online: [JSON Formatter & Validator](https://jsonformatter.curiousconcept.com/#)
- Extensão VS Code: "JSON Validator"

Se houver erro de formatação, o jogo exibirá: `"ERRO: Nenhuma pergunta carregada!"`

---

## Estrutura do Projeto

### Arquivos-Fonte

| Arquivo | Descrição |
|---------|-----------|
| **main.c** | Ponto de entrada do programa - gerencia o menu principal |
| **pergunta.c** | Lógica de carregamento e gerenciamento de perguntas |
| **jogo.c** | Mecânicas do jogo (vidas, dicas, loja, validação) |
| **json.c** | Parser JSON para carregar perguntas do arquivo |
| **interface.c** | Componentes visuais (menus, títulos, regras) |
| **utils.c** | Funções auxiliares (limpeza de buffer, formatação) |

### Arquivos-Header

Cada `.c` possui um `.h` correspondente que define estruturas e protótipos:

| Header | Estruturas Principais |
|--------|----------------------|
| **pergunta.h** | `pgt` (pergunta), `alt` (alternativa), `bQ` (banco de questões) |
| **jogo.h** | `acoesJogador` (estado do jogador) |
| **json.h** | Funções de parsing JSON |
| **interface.h** | Prototipagem de funções de UI |
| **utils.h** | Funções utilitárias |

---

## Guia do Jogador

### Como Jogar

1. **Inicie o Jogo**: Execute `game.exe`
2. **Escolha Jogar**: Pressione `1` no menu principal
3. **Responda as Perguntas**: Use `A`, `B`, `C` ou `D` para escolher
4. **Use Recursos Estrategicamente**:
  - `1`: Use uma dica
  - `2`: Pule a pergunta
  - `3`: Troque por outra pergunta
  - `4`: Acesse a loja
  - `5`: Veja seu status
  - `6`: Saia da partida

### Sistema de Dificuldades

| Nível | Tipo | Quantidade Esperada |
|-------|------|---------------------|
| 1 | Iniciante | 10-15 perguntas |
| 2 | Básico | 10-15 perguntas |
| 3 | Intermediário | 10-15 perguntas |
| 4 | Avançado | 10-15 perguntas |
| 5 | Expert | 10-15 perguntas |

### Mecânicas Principais

- **Vidas**: Comece com 1. Respostas erradas causam perda de vida
- **Moedas**: Ganhe 2.5 por resposta correta
- **Vitória**: Responda todas as perguntas de todos os níveis
- **Derrota**: Ficar sem vidas

### Dicas de Estratégia

- Compre vidas extras na loja antes de ficarem difíceis  
- Use dicas em perguntas que não tem certeza  
- Acumule moedas antes de perder uma vida  
- Troque perguntas pelo mesmo nível se não souber  

---

## Desenvolvedores

**Dev Game Quest v1.0**

- Franklee Batiello Vieira Rocha
- Fernando de Araujo Dias
- Miguel Guimaraes Galvao
- Miguel Dourado de Jesus
- Gustavo Augusto Leite
- Lucas de Souza Martins Araujo
- Joao Pedro Bezerra de Jesus

Um jogo educativo sobre programação, criado para testar e expandir conhecimentos em diversas áreas da computação.

---

## Suporte

### Problemas Comuns

**P: "ERRO: Nenhuma pergunta carregada!"**  
R: Verifique se o arquivo `perguntas.json` está na mesma pasta que `game.exe` e se o JSON está validado.

**P: Comando gcc não encontrado**  
R: Instale o MinGW ou adicione GCC ao PATH do Windows.

**P: O jogo fecha de repente**  
R: Pode haver erro no JSON. Valide o arquivo em [JSON Formatter & Validator](https://jsonformatter.curiousconcept.com/#).

**P: Não consigo compilar**  
R: Verifique se todos os arquivos estão na mesma pasta e use o comando de compilação exato.

---

## Licença

Este projeto foi desenvolvido como trabalho educacional.

---

**Última atualização:** 2025  
**Versão:** 1.0
