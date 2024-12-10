# Projetos Iniciais em Arduino

Este repositório contém dois projetos distintos desenvolvidos utilizando Arduino para a disciplina de Automação de Sistemas ministrados pelo professor **Alex Luiz de Sousa** para o Bacharelado em Sistemas da Informação - UDESC:

1. **Radar com Arduino e Processing**
2. **Jukebox com sons em 8 bits**

Cada projeto está devidamente documentado abaixo com suas respectivas instruções de uso, dependências e diagramas ilustrativos.
Além disso, apresenta-se uma documentação explicando todos os detalhes de funcionamento dos componentes utilizados

---

## 1. Radar com Arduino e Processing

### Descrição

Este projeto utiliza um sensor de distância conectado ao Arduino para detectar objetos em um determinado ângulo e representá-los visualmente em um radar criado na linguagem Processing. A representação gráfica inclui um "calor" no ponto detectado, utilizando cores para indicar a proximidade dos objetos.

### Componentes Necessários

- Arduino Uno (ou equivalente)
- Sensor de distância ultrassônico (ex.: HC-SR04)
- Servo motor
- Cabos jumpers
- Protoboard (opcional)
- Computador com Processing instalado

### Configuração

1. Conecte o sensor ultrassônico ao Arduino conforme o esquema do circuito.
2. Conecte o servo motor para controlar o movimento do sensor.
3. Compile e envie o código `Codigo_Radar_Arduino.ino` para o Arduino.
4. Abra o código Processing e execute-o para visualizar o radar.

### Diagrama de Ligação

**Esquemático:**
![Diagrama esquemático do Radar Ultrassônico](https://github.com/SiqueiraGabriel/Projetos_Iniciais_Arduino/blob/main/Radar_Ultrassonico/Diagrama_Esquematico.png)

### Como Executar

1. Certifique-se de que todos os componentes estão conectados corretamente.
2. Abra o software Arduino IDE e carregue o código.
3. No Processing, ajuste a porta serial conforme a comunicação estabelecida pelo Arduino.
4. Execute ambos os códigos e observe o funcionamento do radar.

---

## 2. Jukebox com sons em 8 bits

### Descrição

Este projeto é uma Jukebox que simula sons em 8 bits utilizando o Arduino. A interação é realizada através de botões ou sensores, permitindo ao usuário tocar diferentes sons pré-definidos.

### Componentes Necessários

- Arduino Uno (ou equivalente)
- Módulo buzzer ou alto-falante
- Botões (ou sensores capacitivos, se preferir)
- Resistores
- Cabos jumpers
- Protoboard (opcional)

### Configuração

1. Conecte os botões ao Arduino para atuar como entradas de seleção de música.
2. Conecte o buzzer à saída de áudio do Arduino.
3. Compile e envie o código `Codigo_jukebox.ino` para o Arduino.

### Diagrama de Ligação

**Esquemático:**
![Diagrama esquemático da Jukebox](https://github.com/SiqueiraGabriel/Projetos_Iniciais_Arduino/blob/main/Jukebox/Diagrama_Esquematico.png)

### Como Executar

1. Certifique-se de que o circuito foi montado corretamente.
2. Abra o software Arduino IDE e carregue o código.
3. Pressione os botões conectados ao Arduino para reproduzir os sons.

---

## Contribuições

Contribuições são bem-vindas! Por favor, envie um *pull request* com as alterações ou melhorias que desejar.

## Licença

Este projeto é licenciado sob a [MIT License](LICENSE).

---
