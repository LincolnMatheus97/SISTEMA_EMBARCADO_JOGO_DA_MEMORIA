#ifndef DISPLAY_OLED_H // Include guard para evitar múltiplas inclusões
#define DISPLAY_OLED_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "inc/ssd1306.h"

const uint I2C_SDA = 14;
const uint I2C_SCL = 15;

// Estrutura do display OLED
ssd1306_t ssd;

// Buffer do OLED
static uint8_t ssd_buffer[ssd1306_buffer_length];
static struct render_area frame_area = {
    .start_column = 0,
    .end_column = ssd1306_width - 1,
    .start_page = 0,
    .end_page = ssd1306_n_pages - 1};

// Display de mensagem no OLED
void displayMensagem(const char *linha1, const char *linha2, const char *linha3, const char *linha4, const char *linha5)
{
    memset(ssd_buffer, 0, ssd1306_buffer_length);
    ssd1306_draw_string(ssd_buffer, 5, 0, (char *)linha1);
    ssd1306_draw_string(ssd_buffer, 5, 10, (char *)linha2);
    ssd1306_draw_string(ssd_buffer, 5, 20, (char *)linha3);
    ssd1306_draw_string(ssd_buffer, 5, 30, (char *)linha4);
    ssd1306_draw_string(ssd_buffer, 5, 40, (char *)linha5);
    render_on_display(ssd_buffer, &frame_area);
}

// Inicialização do display OLED
void inicializacaoDisplay()
{
    i2c_init(i2c1, ssd1306_i2c_clock * 5000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    ssd1306_init();

    // Calcular a área de renderização
    calculate_render_area_buffer_length(&frame_area);

    memset(ssd_buffer, 0, ssd1306_buffer_length);
    render_on_display(ssd_buffer, &frame_area);
}

#endif