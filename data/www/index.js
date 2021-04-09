var current_request = false;
var colorPicker = null;

async function handleChange(color) {
    if (current_request == true) { return true; }
    current_request = true;
    const formData = new FormData();
    formData.append("action", "changecolor");
    formData.append("newcolor", color.hexString.replace("#", ""));

    var response = await fetch("./post", {
        "headers": {
            "accept": "*/*",
            "accept-language": "de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7,nl;q=0.6",
            "cache-control": "no-cache",
            "pragma": "no-cache"
        },
        "referrerPolicy": "strict-origin-when-cross-origin",
        "body": formData,
        "method": "POST",
        "mode": "cors",
        "credentials": "omit"
    });
    current_request = false;

}

async function colorRefresher() {
    setTimeout(async function() {
        const formData = new FormData();
        formData.append("action", "get_currentcolor");
        var response = await fetch("./post", {
            "headers": {
                "accept": "*/*",
                "accept-language": "de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7,nl;q=0.6",
                "cache-control": "no-cache",
                "pragma": "no-cache"
            },
            "referrerPolicy": "strict-origin-when-cross-origin",
            "body": formData,
            "method": "POST",
            "mode": "cors",
            "credentials": "omit"
        });
        var text = await response.text();
        colorPicker.setColors([text])
        colorRefresher();
    }, 1000);
}

async function speedRefresher() {
    setTimeout(async function() {
        const formData = new FormData();
        formData.append("action", "get_currentmodespeed");
        var response = await fetch("./post", {
            "headers": {
                "accept": "*/*",
                "accept-language": "de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7,nl;q=0.6",
                "cache-control": "no-cache",
                "pragma": "no-cache"
            },
            "referrerPolicy": "strict-origin-when-cross-origin",
            "body": formData,
            "method": "POST",
            "mode": "cors",
            "credentials": "omit"
        });
        var text = await response.text();
        document.getElementById("mode_speed").value = text;
        speedRefresher();
    }, 1000);
}

async function changeMode(mode) {
    if (mode) {
        const formData = new FormData();
        formData.append("action", "changemode");
        formData.append("newmode", mode);

        var response = await fetch("./post", {
            "headers": {
                "accept": "*/*",
                "accept-language": "de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7,nl;q=0.6",
                "cache-control": "no-cache",
                "pragma": "no-cache"
            },
            "referrerPolicy": "strict-origin-when-cross-origin",
            "body": formData,
            "method": "POST",
            "mode": "cors",
            "credentials": "omit"
        });
    }
}

async function changeModeSpeed(speed) {
    speed = speed.target.value;
    if (speed) {
        speed = (275 - speed) / 100;
        const formData = new FormData();
        formData.append("action", "changemodespeed");
        formData.append("newspeed", speed);
        var response = await fetch("./post", {
            "headers": {
                "accept": "*/*",
                "accept-language": "de-DE,de;q=0.9,en-US;q=0.8,en;q=0.7,nl;q=0.6",
                "cache-control": "no-cache",
                "pragma": "no-cache"
            },
            "referrerPolicy": "strict-origin-when-cross-origin",
            "body": formData,
            "method": "POST",
            "mode": "cors",
            "credentials": "omit"
        });
    }
}

async function showDeviceInfo() {
    Swal.fire({
        title: 'Geräteinfos',
        html: '<a>Gerät: <b>~DEVICE_NAME~</b><a><br> \
               <a>Hostname: <b>~HOSTNAME~</b><a><br> \
               <a>Alexa Name: <b>~ESPALEXA_NAME~</b><a><br> \
               <a>IP Addresse: <b>~IP_ADDRESS~</b><a><br><br> \
               <a>Firmware Version: <b>~FIRM_VERSION~</b></a><br> \
               <a>UI/Frontend Version: <b>v1.0</b></a><br> \
               <a>ESPAlexa Version: <b>~ESPALEXA_VERSION~</b></a><br> \
               <a>LED-Treiber: <b>~LED_DRIVER~</b></a><br> \
               <a>LED-Treiber Version: <b>~LED_DRIVER_VERSION~</b></a><br> \
               <a>LED Typ: <b>~LED_TYPE~</b></a><br><br> \
               <a><u>Entwickler:</u></a><br><a><b>~FIRM_AUTHOR~</b></a> \
               ',
        icon: 'info',
        confirmButtonText: 'Ok'
    });
}


setTimeout(function() {
    var picker_width = window.innerWidth * 0.75;
    if (picker_width > 320) {
        picker_width = 320;
    }
    colorPicker = new iro.ColorPicker('#picker', {
        width: picker_width,
        color: "#ffffff"
    });
    colorPicker.on('color:change', handleChange);
    document.getElementById("mode_speed").addEventListener('change', changeModeSpeed);
    colorRefresher();
    speedRefresher();
}, 5);