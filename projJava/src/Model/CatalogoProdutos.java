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

public class CatalogoProdutos implements Serializable,ICatalogoProdutos {
    private static final long serialVersionUID = -123213123212387L;
    private final Set<IProduto> produtos;

    /**
     * Construtor vazio
     */
    public CatalogoProdutos (){
        this.produtos = new HashSet<>();
    }

    /**
     * Construtor do Catalogo de Produtos
     * @param file Ficheiro com informcação dos clientes
     * Traduz o ficheiro dos clientes para um Set
     * @throws IOException erros de leitura
     */
    public CatalogoProdutos(String file) throws IOException {
        List<String> prods = Files.readAllLines(Paths.get(file), StandardCharsets.UTF_8);
        this.produtos = prods.stream().map(Produto::new).collect(Collectors.toSet());
    }

    /**
     * Verifica se um Produto existe no Set
     * @param p ID do cliente a pesquisar
     * @return Produto existe=true / Produto não existe=false
     */
    public boolean existsProduct(IProduto p){
        return this.produtos.contains(p);
    }

    /**
     * @return get Set dos clientes
     */
    public Set<IProduto> getProdutos() {
        return produtos;
    }

}