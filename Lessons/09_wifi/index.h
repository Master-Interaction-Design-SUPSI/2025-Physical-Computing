const char indexHtml[] PROGMEM = R"(
<!DOCTYPE HTML>
<html>
  <head>
    <title>Arduino web page</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="style.css">
    <script src="script.js" defer></script>
  </head>
  <body>
    <h1>Arduino web page</h1>
    <h2>LED control</h2>
    <div id="led-status"></div>
    <button id="led-on">ON</button>
    <button id="led-off">OFF</button>
    <h2>Potentimeter</h2>
    <div id="potentiometer"></div>
  </body>
</html>
)";