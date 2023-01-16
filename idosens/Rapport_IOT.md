# Rapport Projet IOT:  Generation de QRCode

## Objectif du projet : 
Ce projet permet d’envoyer une url d’un serveur à un boîtier e-paper via une liaison LoraWan. Le boîtier génère et affiche par la suite un qr-code correspondant à l’url envoyée.Cela peut permettre de nombreuses utilisations, par exemple : On peut envisager une course d’orientation “nouvelle génération” qui permettrait aux participants de chercher et de scanner les qr-codes. On pourrait aussi faire de la gestion de file d’attente mais aussi de la gestion de rondes de surveillance.
Dans ce projet nous utilisons une écran idosens pour afficher le qr code généré. De base l’écran idosens était un système permettant de surveiller des pièces ou des lieux éloignés sans faire appel à une connexion Internet. Il était destiné particulièrement bien aux caves, aux garages, aux abris de jardins, aux remises et autres dépendances. Depuis 2016 le produit n’existe plus dans le marché, donc nous avons récupéré ce produit pour générer des qr-code. 

## Analyse du marché des produits commerciaux concurrents : 
La solution proposée étant à la fois très spécifique et permettant de nombreuses utilisations, il est difficile d’en trouver des produits concurrents. Nous nous sommes cependant penchés sur certaines des utilisations de notre projet pour en évaluer les autres solutions.
Nous pouvons remarquer dans un premier temps qu’il existe depuis longtemps le système des tickets avec un simple numéro pour gérer efficacement l’heure de passage des clients. Cette solution est plutôt simple et déjà implémentée mais elle a cependant le problème de dépenser des ressources comme du papier. Nous avons également la solution Izyfil qui consiste en une borne tactile de gestion de file d’attente. Cette borne permet de spécifier la raison de l’attente du client et lui imprime un ticket en fonction de la file d’attente vers laquelle le client doit se diriger. On a ici une solution très performante mais qui a, comme pour la solution précédente, le désavantage de beaucoup consommer mais également de toujours imprimer du papier. Notre solution prend ici un avantage par rapport aux autres.
Il existe également d'autres produits qui gèrent le QR code qui génèrent des QR codes pour gérer les files d'attente dans les restaurants et envoient des notifications aux utilisateurs lorsqu'une table est disponible. Voici quelques exemples:

**Qless:** une plateforme de gestion de files d'attente qui utilise des QR codes pour permettre aux clients de rejoindre une file d'attente virtuelle et de recevoir des notifications lorsqu'une table est disponible.


**Waitlist Me:** un système de gestion de files d'attente qui utilise des QR codes pour permettre aux clients de rejoindre une file d'attente virtuelle et de recevoir des notifications lorsqu'une table est disponible.


**TableUp:** une solution de gestion de file d'attente pour les restaurants qui utilise des QR codes pour permettre aux clients de rejoindre une file d'attente virtuelle et de recevoir des notifications lorsqu'une table est disponible.

## L’architecture globale du systèmes : 

On utilise ici un boîtier idosens sensor, le boitier permet d’afficher des qr code. Pour développer notre produit nous avons utilisé une carte STM32 Nucleo-32, la carte téléverse le programme développé sur le boîtier.. 
L'architecture globale de ce système comprend donc plusieurs éléments :


**Le boîtier idosens sensor** : l'élément physique du système. Il est composé d'une carte électronique et d'un écran e-ink pour afficher des QR codes. Il est alimenté par une source USB.


**Une carte STM32 Nucleo-32** : utilisée pour développer le programme qui est ensuite téléversé sur le boîtier.


**Le protocole LoRaWAN** : utilisé pour recevoir l’URL et ensuite envoyer le qr code. 


**Chirp Stack:** serveur qui permet d’afficher les données envoyées par le LoRaWAN de les rendre accessibles à distance pour une analyse ou une utilisation ultérieure.
Ensemble, ces éléments forment un système qui permet de collecter des données à partir d'un boîtier physique, de les stocker dans le cloud et de les envoyer au boîtier. 

## Sécurité globale du système : 

On envoie les données cryptées avec une clef de hachage. On envoie un URL qui contient l’heure en seconde depuis l’epoch de Linux, l’identifiant de l’écran idosens signé. On chiffre l’URL avec un clé globale, ce qui permet de protéger les données envoyées de manière efficace lorsqu'elles sont transmises. Cela implique l'utilisation d'une clé de chiffrement unique pour chiffrer toutes les données, plutôt que d'utiliser des clés différentes pour chaque session de communication ou pour chaque QR code. Cela rend le déchiffrement des données plus difficile pour les personnes non autorisées, car ils doivent d'abord découvrir la clé de chiffrement globale avant de pouvoir accéder aux données.






