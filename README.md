# Documentation du Projet Point d'Accès Wi-Fi

## 0. Introduction

Ce projet transforme un ESP32 en point d'accès Wi-Fi sécurisé et dynamique. Il génère un mot de passe aléatoire à chaque connexion client et tente de se connecter à des réseaux Wi-Fi détectés en utilisant une liste de mots de passe. Il enregistre les connexions réussies pour optimiser les tentatives futures.

## 1. Installation

1. Installer **Arduino IDE**.
2. Ajouter la carte **ESP32 DEV MODULE** dans le gestionnaire de cartes.
3. Installer la bibliothèque `esp32` dans le gestionnaire de bibliothèques.
4. Flasher le code sur un ESP32.

## 2. Architecture Technique

### 2.1. Point d'accès Wi-Fi

- **Nom du réseau (SSID)** : `wifi_m2dfs_milan`
- **Mot de passe** : Généré aléatoirement à partir d'une liste.
- **Mise à jour du mot de passe** : Lorsque qu'un client se connecte, le mot de passe change.

### 2.2. Gestion des événements Wi-Fi

- `WIFI_EVENT_AP_STACONNECTED` : Un client se connecte → le mot de passe du point d'accès est changé.
- `WIFI_EVENT_AP_STADISCONNECTED` : Un client se déconnecte.

### 2.3. Scanning et Connexion aux Réseaux Wi-Fi

- Le programme scanne régulièrement les réseaux Wi-Fi disponibles.
- Il tente de se connecter à chaque réseau en utilisant une liste de mots de passe.
- Si une connexion réussit, le réseau est ajouté à la liste des connexions réussies (max 10).
- Un réseau déjà réussi ne sera pas retesté.

## 3. Fonctionnement

### 3.1. Connexion au Point d'Accès

1. **Rechercher le réseau** : Se connecter à `wifi_m2dfs_milan`.
2. **Saisir le mot de passe** : Il est généré aléatoirement par le programme.
3. **Connexion** : Une fois connecté, le mot de passe changera automatiquement.

### 3.2. Connexion aux Réseaux Voisins

1. **Scan régulier des réseaux Wi-Fi**.
2. **Tentative de connexion** à chaque réseau avec tous les mots de passe de la liste.
3. **Ajout des succès** à la liste des connexions réussies.

### 3.3. Affichage dans le terminal série

- Les réseaux détectés.
- Les essais de connexion.
- Les connexions réussies.
- Les échecs et les changements de mot de passe.

## 4. Récapitulatif des Tests

### 4.1. Vérification du Point d'Accès

1. Vérifier que le réseau `wifi_m2dfs_milan` est disponible.
2. Tester la connexion avec un mot de passe généré aléatoirement.
3. Vérifier le changement du mot de passe à chaque connexion.

### 4.2. Test de Connexion aux Réseaux Voisins

1. Vérifier que le scan des réseaux s'exécute.
2. Confirmer que les connexions réussies sont bien enregistrées.
3. S'assurer que les réseaux déjà réussis ne sont pas retestés.

### 4.3. Gestion des Erreurs

1. Tester avec des mots de passe incorrects pour voir si le programme continue les essais.
2. Vérifier l'affichage des erreurs et des succès dans le terminal série.

## 5. Fonctionnalités Bonus

- **Changement automatique du mot de passe à chaque connexion client.**
- **Scan et connexion automatique aux réseaux Wi-Fi voisins.**
- **Optimisation des essais en évitant les réseaux déjà réussis.**

## 6. Conclusion

Ce projet permet de gérer un point d'accès Wi-Fi dynamique avec une sécurité améliorée. Il assure une connexion optimisée aux réseaux disponibles tout en enregistrant les succès pour réduire les tentatives inutiles.

