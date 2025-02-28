SELECT CittàCliente, ProvinciaV, Mese,
    SUM(Incasso) / SUM(NumOspiti),
    100 * SUM(NumOspiti) / SUM(SUM(NumOspiti)) OVER (PARTITION BY CittàCliente, ProvinciaV, 6M),
    SUM(SUM(Incasso)) OVER (PARTITION BY CittàCliente),
    SUM(SUM(NumOspiti)) OVER (PARTITION BY CittàCliente, Mese)
FROM GESTIONE-VILLAGGI GV, CARATTERISTICHE-CLIENTE CC, VILLAGGIO V, TEMPO T
WHERE GV.CodV = V.CodV AND CC.CodCC = GV.CodCC AND T.CodT = GV.CodT
    AND StatoC = 'Italia'
GROUP BY CittàCliente, ProvinciaV, Mese, 6M;

SELECT TipologiaAlloggio, RegioneV, 6M,
    SUM(Incasso) / COUNT(DISTINCT Data),
    SUM(NumOspiti),
    100 * SUM(Incasso) / SUM(SUM(Incasso)) OVER (PARTITION BY TipologiaAlloggio, RegioneV, Anno),
    RANK() OVER (PARTITION BY StatoV ORDER BY SUM(Incasso) / COUNT(DISTINCT Data)),
    RANK() OVER (ORDER BY SUM(NumOspiti) DESC)
FROM GESTIONE-VILLAGGI GV, VILLAGGIO V, TEMPO T, JUNK-ALLOGGIO-PAGAMENTO JAP
WHERE GV.CodV = V.CodV AND T.CodT = GV.CodT AND JAP.CodAP = GV.CodAP
    AND Anno >= 2013 AND Anno <= 2023
GROUP BY TipologiaAlloggio, RegioneV, StatoV, 6M, Anno;

/* 
Trigger 

Query 1
3M, ModalitàPagamento, RegioneV, SUM(NumOspiti)
GESTIONE-VILLAGGI GV, VILLAGGIO V, TEMPO T, JUNK-ALLOGGIO-PAGAMENTO JAP
3M, ModalitàPagamento, RegioneV

Query 2
Anno, RegioneV, Ristorazione, SUM(NumOspiti), SUM(Incasso)
GESTIONE-VILLAGGI GV, VILLAGGIO V, TEMPO T, JUNK-ALLOGGIO-PAGAMENTO JAP
Anno, RegioneV, Ristorazione

Query 3

StatoV, 4M, SUM(Incasso)
GESTIONE-VILLAGGI GV, VILLAGGIO V, TEMPO T
StatoV, 4M

*/

CREATE MATERIALIZED VIEW ViewVillaggi
BUILD IMMEDIATE
REFRESH FAST ON COMMIT
AS
SELECT 3M, 4M, Anno, RegioneV, StatoV, ModalitàPagamento, Ristorazione,
    SUM(NumOspiti) AS NumOspitiTot,
    SUM(Incasso) AS IncassoTot
FROM GESTIONE-VILLAGGI GV, VILLAGGIO V, TEMPO T, JUNK-ALLOGGIO-PAGAMENTO JAP
WHERE GV.CodV = V.CodV AND T.CodT = GV.CodT AND JAP.CodAP = GV.CodAP
GROUP BY 3M, 4M, Anno, RegioneV, StatoV, ModalitàPagamento, Ristorazione;

/* ID
3M, 4M, RegioneV, ModalitàPagamento, Ristorazione
*/

CREATE OR REPLACE TRIGGER Test
AFTER INSERT ON GESTIONE-VILLAGGI
FOR EACH ROW
DECLARE
    Var3M, Var4M, VarAnno DATE;
    VarRegioneV, VarStatoV, VarModalitàPagamento;
    VarRistorazione BOOLEAN;
    N INTEGER;
BEGIN
    SELECT 3M, 4M, Anno INTO Var3M, Var4M, VarAnno
    FROM TEMPO
    WHERE CodT = :NEW.CodT;

    SELECT RegioneV, StatoV, Ristorazione INTO VarRegioneV, VarStatoV, VarRistorazione
    FROM VILLAGGIO
    WHERE CodV = :NEW.CodV;

    SELECT ModalitàPagamento INTO VarModalitàPagamento
    FROM JUNK-ALLOGGIO-PAGAMENTO
    WHERE CodAP = NEW.CodAP;

    SELECT COUNT(*) INTO N
    FROM ViewVillaggi
    WHERE 3M = Var3M  AND 4M = Var4M AND RegioneV = VarRegioneV AND ModalitàPagamento = VarModalitàPagamento AND Ristorazione = VarRistorazione;

    IF N > 0 THEN
        UPDATE ViewVillaggi
        SET NumOspitiTot = NumOspitiTot + :NEW.NumOspiti,
            IncassoTot = IncassoTot + :NEW.IncassoTot
        WHERE 3M = Var3M  AND 4M = Var4M AND RegioneV = VarRegioneV AND ModalitàPagamento = VarModalitàPagamento AND Ristorazione = VarRistorazione;
    ELSE
        INSERT INTO ViewVillaggi (...)
        VALUES (
            Var3M, Var4M, VarAnno, VarRegioneV, VarStatoV, VarModalitàPagamento, VarRistorazione, :NEW.Incasso, :NEW.NumOspiti
        )
    END;
END;

SELECT CittàV, 3M, ModalitàPagamento,
    SUM(Incasso),
    SUM(NumOspiti) / COUNT(DISTINCT Mese),
    100 * SUM(Incasso) * SUM(SUM(Incasso)) OVER (PARTITION BY RegioneV, 3M, ModalitàPagamento),
    SUM(SUM(Incasso)) OVER (PARTITION BY CittàV, Anno, ModalitàPagamento ORDER BY 3M ROWS UNBOUNDED PRECEDING)
FROM GESTIONE-VILLAGGI GV, VILLAGGIO V, TEMPO T, JUNK-ALLOGGIO-PAGAMENTO JAP
WHERE GV.CodV = V.CodV AND T.CodT = GV.CodT AND JAP.CodAP = GV.CodAP
    AND (Animazione = 1 OR BabyParking = 1)
GROUP BY CittàV, RegioneV, 3M, Anno, ModalitàPagamento;