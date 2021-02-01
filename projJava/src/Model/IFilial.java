package Model;

import java.util.List;
import java.util.Map;
import java.util.Set;

public interface IFilial {
    void addVenda(IInfoVenda v);
    Map.Entry<Integer,Set<String>> vendasByMonth(int mes);
    Map.Entry<Integer,Map.Entry<Integer,Double>> getClientHistoryByMonth(String client, int mes);
    Map.Entry<Integer,Map.Entry<Integer,Double>> getProductHistoryByMonth(String product, int mes);
    List<Map.Entry<String,Integer>> topProductsClient (String cliente);
    List<String> prodCompradores(String produto);
    List<Map.Entry<String,Double>> topBuyers ();
    double totalFatClient(String client);
    Set<String> totalProdsClient(String client);
    Map<String,Set<String>> parProdsClient();
    Map.Entry<String,Map.Entry<Integer,Double>> getProdutosCliente (String client, String product);
    Map <String,Map.Entry<Integer,Double>> getClientesMaisCompraram(String codProduto);
    int totalZero();
    Map<Integer,Integer> clientesFilial();
    boolean fezComprasMes(String cliente, int mes);
    Set<String> getKeySet();
}