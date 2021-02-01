package Model;

public interface IProduto {
    String getCodigoP();
    boolean equals(Object o);
    int hashCode();
    IProduto clone();
}
