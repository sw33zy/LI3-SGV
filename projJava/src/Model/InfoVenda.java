package Model;

import java.io.Serializable;

public class InfoVenda implements  IInfoVenda, Serializable{
    private static final long serialVersionUID = -1245562132321L;
    private final String cliente;
    private final String produto;
    private final double preco;
    private final int quantidade;
    private final char tipo;
    private final int mes;
    private final int filial;

    /**
     * Construtor vazio
     */
    public InfoVenda(){
        this.cliente = null;
        this.produto = null;
        this.preco = 0.0;
        this.quantidade = 0;
        this.tipo = ' ';
        this.mes = 0;
        this.filial = 0;
    }

    /**
     * Construtor de uma infovenda, a partir de uma linha do ficheiro
     * @param venda String com informação da venda
     */
    public InfoVenda (String venda) {
        InfoVenda v = new InfoVenda();
        String[] vendaSplit = venda.split(" ");
        this.cliente = vendaSplit[4];
        this.produto = vendaSplit[0];
        this.preco = Double.parseDouble(vendaSplit[1]);
        this.quantidade = Integer.parseInt(vendaSplit[2]);
        this.tipo = vendaSplit[3].charAt(0);
        this.mes = Integer.parseInt(vendaSplit[5]);
        this.filial = Integer.parseInt(vendaSplit[6]);

    }

    /**
     * Getter do codigo do cliente
     * @return Codigo do cliente
     */
    public String getCliente() {
        return cliente;
    }

    /**
     * Getter do codigo do produto
     * @return Codigo do produto
     */
    public String getProduto() {
        return produto;
    }

    /**
     * Getter do preço
     * @return preço
     */
    public double getPreco() {
        return preco;
    }

    /**
     * Getter da quantidade
     * @return quantidade
     */
    public int getQuantidade() {
        return quantidade;
    }

    /**
     * Getter do lucro/faturado
     * @return lucro/faturado
     */
    public double getLucro(){ return this.quantidade*this.preco;}

    /**
     * Getter do tipo de venda
     * @return tipo de venda
     */
    public char getTipo() {
        return tipo;
    }

    /**
     * Getter do mês de venda
     * @return mês da venda
     */
    public int getMes() {
        return mes;
    }

    /**
     * Getter da filial da venda
     * @return filial da venda
     */
    public int getFilial() {
        return filial;
    }

}
