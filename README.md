# Documentation du Projet Point d'Accès Wi-Fi

## 1. Introduction

Ce projet crée un point d'accès Wi-Fi sur une plateforme basée sur un microcontrôleur ESP32. Le programme génère un mot de passe aléatoire pour chaque connexion, le change dès qu'un client se connecte et essaie de se connecter à des réseaux Wi-Fi détectés. Ce système peut être utilisé dans des environnements où l'on souhaite sécuriser l'accès tout en permettant la gestion dynamique des connexions.

## 2. Architecture Technique

### 2.1. Point d'accès Wi-Fi

Le programme transforme un microcontrôleur ESP32 en point d'accès Wi-Fi. Il utilise la bibliothèque `WiFi.h` pour gérer les connexions. Le SSID du point d'accès est fixe (`wifi_m2dfs_milan`), mais le mot de passe change de manière aléatoire parmi une liste pré-définie.

- **Nom du réseau (SSID)** : `wifi_m2dfs_milan`
- **Mot de passe** : Un mot de passe est sélectionné au hasard parmi une liste définie. Lorsqu'un client se connecte, le mot de passe est modifié.

### 2.2. Fonctionnement de la Connexion et du Changement de Mot de Passe

- Lorsqu'un client se connecte au point d'accès, un événement est déclenché (`WIFI_EVENT_AP_STACONNECTED`), et le mot de passe du point d'accès est changé de manière aléatoire.
- Les réseaux Wi-Fi sont scannés, et les connexions réussies (avec des mots de passe valides) sont enregistrées dans une liste.
- Le mot de passe du point d'accès change périodiquement pour chaque nouvelle connexion afin d'améliorer la sécurité.

### 2.3. Comptabilisation des Connexions Réussies

Le programme conserve une liste des réseaux Wi-Fi auxquels il a pu se connecter avec succès. Un maximum de 10 connexions réussies est stocké.

### 2.4. Scanning et Connexion aux Réseaux

Le programme scanne tous les réseaux disponibles et tente de se connecter à ceux dont le SSID commence par `wifi_m2dfs_`. Pour chaque réseau trouvé, il essaie tous les mots de passe dans la liste.

## 3. Fonctionnement

### 3.1. Connexion au Point d'Accès Wi-Fi

1. **Rechercher le réseau Wi-Fi** : Sur un appareil (ordinateur, smartphone), recherchez le réseau nommé `wifi_m2dfs_milan`.
2. **Saisir le mot de passe** : Le mot de passe est généré de manière aléatoire à partir de la liste dans le programme.
3. **Connexion** : Une fois connecté, le mot de passe sera automatiquement modifié, et vous serez autorisé à vous connecter à nouveau en utilisant un mot de passe valide.

### 3.2. Test de Connexion à d'autres Réseaux Wi-Fi

Le programme recherche également des réseaux Wi-Fi voisins qui commencent par `wifi_m2dfs_` et essaie de s'y connecter avec les mots de passe définis.

1. **Scan des réseaux** : Chaque réseau détecté avec un SSID correspondant à `wifi_m2dfs_` sera testé avec tous les mots de passe.
2. **Connexion réussie** : Lorsqu'une connexion est établie, le réseau est ajouté à la liste des connexions réussies.

### 3.3. Messages et Résultats

Le programme affiche les informations suivantes dans le terminal série :
- Le changement du mot de passe à chaque connexion.
- Les réseaux Wi-Fi détectés.
- Les connexions réussies.
- Les erreurs en cas de tentative de connexion infructueuse.

## 4. Récapitulatif des Tests

Voici les étapes pour tester et vérifier que tout fonctionne comme prévu :

### 4.1. Vérification de la création du point d'accès

1. Vérifiez que le microcontrôleur crée un point d'accès Wi-Fi avec le SSID `wifi_m2dfs_milan`.
2. Le mot de passe doit être généré aléatoirement parmi les mots définis dans le code.

### 4.2. Test de connexion d'un client

1. Connectez un appareil au réseau `wifi_m2dfs_milan` avec le mot de passe généré.
2. Une fois connecté, le mot de passe du point d'accès doit être modifié.

### 4.3. Test de la connexion aux réseaux voisins

1. Assurez-vous que le programme scanne les réseaux Wi-Fi voisins et essaie de se connecter à ceux qui commencent par `wifi_m2dfs_`.
2. Vérifiez que les connexions réussies sont correctement ajoutées à la liste des réseaux connectés.

### 4.4. Test de la gestion des erreurs

1. Testez avec des mots de passe incorrects pour vérifier que le programme passe au mot de passe suivant et continue d'essayer.
2. Assurez-vous que le programme affiche les erreurs et les succès dans le terminal série.

## 5. Fonctionnalités Bonus (si implémentées)

- **Changement dynamique du mot de passe** : Chaque client connecté entraîne le changement du mot de passe du point d'accès, augmentant ainsi la sécurité.
- **Scan des réseaux voisins** : Le programme scanne régulièrement les réseaux Wi-Fi et tente de se connecter à ceux qui correspondent à un certain format de SSID.

## 6. Conclusion

Ce projet permet de gérer un point d'accès Wi-Fi avec une sécurité dynamique. Le mot de passe change à chaque nouvelle connexion, et le programme tente de se connecter à des réseaux voisins. Ce système peut être utilisé dans des environnements nécessitant une gestion sécurisée des connexions et une comptabilisation des réseaux Wi-Fi trouvés.

