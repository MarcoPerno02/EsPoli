WITH HOTEL_CON_ALMENO_MENO_3_GIORNI AS (
SELECT S.HID as HID_INT
FROM SOGGIORNO S
WHERE (S.DataFine - S.DataInizio) * 60 * 60 * 24 < 259200 )

WITH HOTEL_CON_PIU_3_GIORNI AS (
SELECT DISTINCT(S.HID) as HID_INT
FROM SOGGIORNO S
WHERE S.HID NOT IN HOTEL_CON_ALMENO_MENO_3_GIORNI)

SELECT H.nome, H.Citta
FROM HOTEL H, HOTEL_CON_PIU_3_GIORNI
WHERE HOTEL_CON_PIU_3_GIORNI.HID_INT = H.HID

                             p
                             =
                             |
                            pi(nome, citta)
                             |
                    _________⋈___________
                  /                        \ 
                  |                  ______ - _______
                  |                 /                \
                HOTEL           pi(HID)             pi(HID)
                                    |                   |
                                    |               sigma(DataFine - DataInizio < 3)
                                    |                   |
                                SOGGIORNO           SOGGIORNO