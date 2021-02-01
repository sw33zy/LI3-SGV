package View;

import java.util.*;
import java.util.stream.Collectors;

import static java.lang.System.in;
import static java.lang.System.out;

public class View implements IView{
    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_BLACK = "\u001B[30m";
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_YELLOW = "\u001B[33m";
    public static final String ANSI_BLUE = "\u001B[34m";
    public static final String ANSI_PURPLE = "\u001B[35m";
    public static final String ANSI_CYAN = "\u001B[36m";
    public static final String ANSI_WHITE = "\u001B[37m";
    public static final String ANSI_BOLD = "\u001B[1m";

    /**
     * Menu do projeto
     */
    public void  menu (){
        String CSI = "\u001B[";
        System.out.println();
        System.out.print (CSI + "33" + "m");
        System.out.print ("*************************** MENU ***************************");
        System.out.println (CSI + "m");
        System.out.print (CSI + "33" + "m");
        System.out.print ("                     Selecione uma opção");
        System.out.println (CSI + "m");
        linha();
        System.out.println("0- Carregar ficheiros");
        linha();
        System.out.println("1- Lista dos produtos nunca comprados");
        linha();
        System.out.println("2- Nº total de vendas e de clientes de um mês, por filial");
        linha();
        System.out.println("3- Nº de compras, nº de produtos e total comprado de cliente");
        linha();
        System.out.println("4- Nº de compras de produto,nº clientes e total € por mês");
        linha();
        System.out.println("5- Lista de produtos que um cliente mais comprou");
        linha();
        System.out.println("6- N produtos mais vendidos e nº de clientes que comprou");
         linha();
        System.out.println("7- Lista dos 3 maiores comprados de cada filial");
        linha();
        System.out.println("8- Lista dos N clientes que compraram mais produtos ");
        linha();
        System.out.println("9- N clientes que mais compraram um produto");
        linha();
        System.out.println("10- Faturação mês a mês, por filial de produto");
        linha();
        System.out.println("11 - Dados referentes ao último ficheiro de vendas lido");
        linha();
        System.out.println("12 - Dados registados nas estruturas");
        linha();
        System.out.println("13- Save");
        linha();
        System.out.println("14- Load");
        linha();
        System.out.print (CSI + "31" + "m");
        System.out.println("15- SAIR\n");
        System.out.println (CSI + "m");

    }
    private void linha(){
        String CSI = "\u001B[";
         System.out.print (CSI + "33" + "m");
        System.out.print(" ----------------------------------------------------------");
        System.out.println (CSI + "m");
    }

    /**
     * Press Enter to Continue
     */
    public void promptEnterKey(){
        System.out.println("\033[1m"+"Press \"ENTER\" to continue..."+"\033[0m");
        Scanner scanner = new Scanner(System.in);
        scanner.nextLine();
    }


    /**
     * Método que lê um int válido
     * @param message informação sobre qual o input a fazer
     * @return int lido
     */
    public int getInt(String message) {
        System.out.print(message);
        Scanner input = new Scanner(in);
        boolean ok = false;
        int i = 0;
        while(!ok) {
            try {
                i = input.nextInt();
                ok = true;
            }
            catch(InputMismatchException e)
            { out.println("Inteiro Invalido");
                out.print("Novo valor: ");
                input.nextLine();
            }
        }
        //input.close();
        return i;
    }

    /**
     * Método que lê uma String válida
     * @param message informação sobre qual o input a fazer
     * @return string lida
     */
    public String getInputString(String message){
        System.out.println(message);
        Scanner input = new Scanner(in);
        boolean ok = false;
        String txt = "";
        while(!ok) {
            try {
                txt = input.nextLine();
                ok = true;
            }
            catch(InputMismatchException e)
            { out.println("Texto Invalido");
                out.print("Novo valor: ");
                input.nextLine();
            }
        }
        //input.close();
        return txt;
    }

    /**
     * Método que verifica se o input feito para um mês é valido
     * @param mes input que foi feito
     * @return 1 if true 0 if False
     */
    public boolean mesValido(int mes){
        boolean res = false;
        if (mes>0 && mes<13) res = true;
        return res;
    }

