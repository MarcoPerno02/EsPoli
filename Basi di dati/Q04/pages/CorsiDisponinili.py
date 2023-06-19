import streamlit as st
import numpy as np
from utils.utils import *
import pandas as pd

st.subheader("Corsi disponibili")

def create_filtri_corsi():
    col1, col2=st.columns(2, gap="large")
    tipo = ""
    livello = 0
    with col1:
        numero_corsi = "SELECT COUNT(*) as NumCorsi FROM CORSI;"
        result = execute_query(st.session_state["connection"],numero_corsi)
        num_corsi = result.first()[0]
        st.metric(label="Numero di corsi disponibili",value=num_corsi)
        tipi_query = "SELECT DISTINCT Tipo FROM CORSI"
        result=execute_query(st.session_state["connection"],tipi_query)
        result_list = []
        for row in result.mappings():
            result_list.append(row["Tipo"])
        result_list.append("Qualunque")
        tipo = st.selectbox(label="Tipi corsi", options=result_list) 

    with col2:
        num_tipi_query = "SELECT COUNT(DISTINCT Tipo) as NumTipi FROM CORSI"
        result = execute_query(st.session_state["connection"],num_tipi_query)
        num_tipi = result.first()[0]
        st.metric(label="Numero di tipi diponibili",value=num_tipi)
        min_query="SELECT MIN(Livello) as Minimo FROM CORSI;"
        result=execute_query(st.session_state["connection"],min_query)
        min = result.first()[0]
        max_query="SELECT MAX(Livello) as Massimo FROM CORSI;"
        result=execute_query(st.session_state["connection"],max_query)
        max = result.first()[0]
        livello = st.slider(label="Livello corso", min_value= min, max_value= max)

    if tipo == "Qualunque":
        corsi_query=f"SELECT CodC, Nome, Tipo, Livello FROM CORSI WHERE Livello = {livello};"
    else:
        corsi_query=f"SELECT CodC, Nome, Tipo, Livello FROM CORSI WHERE Tipo = '{tipo}' AND Livello = {livello};"
    result = execute_query(st.session_state["connection"],corsi_query)
    df_corsi = pd.DataFrame(result, columns=["Codice Corso", "Nome", "Tipo", "Livello"])
    if df_corsi.empty:
            st.warning("Non ci sono corrsipondenze per i criteri inseriti")
    else:
        st.write("Corsi:")
        st.dataframe(df_corsi, use_container_width=True)
        corso_sel =st.multiselect("Riga selezionata:",df_corsi)
        with st.expander("Programmi:"):
            if(len(corso_sel)!=0):
                corso_sel=(tuple(corso_sel))
                corso_sel = '(%s)' % ', '.join(map(repr, corso_sel))
                programmi_query=f"SELECT CodFisc, Giorno, Orainizio, Durata, Sala FROM PROGRAMMA P WHERE CodC IN {corso_sel};"
                result=execute_query(st.session_state["connection"],programmi_query)
                df_programmi = pd.DataFrame(result, columns=["CddFiscale Istruttore", "Giorno", "Ora Inizio", "Durata", "Sala"])
                if df_programmi.empty:
                    st.warning("Nessun dato trovato.",icon='⚠️')
                else:
                    st.dataframe(df_programmi, use_container_width=True)

if __name__ == "__main__":
    if "connection" not in st.session_state.keys():
        st.session_state["connection"] = False
    if check_connection():
        create_filtri_corsi()