package Model;

import Exceptions.InvalidClientException;
import Exceptions.InvalidProductException;

import java.io.*;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import java.util.stream.Collectors;

public class GestaoVendas implements IGestaoVendas,Serializable {
    private static final long serialVersionUID = -63883274938724L;

    ICatalogoClientes catCl;
    ICatalogoProdutos catPd;
    IFilial f1,f2,f3;
    IFaturacao ft;
    IFicheiro ficheiro;

    /**
     * Construtor Vazio
     */
    public GestaoVendas(){
        this.catCl = new CatalogoClientes();
        this.catPd = new CatalogoProdutos();
        this.f1 = new Filial();
        this.f2 = new Filial();
        this.f3 = new Filial();
        this.ft = new Faturacao();

    }

    /**
     * Construtor com as estruturas preenchidas a partir da leitura dos ficheiros
     * @param clients Ficheiro dos clientes
     * @param products Ficheiro dos Produtos
     * @param sales Ficheiro das vendas
     * @throws IOException erros de leitura
     */
    public GestaoVendas(String clients, String products, String sales) throws IOException {
        this.catCl = new CatalogoClientes(clients);
        this.catPd = new CatalogoProdutos(products);
        int validas=0;
        List<String> venda = new ArrayList<>();
        BufferedReader file = new BufferedReader(new FileReader(sales));
        String linha;
        while((linha = file.readLine()) != null)
            venda.add(linha);
        int lida = venda.size();
        venda = venda
                .parallelStream()
                .filter(e -> ValidaVendas.divideLinha(e,catCl,catPd))
                .collect(Collectors
                        .toList());
        validas = venda.size();
        this.ft = new Faturacao(this.catPd.getProdutos());
        //System.out.println(this.ft);
        this.f1 = new Filial();
        this.f2 = new Filial();
        this.f3 = new Filial();
        venda.forEach(e -> {this.ft.addInfos(new InfoFatur(e));
                            InfoVenda ivenda = new InfoVenda(e);
                            if(ivenda.getFilial()==1) this.f1.addVenda(ivenda);
                            if(ivenda.getFilial()==2) this.f2.addVenda(ivenda);
                            if(ivenda.getFilial()==3) this.f3.addVenda(ivenda);
        });
        Map<Integer,Integer> cpM = new HashMap<>();
        for(int i = 0 ; i<12 ; i++) cpM.put(i,0);
        venda.forEach(e->{
            InfoVenda ivenda = new InfoVenda(e);
            int mes = ivenda.getMes();
            cpM.replace(mes-1,cpM.get(mes-1)+1);
        });
        this.ficheiro = new Ficheiro(sales,lida,validas, this.catCl.getClientes().size(), this.catPd.getProdutos().size(),cpM);
    }



    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        GestaoVendas that = (GestaoVendas) o;
        return Objects.equals(catCl, that.catCl) &&
                Objects.equals(catPd, that.catPd) &&
                Objects.equals(f1, that.f1) &&
                Objects.equals(f2, that.f2) &&
                Objects.equals(f3, that.f3);
    }

    /**
     * Query1 - Produtos não comprados
     * @return Lista de Produtos não comprados
     */
    public List<String> prodsNComprados(){
        return this.ft.naoComprados();
    }

    /**
     * Query2
     * Método que dado um mês válido, determina o número total global de vendas realizadas e o
     * número total de clientes distintos que as fizeram;
     * @param mes Mes a verificar;
     * @param filial Filial (ou filiais) a verificar;
     * @return Par que representa o número total global de vendas realizadas e o
     * número total de clientes distintos que as fizeram;
     */
    public Map.Entry<Integer,Integer> clientesVendasTotais(int filial, int mes){
        Map.Entry<Integer,Set<String>> rf1 = this.f1.vendasByMonth(mes);
        Map.Entry<Integer,Set<String>> rf2 = this.f2.vendasByMonth(mes);
        Map.Entry<Integer,Set<String>> rf3 = this.f3.vendasByMonth(mes);
        Set<String> total = new HashSet<>();
        total.addAll(rf1.getValue());
        total.addAll(rf2.getValue());
        total.addAll(rf3.getValue());
        if(filial == 1) {
            return new AbstractMap.SimpleEntry<>(rf1.getKey(),rf1.getValue().size());
        }
        if(filial == 2) {
            return new AbstractMap.SimpleEntry<>(rf2.getKey(),rf2.getValue().size());
        }
        if(filial == 3) {
            return new AbstractMap.SimpleEntry<>(rf3.getKey(),rf3.getValue().size());
        }
        else return new AbstractMap.SimpleEntry<>
                (rf1.getKey() + rf2.getKey() + rf3.getKey(),
                        total.size());
    }

    /**
     * Query3
     * Método que recebendo um código de cliente, determina, para cada mês, quantas compras fez,
     * quantos produtos distintos comprou e quanto gastou no total.
     * @param client Cliente a verificar.
     * @return Lista que representa um triplo com quantas compras fez,
     *         quantos produtos distintos comprou e quanto gastou no total.
     * @throws InvalidClientException caso o Cliente não exista
     */
    public List <Map.Entry<Integer,Map.Entry<Integer,Double>>> getClientHistory(String client) throws InvalidClientException {
        Cliente c = new Cliente(client);
        List<Map.Entry<Integer, Map.Entry<Integer, Double>>> res = new ArrayList<>();
        if(!this.catCl.existsClient(c))
                throw new InvalidClientException();
        for(int  mes = 1; mes < 13; mes++) {
            Map.Entry<Integer, Map.Entry<Integer, Double>> rf1 = this.f1.getClientHistoryByMonth(client, mes);
            Map.Entry<Integer, Map.Entry<Integer, Double>> rf2 = this.f2.getClientHistoryByMonth(client, mes);
            Map.Entry<Integer, Map.Entry<Integer, Double>> rf3 = this.f3.getClientHistoryByMonth(client, mes);

            Map.Entry<Integer, Double> par = new AbstractMap.SimpleEntry<>(
                    rf1.getValue().getKey() + rf2.getValue().getKey() + rf3.getValue().getKey(),
                    rf1.getValue().getValue() + rf2.getValue().getValue() + rf3.getValue().getValue());

            Map.Entry<Integer, Map.Entry<Integer, Double>> triplo = new AbstractMap.SimpleEntry<>
                    (rf1.getKey() + rf2.getKey() + rf3.getKey(), par);
            res.add(triplo);
        }

        return res;
    }

    /**
     * Query3
     * Dado o código de um produto existente, determinar, mês a mês, quantas vezes foi
     * comprado, por quantos clientes diferentes e o total facturado;
     * @param produto Produto a verificar.
     * @return Representa uma lista, contendo por mês
     *         quantas vezes o produto foi comprado, por quantos clientes diferentes e o total faturado.
     * @throws InvalidProductException caso o Produto não exista
     */
    public List<Map.Entry<Integer, Map.Entry<Integer, Double>>> getProductHistory (String produto) throws InvalidProductException {
        IProduto p = new Produto(produto);
        List<Map.Entry<Integer, Map.Entry<Integer, Double>>> res = new ArrayList<>();
        if(!this.catPd.existsProduct(p))
            throw new InvalidProductException();
        for(int  mes = 1; mes < 13; mes++) {
            Map.Entry<Integer, Map.Entry<Integer, Double>> rf1 = this.f1.getProductHistoryByMonth(produto, mes);
            Map.Entry<Integer, Map.Entry<Integer, Double>> rf2 = this.f2.getProductHistoryByMonth(produto, mes);
            Map.Entry<Integer, Map.Entry<Integer, Double>> rf3 = this.f3.getProductHistoryByMonth(produto, mes);

            Map.Entry<Integer, Double> par = new AbstractMap.SimpleEntry<>(
                    rf1.getValue().getKey() + rf2.getValue().getKey() + rf3.getValue().getKey(),
                    rf1.getValue().getValue() + rf2.getValue().getValue() + rf3.getValue().getValue());

            Map.Entry<Integer, Map.Entry<Integer, Double>> triplo = new AbstractMap.SimpleEntry<>
                    (rf1.getKey() + rf2.getKey() + rf3.getKey(), par);
            res.add(triplo);
        }

        return res;
    }

    /**
     * Query5
     * Lista de códigos de produtos que mais comprou  (e  quantos),  ordenada  por ordem  decrescente
     * de  quantidade  e, para quantidades iguais, por ordem alfabética dos códigos;
     * @param cliente Cliente em questão
     * @return lista ordenada de produtos e quantas vezes um dado cliente comprou
     * @throws InvalidClientException caso o Cliente não exista
     */
    public List<Map.Entry<String,Integer>> query5 (String cliente) throws InvalidClientException {
        ICliente c = new Cliente(cliente);
        if(!this.catCl.existsClient(c))
            throw new InvalidClientException();
        List<Map.Entry<String,Integer>> f1 = this.f1.topProductsClient(cliente);
        List<Map.Entry<String,Integer>> f2 = this.f2.topProductsClient(cliente);
        List<Map.Entry<String,Integer>> f3 = this.f3.topProductsClient(cliente);

        List<Map.Entry<String,Integer>> ft = new ArrayList<>();
        ft.addAll(f1);
        ft.addAll(f2);
        ft.addAll(f3);

        ft.sort((o1, o2) -> {
            int o = Integer.compare(o2.getValue(), o1.getValue());
            if (o == 0) o = o1.getKey().compareTo(o2.getKey());
            return o;
        });
        return ft;

    }

    /**
     * Query6
     * Conjunto dos produtos mais vendidos em tdo o ano e quem os comprou
     * @param limit X produtos mais vendidos
     * @return Lista ordenada dos produtos mais vendidos
     */
    public List<Map.Entry<Map.Entry<String,Integer>,Integer>> topXProds(int limit){
        List<Map.Entry<Map.Entry<String,Integer>,Integer>> res = new ArrayList<>();
        Set<String> cQ = new HashSet<>();
        List<Map.Entry<String,Integer>> clientesQuantidades = this.ft.maisComprados().subList(0,limit);
        int j=0;
        for(Map.Entry<String,Integer> p : clientesQuantidades){
            List<String> f1 = this.f1.prodCompradores(p.getKey());
            List<String> f2 = this.f2.prodCompradores(p.getKey());
            List<String> f3 = this.f3.prodCompradores(p.getKey());
            cQ.addAll(f1);
            cQ.addAll(f2);
            cQ.addAll(f3);
            int nrClientes = cQ.size();
            Map.Entry<Map.Entry<String,Integer>,Integer> pQc = new AbstractMap.SimpleEntry<>(p,nrClientes);
            res.add(pQc);
            cQ.clear();
        }
        return res;
    }

    /**
     * Query7
     * Determina,  para  cada  filial, a  lista dos três  maiores  compradores
     * em  termos de dinheiro faturado;
     */
    public List<Map.Entry<String,Double>> top3Buyers(){
        List<Map.Entry<String,Double>> f1 = this.f1.topBuyers().subList(0,3);
        List<Map.Entry<String,Double>> f2 = this.f2.topBuyers().subList(0,3);
        List<Map.Entry<String,Double>> f3 = this.f3.topBuyers().subList(0,3);

        List<Map.Entry<String,Double>> fTot = new ArrayList<>();
        fTot.addAll(f1);
        fTot.addAll(f2);
        fTot.addAll(f3);
        return fTot;
    }


    /**
     * Query8
     * Determina os códigos dos X clientes que compraram mais produtos diferentes
     * @return Lista de clientes ordenada pelo numero de produtos distintos
     */
    public List<Map.Entry<String,Integer>> topMostDiverse(){
        Map<String,Set<String>> f1 = this.f1.parProdsClient();
        Map<String,Set<String>> f2 = this.f2.parProdsClient();
        Map<String,Set<String>> f3 = this.f3.parProdsClient();

        Map<String,Set<String>> total = new HashMap<>(f1);

        for(Map.Entry<String,Set<String>> i : f2.entrySet()){
            if(total.containsKey(i.getKey())){
                total.get(i.getKey()).addAll(i.getValue());
            }
            else{
                total.put(i.getKey(),i.getValue());
            }
        }
        for(Map.Entry<String,Set<String>> i : f3.entrySet()){
            if(total.containsKey(i.getKey())){
                total.get(i.getKey()).addAll(i.getValue());
            }
            else{
                total.put(i.getKey(),i.getValue());
            }
        }
        List<Map.Entry<String,Set<String>>> list= new ArrayList<>(total.entrySet());
        list.sort((o1, o2) -> Integer.compare(o2.getValue().size(), o1.getValue().size()));
        List<Map.Entry<String,Integer>> res = new ArrayList<>();
        for (Map.Entry<String,Set<String>> i : list){
            res.add(new AbstractMap.SimpleEntry<>(i.getKey(),i.getValue().size()));
        }
        return res;
    }

    /**
     * Query9
     * Determina o conjunto dos clientes que mais compraram um produto e, para cada um,
     * qual o valor gasto;
     * @param produto Produto a verificar
     * @return Lista ordenada dos clientes que mais compraram o produto
     * @throws InvalidProductException Caso o Produto não exista
     */
    public List <Map.Entry <String,Map.Entry<Integer,Double>>> topClientsProd(String produto) throws InvalidProductException {
        IProduto c = new Produto(produto);
        if(!this.catPd.existsProduct(c))
            throw new InvalidProductException();
        Map <String,Map.Entry<Integer,Double>> f1 = this.f1.getClientesMaisCompraram(produto);
        Map <String,Map.Entry<Integer,Double>> f2 = this.f2.getClientesMaisCompraram(produto);
        Map <String,Map.Entry<Integer,Double>> f3 = this.f3.getClientesMaisCompraram(produto);

        Map <String,Map.Entry<Integer,Double>> total = new HashMap<>(f1);

        for(Map.Entry<String,Map.Entry<Integer,Double>> i : f2.entrySet()){
            if(total.containsKey(i.getKey())){
                total.replace(i.getKey(), new AbstractMap.SimpleEntry<>(total.get(i.getKey()).getKey()+i.getValue().getKey() , total.get(i.getKey()).getValue()+i.getValue().getValue()));
            }
            else{
                total.put(i.getKey(),i.getValue());
            }
        }
        for(Map.Entry<String,Map.Entry<Integer,Double>> i : f3.entrySet()){
            if(total.containsKey(i.getKey())){
                total.replace(i.getKey(), new AbstractMap.SimpleEntry<>(total.get(i.getKey()).getKey()+i.getValue().getKey() , total.get(i.getKey()).getValue()+i.getValue().getValue()));
            }
            else{
                total.put(i.getKey(),i.getValue());
            }
        }
        List<Map.Entry<String,Map.Entry<Integer,Double>>> list= new ArrayList<>(total.entrySet());
        list.sort((o1, o2) -> {
            int o = Integer.compare(o2.getValue().getKey(), o1.getValue().getKey());
            if (o == 0) o = o1.getKey().compareTo(o2.getKey());
            return o;
        });
        return list;
    }

    /**
     * Query10
     * Determina para cada produto, a faturação mês a mês e filial a filial
     * @return Lista de produtos com a respetiva faturação mês a mês e filial a filial
     */
    public List<Map.Entry<String,List<Double>>> faturacaoPorProd (){
        return this.ft.totalFaturado();
    }

    /**
     * Query Estatística 1
     * Dados referentes ao último ficheiro de vendas lido;
     * @return Nome  do  ficheiro;
     *         Número  total  de  registos  de  venda  errados;
     *         Número  total  de produtos;
     *         Total  de diferentes  produtos  comprados;
     *         Total  de  não comprados;
     *         Número total de clientes;
     *         Total dos que realizaram compras;
     *         Total de clientes que nada compraram;
     *         Total de compras de valor total igual a 0.0;
     *         Faturação total;
     */
    public Map.Entry<String,Map.Entry<List<Integer>,Double>> estatisticas1(){
        List<Integer> infos = new ArrayList<>();
        infos.add(this.ficheiro.getNumVendasLidas() - this.ficheiro.getNrVendasValidas());
        infos.add(this.ficheiro.getNrProds());
        infos.add(this.ficheiro.getNrProds() - this.ft.naoComprados().size());
        infos.add(this.ft.naoComprados().size());
        infos.add(this.ficheiro.getNrClients());
        infos.add(this.f1.getKeySet().size());
        infos.add(this.ficheiro.getNrClients() - this.f1.getKeySet().size());
        infos.add(this.f1.totalZero() + this.f2.totalZero() + this.f3.totalZero());

        return new AbstractMap.SimpleEntry<>(this.ficheiro.getFichVendas(),
                new AbstractMap.SimpleEntry<>(infos,this.ft.fatTot()));
    }

    /**
     * QUery Estatística 2
     * Dados atuais já registados nas estruturas
     * @return Número total de compras por mês;
     *         Faturação total por mês para cada filial e o valor total global;
     *         Número de distintos clientes que compraram em cada mês filial a filial;
     */
    public Map.Entry<Map<Integer, Integer>, Map.Entry<List<Map<Integer,Double>>,List<Map<Integer,Integer>>>> estatisticas2(){
        Map<Integer, Integer> cpM = this.ficheiro.getClientesPorMes();

        List<Map<Integer,Double>> fatFil= new ArrayList<>();
        fatFil.add(this.ft.fatTotF(1));
        fatFil.add(this.ft.fatTotF(2));
        fatFil.add(this.ft.fatTotF(3));

        List<Map<Integer,Integer>> cliMesF = new ArrayList<>();
        cliMesF.add(this.f1.clientesFilial());
        cliMesF.add(this.f2.clientesFilial());
        cliMesF.add(this.f3.clientesFilial());

        return new AbstractMap.SimpleEntry<>(cpM,
                new AbstractMap.SimpleEntry<>(fatFil,cliMesF));
    }

    /**
     * Guarda o estado atual da estrutura SGV para um dado ficheiro
     * @param fName Caminho do ficheiro a guardar
     * @param sgv estado a guardar
     * @throws IOException Exceção de erro a escrever para o ficheiro
     */
    public void save(String fName, IGestaoVendas sgv) throws IOException {
        FileOutputStream a = new FileOutputStream(fName);
        ObjectOutputStream r = new ObjectOutputStream(a);
        r.writeObject(sgv);
        r.flush();
        r.close();
    }

    /**
     * Carrega o SGV a partir de um ficheiro de ObjectStream
     * @param fName Caminho do ficheiro a carregar
     * @return SGV lido
     * @throws IOException Erro a ler do ficheiro
     * @throws ClassNotFoundException O ficheiro lido é invalido
     */
    public IGestaoVendas load(String fName) throws IOException, ClassNotFoundException {
        ObjectInputStream a = new ObjectInputStream(Files.newInputStream(Paths.get(fName)));
        IGestaoVendas u = (IGestaoVendas) a.readObject();
        a.close();
        return u;
    }
}