    /**
     * Verifica se uma filial inserida é valida
     * @param filial filial inserido
     * @return 1 if true 0 if False
     */
    public boolean filialValido(int filial){
        boolean res = false;
        if (filial>=0 && filial<4) res = true;
        return res;
    }

    /**
     * Verifica se uma opção inserida é valida
     * @param op opçao inserida
     * @return 1 if true 0 if False
     */
    public boolean opcaoValido(int op){
        boolean res = false;
        if (op>0 && op<3) res = true;
        return res;
    }

    /**
     * Verifica se um limite inserido é valido
     * @param op limite inserido
     * @return 1 if true 0 if False
     */
    public boolean limiteValido(int op){
        boolean res = false;
        if (op>0) res = true;
        return res;
    }

    /**
     * Método responsável pelo output da leitura dos fichheiros
     * @param x
     * @param time tempo que demorou a fazer a leitura
     */
    public void show_q0(int x, String time) {
        if(x==0) {
            System.out.println("1- Pretendo carregar os ficheiros default");
            System.out.println("2- Pretendo carregar os meus ficheiros");
        }
        if(x==1) {
            System.out.println(ANSI_GREEN + "Ficheiros Lidos Com Sucesso!" + ANSI_RESET);
            System.out.println(time);
        }
        if(x==2){
            System.out.println(ANSI_BOLD+"LOADING..."+ANSI_RESET);
        }
    }

    /**
     * Método responsável pelo output da query 1
     * @param l lista dos produtos não comprados
     * @param time tempo que demorou a executar a query1
     */
    public void show_q1(List<String> l, String time){
        System.out.println(time);
        int nr=-1;
        while(!limiteValido(nr)) {
            nr = getInt("Introduza o número de elementos por página:");
        }
        navegador(l,nr,"Lista de produtos nunca comprados");
    }

    /**
     * Método responsável pelo output da query 2
     * @param sales Vendas e clientes totais, respetivamente
     * @param mes mês a verificar
     * @param filial filial a verificar
     * @param time tempo que demorou a executar a query
     */
    public void show_q2(Map.Entry<Integer, Integer> sales, int mes, int filial, String time){
        System.out.println("\n"+time);
        if(filial == 0){
            System.out.println(ANSI_BOLD + "Vendas totais no mês " + mes + ": " + ANSI_RESET +
                    String.format("%8s",sales.getKey()));
            System.out.println(ANSI_BOLD + "Clientes totais no mês " + mes + ": " + ANSI_RESET +
                    String.format("%6s\n",sales.getValue()));
        }
        else {
            System.out.println(ANSI_BOLD + "Vendas no mês " + mes + " na filial " + filial + ": " + ANSI_RESET +
                    String.format("%8s",sales.getKey()));
            System.out.println(ANSI_BOLD + "Clientes no mês " + mes + " na filial " + filial + ": " + ANSI_RESET +
                    String.format("%6s\n",sales.getValue()));
        }
    }

    /**
     * Método responsǘel pelo output da Query 3
     * @param res Lista de triplos com o número de compras, produtos e faturação respetivamente
     * @param client Cliente a verificar
     * @param time tempo que demorou a executar a query
     */
    public void show_q3(List<Map.Entry<Integer, Map.Entry<Integer, Double>>> res, String client, String time){
        System.out.println("\n"+time);
        String[] header = {"Mês","Compras","Produtos","Faturação"};
        System.out.println(ANSI_BOLD + " ===============CLIENT " + client + "===============");
        System.out.format(" %s%13s%12s%14s",header[0],header[1],header[2],header[3]);
        System.out.println();
        System.out.println(" ==========================================" + ANSI_RESET);
        for(int  mes = 1; mes < 13; mes++){
            System.out.format(" %-2d%11d%11d%18f",
                    mes,
                    res.get(mes-1).getKey(),
                    res.get(mes-1).getValue().getKey(),
                    res.get(mes-1).getValue().getValue());
            System.out.println();
        }
    }

