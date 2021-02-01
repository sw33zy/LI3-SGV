package Model;

public interface IInfoFatur {
    boolean compareInfos(IInfoFatur aux);
    void addInfos(IInfoFatur soma);
    String get_produto();
    int get_mes();
    int get_fil();
    int get_nr_vendasN();
    int get_nr_vendasP();
    double get_FatN();
    double get_FatP();
    int get_unidT();
}
