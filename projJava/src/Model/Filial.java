package Model;

import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;


public class Filial implements IFilial, Serializable {
    private static final long serialVersionUID = 5638203936421L;
    private final Map<String,List<IInfoVenda>> filial;

    /**
     * Construtor de uma Filial
     */
    public Filial(){
        this.filial = new HashMap<>();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Filial filial1 = (Filial) o;
        return Objects.equals(filial, filial1.filial);
    }

    /**
     * Adiciona à filial a informação de uma venda
     * @param v Venda com informação a atualizar
     */
    public void addVenda(IInfoVenda v){
        String keycl = v.getCliente();
        List<IInfoVenda> vendas = new ArrayList<>();
        if (keycl!=null){
            vendas = filial.get(keycl);
        }
        if (vendas==null) { vendas= new ArrayList<>();}
        vendas.add(v);
        filial.put(keycl,vendas);
    }

    /**
     * Método que devolve um par com o total de vendas num mês e o número total de clientes
     * distintos que efetuaram compras nesse mês.
     * @param mes Mês a verificar.
     * @return Par de Número de Vendas num mês e o número de clientes que efeturam compras.
     */
    public Map.Entry<Integer,Set<String>> vendasByMonth(int mes){
        ArrayList<String> result = new ArrayList<>();
        for(Map.Entry<String,List<IInfoVenda>> entry : filial.entrySet()){
            List<IInfoVenda> venda = new ArrayList<IInfoVenda>();
            venda = entry.getValue();
            for (IInfoVenda vendas : venda) {
                if (vendas.getMes() == mes) {
                    result.add(entry.getKey());
                }
            }
        }
        int vendas = result.size();
        Set<String> set = new HashSet<>(result);
        result.clear();
        result.addAll(set);
        return new AbstractMap.SimpleEntry<>(vendas, set);
    }

    /**
     * Método que devolve um triplo com o número total de compras do cliente, o número total de produtos diferentes
     * que comprou e o total faturado, durante um mês.
     * @param client Código do cliente a obter informação.
     * @param mes Mês a verificar.
     * @return Triplo com o número total de compras do cliente, o número
     *         total de produtos diferentesque comprou e o total faturado, durante um mês.
     */
    public Map.Entry<Integer,Map.Entry<Integer,Double>> getClientHistoryByMonth(String client, int mes){
        List<IInfoVenda> cliList= this.filial.get(client);
        Set<String> set = new HashSet<>();
        int compras=0;
        double faturacao = 0;
        for (IInfoVenda i : cliList){
            if(i.getMes() == mes){
                faturacao+=i.getLucro();
                compras++;
                set.add(i.getProduto());
            }
        }
        Map.Entry<Integer, Double> par = new AbstractMap.SimpleEntry<>(compras,faturacao);
        return new AbstractMap.SimpleEntry<>(set.size(),par);

    }

    /**
     * Método que dado o código de um produto existente e um mês, determina
     * quantas vezes o produto foi comprado, por quantos clientes diferentes
     * e o total faturado, durante um mês.
     * @param product Produto a verificar.
     * @param mes     Mês a verificar.
     * @return Representa um triplo
     *         com: quantas vezes o produto foi comprado, por quantos clientes diferentes
     *         e o total facturado, durante um mês.
     */
    public Map.Entry<Integer,Map.Entry<Integer,Double>> getProductHistoryByMonth(String product, int mes) {
        Set<String> set = new HashSet<>();
        double faturacao = 0;
        int compras = 0;
        for(Map.Entry<String,List<IInfoVenda>> entry : filial.entrySet()){
            List<IInfoVenda> venda = new ArrayList<IInfoVenda>();
            venda = entry.getValue();
            for (IInfoVenda vendas : venda) {
                if (vendas.getMes() == mes && vendas.getProduto().equals(product)) {
                    set.add(entry.getKey());
                    faturacao += vendas.getLucro();
                    compras++;

                }
            }
        }
        Map.Entry<Integer, Double> par = new AbstractMap.SimpleEntry<>(compras,faturacao);
        return new AbstractMap.SimpleEntry<>(set.size(),par);
    }

    /**
     * Determina a lista de produtos comprados por um cliente e quantas unidades comprou
     * @param cliente ID do cliente em questão
     * @return Produtos comprados e respetiva faturação
     */
    public List<Map.Entry<String,Integer>> topProductsClient (String cliente){
        List<IInfoVenda> cliList= this.filial.get(cliente);
        /*List<InfoVenda> sortedUsers = cliList.stream()
                .sorted(Comparator.comparing(InfoVenda::getQuantidade).reversed())
                .collect(Collectors.toList());*/
        List<Integer> qField = cliList.stream().map(IInfoVenda -> IInfoVenda.getQuantidade()).collect(Collectors.toList());
        List<String> pField = cliList.stream().map(IInfoVenda -> IInfoVenda.getProduto()).collect(Collectors.toList());
        List<Map.Entry<String,Integer>> qprods = new ArrayList<>();
        int i = qField.size();
        for(int j = 0; j < i; j++){
            Map.Entry<String, Integer> par = new AbstractMap.SimpleEntry<>(pField.get(j),qField.get(j));
            qprods.add(j,par);
        }
        return qprods;
    }


    /**
     * Determina a lista de clientes que compraram um deteterminado produto
     * @param produto ID do produto em questão
     * @return Clientes compradores
     */
    public List<String> prodCompradores(String produto){
        List<String> res = new ArrayList<>();
        for(Map.Entry<String,List<IInfoVenda>> entry : filial.entrySet()){
            List<IInfoVenda> venda = new ArrayList<IInfoVenda>();
            venda = entry.getValue();
            for (IInfoVenda vendas : venda) {
                if (vendas.getProduto().equals(produto)) {
                    res.add(entry.getKey());

                }
            }
        }
        return res;
    }

