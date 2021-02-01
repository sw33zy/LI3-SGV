package View;

import java.util.List;
import java.util.Map;

public interface IView {
    void  menu ();
    void promptEnterKey();
    int getInt(String message);
    String getInputString(String message);
    boolean mesValido(int mes);
    boolean filialValido(int filial);
    boolean opcaoValido(int op);
    boolean limiteValido(int op);
    void show_q0(int x, String time);
    void show_q1(List<String> l, String time);
    void show_q2(Map.Entry<Integer, Integer> sales, int mes, int filial, String time);
    void show_q3(List<Map.Entry<Integer, Map.Entry<Integer, Double>>> res, String client, String time);
    void show_q4(List<Map.Entry<Integer, Map.Entry<Integer, Double>>> res, String product, String time);
    void show_q5(List<Map.Entry<String,Integer>> ft, String time);
    void show_q6(List<Map.Entry<Map.Entry<String,Integer>,Integer>> ft, String time);
    void show_q7(List<Map.Entry<String,Double>> values, String time);
    void show_q8(List<Map.Entry<String, Integer>> l, String time);
    void show_q9(List<Map.Entry<String, Map.Entry<Integer, Double>>> l, String time);
    void show_q10(List<Map.Entry<String, List<Double>>> l, String time);
    void show_q11(Map.Entry<String,Map.Entry<List<Integer>,Double>> l , String time);
    void show_q12(Map.Entry<Map<Integer, Integer>, Map.Entry<List<Map<Integer,Double>>,List<Map<Integer,Integer>>>> l, String time);
    void show_save(String file);
    void show_load(String file);
    void show_q15();
    void navegador (List<String> l, int nrEntries, String message);
    void showInvalidClientException();
    void showInvalidProductException();
    void showNoFileException();
}
