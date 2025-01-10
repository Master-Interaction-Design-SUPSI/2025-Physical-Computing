const char styleCSS[] PROGMEM = R"(
html {
  font-size: 20px;
}
body {
  background-color: blue;
  color: white;
  font-family: sans-serif;
  text-align: center;
}
#led-status {
  width: 8rem;
  height: 8rem;
  border-radius: 4rem;
  border: 0.1rem solid white;
  margin-bottom: 1rem;
  margin-left: auto;
  margin-right: auto;
}
.led-on {
  background-color: white;
}
#potentiometer {
  height: 1rem;
  background-color: white;
  margin-left: auto;
  margin-right: auto;
}
)";