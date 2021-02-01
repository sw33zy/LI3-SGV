package Model;

import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;


public class Faturacao implements IFaturacao, Serializable{
    private static final long serialVersionUID = 67464523441343L;
    private final Map<String, List<IInfoFatur>> faturacao;

    /**
     * Construtor Vazio de uma Faturação
     */
    public Faturacao(){
        this.faturacao = new HashMap<>();
    }

    /**
     * Construtor de uma Faturação, a partir do catalogo de produtos
     * @param p Catalogo dos produtos
     */
    public Faturacao(Set<IProduto> p){

        this.faturacao = p.stream()
                .collect(Collectors.toMap(IProduto::getCodigoP, listainicial-> new ArrayList<>()));
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Faturacao fat = (Faturacao) o;
        return Objects.equals(faturacao, fat.faturacao);
    }


    /**
     * Função que atualiza  Faturação com mais uma infofatur. 3 casos possíveis: se a lista de infofatur
     * do produto que tem na infofatur estiver vazia, entao adiciona a infofatur a essa lista vazia; se não
     * estiver vazia, então vê se algum elemento da lista tem mês e filial igual á que estamos a tentar acrescentar,
     * se isto se verificar, adicionamos as informações desta filial ao elemento; se a lista não for vazia
     * e não encontrar nenhum elemento com mês e filial igual, então adiciona à lista de infofatur
     * @param fat Infofatur que se quer adicionar
     */
    public void addInfos(IInfoFatur fat){
        int x=0;
        String prod = fat.get_produto();
        List<IInfoFatur> listaFat = new ArrayList<>();
        listaFat = this.faturacao.get(prod);
        if (listaFat.size() == 0) {        //Para o caso de estar a adicionar pela 1ª vez uma InfoFatur
            listaFat.add(fat);
            x=1;
        }
        else for (IInfoFatur f : listaFat) {

                if (f.compareInfos(fat)) {
                    f.addInfos(fat);
                    x = 1;
                    break;
                }

        }
        if(x==0){  //Para o caso de ainda nao haver uma info que tenha a mesma filial ou mes que aquela que queremos adicionar
            listaFat.add(fat);
            faturacao.replace(prod,listaFat);
        }


    }

    /**
     * Determina a lista dos produtos nunca comprados (keys com lists vazias)
     * @return lista dos produtos nunca comprados
     */
    public List<String> naoComprados() {
        List<String> res= new ArrayList<>();
        for(Map.Entry<String,List<IInfoFatur>> entry : faturacao.entrySet()) {
            List<IInfoFatur> fat = new ArrayList<IInfoFatur>();
            fat = entry.getValue();
            if (fat.size()==0) res.add(entry.getKey());
        }
        Collections.sort(res);
        return res;
    }

    /**
     * Determina, para cada produto quantas unidades foram compradas, numa lista ordenada por quantidades
     * @return lista ordenada por quantidades comprads de cada produto
     */
    public List<Map.Entry<String,Integer>> maisComprados () {
        int qT=0;
        List<Map.Entry<String,Integer>> top = new ArrayList<>();
        for (Map.Entry<String, List<IInfoFatur>> entry : faturacao.entrySet()) {
            List<IInfoFatur> fat = new ArrayList<IInfoFatur>();
            fat = entry.getValue();
            for (IInfoFatur ft : fat) {
                qT += ft.get_unidT();
            }
            Map.Entry<String,Integer> par = new AbstractMap.SimpleEntry<>(entry.getKey(),qT);
            top.add(par);
            qT=0;
        }
        top.sort((o1, o2) -> Integer.compare(o2.getValue(), o1.getValue()));
        return top;
    }

    /**
     * Determina o total faturado por cada produto
     * @return total faturado por cada produto
     */
    public List<Map.Entry<String,List<Double>>> totalFaturado() {
        double faturado = 0;
        List<Map.Entry<String,List<Double>>> res = new ArrayList<>();

        for (Map.Entry<String, List<IInfoFatur>> entry : faturacao.entrySet()) {
            List<Double> fatM = new ArrayList<>();
            for (int i = 0; i < 36; i++) {
                fatM.add(0.0);
            }
            List<IInfoFatur> fat = new ArrayList<IInfoFatur>();
            fat = entry.getValue();
            for (IInfoFatur ft : fat) {
                if(ft.get_fil()==1) {
                    faturado = ft.get_FatN() + ft.get_FatP();
                    fatM.set(ft.get_mes() - 1, fatM.get(ft.get_mes() - 1) + faturado);
                    faturado = 0;
                }
                if(ft.get_fil()==2) {
                    faturado = ft.get_FatN() + ft.get_FatP();
                    fatM.set(ft.get_mes() + 11, fatM.get(ft.get_mes() + 11) + faturado);
                    faturado = 0;
                }
                if(ft.get_fil()==3) {
                    faturado = ft.get_FatN() + ft.get_FatP();
                    fatM.set(ft.get_mes() + 23, fatM.get(ft.get_mes() + 23) + faturado);
                    faturado = 0;
                }

            }

            res.add(new AbstractMap.SimpleEntry<>(entry.getKey(), fatM));

            faturado = 0;

        }
        return res;
    }

    /**
     * Total faturado
     * @return Total faturado
     */
    public double fatTot(){
        double res=0.0;
        for(Map.Entry<String,List<IInfoFatur>> entry : faturacao.entrySet()) {
            List<IInfoFatur> fat = new ArrayList<IInfoFatur>();
            fat = entry.getValue();
            for (IInfoFatur ft : fat) {
                res += ft.get_FatN() + ft.get_FatP();
            }
        }
        return res;
    }

    /**
     * Total faturado por filial, mês a mês
     * @param filial filial em questão
     * @return Total faturado por filial, mês a mês
     */
    public Map<Integer, Double> fatTotF(int filial){
        Map<Integer, Double> l = new HashMap<>();
        for(int i = 0 ; i<12 ; i++) l.put(i,0.0);
        for(Map.Entry<String,List<IInfoFatur>> entry : faturacao.entrySet()) {
            List<IInfoFatur> fat = new ArrayList<IInfoFatur>();
            fat = entry.getValue();
            for (IInfoFatur ft : fat) {
                if(ft.get_fil()==filial) {
                    l.replace(ft.get_mes() - 1, l.get(ft.get_mes() - 1) + ft.get_FatN() + ft.get_FatP());
                }
            }
        }
        return l;
    }
}