    /**
     * Método responsável pelo output da query 4
     * @param res Lista de triplos com o número de compras, clientes e faturação, respetivamente
     * @param product Produto a verificar
     * @param time tempo que demorou a executar a query
     */
    public void show_q4(List<Map.Entry<Integer, Map.Entry<Integer, Double>>> res, String product, String time){
        System.out.println("\n"+time);
        String[] header = {"Mês","Compras","Clientes","Faturação"};
        System.out.println(ANSI_BOLD + " ==============PRODUCT " + product + "==============");
        System.out.format(" %s%13s%12s%14s",header[0],header[1],header[2],header[3]);
        System.out.println();
        System.out.println(" ==========================================" + ANSI_RESET);
        for(int  mes = 1; mes < 13; mes++){
            System.out.format(" %-2d%11d%11d%18f",
                    mes,
                    res.get(mes-1).getKey(),
                    res.get(mes-1).getValue().getKey(),
                    res.get(mes-1).getValue().getValue());
            System.out.println();
        }
    }

    /**
     * Método responsável pelo output da query 5
     * @param ft Lista dos produtos e quantidades mais comprados
     * @param time tempo que demorou a executar a query
     */
    public void show_q5(List<Map.Entry<String,Integer>> ft, String time){
        System.out.println("\n" +time);
        int nr=-1;
        List<String> prodsQuantidade = new ArrayList<>();
        for(Map.Entry<String,Integer> p : ft){
            prodsQuantidade.add("Produto: " + p.getKey() + " | " + "Quantidade: " + p.getValue());
        }
        while(!limiteValido(nr)) {
            nr = getInt("Introduza o número de elementos por página:");
        }
        navegador(prodsQuantidade,nr,"Lista de produtos mais comprados");
    }

    /**
     * Método responsável pelo output da query 6
     * @param ft Lista de produtos mais vendidos, quantidades e número de clientes
     * @param time tempo que demorou a executar a query
     */
    public void show_q6(List<Map.Entry<Map.Entry<String,Integer>,Integer>> ft, String time){
        System.out.println(time);
        int nr=-1;
        List<String> cliQuantNr = new ArrayList<>();
        for(Map.Entry<Map.Entry<String,Integer>,Integer> p : ft){
            cliQuantNr.add("Produto: " + p.getKey().getKey() + " | " + "Quantidade: " + p.getKey().getValue() + " | " + "NrClientes: " + p.getValue());
        }
        while(!limiteValido(nr)) {
            nr = getInt("Introduza o número de elementos por página:");
        }
        navegador(cliQuantNr,nr,"Lista de produtos mais comprados");
    }

    /**
     * Método responsável pelo output da query7
     * @param values Lista de pares Cliente, Faturação
     * @param time tempo que demorou a executar a query 7
     */
    public void show_q7(List<Map.Entry<String,Double>> values, String time){
        System.out.println("\n"+time);
        System.out.println(ANSI_BOLD + "Maiores Comprados Por Filial\n" + ANSI_RESET);
        String[] header = {"FILIAL 1:\n","FILIAL 2:\n","FILIAL 3:\n"};
        int i=0,filial = 0;
        for(i = 0 ; i < 9 && filial < 3; i+=3 ) {
            System.out.println(ANSI_BOLD + header[filial] + ANSI_RESET +
                    "\t1º: Cliente -> " + values.get(i).getKey() + " Faturação -> " + values.get(i).getValue() + "\n" +
                    "\t2º: Cliente -> " + values.get(i+1).getKey() + " Faturação -> " + values.get(i+1).getValue() + "\n" +
                    "\t3º: Cliente -> " + values.get(i+2).getKey() + " Faturação -> " + values.get(i+2).getValue() + "\n" );
            filial++;
        }
    }

    /**
     * Método responsável pelo output da query 8
     * @param l Lista de clientes, e número de diferentes produtos que comprou
     * @param time tempo que demorou a executar a query
     */
    public void show_q8(List<Map.Entry<String, Integer>> l, String time){
        System.out.println(time);
        int nr=-1;
        List<String> res = new ArrayList<>();
        for(Map.Entry<String,Integer> p : l){
            res.add("Cliente: " + p.getKey() + " | " + "Nr de Produtos Diferentes: " + p.getValue());
        }
        while(!limiteValido(nr)) {
            nr = getInt("Introduza o número de elementos por página:");
        }
        navegador(res,nr,"Lista de clientes que compraram mais produtos diferentes");
    }

