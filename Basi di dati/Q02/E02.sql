WITH CHIRURGHI_INT AS (
SELECT CodC, Data
FROM INTERVENTO I, PAZIENTE P
WHERE P.CodFiscale = I.CodFiscale AND 
I.DATA >= '2021-01-01' AND I.DATA <= '2021-12-31' AND P.Citta = "Torino" AND I.Priorita = "Bassa"
GROUP BY CodC HAVING COUNT(DISTINCT Data) >= 2 AND COUNT(DISTINCT Tipologia) >= 2
)
SELECT C.Nome, C.Cognome
FROM Chirurgo C, CHIRURGHI_INT
WHERE CHIRURGHI_INT.CodC = C.CodC

                                                    pi
                                                    =
                                                    |
                                                pi(C.Nome, C.Cognome)
                                                    |
                     _______________________⋈(C.CodC = I1.CodC)_____________________
                    /                                                                \
                    |                                                                |
                Chirurgo C                   _________________⋈(I1.CodC = I2.CodC and I1.data <> I2.data and I1.tipologia <> I2.tipologia)_______________________
                                           /                                                                                                                     \ 
                                           |                                                                                                                     |                                                                          
     ______________________________________⋈___________________________                                                   _____________________________________⋈_____________________________
    /                                                                   \                                                 /                                                                   \
    |                                                                   |                                                 |                                                                   |
P1.Citta = "Torino"            I1.Priorita = "Bassa" AND sigma(I1.DATA >= '2021-01-01' AND I1.DATA <= '2021-12-31')   P2.Citta = "Torino"                        I2.Priorita = "Bassa" AND  sigma(I2.DATA >= '2021-01-01' AND I2.DATA <= '2021-12-31')
    |                                                                   |                                                 |                                                                   |
PAZIENTE P1                                                        INTERVENTO I1                                     PAZIENTE P2                                                         INTERVENTO I2