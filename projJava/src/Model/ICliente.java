package Model;

public interface ICliente {
    String getCodigoC();
    boolean equals(Object o);
    int hashCode();
    ICliente clone();
}
