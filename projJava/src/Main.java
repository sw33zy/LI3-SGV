import Controller.Controller;
import Model.GestaoVendas;
import Model.IGestaoVendas;
import View.IView;
import View.View;

public class Main {
    public static void main(String[] args) {

        IGestaoVendas sgv = new GestaoVendas();
        IView view = new View();

        Controller controller = new Controller();
        controller.setView(view);
        controller.setModel(sgv);
        controller.run();
    }
}
