const char scriptJS[] PROGMEM = R"(
const buttonOn = document.getElementById("led-on");
const buttonOff = document.getElementById("led-off");
const ledStatus = document.getElementById("led-status");
const potentiometer = document.getElementById("potentiometer");

const webSocket = new WebSocket("ws://192.168.4.1:8080");

webSocket.addEventListener("open", (event) => {
  console.log("WebSocket connected!");
})

webSocket.addEventListener("message", (event) => {
  console.log("New message from Arduino: " + event.data);
  if(event.data == "ON") {
    ledStatus.classList.add("led-on");
  }
  else if(event.data == "OFF") {
    ledStatus.classList.remove("led-on");
  }
  else {
    potentiometer.style.width = event.data + "%";
  }
})

buttonOn.addEventListener("click", ()=> {
  webSocket.send("ON");
  ledStatus.classList.add("led-on");
})

buttonOff.addEventListener("click", ()=> {
  webSocket.send("OFF");
  ledStatus.classList.remove("led-on");
})

)";