    /**
     * Método responsável pelo output da query 9
     * @param l Lista de triplos Cliente, quantidade, faturação , respetivamente
     * @param time tempo que demorou a executar a query
     */
    public void show_q9(List<Map.Entry<String, Map.Entry<Integer, Double>>> l, String time){
        System.out.println(time);
        int nr=-1;
        List<String> res = new ArrayList<>();
        for(Map.Entry<String, Map.Entry<Integer, Double>> p : l){
            res.add("Cliente: " + p.getKey() + " | " + "Quantidade: " + p.getValue().getKey() + " | " + "Faturação: " + p.getValue().getValue());
        }
        while(!limiteValido(nr)) {
            nr = getInt("Introduza o número de elementos por página:");
        }
        navegador(res,nr,"Lista de clientes que mais compraram o produto");
    }

    /**
     * menu de opções para a query10
     * @return opção escolhida
     */
    private static String menuNav2(){
        String ch;
        System.out.print("\033[1m"+"Pagina Seguinte       (P)\nPagina Anterior       (A)\nEscolher Pagina       (E)\nEscolher Opção        (O)\nMenu                  (M)\n"+"\033[0m");
        String txt = "";
        do{
            System.out.println("-->");
            Scanner input = new Scanner(in);
            boolean ok = false;
            while(!ok) {
                try {
                    txt = input.nextLine();
                    ok = true;
                }
                catch(InputMismatchException e)
                { out.println("Texto Invalido");
                    out.print("Novo valor: ");
                    input.nextLine();
                }
            }
        } while(!(txt.equals("P")) && !(txt.equals("A")) && !(txt.equals("E")) && !(txt.equals("O")) && !(txt.equals("M")));
        return txt;
    }

    /**
     * Navegador de uma lista de opções para a query 10
     * @param prods Lista de todos os produtos ordenada
     * @return número da lista que quer verificar
     */
    private int menuQ10(List<String> prods){
        int r=0;
        int p = prods.size();
        List<String> res = new ArrayList<String>();
        for(int i = 0; i<prods.size() ; i+=1000){
            if(i+999> prods.size()) res.add(" Produtos ["+prods.get(i)+" - "+prods.get(prods.size()-1)+"]");
            else res.add(" Produtos ["+prods.get(i)+" - "+prods.get(i+999)+"]");
            r++;
        }
        int i;
        i=res.size();
        int pages= i / 15;
        if ((i%15)!=0) pages=pages+1;

        int m=-1;
        int j=1;
        int k=0;
        int t=0;
        String ch;
        int temp1=0;
        int temp2=0;
        int n;
        int nr=-1;
        String message = "Escolha uma número da lista";
        Scanner sc = new Scanner(System.in);
        label:
        do {
            temp1=t;
            System.out.format("\033[1m"+"%s\n\n"+"\033[0m", message);
            for(n=0;n<15&&t<i;n++){
                System.out.format("\t%2d. %s\n",n+k+1, res.get(k+n));
                t++;
            }
            temp2=k;
            k+=15;
            System.out.format("\033[1m"+"\nPage <%d/%d> \n\n"+"\033[0m",j ,pages);
            j++;

            do {

                switch (ch=menuNav2()) {
                    case "P":
                        if (j == pages + 1) {
                            j = 1;
                            t = 0;
                            k = 0;
                            System.out.print("You are already on the last page!\nPress C to return to the first page\n");
                            while (!sc.nextLine().equals("C")) ;
                            System.out.print("\033[2J");
                        }
                        break;
                    case "A":
                        if (j != 2) {

                            k = temp2 - 15;
                            j = j - 2;
                            t=temp1-15;
                        } else {
                            System.out.print("You are already on the first page!\nPress C to continue\n");
                            while (!sc.nextLine().equals("C")) ;

                        }
                        break;
                    case "E": {
                        System.out.print("\nEscolha o numero da pagina: ");
                        int f;
                        do {
                            f = sc.nextInt();
                            if (f < 1 || f > pages) System.out.format("Pagina Invalida. Insira uma página entre 1 e %d.\n", pages);
                            else {
                                k = (f * 15) - 15;
                                j = f;
                                t = k;
                                break;
                            }
                        }while(f < 1 || f > pages);
                        break;
                    }
                    case "O":
                        while(!limiteValido(m)) {
                            m = getInt("Opção (número da lista):");
                        }
                        break label;

                    case "M":
                        m = -1;
                        break label;
                }
            } while(ch.equals("O")||ch.equals("M"));
        } while(j<=pages && t<i);
        return m;
    }


