const char indexHtml[] PROGMEM = R"(
<!DOCTYPE HTML>
<html>
  <head>
    <title>Arduino web page</title>
    <link rel="stylesheet" href="style.css">
    <script src="script.js" defer></script>
  </head>
  <body>
    <h1>Arduino web page</h1>
    <h2>LED control</h2>
    <button id="led-on">ON</button>
    <button id="led-off">OFF</button>
  </body>
</html>
)";