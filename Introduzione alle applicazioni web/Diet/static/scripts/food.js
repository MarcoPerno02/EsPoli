/**
 * 
 * @param {div} divErrato il div errato a cui dobbiamo fare accesso
 * @param {string} msg la stringa di errore da visuallizare
 */

function messaggioErrore(divErrato, msg) {
    divErrato.className = "errore"
    document.getElementById("messaggioErrore").textContent += msg + "\n"
}


function salva() {
    let nomiAziende = []
    let nomiAziendeJson = sessionStorage.getItem('nomiAziende')
    if(nomiAziendeJson != null)
        nomiAziende = JSON.parse(nomiAziendeJson)

    let nomeInput = document.getElementById("nomeInput")
    nomeInput.className = ""
    let kcalInput = document.getElementById("kcalInput")
    kcalInput.className = ""
    let centogInput = document.getElementById("100gInput")
    let nomeAziendaInput = document.getElementById("nomeAziendaInput")
    nomeAziendaInput.className = ""
    
    document.getElementById("messaggioErrore").textContent = ""

    let errori = false
    
    if (nomeInput.value.length < 3) {
        messaggioErrore(nomeInput, "Nome troppo corto.")
        errori = true
    }

    if (kcalInput.value < 0) {
        messaggioErrore(kcalInput, "Kcal non può essere minore di zero")
        errori = true
    }

    if(nomiAziende.includes(nomeAziendaInput.value) == false) {
        messaggioErrore(nomeAziendaInput, "Il nome dell'azienda non esiste")
        errori = true
    }

    if(errori == true) return;

    let myTableBody = document.getElementById("myTableBodyId")
    let trDaAggiungere = document.createElement("tr")

    myTableBody.append(trDaAggiungere)

    let thNome = document.createElement("th")
    thNome.textContent = nomeInput.value
    trDaAggiungere.append(thNome)
    
    let tdKcal = document.createElement("td")
    tdKcal.textContent = kcalInput.value
    trDaAggiungere.append(tdKcal)

    let tdcentog = document.createElement("td")
    tdcentog.textContent = centogInput.value
    trDaAggiungere.append(tdcentog)

    let tdcompany = document.createElement("td")
    tdcompany.textContent = nomeAziendaInput.value
    trDaAggiungere.append(tdcompany)

}