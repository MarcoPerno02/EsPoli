function mostraErrore(mesaggioDiTesto, gradoGravità) {
    document.getElementById("messaggioErrore").textContent += mesaggioDiTesto + "\n";
    document.getElementById("messaggioErrore").className = "";
    if(gradoGravità == 1) {
        document.getElementById("messaggioErrore").style = "color: red;"
    }
}

let righeInserite = []

window.onload = function () {
    lastName = localStorage.getItem("lastName")
    if(lastName != null) {
        document.getElementById("nomeBenvenutoId").textContent = "Benvenuto, " + localStorage.getItem("lastName")
    }

    righeInserite = localStorage.getItem("righeInserite")
    if(righeInserite != null) {
        tmp = "[" + localStorage.getItem("righeInserite") + "]"
        righeInserite = []
        righePrecedenti = JSON.parse(tmp)
        for(let i = 0; i <righePrecedenti.length; i++) {
            righeInserite.push(JSON.stringify(righePrecedenti[i]))
            let dizionario = righePrecedenti[i]
            let tableBody = document.getElementById("myTableBodyId");
            let trDaAggiungere = document.createElement("tr");
            tableBody.append(trDaAggiungere)

            let tdNomeDaAggiungere = document.createElement("td")
            tdNomeDaAggiungere.textContent = dizionario["nome"];
            trDaAggiungere.appendChild(tdNomeDaAggiungere)

            let tdCognomeDaAggiungere = document.createElement("td")
            tdCognomeDaAggiungere.textContent = dizionario["cognome"];
            tdCognomeDaAggiungere.onclick = function () {
                alert(cognomeInput)
                
            }
            tdCognomeDaAggiungere.onmouseover = function () {
                alert("Non devi avvicinarti!")
            }
            trDaAggiungere.appendChild(tdCognomeDaAggiungere)

            let tdEtaDaAggiungere = document.createElement("td")
            tdEtaDaAggiungere.textContent = dizionario["eta"];
            trDaAggiungere.appendChild(tdEtaDaAggiungere)

            let tdIndirizzoDaAggiungere = document.createElement("td")
            tdIndirizzoDaAggiungere.textContent = dizionario["indirizzo"];
            trDaAggiungere.appendChild(tdIndirizzoDaAggiungere)

            let tdMacchinaPreferita = document.createElement("td")
            tdMacchinaPreferita.textContent = dizionario["macchinaPreferita"];
            trDaAggiungere.appendChild(tdMacchinaPreferita)
        }
    }
    else {
        righeInserite = []
    }
    
    document.getElementById("nomeInput").value = "aaaa"
    

    document.getElementById("cognomeInput").value = "Bianchi"

    document.getElementById("etaInput").value = 66

    document.getElementById("indirizzoInput").value = "Milano"
}

function salva() {
    alert("Sto salvando...")
    document.getElementById("messaggioErrore").textContent = "";

    let nomeInput = ""
    nomeInput = document.getElementById("nomeInput").value
    if(nomeInput.length < 3 || nomeInput.length > 10) {
        mostraErrore("il nome è minore di 3 cartteri oppure maggiore di 10 caratteri", 1)
    }

    let cognomeInput = document.getElementById("cognomeInput").value;
    if(cognomeInput == "Rossi") {
        mostraErrore("Cognome non valido", 0)
    }

    let etaInput
    etaInput = document.getElementById("etaInput").value
    if(etaInput < 18 || etaInput > 99) {
        mostraErrore("Età non corretta", 1)
    }

    let indirizzoInput
    indirizzoInput = document.getElementById("indirizzoInput").value
    // Controlliamo che indirizzoInput sia valido. Es deve essere lungo tra i 5 e 20 caratteri compresi
    if(indirizzoInput.length < 5 || indirizzoInput.length > 20) {
        mostraErrore("Il nome è troppo lungo o troppo corto")
    }

    let macchinaPreferitaInput
    macchinaPreferitaInput = document.getElementById("macchinaPreferitaInput").value // Selezione dinamica dell'elemento selezionato
    
    // Mostraimo i dati dell'utente
    if(document.getElementById("messaggioErrore").textContent == "") {
        alert("Nome: " + nomeInput + "\nCognome: " + cognomeInput + "\nEtà: "+ etaInput + "\nIndirizzo: " + indirizzoInput + "\nMacchina preferita: " + macchinaPreferitaInput)
        let divPerMostrareErrore = document.getElementById("messaggioErrore")
        divPerMostrareErrore.className = "noErrore"
        divPerMostrareErrore.textContent = "Dati corretti!"

        let tableBody = document.getElementById("myTableBodyId");
        let trDaAggiungere = document.createElement("tr");
        tableBody.append(trDaAggiungere)

        let tdNomeDaAggiungere = document.createElement("td")
        tdNomeDaAggiungere.textContent = nomeInput;
        trDaAggiungere.appendChild(tdNomeDaAggiungere)

        let tdCognomeDaAggiungere = document.createElement("td")
        tdCognomeDaAggiungere.textContent = cognomeInput;
        tdCognomeDaAggiungere.onclick = function () {
            alert(cognomeInput)
            
        }
        tdCognomeDaAggiungere.onmouseover = function () {
            alert("Non devi avvicinarti!")
        }
        trDaAggiungere.appendChild(tdCognomeDaAggiungere)

        let tdEtaDaAggiungere = document.createElement("td")
        tdEtaDaAggiungere.textContent = etaInput;
        trDaAggiungere.appendChild(tdEtaDaAggiungere)

        let tdIndirizzoDaAggiungere = document.createElement("td")
        tdIndirizzoDaAggiungere.textContent = indirizzoInput;
        trDaAggiungere.appendChild(tdIndirizzoDaAggiungere)

        let tdMacchinaPreferita = document.createElement("td")
        tdMacchinaPreferita.textContent = macchinaPreferitaInput;
        trDaAggiungere.appendChild(tdMacchinaPreferita)

        
        localStorage.setItem("lastName", nomeInput)
        dizionarioRiga = {
            "nome": nomeInput, 
            "cognome": cognomeInput,
            "eta": etaInput,
            "indirizzo": indirizzoInput,
            "macchinaPreferita": macchinaPreferitaInput
        }
        righeInserite.push(JSON.stringify(dizionarioRiga));
        localStorage.setItem("righeInserite", righeInserite)
    }
    
}