    /**
     * Determina a lista de clientes e respetiva faturação ordenada por ordem descrescente de total faturado
     * @return Lista de clientes que mais gastaram
     */
    public List<Map.Entry<String,Double>> topBuyers () {
        List<String> clientes = new ArrayList<>();
        List<Double> fat = new ArrayList<>();
        int i = 0;
        for (Map.Entry<String, List<IInfoVenda>> entry : filial.entrySet()) {
            fat.add(i,totalFatClient(entry.getKey()));
            clientes.add(i,entry.getKey());
            i++;
        }
        List<Map.Entry<String,Double>> res = new ArrayList<>();
        List<String> resS = new ArrayList<>();
        int size = fat.size();
        for(int j = 0; j < size; j++){
            Map.Entry<String, Double> par = new AbstractMap.SimpleEntry<>(clientes.get(j),fat.get(j));
            res.add(j,par);
        }
        res.sort((o1, o2) -> Double.compare(o2.getValue(), o1.getValue()));

        return res;
    }

    /**
     * Total faturado por um determinado cliente
     * @param client Cliente a verificar
     * @return Total faturado por um determinado cliente
     */
    public double totalFatClient(String client){
        List<IInfoVenda> cliList= this.filial.get(client);
        double faturacao = 0;
        for (IInfoVenda i : cliList){
            faturacao += i.getLucro();
        }
        return faturacao;
    }

    /**
     * Lista de produtos diferentes que um determinado cliente comprou
     * @param client Cliente a verificar
     * @return Lista de produtos diferentes que um determinado cliente comprou
     */
    public Set<String> totalProdsClient(String client){
        List<IInfoVenda> cliList= this.filial.get(client);
        Set<String> prods = new HashSet<>();
        for (IInfoVenda i : cliList){
            prods.add(i.getProduto());
        }
        return prods;
    }

    /**
     * Determina os produtos comprados por cada cliente
     * @return Produtos comprados por cada cliente
     */
    public Map<String,Set<String>> parProdsClient(){
        Map<String,Set<String>> res = new HashMap<>();
        for (Map.Entry<String, List<IInfoVenda>> entry : filial.entrySet()) {
            res.put(entry.getKey(),totalProdsClient(entry.getKey()));
        }
        //res.sort((o1, o2) -> Integer.compare(o2.getValue().size(), o1.getValue().size()));

        return res;
    }

    /**
     * Determina a quantidade e faturação que um cliente fez de um determinado produto
     * @param client Cliente a verificar
     * @param product Produto a verificar
     * @return Triplo com o id do cliente, a quantidade, e a faturação do produto
     */
    public Map.Entry<String,Map.Entry<Integer,Double>> getProdutosCliente (String client, String product){
        List<IInfoVenda> cliList= this.filial.get(client);
        int compras=0;
        double faturacao = 0;
        for (IInfoVenda i : cliList){
            if(i.getProduto().equals(product)){
                faturacao+=i.getLucro();
                compras+=i.getQuantidade();
            }
        }
        return new AbstractMap.SimpleEntry<>(client,new AbstractMap.SimpleEntry<>(compras,faturacao));
    }

    /**
     * Determina para cada cliente, quando comprou e faturou de um determinado produto
     * @param codProduto Produto a verificar
     * @return Map com cada cliente e a respetiva faturação e quantidade para esse produto
     */
    public Map <String,Map.Entry<Integer,Double>> getClientesMaisCompraram(String codProduto){
        Map <String,Map.Entry<Integer,Double>> cQf = new HashMap<>();
        for (Map.Entry<String, List<IInfoVenda>> entry : filial.entrySet()) {
            Map.Entry<String,Map.Entry<Integer,Double>> triplo = getProdutosCliente(entry.getKey(),codProduto);
            cQf.put(triplo.getKey(),triplo.getValue());
        }
        return cQf;
    }

    /**
     * Determina o Número total de compras de valor total igual a 0.0
     * @return Número total de compras de valor total igual a 0.0
     */
    public int totalZero(){
        int res=0;
        for(Map.Entry<String,List<IInfoVenda>> entry : filial.entrySet()) {
            List<IInfoVenda> venda = new ArrayList<IInfoVenda>();
            venda = entry.getValue();
            for (IInfoVenda vendas : venda) {
                if (vendas.getPreco() == 0) res++;
            }
        }
        return res;
    }

    /**
     * Determina o Número de clientes distintos mês a mês
     * @return Número de clientes distintos mês a mês
     */
    public Map<Integer,Integer> clientesFilial () {
        Map<Integer, Integer> cmF = new HashMap<>();
        for (int i = 0; i < 12; i++) cmF.put(i, 0);
        for (Map.Entry<String, List<IInfoVenda>> entry : filial.entrySet()) {
            for(int i = 1; i < 13; i++){
                if(fezComprasMes(entry.getKey(),i)) cmF.replace(i-1,cmF.get(i-1)+1);
            }
        }
        return cmF;
    }

    /**
     * Verifica se um determinado cliente fez compras num mês
     * @param cliente Cliente a verificar
     * @param mes Mês a verificar
     * @return true se fez compras nesse mês, false caso contrário
     */
    public boolean fezComprasMes(String cliente, int mes){
        boolean res = false;
        List<IInfoVenda> cliList= this.filial.get(cliente);
        for (IInfoVenda i : cliList){
            if(i.getMes()==mes){
                res=true;
                break;
            }
        }
        return res;
    }

    /**
     * @return keySet da estrutura Filial
     */
    public Set<String> getKeySet(){
        return this.filial.keySet();
    }

}
