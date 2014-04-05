# Bounce Ball

Jeg har som plan å lage et spill som ligner på den gamle klassikern **DX Ball**. Det er mye mulig at spillet blir en kopi som oppfører seg helt likt, men jeg har som mål og prøve å gi det min egen touch.

## Hovedfunksjonalitet

Spillet går ut på at brukern/spilleren styrer en "racket" i sidled som skal forhindre ballen å falle utenfor spillplanen. En "level" består av flere bricks i forskjellige farger som ballen skal treffe for å knuse. Forskjellige farger trenger ulike antall treffer for å "knuse". Spilleren får poeng for å knuse bricksen.

## Krav
- Smart kode - spillet skal være mulig å utvide uten for mye arbeid.
- Polymorfi der det gir mening.
- Exceptions der det gir mening.
- Effektive algoritmer og kalkuleringer som undviker at spillet arbeider unødvendig mye.
- En god mappestruktur.

## Mål
- Minimum 2 levels(maps). Disse skal leses inn fra fil.
- Tracking av high-score.
- Synlig poeng.
- Spillet skal ha en splash screen og en meny der spilleren kan velge å starte et spill.
- Spillet skal bruke OpenGL og kunne kjøres i fullscreen.
- Grafikkbiblioteket i Qt skal brukes (hvis dette ikke er alt for vanskelig)

## Videreutvikling
Disse er ting jeg ønsker å få implementert i spillet, avhenging av hva jeg rekker til.

- Lydeffekter.
- Innlastning av egna sprites på GameObjects.
- Powerups - en brick kan gi ifra seg random powerups som påvirker ballens eller rackets oppførende.
- Level editor - brukeren kan selv lage egen bane som lagres på fil.
- Muligheten og velge hvilken bane som skal spilles.
- Resolution skal være dynamisk, og kalkuleringer skal gjøres utifra denne.

## Utfodringer
- Effektiv "collision detection" (ball-brick og ball-racket) - hvordan dette skal kunne implementeres lurt og for å undgå unødvendige beregninger. Forslag?



