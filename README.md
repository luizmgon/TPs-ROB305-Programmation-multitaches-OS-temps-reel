# TPs - ROB305

Ce dépôt contient les TPs (Travaux Dirigés) du cours ROB305 - Programmation multitâche et temps réel.

------------------------------------------------------------

## 📁 Structure des répertoires
```
TPs-ROB305-Programmation-multitaches-OS-temps-reel
├── TD1
│   ├── Utils
│   │   ├── Chrono.cpp
│   │   ├── Chrono.h
│   │   ├── timespec.cpp
│   │   └── timespec.h
│   ├── td1a.cpp
│   ├── td1a.exe
│   ├── td1b.cpp
│   └── td1b.exe
├── TD2
│   ├── Utils
│   │   ├── Calibrator.cpp
│   │   ├── Calibrator.h
│   │   ├── CountDown.cpp
│   │   ├── CountDown.h
│   │   ├── CpuLoop.cpp
│   │   ├── CpuLoop.h
│   │   ├── Looper.cpp
│   │   ├── Looper.h
│   │   ├── Timer.cpp
│   │   └── Timer.h
│   ├── td2a.cpp
│   ├── td2a.exe
│   ├── td2b.cpp
│   ├── td2b.exe
│   ├── td2c.cpp
│   ├── td2c.exe
│   ├── td2d.cpp
│   ├── td2d.exe
│   ├── td2e.cpp
│   └── td2e.exe
├── TD3
│   ├── Utils
│   │   ├── Counter.cpp
│   │   ├── Counter.h
│   │   ├── Incrementer.cpp
│   │   ├── Incrementer.h
│   │   ├── Mutex.cpp
│   │   ├── Mutex.h
│   │   ├── Thread.cpp
│   │   ├── Thread.h
│   │   ├── TimeoutException.cpp
│   ├── TD3a
│   │   ├── td3a1.cpp
│   │   ├── td3a1.exe
│   │   ├── td3a2-1t.cpp
│   │   ├── td3a2-1t.exe
│   │   ├── td3a2-3t.cpp
│   │   ├── td3a2-3t.exe
│   │   ├── td3a3.cpp
│   │   └── td3a3.exe
│   ├── TD3e
│   │   ├── td3e.cpp
│   │   └── td3e.exe
│   ├── td3d.cpp
│   └── td3d.exe
└── TD4
    ├── Monitor.cpp
    ├── Monitor.h
    ├── Semaphore.cpp
    ├── Semaphore.h
    └── td4b.cpp

     
```
------------------------------------------------------------

## 📋 TD1 – Mesure du temps

### 🔹 A - Gestion simplifiée du temps Posix

Le programme `td1a.exe` teste les fonctions de mesure du temps basées sur le fichier `timespec.cpp`.


#### 🛠️ Compilation (depuis `./TD1`)

```bash
arm-linux-g++ -Wall -Wextra ./Utils/*.cpp td1a.cpp  -o  td1a.exe
```

### 🔹 B - Classe Chrono

Le programme `td1b.exe` teste les fonctions de mesure du temps basées sur la classe `Chrono`.

#### 🛠️ Compilation (depuis `./TD1`)

```bash
arm-linux-g++ -Wall -Wextra ./Utils/*.cpp td1b.cpp  -o  td1b.exe
```

------------------------------------------------------------
## 📋 TD2 – Timers et échantillonnage en temps

### 🔹 A - Timers avec callback

 Timer Posix périodique de fréquence 2 Hz imprimant un message avec la valeur d’un compteur régulièrement incrémenté. Le programme doit s’arrêter après 15 incrémentations.

#### 🛠️ Compilation (depuis `./TD2`)

```bash
arm-linux-g++ -Wall -Wextra td2a.cpp  -o  td2a.exe
```

### 🔹 B - Classe Timer

Test de la classe `Timer` en utilisant une classe dérivée `CountDown` imprimant à l’écran un compte à rebours à 1 Hz depuis un nombre n jusqu’à 0.

#### 🛠️ Compilation (depuis `./TD2`)

```bash
arm-linux-g++ -Wall -Wextra ../TD1/Utils/*.cpp ./Utils/*cpp td2b.cpp  -o  td2b.exe
```

### 🔹 C - Fonction simple consommant du CPU

#### 📌 Réponses

