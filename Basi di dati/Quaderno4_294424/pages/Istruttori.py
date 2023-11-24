import streamlit as st
import numpy as np
from utils.utils import *
import pandas as pd


def interface():
    cognome = st.text_input("Cognome", "")
    query = "SELECT MIN(DataNascita) as MinData, MAX(DataNascita) as MaxData FROM ISTRUTTORE;"
    result=execute_query(st.session_state["connection"],query)
    result = result.first()
    min = result[0]
    max = result[1]
    query = "SELECT DISTINCT DataNascita FROM ISTRUTTORE ORDER BY DataNascita ASC"
    result=execute_query(st.session_state["connection"], query)
    date_nascita = []
    for row in result.mappings():
        date_nascita.append(row["DataNascita"])
    data_nascita_min, data_nascita_max = st.select_slider(label="Data nascita:", options=date_nascita,  value = (min, max), )

    query = "SELECT * FROM ISTRUTTORE WHERE Cognome = '" + cognome + "' AND DataNascita >= '" + str(data_nascita_min) + "' AND DataNascita <= '" + str(data_nascita_max) + "';"
    result=execute_query(st.session_state["connection"], query)
    df=pd.DataFrame(result)
    if df.empty:
        st.warning("Nessun istruttore trovato.")
    else:
        for idx, row in df.iterrows():
            st.subheader("Istruttore " + str(idx+1) )
            col1,col2=st.columns(2)
            print(row)
            col1.text("Codice Fiscale: " + row[0] )
            col1.text("Nome: " + row[1] )
            col1.text("Cognome: " + row[2] )
            col2.text("Data di Nascita: " + str(row[3]) )
            col2.text("Email: " + row[4] )
            col2.text("Telefono: " + row[5] )
                
if __name__ == "__main__":
    if "connection" not in st.session_state.keys():
        st.session_state["connection"] = False
    if check_connection():
        st.header("Corsi")
        interface()