    /**
     * Método responsável pelo output da query 10
     * Primeiro mostra um menu que divide os produtos por grupos, o utilizador escolhe o número
     * do grupo onde está o(s) produto(S) que quer verificar e segundo a opção escolhida, é dividida
     * a lista l na subList que contém esse grupo de produtos.
     * @param l Lista de produto, faturação mês a mês para cada filial
     * @param time tempo que demorou a executar a query
     */
    public void show_q10(List<Map.Entry<String, List<Double>>> l, String time){
        System.out.println(time);
        int i = 0;
        int atual=0;
        int o = -2;
        l.sort(Map.Entry.comparingByKey());
        List<String> qField = l.stream().map(Map.Entry::getKey).collect(Collectors.toList());
        do {
            o = menuQ10(qField);
            if(o!=-1) {
                int nr = getInt("Introduza o número de elementos por página:");
                List<Map.Entry<String, List<Double>>> newL = l.subList(o * 1000, o * 1000 + 1000);
                List<String> prodI = new ArrayList<>();
                for (Map.Entry<String, List<Double>> p : newL) {
                    if (!l.get(l.indexOf(p) + 1).getKey().equals(p.getKey())) atual++;
                    for (i = 0; i < 36; i++) {
                        prodI.add("Produto " + atual + ": " + p.getKey() + " | " + "Filial: " + (i / 12 + 1) + " | " + "Mês: " + (i % 12 + 1) + " | " + "Faturação: " + p.getValue().get(i));
                    }
                }
                navegador(prodI, nr, "Informação do Produto");
            }
        } while(o!=-1);

    }

    /**
     * Método responsável pelo output da query estatistica 1
     * @param l Dados referentes aos ficheiros lidos
     * @param time tempo que demorou a executar a query
     */
    public void show_q11(Map.Entry<String,Map.Entry<List<Integer>,Double>> l , String time){
        System.out.println("\n"+time);
        System.out.println(ANSI_BOLD+"Ficheiro de vendas lido : " +ANSI_RESET+ l.getKey());
        System.out.println(ANSI_BOLD+"Número  total  de  registos  de  venda  errados: "+ANSI_RESET  + l.getValue().getKey().get(0));
        System.out.println(ANSI_BOLD+"Número  total  de produtos: "+ANSI_RESET  + l.getValue().getKey().get(1));
        System.out.println(ANSI_BOLD+"Número  total  de diferentes  produtos  comprados: "+ANSI_RESET  + l.getValue().getKey().get(2));
        System.out.println(ANSI_BOLD+"Número  total  de produtos não comprados: "+ANSI_RESET  + l.getValue().getKey().get(3));
        System.out.println(ANSI_BOLD+"Número total de clientes: "+ANSI_RESET  + l.getValue().getKey().get(4));
        System.out.println(ANSI_BOLD+"Número total dos clientes que realizaram compras: "+ANSI_RESET  + l.getValue().getKey().get(5));
        System.out.println(ANSI_BOLD+"Número total de clientes que nada compraram: "+ANSI_RESET  + l.getValue().getKey().get(6));
        System.out.println(ANSI_BOLD+"Número total de compras de valor total igual a 0.0: "+ANSI_RESET  + l.getValue().getKey().get(7));
        System.out.println(ANSI_BOLD+"Faturação: "+"\033[0m"  + l.getValue().getValue());
    }

