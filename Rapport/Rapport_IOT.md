# Rapport Projet IOT:  Génération de QRCode

## Introduction et Objectif du projet : 
Nous avons travaillé au FabLab durant ce projet afin de réaliser un boitier permettant de donner des justificatifs de présence. 
Ce projet permet d’envoyer une clef de chiffrement d’un serveur à un boîtier e-paper via une liaison LoraWan. Le boîtier génère et affiche par la suite un qr-code correspondant à une url datée construite et chiffrée avec cette clef. On peut ainsi s'en servir de justificatif de présence. Cela peut permettre de nombreuses utilisations, par exemple : On peut envisager une course d’orientation “nouvelle génération” qui permettrait aux participants de chercher et de scanner les qr-codes. On pourrait aussi faire de la gestion de file d’attente mais aussi de la gestion de rondes de surveillance.
Dans ce projet nous utilisons une écran idosens pour afficher le qr code généré. De base l’écran idosens qui a servi pour réaliser un prototype était un système permettant de surveiller des pièces ou des lieux éloignés sans faire appel à une connexion Internet. Il était destiné particulièrement bien aux caves, aux garages, aux abris de jardins, aux remises et autres dépendances. Depuis 2016 le produit n’existe plus dans le marché, donc nous avons récupéré ce produit pour générer des qr-code. 

## Analyse du marché des produits commerciaux concurrents : 
La solution proposée étant à la fois très spécifique et permettant de nombreuses utilisations, il est difficile d’en trouver des produits concurrents. Nous nous sommes cependant penchés sur certaines des utilisations de notre projet pour en évaluer les autres solutions.
Nous pouvons remarquer dans un premier temps qu’il existe depuis longtemps le système des tickets avec un simple numéro pour gérer efficacement l’heure de passage des clients. Cette solution est plutôt simple et déjà implémentée mais elle a cependant le problème de dépenser des ressources comme du papier. Nous avons également la solution Izyfil qui consiste en une borne tactile de gestion de file d’attente. Cette borne permet de spécifier la raison de l’attente du client et lui imprime un ticket en fonction de la file d’attente vers laquelle le client doit se diriger. On a ici une solution très performante mais qui a, comme pour la solution précédente, le désavantage de beaucoup consommer mais également de toujours imprimer du papier. Notre solution prend ici un avantage par rapport aux autres.
Il existe également d'autres produits qui gèrent le QR code qui génèrent des QR codes pour gérer les files d'attente dans les restaurants et envoient des notifications aux utilisateurs lorsqu'une table est disponible. Voici quelques exemples:

**Qless:** une plateforme de gestion de files d'attente qui utilise des QR codes pour permettre aux clients de rejoindre une file d'attente virtuelle et de recevoir des notifications lorsqu'une table est disponible.


**Waitlist Me:** un système de gestion de files d'attente qui utilise des QR codes pour permettre aux clients de rejoindre une file d'attente virtuelle et de recevoir des notifications lorsqu'une table est disponible.


**TableUp:** une solution de gestion de file d'attente pour les restaurants qui utilise des QR codes pour permettre aux clients de rejoindre une file d'attente virtuelle et de recevoir des notifications lorsqu'une table est disponible.

On a ci dessous un tableau résumant les avantages et inconvénients de ces concurrents : 

| Produit concurrent       | Avantages                 | inconvénients                 |
|--------------------------|---------------------------|-------------------------------|
|IzyFil / Waitlist Me / Table Up| Gestion des rendez-vous : - moins d’attente pour les utilisateurs et les clients - moins de stress pour les agents et les employés - satisfaction de toute le monde|Aucun interaction humain|
|IzyFil | Gestion de fil d’attente : - Diminue la sensation d'attente et organise l'accueil des clients- Traite de manière équitablement les visiteurs - Informe et sensibilise grâce à l'affichage dynamique intégré|- Aucun interaction humain - Ne priorise pas les personnes en situation prioritaire|
|IzyFil | Gestion des tickets :  - Simple et accessible, il ne nécessite pas de télécharger une application - Informe du temps d'attente et de l'état de sa demande - Hygiénique les tickets virtuel évite tout contact avec un appareil publique -diminuer l'attente éventuelle - Permet d'avoir moins de matériel à maintenir - Plus économique et écologique, il évite l'impression de tickets papier - Présente une meilleure image des services|Ne priorise pas les personnes en situation prioritaire (personnes âgées , personnes à mobilité réduite ...)|

## L’architecture globale du systèmes : 

On utilise ici un boîtier idosens sensor, le boitier permet d’afficher des qr code. Pour développer notre produit nous avons utilisé une carte STM32f0 discovery, la carte téléverse le programme développé sur le boîtier.
L'architecture globale de ce système comprend donc plusieurs éléments :


**Le boîtier idosens sensor** : l'élément physique du système. Il est composé d'une carte électronique et d'un écran e-paper pour afficher des QR codes. Il est alimenté par une source USB.

