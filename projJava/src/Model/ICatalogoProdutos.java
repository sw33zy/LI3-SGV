package Model;

import java.util.Set;

public interface ICatalogoProdutos{
    boolean existsProduct(IProduto p);
    Set<IProduto> getProdutos();
}