    /**
     * Método responsável pelo output da query estatistica 12
     * @param l Dados referentes à estrutura de dados
     * @param time tempo que demorou a executar a query
     */
    public void show_q12(Map.Entry<Map<Integer, Integer>, Map.Entry<List<Map<Integer,Double>>,List<Map<Integer,Integer>>>> l, String time){
        System.out.println(time);
        int nr=-1;
        System.out.println("1. Número total de compras por mês\n" +
                "2. Faturação total por mês para cada filial e o valor total global\n" +
                "3. Número de distintos clientes que compraram em cada mês filial a filial");

        while(!limiteValido(nr)||nr>3) {
            nr = getInt("Introduza uma opção:");
        }
        if(nr==1){
            for (Map.Entry<Integer,Integer> entry : l.getKey().entrySet()){
                System.out.println(ANSI_BOLD+"Mês"+String.format("%2d",(entry.getKey()+1))+": "+ANSI_RESET  + " | Compras: " + entry.getValue());
            }
        }
        if(nr==2){
            System.out.println(ANSI_BOLD+String.format("%21s %25s %23s %23s","Filial 1","Filial 2","Filial 3","Total")+ANSI_RESET);
            for(int i =0; i<12; i++){
                System.out.println(ANSI_BOLD+"Mês"+String.format("%2d",(i+1))+": "+ANSI_RESET
                        + String.format("%-25s",l.getValue().getKey().get(0).get(i))
                        + String.format("%-25s",l.getValue().getKey().get(1).get(i))
                        + String.format("%-25s",l.getValue().getKey().get(2).get(i))
                        + String.format("%-25s",(l.getValue().getKey().get(0).get(i)+l.getValue().getKey().get(1).get(i)+l.getValue().getKey().get(2).get(i))));
            }
        }
        if(nr==3){
            System.out.println(ANSI_BOLD+String.format("%17s %20s %18s","Filial 1","Filial 2","Filial 3")+ANSI_RESET);
            for(int i =0; i<12; i++){
                System.out.println(ANSI_BOLD+"Mês"+String.format("%2d",(i+1))+": "+ANSI_RESET
                        + String.format("%8s",l.getValue().getValue().get(0).get(i))
                        + String.format("%21s",l.getValue().getValue().get(1).get(i))
                        + String.format("%19s",l.getValue().getValue().get(2).get(i)));
            }
        }
    }

    /**
     * Método responsável pelo output da opçao Save
     * @param file nome do ficheiro escolhido
     */
    public void show_save(String file){
        String CSI = "\u001B[";
        System.out.println(CSI + "32" + "m");
        System.out.println("Estado guardado com sucesso!");
        System.out.println(file);
        System.out.print (CSI  + "m");
    }

    /**
     * Método responsável pelo output da opção LOAD
     * @param file nome do ficheiro carregado
     */
    public void show_load(String file){
        String CSI = "\u001B[";
        System.out.println(CSI + "32" + "m");
        System.out.println("Estado carregado com sucesso!");
        System.out.println(file);
        System.out.print (CSI  + "m");
    }

    /**
     * Mensagem de saída
     */
    public void show_q15(){
        String CSI = "\u001B[";
        System.out.print (ANSI_YELLOW);
        System.out.println("/////////////////////////////////////////////////////////////");
        System.out.println("\tMVC - Gestão das Vendas de uma Cadeia de Distribuição\t\t");
        System.out.println("\n\t\t@author Leonardo de Freitas Marreiros - A89537\n");
        System.out.println("/////////////////////////////////////////////////////////////");
        System.out.print (ANSI_RESET);
    }

    /**
     * menu de opções do navegador
     * @return opção escolhida
     */
    static String menuNav(){
        String txt ="";
        System.out.print("\033[1m"+"Pagina Seguinte       (P)\nVoltar ao Menu        (M)\nPagina Anterior       (O)\nEscolher Pagina       (E)\nVer quantidade total  (Q)\nProcurar por elemento (S)\n"+"\033[0m");
        do{
            System.out.println("Escolha uma Opção: ");
            Scanner input = new Scanner(in);
            boolean ok = false;
            while(!ok) {
                try {
                    txt = input.nextLine();
                    ok = true;
                }
                catch(InputMismatchException e)
                { out.println("Texto Invalido");
                    out.print("Novo valor: ");
                    input.nextLine();
                }
            }
        } while(!(txt.equals("P")) && !(txt.equals("M")) && !(txt.equals("O")) && !(txt.equals("E")) && !(txt.equals("Q")) && !(txt.equals("S")));
        return txt;
    }


