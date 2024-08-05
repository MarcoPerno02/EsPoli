function mostraErrore(testoErrore) {
    let divPerMostrareErrore = document.getElementById("mesaggioErrore")
    divPerMostrareErrore.textContent = testoErrore
    divPerMostrareErrore.className = "errore"
}


function salva() {
    alert("Sto salvando...")

    let nomeInput // Uso let perchè prefersico che la variabile 'nomeInput' sia solo visibile all'interno della funzione e non fuori, a differenza di var
    nomeInput = document.getElementById("nomeInput").value
    // Controlliamo che nomeInput sia valido. Es deve essere lungo tra i 5 e 15 caratteri compresi
    if(nomeInput.length < 5 || nomeInput.length > 15) {
        mostraErrore("Il nome è troppo lungo o troppo corto")
        return // Interommpiamo la funzione di salavataggio
    }
    
    let cognomeInput
    cognomeInput = document.getElementById("cognomeInput").value
    // Controlliamo che cognomeInput sia valido. Es deve essere lungo tra i 5 e 15 caratteri compresi
    if(cognomeInput.length < 5 || cognomeInput.length > 15) {
        mostraErrore("Il nome è troppo lungo o troppo corto")
        return // Interommpiamo la funzione di salavataggio
    }

    let etaInput
    etaInput = document.getElementById("etaInput").value
    // Controlliamo che etaInput sia valido. Es deve essere lungo tra 18 e 99 compresi
    if(etaInput < 18 || etaInput > 99) {
        mostraErrore("L'eta non è corretta")
        return // Interommpiamo la funzione di salavataggio
    }

    let indirizzoInput
    indirizzoInput = document.getElementById("indirizzoInput").value
    // Controlliamo che indirizzoInput sia valido. Es deve essere lungo tra i 5 e 20 caratteri compresi
    if(indirizzoInput.length < 5 || indirizzoInput.length > 20) {
        mostraErrore("Il nome è troppo lungo o troppo corto")
        return // Interommpiamo la funzione di salavataggio
    }

    let macchinaPreferitaInput
    macchinaPreferitaInput = document.getElementById("macchinaPreferitaInput").value // Selezione dinamica dell'elemento selezionato
    
    // Mostraimo i dati dell'utente
    alert("Nome: " + nomeInput + "\nCognome: " + cognomeInput + "\nEtà: "+ etaInput + "\nIndirizzo: " + indirizzoInput + "\nMacchina preferita: " + macchinaPreferitaInput)

    let divPerMostrareErrore = document.getElementById("mesaggioErrore")
    divPerMostrareErrore.className = "noErrore"
    divPerMostrareErrore.textContent = ""
}