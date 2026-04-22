# 🔹 ft_malcolm 💻 

## 🔹 Objectif du projet

Implémenter une attaque d’ARP spoofing permettant de manipuler la table ARP d’une machine cible.

Ce projet introduit les bases des attaques de type Man-In-The-Middle (MITM), sans en implémenter un véritable (pour des raisons évidentes de sécurité).

---

## 🔹Qu’est-ce qu’une table ARP?

Une table ARP (Address Resolution Protocol) est une table utilisée par une machine pour associer une adresse IP à une adresse MAC.

Elle permet de savoir à quelle carte réseau envoyer les paquets Ethernet.

Exemple : IP = 192.168.1.1 → aa:bb:cc:dd:ee:ff = MAC (Media Access Control)

---

## 🔹Qu’est-ce qu’une attaque MITM ?

Une attaque MITM (Man-In-The-Middle) consiste à s’interposer entre deux machines qui communiquent, de manière transparente.

Victime  <---->  Attaquant  <---->  Gateway


Les deux machines pensent communiquer directement entre elles, alors que l’attaquant intercepte et peut manipuler les échanges.

---

## 🔹Lien avec ft_malcolm

Dans ce projet, nous utilisons l’ARP spoofing pour tromper une machine cible.

Le programme :

- attend une requête ARP broadcast de la cible
- envoie une seule réponse ARP falsifiée
- associant une IP légitime (ex: gateway) à la MAC de l’attaquant

⚠️ Le programme ne met pas en place un MITM complet (pas de forwarding de trafic), il s’arrête après l’envoi de la réponse.

---

## 🔹Utilisation

./ft_malcolm [source ip] [source mac address] [target ip] [target mac adress]

---

## 🔹malcolm_lab

Un environnement Docker permettant de simuler un réseau local sécurisé composé de :

- une machine victime
- une machine attaquante
- une gateway

Le tout orchestré via docker-compose.

---

## 🔹Arborescence

```
├── inc
│   └── malcolm.h
├── libft
│   ├── ft_atoi.c
|	├── ft_memcmp.c
│   ├── ft_memcpy.c
│   ├── ft_memset.c
│   ├── ft_strcmp.c
│   ├── ft_strdup.c
│   ├── ft_strlen.c
│   └── libft.h
├── Makefile
├── malcolm_lab
│   ├── attacker
│   │   └── Dockerfile
│   ├── docker-compose.yml
│   ├── gateaway
│   │   └── Dockerfile
│   ├── script.sh
│   └── victim
│       └── Dockerfile
├── mandatory
│   ├── main.c
│   ├── parsing.c
│   ├── signal.c
│   ├── sniffer.c
│   ├── socket.c
│   └── utils.c
└── README.md
```

---

## 🔹 Techno

- C
- Docker 🐋
