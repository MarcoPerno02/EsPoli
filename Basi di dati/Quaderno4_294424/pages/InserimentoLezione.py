import streamlit as st
import numpy as np
from utils.utils import *
import pandas as pd

def convert_to_list(response, field):
    result_list = []
    for row in response.mappings():
            result_list.append(row[field])
    return result_list


def insertLezione(params):
    query = "SELECT * FROM PROGRAMMA WHERE CodFisc = '" + params["CodFisc"] + "' AND Giorno='" + params["Giorno"] + "' AND OraInizio='" + str(params["OraInizio"]) + "';"
    query_result = execute_query(st.session_state["connection"], query)
    result_list = list(query_result.mappings())
    if(len(result_list) > 0):
            st.error("Errore nell'aggiungere la lezione")
            return False
    else:
        query = "INSERT INTO PROGRAMMA (CodFisc, Giorno, OraInizio, Durata, Sala, CodC) VALUES ('" + params["CodFisc"] + "', '" + params["Giorno"] + "', '" + str(params["OraInizio"]) + "', '" + str(params["Durata"]) + "', '" + str(params["Sala"]) + "', '" + params["CodC"] + "') ;"
        try:
            execute_query(st.session_state["connection"], query)
            st.session_state["connection"].commit()
        except Exception as e:
            st.error(e)
            st.error("Errore nell'aggiungere la lezione")
            return False
        return True

def interfaccia():
    with st.form("Nuova lezione"):
        st.header("Aggiungi lezione")
        col1, col2, col3 = st.columns(3, gap = "large")
        with col1:
            cod_fisc_query = "SELECT CodFisc FROM ISTRUTTORE;"
            result = execute_query(st.session_state["connection"], cod_fisc_query)
            codFisc_list = convert_to_list(result, "CodFisc")
            codFisc = st.selectbox(label = "Codice Fiscale Istruttore", options = codFisc_list) 
            durata = st.number_input("Durata", value = 60)
        with col2:
            giorni_list = ["Lunedì", "Martedì", "Mercoledì", "Giovedì", "Venerdì"]
            giorno = st.selectbox(label = "Giorno Settimana", options = giorni_list) 
            sala = st.number_input("Sala", value = 1)
        with col3:
            ora_inizio = st.time_input("Ora Inizio")
            query = "SELECT CodC FROM CORSI;"
            result = execute_query(st.session_state["connection"], query)
            CodC_list = convert_to_list(result, "CodC")
            codC = st.selectbox(label = "Codice corso", options = CodC_list) 

        params =  {"CodFisc" : codFisc, "Giorno" : giorno, "OraInizio" : ora_inizio, "Durata" : durata, "Sala" : sala,"CodC" : codC}
        submitted  = st.form_submit_button("Aggiungi", type = 'primary')
                
    if submitted:
        if(durata > 0 and durata <= 60 and sala > 0):
            if insertLezione(params):
                st.success("inserimento ok")
        else:
            st.error("Errore nei dati da inserire")


if __name__ == "__main__" : 
    if "connection" not in st.session_state.keys():
        st.session_state["connection"] = False
    if check_connection():
        st.header("Inseriemnto lezione")
        interfaccia()