<p align="center">
  <img src="idosens.jpg" width="200">
  <br>
  <i>L'écran Idosens</i>
</p>

**Une carte STM32f0 discovery** : utilisée pour développer le programme qui est ensuite téléversé sur le boîtier.

<p align="center">
  <img src="STM32F0DISCOVERY.jpg" width="400">
  <br>
  <i>carte STM32f0</i>
</p>

**Le protocole LoRaWAN** : utilisé pour recevoir l’URL et ensuite envoyer le qr code. 


**Chirp Stack:** serveur qui permet d’afficher les données envoyées par le LoRaWAN de les rendre accessibles à distance pour une analyse ou une utilisation ultérieure.
Ensemble, ces éléments forment un système qui permet de collecter des données à partir d'un boîtier physique, de les stocker dans le cloud et de les envoyer au boîtier. 

## Sécurité globale du système : 

On envoie les données cryptées avec une clef de hachage. On envoie un URL qui contient l’heure en seconde depuis l’epoch de GPS, l’identifiant de l’écran idosens signé. On chiffre l’URL avec un clé globale, ce qui permet de protéger les données envoyées de manière efficace lorsqu'elles sont transmises. Cela implique l'utilisation d'une clé de chiffrement unique pour chiffrer toutes les données, plutôt que d'utiliser des clés différentes pour chaque session de communication ou pour chaque QR code. Cela rend le déchiffrement des données plus difficile pour les personnes non autorisées, car ils doivent d'abord découvrir la clé de chiffrement globale avant de pouvoir accéder aux données.

## Le respect de la vie privée du service (RGPD) : 

Le respect de la vie privée est un enjeu crucial pour tout service qui génère des QR codes avec LoRaWAN, et il est important de prendre en compte les différents risques d'atteinte à la vie privée qui peuvent survenir dans ce cas : 


**Stockage des données :** Les QR codes générés peuvent contenir des informations sensibles, il est important de s'assurer que ces données sont stockées de manière sécurisée. L’URL qu’on envoie est un URL signé donc elle est difficile d'accéder au URL.  
  
  
**Vie privée des utilisateurs :** Il est important de s'assurer que les QR codes ne sont pas utilisés pour surveiller les utilisateurs de manière non autorisée. Notre produit n’atteint pas la  vie privée des utilisateurs du boîtier puisque la seule information qui transite est que le qr code a été flashé. On pourrait imaginer un scénario où le système qui envoie les qr codes se fait hacker et enverrait des qr codes endommagés. Cependant, cela ne concerne pas notre programme qui gère la liaison entre le serveur et le boîtier.
  
  
**Prévention de la fuite des données :** les données stockées dans les QR codes ne sont pas diffusées à des tiers non autorisés. 


## L’architecture matérielle du produit : 


**Boîtier en plastique :** Il sert de protection pour les composants électroniques et de support pour l'écran e-paper.


**PCB (Circuit imprimé) :** Pour connecter les différents composants électroniques et pour permettre la communication entre ces composants.


**Ecran e-paper :** Pour afficher les qr-code. Il est alimenté par une batterie ou une alimentation fixe en fonction de l’utilisation.


**Batterie / Alimentation :** Pour alimenter l'écran e-paper et les autres composants.


## Le coût de la BOM de votre produit :

On a réalisé le prototype à l’aide d’un boîtier idosens comprenant déjà un écran e paper, un pcb et un boitier. Nous allons donc développer le coût de chaque composant si on devait le réaliser en gros. Dans le cas de la création de 5 000 boîtiers : 


**Coût du boîtier en plastique :** Environ 0,50 € par unité, soit un coût total de 2500 € pour 5000 exemplaires.


**Coût du PCB :** Environ 5 € par unité, soit un coût total de 25 000 € pour 5000 exemplaires.


**Coût de l'écran e-paper :** Environ 15 € par unité, soit un coût total de 75 000 € pour 5000 exemplaires.


**Coûts de fabrication :** Environ 10 € par unité, soit un coût total de 50 000 € pour 5000 exemplaires.


## Le coût de certification ETSI du produit et le coût de certification LoRa Alliance du produit : 

Le coût de certification ETSI pour un produit peut varier en fonction de plusieurs facteurs  on peut toutefois estimer un coût de certification d'environ 5000 à 10000€ pour un produit standard.

Concernant les coûts de certification Lora Alliance, on peut estimer à environ 2500€ la certification. 

## Une implémentation du logiciel embarqué de l’objet QRCode generation : 

Nous donnons ci-dessous les points importants du logiciel embarqué pour générer le QR code:

- Intégrer une bibliothèque de génération de QR code, comme celle disponible dans RIOT, à notre projet.

- Utiliser le protocole LoraWan pour envoyer une clef d'un serveur et la recevoir sur le boitier pour signer une URL 

