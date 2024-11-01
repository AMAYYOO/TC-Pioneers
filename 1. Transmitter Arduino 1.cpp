#include <VirtualWire.h>

void setup() {
  Serial.begin(9600);       // Memulai komunikasi serial
  vw_set_tx_pin(12);        // Mengatur pin TX RF433 MHz
  vw_setup(2000);           // Mengatur kecepatan komunikasi RF ke 2000 bps
  Serial.println("Transmitter ready. Enter text to send:");
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');  // Membaca input dari Serial Monitor
    input.trim();  // Menghapus karakter spasi kosong di awal/akhir

    if (input.length() > 0) {
      const char *msg = input.c_str();            // Mengonversi String ke char array
      vw_send((uint8_t *)msg, input.length());    // Mengirim data melalui RF433 MHz
      vw_wait_tx();                               // Menunggu hingga pengiriman selesai
      Serial.println("Data sent: " + input);
    }
  }
}
