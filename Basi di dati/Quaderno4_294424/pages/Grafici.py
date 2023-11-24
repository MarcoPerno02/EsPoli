import streamlit as st
import numpy as np
from utils.utils import *
import pandas as pd

def interface():
    query = "SELECT COUNT(*) as NumeroLezioni, OraInizio AS PeriodoTempo FROM PROGRAMMA GROUP BY OraInizio ORDER BY OraInizio ASC;"
    result = execute_query(st.session_state["connection"], query)
    df = pd.DataFrame(result, columns = ["Numero Lezioni", "Slot Orario"])
    st.subheader("Orari Lezioni")
    st.bar_chart(df,y="Numero Lezioni",x='Slot Orario')

    query="SELECT COUNT(*) as NumeroLezioni, Giorno AS PeriodoTempo FROM PROGRAMMA GROUP BY Giorno ORDER BY Giorno ASC;"
    result = execute_query(st.session_state["connection"], query)
    df = pd.DataFrame(result, columns = ["Numero Lezioni", "Giorno"])
    st.subheader("Lezioni Settimanali")
    st.line_chart(df, y="Numero Lezioni", x='Giorno')
        

if __name__ == "__main__":
    if "connection" not in st.session_state.keys():
        st.session_state["connection"] = False
    if check_connection():
        st.header("Corsi")
        interface()