- La méthode `Looper::getSamplep` peut être déclarée `const` car elle ne fait qu’une lecture de la variable `iLoop`, sans modifier aucun attribut de l’objet.

-  `doStop ` doit être qualifié de  `volatile ` afin de garantir que la boucle utilise toujours sa valeur à jour, celle-ci pouvant être modifiée par un appel à  `stopLoop()` depuis un thread externe.

Test de la classe ``Looper`` en affichant le nombre de boucles effectuées (loops) ainsi que le temps d'exécution.

#### 🛠️ Compilation (depuis `./TD2`)

```bash
arm-linux-g++ -Wall -Wextra ../TD1/Utils/*.cpp ./Utils/*cpp td2c.cpp  -o  td2c.exe
```
### 🔹 D - Échantillonage du temps d’exécution d’une fonction

Vérification de la calibration faite par la classe ``Calibrator`` avec des tests pour des temps d’exécution de 0.5 à 10 secondes par pas de 200ms.

#### 🛠️ Compilation (depuis `./TD2`)

```bash
arm-linux-g++ -Wall -Wextra ../TD1/Utils/*.cpp ./Utils/*cpp td2d.cpp  -o  td2d.exe
```

### 🔹 E - Classe consommatrice de CPU durant un temps donné

Vérification de la classe consommatrice ``CpuLoop`` en affichant le pourcentage représentant l’erreur relative pour des durées d’exécution allant de 0,5 à 10 secondes, par pas de 200 ms : le taux d’erreur obtenu est inférieur à 0,1 %.

#### 🛠️ Compilation (depuis `./TD2`)

```bash
arm-linux-g++ -Wall -Wextra ../TD1/Utils/*.cpp ./Utils/*cpp td2e.cpp  -o  td2e.exe
```


------------------------------------------------------------


## 📋 TD3 – Tâches et mutex Posix

### 🔹 A - Création et utilisation de tâches et de mutex Posix

#### 🛠️ Compilation (depuis `./TD3/TD3a`)

```bash
arm-linux-g++ -Wall -Wextra td3a1.cpp  -o  td3a1.exe
arm-linux-g++ -Wall -Wextra td3a2-1t.cpp  -o  td3a2-1t.exe
arm-linux-g++ -Wall -Wextra td3a2-1t.cpp  -o  td3a2-1t.exe
arm-linux-g++ -Wall -Wextra td3a3.cpp  -o  td3a3.exe

```

### 🔹 B - Classe Mutex

Création des outils ``Mutex``, ``Mutex::Lock`` et ``TimeOutException``.

#### 🛠️ Compilation - Test des erreurs et warnings (depuis `./TD3/Utils`)

```bash
arm-linux-g++ -Wall -Wextra ../../TD1/Utils/*.cpp Mutex.cpp
arm-linux-g++ -Wall -Wextra ../../TD1/Utils/*.cpp TimeoutException.cpp
```

### 🔹 C - Classe Thread

#### 🛠️ Compilation - Test des erreurs et warnings (depuis `./TD3/Utils`)

```bash
arm-linux-g++ -Wall -Wextra ../../TD1/Utils/*.cpp Thread.cpp
```

### 🔹 D - Accès concurrent à des données partagées

#### 🛠️ Compilation (depuis `./TD3`)

```bash
arm-linux-g++ -Wall -Wextra ../TD1/Utils/*.cpp ./Utils/*.cpp td3d.cpp  -o  td3d.exe
```


### 🔹 E - Inversion de priorité

#### 🛠️ Compilation (depuis `./TD1`)

```bash
arm-linux-g++ -Wall -Wextra ../TD1/Utils/*.cpp ../TD2/Utils/*.cpp ./Utils/*.cpp td3e.cpp  -o  td3e.exe
```




------------------------------------------------------------

⚙️ TD4

📌 Réponses

_(espace réservé pour les réponses du TD4)_

🛠️ Compilation

cd TD4
g++ -std=c++11 -pthread main.cpp Semaphore.cpp Monitor.cpp Mutex.cpp ../TD1/timespec.cpp -o td4
./td4 <nb_consommateurs> <nb_producteurs> <jetons_par_producteur>

------------------------------------------------------------

👋 Hello World

🛠️ Compilation

cd hello
g++ hello.cpp -o hello -pthread
./hello
