Bildmatchning
=============

- Ungefärligt antal timmar spenderade på labben (valfritt):
    Ω(1)

- Vad är tidskomplexiteten på "slow.cpp" och din implementation av "fast.cpp",
  uttryckt i antalet bilder (n).

slow: n^2
fast: n


- Hur lång tid tar det att köra "slow.cpp" respektive "fast.cpp" på de olika
  datamängderna?
  Tips: Använd flaggan "--nowindow" för enklare tidsmätning.
  Tips: Det är okej att uppskatta tidsåtgången för de fall du inte orkar vänta
  på att de blir klara.
  Tips: Vid uppskattning av körtid för "slow.cpp" är det en bra idé att beräkna
  tiden det tar att läsa in (och skala ner) bilderna separat från tiden det tar att
  jämföra bilderna. (Varför?)

|--------+-----------+----------+----------|
|        | inläsning | slow.cpp | fast.cpp |
|--------+-----------+----------+----------|
| tiny   |    169    |   256    |   147    |
| small  |    850    |   1048   |   773    |
| medium |    3294   |   4669   |   3218   |
| large  |    55729  |   405074 |   49411  |
|--------+-----------+----------+----------|


- Testa olika värden på "summary_size" (exempelvis mellan 6 och 10). Hur
  påverkar detta vilka dubbletter som hittas i datamängden "large"?
  
  SVAR: Vi kan se att om vi minskar vår "summary_size" så ökar mängden matchningar dock får vi större risk för felaktiga matchningar, 
        i vårat fall stämde alla matchningar med "summary_size" 6.
        Samtidigt kan vi se att om vi ökar vår "summary_size" så minskar mängden matchningar men risken för felaktiga minskar.


- Algoritmen som implementeras i "compute_summary" kan ses som att vi beräknar
  en hash av en bild. Det är dock inte helt lätt att hitta en bra sådan funktion
  som helt motsvarar vad vi egentligen är ute efter. Vilken eller vilka
  egenskaper behöver "compute_summary" ha för att vi ska kunna lösa problemet i
  labben? Tycker du att den givna funktionen uppfyller dessa egenskaper?

  SVAR: "compute_summary" bör kunna krympa ner bilder till en lätthanterlig jämförbar nyckel. 
        Denna ska vi kunna använda för att se om två bilder får samma "nyckel" för att konstatera att bilderna liknar varandra.


- Ser du några problem med metoden som används i labben? Kan du komma på andra
  metoder för att identifiera bilder som liknar varandra? Ditt/dina förslag behöver
  inte kunna mäta sig med det som beskrivs i labhandledningen. Vad har dina förslag
  för för- och nackdelar jämfört med det som föreslås i labben? Fokusera exempelvis
  på vilka typer av olikheter som hanteras, eller vilken tidskomplexitet de har.
  Exempelvis går det inte att implementera metoden i "slow.cpp" med samma
  tidskomplexitet som metoden i "fast.cpp".

  SVAR: Att jämföra ljusstyrka kommer med nackdelen att två bilder som egentligen inte är likadana kan ha samma skillnad i ljusstyrka.
        
        Ett bättre sätt skulle vara att jämföra färger då det är detta som bäst skiljer bilder åt, men detta kommer med nackdelen att det 
        det tar längre tid. För att man skulle vara tvungen att göra tre olika kontroller per ner shrinkad pixel där alla tre måste matcha, 
        och att hålla koll på matchningarna skulle troligtvis kräva en vector av bools som i sin tur tar längre tid att kontrollera. 