- Utiliser la fonction pour générer le QR code avec les données souhaitées dans notre cas une URL qui contient une signature,l'identifiant de l'écran Idosens et une date calculée depuis l'epoch de GPS.

- Utiliser l’écran Idosens pour afficher le QR code généré.

- Répéter ces opérations toutes les minutes (modifiable)

Le schéma suivant montre le logiciel embarqué implémenter dans le boîtier 

<p align="center">
  <img src="Schema_explicatif.jpg" width="400">
  <br>
  <i>Schéma explicatif</i>
</p>

## Le format des messages LPP :

Le format de messages uplink et downlink échangés pour les objets LoRaWAN est généralement défini en utilisant le format LPP (LoRaWAN Payload Protocol). Qui est un protocole de couche application qui permet d'encoder et de décoder des données pour les transmissions LoRaWAN. Il fournit des fonctionnalités de codage pour un large éventail de types de données, tels que les entiers, les flottants, les chaînes de caractères, les booléens, etc. Dans notre cas, le format de LPP est une chaîne de caractère. LPP nous permet d'encoder et de décoder l’URL pour les transmissions LoRaWAN.
## Estimation de la durée de vie de la batterie du produit : 

Notre objet peut fonctionner sous batterie et on peut donner une estimation en prennant pour hypothèses que le débit de données est du 0.3 kbps, que la puissance de transmission est de 14 dBm et que la capacité de la batterie est de 2000 mAh. Ces hypothèses peuvent bien sûr changer en fonction de la batterie mais on obtiendrait en moyenne :
  - Pour une fréquence de transmission de 1 fois par jour, une durée de vie d'environ 8 ans.
  - Pour une fréquence de transmission de 1 fois par heure, une durée de vie d'environ 6 mois.
  - Pour une fréquence de transmission de 1 fois par minute, une durée de vie d'environ 4 mois.
 
Dans notre cas, on envisage une utilisation d'une fois par minute on aurait donc une durée de batterie d'environ 4 mois. Bien sûr ce résultat peut être voué à changer selon les conditions du client mais également si ce dernier a la possibilité de le brancher directement à une alimentation


## Analyse du cycle de vie du produit : 

L'analyse du cycle de vie (ACV) de notre produit "durable" et "sobre" consiste à évaluer les impacts environnementaux et sociaux de ce produit tout au long de son cycle de vie, c'est-à-dire de sa conception à sa fin de vie.
Les étapes clés de l'ACV comprennent l'acquisition des matières premières, la production, l'utilisation, l'élimination et le recyclage. Donc l'accent est mis sur les phases suivantes : 

- Phase de recherche et développement : Pour concevoir le produit


- Phase de production : Création des PCB, boîtiers et écrans e paper ainsi que leur assemblage


- Phase d’utilisation : 
     - La durée de vie de l'écran e-paper est estimée à environ 5 ans ce qui est relativement long comparé aux écrans traditionnels.
     - Les composants électroniques du produit peuvent être remplacés s'ils sont endommagés ou défectueux.
     - Des mises à jour logicielles peuvent être effectuées pour améliorer les performances du produit.


- Phase de fin de vie : 
    - Le boîtier en plastique, le PCB et l'écran e-paper peuvent être recyclés pour réutiliser les matières premières. Il ne faut cependant pas oublier que le recyclage est coûteux et pas toujours optimal.
    - Les consommateurs peuvent également choisir de donner leur produit en fin de vie à des organisations caritatives ou à des programmes de recyclage.
  
Donc notre produit utilise des matériaux recyclables, à une conception pour une longue durée de vie,facile à réparer et à recycler.

## Métriques du logiciel embarqué : 

Pour réaliser ce projet, nous avons utiliser du code qui était déjà développé pour le boitier idosens. Nous avons réalisé environ 60 lignes de code pour la génération du qr-code en nous aidant des librairies de RIOT OS. Nous n'avons pas compté dans ces métriques les lignes de code pour la partie LoraWan puisque ces dernières n'ont pas pu être mises à profit.


## Problèmes rencontrés :

Durant ce projet, nous avons été confrontées à de nombreux problèmes techniques. Les plus impactants ont été l'impossibilité de connecter le boîtier idosens au serveur LoraWan ce qui nous a empêché de faire toute la partie IoT. Enfin, suite à des problèmes que nous pensons être connectiques, le boîtier en fin de projet ne pouvait plus se connecter à l'application CubeProgrammer ce qui nous a empêché de téléverser le programme sur le boitier et ainsi de faire toute la phase de test.

## Conclusion :

Ce projet, bien que diminué par les nombreux problèmes techniques rencontrés a été très enrichissant. Il nous a permis d'apprendre à s'adapter plus rapidement aux problèmes, à valoriser les recherches dans ce qui a déjà été fait afin d'optimiser notre temps mais également a avoir une vision plus globale de la conception d'un produit électronique en étudiant ces coûts de fabrication, ses potentiels concurrents et son cycle de vie.

















