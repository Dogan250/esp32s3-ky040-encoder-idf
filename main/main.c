#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define PIN_CLK GPIO_NUM_4
#define PIN_DT  GPIO_NUM_5
#define PIN_SW  GPIO_NUM_6

static const char *TAG = "ENCODER_FIRMWARE";

void app_main(void)
{
    // Pinleri giriş (Input) ve dahili pull-up dirençli olarak ayarla
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,
        .mode = GPIO_MODE_INPUT,
        .pin_bit_mask = (1ULL << PIN_CLK) | (1ULL << PIN_DT) | (1ULL << PIN_SW),
        .pull_down_en = 0,
        .pull_up_en = 1,
    };
    gpio_config(&io_conf);

    int son_clk = gpio_get_level(PIN_CLK);
    int sayac = 0;

    ESP_LOGI(TAG, "KY-040 Encoder Hazir! Dugmeyi cevir veya bas...");

    while (1) {
        int mevcut_clk = gpio_get_level(PIN_CLK);

        // Düğme çevrildiyse (CLK durumu değiştiyse)
        if (mevcut_clk != son_clk && mevcut_clk == 1) {
            if (gpio_get_level(PIN_DT) != mevcut_clk) {
                sayac++;
                ESP_LOGI(TAG, "Saga Dondu -> Deger: %d", sayac);
            } else {
                sayac--;
                ESP_LOGI(TAG, "Sola Dondu -> Deger: %d", sayac);
            }
        }
        son_clk = mevcut_clk;

        // Ortadaki butona basıldıysa
        if (gpio_get_level(PIN_SW) == 0) {
            ESP_LOGW(TAG, "BUTONA BASILDI! Sayac Sifirlandi.");
            sayac = 0;
            vTaskDelay(pdMS_TO_TICKS(300)); // Buton sıçramasını (debounce) önle
        }

        vTaskDelay(pdMS_TO_TICKS(2)); // 2ms örnekleme hızı
    }
}
