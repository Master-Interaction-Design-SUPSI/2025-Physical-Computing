const char scriptJS[] PROGMEM = R"(
const webSocket = new WebSocket("ws://192.168.4.1:8080");

webSocket.addEventListener("open", (event) => {
  console.log("WebSocket connected!");
})

webSocket.addEventListener("message", (event) => {
  console.log("New message from Arduino: " + event.data);
})

const buttonOn = document.getElementById("led-on");
const buttonOff = document.getElementById("led-off");

buttonOn.addEventListener("click", ()=> {
  webSocket.send("ON");
})

buttonOff.addEventListener("click", ()=> {
  webSocket.send("OFF");
})

)";