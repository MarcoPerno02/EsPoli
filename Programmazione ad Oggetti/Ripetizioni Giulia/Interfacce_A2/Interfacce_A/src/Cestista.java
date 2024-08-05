import java.util.ArrayList;

public class Cestista extends Sportivo implements ICestista {

    /*
     * Quando si crea un ArrayList di un tipo, bisogna sempre dergli una Classe! Integer è la classe di tipo int,
     * mentre int è un dato primitivo.
     * Tendenzialmente si usa Integer, Double, Float ecc solo per liste o array o hashmap, altrimenti usare i primitivi
     */
    private ArrayList<Integer> storicoPuntiFatti = new ArrayList<>();

    public Cestista() {
        super();// super() richiama Sportivo.Sportivo(), in questo caso è stato messo solo per esempio, qui non era neccessario
    }

    @Override
    public void addStatistica(int puntiFatti) {
        storicoPuntiFatti.add(puntiFatti);
    }

    @Override
    public int getTotalePunti(int nroGare) {
        
        int puntiTotali = 0;
        for(int i = 0; i < storicoPuntiFatti.size(); i++) {
            if(i == nroGare)
                break;
            puntiTotali += storicoPuntiFatti.get(i);
        }
        return puntiTotali;
    }

    @Override
    public double getPercentualeGiorniAllenamento(int anno) {
        // Supponiamo che il cestista non abbia bisogna di aggiungere i giorni di allenamento pervhè si allena tutt'anno per qualunque anno
        System.out.println("Il cestista si allenna sempre tutti gli anni!");
        return 365;
    }
    
}
