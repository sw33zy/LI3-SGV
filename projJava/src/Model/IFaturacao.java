package Model;

import java.util.List;
import java.util.Map;

public interface IFaturacao {
    void addInfos(IInfoFatur fat);
    List<String> naoComprados();
    List<Map.Entry<String,Integer>> maisComprados ();
    List<Map.Entry<String,List<Double>>> totalFaturado();
    double fatTot();
    Map<Integer, Double> fatTotF(int filial);
}
