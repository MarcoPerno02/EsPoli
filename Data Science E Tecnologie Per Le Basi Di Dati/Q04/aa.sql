/* Query 1*/
SELECT O.Regione, Anno, SUM(APS.#Visite),
    SUM(APS.OreTotali) / SUM(APS.#Pazienti),
    SUM(#Pazienti)/ COUNT(DISTINCT Provincia) 
FROM ACCESSI-PRONTO-SOCCORSO APS, TRIAGE T, OSPEDALE O, TEMPO
WHERE APS.CodTriage = T.CodTriage AND APS.CodO = O.CodO, APS.CodT = CodT
    AND T.CodColore = 'Giallo'
GROUP BY O.Regione, Anno

/* Query 2 */
SELECT Mese, Anno, SUM(SUM(APS.#Pazienti)) OVER (PARTITION BY Anno ORDER BY Mese ROWS UNBOUNDED PRECEDING)
FROM ACCESSI-PRONTO-SOCCORSO APS, TRIAGE T
WHERE APS.CodTriage = T.CodTriage
    AND T.CodColore = 'Rosso'
    AND T.ModalitaArrivo = 'Ambulanza'
GROUP BY Mese, Anno

/* Query 3 */
SELECT O.Provincia, 6-Mesi, SUM(APS.#Pazienti), SUM(#Visite) / SUM(#Pazienti)
FROM ACCESSI-PRONTO-SOCCORSO APS, OSPEDALE O, TEMPO
WHERE APS.CodO = O.CodO, APS.CodT = CodT
    AND O.Regione = 'Piemonte'
    AND O.Ortopedia = 1
    AND O.Geriatria = 0
GROUP BY O.Provincia, 6-Mesi

/* 1 */
CREATE MATERIALIZED VIEW ViewAccessi
BUILD IMMEDIATE
REFRESH FAST ON COMMIT
AS
SELECT O.Provincia, O.Regione, Mese, 6-Mesi, Anno, T.CodColore, T.ModalitaArrivo, O.Ortopedia, O.Geriatria
    SUM(APS.#Pazienti) AS #PazientiTot,
    SUM(#Visite) AS #VisiteTot,
    SUM(APS.OreTotali) AS OreTotaliTot
FROM APS.CodTriage = T.CodTriage AND APS.CodO = O.CodO, APS.CodT = CodT
GROUP BY O.Provincia, O.Regione, Mese, 6-Mesi, Anno, T.CodColore, T.ModalitaArrivo, O.Ortopedia, O.Geriatria

/* Identificatore */
/* O.Provincia, Mese, T.CodColore, T.ModalitaArrivo, O.Ortopedia, O.Geriatria */

/* Trigger */
CREATE OR REPLACE TRIGGER t1
AFTER INSERT ON ACCESSI_PRONTO_SOCCORSO
FOR EACH ROW
DECLARE
    VarMese, Var6Mesi, VarAnno DATE;
    VarProvincia, VarRegione, VarCodColore, VarModalitaArrivo VARCHAR(50);
    VarOrtopedia, VarGeriatria BOOLEAN;
    N INTEGER;

BEGIN
    SELECT Mese, 6-Mesi, Anno INTO VarMese, Var6Mesi, VarAnno
    FROM TEMPO
    WHERE CodT = :NEW.CodT;

    SELECT O.Provincia, O.Regione, O.Ortopedia, O.Geriatria INTO VarProvincia, VarRegione, VarOrtopedia, VarGeriatria
    FROM OSPEDALE O
    WHERE O.CodO = :NEW.CodO;

    SELECT T.CodColore, T.ModalitaArrivo INTO VarCodColore, VarModalitaArrivo
    FROM TRIAGE T
    WHERE T.CodTriage = :NEW.CodTriage

    SELECT COUNT(*) INTO N
    FROM ViewAccessi
    WHERE Provincia = VarProvincia AND Mese = VarMese AND CodColore = VarCodColore
    AND ModalitaArrivo = VarModalitaArrivo AND Ortopedia = VarOrtopedia AND Geriatria = VarGeriatria

    IF N > 0 THEN
        UPDATE ViewAccessi
        SET OreTotaliTot = OreTotaliTot + :NEW.OreTotali,
            #VisiteTotaliTot = #VisiteTotaliTot + :NEW.#Visite,
            #PazientiTotaliTot = #PazientiTotaliTot + :NEW.#Pazienti,
    ELSE
        INSERT INTO ViewAccessi
        VALUES (
            VarMese, Var6Mesi, VarAnno,VarProvincia, VarRegione, VarCodColore,
            VarModalitaArrivo, VarOrtopedia, VarGeriatria,
            :NEW.#Pazienti, :NEW.#Visite, :NEW.OreTotali
        )

END;

