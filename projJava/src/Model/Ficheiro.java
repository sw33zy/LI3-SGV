package Model;

import java.io.Serializable;
import java.util.Map;

public class Ficheiro implements IFicheiro, Serializable {
    private static final long serialVersionUID = -637438184013984L;
    private final String fichVendas;
    private final int numVendasLidas;
    private final int nrVendasValidas;
    private final int nrProds;
    private final int nrClients;
    private final Map<Integer,Integer> clientesPorMes;


    /**
     * Construtor parametrizado de um Ficheiro
     * @param fichVendas ficheiro de vendas lido
     * @param numVendasLidas número de vendas lidas
     * @param nrVendasValidas número de vendas válidas lidas
     * @param nrClients número de clientes
     * @param nrProds número de produtos
     * @param clientesPorMes número de clientes mês a mês
     */
    public Ficheiro(String fichVendas, int numVendasLidas, int nrVendasValidas, int nrClients, int nrProds, Map<Integer,Integer> clientesPorMes){
        this.fichVendas = fichVendas;
        this.numVendasLidas = numVendasLidas;
        this.nrVendasValidas = nrVendasValidas;
        this.nrProds = nrProds;
        this.nrClients = nrClients;
        this.clientesPorMes = clientesPorMes;
    }

    /**
     * Getter do ficheiro de vendas lido
     * @return ficheiro de vendas lido
     */
    public String getFichVendas() {
        return this.fichVendas;
    }

    /**
     * Getter do número de vendas lido
     * @return número de vendas lido
     */
    public int getNumVendasLidas() {
        return this.numVendasLidas;
    }

    /**
     * Getter do número de produtos lido
     * @return número de produtos lido
     */
    public int getNrProds() {
        return this.nrProds;
    }

    /**
     * Getter do número de clientes lido
     * @return número de clientes lido
     */
    public int getNrClients() {
        return this.nrClients;
    }

    /**
     * Getter do número de vendas válidas lido
     * @return número de vendas válidas lido
     */
    public int getNrVendasValidas() {
        return this.nrVendasValidas;
    }

    /**
     * Getter do número de clientes mês a mês
     * @return número de clientes mês a mês
     */
    public Map<Integer, Integer> getClientesPorMes() {
        return this.clientesPorMes;
    }
}
