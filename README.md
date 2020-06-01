# Driverbot
## Projektet
Våran uppgift var att bygga en bil av lego som man sedan kan styra trådlöst. Jag valde att styra bilen genom en hemsida gjort i Vue. Skolan stängdes och vi var tvugna att göra allting hemifrån vilket strulade till det väldigt mycket men förutom det gick projektet framåt och nu är det en "fungerande" bil.


## Hur fungerar det?
Hemsidan använder sig av sliders för att ställa in värdena för hastighet och vinkeln. Därefter fyller den i värdena så att de finns 0 före tills hela värdet för ex. hastighet är fyra tecken och gör samma sak för vinkeln, sedan skickar den värdena med MQTT. Mikrokontrollern subscribar till topicen och tar emot payloaden. Därefter substringar den dem fyra första värdena som hastighet och de fyra sista som vinkeln. Därefter tar den hastighet - 100 för att ta reda på vad riktningen är, om det är negativt ska den köra bakåt och tvärtom. Sedan använder de värdena för att få bilen att köra. 

## Vue Setup
- npm install
- npm run serve
