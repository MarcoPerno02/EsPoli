SELECT ModelloDispElettronico, 6-Mesi, Genere,
    SUM(ImportTotApprovato) / SUM(#RichiesteConcluse),
    SUM(SUM(ImportTotApprovato)) OVER(PARTITION BY ModelloDispElettronico ORDER BY 6-Mesi ROWS UNBOUNDED PRECEDING),
    SUM(SUM(ImportTotRichiesto)) OVER ()
FROM RICHIESTE-RIMBORSO RR, TEMPO T, MODELLO-DISP-ELETTRONICO MDE, JUNK-CARAT-AQUIRENTE JCA
WHERE RR.IDTempo = T.IDTempo AND RR.IDModDispEle = MDE.IDModDispEle AND RR.IDJCA = JCA.IDJCA
    AND T.Anno < 2020
GROUP BY ModelloDispElettronico, 6-Mesi, Genere;


SELECT N.Negozio, MDE.Categoria, T.2-Mesi,
    SUM(ImportTotApprovato) / SUM(ImportTotRichiesto) * 100,
    SUM(#RichiestRicevute) - SUM(#RichiesteConcluse),
    SUM(SUM(ImportTotApprovato)) PARTITION BY (MDE.Categoria, T.2-Mesi),
    SUM(ImportTotApprovato) / SUM(SUM(ImportTotApprovato)) PARTITION BY (MDE.Categoria, T.2-Mesi, N.Citta)
FROM RICHIESTE-RIMBORSO RR, TEMPO T, MODELLO-DISP-ELETTRONICO MDE, NEGOZIO N
WHERE RR.IDTempo = T.IDTempo AND RR.IDModDispEle = MDE.IDModDispEle AND RR.IDNegozio = N.IDNegozio
GROUP BY N.Negozio, MDE.Categoria, T.2-Mesi, N.Citta;

/* Query 1 */
SELECT Regione, Anno, AreaGeografica
    SUM(#RichiesteConcluse),
    SUM(#ImportTotApprovato),
    SUM(DurataTotProcessamento) / SUM(#RichiesteConcluse)
FROM RICHIESTE-RIMBORSO RR, TEMPO T, NEGOZIO N
WHERE ... N.AreaGeografica = 'Nord'
GROUP BY Regione, Anno, AreaGeografica

/* Query 2 */
SELECT Mese, AreaGeografica, JCCA.DanniAccidentali, JCCA.Furto, SUM(#RichiesteConcluse), SUM(#ImportTotRichiesto) - SUM(#ImportTotApprovato)
FROM RICHIESTE-RIMBORSO RR, TEMPO T, JUNK-CARAT-COPERTURE-ASSICURATIVE JCCA
WHERE RR.IDTempo = T.IDTempo AND RR.IDJCCA = JCCA.IDJCCA
    AND JCCA.DanniAccidentali = 'Y' AND JCCA.Furto = 'N'
GROUP BY Mese, AreaGeografica, JCCA.DanniAccidentali, JCCA.Furto

/* Query 3 */
SELECT 6-Mesi, Anno, Regione, SUM(RichiesteConcluse), SUM(#ImportTotApprovato) / SUM(RichiesteConcluse)
FROM RICHIESTE-RIMBORSO RR, TEMPO T, NEGOZIO N
WHERE RR.IDTempo = T.IDTempo AND RR.IDNegozio = N.IDNegozio
    AND (Anno = 2021 OR Anno = 2022)
GROUP BY 6-Mesi, Anno, Regione

CREATE MATERIALIZED VIEW ViewTema
BUILD IMMEDIATE
REFRESH FAST ON COMMIT
AS
SELECT Mese, 6-Mesi, Anno, Regione, AreaGeografica, JCCA.DanniAccidentali, JCCA.Furto,
    SUM(#RichiesteConcluse) RichiesteConcluseTot,
    SUM(#ImportTotApprovato) ImportTotApprovatoTot,
    SUM(DurataTotProcessamento) DurataTotProcessamentoTot,
    SUM(#ImportTotRichiesto) ImportTotRichiestoTot
FROM RICHIESTE-RIMBORSO RR, TEMPO T, NEGOZIO N, JUNK-CARAT-COPERTURE-ASSICURATIVE JCCA
WHERE RR.IDTempo = T.IDTempo AND RR.IDNegozio = N.IDNegozio AND RR.IDJCCA = JCCA.IDJCCA
GROUP BY Mese, 6-Mesi, Anno, Regione, AreaGeografica, JCCA.DanniAccidentali, JCCA.Furto;

/* Chiave */
/* GROUP BY Mese, Regione, JCCA.DanniAccidentali, JCCA.Furto */

CREATE OR REPLACE TRIGGER t1
AFTER INSERT ON Tabella
FOR EACH ROW
DECLARE
    VarMese, Var6Mesi, VarAnno DATE;
    VarRegione, VarAreaGeo VARCHAR(10);
    VarDanniAccidentali, VarFurto BOOLEAN;
    N INTEGER;
BEGIN
    SELECT Mese, 6Mesi, Anno INTO VarMese, Var6Mesi, VarAnno
    FROM TEMPO
    WHERE TEMPO.IDTempo = :NEW.IDTempo;

    SELECT Regione, AreaGeografica INTO VarRegione, VarAreaGeografica
    FROM Negozio
    WHERE IDNegozio = :NEW.IDNegozio;

    SELECT DanniAccidentali, Furto INTO VarDanniAccidentali, VarFurto
    FROM JUNK-CARAT-COPERTURE-ASSICURATIVE JCCA
    WHERE JCCA.IDJCCA = :NEW.IDJCCA;

    SELECT COUNT(*) INTO N
    FROM ViewTema
    WHERE Mese = VarMese AND Regione = VarRegione AND JCCA.DanniAccidentali = VarDanniAccidentali AND JCCA.Furto = VarFurto;

    IF N > 0 THEN
        UPDATE ViewTema
        SET
        RichiesteConcluseTot = RichiesteConcluseTot + :NEW.RichiesteConcluse,
        ImportTotApprovatoTot = ImportTotApprovatoTot + :NEW.ImportTotApprovato,
        DurataTotProcessamentoTot = DurataTotProcessamentoTot + :NEW.DurataTotProcessamento,
        ImportTotRichiestoTot = ImportTotRichiestoTot + :NEW.ImportTotRichiesto
        WHERE Mese = VarMese AND Regione = VarRegione AND JCCA.DanniAccidentali = VarDanniAccidentali AND JCCA.Furto = VarFurto;
    ELSE
        INSERT INTO ViewTema (...) VALUES (
            Mese, Var6-Mesi, VarAnno, VarRegione, VarAreaGeografica, VarDanniAccidentali, VarFurto,
            :NEW.#RichiesteConcluse,
            :NEW.#ImportTotApprovato,
            :NEW.DurataTotProcessamento,
            :NEW.ImportTotRichiesto
        );
    END IF;
END;