package Model;

import java.io.Serializable;

public class InfoFatur implements IInfoFatur, Serializable {
    private static final long serialVersionUID = -78465562523422L;
    private final String produto;
    private final int mes;
    private final int filial;
    private int nr_vendasN;  //número de clientes diferentes que compraram este produto em N
    private int nr_vendasP;  //número de clientes diferentes que compraram este produto em P
    private double fatP;     //total da faturacao em modo P
    private double fatN;     //total da faturacao em modo N
    private int unidT;       //número Total de unidades adquiridas deste produto

    /**
     * Construtor vazio
     */
    public InfoFatur(){
        this.produto = "";
        this.mes = 0;
        this.filial = 0;
        this.nr_vendasN = 0;
        this.nr_vendasP = 0;
        this.fatP = 0.0;
        this.fatN = 0.0;
        this.unidT = 0;
    }

    /**
     * Construtor de uma infofatur, a partir de uma linha do ficheiro
     * @param venda String com informação da venda
     */
    public InfoFatur (String venda){
        String[] vendaSplit = venda.split(" ");
        this.produto = vendaSplit[0];
        this.mes = Integer.parseInt(vendaSplit[5]);
        this.filial = Integer.parseInt(vendaSplit[6]);
        if((vendaSplit[3].charAt(0))=='N'){
            this.nr_vendasN++;
            this.fatN += Double.parseDouble(vendaSplit[1]);
        }
        else {
            this.nr_vendasP++;
            this.fatP += Double.parseDouble(vendaSplit[1]);
        }
        this.unidT += Integer.parseInt(vendaSplit[2]);
    }

    /**
     * Vê se uma infofatur tem igual produto, mes e filial
     * @param aux infofatur
     * @return boolean
     */
    public boolean compareInfos(IInfoFatur aux){
        if(this.get_produto().equals(aux.get_produto())){
            if(this.get_mes() == (aux.get_mes())){
                return this.get_fil() == (aux.get_fil());
            }
        }
        return false;
    }

    /**
     * Soma duas infofatur
     * @param soma infofatur a somar
     */
    public void addInfos(IInfoFatur soma){
        this.nr_vendasN += soma.get_nr_vendasN();
        this.nr_vendasP += soma.get_nr_vendasP();
        this.fatN += soma.get_FatN();
        this.fatP += soma.get_FatP();
        this.unidT += soma.get_unidT();
    }

    /**
     * Getter do codigo do produto
     * @return Codigo do produto
     */
    public String get_produto(){
        return this.produto;
    }

    /**
     * Getter do mês da infofatur
     * @return mês da infofatur
     */
    public int get_mes(){
        return this.mes;
    }

    /**
     * Getter da filial da infofatur
     * @return filial da infofatur
     */
    public int get_fil(){
        return this.filial;
    }

    /**
     * Getter do número de vendas do tipo N da infofatur
     * @return número de vendas do tipo N
     */
    public  int get_nr_vendasN(){
        return this.nr_vendasN;
    }

    /**
     * Getter do número de vendas do tipo P da infofatur
     * @return número de vendas do tipo P
     */
    public int get_nr_vendasP(){
        return this.nr_vendasP;
    }

    /**
     * Getter do total faturado do tipo N da infofatur
     * @return total faturado do tipo N
     */
    public double get_FatN(){
        return this.fatN;
    }

    /**
     * Getter do total faturado do tipo P da infofatur
     * @return total faturado do tipo P
     */
    public double get_FatP(){
        return this.fatP;
    }

    /**
     * Getter do total de unidades da infofatur
     * @return total de unidades
     */
    public int get_unidT(){
        return this.unidT;
    }


}
