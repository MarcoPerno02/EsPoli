import streamlit as st
import pymysql
import numpy as np
import pandas as pd

st.set_page_config(
    page_title="La mia App",
    layout="wide",
    initial_sidebar_state="expanded",
    menu_items={
        'Get Help': 'https://dbdmg.polito.it/',
        'Report a bug': "https://dbdmg.polito.it/",
        'About': "# Corso di *Basi di Dati*"
    }
)

# Connect to the database
connection = pymysql.connect(host='localhost',user='root',password='',database='palestra',charset='utf8mb4',cursorclass=pymysql.cursors.DictCursor)
with connection:
    with connection.cursor() as cursor:
        query = "SELECT * FROM corsi"
        cursor.execute(query)
        result = cursor.fetchone()
        print(result)
st.title("Marco Perno")
st.subheader("Quaderno04. In ogni pagina vengono soddisfate le varie richieste")