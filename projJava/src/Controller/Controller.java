package Controller;


import Exceptions.InvalidClientException;
import Exceptions.InvalidProductException;
import Model.Crono;
import Model.GestaoVendas;
import Model.IGestaoVendas;
import View.IView;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class Controller implements IController{
    private IGestaoVendas sgv;
    private IView view;
    private final Crono crono;

    /**
     * Construtor do Controller
     */
    public Controller() {
        this.crono = new Crono();
    }

    /**
     * Setter do Model
     * @param sgv model que quer utilizar
     */
    public void setModel(IGestaoVendas sgv) {
        this.sgv = sgv;
    }

    /**
     * Setter da View
     * @param view view que quer utilizar
     */
    public void setView(IView view) {
        this.view = view;
    }

    /**
     * Função que Realiza todas as queries pretendidas
     */
    public void run() {

        int opcao=-1;
        String fCl = "",fPd = " ",fVd = " ";
        do {
            this.view.menu();
            opcao =this.view.getInt("Insira uma opção: ");

            switch (opcao) {

                case 0: {
                    this.view.show_q0(0,"");
                    while(!this.view.opcaoValido(opcao)) {
                        opcao = this.view.getInt("Insira uma opção: ");
                    }
                    if (opcao==1){
                        fPd= "Produtos.txt";
                        fCl = "Clientes.txt";
                        fVd = "Vendas_1M.txt";
                    }
                    else if (opcao==2) {
                        fPd = this.view.getInputString("Insira o Ficheiro dos Produtos: ");
                        fCl = this.view.getInputString("Insira o Ficheiro dos Clientes: ");
                        fVd = this.view.getInputString("Insira o Ficheiro das Vendas: ");
                    }
                    try {
                        this.view.show_q0(2,"");
                        this.crono.start();
                        this.sgv = new GestaoVendas(fCl, fPd, fVd);
                        this.crono.stop();
                    }
                    catch(IOException e) {this.view.showNoFileException();this.view.promptEnterKey();}
                    this.view.show_q0(1, this.crono.getTImeString());
                    break;
                }
                case 1:{
                    this.crono.start();
                    List<String> l= this.sgv.prodsNComprados();
                    this.crono.stop();
                    this.view.show_q1(l,this.crono.getTImeString());
                    break;
                }
                case 2:{
                    int f=-1,m=-1;
                    Map.Entry<Integer,Integer> r;
                    while(!this.view.mesValido(m)) {
                        m = this.view.getInt("Insira um mês [0-12]: ");
                    }
                    while(!this.view.filialValido(f)) {
                        f = this.view.getInt("Insira uma filial[1-3] (0 para Total): ");
                    }
                    this.crono.start();
                    r=this.sgv.clientesVendasTotais(f,m);
                    this.crono.stop();
                    this.view.show_q2(r,m,f,this.crono.getTImeString());
                    this.view.promptEnterKey();
                    break;
                }
                case 3: {
                    try {
                        String client = this.view.getInputString("Insira um Cliente: ");
                        this.crono.start();
                        List<Map.Entry<Integer, Map.Entry<Integer, Double>>> res = this.sgv.getClientHistory(client);
                        this.crono.stop();
                        this.view.show_q3(res, client, this.crono.getTImeString());
                        this.view.promptEnterKey();
                    }
                    catch (InvalidClientException e) { this.view.showInvalidClientException(); this.view.promptEnterKey();}
                    break;
                }
                case 4: {
                    try {
                        String product = this.view.getInputString("Insira um Produto: ");
                        this.crono.start();
                        List<Map.Entry<Integer, Map.Entry<Integer, Double>>> res = this.sgv.getProductHistory(product);
                        this.crono.stop();
                        this.view.show_q4(res, product, this.crono.getTImeString());
                        this.view.promptEnterKey();
                    }
                    catch (InvalidProductException e) {this.view.showInvalidProductException(); this.view.promptEnterKey();}
                    break;
                }
                case 5: {
                    try {
                        List<Map.Entry<String, Integer>> ft = new ArrayList<>();
                        String client = this.view.getInputString("Insira um Cliente: ");
                        this.crono.start();
                        ft = this.sgv.query5(client);
                        this.crono.stop();
                        this.view.show_q5(ft, this.crono.getTImeString());
                    }
                    catch (InvalidClientException e) { this.view.showInvalidClientException(); this.view.promptEnterKey();}
                    break;
                }
                case 6: {
                    int nr=-1;
                    while(!this.view.limiteValido(nr)) {
                        nr = this.view.getInt("Introduza o limite:");
                    }
                    this.crono.start();
                    List<Map.Entry<Map.Entry<String, Integer>, Integer>> res = this.sgv.topXProds(nr);
                    this.crono.stop();
                    this.view.show_q6(res,this.crono.getTImeString());
                    break;
                }
                case 7: {
                    this.crono.start();
                    List<Map.Entry<String, Double>> res = this.sgv.top3Buyers();
                    this.crono.stop();
                    this.view.show_q7(res,this.crono.getTImeString());
                    this.view.promptEnterKey();
                    break;
                }
                case 8: {
                    int nr=-1;
                    while(!this.view.limiteValido(nr)) {
                        nr = this.view.getInt("Introduza o limite:");
                    }
                    this.crono.start();
                    List<Map.Entry<String, Integer>> res = this.sgv.topMostDiverse().subList(0,nr);
                    this.crono.stop();
                    this.view.show_q8(res,this.crono.getTImeString());
                    break;
                }
                case 9: {
                    try {
                        String produto = this.view.getInputString("Insira um Produto: ");
                        int nr=-1;
                        while(!this.view.limiteValido(nr)) {
                            nr = this.view.getInt("Introduza o limite:");
                        }
                        this.crono.start();
                        List<Map.Entry<String, Map.Entry<Integer, Double>>> res = this.sgv.topClientsProd(produto).subList(0, nr)
                                .stream().filter(a -> a.getValue().getValue() != 0).collect(Collectors.toList());
                        this.crono.stop();
                        this.view.show_q9(res, this.crono.getTImeString());
                    }
                    catch (InvalidProductException e) {this.view.showInvalidProductException(); this.view.promptEnterKey();}
                    break;
                }
                case 10: {
                    this.crono.start();
                    List<Map.Entry<String, List<Double>>> l= this.sgv.faturacaoPorProd();
                    this.crono.stop();
                    this.view.show_q10(l,this.crono.getTImeString());
                    this.view.promptEnterKey();
                    break;
                }
                case 11: {
                    this.crono.start();
                    Map.Entry<String, Map.Entry<List<Integer>, Double>> res = this.sgv.estatisticas1();
                    this.crono.stop();
                    this.view.show_q11(res,this.crono.getTImeString());
                    this.view.promptEnterKey();
                    break;
                }
                case 12:{
                    this.crono.start();
                    Map.Entry<Map<Integer, Integer>, Map.Entry<List<Map<Integer,Double>>,List<Map<Integer,Integer>>>> l =
                            this.sgv.estatisticas2();
                    this.crono.stop();
                    this.view.show_q12(l,this.crono.getTImeString());
                    this.view.promptEnterKey();
                    break;
                }
                case 13:  {
                    try {
                        String file = this.view.getInputString("Nome do ficheiro a guardar: ");
                        this.sgv.save(file,this.sgv);
                        this.view.show_save(file);
                        this.view.promptEnterKey();
                    } catch (IOException e) {
                        this.view.showNoFileException(); this.view.promptEnterKey();
                    }
                    break;

                }
                case 14:{
                    try {
                        String file = this.view.getInputString("Nome do ficheiro a carregar: ");
                        this.sgv = this.sgv.load(file);
                        this.view.show_load(file);
                        this.view.promptEnterKey();
                    } catch (IOException | ClassNotFoundException e) {
                        this.view.showNoFileException(); this.view.promptEnterKey();
                    }
                    break;
                }
                case 15:{
                    this.view.show_q15();
                    break;
                }
            }
        }
        while (opcao!=15);
    }


}



