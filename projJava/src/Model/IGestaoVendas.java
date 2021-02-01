package Model;

import Exceptions.InvalidClientException;
import Exceptions.InvalidProductException;

import java.io.IOException;
import java.util.List;
import java.util.Map;

public interface IGestaoVendas {
    List<String> prodsNComprados();
    Map.Entry<Integer,Integer> clientesVendasTotais(int filial, int mes);
    List <Map.Entry<Integer,Map.Entry<Integer,Double>>> getClientHistory(String client) throws InvalidClientException;
    List<Map.Entry<Integer, Map.Entry<Integer, Double>>> getProductHistory (String produto) throws InvalidProductException;
    List<Map.Entry<String,Integer>> query5 (String cliente) throws InvalidClientException;
    List<Map.Entry<String,Double>> top3Buyers();
    List<Map.Entry<Map.Entry<String,Integer>,Integer>> topXProds(int limit);
    List<Map.Entry<String,Integer>> topMostDiverse();
    List <Map.Entry <String,Map.Entry<Integer,Double>>> topClientsProd(String produto) throws InvalidProductException;
    List<Map.Entry<String,List<Double>>> faturacaoPorProd ();
    Map.Entry<String,Map.Entry<List<Integer>,Double>> estatisticas1();
    Map.Entry<Map<Integer, Integer>, Map.Entry<List<Map<Integer,Double>>,List<Map<Integer,Integer>>>> estatisticas2();
    void save(String fName, IGestaoVendas sgv) throws IOException;
    IGestaoVendas load(String fName) throws IOException, ClassNotFoundException;
    }
