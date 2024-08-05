public interface ISaltatore {
    void addStatistica(double incasso, int saltiNulli, double saltoMedio);
    int getNroGareSaltiTuttiNulli();
    int getNroGareSaltiSopraLaMedia();
}
