#ifndef HTML_H
#define HTML_H

;const char html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 WebSite</title>
    <style>
        .block {
            top: 60%;
        }

        .text {
            text-align: center;
            font-family:'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif
        }
        
        .button-block {
            margin: 0 auto;
            width: 60%;
            height: 5rem;
        }

        .button {
            width: 100%;
            height: 100%;
            border-radius: 40px;
            border: none;

            color: #ffffff;
            background-color: #2369b4;

            transition: linear 0.3s;
        }

        .button:hover {
            transform: scale(1.1);
            color: #000000;
            background-color: #62aeff;
        }

        .button:active {
            transform: scale(0.9);
            background-color: #0053ac;
        }

    </style>
</head>
<body>
    <div class="block">
        <h1 class="text">ESP32 Web Site</h1>
        <div class="button-block">
            <button class="button" onclick="sendCommand()">Set Interval</button>
            <p id="p"></p>
        </div>
    </div>
    <script>
      function sendCommand() {
        fetch("/click", { method: "GET" });
      }

    </script>
</body>
</html>
)rawliteral";

#endif // HTML_H
