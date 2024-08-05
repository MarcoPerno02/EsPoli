import java.util.ArrayList;

public class Sportivo implements ISportivo {

    private class DatiAnno {
        private int anno;
        public int getAnno() {
            return anno;
        }

        private double incasso;
        public double getIncasso() {
            return incasso;
        }

        private int giorniAllenamentoAnno;

        public int getGiorniAllenamentoAnno() {
            return giorniAllenamentoAnno;
        }

        public DatiAnno(int anno, double incasso, int giorniAllenamentoAnno) {
            this.anno = anno;
            this.incasso = incasso;
            this.giorniAllenamentoAnno = giorniAllenamentoAnno;
        }

    }

    private ArrayList<DatiAnno> anniDiAllenamento = new ArrayList<>();

    public Sportivo() {
    }

    @Override
    public double getPercentualeGiorniAllenamento(int anno) {
        for(DatiAnno tmp:anniDiAllenamento) {
            if(tmp.getAnno() == anno) {
                double response = (double) tmp.getGiorniAllenamentoAnno()/356*100;
                return response;
            }
        }
        return 0;
    }

    private int getLastAnnoDiAllenamento() {
        int maxAnno = 2000;
        for(DatiAnno tmp:anniDiAllenamento) {
            if(maxAnno == 0) {
                maxAnno = tmp.getAnno();
            }
            else if (tmp.getAnno() > maxAnno) {
                maxAnno = tmp.getAnno();
            }
        }
        return maxAnno;
    }

    @Override
    public void addDatiAnno(int giorniAllenamento, double incasso) {
        DatiAnno tmp = new DatiAnno(getLastAnnoDiAllenamento() + 1, incasso, giorniAllenamento);
        anniDiAllenamento.add(tmp);
    }
}
