# Come importare la libreria statica `.a` in STM32CubeIDE

Questa guida spiega come importare e utilizzare una libreria statica (ad esempio `libarmfft.a`) in un progetto STM32CubeIDE.

---

## 1. Copia la libreria nel progetto

Copia il file `libarmfft.a` nella cartella del tuo progetto STM32CubeIDE, ad esempio in una sottocartella chiamata `lib` (creala se non esiste).

---

## 2. Configura le impostazioni del linker

- Apri STM32CubeIDE.
- Clicca col tasto destro sul progetto → **Properties**.
- Vai su **C/C++ Build** → **Settings**.
- Nella scheda **Tool Settings**, seleziona **MCU GCC Linker** → **Libraries**.

---

## 3. Aggiungi la libreria statica

- Nel campo **Libraries (-l)** aggiungi il nome della libreria **senza** il prefisso `lib` e senza estensione `.a`.

  Per esempio, per `libarmfft.a` scrivi armfft.
  
  
- Nel campo **Library search path (-L)** aggiungi il percorso della cartella contenente la libreria.  
Se hai creato una cartella `lib` nel progetto, scrivi ${ProjDirPath}/lib.


---

## 4. Aggiungi il percorso degli header

- Vai su **C/C++ General** → **Paths and Symbols** → **Includes**.
- Aggiungi il percorso alla cartella contenente gli header `.h` della libreria (es. `${ProjDirPath}/src` o `${ProjDirPath}/lib/include`).

---

## 5. Usa la libreria nel codice

Nel file `.c` dove vuoi usare la libreria, includi gli header necessari ove specificato dalla configurazione fatta con CUBEMX:

```c
#include "arm_fft.h"
#include "fftmath.h"




