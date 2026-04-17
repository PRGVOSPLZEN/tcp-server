# TCP Logging Server v C++

Tento projekt implementuje jednoduchý, nepřetržitě běžící TCP server pro Linux/Unix systémy. Server přijímá zprávy od klientů a ukládá je s časovým razítkem do textového souboru.

## Funkcionalita
- **Nekonečný cyklus:** Server po obsloužení klienta nekončí, ale okamžitě čeká na další spojení.
- **Automatické logování:** Veškerá přijatá data ukládá do souboru `log.txt`.
- **Režim Append:** Nová data se připisují na konec souboru, staré záznamy zůstávají zachovány.
- **Časová razítka:** Každý záznam v logu začíná datem a časem přijetí ve formátu `[YYYY-MM-DD HH:MM:SS]`.
- **Robustní síťové nastavení:** Používá `SO_REUSEADDR`, což umožňuje okamžitý restart serveru na stejném portu.

## Požadavky
- Překladač podporující C++11 nebo novější (např. `g++`).
- Operační systém Linux, macOS nebo WSL (Windows Subsystem for Linux).

## Jak začít

### 1. Kompilace
V terminálu spusťte následující příkaz:
```bash
g++ -o server main.cpp