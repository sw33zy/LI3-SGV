package Model;

import java.util.Set;

public interface ICatalogoClientes {

    boolean existsClient(ICliente c);
    Set<ICliente> getClientes();

}
