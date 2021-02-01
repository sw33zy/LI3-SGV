package Model;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.*;
import java.util.stream.Collectors;

public class Tests {
    public static List<String> bufferedReader(String file) {
        List<String> lines = new ArrayList<>();
        String linha = "";
        try {
            BufferedReader ficheiro = new BufferedReader(new FileReader(file));
            while((linha = ficheiro.readLine()) != null)
                lines.add(linha);
        }
        catch(IOException e) {
            System.out.println(e.getMessage());
        }
        return lines;

    }

    public static List<String> fileReader(String file) {
        List<String> lines = new ArrayList<>();
        try {
            lines = Files.readAllLines(Paths.get(file), StandardCharsets.UTF_8);
        }
        catch(IOException e) {
            System.out.println(e.getMessage());
        }
        return lines;
    }


    public static void main(String[] args){
        System.out.println("Ficheiro:");
        String filename = Input.lerString();
        Crono time = new Crono();
        ICatalogoClientes catCl = null;
        ICatalogoProdutos catPd = null;
        try{
            catCl = new CatalogoClientes("Clientes.txt");
        }
        catch (IOException e) {
            System.out.println(e.getMessage());
        }

        try{
            catPd = new CatalogoProdutos("Produtos.txt");
        }
        catch (IOException e) {
            System.out.println(e.getMessage());
        }
        ICatalogoClientes clientes = catCl;
        ICatalogoProdutos produtos = catPd;

        System.out.println("1.Tempos de leitura do ficheiro");
        time.start();
        fileReader(filename);
        time.stop();
        System.out.println("Tempo de leitura com Files: " + time.getTImeString());

        time.start();
        bufferedReader(filename);
        time.stop();
        System.out.println("Tempo de leitura com BufferedReader: " + time.getTImeString());

        System.out.println("2.Tempos de leitura do ficheiro com parsing");
        List<IInfoVenda> it2f = new ArrayList<>();
        time.start();
        List<String> t2f = fileReader(filename);
        t2f.forEach(e -> {it2f.add(new InfoVenda(e));});
        time.stop();
        System.out.println("Tempo de leitura com Files e parsing: " + time.getTImeString());

        List<IInfoVenda> it2bf = new ArrayList<>();
        time.start();
        List<String> t2bf = fileReader(filename);
        t2f.forEach(e -> {it2bf.add(new InfoVenda(e));});
        time.stop();
        System.out.println("Tempo de leitura com BufferedReader e parsing: " + time.getTImeString());

        System.out.println("3.Tempos de leitura do ficheiro com parsing e validação");
        List<IInfoVenda> it3f = new ArrayList<>();
        time.start();
        List<String> t3f = fileReader(filename);
        t3f = t3f
                .parallelStream()
                .filter(e -> ValidaVendas.divideLinha(e,clientes,produtos))
                .collect(Collectors
                        .toList());
        t3f.forEach(e -> {it3f.add(new InfoVenda(e));});
        time.stop();
        System.out.println("Tempo de leitura com Files, parsing e validaçao: " + time.getTImeString());

        List<IInfoVenda> it3bf = new ArrayList<>();
        time.start();
        List<String> t3bf = bufferedReader(filename);
        t3bf = t3bf
                .parallelStream()
                .filter(e -> ValidaVendas.divideLinha(e,clientes,produtos))
                .collect(Collectors
                        .toList());
        t3bf.forEach(e -> {it3bf.add(new InfoVenda(e));});
        time.stop();
        System.out.println("Tempo de leitura com BufferedReader, parsing e validaçao: " + time.getTImeString());


    }
}
