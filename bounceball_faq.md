# Bounceball FAQ

*NB! Spillet må Qmakes i Release på Macen min for at den skal finne alle filene.*

## Klassediagram
Se bilde "bounceball_class_hierarchy_final.png".

## Moduler
**Bounceball** opprettes i main og starter et spill (**Game**).

### Engine
**Game** er selve hjertet i programmet, og vil ta for seg  å skifte menyer (**Menu**), ta imot knappetrykk fra menyene, og opprette levels (**Level**). Den vil også lese inn filnavn på alle levels fra disk.
Game arver *QGraphicsView*, vars hovedfunksjon er å visualisere innholdet i en *QGraphicsScene*.

**Level** vil være det "spillbare" i Bounceball. Dette er en QGraphicsScene. Denne vil også ha en *QTimer*, som kan stoppes og startes, som har som oppgave og animere(avancere) objekten på scenene.
Den vil også ta seg ann og og notfiere Game om nødvendige kall.
Når en level er aktiv i Game, så vil mouseMoveEvents bli registrert på scene-nivå, og ikke game-nivå. Dette vil då bevege **Paddle**.
Level vil i hovedsak bli populert av **GameObject**s.
Level er også **Scoreboard**, vars oppgave er å oppdatere og vise frem poeng.

### Entites
**GameObject** er objekt som er interaktive i spillet (på en Level). Disse arver *QGraphicsItem* som gjør det mulig å plassere disse i en scene(Level). Det som kjennetegner et GameObject er:

* Bredde og høyde.
* paint() for å bestemme hvordan objektet skal tegnes på skjermen
* advance() for å bestemme hva som skal skje hva gang Level avancerer en frame.
* En lydeffekt som bestemmer hvilket lyd objektet skal spille opp.
* handleCollision() som sier hvordan objektet skal bete seg ved interaksjon av andre GameObjects.

**Ball** er en ball som beveger seg på en Level. Det er atm. det eneste objektet som beveger seg automatiskt på scenen, med hjelp av interfacet **isVector**. isVector kontrollerer fart og retning som ballen skal bevege seg, med hjelp av sin inre vector-klasse.

**Paddle** er det som spilleren bruker for å forhindre at ballen faller ut av banen. Leveln tar emot mus-bevegelser og sende disse videre til sin Paddle for å flytte denne i sidled på banen.

**Brick** er det som spilleren skal knuse med hjelp av ballen for å få poeng og klare banen. Disse har en gitt healthpoint, og dette representeres med en bestemt farge. Hver gang ballen treffer en brick, vil hp gå ned og bricken skifte farge. Denne sender siden dette videre opp til Level(Scoreboard) som registrerer poengen. Når en bricks hp == 0, vil Level utføre en sjekk som sjekker om banen er fullført, og hvis den er, då avslutte leveln.

### Gui
**Menu** er en meny, som arver QGraphicsScene for å kunne visualiseres i Game. Denne innholder forskjellige mål som brukes til å plassere **Button**s på scenen, og en gitt bakgrund.

Dette er implementerert flere forskjellige representasjoner, som alle bygger på Menu, som alle har sine egna knapper.

**Button** har som oppgave å representere en knapp. Button har også en liste på forskjellige "GameFunctions" som Game vil håndtere. Hvilken knapp som har hvilken funksjon bestems i representasjonen av Menu.
Game vil fange opp tastetrykk på en knapp, og deretter håndtere Buttons GameFunction.

### Helpers
**LevelFactory** oppgave er å opprette en Level for Game. Dette vil gjøres med hjelp av et filnavn, som da oppretter hjelpeobjektet **LevelFile**, og deretter populere Level med Bricks, Ball og Paddle.

**LevelFile** har som oppgave og opprette en datastrøm fra fil, og lesse inn alle tallen fra denne. Disse vil siden bli plassert i en matrise, som LevelFactory siden kan bruke til å legge inn Bricks på riktig sted på Level.
LevelFile vil og kunne sjekke hvis en gitt map har riktig layout i følge reglene som er satt opp.

**MenuFactory** har som oppgave å opprette spesifike menyer til Game. MenuFactory vil ha en liste på menyene som tilbyds, og kunne opprette riktig menye til spillet.


## Styrker
Programmet har mange gode løsninger på forskjellige problem. Jeg vil mene på at det er lagt opp for å enkelt kunne videreutvikles. Dessverre endte det kun opp med standard factories, men muligheten for å implementere andre egenskaper finnes der (kanskje ikke til 100% men nesten..).

Tanken bak mine abstraksjoner er god, og hvis jeg hade haft en bedre forståelse for Qt hade disse blitt mye penere. Takk være realtivt god planlegging har det ikke tilkommet alt for mange, på forhånd ubestemte, klasser.

## Svakheter
**Collision detection** mellom ball og brick blev ikke som jeg tenkt meg. Det endte opp med at jeg tilslutt brukt alldeles for mye tid på dette, og resultatet blev den siste implementasjonen. Dette grunner seg til stor del i mangel på forståelse av Qt og dess collision-detection.

Jo nemre en slutt jeg kom, og ting skulle bindes sammen blev jeg nødt til å legge inn en god del stygge **"up-casts"**. Hade jeg haft bedre peiling på alternativen Qt tilbydd, og en bedre forståelse for hvordan biblioteket fungerer, hade dette kunnet ungås. Alternativen til hade kunnet være å sende Events til applikasjonen (toppnivå), eller bruke signals/slots (dette hade dog kunnet forsemre prestanden etter min forståelse, da dette er ganske heavy). Dette resulterer til en rotete **event-handling**, som også burde være sentralisert.

**Enums** og andre **preferenser(innstillinger)** kanskje kunde og kunnet være mer samlet.

## Refleksjon
Helt plutsleig var fristen kommet, og programmet blev ikke helt ferdig. Mange av mine idéer blev aldrig implementert, og implementering av de siste funksjonene til programmet blev veldig rotete og "kastet inn". Grunnen til dårlig tid skyldes småpussing og problemløsning av små trivielle ting, som sikkert kunnet gjøres senere på prosjektet.

Hade jeg lagd dette programmet pånytt hade jeg nog droppet Qt-biblioteket og opprettet alle datastrukterer selv. Dels for at jeg syns det er gøy, men også for at Qt er otroligt mye å sette seg inn, spesiellt når man knappt hatt noen C++ fra før. Med sikkert over 100 timer i dette prosjektet, vil halvparten ha gått til å google og lese i Qts dokumentasjon.

Alt som alt er jeg fornøyd med spillet mitt, og jeg føler meg nå mye tryggere på C++ og Qt.
