#include <VirtualWire.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Pastikan alamat I2C LCD sesuai dengan modul Anda

void setup() {
  Serial.begin(9600);               // Memulai komunikasi serial untuk debugging
  lcd.begin();                      // Menginisialisasi LCD
  lcd.backlight();                  // Mengaktifkan backlight LCD
  vw_set_rx_pin(11);                // Mengatur pin RX untuk RF433 MHz
  vw_setup(2000);                   // Kecepatan komunikasi RF yang sama dengan transmitter
  vw_rx_start();                    // Memulai receiver
  Serial.println("Receiver ready.");
  lcd.clear();
  lcd.print("Waiting data...");     // Menampilkan pesan awal di LCD
}

void loop() {
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  // Jika ada pesan yang diterima
  if (vw_get_message(buf, &buflen)) {
    String receivedText = "";
    for (int i = 0; i < buflen; i++) {
      receivedText += (char)buf[i]; // Konversi buffer data ke teks
    }

    Serial.println("Data received: " + receivedText); // Menampilkan data di Serial Monitor

    // Menampilkan data di LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Received:");
    lcd.setCursor(0, 1);
    lcd.print(receivedText.substring(0, 16)); // Menampilkan hingga 16 karakter di baris kedua
  }
}
