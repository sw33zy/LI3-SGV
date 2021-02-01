package Model;

import java.io.IOException;
import java.io.Serializable;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

public class CatalogoClientes implements Serializable, ICatalogoClientes {
    private static final long serialVersionUID = 21334574347283L;
    private final Set<ICliente> clientes;


    /**
     * Construtor vazio
     */
    public CatalogoClientes (){
        this.clientes = new HashSet<>();
    }

    /**
     * Construtor do Catalogo de Clientes
     * @param file Ficheiro com informcação dos clientes
     * Traduz o ficheiro dos clientes para um Set
     * @throws IOException erros de leitura
     */
    public CatalogoClientes(String file) throws IOException {
        List<String> clients = Files.readAllLines(Paths.get(file), StandardCharsets.UTF_8);
        this.clientes = clients.stream().map(Cliente::new).collect(Collectors.toSet());
    }

    /**
     * Verifica se um Cliente existe no Set
     * @param c ID do cliente a pesquisar
     * @return Cliente existe=true / CLiete não existe=false
     */
    public boolean existsClient(ICliente c){
        return this.clientes.contains(c);
    }

    /**
     * @return get Set dos clientes
     */
    public Set<ICliente> getClientes() {
        return clientes;
    }

}


