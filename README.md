# 🕹️ Sistema Embarcado - Jogo da Memória

Este é um projeto de um **Jogo da Memória** desenvolvido na placa didática **BitDogLab** utilizando um **Raspberry Pi Pico W**. O jogo utiliza a matriz de LEDs endereçáveis, display OLED, joystick, botões fisícos e buzzer para proporcionando uma experiência interativa, divertida e educativa para demonstrar os conhecimentos adquiridos na residência de sistemas embarcados **EmbarcaTech**.

⚠️ **Atenção**: Este projeto utiliza a versão **1.5.1** do **Pico SDK**. Certifique-se de estar utilizando a versão correta ao importar e compilar o código.

## 🚀 Funcionalidades

- Interface com **matriz de LED** para exibição do jogo
- Controle por **joystick** e **botões** para seleção do LED correto
- Exibição de mensagens em **display OLED**, como instruções e alertas
- Sinais sonoros pelo **buzzer**, para acertos e erros
- Código modularizado, organizado em arquivos `.h` e `.c`

## 🛠️ Tecnologias e Ferramentas Utilizadas

- **Linguagem**: C
- **Placa**: BitDogLab com Raspberry Pi Pico W
- **IDE**: VS Code
- **Bibliotecas**: 
   - Bibliotecas padrão do C: stdio.h, stdlib.h, string.h, time.h
   - Bibliotecas do SDK do Raspberry Pi Pico: pico/stdlib.h, hardware/pio.h, hardware/clocks.h, hardware/adc.h, hardware/pwm.h, hardware/i2c.h
   - Bibliotecas específicas do projeto: inc/matriz_led.h, inc/display_oled.h, inc/buzzer.h, inc/logica_jogo.h, ws2818b.pio.h

## 📦 Estrutura do Projeto

```
SISTEMA_EMBARCADO_JOGO_DA_MEMORIA/

├── .vscode/   # Configurações do VS Code 
├── build/     # Pasta de build 
├── inc/       # Arquivos de cabeçalho (.h) 
│ ├── buzzer.h             # Configurações do buzzer
│ ├── display_OLED.h       # Configurações do display OLED
│ ├── logica_jogo.h        # Configurações de joystick e lógica do Jogo
│ ├── matriz_led.h         # Configurações da matriz de LED
│ ├── ssd1306_font.h 
│ ├── ssd1306_i2c.h 
│ ├── ssd1306.h 
│ ├── ssd1306_i2c.c 
├── .gitignore             # Arquivos ignorados pelo Git 
├── CMakeLists.txt         # Configuração do CMake 
├── pico_sdk_import.cmake  # Importação do Pico SDK 
├── ws2818b.pio            # Configuração para matriz de LED 
├── jogoMemoria.c          # Lógica principal do jogo 
├── README.md              # Documentação principal 
└── LICENSE                # Licença do projeto
```

## ⚙️ Como Executar

1. Clone o repositório:
   ```bash
   git clone https://github.com/LincolnMatheus97/SISTEMA_EMBARCADO_JOGO_DA_MEMORIA.git
   ```
2. Certifique-se de estar utilizando a versão **1.5.1** do **Pico SDK**.
3. Compile o código e envie para a placa (dependendo do ambiente de desenvolvimento que você está usando).
4. Conecte a BitDogLab e execute o jogo.

## 📜 Licença

Este projeto está licenciado sob a **MIT License** - veja o arquivo [LICENSE](LICENSE) para mais detalhes.

---

Desenvolvido por [Lincoln Matheus](https://github.com/LincolnMatheus97).
