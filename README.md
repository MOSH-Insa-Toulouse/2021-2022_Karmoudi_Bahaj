# 2021-2022_Bahaj_Karmoudi

## Projet Capteur - INSA Toulouse

    Réalisation d'un capteur de déformation low-tech à base de graphite dans le cadre du Projet Capteur de 4ème année Génie Physique à l'INSA de Toulouse.

## Description 

Durant ce projet, nous avons été amenés à concevoir un capteur à jauge de contrainte à base de graphite développé afin de mesurer la résistance en fonction de la courbure appliquée. Une couche de graphite est déposé sur un bout de papier, ce dépôt étant un système granuleux, il existe donc une relation entre la conductivité électrique et l'espace entre les nanoparticules de graphite. Nous avons donc exploité cette propriété afin de relever la variation de la résistance induite par la traction ou la compression du réseau percolé. Pendant ce projet, nous avons été amenés à faire design, la conception et le codage.

## Sommaire

  - [1. Matériel et livrables](#1-Matériel-et-livrables)
      - [1.1 Matériel requis](#11-Matériel-requis)
      - [1.2 Livrables](#12-Livrables)
  - [2. Kicad](#2-Kicad)
      - [2.1 Schématique complète](#22-Schématique)
      - [2.2 Schématique et empreinte des composants](#21-Schématique-et-empreinte-des-composants)
      - [2.3 Création du PCB](#23-Création-du-PCB)
  - [3. Code Arduino](#3-code-arduino)
  - [4. Application Bluetooth](#4-application-Bluetooth)
  - [5. Banc de test](#5-Banc-de-test)
  - [6. Datasheet](#6-datasheet)
  - [7. Contact](#6-Contact)

## 1. Matériel et livrables

### 1.1 Matériel

- Carte Arduino UNO
- Une plaque de cuivre pour le Shield
- Papier et crayon à papier
- Un module Bluetooth HC-05 
- Un encodeur rotatoire KY-040
- Un écran OLED
- Deux pinces crocodiles en cuivre pour attacher le capteur au PCB
- Un amplificateur opérationnel LTC1050  
- 3 condensateurs de 100nf
- 1 condensateur de 1µF
- 2 résistances de 100kΩ
- 1 résistance de 10kΩ
- 1 résistance de 1kΩ
- Smartphone Android

### 1.2 Livrables

Les livrables du projet sont comme suit : 

- Un shield PCB contenant un circuit amplificateur transimpédance, un module bluetooth, un écran OLED et un encodeur rotatoire
- Un code Arduino
- Une application Android APK qui nous affiche l'état de connexion, nous affiche les valeurs de la tension et de la résistance ainsi qu'une courbe de la résistance aux bornes du capteur en fonction du temps
- Un banc de test
- Une datasheet détaillant les caractéristiques du capteur

## 2. Kicad 

Kicad est un logiciel de conception pour l'électronique qui a permis dans notre cas de créer le Shield pour la carte Arduino UNO. Toutes nos empreintes et plans de notre shield sont disponibles dans notre [kiCad](https://github.com/MOSH-Insa-Toulouse/2021-2022_Karmoudi_Bahaj/blob/main/KiCad.zip) 

### 2.1 Schématique complète

Ci-dessous, la schématique complète de notre circuit : 

<img width="1119" alt="Circuit_Global" src="https://user-images.githubusercontent.com/98756781/163234310-c5dac24e-6cb2-4641-828d-029fb318ab58.png">

Nous pouvons noter aussi la présence de nos modules dont les schématiques et les empreintes seront détaillés dans la section d'après.

### 2.2 Schématique et empreinte des composants

- Module Bluetooth HC-05 

<img width="300" alt="Bluetooth" src="https://user-images.githubusercontent.com/98756781/163250546-80f8b965-5fe9-45e8-9498-64a52b3f48bd.png"> <img width="300" alt="Bluetooth_empreinte" src="https://user-images.githubusercontent.com/98756781/163250585-1ead2f99-e559-4900-90e3-f02ed3c5cdf7.png">

- Encodeur rotatoire KY-040 

<img width="300" alt="Encodeur" src="https://user-images.githubusercontent.com/98756781/163250597-e179f560-ac60-469c-b39b-23e5a3a0cb32.png"> <img width="300" alt="Encodeur_empreinte" src="https://user-images.githubusercontent.com/98756781/163250618-e03651a0-fc67-4e6c-9edf-e04009fa2306.png">

- Ecran OLED

<img width="300" alt="OLED" src="https://user-images.githubusercontent.com/98756781/163250638-e178ca9e-4439-4205-b3ee-b066b4fda9b2.png"> <img width="300" alt="OLED_empreinte" src="https://user-images.githubusercontent.com/98756781/163250654-5d32f72d-84d2-456b-aad5-503e6f83ce70.png">

- Amplificateur opérationnel LT1050

<img width="300" alt="LT1050" src="https://user-images.githubusercontent.com/98756781/163250668-7eefca14-919f-42c7-ac00-781d0aa0e27e.png"> <img width="300" alt="LT1050_empreinte" src="https://user-images.githubusercontent.com/98756781/163250681-a060f38c-9687-40f6-8cae-5fa2e911b794.png">



### 2.3 Création du PCB 

Après avoir fini la schématique et créer les empreintes des différents composants qui n'étaient pas disponibles dans les librairies de Kicad, nous avons pu commencer à créer notre PCB en organisant les composants sur le Shield. Nous avons ensuite procéder au routage pour au final avoir le PCB ci-dessous :

<img width="1119" alt="PCB" src="https://user-images.githubusercontent.com/98756781/163233127-a283cf14-b479-43d0-925e-681a7dbba952.png">

- Visualisation 3D du shield :

<img width="1119" alt="PCB_3D_2" src="https://user-images.githubusercontent.com/98756781/163233176-00b62a34-27b5-43b2-bbe8-2fa7eec47cfb.png">


## 3. Code Arduino

Notre code Arduino nous permet d'afficher un menu sur l'OLED, de naviguer dans ce même menu grâce à un encodeur rotatoire, d'afficher les mesures de la déformation récoltés sur l'OLED en fonction de l'option d'affichage choisie auparvant, et de les envoyer vers notre Android grâce au module bluetooth.

Ci-joint notre code complet : [Code_Projet_Capteur](https://github.com/Imane-Karmoudi/2021-2022_Bahaj_Karmoudi/tree/main/Code_Projet_Capteur) 

- Bibliothèques utilisées : "Adafruit GFX Library" , "Adafruit SSD1306" , "SoftwareSerial library"

## 4. Application Bluetooth

L'application conçue nous permet tout d'abord de détecter si la connexion avec notre PCB est établie ou non, puis de recevoir sur notre smartphone la valeur de la tension délivré par le capteur ainsi que la valeur de la résistance à ses bornes. En plus de nous afficher en temps réel la valeur de ces deux grandeurs, l'application trace un graphique de la variation de la résitance en fonction du temps. 

[CodeAPK]


## 5. Banc de test 

Afin d'étudier les variations relatives de résistance de notre capteur de déformation à base de graphite, nous avons réalisé un banc de test. Le but étant de déterminer la sensibilité du capteur aux différents type de crayons à papier qui sont par ailleurs classées selon leur concentration en graphite (6B,B,HB/2). 

Pour une description détaillée du protocole suivi, du matériel nécessaire, ainsi que l'analyse de nos résultats, je vous invite à lire le document suivant : [Banc de test](https://github.com/MOSH-Insa-Toulouse/2021-2022_Karmoudi_Bahaj/tree/main/Banc%20de%20test)  

## 6. Datasheet 

Ci-joint la Datasheet détaillant les différentes caractéristiques du capteur : [Datasheet](https://github.com/Imane-Karmoudi/2021-2022_Bahaj_Karmoudi/blob/main/Datasheet.pdf) 

## 7. Contact

Pour toutes questions ou informations supplémentaires concernant notre projet, je vous invite à nous contacter par mail : 

- Imane Karmoudi : karmoudi@insa-toulouse.fr
- Fatima Ezzahra Bahaj : Bahaj@insa-toulouse.fr

