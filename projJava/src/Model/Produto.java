package Model;

import java.io.Serializable;
import java.util.Objects;

public class Produto implements Serializable,IProduto {
    private static final long serialVersionUID = 237857565984576L;
    private final String codigo;

    //Construtor parameterizado
    /**
     * Construtor de um Produto dado o seu id
     * @param codigo Id do produto a construir
     */
    public Produto(String codigo){
        this.codigo = codigo;
    }

    //Getters e Setters
    /**
     * Getter do ID do produto
     * @return ID do produto
     */
    public String getCodigoP() {
        return this.codigo;
    }

    //Equals
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Produto produto = (Produto) o;
        return this.codigo.equals(produto.getCodigoP());
    }

    //HashCode
    public int hashCode() {
        return Objects.hash(codigo);
    }

    /**
     * Cria um clone do produto
     * @return Produto clonado
     */
    public IProduto clone() {
        return new Produto(this.getCodigoP());
    }
}


