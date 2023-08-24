# NucleoboardAddEthernetboard

## Hardware

- Nucleoboard L476RG
    Die MAC-Adresse: 2C:F7:F1:08:38:CC
- eventuell das Praktikumsboard, falls nicht die Pins überschneiden
- Ethernet-Shield W5500
- Beschleunigungssensor

## Aufgabe

- Ein TCP Protokollstack (z.B. IwIP) soll integriert werden. Die Kommunikation soll
  gemessen auf möglichst hohen Datendurchsatz optimiert werden. Dazu soll eine Webapplikation
  entwickelt werden. Test mit Firefox Browser in einem privaten Netz.
- Die SD-Karte soll mit FAT Dateisystem erstellt/ gemacht werden.
- Nutzen der FreeRTOS+FAT Treiber
- Ein weiterer Teilnehmer am SPI Bus soll in Betrieb genommen werden, in einer Multi-Threading
  Anwendung soll gezeigt werden, dass es der Protokollstack - Task nicht zu Race Condition auf
  dem Bus führt.

## Weitere Informationen

Anbindung als Laufwerk unter Windows ist m. E. nicht in der Arbeit realisierbar, kleiner Webserver,
http (kein https!) in einem privaten Netz. SPI Display Anbindung kostet ebenfalls Zeit (Analys der HW, SW
Treiber müsste vorhanden sein). Wenn möglich nur Beschleunigungssensor.

### Abgrenzung

kein DHCP, feste IP-Adresse zur Compilable, evtl. über Terminal konfigurierbar. Adresse im EEPROM speichern?

### Nichtfunktionale Anforderung:

Die Entwicklung erfolg mit FreeRTOS und CMSIS RTOS API v1, evtl. OOP Kapselung der HS.
