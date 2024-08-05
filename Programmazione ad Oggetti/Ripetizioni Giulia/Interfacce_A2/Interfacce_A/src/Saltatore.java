import java.util.ArrayList;

public class Saltatore extends Sportivo implements ISaltatore  {

    private ArrayList<Double> storicoIncassi = new ArrayList<>();
    private ArrayList<Integer> storicoSaltiNulli = new ArrayList<>();
    private ArrayList<Double> storicoSaltoMedio = new ArrayList<>();

    public Saltatore() {

    }

    @Override
    public void addStatistica(double incasso, int saltiNulli, double saltoMedio) {
        storicoIncassi.add(incasso);
        storicoSaltiNulli.add(saltiNulli);
        storicoSaltoMedio.add(saltoMedio);
    }

    @Override
    public int getNroGareSaltiTuttiNulli() {
        int gareSaltiNulliCont = 0;
        for(double tmp:storicoSaltoMedio) {
            if(tmp == 0.0)
                gareSaltiNulliCont++;
        }
        return gareSaltiNulliCont;
    }

    @Override
    public int getNroGareSaltiSopraLaMedia() {
        double media = 0;
        for(int i = 0; i < storicoSaltoMedio.size(); i++) {
            media += storicoSaltoMedio.get(i);
        }

        media = media / storicoSaltoMedio.size();

        int gareSaltiSopraLaMediaCont = 0;
        for(int i = 0; i < storicoSaltoMedio.size(); i++) {
            if(storicoSaltoMedio.get(i) >= media) {
                gareSaltiSopraLaMediaCont++;
            }
        }
        
        return gareSaltiSopraLaMediaCont;
    }
    
    
}
