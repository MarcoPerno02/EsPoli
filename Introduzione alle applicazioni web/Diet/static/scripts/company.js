let nomiAziende = []
function aggiungiNomeAziendaInSessionStorage(nomeAzienda) {
    if(nomiAziende.includes(nomeAzienda) == true) return;
    nomiAziende.push(nomeAzienda)
    sessionStorage.setItem("nomiAziende", JSON.stringify(nomiAziende))
}

function salva() {
    let nomeAziendaInput = document.getElementById("nomeAziendaInput")
    nomeAziendaInput.className = ""

    aggiungiNomeAziendaInSessionStorage(nomeAziendaInput.value)
    
}

function cambiaPagina() {
    window.location.href = "./food.html"
}