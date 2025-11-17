# QUIZ

Jogo de perguntas e respostas em **C** com interface 100% textual, construído para a disciplina de **Algoritmo e Programação Estruturada** como trabalho final.

## Funcionalidades

- Leitura de **um único arquivo JSON** com todas as perguntas.
- **Níveis de dificuldade** (ex.: Moleza, Fácil, Médio, Difícil, Hard, Expert).
- **Sorteio aleatório** de perguntas por nível.
- **Ações especiais** (uma vez por partida):
  - **Pular** questão (avança de nível sem responder).
  - **Trocar** questão (sorteia outra do mesmo nível).
  - **Dica** (exibe a dica da questão atual).
- **Vidas**: começa com 1; errou, perde 1; vida 0 = game over.
- **Vitória**: acerte a pergunta do último nível.
- **Menu textual**: responder, sair, ação especial, estado do jogo, exibir pergunta novamente.
- **Memória dinâmica** e uso de **struct** para perguntas.

---
## Estrutura do projeto

...

---
## Estrutura do jSON

Um único objeto raiz com a chave "Perguntas" que contém um array de perguntas.
Cada pergunta:
> {
 
    "Perguntas": [
        {
            "Enunciado": "Qual a frase mais popular entre os programadores de computadores?",
            "Alternativas": [
              {
                    "Alternativa": "a)",
                    "Texto": "Meu Primeiro Código",
                    "correta": false
                },
                {
                    "Alternativa": "b)",
                    "Texto": "Hello World",
                    "correta": true
                },
                {
                    "Alternativa": "c)",
                    "Texto": "Seja Bem Vindo",
                    "correta": false
                },
                {
                    "Alternativa": "d)",
                    "Texto": "Hello Code",
                    "correta": false
                }
            ],
            "Dica": "Você está entrando no mundo da programação.",
            "Dificuldade": "Moleza"
        },...
    ]
> }


---
**COLABORADORES** 
1. FRANKLEE BATIELLO VIEIRA ROCHA 
2. GUSTAVO AUGUSTO LEITE
3. FERNANDO DE ARAÚJO DIAS
4. MIGUEL DOURADO DE JESUS
5. MIGUELGUIMARAES GALVAO
6. JOÃO PEDRO BEZERRA DE JESUS


---
**Links para as bibliotecas necessárias para execução do programa**
[cJSON.h](https://github.com/DaveGamble/cJSON/blob/master/cJSON.h)
[cJSON.c](https://github.com/DaveGamble/cJSON/blob/master/cJSON.c)


`Código inline`

*Itálico*

~~Riscado~~


```python
# Bloco de código com linguagem
print("Olá, Mundo!")
```
---

Linha horizontal