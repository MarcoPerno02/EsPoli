import streamlit as st
import numpy as np
from utils.utils import *
import pandas as pd

def insertCorso(params):
    if(params["CodC"] == "" or params["Nome"] == "" or params["Tipo"] == "" or params["Livello"] < 0 or params["Livello"] > 4):
            print(params["CodC"] + " " + params["Nome"] + " " + params["Tipo"])
            st.error("Errore nell'inserimento del corso")
            return False
    else:
        query = "SELECT * FROM CORSI WHERE CodC = '" + params["CodC"] + "';"
        query_result = execute_query(st.session_state["connection"], query)
        result_list = list(query_result.mappings())
        if(len(result_list) > 0):
                st.error("Errore nell'aggiungere il corso")
                return False
        query="INSERT INTO CORSI (CodC, Nome, Tipo, Livello) VALUES ('" + params["CodC"] + "', '" + params["Nome"] + "', '" + params["Tipo"] + "', " + str(params["Livello"]) + ") ;"
        try:
            execute_query(st.session_state["connection"],query)
            st.session_state["connection"].commit()
        except Exception as e:
            st.error(e)
            st.error("Errore nell'inserimento del corso")
            return False
        return True

def interfaccia():
    with st.form("Nuovo corso"):
        st.header("Aggiungi corso")
        col1, col2 = st.columns(2, gap="large")
        with col1:
            code = st.text_input("Codice corso")
            nome = st.text_input("Nome corso", placeholder = "Inserisci il nome del corso")
        with col2:
            tipo = st.text_input("Tipo corso", placeholder = "Inserisci il tipo del corso")
            livello=st.number_input("Livello corso", min_value=1, max_value=4)
        params = {"CodC" :code, "Nome": nome, "Tipo": tipo, "Livello": livello}
        submitted =st.form_submit_button("Aggiungi", type='primary')
                
    if submitted:
        if insertCorso(params ):
            st.success("Hai inserito il corso con successo")

if __name__ == "__main__":
    if "connection" not in st.session_state.keys():
        st.session_state["connection"] = False
    if check_connection():
        st.header("Form inserimento corso")
        interfaccia()