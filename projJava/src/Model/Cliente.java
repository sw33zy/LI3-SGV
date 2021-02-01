package Model;

import java.io.Serializable;
import java.util.Objects;

public class Cliente implements Serializable, ICliente {
    private static final long serialVersionUID = -64572398472387L;
    private final String codigo;


    //Construtor parameterizado
    /**
     * Construtor de um cliente
     * @param codigo ID do cliente a construir
     */
    public Cliente(String codigo){
        this.codigo = codigo;
    }

    //Getters e Setters
    /**
     * Getter do ID do cliente
     * @return ID do cliente
     */
    public String getCodigoC() {
        return this.codigo;
    }

    //Equals
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Cliente cliente = (Cliente) o;
        return this.codigo.equals(cliente.getCodigoC());
    }

    //HashCode
    public int hashCode() {
        return Objects.hash(codigo);
    }

    /**
     * Cria um clone de um cliente
     * @return Cliente clonado
     */
    public ICliente clone() {
        return new Cliente(this.getCodigoC());
    }

}
