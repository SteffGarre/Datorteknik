Stacking Game!
	
1.	Mål och krav
Målet med projektet är att utveckla ett spel baserat på arkadspelet Stacker samt att uppfylla kraven för ett avancerat projekt. Utvecklingen görs med hjälp 
av ChipKIT Uno32 samt Basic I/O Shield. Programmering av spelet görs i C.

1.1 Beskrivning av spel
Målet med spelet är att stapla block som rör sig i sidled, där blockens hastighet ökar och storlek minskar ju högre upp spelaren kommer. Spelet når sitt slut 
när spelaren når toppen av skärmen eller helt missar att stapla blocken.

1.2 Förutsättningar/Regler
Ett set består vid start av fyra block. När spelaren når den första nivån (ca 1/3 av skärmen) minskar set-storleken till tre block, om spelaren når den sista
nivån (ca 2/3 av skärmen) minskar set-storleken till två block. Hastigheten ökar efter varje nivå.
Om spelaren delvis missar att stapla blocken minskar set-storleken.

1.2.1 Funktioner som har implementeras:
•	Spelaren kan kontrollera spelet via knapparna på Basic I/O Shield.
•	Spelet stödjer en high score lista.
•	Spelet stödjer olika svårighetsgrader baserade på spelets nivå.
•	En spelarvänlig marginal för att matcha block.
•	Om ett block inte matchar så renderas detta på tidigare block.
•	En life counter visas på displayen och sjunker när spelaren förlorar ett liv.
•	En bakgrundsmåne som åker i X och Y-led.
•	Spelets logo visas på toppen av displayen.



2.	Lösning
All utveckling av projektet har utförts med hjälp av ChipKIT Uno32 samt Basic I/O Shielden. 
All kod skrevs i programmeringsspråket C. För all kommunikation samt delning av mindre kodsekvenser användes Discord. Spelet har utformats för att fungera 
på OLED displayen på Basic I/O Shielden och styras med hjälp av Basic I/O Shielden knappar för att bestämma när blocken i rörelse ska stanna.



Stacker är ett spel med en enkel logik. Enligt gemensamt beslut har vi prioriterat de grundläggande kodavsnitten och funktionerna som t.ex. att få ett block 
att röra sig på skärmen och att implementera knappfunktioner för att få blocken att stanna på vald position. Med detta i åtanke har test och utveckling av 
spelet gjorts enligt följande:

1.	Som första steg har vi gått igenom kursens färdiga templates och tidigare tillgängliga projekt för inspiration. Detta hjälpte oss att få en bild av hur
en eventuell sammanställning av vårt projekt kunde komma att se ut.

2.	En stor del av projektet har gått till att få kontroll över displayen. Efter flera misslyckanden lyckades vi hantera displayen genom att släcka/tända 
alla pixlar och skriva ut strängar av text.

3.	Vi implementerade en rektangel (6x10 pixlar) som rörde sig i Y-led (displayen hanterades i horisontellt läge) och testades i olika hastigheter.
En stor utmaning var att hantera flera rektanglar samt få kontroll över uppdateringen av displayen och få detta att fungera med Basic I/O Shieldens knappar. 

4.	En fungerade start- och förlorarmeny skapades som fungerade tillsammans med spelet. I detta steg hade vi en stadig grund och valde att fokusera på 
detaljer såsom att få block att matcha samt att designa om rektangeln till ett set av block.

5.	När steg 4 var klart kunde vi under de sista dagarna fokusera på att lägga till funktioner som life counter, high score lista, animerad måne och 
logo och till slut slå ihop allt till ett fungerande spel.


