

https://github.com/user-attachments/assets/b1a74bbb-0018-407b-bf53-18305e44b64e



https://github.com/user-attachments/assets/4cf188ea-a1e7-4122-8c7e-02651861ebf1

# ESP32-S3 KY-040 Encoder Testi (ESP-IDF)

Arduino IDE'den çıkıp biraz daha işin mutfağına, gerçek firmware tarafına gireyim dedim ve ESP-IDF + FreeRTOS ile ilk denememi yaptım. Elimdeki ESP32-S3'e KY-040 döner butonu bağlayıp sağa sola dönüşleri ve ortadaki tuşa basılma durumunu terminalden okudum.

## Neler Yaptım?
* ESP-IDF ortamını kurup hazır `delay()` yerine işlemciyi kilitlemeyen `vTaskDelay` kullandım.
* Dışarıdan ekstra direnç takmamak için çipin içindeki dahili pull-up dirençlerini yazılımdan açtım.
* Düğmeyi sağa çevirince sayacı artırıp sola çevirince azaltan, ortasına basınca da sıfırlayan basit ve temiz bir mantık kurdum.

## Kablo Bağlantıları

| KY-040 Pini | ESP32-S3 Pini |
| :--- | :--- |
| GND | GND |
| + | 3V3 |
| CLK | GPIO 4 |
| DT | GPIO 5 |
| SW | GPIO 6 |


https://github.com/user-attachments/assets/2e0f3eb9-54ae-4e1c-9b15-a4e77dd0fc3e


