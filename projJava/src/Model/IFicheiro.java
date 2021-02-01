package Model;

import java.util.Map;

public interface IFicheiro {
    String getFichVendas();
    int getNumVendasLidas();
    int getNrProds();
    int getNrClients();
    int getNrVendasValidas();
    Map<Integer, Integer> getClientesPorMes();
}
