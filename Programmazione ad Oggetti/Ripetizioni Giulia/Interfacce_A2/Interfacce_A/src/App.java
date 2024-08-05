import java.util.ArrayList;

public class App {
    public static void main(String[] args) throws Exception {
        Sportivo sportivo1 = new Sportivo();
        sportivo1.addDatiAnno(50, 23); // 2000
        sportivo1.addDatiAnno(53, 24); // 2001
        sportivo1.addDatiAnno(56, 48); // 2002

        System.out.println(sportivo1.getPercentualeGiorniAllenamento(2002));

        Cestista cestista1 = new Cestista();
        cestista1.addStatistica(23);
        cestista1.addStatistica(27);
        cestista1.addStatistica(23);

        System.out.println(cestista1.getTotalePunti(2));

        Saltatore saltatore1 = new Saltatore();
        saltatore1.addStatistica(12, 0, 5);
        saltatore1.addStatistica(25, 0, 10);
        System.out.println(saltatore1.getNroGareSaltiSopraLaMedia());

        ArrayList<ISportivo> sportivi = new ArrayList<>();
        sportivi.add(sportivo1);
        sportivi.add(cestista1);
        sportivi.add(saltatore1);

        for(ISportivo sportivo:sportivi) {
            // Java sceglie la 'getPercentualeGiorniAllenamento' più specifica per il tipo che è nella lista sportivi
            System.out.println(sportivo.getPercentualeGiorniAllenamento(2002));
        }

    }
    
    
}
