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
            display: flex;
            justify-content: space-between;
            margin: 0 auto;
            width: 60%;
            height: 5rem;
        }

        .button {
            width: 45%;
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

        .led-block {
            display: flex;
            justify-content: space-between;
            margin: 0 auto;
            margin-top: 1rem;
            width: 60%;
            height: 10rem;
        }

        .box {
            width: 20%;
            height: 100%;
            border-style: solid;
        }

        .led-1 {
            background: #ffffff;
        }

        .led-2 {
            background: #ffffff;
        }

        .led-3 {
            background: #ffffff;
        }

    </style>
</head>
<body>
    <div class="block">
        <h1 class="text">ESP32 Web Site</h1>
        <div class="button-block">
            <button class="button" onclick="sendCommand1()">Algoritm 1</button>
            <button class="button" onclick="sendCommand2()">Algoritm 2</button>
        </div>
        <div class="led-block">
            <div class="box led-1"></div>
            <div class="box led-2"></div>
            <div class="box led-3"></div>
        </div>
    </div>
    <script>
        let ledStateList = [0, 1, 0];

        function ledOn(numberOfLed) {
            let color = "#ffffff";
            switch(numberOfLed) {
                case 0:
                    color = "#00ff00";
                    break;
                case 1:
                    color = "#eff30b";
                    break;
                case 2:
                    color = "#f3390b";
                    break;
            }

            return color;
        }

        function ledLighting() {
            const led1 = document.querySelector(".led-1");
            const led2 = document.querySelector(".led-2");
            const led3 = document.querySelector(".led-3");

            const ledList = [led1, led2, led3];
            let color = "#000000";

            for (i = 0; i < 3; i++) {
                if (ledStateList[i] == 1) {
                    color = ledOn(i);
                } else {
                    color = "#ffffff";
                }

                ledList[i].style.background = color;
            }
        }

        function sendCommand1() {
            fetch("/click", { method: "GET" });
            ledLighting();
        }

    </script>
</body>
</html>
)rawliteral";

#endif // HTML_H