    /**
     * Navegador de Listas
     * @param l Lista que se quer dividir
     * @param nrEntries número de elementos por página
     * @param message Informação acerca da lista
     */
    public void navegador (List<String> l, int nrEntries, String message) {
        int i;
        i=l.size();
        int pages= i / nrEntries;
        if ((i%nrEntries)!=0) pages=pages+1;

        int j=1;
        int k=0;
        int t=0;
        String ch;
        int temp1=0;
        int temp2=0;
        int n;
        Scanner sc = new Scanner(System.in);
        label:
        do {
            temp1=t;
            System.out.format("\033[1m"+"%s\n\n"+"\033[0m", message);
            for(n=0;n<nrEntries&&t<i;n++){
                System.out.format("\t%2d. %s\n",n+k+1, l.get(k+n));
                t++;
            }
            temp2=k;
            k+=nrEntries;
            System.out.format("\033[1m"+"\nPage <%d/%d> \n\n"+"\033[0m",j ,pages);
            j++;

            do {

                switch (ch=menuNav()) {
                    case "P":
                        if (j == pages + 1) {
                            j = 1;
                            t = 0;
                            k = 0;
                            System.out.print("You are already on the last page!\nPress C to return to the first page\n");
                            while (!sc.nextLine().equals("C")) ;
                            System.out.print("\033[2J");
                        }
                        break;
                    case "M":
                        break label;
                    case "O":
                        if (j != 2) {
                            k = temp2 - nrEntries;
                            j = j - 2;
                            t=temp1-nrEntries;
                        } else {
                            System.out.print("You are already on the first page!\nPress C to continue\n");
                            while (!sc.nextLine().equals("C")) ;
                        }
                        break;
                    case "E": {
                        System.out.print("\nEscolha o numero da pagina: ");
                        int f;
                        do {
                            f = sc.nextInt();
                            if (f < 1 || f > pages) System.out.format("Pagina Invalida. Insira uma página entre 1 e %d.\n", pages);
                            else {
                                k = (f * nrEntries) - nrEntries;
                                j = f;
                                t = k;
                                break;
                            }
                        }while(f < 1 || f > pages);
                        break;
                    }
                    case "Q":
                        System.out.format("Quantidade Total: %d\n", i);
                        System.out.print("Press C to continue\n");
                        while (!sc.nextLine().equals("C")) ;
                        k = temp2;
                        j = j - 1;
                        t = temp1;
                        break;
                    case "S":
                        System.out.print("\nEscolha o elemento a procurar: ");
                        String p = sc.nextLine();
                        int index = -2;
                        for(String listItem : l) {
                            if (listItem.indexOf(p) > p.length()) {
                                index = l.indexOf(listItem);
                                break;
                            }
                        }
                        if (index==-2) {
                            System.out.print("Elemento não existe\n");
                            System.out.print("Press C to continue\n");
                            while (!sc.nextLine().equals("C")) ;
                            k = temp2;
                            j = j - 1;
                            t = temp1;
                        } else {
                            j = (index / nrEntries) + 1;
                            k = (j * nrEntries) - nrEntries;
                            t = k;
                            System.out.format("Elemento encontrado na posição: %d!\n\n", index+1);
                        }
                        break;
                    }
            } while(ch.equals("M"));
        } while(j<=pages && t<i);
    }

    /**
     * Output da exception InvalidClientException
     */
    public void showInvalidClientException(){
        System.out.println(ANSI_RED + "Cliente Não Existe!" + ANSI_RESET);
    }

    /**
     * Output da exception InvalidProductException
     */
    public void showInvalidProductException(){
        System.out.println(ANSI_RED + "Produto Não Existe!" + ANSI_RESET);
    }

    /**
     * Output da exception NoFileException
     */
    public void showNoFileException(){
        System.out.println(ANSI_RED + "Ficheiro Não Existe!" + ANSI_RESET);
    }
}


