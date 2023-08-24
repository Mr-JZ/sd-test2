#ifndef _WEBPAGE_H_
#define _WEBPAGE_H_

#define index_page \
    "<!DOCTYPE html 5>\r\n" \
    "<html>\r\n" \
    "<head>\r\n" \
    "    <title>Webserver</title>\r\n" \
    "    <!-- Link to CanvasJS library -->\r\n" \
    "    <script src=\"https://canvasjs.com/assets/script/canvasjs.min.js\"></script>\r\n" \
    "    <link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css\" rel=\"stylesheet\"\r\n" \
    "          integrity=\"sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC\" crossorigin=\"anonymous\">\r\n" \
    "    <style>\r\n" \
    "        html, body {\r\n" \
    "            height: 100%;\r\n" \
    "        }\r\n" \
    "        .card {\r\n" \
    "            display: flex;\r\n" \
    "            height: 90%;\r\n" \
    "            width: 90%;\r\n" \
    "            left: 5%;\r\n" \
    "            top: 5%;\r\n" \
    "            border-radius: 10px;\r\n" \
    "            background: lightgrey;\r\n" \
    "        }\r\n" \
    "        .card-body {\r\n" \
    "            position: relative;\r\n" \
    "            margin: 5%;\r\n" \
    "        }\r\n" \
    "        .card-title {\r\n" \
    "            font-weight: bold;\r\n" \
    "            font-size: 50px;\r\n" \
    "        }\r\n" \
    "        .card-text {\r\n" \
    "            margin-top: 30px;\r\n" \
    "            font-size: 30px;\r\n" \
    "        }\r\n" \
    "        .btn.btn-success {\r\n" \
    "            background: lightgreen;\r\n" \
    "            margin-top: 5%;\r\n" \
    "            margin-left: 45%;\r\n" \
    "            color: black;\r\n" \
    "        }\r\n" \
    "        .row {\r\n" \
    "            display: flex;\r\n" \
    "        }\r\n" \
    "        .row > div {\r\n" \
    "            flex: 1;\r\n" \
    "            background: lightgrey;\r\n" \
    "            border: 1px solid grey;\r\n" \
    "        }\r\n" \
    "    </style>\r\n" \
    "</head>\r\n" \
    "<body>\r\n" \
    "<script>\r\n" \
    "// Platzhalter-Daten (leer)\r\n" \
    "let dataFromServer = [];\r\n" \
    "// AJAX-Anfrage zum Abrufen der Daten vom Server\r\n" \
    "function getData() {\r\n" \
    "    showData(dataFromServer);\r\n" \
    "    var xhr = new XMLHttpRequest();\r\n" \
    "    xhr.open(\"GET\", \"your_server_url_here\", true);\r\n" \
    "    xhr.onreadystatechange = function () {\r\n" \
    "        if (xhr.readyState === 4 && xhr.status === 200) {\r\n" \
    "            dataFromServer = JSON.parse(xhr.responseText); // Daten aktualisieren\r\n" \
    "            // Diagramm rendern\r\n" \
    "            showData(dataFromServer);\r\n" \
    "        }\r\n" \
    "    };\r\n" \
    "    xhr.send();\r\n" \
    "}\r\n" \
    "function showData(data) {\r\n" \
    "    const gridContainer = document.getElementById(\"container\");\r\n" \
    "    gridContainer.innerHTML = \"\"; // Vorhandenes Grid loeschen\r\n" \
    "    var rowDiv = document.createElement(\"div\");\r\n" \
    "    rowDiv.className = \"row md-3\";\r\n" \
    "    //Header X-Value\r\n" \
    "    var colDiv = document.createElement(\"div\");\r\n" \
    "    colDiv.className = \"col-sm\";\r\n" \
    "    colDiv.innerText = `X Value`;\r\n" \
    "    colDiv.style.cssText += \"font-weight:bold\";\r\n" \
    "    rowDiv.appendChild(colDiv);\r\n" \
    "    //Header Y-Value\r\n" \
    "    colDiv = document.createElement(\"div\");\r\n" \
    "    colDiv.className = \"col-sm\";\r\n" \
    "    colDiv.innerText = `Y Value`;\r\n" \
    "    colDiv.style.cssText += \"font-weight:bold\";\r\n" \
    "    rowDiv.appendChild(colDiv);\r\n" \
    "    //Header Z-Valiue\r\n" \
    "    colDiv = document.createElement(\"div\");\r\n" \
    "    colDiv.className = \"col-sm\";\r\n" \
    "    colDiv.innerText = `Z Value`;\r\n" \
    "    colDiv.style.cssText += \"font-weight:bold\";\r\n" \
    "    rowDiv.appendChild(colDiv);\r\n" \
    "    //Header setzen\r\n" \
    "    gridContainer.appendChild(rowDiv);\r\n" \
    "    //Dummy Data\r\n" \
    "    for (let i = 0; i < 5; i++) {\r\n" \
    "        rowDiv = document.createElement(\"div\");\r\n" \
    "        rowDiv.className = \"row md-3\";\r\n" \
    "        for (let j = 0; j < 3; j++) { // 3 Spalten pro Zeile\r\n" \
    "            colDiv = document.createElement(\"div\");\r\n" \
    "            colDiv.className = \"col-sm\";\r\n" \
    "            colDiv.innerText = `Row ${i + 1}, Column ${j + 1}`;\r\n" \
    "            rowDiv.appendChild(colDiv);\r\n" \
    "        }\r\n" \
    "        gridContainer.appendChild(rowDiv);\r\n" \
    "    }\r\n" \
    "    //Reload Button\r\n" \
    "    let button = document.createElement(\"div\");\r\n" \
    "    button.className = \"btn btn-success\";\r\n" \
    "    button.innerText = \"Refresh\";\r\n" \
    "    button.style.cssText += \"left:0px;\";\r\n" \
    "    button.onclick = getData;\r\n" \
    "    gridContainer.appendChild(button);\r\n" \
    "    // Back Button\r\n" \
    "    button = document.createElement(\"div\");\r\n" \
    "    button.className = \"btn btn-success\";\r\n" \
    "    button.innerText = \"Back\";\r\n" \
    "    button.style.cssText += \"left:0px;\";\r\n" \
    "    button.onclick = welcomePage;\r\n" \
    "    gridContainer.appendChild(button);\r\n" \
    "}\r\n" \
    "function welcomePage() {\r\n" \
    "    const gridContainer = document.getElementById(\"container\");\r\n" \
    "    gridContainer.innerHTML = \"\"; // Vorhandenes Grid loeschen\r\n" \
    "    const header = document.createElement(\"h\");\r\n" \
    "    header.className = \"card-title\";\r\n" \
    "    header.innerText = \"Nucleo 64 Webserver\";\r\n" \
    "    gridContainer.appendChild(header);\r\n" \
    "    let content = document.createElement(\"p\");\r\n" \
    "    content.className = \"card-text\";\r\n" \
    "    content.innerText = \"In diesem Projekt wird das im Praktikum verwendete Board Ethernetfähig gemacht.\";\r\n" \
    "    content.innerText += \"Die Sensordaten des Beschleunigungssensors werden gespeichert und persistiert.\";\r\n" \
    "    content.innerText += \" Sie können auf dieser Website abgerufen werden.\";\r\n" \
    "    gridContainer.appendChild(content);\r\n" \
    "    //Show Data Button\r\n" \
    "    const button = document.createElement(\"div\");\r\n" \
    "    button.className = \"btn btn-success\";\r\n" \
    "    button.innerText = \"Show Data\";\r\n" \
    "    button.style.cssText += \"left:0px;\";\r\n" \
    "    button.onclick = getData;\r\n" \
    "    gridContainer.appendChild(button);\r\n" \
    "}\r\n" \
    "</script>\r\n" \
    "<div class=\"card\">\r\n" \
    "    <div class=\"card-body\" id=\"container\">\r\n" \
    "        <script>welcomePage();</script>\r\n" \
    "    </div>\r\n" \
    "</div>\r\n" \
    "</body>\r\n" \
    "</html>\r\n"
#endif //WEBPAGE_H
